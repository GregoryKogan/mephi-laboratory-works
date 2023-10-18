#include "Logger.hpp"

void kogan::Logger::Logger::log(const httplib::Request& req, const httplib::Response& res) {
    log_stream << req.method << " " << req.path << " " << res.status << std::endl;
}
