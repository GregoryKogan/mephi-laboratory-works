#include "endpoints.hpp"

void ping(const httplib::Request& req, httplib::Response& res) {
    std::ostringstream oss;
    oss << "{\n"
        << "    \"message\": \"pong\"\n"
        << "}";
    res.status = 200;
    res.set_content(oss.str(), "application/json");
}
