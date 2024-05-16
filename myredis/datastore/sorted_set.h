#ifndef __ALPHA_MYREDIS_DATASTORE_SORTED_SET_H__
#define __ALPHA_MYREDIS_DATASTORE_SORTED_SET_H__

#include <memory>
#include <vector>
#include <string>

namespace alphaMin {

class SortedSet {
public:
    typedef std::shared_ptr<SortedSet> ptr;

    virtual ~SortedSet() {}

    virtual void add(int64_t score, std::string member) = 0;
    virtual int64_t rem(std::string member) = 0;
    virtual std::vector<std::string> range(int64_t score1, int64_t score2) = 0;
};

}

#endif