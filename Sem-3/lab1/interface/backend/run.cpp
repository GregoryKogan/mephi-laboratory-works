#include "Logger/Logger.hpp"
#include "dependencies/cpp-httplib/httplib.h"
#include "routes/ping/set_ping_routes.hpp"
#include "routes/records/set_records_routes.hpp"
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

    // routes
    kogan::set_ping_routes(svr);
    kogan::set_records_routes(svr);

    // start server
    logger.log_start();
    svr.listen("localhost", 8080);
}