#include "set_ping_routes.hpp"

void kogan::set_ping_routes(httplib::Server& server) {
    // CORS
    server.Options("/ping", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });

    // observers
    server.Get("/ping", ping);
}