#include "set.h"
#include "kv_store.h"

namespace alphaMin {

Set::ptr KVStore::getAsSet(std::string key) {
    auto v = get_data<Set::ptr>(key);
    if(v.get() == nullptr) {
        return std::shared_ptr<Set>(nullptr);
    }

    return v;
}
 
void KVStore::putAsSet(std::string key, Set::ptr set) {
    set_data(key, set);
}

int64_t setEntity::add(std::string value) {
    auto has = m_container.count(value);
    if(has) {
        return 0;
    }
    m_container.insert(value);
    return 1;
}

int64_t setEntity::exist(std::string value) {
    return m_container.count(value);
}

int64_t setEntity::rem(std::string value) {
    if(m_container.count(value)) {
        m_container.erase(value);
        return 1;
    }
    return 0;
}

std::vector<std::string> setEntity::toCmd() {
    std::vector<std::string> args;
    args.reserve(2 + m_container.size());
    args.push_back(CmdTypeSAdd);
    args.push_back(m_key);
    for(auto& value : m_container) {
        args.push_back(value);
    }

    return args;
}

}