#ifndef __ALPHA_MYREDIS_HANDLER_REPLY_H__
#define __ALPHA_MYREDIS_HANDLER_REPLY_H__

#include <memory>
#include <string>
#include <vector>

namespace alphaMin {

#define CRLF "\r\n"

struct OKReply {
    typedef std::shared_ptr<OKReply> ptr;
    std::string toString() {
        return okStrings;
    }
};

OKReply::ptr newOKReply() { return theOKReply;}

std::string okStrings = "+OK\r\n";

auto theOKReply = std::make_shared<OKReply>();

// 简单字符串类型. 协议为 【+】【string】【CRLF】
struct SimpleStringReply {
    typedef std::shared_ptr<SimpleStringReply> ptr;

    SimpleStringReply(std::string str)
        :str_(str) {}

    std::string toString();

    std::string str_;
};

// 简单数字类型. 协议为 【:】【int】【CRLF】
struct IntReply {
    typedef std::shared_ptr<IntReply> ptr;

    IntReply(int64_t code)
        :code_(code) {}

    std::string toString();

    int64_t code_;
};

// 参数语法错误
struct SyntaxErrReply {
    typedef std::shared_ptr<SyntaxErrReply> ptr;

    std::string toString();
    std::string error();
};

std::string syntaxErrBytes = "-Err syntax error\r\n";
auto theSyntaxErrReply = std::make_shared<SyntaxErrReply>();

SyntaxErrReply::ptr newSyntaxErrReply() {
    return theSyntaxErrReply;
}

// 数据类型错误
struct WrongTypeErrReply {
    typedef std::shared_ptr<WrongTypeErrReply> ptr;

    std::string toString();
    std::string error();
};

std::string wrongTypeErrBytes = "-WRONGTYPE Operation against a key holding the wrong kind of value\r\n";
auto theWrongTypeErrReply = std::make_shared<WrongTypeErrReply>();

WrongTypeErrReply::ptr newWrongTypeErrReply() {
    return theWrongTypeErrReply;
}

// 错误类型. 协议为 【-】【err】【CRLF】
struct ErrReply {
    typedef std::shared_ptr<ErrReply> ptr;

    ErrReply(std::string errStr)
        :errStr_(errStr) {}

    std::string toString();

    std::string errStr_;
};

struct NillReply {
    typedef std::shared_ptr<NillReply> ptr;

    std::string toString() { return nillBulkBytes;}
};

auto nillReply = std::make_shared<NillReply>();
std::string nillBulkBytes = "$-1\r\n";

NillReply::ptr newNillReply() {
    return nillReply;
}

// 定长字符串类型，协议固定为 【$】【length】【CRLF】【content】【CRLF】
struct BulkReply {
    std::shared_ptr<BulkReply> ptr;

    BulkReply(std::string arg)
        :arg_(arg) {}

    std::string toString();

    std::string arg_;
};

// 数组类型. 协议固定为 【*】【arr.length】【CRLF】+ arr.length * (【$】【length】【CRLF】【content】【CRLF】)
class MultiBulkReply {
public:
    typedef std::shared_ptr<MultiBulkReply> ptr;

    MultiBulkReply(std::vector<std::string> args)
        :m_args(args) {}

    std::vector<std::string> getArgs() { return m_args;}

    std::string toString();
private:
    std::vector<std::string> m_args;
};

// 空数组类型. 采用单例，协议固定为【*】【0】【CRLF】
struct EmptyMultiBulkReply {
    typedef std::shared_ptr<EmptyMultiBulkReply> ptr;

    EmptyMultiBulkReply() {}

    std::string toString() { return emptyMultiBulkBytes;}
};

std::string emptyMultiBulkBytes = "*0\r\n";

}

#endif