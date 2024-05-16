#ifndef __ALPHA_MYREDIS_DATASTORE_KV_STORE_H__
#define __ALPHA_MYREDIS_DATASTORE_KV_STORE_H__

#include <memory>
#include <string>
#include <unordered_map>
#include "sorted_set.h"
#include "../handler/persister.h"
#include "../handler/struct.h"
#include "../database/struct.h"

namespace alphaMin {

class AnyBase {
public:
    virtual ~AnyBase() = default;
    virtual const std::type_info& type() const = 0;
};

template<typename T>
class AnyDerived : public AnyBase {
public:
    AnyDerived(const T& value)
        :value_(value) {}

    AnyDerived(T&& value)
        :value_(std::move(value)) {}

    const std::type_info& type() const override { return typeid(T);}
    T value_;
};

class KVStore : public DataStore {
public:
    typedef std::shared_ptr<KVStore> ptr;

    virtual Reply::ptr expire(Command::ptr cmd) override;
    virtual Reply::ptr expireAt(Command::ptr) override;

    // string
    virtual Reply::ptr get(Command::ptr) override;
    virtual Reply::ptr mGet(Command::ptr) override;
    virtual Reply::ptr set(Command::ptr) override;
    virtual Reply::ptr mSet(Command::ptr) override;

    // list
    virtual Reply::ptr lPush(Command::ptr) override;
    virtual Reply::ptr lPop(Command::ptr) override;
    virtual Reply::ptr rPush(Command::ptr) override;
    virtual Reply::ptr rPop(Command::ptr) override;
    virtual Reply::ptr lRange(Command::ptr) override;

    // set
    virtual Reply::ptr sAdd(Command::ptr) override;
    virtual Reply::ptr sIsMember(Command::ptr) override;
    virtual Reply::ptr sRem(Command::ptr) override;

    // hash
    virtual Reply::ptr hSet(Command::ptr) override;
    virtual Reply::ptr hGet(Command::ptr) override;
    virtual Reply::ptr hDel(Command::ptr) override;
    
    // sorted set
    virtual Reply::ptr zAdd(Command::ptr) override;
    virtual Reply::ptr zRangeByScore(Command::ptr) override;
    virtual Reply::ptr zRem(Command::ptr) override;

private:
    std::unordered_map<std::string, std::shared_ptr<AnyBase>> m_data;
    std::unordered_map<std::string, uint64_t> m_expireAt;

    SortedSet::ptr m_expireTimeWheel;

    Persister::ptr m_persister;
};

}

#endif