#include <iostream>
#include <functional>
#include <boost/test/unit_test.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

// Short alias for this namespace
namespace pt = boost::property_tree;


class Source {
public:
    std::string source;
    std::string token;

    Source(std::string source, std::string token) : source(source), token(token) {

    }
};

class AppConfig {
    std::vector<Source> app_sources;

public:
    bool has_sources() {
        return !app_sources.empty();
    }

    void add(Source source) {
        app_sources.push_back(source);
    }
    void each_source(std::function<void(Source)> const& l) {
        for (auto s : app_sources) {
            l(s);
        }
    }
};

class ConfigReader {

public:
    static AppConfig read(std::iostream &config) {
        AppConfig appconfig;
        pt::ptree root;
        pt::read_json(config, root);

        auto sources = root.get_child_optional("sources");

        if (sources.has_value()) {
            for (auto &v : root.get_child("sources")) {
                auto &node = v.second;
                appconfig.add(Source(node.get<std::string>("source"), node.get<std::string>("token")));
            }
        }
        return appconfig;
    }
};

BOOST_AUTO_TEST_CASE(ConfigReaderTests) {
    std::stringstream input("{}");

    AppConfig config = ConfigReader::read(input);

    BOOST_CHECK_EQUAL(config.has_sources(), false);
}

BOOST_AUTO_TEST_CASE(ConfigReaderTests_single_source) {
    std::stringstream input("{\"sources\": [{\"source\": \"github\", \"token\": \"atoken\"}]}");

    AppConfig config = ConfigReader::read(input);

    BOOST_CHECK_EQUAL(config.has_sources(), true);
    bool called = false;

    auto handler = [&](Source src) {
        BOOST_CHECK_EQUAL(src.source, "github");
        BOOST_CHECK_EQUAL(src.token, "atoken");
        called = true;
    };

    config.each_source(handler);

    BOOST_CHECK(called);
}
