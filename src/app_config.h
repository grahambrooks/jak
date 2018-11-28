#pragma once

#include <iostream>
#include "source.h"

namespace jak {
    class AppConfig {
        std::vector<source> app_sources;

    public:
        bool has_sources() {
          return !app_sources.empty();
        }

        void add(source source) {
          app_sources.push_back(source);
        }

        void each_source(std::function<void(source)> const &l) {
          for (auto s : app_sources) {
            l(s);
          }
        }
    };

}
