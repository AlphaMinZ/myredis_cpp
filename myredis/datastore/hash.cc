#include "hash.h"
#include "kv_store.h"

namespace alphaMin {

HashMap::ptr KVStore::getAsHashMap(std::string key) {
    auto v = get_data<HashMap::ptr>(key);
    if(v.get() == nullptr) {
        return std::make_shared<HashMap>();
    }

    return v;
}

void KVStore::putAsHashMap(std::string key, HashMap::ptr hmap) {
    set_data(key, hmap);
}

void hashMapEntity::put(std::string key, std::string value) {
    m_data[key] = value;
}

std::string hashMapEntity::get(std::string key) {
    return m_data[key];
}

int64_t hashMapEntity::del(std::string key) {
    auto has = m_data.count(key);
    if(!has) return 0;
    m_data.erase(key);
    return 1;
}

std::vector<std::string> hashMapEntity::toCmd() {
    std::vector<std::string> args;
    args.reserve(2 + 2 * m_data.size());
    args.push_back(CmdTypeHSet);
    args.push_back(m_key);
    for(auto& kv : m_data) {
        args.push_back(kv.first);
        args.push_back(kv.second);
    }

    return args;
}

}