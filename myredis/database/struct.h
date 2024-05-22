#ifndef __ALPHA_MYREDIS_DATABASE_STRUCT_H__
#define __ALPHA_MYREDIS_DATABASE_STRUCT_H__

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "../../lib/alpha/channel.h"
#include "../handler/struct.h"

namespace alphaMin {

using CmdReceiver = Chan<Reply::ptr>;
using CmdType = std::string;

const CmdType CmdTypeExpire = "expire";
const CmdType CmdTypeExpireAt = "expireat";

// string
const CmdType CmdTypeGet = "get";
const CmdType CmdTypeSet = "set";
const CmdType CmdTypeMGet = "mget";
const CmdType CmdTypeMSet = "mset";

// list
const CmdType CmdTypeLPush = "lpush";
const CmdType CmdTypeLPop = "lpop";
const CmdType CmdTypeRPush = "rpush";
const CmdType CmdTypeRPop = "rpop";
const CmdType CmdTypeLRange = "lrange";

// hash
const CmdType CmdTypeHSet = "hset";
const CmdType CmdTypeHGet = "hget";
const CmdType CmdTypeHDel = "hdel";

// set
const CmdType CmdTypeSAdd = "sadd";
const CmdType CmdTypeSIsMember = "sismember";
const CmdType CmdTypeSRem = "srem";

// sorted set
const CmdType CmdTypeZAdd = "zadd";
const CmdType CmdTypeZRangeByScore = "zrangebyscore";
const CmdType CmdTypeZRem = "zrem";

class Command {
public:
    typedef std::shared_ptr<Command> ptr;

    Command() {}

    Command(CmdType cmd, std::vector<std::string> args)
        :m_cmd(cmd)
        ,m_args(args) {}

    ~Command() {}

    CmdReceiver::ptr& getReceiver() { return m_receiver;}

    std::vector<std::string>& getArgs() { return m_args;}

    std::string getCmd() { return m_cmd;}

    Chan<void*>::ptr& getCancelc() { return m_cancelc;}

    void setCmd(CmdType cmd) { m_cmd = cmd;}

    void setArgs(std::vector<std::string> args) { m_args = args;}

    void setReceiver(CmdReceiver::ptr receiver) { m_receiver = receiver;}

    void setCancelc(Chan<void*>::ptr cancelc) { m_cancelc = cancelc;}
private:
    CmdType m_cmd;
    std::vector<std::string> m_args;
    CmdReceiver::ptr m_receiver;
    Chan<void*>::ptr m_cancelc;
};

class Executor {
public:
    typedef std::shared_ptr<Executor> ptr;

    virtual ~Executor() {}

    virtual Chan<Command::ptr>::ptr entrance() = 0;
    virtual bool validCommand(CmdType cmd) = 0;
    virtual void close() = 0;
};

class CmdAdpter {
public:
    typedef std::shared_ptr<CmdAdpter> ptr;

    virtual ~CmdAdpter() {}
    virtual std::vector<std::string> toCmd() = 0;
};

class DataStore {
public:
    typedef std::shared_ptr<DataStore> ptr;

    virtual void forEach(std::function<void(std::string, CmdAdpter::ptr, uint64_t)>) = 0;

    virtual void expirePreprocess(std::string key) = 0;
    virtual void gc() = 0;

    virtual Reply::ptr expire(Command::ptr) = 0;
    virtual Reply::ptr expireAt(Command::ptr) = 0;

    // string
    virtual Reply::ptr get(Command::ptr) = 0;
    virtual Reply::ptr mGet(Command::ptr) = 0;
    virtual Reply::ptr set(Command::ptr) = 0;
    virtual Reply::ptr mSet(Command::ptr) = 0;

    // list
    virtual Reply::ptr lPush(Command::ptr) = 0;
    virtual Reply::ptr lPop(Command::ptr) = 0;
    virtual Reply::ptr rPush(Command::ptr) = 0;
    virtual Reply::ptr rPop(Command::ptr) = 0;
    virtual Reply::ptr lRange(Command::ptr) = 0;

    // set
    virtual Reply::ptr sAdd(Command::ptr) = 0;
    virtual Reply::ptr sIsMember(Command::ptr) = 0;
    virtual Reply::ptr sRem(Command::ptr) = 0;

    // hash
    virtual Reply::ptr hSet(Command::ptr) = 0;
    virtual Reply::ptr hGet(Command::ptr) = 0;
    virtual Reply::ptr hDel(Command::ptr) = 0;
    
    // sorted set
    virtual Reply::ptr zAdd(Command::ptr) = 0;
    virtual Reply::ptr zRangeByScore(Command::ptr) = 0;
    virtual Reply::ptr zRem(Command::ptr) = 0;
};

}

#endif