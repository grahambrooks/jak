#pragma once

namespace jak {
    class source {
    public:
        std::string source_system;
        std::string token;

        source(std::string source, std::string token) : source_system(source), token(token) {

        }
    };
}
