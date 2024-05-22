#ifndef __ALPHA_MYREDIS_HANDLER_REPLY_H__
#define __ALPHA_MYREDIS_HANDLER_REPLY_H__

#include <memory>
#include <string>
#include <vector>
#include "struct.h"

namespace alphaMin {

#define CRLF "\r\n"

extern std::string okStrings;

struct OKReply : public Reply {
    typedef std::shared_ptr<OKReply> ptr;
    std::string toString() override {
        return okStrings;
    }
};

extern OKReply::ptr theOKReply;

OKReply::ptr newOKReply();

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

extern std::string syntaxErrBytes;
extern SyntaxErrReply::ptr theSyntaxErrReply;

SyntaxErrReply::ptr newSyntaxErrReply();

// 数据类型错误
struct WrongTypeErrReply : public Reply {
    typedef std::shared_ptr<WrongTypeErrReply> ptr;

    std::string toString() override;
    std::string error() { return "WRONGTYPE Operation against a key holding the wrong kind of value";}
};

extern std::string wrongTypeErrBytes;
extern WrongTypeErrReply::ptr theWrongTypeErrReply;

WrongTypeErrReply::ptr newWrongTypeErrReply();

// 错误类型. 协议为 【-】【err】【CRLF】
struct ErrReply : public Reply {
    typedef std::shared_ptr<ErrReply> ptr;

    ErrReply(std::string errStr)
        :errStr_(errStr) {}

    std::string toString() override;

    std::string errStr_;
};

extern std::string nillBulkBytes;

struct NillReply : public Reply {
    typedef std::shared_ptr<NillReply> ptr;

    std::string toString() override { return nillBulkBytes;}
};

extern NillReply::ptr nillReply;

NillReply::ptr newNillReply();

// 定长字符串类型，协议固定为 【$】【length】【CRLF】【content】【CRLF】
struct BulkReply : public Reply {
    std::shared_ptr<BulkReply> ptr;

    BulkReply(std::string arg)
        :arg_(arg) {}

    std::string toString() override;

    std::string arg_;
};

// 数组类型. 协议固定为 【*】【arr.length】【CRLF】+ arr.length * (【$】【length】【CRLF】【content】【CRLF】)
class MultiBulkReply : public MultiReply, public Reply {
public:
    typedef std::shared_ptr<MultiBulkReply> ptr;

    MultiBulkReply(std::vector<std::string> args)
        :m_args(args) {}

    MultiBulkReply() = default; 

    std::vector<std::string> getArgs() override { return m_args;}

    std::string toString() override;
private:
    std::vector<std::string> m_args;
};

extern std::string emptyMultiBulkBytes;
// 空数组类型. 采用单例，协议固定为【*】【0】【CRLF】
struct EmptyMultiBulkReply : public Reply {
    typedef std::shared_ptr<EmptyMultiBulkReply> ptr;

    EmptyMultiBulkReply() {}

    std::string toString() override { return emptyMultiBulkBytes;}
};

}

#endif