#ifndef LAB1_INTERFACE_ENDPOINTS_HPP
#define LAB1_INTERFACE_ENDPOINTS_HPP

#include "../../../sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../dependencies/cpp-httplib/httplib.h"
#include "../state/state.hpp"

void ping(const httplib::Request& req, httplib::Response& res);

// observers
void get_records(const httplib::Request& req, httplib::Response& res);

// modifiers
void add_record(const httplib::Request& req, httplib::Response& res);

#endif