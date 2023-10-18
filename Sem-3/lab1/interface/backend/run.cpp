#include "../../sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../../sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp"
#include "Logger/Logger.hpp"
#include "dependencies/cpp-httplib/httplib.h"
#include "endpoints/endpoints.hpp"
#include "state/state.hpp"

int main(void) {
    httplib::Server svr;

    // logging
    std::ostream& log_stream = std::cout;
    kogan::Logger::Logger logger(log_stream);
    svr.set_logger([&](const auto& req, const auto& res) { logger.log(req, res); });

    // CORS
    svr.set_post_routing_handler(
        [](const auto& req, auto& res) { res.set_header("Access-Control-Allow-Origin", "*"); });

    svr.Get("/ping", ping);
    svr.Get("/stop", [&](const httplib::Request& req, httplib::Response& res) { svr.stop(); });

    // observers
    svr.Get("/records", get_records);

    // modifiers
    svr.Post("/records", add_record);

    svr.listen("localhost", 8080);
}