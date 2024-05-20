#ifndef __ALPHA_MYREDIS_UTILS_PARSER_H__
#define __ALPHA_MYREDIS_UTILS_PARSER_H__

#include "../../lib/alpha/alpha.h"
#include "../../lib/alpha/channel.h"
#include "../../lib/alpha/socket_stream.h"
#include "../handler/struct.h"
#include <memory>
#include <functional>
#include <unordered_map>

namespace alphaMin {

using lineParser = std::function<Droplet::ptr(std::string header, SocketStream::ptr sockStream)>;

class Parse : public Parser , std::enable_shared_from_this<Parse> {
public:
    typedef std::shared_ptr<Parser> ptr;

    Parse(Logger::ptr logger = ALPHA_LOG_NAME("Parser"))
        :m_logger(logger) {}

    ~Parse() {};

    Chan<Droplet::ptr>::ptr parseStream(SocketStream::ptr sockStream) override;

    void parse_pb(SocketStream::ptr sockStream, Chan<Droplet::ptr>::ptr ch) { parse(sockStream, ch);}
    // 解析简单 string 类型
    Droplet::ptr parseSimpleString_pb(std::string header, SocketStream::ptr sockStream) { return parseSimpleString(header, sockStream);}
    // 解析简单 int 类型
    Droplet::ptr parseInt_pb(std::string header, SocketStream::ptr sockStream) { return parseInt(header, sockStream);}
    // 解析错误类型
    Droplet::ptr parseError_pb(std::string header, SocketStream::ptr sockStream) { return parseError(header, sockStream);}
    // 解析定长 string 类型
    Droplet::ptr parseBulk_pb(std::string header, SocketStream::ptr sockStream) { return parseBulk(header, sockStream);}

    // 解析定长 string
    std::string parseBulkBody_pb(std::string header, SocketStream::ptr sockStream) { return parseBulkBody(header, sockStream);}

    // 解析
    Droplet::ptr parseMultiBulk_pb(std::string header, SocketStream::ptr sockStream) { return parseMultiBulk(header, sockStream);}

    std::unordered_map<char, lineParser>& getLineParsers() { return m_lineParsers;}
    void setLineParser(char header, lineParser fc) { m_lineParsers[header] = fc;}
    // void setLineParser(char header, lineParser fc) { m_lineParsers.insert({header, fc});}

private:
    void parse(SocketStream::ptr sockStream, Chan<Droplet::ptr>::ptr ch);
    // 解析简单 string 类型
    Droplet::ptr parseSimpleString(std::string header, SocketStream::ptr sockStream);
    // 解析简单 int 类型
    Droplet::ptr parseInt(std::string header, SocketStream::ptr sockStream);
    // 解析错误类型
    Droplet::ptr parseError(std::string header, SocketStream::ptr sockStream);
    // 解析定长 string 类型
    Droplet::ptr parseBulk(std::string header, SocketStream::ptr sockStream);

    // 解析定长 string
    std::string parseBulkBody(std::string header, SocketStream::ptr sockStream);
    // 解析
    Droplet::ptr parseMultiBulk(std::string header, SocketStream::ptr sockStream);
private:
    std::unordered_map<char, lineParser> m_lineParsers;
    Logger::ptr m_logger;
};

Parse::ptr newParser(Logger::ptr logger) {
    auto p = std::make_shared<Parse>(logger);
    
    p->setLineParser('+', std::bind(&Parse::parseSimpleString_pb, p, std::placeholders::_1, std::placeholders::_2));
    p->setLineParser('-', std::bind(&Parse::parseError_pb, p, std::placeholders::_1, std::placeholders::_2));
    p->setLineParser(':', std::bind(&Parse::parseInt_pb, p, std::placeholders::_1, std::placeholders::_2));
    p->setLineParser('$', std::bind(&Parse::parseBulk_pb, p, std::placeholders::_1, std::placeholders::_2));
    p->setLineParser('*', std::bind(&Parse::parseMultiBulk_pb, p, std::placeholders::_1, std::placeholders::_2));

    return p;
}

}

#endif