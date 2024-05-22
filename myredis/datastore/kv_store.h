#ifndef __ALPHA_MYREDIS_DATASTORE_KV_STORE_H__
#define __ALPHA_MYREDIS_DATASTORE_KV_STORE_H__

#include <memory>
#include <string>
#include <unordered_map>
#include "sorted_set.h"
#include "../handler/persister.h"
#include "../handler/struct.h"
#include "../database/struct.h"
#include "hash.h"
#include "list.h"
#include "set.h"
#include "sorted_set.h"
#include "string.h"

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

    virtual void forEach(std::function<void(std::string, CmdAdpter::ptr, uint64_t)>) override;

    virtual void expirePreprocess(std::string key) override;
    virtual void gc() override;

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

    HashMap::ptr getAsHashMap(std::string key);
    void putAsHashMap(std::string key, HashMap::ptr hmap);

    List::ptr getAsList(std::string key);
    void putAsList(std::string key, List::ptr list);

    Set::ptr getAsSet(std::string key);
    void putAsSet(std::string key, Set::ptr set);

    String::ptr getAsString(std::string key);
    int64_t put(std::string key, std::string value, bool insertStrategy);

    // 向 m_data 写入数据的成员函数模板
    template<typename T>
    void set_data(const std::string& key, T&& value) {
        m_data[key] = std::make_shared<AnyDerived<std::decay_t<T> > >(std::forward<T>(value));
    }

    // 读取 m_data 中数据的成员函数模板
    template<typename T>
    T get_data(const std::string& key) const {
        auto it = m_data.find(key);
        if(it == m_data.end()) {
            return T{};
        }
    
        auto derived_ptr = std::dynamic_pointer_cast<AnyDerived<T> >(it->second);
        if(!derived_ptr) {
            return T{};
        }

        return derived_ptr->value_;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<AnyBase>> m_data;
    std::unordered_map<std::string, uint64_t> m_expireAt;

    SortedSet::ptr m_expireTimeWheel;

    Persister::ptr m_persister;
};

}

#endif