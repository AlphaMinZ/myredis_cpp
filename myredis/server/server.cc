#include "server.h"
#include "../../lib/alpha/fiber_sync.h"

namespace alphaMin {

void Server::run(Address::ptr address) {
    m_handler->run();

    // TODO
}

void Server::stop() {
    m_stopc->close();
}

void Server::listenAndServe(Socket::ptr listener, Chan<std::string>::ptr closec) {
    Chan<std::string>::ptr errorc(new Chan<std::string>(1));

    // 遇到意外错误，则终止流程
    Chan<std::string>::ptr cancel(new Chan<std::string>);

    auto this_server = shared_from_this();

    IOManager::GetThis()->schedule([cancel, closec, errorc, this_server, listener]() {
        auto cond = std::make_shared<FiberCondition>();
        auto mutex = std::make_shared<FiberMutex>();
        mutex->lock();
        
        auto result_closec = std::make_shared<std::pair<std::unique_ptr<std::string>, bool> >();
        auto result_errorc = std::make_shared<std::pair<std::unique_ptr<std::string>, bool> >();

        alphaMin::select(closec, cond, mutex, result_closec, [this_server]() {
            ALPHA_LOG_ERROR(this_server->getLogger()) << "[server]server closing...";
        });

        cond->wait(*mutex);
        // cancel->cancel(); // TODO
        ALPHA_LOG_WARN(this_server->getLogger()) << "server closeing...";
        this_server->getHandler()->close();
        listener->close();
    });

    ALPHA_LOG_WARN(m_logger) << "server starting...";

    WaitGroup::ptr wg(new WaitGroup);
    // io 多路复用模型，Fiber for per conntion
    for(;;) {
        Socket::ptr conn = listener->accept();

        wg->add(1);
        IOManager::GetThis()->schedule([wg, this_server, conn, cancel]() {
            this_server->getHandler()->handle(cancel, conn);
            wg->done();
        });
    }

    wg->wait();
}

}