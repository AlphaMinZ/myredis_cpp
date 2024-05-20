#ifndef __ALPHA_MYREDIS_HANDLER_REPLY_H__
#define __ALPHA_MYREDIS_HANDLER_REPLY_H__

#include <memory>
#include <string>
#include <vector>
#include "struct.h"

namespace alphaMin {

#define CRLF "\r\n"

struct OKReply : public Reply {
    typedef std::shared_ptr<OKReply> ptr;
    std::string toString() override {
        return okStrings;
    }
};

OKReply::ptr newOKReply() { return theOKReply;}

std::string okStrings = "+OK\r\n";

auto theOKReply = std::make_shared<OKReply>();

// 简单字符串类型. 协议为 【+】【string】【CRLF】
struct SimpleStringReply : public Reply {
    typedef std::shared_ptr<SimpleStringReply> ptr;

    SimpleStringReply(std::string str)
        :str_(str) {}

    std::string toString() override;

    std::string str_;
};

// 简单数字类型. 协议为 【:】【int】【CRLF】
struct IntReply : public Reply {
    typedef std::shared_ptr<IntReply> ptr;

    IntReply(int64_t code)
        :code_(code) {}

    std::string toString() override;

    int64_t code_;
};

// 参数语法错误
struct SyntaxErrReply : public Reply {
    typedef std::shared_ptr<SyntaxErrReply> ptr;

    std::string toString() override;
    std::string error() { return "Err syntax error";}
};

std::string syntaxErrBytes = "-Err syntax error\r\n";
auto theSyntaxErrReply = std::make_shared<SyntaxErrReply>();

SyntaxErrReply::ptr newSyntaxErrReply() {
    return theSyntaxErrReply;
}

// 数据类型错误
struct WrongTypeErrReply : public Reply {
    typedef std::shared_ptr<WrongTypeErrReply> ptr;

    std::string toString() override;
    std::string error() { return "WRONGTYPE Operation against a key holding the wrong kind of value";}
};

std::string wrongTypeErrBytes = "-WRONGTYPE Operation against a key holding the wrong kind of value\r\n";
auto theWrongTypeErrReply = std::make_shared<WrongTypeErrReply>();

WrongTypeErrReply::ptr newWrongTypeErrReply() {
    return theWrongTypeErrReply;
}

// 错误类型. 协议为 【-】【err】【CRLF】
struct ErrReply : public Reply {
    typedef std::shared_ptr<ErrReply> ptr;

    ErrReply(std::string errStr)
        :errStr_(errStr) {}

    std::string toString() override;

    std::string errStr_;
};

struct NillReply : public Reply {
    typedef std::shared_ptr<NillReply> ptr;

    std::string toString() override { return nillBulkBytes;}
};

auto nillReply = std::make_shared<NillReply>();
std::string nillBulkBytes = "$-1\r\n";

NillReply::ptr newNillReply() {
    return nillReply;
}

// 定长字符串类型，协议固定为 【$】【length】【CRLF】【content】【CRLF】
struct BulkReply : public Reply {
    std::shared_ptr<BulkReply> ptr;

    BulkReply(std::string arg)
        :arg_(arg) {}

    std::string toString() override;

    std::string arg_;
};

// 数组类型. 协议固定为 【*】【arr.length】【CRLF】+ arr.length * (【$】【length】【CRLF】【content】【CRLF】)
class MultiBulkReply : public MultiReply, Reply {
public:
    typedef std::shared_ptr<MultiBulkReply> ptr;

    MultiBulkReply(std::vector<std::string> args)
        :m_args(args) {}

    std::vector<std::string> getArgs() override { return m_args;}

    std::string toString() override;
private:
    std::vector<std::string> m_args;
};

// 空数组类型. 采用单例，协议固定为【*】【0】【CRLF】
struct EmptyMultiBulkReply : public Reply {
    typedef std::shared_ptr<EmptyMultiBulkReply> ptr;

    EmptyMultiBulkReply() {}

    std::string toString() override { return emptyMultiBulkBytes;}
};

std::string emptyMultiBulkBytes = "*0\r\n";

}

#endif