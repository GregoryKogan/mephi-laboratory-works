#include <iostream>
#include "exceptions/Exception.h"

int main() {
    try {
        throw kogan::Exception(kogan::ExceptionType::value, "my value error");
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    return 0;
}
