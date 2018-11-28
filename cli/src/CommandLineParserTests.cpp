#include <iostream>
#include "CommandLineParser.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(CommandLineParsing_NoArguments_AreInvalid) {
    CommandLineParser parser;
    char *args[] = {"jak"};
    BOOST_CHECK_EQUAL(parser.parse(1, args).valid(), false);
}

BOOST_AUTO_TEST_CASE(CommandLineParsing_NoArguments_ReturnsErrorMessage) {
    CommandLineParser parser;
    char *args[] = {"jak"};

    BOOST_CHECK_EQUAL(parser.parse(1, args).error_message(), "");
}

BOOST_AUTO_TEST_CASE(Accepts_Command_Chain) {
    CommandLineParser parser;
    char *args[] = {"jak", "add", "github", "username"};

    auto config = parser.parse(4, args);

    BOOST_CHECK_EQUAL(config.commands()[0], "add");
    BOOST_CHECK_EQUAL(config.commands()[1], "github");
    BOOST_CHECK_EQUAL(config.commands()[2], "username");
}

BOOST_AUTO_TEST_CASE(Accepts_Command_token) {
    CommandLineParser parser;
    char *args[] = {"jak", "add", "github", "username", "--token", "foo"};

    auto config = parser.parse(6, args);

    BOOST_CHECK_EQUAL(config.commands()[0], "add");
    BOOST_CHECK_EQUAL(config.commands()[1], "github");
    BOOST_CHECK_EQUAL(config.commands()[2], "username");
}
