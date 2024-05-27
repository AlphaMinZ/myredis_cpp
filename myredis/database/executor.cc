#include "executor.h"
#include "struct.h"
#include "iostream"
#include <functional>
#include <iostream>
#include <utility>
#include "../../lib/alpha/channel.h"
#include "../handler/reply.h"

namespace alphaMin {

DBExecutor::DBExecutor(DataStore::ptr dataStore)
    :m_dataStore(dataStore)
    ,m_ch(std::make_shared<Chan<Command::ptr> >()) 
    ,m_cancel(std::make_shared<Chan<void*>>()) {
    
    m_gcTimer = IOManager::GetThis()->addTimer(60000, std::bind(&DataStore::gc, m_dataStore.get()), true);

    // m_cmdHandlers.insert(std::make_pair(CmdTypeExpire, std::bind(&DataStore::expire, m_dataStore.get(), std::placeholders::_1)));
    m_cmdHandlers_2.emplace(CmdTypeExpire, std::bind(&DataStore::expire, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeExpireAt, std::bind(&DataStore::expireAt, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeExpire] = std::make_shared<CmdHandler>(std::bind(&DataStore::expire, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeExpireAt] = std::make_shared<CmdHandler>(std::bind(&DataStore::expireAt, m_dataStore.get(), std::placeholders::_1));

    // string
    m_cmdHandlers_2.emplace(CmdTypeGet, std::bind(&DataStore::get, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeSet, std::bind(&DataStore::set, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeMGet, std::bind(&DataStore::mGet, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeMSet, std::bind(&DataStore::mSet, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeGet] = std::make_shared<CmdHandler>(std::bind(&DataStore::get, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeSet] = std::make_shared<CmdHandler>(std::bind(&DataStore::set, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeMGet] = std::make_shared<CmdHandler>(std::bind(&DataStore::mGet, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeSet] = std::make_shared<CmdHandler>(std::bind(&DataStore::mSet, m_dataStore.get(), std::placeholders::_1));

    // list
    m_cmdHandlers_2.emplace(CmdTypeLPush, std::bind(&DataStore::lPush, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeLPop, std::bind(&DataStore::lPop, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeRPush, std::bind(&DataStore::rPush, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeRPop, std::bind(&DataStore::rPop, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeLRange, std::bind(&DataStore::lRange, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeLPush] = std::make_shared<CmdHandler>(std::bind(&DataStore::lPush, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeLPop] = std::make_shared<CmdHandler>(std::bind(&DataStore::lPop, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeRPush] = std::make_shared<CmdHandler>(std::bind(&DataStore::rPush, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeRPop] = std::make_shared<CmdHandler>(std::bind(&DataStore::rPop, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeLRange] = std::make_shared<CmdHandler>(std::bind(&DataStore::lRange, m_dataStore.get(), std::placeholders::_1));

    // set
    m_cmdHandlers_2.emplace(CmdTypeSAdd, std::bind(&DataStore::sAdd, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeSIsMember, std::bind(&DataStore::sIsMember, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeSRem, std::bind(&DataStore::sRem, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeSAdd] = std::make_shared<CmdHandler>(std::bind(&DataStore::sAdd, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeSIsMember] = std::make_shared<CmdHandler>(std::bind(&DataStore::sIsMember, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeSRem] = std::make_shared<CmdHandler>(std::bind(&DataStore::sRem, m_dataStore.get(), std::placeholders::_1));

    // hash
    m_cmdHandlers_2.emplace(CmdTypeHSet, std::bind(&DataStore::hSet, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeHGet, std::bind(&DataStore::hGet, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeHDel, std::bind(&DataStore::hDel, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeHSet] = std::make_shared<CmdHandler>(std::bind(&DataStore::hSet, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeHGet] = std::make_shared<CmdHandler>(std::bind(&DataStore::hGet, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeHDel] = std::make_shared<CmdHandler>(std::bind(&DataStore::hDel, m_dataStore.get(), std::placeholders::_1));

    // sorted set
    m_cmdHandlers_2.emplace(CmdTypeZAdd, std::bind(&DataStore::zAdd, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeZRangeByScore, std::bind(&DataStore::zRangeByScore, m_dataStore.get(), std::placeholders::_1));
    m_cmdHandlers_2.emplace(CmdTypeZRem, std::bind(&DataStore::zRem, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeZAdd] = std::make_shared<CmdHandler>(std::bind(&DataStore::zAdd, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeZRangeByScore] = std::make_shared<CmdHandler>(std::bind(&DataStore::zRangeByScore, m_dataStore.get(), std::placeholders::_1));
    // m_cmdHandlers[CmdTypeZRem] = std::make_shared<CmdHandler>(std::bind(&DataStore::zRem, m_dataStore.get(), std::placeholders::_1));

    IOManager::GetThis()->schedule(std::bind(&DBExecutor::run, shared_from_this().get()));
}

Chan<Command::ptr>::ptr DBExecutor::entrance() {
    return m_ch;
}

bool DBExecutor::validCommand(CmdType cmd) {
    auto it = m_cmdHandlers_2.find(cmd);
    return it != m_cmdHandlers_2.end();
}

void DBExecutor::close() {
    // TODO
    // m_cancel->cancel();
}

void DBExecutor::run() {
    auto cond = std::make_shared<FiberCondition>();
    auto mutex = std::make_shared<FiberMutex>();
    mutex->lock();

    auto result_cancel = std::make_shared<result_chan<void*> >();
    auto result_cmd = std::make_shared<result_chan<Command::ptr> >();
    for(;;) {
        alphaMin::select<void*>(m_cancel, cond, mutex, result_cancel, nullptr);
        alphaMin::select<Command::ptr>(m_ch, cond, mutex, result_cmd, nullptr);

        cond->wait(*mutex);
        if(result_cancel->from_me) {
            return;
        }
        if(result_cmd->from_me) {
            std::string cmd = (*(result_cmd->result))->getCmd()[0];
            auto it = m_cmdHandlers_2.find(cmd);
            if(it == m_cmdHandlers_2.end()) {
                (*(result_cmd->result))->getReceiver()->send(std::make_shared<ErrReply>("unknown command " + cmd));
                continue;
            }

            m_dataStore->expirePreprocess((*(result_cmd->result))->getArgs()[0]);
            auto& handlerFunc = it->second;
            (*(result_cmd->result))->getReceiver()->send(handlerFunc(*(result_cmd->result)));
        }
    }
}

}