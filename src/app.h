#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "GitHub.h"
#include "CommandLineParser.h"
#include "config_reader.h"

namespace jak {
    class app {

    public:
        void run_command(const std::string &command_name, std::vector<std::string>::iterator arguments) {
          if (command_name == "status") {
            std::cout << "Status Command" << std::endl;
          } else if (command_name == "git") {
            std::cout << "Git commands" << std::endl;
            GitHub github;
            github.repos("");
          }
        }

        AppConfig read_configuration(const std::string &config_path) {
          std::ifstream config_file(config_path);
          AppConfig config;
          if (config_file.good()) {
            config = jak::config::reader::read(config_file);
            config_file.close();
          } else {
            std::cout << "warning: " << config_path << " missing" << std::endl;
          }
          return config;
        }

        int run(int argc, char *argv[]) {

          AppConfig config = read_configuration("~/.jak/config");
          CommandLineParser parser;
          auto arguments = parser.parse(argc, argv);
          if (arguments.valid()) {
            auto commands = arguments.commands();
            if (!commands.empty()) {
              std::string command = commands.front();

              run_command(command, commands.erase(commands.begin()));
            } else {
              std::cout << "Display help pending" << std::endl;
            }

          } else {
            std::cout << arguments.error_message();
          }
          return 0;
        }
    };
}
