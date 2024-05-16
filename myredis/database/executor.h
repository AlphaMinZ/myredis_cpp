#ifndef __ALPHA_MYREDIS_DATABASE_EXECUTOR_H__
#define __ALPHA_MYREDIS_DATABASE_EXECUTOR_H__

#include <memory>
#include <unordered_map>
#include "../../lib/alpha/channel.h"
#include "../../lib/alpha/alpha.h"
#include "struct.h"

namespace alphaMin {

class DBExecutor : public Executor {
public:
    typedef std::shared_ptr<DBExecutor> ptr;

    DBExecutor(DataStore::ptr dataStore);

    Chan<Command::ptr>::ptr entrance() override;

    bool validCommand(CmdType cmd) override;

    void close() override;

    void run();
private:
    Chan<Command::ptr>::ptr m_ch;
    std::unordered_map<CmdType, CmdHandler> m_cmdHandlers;
    DataStore::ptr m_dataStore;
    Timer::ptr m_gcTimer;
};

}

#endif