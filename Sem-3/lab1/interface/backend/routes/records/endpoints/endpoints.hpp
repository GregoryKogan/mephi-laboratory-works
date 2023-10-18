#ifndef LAB1_INTERFACE_BACKEND_ROUTES_RECORDS_ENDPOINTS_ENDPOINTS_HPP
#define LAB1_INTERFACE_BACKEND_ROUTES_RECORDS_ENDPOINTS_ENDPOINTS_HPP

#include "../../../../../sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../../../dependencies/cpp-httplib/httplib.h"
#include "../../../state/state.hpp"

// observers
void get_records(const httplib::Request& req, httplib::Response& res);

// modifiers
void add_record(const httplib::Request& req, httplib::Response& res);
void remove_record(const httplib::Request& req, httplib::Response& res);

#endif