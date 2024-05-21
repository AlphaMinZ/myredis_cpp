#ifndef __ALPHA_MYREDIS_DATASTORE_H__
#define __ALPHA_MYREDIS_DATASTORE_H__

#include <memory>
#include "../database/struct.h"

namespace alphaMin {

class List : public CmdAdpter {
public:
    typedef std::shared_ptr<List> ptr;

    virtual void lPush(std::string value) = 0;
    virtual void lPush(std::vector<std::string> values) = 0;

    virtual std::vector<std::string> lPop(int64_t cnt) = 0;

    virtual void rPush(std::string value) = 0;
    virtual void rPush(std::vector<std::string> values) = 0;

    virtual std::vector<std::string> rPop(int64_t cnt) = 0;

    virtual int64_t len() = 0;

    virtual std::vector<std::string> range(int64_t start, int64_t stop) = 0;
};

class listEntity : public List {
public:
    typedef std::shared_ptr<listEntity> ptr;

    listEntity(std::string key, std::vector<std::string> elements)
        :m_key(key)
        ,m_data(elements) {}

    virtual void lPush(std::string value) override;
    virtual void lPush(std::vector<std::string> values) override;

    virtual std::vector<std::string> lPop(int64_t cnt) override;

    virtual void rPush(std::string value) override;
    virtual void rPush(std::vector<std::string> values) override;

    virtual std::vector<std::string> rPop(int64_t cnt) override;

    virtual int64_t len() override;

    virtual std::vector<std::string> range(int64_t start, int64_t stop) override;

    virtual std::vector<std::string> toCmd() override;

private:
    std::string m_key;
    std::vector<std::string> m_data;
};

}

#endif
