#include "kv_store.h"

namespace alphaMin {

void KVStore::gc() {
    // 找出当前所有已过期的 key，批量回收
    uint64_t currentMs = GetCurrentMS();

    for(auto& expiredKey : m_expireTimeWheel->range(0, currentMs)) {
        expirePreprocess(expiredKey);
    }
}

void KVStore::expirePreprocess(std::string key) {
    auto expiredAt = m_expireAt.find(key);
    if(expiredAt == m_expireAt.end()) {
        return;
    }

    if(expiredAt->second > GetCurrentMS()) {
        return;
    }

    expireProcess(key);
}

void KVStore::expireProcess(std::string key) {
    m_expireAt.erase(key);
    m_data.erase(key);
    m_expireTimeWheel->rem(key);
}

void KVStore::expire(std::string key, uint64_t expiredAt) {
    auto it = m_data.find(key);
    if(it == m_data.end()) {
        return;
    }
    m_expireAt[key] = expiredAt;
    m_expireTimeWheel->add(expiredAt, key);
}

}