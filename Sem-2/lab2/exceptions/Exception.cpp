//
// Created by Gregory Kogan on 02.05.2023.
//

#include "Exception.h"


namespace kogan {
    Exception::Exception() {
        exception_type = ExceptionType::Unknown;
        message = "unknown exception";
    }

    Exception::Exception(ExceptionType exc_t, std::string msg) {
        exception_type = exc_t;
        message = std::move(msg);
    }

    std::string Exception::exception_type_to_string(ExceptionType exc_t) {
        switch (exc_t) {
            case Unknown:
                return "Unknown";
            case IndexOutOfRange:
                return "IndexOutOfRange";
            case InvalidSize:
                return "InvalidSize";
            case EmptyContainer:
                return "EmptyContainer";
            case InvalidArgument:
                return "InvalidArgument";
            default:
                return "Invalid";
        }
    }

    const char *Exception::what() const noexcept {
        std::string err_msg = "(" + Exception::exception_type_to_string(exception_type) + "): " + message;
        char* char_err_msg = new char;
        strncpy(char_err_msg, err_msg.c_str(), err_msg.length());
        return char_err_msg;
    }
} // kogan