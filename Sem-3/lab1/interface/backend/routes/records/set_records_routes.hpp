#ifndef LAB1_INTERFACE_BACKEND_ROUTES_RECORDS_SET_RECORDS_ROUTES_HPP
#define LAB1_INTERFACE_BACKEND_ROUTES_RECORDS_SET_RECORDS_ROUTES_HPP

#include "../../dependencies/cpp-httplib/httplib.h"
#include "endpoints/endpoints.hpp"

namespace kogan {

void set_records_routes(httplib::Server& server);

}

#endif