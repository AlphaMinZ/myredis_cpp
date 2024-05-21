#ifndef __ALPHA_MYREDIS_DATASTORE_HASH_H__
#define __ALPHA_MYREDIS_DATASTORE_HASH_H__

#include <memory>
#include "../database/struct.h"

namespace alphaMin {

class HashMap : public CmdAdpter {
public:
    typedef std::shared_ptr<HashMap> ptr;

    virtual void put(std::string key, std::string value) = 0;

    virtual std::string get(std::string key) = 0;

    virtual int64_t del(std::string key) = 0;
};

class hashMapEntity : public HashMap {
public:
    typedef std::shared_ptr<hashMapEntity> ptr;

    hashMapEntity(std::string key)
        :m_key(key) {}

    virtual void put(std::string key, std::string value) override;

    virtual std::string get(std::string key) override;

    virtual int64_t del(std::string key) override;

    virtual std::vector<std::string> toCmd() override;

private:
    std::string m_key;
    std::unordered_map<std::string, std::string> m_data;
};

};

#endif