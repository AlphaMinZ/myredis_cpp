#ifndef __ALPHA_MYREDIS_HANDLER_H__
#define __ALPHA_MYREDIS_HANDLER_H__

#include <memory>
#include <atomic>
#include "../../lib/alpha/fiber_sync.h"
#include "../../lib/alpha/alpha.h"
#include "../../lib/alpha/socket.h"
#include "../utils/parser.h"

namespace alphaMin {

class Handler {
public:
    typedef std::shared_ptr<Handler> ptr;

    Handler(Logger::ptr logger = ALPHA_LOG_NAME("Handler"), 
            Parser::ptr parser = std::make_shared<Parser>())
        :m_logger(logger) {}

    ~Handler();

    void run();

    void handle(Socket::ptr sock);

    void close();
private:
    void handle(Socket::ptr sock);
    void handleDroplet();
private:
    FiberMutex m_mutex;
    std::unordered_set<Socket::ptr> m_conns;
    std::atomic<bool> m_closed;

    // DB m_db;
    Parser::ptr m_parser;
    // Persister m_persister;
    Logger::ptr m_logger;
};

}

#endif