#include "handler.h"
#include "../../lib/alpha/socket_stream.h"

namespace alphaMin {

void Handle::run() {
    // TODO 加载持久化功能


}

void Handle::handle(Chan<std::string>::ptr cancel, SocketStream::ptr sockStream) {
    m_mutex.lock();

    if(m_closed.load()) {
        m_mutex.unlock();
        return;
    }

    m_conns.insert(sockStream->getSocket());
    m_mutex.unlock();

    handler(cancel, sockStream);
}

void Handle::handler(Chan<std::string>::ptr cancel, SocketStream::ptr sockStream) {
    auto stream = m_parser->parseStream(std::make_shared<SocketStream>(sockStream));

    auto cond = std::make_shared<FiberCondition>();
    auto mutex = std::make_shared<FiberMutex>();
    mutex->lock();

    auto result_cancelc = std::make_shared<result_chan<std::string> >();
    auto result_dropletc = std::make_shared<result_chan<alphaMin::Droplet::ptr> >();

    for(;;) {
        alphaMin::select<std::string>(cancel, cond, mutex, result_cancelc, nullptr);
        alphaMin::select<alphaMin::Droplet::ptr>(stream, cond, mutex, result_dropletc, nullptr);
        cond->wait(*mutex);
        
        if(result_cancelc->from_me) {
            ALPHA_LOG_WARN(m_logger) << "handler cencel";
            return;
        }
        if(result_dropletc->from_me) {
            handleDroplet(cancel, sockStream, *(result_dropletc->result));
            // TODO 错误类型查看是否 return
        }
    }
}

// TODO 加一个错误类型，这个函数需要传递一个错误类型出来
void Handle::handleDroplet(Chan<std::string>::ptr cancel, SocketStream::ptr sockStream, Droplet::ptr droplet) {
    if(droplet->terminated()) {
        return;
    }

    if(droplet->haveErr) {
        sockStream->write(droplet->reply->toString().c_str(), droplet->reply->toString().size());
        ALPHA_LOG_ERROR(m_logger) << "conn request err";
        return;
    }

    if(droplet->reply.get() == nullptr) {
        ALPHA_LOG_ERROR(m_logger) << "conn empty request";
        return;
    }

    // need test
    MultiReply* multiReply = dynamic_cast<MultiReply*>(droplet->reply.get());
    if(!multiReply) {
        ALPHA_LOG_ERROR(m_logger) << "conn invalid request: " << droplet->reply->toString();
        return;
    }

    auto reply = m_db->Do(cancel, multiReply->getArgs());
    if(!reply.get()) {
        sockStream->write(reply->toString().c_str(), reply->toString().size());
        return;
    }
}

void Handle::close() {
    ALPHA_LOG_WARN(m_logger) << "handler closing...";
    m_closed.store(true);
    m_mutex.lock();
    for(auto& conn : m_conns) {
        conn->close();
    }
    m_conns.clear();
    m_db->close();
    m_persister->close();
    m_mutex.unlock();
}

}