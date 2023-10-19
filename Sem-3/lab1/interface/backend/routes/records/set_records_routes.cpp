#include "set_records_routes.hpp"

void set_methods(httplib::Response& res, const std::string& methods) {
    res.set_header("Access-Control-Allow-Methods", methods.c_str());
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

void kogan::set_records_routes(httplib::Server& server) {
    // CORS
    server.Options("/records",
                   [](const httplib::Request& req, httplib::Response& res) { set_methods(res, "GET, POST, OPTIONS"); });
    server.Options("/records/:index",
                   [](const httplib::Request& req, httplib::Response& res) { set_methods(res, "DELETE, OPTIONS"); });
    server.Options("/records/:index/append",
                   [](const httplib::Request& req, httplib::Response& res) { set_methods(res, "POST, OPTIONS"); });

    // observers
    server.Get("/records", get_records);

    // modifiers
    server.Post("/records", add_record);
    server.Delete("/records/:index", remove_record);
    server.Post("/records/:index/append", append);
}