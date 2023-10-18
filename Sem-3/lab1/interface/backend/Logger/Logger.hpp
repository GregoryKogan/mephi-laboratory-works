#ifndef LAB1_INTERFACE_BACKEND_LOGGER_HPP
#define LAB1_INTERFACE_BACKEND_LOGGER_HPP

#include <iostream>

#include "../dependencies/cpp-httplib/httplib.h"

namespace kogan {

namespace Logger {

class Logger {
   private:
    std::ostream& log_stream;

   public:
    Logger(std::ostream& log_stream) : log_stream(log_stream) {}

    void log(const httplib::Request& req, const httplib::Response& res);
};

}  // namespace Logger

}  // namespace kogan

#endif