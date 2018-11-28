#include <iostream>
#include "CommandLineParser.h"
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

CommandLineParser::RuntimeConfiguration CommandLineParser::parse(int argc, char *argv[]) {

    const char* commands_key = "commands";
    try {
        std::string appName = boost::filesystem::basename(argv[0]);
        std::vector<std::string> sentence;

        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
                ("help,h", "Print help messages")
                ("token,t", po::value<std::string>(), "Access token for account access")
                (commands_key, po::value<std::vector<std::string> >(), commands_key);

        po::positional_options_description positionalOptions;
        positionalOptions.add(commands_key, -1);

        po::variables_map vm;

        try {
            po::store(po::command_line_parser(argc, argv)
                              .options(desc)
                              .positional(positionalOptions).run(), vm);
            if (vm.count("help")) {
                std::cout << desc;
                return RuntimeConfiguration(ParserStatus::SUCCESS);
            }

            po::notify(vm);

            if (vm.count(commands_key)) {
                auto commands = vm[commands_key].as<std::vector<std::string>>();

                return RuntimeConfiguration(ParserStatus::SUCCESS, "", commands);
            }
        }
        catch (boost::program_options::required_option &e) {
            return RuntimeConfiguration(ParserStatus::ERROR_IN_COMMAND_LINE, e.what());
        }
        catch (boost::program_options::error &e) {
            return RuntimeConfiguration(ParserStatus::ERROR_IN_COMMAND_LINE, e.what());
        }
    }
    catch (std::exception &e) {
        std::cerr << "Unhandled Exception reached the top of main: "
                  << e.what() << ", application will now exit" << std::endl;
        return RuntimeConfiguration(ParserStatus::ERROR_UNHANDLED_EXCEPTION);
    }


    return RuntimeConfiguration(ParserStatus::SUCCESS);
}
