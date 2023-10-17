#ifndef LAB1_INTERFACE_ENDPOINTS_HPP
#define LAB1_INTERFACE_ENDPOINTS_HPP

#include "../../dependencies/cpp-httplib/httplib.h"
#include "../state/state.hpp"

void ping(const httplib::Request& req, httplib::Response& res);
void get_state(const httplib::Request& req, httplib::Response& res);

#endif