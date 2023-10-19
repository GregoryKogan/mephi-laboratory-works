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
void append(const httplib::Request& req, httplib::Response& res);
void prepend(const httplib::Request& req, httplib::Response& res);
void set(const httplib::Request& req, httplib::Response& res);
void insert(const httplib::Request& req, httplib::Response& res);
void remove_item(const httplib::Request& req, httplib::Response& res);
void clear(const httplib::Request& req, httplib::Response& res);
void subsequence(const httplib::Request& req, httplib::Response& res);

// reusable
void set_message_and_status(httplib::Response& res, const std::string& message, int status);
void handle_exception_with_status(std::exception& e, httplib::Response& res, int status);
std::pair<int, bool> get_seq_index(const httplib::Request& req, httplib::Response& res);
std::pair<int, bool> get_parameter_value(const httplib::Request& req, httplib::Response& res,
                                         const std::string& parameter_name = "value");

#endif