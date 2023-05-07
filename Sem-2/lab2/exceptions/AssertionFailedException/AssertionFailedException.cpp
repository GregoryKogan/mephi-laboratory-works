//
// Created by Gregory Kogan on 07.05.2023.
//

#include "AssertionFailedException.h"

namespace kogan {

    void AssertionFailedException::build_message() const {
        snprintf(
                message, MESSAGE_MAX_LENGTH,
                "(AssertionFailed): (%s), file %s, line %d", expression.c_str(), file.c_str(), line
        );
    }

    AssertionFailedException::AssertionFailedException(const std::string& expression, const char *file, int line) {
        this->expression = expression;
        std::string full_filename = file;
        std::string token = full_filename.substr(full_filename.rfind('/') + 1, full_filename.length());
        this->file = token;
        this->line = line;
    }

} // kogan