#include "set_records_routes.hpp"

void kogan::set_records_routes(httplib::Server& server) {
    // CORS
    server.Options("/records", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });
    server.Options("/records/:index", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Methods", "DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });

    // observers
    server.Get("/records", get_records);

    // modifiers
    server.Post("/records", add_record);
    server.Delete("/records/:index", remove_record);
}