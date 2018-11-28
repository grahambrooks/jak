#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;

#include "app_config.h"

namespace jak {
    namespace config {
        class reader {

        public:
            static AppConfig read(std::istream &config) {
              AppConfig appconfig;
              pt::ptree root;
              pt::read_json(config, root);

              auto sources = root.get_child_optional("sources");

              if (sources.has_value()) {
                for (auto &v : root.get_child("sources")) {
                  auto &node = v.second;
                  appconfig.add(source(node.get<std::string>("source"), node.get<std::string>("token")));
                }
              }
              return appconfig;
            }
        };

    }

}
