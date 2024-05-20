#include "reply.h"
#include <sstream>

namespace alphaMin {

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

}