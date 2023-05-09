//
// Created by Gregory Kogan on 07.05.2023.
//

#ifndef SEQUENCE_LIB_ASSERTIONFAILEDEXCEPTION_H
#define SEQUENCE_LIB_ASSERTIONFAILEDEXCEPTION_H

#include "../BaseException.h"

namespace kogan {

    class AssertionFailedException: public BaseException {
        std::string expression;
        std::string file;
        int line;

        void build_message() const override;

    public:
        AssertionFailedException(const std::string& expression, const char* file, int line);
    };

} // kogan

#endif //SEQUENCE_LIB_ASSERTIONFAILEDEXCEPTION_H
