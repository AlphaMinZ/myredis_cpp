#ifndef __ALPHA_MYREDIS_HANDLER_H__
#define __ALPHA_MYREDIS_HANDLER_H__

#include <memory>
#include <atomic>
#include "../../lib/alpha/fiber_sync.h"
#include "../../lib/alpha/alpha.h"
#include "../../lib/alpha/socket.h"
#include "../protocol/parser.h"
#include "../server/server.h"
#include "struct.h"
#include "persister.h"

namespace alphaMin {

class Handle : public Handler {
public:
    typedef std::shared_ptr<Handler> ptr;

    Handle(Logger::ptr logger = ALPHA_LOG_NAME("Handler"), 
            Parser::ptr parser = nullptr,
            DB::ptr db = nullptr)
        :m_logger(logger)
        ,m_parser(parser)
        ,m_db(db) {}

    ~Handle();

    void run() override;

    void handle(Chan<void*>::ptr cancel, SocketStream::ptr sock) override;

    void close() override;
private:
    void handler(Chan<void*>::ptr cancel, SocketStream::ptr sock);
    void handleDroplet(Chan<void*>::ptr cancel, SocketStream::ptr sock, Droplet::ptr droplet);
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