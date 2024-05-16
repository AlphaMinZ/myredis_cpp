#ifndef __ALPHA_MYREDIS_HANDLER_PERSISTER_H__
#define __ALPHA_MYREDIS_HANDLER_PERSISTER_H__

#include <memory>
#include <vector>
#include <string>

class Persister {
public:
    typedef std::shared_ptr<Persister> ptr;

    virtual ~Persister();
    virtual void reloader() = 0;
    virtual void persistCmd(std::vector<std::string> cmd) = 0;
    virtual void close() = 0;
};

#endif