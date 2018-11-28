#include <iostream>
#include "GitHub.h"
#include "CommandLineParser.h"
#include "config_reader.h"

int main(int argc, char *argv[]) {

  std::ifstream confg_file("~/.jak/config");
  if (confg_file.good()) {
    jak::config::reader::read(confg_file);
    confg_file.close();
    CommandLineParser parser;

    auto arguments = parser.parse(argc, argv);

    if (arguments.valid()) {
      GitHub github;

      github.repos("");
    } else {
      std::cout << arguments.error_message();
    }
    return 0;
  } else {
    std::cerr << "Missing configuration file" << std::endl;
    return -1;
  }
}
