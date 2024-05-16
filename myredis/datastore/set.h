#ifndef __ALPHA_MYREDIS_DATASTORE_SET_H__
#define __ALPHA_MYREDIS_DATASTORE_SET_H__

#include <memory>
#include "../database/struct.h"

namespace alphaMin {

class Set : public CmdAdpter {
public:
    typedef std::shared_ptr<Set> ptr;

    virtual int64_t add(std::string value) = 0;

    virtual int64_t exist(std::string value) = 0;

    virtual int64_t rem(std::string value) = 0;
};

class setEntity : public Set {
public:
    typedef std::shared_ptr<setEntity> ptr;

    setEntity(std::string key)
        :m_key(key) {}

    virtual int64_t add(std::string value) override;

    virtual int64_t exist(std::string value) override;

    virtual int64_t rem(std::string value) override;

    virtual std::vector<std::string> toCmd() override;
private:
    std::string m_key;
    std::unordered_set<std::string> m_container;
};

}

#endif