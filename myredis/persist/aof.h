#ifndef __ALPHA_MYREDIS_PERSIST_AOF_H__
#define __ALPHA_MYREDIS_PERSIST_AOF_H__

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <atomic>
#include "../../lib/alpha/channel.h"
#include "file_io.h"
#include "../../lib/alpha/fiber_sync.h"

namespace alphaMin {

typedef std::string appendSyncStrategy; 

const appendSyncStrategy alwaysAppendSyncStrategy = "always";
const appendSyncStrategy everysecAppendSyncStrategy = "everysec";
const appendSyncStrategy noAppendSyncStrategy = "no";

class aofPersister {
public:
    typedef std::shared_ptr<aofPersister> ptr;

private:
    Chan<void*>::ptr m_cancelc;

    Chan<std::vector<std::string> >::ptr m_bufferc;
    FileIO::ptr m_aofFile;
    std::string m_aofFileName;
    appendSyncStrategy m_appendFsync;
    int64_t m_autoAofRewriteAfterCmd;
    std::atomic<int64_t> m_aofCounter;

    FiberMutex::ptr m_mutex;
};

}

#endif