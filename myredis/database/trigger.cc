#include "trigger.h"
#include "../handler/reply.h"

namespace alphaMin {

Reply::ptr DBTrigger::Do(Chan<void*>::ptr cancel, std::vector<std::string> cmdLine) {
    if(cmdLine.size() < 2) {
        return std::make_shared<ErrReply>("invalid cmd line: " + cmdLine[0]);
    }

    auto cmdType = (CmdType)cmdLine[0];
    if(!m_executor->validCommand(cmdType)) {
        return std::make_shared<ErrReply>("unknown cmd " + cmdLine[0]);
    }

    std::vector<std::string> tmp(cmdLine.begin() + 1, cmdLine.end());

    Command::ptr cmd(new Command(cmdType, tmp));
    cmd->setCancelc(cancel);
    cmd->setReceiver(std::make_shared<CmdReceiver>());

    m_executor->entrance()->send(cmd);

    // TODO need to change
    auto cond = std::make_shared<FiberCondition>();
    auto mutex = std::make_shared<FiberMutex>();
    mutex->lock();

    auto result_cmdReceive = std::make_shared<result_chan<Reply::ptr> >();
    alphaMin::select<Reply::ptr>(cmd->getReceiver(), cond, mutex, result_cmdReceive, nullptr);

    cond->wait(*mutex);

    return *(result_cmdReceive->result);
}

void DBTrigger::close() {
    m_executor->close();
}

}