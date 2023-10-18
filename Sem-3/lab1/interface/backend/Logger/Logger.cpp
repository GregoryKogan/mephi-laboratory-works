#include "Logger.hpp"

void kogan::Logger::Logger::log_start() const noexcept {
    log_stream << get_timestamp() << " SERVER STARTED" << std::endl;
}

void kogan::Logger::Logger::log(const httplib::Request& req, const httplib::Response& res) const noexcept {
    log_stream << get_timestamp() << " " << req.method << " " << req.path << " " << res.status << std::endl;
}

std::string kogan::Logger::Logger::get_timestamp() const noexcept {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char buf[100] = {0};
    std::strftime(buf, sizeof(buf), "%Y-%m-%d.%X", std::localtime(&now));
    return buf;
}
