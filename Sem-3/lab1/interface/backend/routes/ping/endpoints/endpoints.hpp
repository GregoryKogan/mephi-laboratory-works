#ifndef LAB1_INTERFACE_BACKEND_ROUTES_PING_ENDPOINTS_ENDPOINTS_HPP
#define LAB1_INTERFACE_BACKEND_ROUTES_PING_ENDPOINTS_ENDPOINTS_HPP

#include "../../../dependencies/cpp-httplib/httplib.h"

void ping(const httplib::Request& req, httplib::Response& res);

#endif