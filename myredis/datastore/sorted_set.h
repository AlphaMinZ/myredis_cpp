#ifndef __ALPHA_MYREDIS_DATASTORE_SORTED_SET_H__
#define __ALPHA_MYREDIS_DATASTORE_SORTED_SET_H__

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace alphaMin {

class SortedSet : public CmdAdpter {
public:
    typedef std::shared_ptr<SortedSet> ptr;

    virtual ~SortedSet() {}

    virtual void add(int64_t score, std::string member) = 0;
    virtual int64_t rem(std::string member) = 0;
    virtual std::vector<std::string> range(int64_t score1, int64_t score2) = 0;
};

struct skipnode {
    typedef std::shared_ptr<skipnode> ptr;

    skipnode(int64_t score, int64_t height) 
        :score_(score) {
        nexts_.reserve(height);
    }

    int64_t score_;
    std::unordered_set<std::string> members_;
    std::vector<skipnode::ptr> nexts_;
};

class skiplist : public SortedSet {
public:
    typedef std::shared_ptr<skiplist> ptr;

    skiplist() {}

    skiplist(std::string key)
        :m_key(key)
        ,m_head(std::make_shared<skipnode>(0, 0)) {}

    void add(int64_t score, std::string member) override;

    int64_t rem(std::string member) override;

    std::vector<std::string> range(int64_t score1, int64_t score2) override;

    std::vector<std::string> toCmd();

private:
    int64_t roll();

    void rem(int64_t score, std::string member);

private:
    std::string m_key;
    std::unordered_map<int64_t, skipnode::ptr> m_scoreToNode;
    std::unordered_map<std::string, int64_t> m_memberToScore;
    skipnode::ptr m_head;
};

}

#endif