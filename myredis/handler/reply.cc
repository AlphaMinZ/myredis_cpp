#include "reply.h"
#include <sstream>

namespace alphaMin {

std::string okStrings = "+OK\r\n";
std::string syntaxErrBytes = "-Err syntax error\r\n";
std::string wrongTypeErrBytes = "-WRONGTYPE Operation against a key holding the wrong kind of value\r\n";
std::string nillBulkBytes = "$-1\r\n";
std::string emptyMultiBulkBytes = "*0\r\n";

OKReply::ptr theOKReply = std::make_shared<OKReply>();
SyntaxErrReply::ptr theSyntaxErrReply = std::make_shared<SyntaxErrReply>();
WrongTypeErrReply::ptr theWrongTypeErrReply = std::make_shared<WrongTypeErrReply>();
NillReply::ptr nillReply = std::make_shared<NillReply>();

std::string SimpleStringReply::toString() {
    return "+" + str_ + CRLF;
}

std::string IntReply::toString() {
    return ":" + std::to_string(code_) + CRLF;
}

std::string SyntaxErrReply::toString() {
    return syntaxErrBytes;
}

std::string WrongTypeErrReply::toString() {
    return wrongTypeErrBytes;
}

std::string ErrReply::toString() {
    return "-" + errStr_ + CRLF;
}

std::string BulkReply::toString() {
    if(arg_.size() == 0) {
        return nillBulkBytes;
    }
    return "$" + std::to_string(arg_.size()) + CRLF + arg_ + CRLF;
}

std::string MultiBulkReply::toString() {
    std::ostringstream os;
    os << "*" << m_args.size() << CRLF;

    for(const auto& arg : m_args) {
        if(arg.empty()) {
            os << nillBulkBytes;
            continue;
        }
        os << "$" << arg.size() << CRLF << arg << CRLF;
    } 

    return os.str();
}

OKReply::ptr newOKReply() { return theOKReply;}

SyntaxErrReply::ptr newSyntaxErrReply() {
    return theSyntaxErrReply;
}

WrongTypeErrReply::ptr newWrongTypeErrReply() {
    return theWrongTypeErrReply;
}

NillReply::ptr newNillReply() {
    return nillReply;
}

}