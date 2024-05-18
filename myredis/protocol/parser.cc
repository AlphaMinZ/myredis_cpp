#include "parser.h"

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
    // TODO
}

}