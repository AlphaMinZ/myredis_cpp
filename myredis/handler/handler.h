#ifndef __ALPHA_MYREDIS_HANDLER_H__
#define __ALPHA_MYREDIS_HANDLER_H__

#include <memory>
#include <atomic>
#include "../../lib/alpha/fiber_sync.h"
#include "../../lib/alpha/alpha.h"
#include "../../lib/alpha/socket.h"
#include "../protocol/parser.h"
#include "../server.h"
#include "struct.h"
#include "persister.h"

namespace alphaMin {

class Handle : public Handler {
public:
    typedef std::shared_ptr<Handler> ptr;

    Handle(Logger::ptr logger = ALPHA_LOG_NAME("Handler"), 
            Parser::ptr parser = std::make_shared<Parser>(),
            DB::ptr db = std::make_shared<DB>())
        :m_logger(logger)
        ,m_parser(parser)
        ,m_db(db) {}

    ~Handle();

    void run() override;

    void handle(Socket::ptr sock) override;

    void close() override;
private:
    void handler(Socket::ptr sock);
    void handleDroplet();
private:
    FiberMutex m_mutex;
    std::unordered_set<Socket::ptr> m_conns;
    std::atomic<bool> m_closed;

    DB::ptr m_db;
    Parser::ptr m_parser;
    Persister::ptr m_persister;
    Logger::ptr m_logger;
};

}

#endif