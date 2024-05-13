#include "../lib/alpha/alpha.h"

alphaMin::Logger::ptr g_logger = ALPHA_LOG_ROOT();

int main(int argc, char** argv) {
    ALPHA_LOG_INFO(g_logger) << "test";
    return 0;
}