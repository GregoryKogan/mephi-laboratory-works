//
// Created by Gregory Kogan on 06.05.2023.
//

#ifndef SEQUENCE_LIB_TEST_H
#define SEQUENCE_LIB_TEST_H

#include <string>
#include <iostream>
#include "../IO/colored_logs.h"

namespace kogan {

    class Test {
        std::string name;
        void (*testFunction)();

    public:
        Test(std::string  name, void (*testFunction)());
        [[nodiscard]] bool run() const;
    };

} // kogan

#endif //SEQUENCE_LIB_TEST_H
