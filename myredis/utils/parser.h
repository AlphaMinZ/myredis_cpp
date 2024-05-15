#ifndef __ALPHA_MYREDIS_UTILS_PARSER_H__
#define __ALPHA_MYREDIS_UTILS_PARSER_H__

#include "../../lib/alpha/alpha.h"
#include <memory>
#include <functional>
#include <map>

namespace alphaMin {

class Parser {
public:
    typedef std::shared_ptr<Parser> ptr;
    typedef std::function<void(std::string)> lineParser;

    Parser(Logger::ptr logger = ALPHA_LOG_NAME("Parser"));

    ~Parser();

    void parserStream();

private:
    void parse();
    // 解析简单 string 类型
    void parseSimpleString();
    // 解析简单 int 类型
    void parseInt();
    // 解析错误类型
    void parseError();
    // 解析定长 string 类型
    void parseBulk();

    // 解析定长 string
    void parseBulkBody();
    // 解析
    void parseMultiBulk();
private:
    std::map<std::string, lineParser> m_lineParsers;
    Logger::ptr m_logger;
};

}

#endif