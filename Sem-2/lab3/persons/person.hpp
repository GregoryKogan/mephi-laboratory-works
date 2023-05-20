//
// Created by Gregory Kogan on 19.05.2023.
//

#ifndef LAB3_PERSON_HPP
#define LAB3_PERSON_HPP

#include <string>

namespace kogan {

    struct PersonID {
        int number;
        int series;
    };

    class Person {
        struct PersonID id{};
        std::string first_name;
        std::string middle_name;
        std::string last_name;
    public:
        Person(struct PersonID id, std::string first_name, std::string middle_name, std::string last_name);

        [[nodiscard]] PersonID get_id() const;

        [[nodiscard]] std::string get_first_name() const;
        [[nodiscard]] std::string get_middle_name() const;
        [[nodiscard]] std::string get_last_name() const;
    };

} // kogan

#endif //LAB3_PERSON_HPP
