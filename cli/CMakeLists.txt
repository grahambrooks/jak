cmake_minimum_required(VERSION 3.12)
project(jak-cli)

set(PENSSL_ROOT_DIR /usr/local/opt/openssl)
set(OPENSSL_INCLUDE_DIR /usr/local/opt/openssl/include)


set(CMAKE_CXX_STANDARD 17)
find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono unit_test_framework)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)

add_executable(jak-cli src/main.cpp src/GitHub.cpp src/GitHub.h src/CommandLineParser.cpp src/CommandLineParser.h)
target_link_libraries(${PROJECT_NAME} PRIVATE cpprestsdk::cpprest ${Boost_LIBRARIES})

add_executable(jak-cli-test src/CommandLineParser.cpp src/CommandLineParser.h src/CommandLineParserTests.cpp src/test_main.cpp src/ConfigReaderTests.cpp)
target_link_libraries(jak-cli-test PRIVATE cpprestsdk::cpprest ${Boost_LIBRARIES})
