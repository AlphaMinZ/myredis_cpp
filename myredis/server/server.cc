#include "server.h"
#include "../../lib/alpha/fiber_sync.h"
#include <unistd.h>
#include <sys/signalfd.h>
#include <cstdlib>

namespace alphaMin {

void Server::run(Address::ptr address) {
    m_handler->run();

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGHUP);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGINT);

    if(sigprocmask(SIG_BLOCK, &mask, nullptr) == -1) {
        ALPHA_LOG_ERROR(m_logger) << "sigprocmask error";
        // TODO error pressess
    }

    int sfd = signalfd(-1, &mask, 0);
    if(sfd == -1) {
        ALPHA_LOG_ERROR(m_logger) << "signalfd error";
        // TODO error pressess
    }

    Chan<std::string>::ptr exitWords(new Chan<std::string>);
    Chan<std::string>::ptr closec(new Chan<std::string>);

    IOManager::GetThis()->addEvent(sfd, IOManager::READ, [exitWords]() {
        exitWords->send("exit");
    });

    auto this_server = shared_from_this();

    IOManager::GetThis()->schedule([exitWords, closec, this_server]() {
        auto cond = std::make_shared<FiberCondition>();
        auto mutex = std::make_shared<FiberMutex>();
        mutex->lock();

        // TODO 无效代码过多，需要整合
        auto result_closec = std::make_shared<result_chan<std::string> >();
        auto result_exitWordsc = std::make_shared<result_chan<std::string> >();

        for(;;) {
            alphaMin::select<std::string>(exitWords, cond, mutex, result_exitWordsc, nullptr);

            alphaMin::select<std::string>(this_server->getStopc(), cond, mutex, result_exitWordsc, nullptr);

            cond->wait(*mutex);
            closec->send("close");
            return;
        }
    });

    Socket::ptr listen_sock = Socket::CreateTCP(address);
    listen_sock->bind(address);

    listen_sock->listen();

    listenAndServe(listen_sock, closec);
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
        
        auto result_closec = std::make_shared<result_chan<std::string> >();

        alphaMin::select<std::string>(closec, cond, mutex, result_closec, [this_server]() {
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
        SocketStream::ptr connStream(new SocketStream(conn));
        wg->add(1);
        IOManager::GetThis()->schedule([wg, this_server, connStream, cancel]() {
            this_server->getHandler()->handle(cancel, connStream);
            wg->done();
        });
    }

    wg->wait();
}

}