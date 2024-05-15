#ifndef __ALPHA_MYREDIS_SERVER_H__
#define __ALPHA_MYREDIS_SERVER_H__

#include <memory>
#include "../lib/alpha/channel.h"
#include "../lib/alpha/alpha.h"
#include "handler/handler.h"

namespace alphaMin {

class Server {
public:
    typedef std::shared_ptr<Server> ptr;

    Server(Handler::ptr handler = std::make_shared<Handler>(), Logger::ptr logger = ALPHA_LOG_NAME("Server"))
        :m_handler(handler)
        ,m_logger(logger) {}

    ~Server();

    void run();

    void stop();
private:
    void listenAndServe(Socket::ptr listener, Chan<std::string> closec);
private:
    Logger::ptr m_logger; // 日志器
    Chan<std::string> m_stopc; // 通知关闭管道
    Handler::ptr m_handler;
};

}

#endif