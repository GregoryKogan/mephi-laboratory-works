//
// Created by Gregory Kogan on 02.05.2023.
//

#include "Exception.h"


namespace kogan {
    Exception::Exception() {
        exception_type = ExceptionType::unknown;
        message = "unknown exception";
    }

    Exception::Exception(ExceptionType exc_t, std::string msg) {
        exception_type = exc_t;
        message = std::move(msg);
    }

    std::string Exception::exception_type_to_string(ExceptionType exc_t) {
        switch (exc_t) {
            case unknown:
                return "UnknownException";
            case value:
                return "ValueException";
            case allocation:
                return "AllocationException";
            default:
                return "InvalidException";
        }
    }

    const char *Exception::what() const noexcept {
        std::string err_msg = "(" + Exception::exception_type_to_string(exception_type) + "): " + message;
        char* char_err_msg = new char;
        strcpy(char_err_msg, err_msg.c_str());
        return char_err_msg;
    }
} // kogan