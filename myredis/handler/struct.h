#ifndef __ALPHA_MYREDIS_HANDLER_STRUCT_H__
#define __ALPHA_MYREDIS_HANDLER_STRUCT_H__

#include <string>
#include <memory>
#include <vector>
#include "../../lib/alpha/channel.h"
#include "../../lib/alpha/socket_stream.h"

namespace alphaMin {

#define UnknownErrReplyBytes "-ERR unknown\r\n"

class Reply {
public:
    typedef std::shared_ptr<Reply> ptr;

    virtual ~Reply() {};
    virtual std::string toString() = 0;
};

class MultiReply {
public:
    typedef std::shared_ptr<MultiReply> ptr;

    virtual ~MultiReply() {};
    virtual std::vector<std::string> getArgs() = 0;
};

class MultiBulkReply;

struct Droplet {
    typedef std::shared_ptr<Droplet> ptr;
    typedef std::shared_ptr<Reply> ReplyPtr;

    Droplet(ReplyPtr reply = nullptr, bool haveErr = false)
        :reply_(reply)
        ,haveErr_(haveErr) {}

    // Droplet(std::shared_ptr<MultiBulkReply> reply, bool haveErr = false)
    //     :reply_(std::static_pointer_cast<Reply>(reply))
    //     ,haveErr_(haveErr) {}

    Droplet() = default;

    Reply::ptr reply_;
    bool haveErr_ = false;

    void setReply(Reply::ptr reply) { reply_ = reply;}
    void sethaveErr(bool haveErr) { haveErr_ = haveErr;}

    bool terminated() {
        return haveErr_;
    }  
};

class DB {
public:
    typedef std::shared_ptr<DB> ptr;

    virtual ~DB() {};

    virtual Reply::ptr Do(Chan<void*>::ptr cancel, std::vector<std::string> cmdLine) = 0;
    virtual void close () = 0;
};

class Parser {
public:
    typedef std::shared_ptr<Parser> ptr;

    virtual ~Parser() {};
    virtual Chan<Droplet::ptr>::ptr parseStream(SocketStream::ptr sockStream) = 0;
};

}

#endif