#ifndef __ALPHA_MYREDIS_HANDLER_STRUCT_H__
#define __ALPHA_MYREDIS_HANDLER_STRUCT_H__

#include <string>
#include <memory>
#include <vector>
#include "../../lib/alpha/channel.h"
#include "../../lib/alpha/stream.h"

namespace alphaMin {

#define UnknownErrReplyBytes "-ERR unknown\r\n"

class Reply {
public:
    typedef std::shared_ptr<Reply> ptr;

    virtual ~Reply();
    virtual std::string toString() = 0;
};

class MultiReply {
public:
    typedef std::shared_ptr<MultiReply> ptr;

    virtual ~MultiReply();
    virtual std::vector<std::string> args() = 0;
};

struct Droplet {
    typedef std::shared_ptr<Droplet> ptr;

    bool terminated();

    Reply::ptr reply;
};

class DB {
public:
    typedef std::shared_ptr<DB> ptr;

    virtual ~DB();

    virtual Reply::ptr Do(std::vector<std::string> cmdLine) = 0;
    virtual void close () = 0;
};

class Parser {
public:
    typedef std::shared_ptr<Parser> ptr;

    virtual ~Parser();
    virtual Chan<Droplet::ptr>::ptr parseStream(Stream::ptr reader) = 0;
};

}

#endif