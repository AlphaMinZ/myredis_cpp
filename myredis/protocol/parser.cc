#include "parser.h"
#include "../handler/reply.h"

namespace alphaMin {

Chan<Droplet::ptr>::ptr Parse::parseStream(SocketStream::ptr sockStream) {
    auto ch = std::make_shared<Chan<Droplet::ptr>>();

    auto this_parser = shared_from_this();

    IOManager::GetThis()->schedule([this_parser, sockStream, ch]() {
        this_parser->parse_pb(sockStream, ch);
    });

    return ch;
}

void Parse::parse(SocketStream::ptr sockStream, Chan<Droplet::ptr>::ptr ch) {
    for(;;) {
        std::string firstLine;
        auto len = sockStream->readUntil(firstLine, '\n');
        if(len <= 0 || (firstLine[firstLine.size() - 1] != '\n') || (firstLine[firstLine.size() - 2] != '\r')) {
            ch->send(std::make_shared<Droplet>(std::make_shared<ErrReply>("err"), true));
            return;
        }

        firstLine = firstLine.substr(0, firstLine.size() - 2);
        auto lineParseFunc = m_lineParsers.find(firstLine[0]);

        if(lineParseFunc == m_lineParsers.end()) {
            ALPHA_LOG_ERROR(m_logger) << "[parser] invalid line handler: " << firstLine[0];
            return;
        }

        ch->send(lineParseFunc->second(firstLine, sockStream));
    }
}

Droplet::ptr Parse::parseSimpleString(std::string header, SocketStream::ptr sockStream) {
    auto content = header.substr(1, header.size());
    return std::make_shared<Droplet>(std::make_shared<SimpleStringReply>(header));
}

Droplet::ptr Parse::parseInt(std::string header, SocketStream::ptr sockStream) {
    int64_t i;

    try {
        i = std::stoll(header.substr(1));
    } catch (const std::exception& e) {
        return std::make_shared<Droplet>(std::make_shared<ErrReply>(e.what()), true);
    }

    return std::make_shared<Droplet>(std::make_shared<IntReply>(i));
}

Droplet::ptr Parse::parseError(std::string header, SocketStream::ptr sockStream) {
    return std::make_shared<Droplet>(std::make_shared<ErrReply>(header.substr(1)));
}

Droplet::ptr Parse::parseBulk(std::string header, SocketStream::ptr sockStream) {
    std::string body;

    try {
        body = parseBulkBody(header, sockStream);
    } catch (const std::exception& e) {
        return std::make_shared<Droplet>(std::make_shared<ErrReply>(e.what()), true);
    }

    return std::make_shared<Droplet>(std::make_shared<BulkReply>(body));
}

std::string Parse::parseBulkBody(std::string header, SocketStream::ptr sockStream) {
    int64_t strLen = std::stoll(header.substr(1));

    std::string body(strLen, ' ');
    // 将 CRLF 也读出来
    auto len = sockStream->readFixSize(&body[0], strLen + 2);
    return body.substr(0, body.size() - 2);
}

Droplet::ptr Parse::parseMultiBulk(std::string header, SocketStream::ptr sockStream) {
    int64_t length = 0;
    try {
        length = std::stoll(header.substr(1));
        if(length <= 0) {
            return std::make_shared<Droplet>(std::make_shared<EmptyMultiBulkReply>());
        }
    } catch (const std::exception& e) {
        return std::make_shared<Droplet>(std::make_shared<ErrReply>(e.what()), true);
    }

    std::vector<std::string> lines;
    lines.reserve(length);

    for(int64_t i = 0; i < length; ++i) {
        std::string firstLine;
        auto len = sockStream->readUntil(firstLine, '\n');
        if(len <= 0 || (firstLine[firstLine.size() - 1] != '\n') || (firstLine[firstLine.size() - 2] != '\r')) {
            return std::make_shared<Droplet>(std::make_shared<ErrReply>("error"), true);
        }

        auto bulkBody = parseBulkBody(firstLine.substr(0, length - 2), sockStream);

        lines.push_back(bulkBody);
    }

    std::shared_ptr<MultiBulkReply> multiBulkReply = std::make_shared<MultiBulkReply>(lines);
    Droplet::ptr ret(new Droplet(multiBulkReply, false));
    // return std::make_shared<Droplet>(std::make_shared<MultiBulkReply>(lines), false);
    return ret;
}

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