#ifndef __ALPHA_MYREDIS_DATABASE_TRIGGER_H__
#define __ALPHA_MYREDIS_DATABASE_TRIGGER_H__

#include <memory>
#include "struct.h"

namespace alphaMin {

class DBTrigger : public DB {
public:
    typedef std::shared_ptr<DBTrigger> ptr;

    DBTrigger(Executor::ptr executor = std::shared_ptr<Executor>(nullptr))
        :m_executor(executor) {}

    DBTrigger() {}

    void setExecutor(Executor::ptr executor) { m_executor = executor;}

    Reply::ptr Do(Chan<void*>::ptr cancel, std::vector<std::string> cmdLine) override;

    void close() override;

private:
    Executor::ptr m_executor;
};

}

#endif