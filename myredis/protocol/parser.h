#ifndef __ALPHA_MYREDIS_UTILS_PARSER_H__
#define __ALPHA_MYREDIS_UTILS_PARSER_H__

#include "../../lib/alpha/alpha.h"
#include "../../lib/alpha/channel.h"
#include "../handler/struct.h"
#include <memory>
#include <functional>
#include <map>

namespace alphaMin {

class Parse : public Parser {
public:
    typedef std::shared_ptr<Parser> ptr;
    typedef std::function<void(std::string)> lineParser;

    Parse(Logger::ptr logger = ALPHA_LOG_NAME("Parser"));

    ~Parse();

    Chan<Droplet::ptr>::ptr parseStream(Stream::ptr reader) override;

private:
    void parse(Stream::ptr reader, Chan<Droplet::ptr>::ptr ch);
    // 解析简单 string 类型
    Droplet::ptr parseSimpleString(std::string header, Stream::ptr reader);
    // 解析简单 int 类型
    Droplet::ptr parseInt(std::string header, Stream::ptr reader);
    // 解析错误类型
    Droplet::ptr parseError(std::string header, Stream::ptr reader);
    // 解析定长 string 类型
    Droplet::ptr parseBulk(std::string header, Stream::ptr reader);

    // 解析定长 string
    std::string parseBulkBody(std::string header, Stream::ptr reader);
    // 解析
    Droplet::ptr parseMultiBulk(std::string header, Stream::ptr reader);
private:
    std::map<std::string, lineParser> m_lineParsers;
    Logger::ptr m_logger;
};

}

#endif