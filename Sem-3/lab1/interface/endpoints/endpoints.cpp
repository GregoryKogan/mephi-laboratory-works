#include "endpoints.hpp"

void ping(const httplib::Request& req, httplib::Response& res) {
    std::ostringstream oss;
    oss << "{\n"
        << "    \"message\": \"pong\"\n"
        << "}";
    res.set_content(oss.str(), "application/json");
    res.status = 200;
}

void get_state(const httplib::Request& req, httplib::Response& res) {
    std::ostringstream oss;
    oss << "{\n"
        << "    \"array_seq\": " << get_array_seq()->to_string() << ",\n"
        << "    \"list_seq\": " << get_list_seq()->to_string() << "\n"
        << "}";
    res.set_content(oss.str(), "application/json");
    res.status = 200;
}
