//
// Created by Gregory Kogan on 19.05.2023.
//

#include "person.hpp"


namespace kogan {

    Person::Person(struct PersonID id, std::string first_name, std::string middle_name, std::string last_name) {
        this->id = id;
        this->first_name = std::move(first_name);
        this->middle_name = std::move(middle_name);
        this->last_name = std::move(last_name);
    }

    PersonID Person::get_id() const {
        return id;
    }

    [[maybe_unused]] std::string Person::get_first_name() const {
        return first_name;
    }

    std::string Person::get_middle_name() const {
        return middle_name;
    }

    std::string Person::get_last_name() const {
        return last_name;
    }

} // kogan