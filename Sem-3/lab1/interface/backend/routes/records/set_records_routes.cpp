#include "set_records_routes.hpp"

void set_methods(httplib::Response& res, const std::string& methods) {
    res.set_header("Access-Control-Allow-Methods", methods);
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

void kogan::set_records_routes(httplib::Server& server) {
    // CORS
    server.Options("/records", [](auto& req, auto& res) { set_methods(res, "GET, POST, OPTIONS"); });
    server.Options("/records/:index", [](auto& req, auto& res) { set_methods(res, "DELETE, OPTIONS"); });
    server.Options("/records/:index/append", [](auto& req, auto& res) { set_methods(res, "POST, OPTIONS"); });
    server.Options("/records/:index/prepend", [](auto& req, auto& res) { set_methods(res, "POST, OPTIONS"); });
    server.Options("/records/:index/set", [](auto& req, auto& res) { set_methods(res, "POST, OPTIONS"); });
    server.Options("/records/:index/insert", [](auto& req, auto& res) { set_methods(res, "POST, OPTIONS"); });
    server.Options("/records/:index/remove", [](auto& req, auto& res) { set_methods(res, "POST, OPTIONS"); });
    server.Options("/records/:index/clear", [](auto& req, auto& res) { set_methods(res, "POST, OPTIONS"); });
    server.Options("/records/:index/subsequence", [](auto& req, auto& res) { set_methods(res, "GET, OPTIONS"); });
    server.Options("/records/:index/concat", [](auto& req, auto& res) { set_methods(res, "POST, OPTIONS"); });

    // observers
    server.Get("/records", get_records);

    // modifiers
    server.Post("/records", add_record);
    server.Delete("/records/:index", remove_record);
    server.Post("/records/:index/append", append);
    server.Post("/records/:index/prepend", prepend);
    server.Post("/records/:index/set", set);
    server.Post("/records/:index/insert", insert);
    server.Post("/records/:index/remove", remove_item);
    server.Post("/records/:index/clear", clear);
    server.Get("/records/:index/subsequence", subsequence);
    server.Post("/records/:index/concat", concat);
}