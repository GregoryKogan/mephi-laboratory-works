//
// Created by Gregory Kogan on 02.05.2023.
//

#ifndef LAB2_EXCEPTION_H
#define LAB2_EXCEPTION_H

#include <string>
#include <cstring>

namespace kogan {
    enum ExceptionType {
        Unknown,
        IndexOutOfRange,
        InvalidSize,
    };

    class Exception : public std::exception {
        ExceptionType exception_type;
        std::string message;

        static std::string exception_type_to_string(ExceptionType exc_t);

    public:
        Exception();
        Exception(ExceptionType exc_t, std::string msg);
        [[nodiscard]] const char* what() const noexcept override;
    };
} // kogan

#endif //LAB2_EXCEPTION_H
