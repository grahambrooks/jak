#include <iostream>
#include <boost/test/unit_test.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

namespace pt = boost::property_tree;

#include "config_reader.h"

BOOST_AUTO_TEST_CASE(configuration_can_be_empty_object) {
  std::stringstream input("{}");

  jak::AppConfig config = jak::config::reader::read(input);

  BOOST_CHECK_EQUAL(config.has_sources(), false);
}

BOOST_AUTO_TEST_CASE(configuration_can_contain_single_source) {
  std::stringstream input("{\"sources\": [{\"source\": \"github\", \"token\": \"atoken\"}]}");

  jak::AppConfig config = jak::config::reader::read(input);

  BOOST_CHECK_EQUAL(config.has_sources(), true);
  bool called = false;

  auto handler = [&](jak::source src) {
      BOOST_CHECK_EQUAL(src.source_system, "github");
      BOOST_CHECK_EQUAL(src.token, "atoken");
      called = true;
  };

  config.each_source(handler);

  BOOST_CHECK(called);
}
