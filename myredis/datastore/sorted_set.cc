#include "sorted_set.h"
#include "kv_store.h"
#include <limits>
#include <random>

namespace alphaMin {

void skiplist::add(int64_t score, std::string member) {
    // 之前存在，需要删除
    auto oldScore = m_memberToScore.find(member);
    if(oldScore != m_memberToScore.end()) {
        if(oldScore->second == score) return;
        rem(oldScore->second, member);
    }

    m_memberToScore[member] = score;
    auto node = m_scoreToNode.find(score);
    if(node != m_scoreToNode.end()) {
        node->second->members_.insert(member);
        return;
    }

    // 新插入，roll 出高度
    auto height = roll();
    while(m_head->nexts_.size() < height + 1) {
        m_head->nexts_.push_back(std::shared_ptr<skipnode>(nullptr));
    }

    skipnode::ptr inserted(new skipnode(score, height + 1));
    inserted->members_.insert(member);
    m_scoreToNode[score] = inserted;

    auto move = m_head;
    for(int i = height; i >= 0; --i) {
        while(move->nexts_[i].get() != nullptr && move->nexts_[i]->score_ < score) {
            move = move->nexts_[i];
            // move = std::move(move->nexts_[i]);
            continue;
        }

        inserted->nexts_[i] = move->nexts_[i];
        move->nexts_[i] = inserted;
    }
}

int64_t skiplist::rem(std::string member) {
    // 之前存在，需要删除
    auto score = m_memberToScore.find(member);
    if(score == m_memberToScore.end()) {
        return 0;
    }
    rem(score->second, member);
    return 1;
}

std::vector<std::string> skiplist::range(int64_t score1, int64_t score2) {
    if(-1 == score2) {
        score2 = std::numeric_limits<int>::max();
    }

    if(score1 > score2) {
        
    }

    auto move = m_head;
    for(int i = m_head->nexts_.size() - 1; i >= 0; --i) {
        while(move->nexts_[i].get() != nullptr && move->nexts_[i]->score_ < score1) {
            move = move->nexts_[i];
        }
    }

    // 来到了 level0 层，move.nexts[i] 如果存在，就是首个 >= score1 的元素
    if(move->nexts_.size() == 0 || move->nexts_[0].get() == nullptr) {
        return std::vector<std::string>();
    }

    std::vector<std::string> res;
    while(move->nexts_[0].get() != nullptr && move->nexts_[0]->score_ >= score1 && move->nexts_[0]->score_ <= score2) {
        for(auto& member : move->nexts_[0]->members_) {
            res.push_back(member);
        }
        move = move->nexts_[0];
    }
    return res;
}

std::vector<std::string> skiplist::toCmd() {
    std::vector<std::string> args;
    args.reserve(2 + 2 * m_memberToScore.size());
    args.push_back(CmdTypeZAdd);
    args.push_back(m_key);

    for(auto& pair : m_memberToScore) {
        args.push_back(std::to_string(pair.second));
        args.push_back(pair.first);
    }
    return args;
}

int64_t skiplist::roll() {
    int64_t level = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    while(dis(gen) > 0) {
        level++;
    }

    return level;
}

void skiplist::rem(int64_t score, std::string member) {
    m_memberToScore.erase(member);
    auto skipnode = m_scoreToNode[score];

    skipnode->members_.erase(member);
    if(skipnode->members_.size() > 0) {
        return;
    }

    m_scoreToNode.erase(score);
    auto move = m_head;
    for(int i = m_head->nexts_.size() - 1; i >= 0; --i) {
        while(move->nexts_[i].get() != nullptr && move->nexts_[i]->score_ < score) {
            move = move->nexts_[i];
        }

        if(move->nexts_[i].get() == nullptr || move->nexts_[i]->score_ > score) {
            continue;
        }

        auto remed = move->nexts_[i];
        move->nexts_[i] = move->nexts_[i]->nexts_[i];
        remed->nexts_[i] = std::shared_ptr<alphaMin::skipnode>(nullptr);
    }
}

}