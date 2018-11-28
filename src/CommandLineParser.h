#pragma once

#include <string>
#include <vector>

class CommandLineParser {
public:
    enum ParserStatus {
        ERROR_IN_COMMAND_LINE,
        SUCCESS,
        ERROR_UNHANDLED_EXCEPTION
    };

    class RuntimeConfiguration {
    private:
        ParserStatus status;
        std::string errors;
        std::string help;
        std::vector<std::string> command_elements;

    public:
        explicit RuntimeConfiguration(ParserStatus status) : status(status) {}

        explicit RuntimeConfiguration(ParserStatus status, std::string errors) : status(status), errors(errors) {}

        explicit RuntimeConfiguration(ParserStatus status, std::string errors, std::vector<std::string> commands)
                : status(status), errors(errors), command_elements(commands) {}

    public:
        bool valid() { return status == ParserStatus::SUCCESS && !command_elements.empty(); };

        std::string error_message() {
            return errors;
        }

        std::vector<std::string> commands() {
            return command_elements;
        }
    };

    RuntimeConfiguration parse(int argc, char *argv[]);
};
