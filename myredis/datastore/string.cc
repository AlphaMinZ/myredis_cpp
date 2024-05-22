#include "string.h"
#include "kv_store.h"

namespace alphaMin {

String::ptr KVStore::getAsString(std::string key) {
    auto v = get_data<String::ptr>(key);
    if(v.get() == nullptr) {
        return std::make_shared<String>();
    }

    return v;
}

int64_t KVStore::put(std::string key, std::string value, bool insertStrategy) {
    auto it = m_data.find(key);
    if(it != m_data.end() && insertStrategy) {
        return 0;
    }

    set_data(key, std::make_shared<String>(key, value));
    return 1;
}

std::string stringEntity::toString() {
    return m_str;
}

std::vector<std::string> stringEntity::toCmd() {
    std::vector<std::string> args;
    args.push_back(CmdTypeSet);
    args.push_back(m_key);
    args.push_back(m_str);
    return args;
}

}