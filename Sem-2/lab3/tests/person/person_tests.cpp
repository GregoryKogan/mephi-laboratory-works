//
// Created by Gregory Kogan on 20.05.2023.
//

#include "person_tests.hpp"


kogan::TestSuite person_test_suite("Person");


TEST(constructor, person_test_suite) {
    kogan::Person p(kogan::PersonID{12, 312}, "John", "Doe", "Junior");

    ASSERT(p.get_id().number == 12);
    ASSERT(p.get_id().series == 312);
    ASSERT(p.get_first_name() == "John");
    ASSERT(p.get_middle_name() == "Doe");
    ASSERT(p.get_last_name() == "Junior");
}


TEST(container, person_test_suite) {
    kogan::Queue<kogan::Person*> q;

    kogan::Person p1(kogan::PersonID{1, 11}, "A", "B", "C");
    kogan::Person p2(kogan::PersonID{2, 22}, "D", "E", "F");
    kogan::Person p3(kogan::PersonID{3, 33}, "G", "H", "I");

    q.push(&p1);
    q.push(&p2);
    q.push(&p3);

    ASSERT(q.size() == 3);
    ASSERT(q.pop()->get_id().number == 1);
    ASSERT(q.pop()->get_id().number == 2);
    ASSERT(q.pop()->get_id().number == 3);
    ASSERT(q.empty());
}


kogan::TestSuite get_person_test_suite() {
    return person_test_suite;
}
