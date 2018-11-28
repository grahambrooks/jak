#include <cpprest/http_client.h>
#include "GitHub.h"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;


std::string print_json(web::json::value v) {
    std::stringstream ss;
    try {
        if (!v.is_null()) {
            if (v.is_object()) {
                for (const auto &iter : v.as_object()) {
                    const utility::string_t &str = iter.first;
                    const web::json::value &value = iter.second;

                    if (value.is_object() || value.is_array()) {
                        ss << "Parent: " << str << std::endl;
                        ss << (value);
                        ss << "End of Parent: " << str << std::endl;
                    } else {
                        ss << "str: " << str << ", Value: " << value.serialize() << std::endl;
                    }
                }
            } else if (v.is_array()) {
                for (size_t index = 0; index < v.as_array().size(); ++index) {
                    const web::json::value &value = v.as_array().at(index);

                    ss << "Array: " << index << std::endl;
                    ss << (value);
                }
            } else {
                ss << "Value: " << v.serialize() << std::endl;
            }
        }
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        ss << "Value: " << v.serialize() << std::endl;
    }

    return ss.str();
}

pplx::task<void> RequestJSONValueAsync(const std::string &token) {
    // TODO: To successfully use this example, you must perform the request

    http_client_config client_config;
    web::credentials cred(token, U(""));
    client_config.set_credentials(cred);
    http_client client(U("https://api.github.com/users/grahambrooks/repos"), client_config);

    return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value> {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                }
                return pplx::task_from_result(json::value());
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    const json::value &res = previousTask.get();

                    std::cout << print_json(res);
                }
                catch (const http_exception &e) {
                    printf("Error exception:%s\n", e.what());
                }
            });
}

void GitHub::repos(std::string token) {
    RequestJSONValueAsync(token).wait();
}
