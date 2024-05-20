#ifndef __ALPHA_MYREDIS_DATABASE_EXECUTOR_H__
#define __ALPHA_MYREDIS_DATABASE_EXECUTOR_H__

#include <memory>
#include <unordered_map>
#include "../../lib/alpha/channel.h"
#include "../../lib/alpha/alpha.h"
#include "struct.h"

namespace alphaMin {

class DBExecutor : public Executor , std::enable_shared_from_this<DBExecutor> {
public:
    typedef std::shared_ptr<DBExecutor> ptr;

    DBExecutor(DataStore::ptr dataStore);

    Chan<Command::ptr>::ptr entrance() override;

    bool validCommand(CmdType cmd) override;

    void close() override;

    void run();
private:
    Chan<Command::ptr>::ptr m_ch;
    Chan<void*>::ptr m_cancel;
    std::unordered_map<CmdType, std::shared_ptr<CmdHandler> > m_cmdHandlers;
    std::unordered_map<CmdType, CmdHandler> m_cmdHandlers_2;
    DataStore::ptr m_dataStore;
    Timer::ptr m_gcTimer;
};

}

#endif