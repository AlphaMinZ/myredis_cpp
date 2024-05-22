#include "list.h"
#include "kv_store.h"

namespace alphaMin {

List::ptr KVStore::getAsList(std::string key) {
    auto v = get_data<List::ptr>(key);
    if(v.get() == nullptr) {
        return std::shared_ptr<List>(nullptr);
    }

    return v;
}
    
void KVStore::putAsList(std::string key, List::ptr list) {
    set_data(key, list);
}

void listEntity::lPush(std::string value) {
    m_data.insert(m_data.begin(), value);
}

void listEntity::lPush(std::vector<std::string> values) {
    // 在 vector 的开头插入多个元素
    m_data.insert(m_data.begin(), values.begin(), values.end());
}

std::vector<std::string> listEntity::lPop(int64_t cnt) {
    if(cnt >= m_data.size()) {
        std::vector<std::string> popped = std::move(m_data);
        m_data.clear();
        return popped;
    }

    std::vector<std::string> popped(m_data.begin(), m_data.begin() + cnt);
    m_data.erase(m_data.begin(), m_data.begin() + cnt);
    return popped;
} 

void listEntity::rPush(std::string value) {
    m_data.push_back(value);
}

void listEntity::rPush(std::vector<std::string> values) {
    m_data.insert(m_data.end(), values.begin(), values.end());
}

std::vector<std::string> listEntity::rPop(int64_t cnt) {
    // 如果 cnt 大于 m_data 的大小，则返回整个列表
    if (cnt >= m_data.size()) {
        std::vector<std::string> popped = std::move(m_data);
        m_data.clear();
        return popped;
    }

    // 否则，返回列表的后 cnt 个元素
    std::vector<std::string> popped(m_data.end() - cnt, m_data.end());
    m_data.erase(m_data.end() - cnt, m_data.end());
    return popped;
}

int64_t listEntity::len() {
    return m_data.size();
}

std::vector<std::string> listEntity::range(int64_t start, int64_t stop) {
    if (stop == -1) {
        stop = static_cast<int64_t>(m_data.size() - 1);
    }

    if (start < 0 || start >= static_cast<int64_t>(m_data.size())) {
        return std::vector<std::string>();
    }

    if (stop < 0 || stop >= static_cast<int64_t>(m_data.size()) || stop < start) {
        return std::vector<std::string>();
    }

    return std::vector<std::string>(m_data.begin() + start, m_data.begin() + stop + 1);
}

std::vector<std::string> listEntity::toCmd() {
    std::vector<std::string> args;
    args.reserve(2 + 1 * m_data.size());
    args.push_back(CmdTypeRPush);
    args.push_back(m_key);
    args.insert(args.end(), m_data.begin(), m_data.end());
    return args;
}

}