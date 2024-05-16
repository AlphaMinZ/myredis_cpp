#ifndef __ALPHA_MYREDIS_DATASTORE_H__
#define __ALPHA_MYREDIS_DATASTORE_H__

#include <memory>
#include "../database/struct.h"

namespace alphaMin {

class String : public CmdAdpter {
public:
    typedef std::shared_ptr<String> ptr;

    virtual std::string bytes() = 0;
};

class stringEntity : public String {
public:
    typedef std::shared_ptr<stringEntity> ptr;

    stringEntity(std::string key, std::string str)
        :m_key(key)
        ,m_str(str) {}

    virtual std::string bytes() override;

    virtual std::vector<std::string> toCmd() override;
private:
    std::string m_key;
    std::string m_str;
};

}

#endif