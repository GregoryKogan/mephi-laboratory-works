#ifndef LAB1_INTERFACE_BACKEND_ROUTES_PING_SET_PING_ROUTES_HPP
#define LAB1_INTERFACE_BACKEND_ROUTES_PING_SET_PING_ROUTES_HPP

#include "../../dependencies/cpp-httplib/httplib.h"
#include "endpoints/endpoints.hpp"

namespace kogan {

void set_ping_routes(httplib::Server& server);

}

#endif