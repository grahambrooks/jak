#include <iostream>
#include "GitHub.h"
#include "CommandLineParser.h"

int main(int argc, char *argv[]) {

    CommandLineParser parser;

    auto arguments = parser.parse(argc, argv);

    if (arguments.valid()) {
        GitHub github;

        github.repos("");
    } else {
        std::cout << arguments.error_message();
    }
    return 0;
}
