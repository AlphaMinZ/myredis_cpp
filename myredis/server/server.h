#ifndef __ALPHA_MYREDIS_SERVER_H__
#define __ALPHA_MYREDIS_SERVER_H__

#include <memory>
#include "../lib/alpha/channel.h"
#include "../lib/alpha/alpha.h"
#include "../../lib/alpha/socket.h"

namespace alphaMin {

class Handler {
public:
    typedef std::shared_ptr<Handler> ptr;

    virtual void run() = 0;

    virtual void handle(Socket::ptr sock) = 0;

    virtual void close() = 0;
};

class Server {
public:
    typedef std::shared_ptr<Server> ptr;

    Server(Handler::ptr handler = std::make_shared<Handler>(), 
            Logger::ptr logger = ALPHA_LOG_NAME("Server"),
            Chan<std::string>::ptr stopc = std::make_shared<Chan<std::string> >())
        :m_handler(handler)
        ,m_logger(logger)
        ,m_stopc(stopc) {}

    ~Server();

    void run();

    void stop();
private:
    void listenAndServe(Socket::ptr listener, Chan<std::string> closec);
private:
    Logger::ptr m_logger; // 日志器
    Chan<std::string>::ptr m_stopc; // 通知关闭管道
    Handler::ptr m_handler;
};

}

#endif