#include "SharedPtr_tests.hpp"

kogan::TestSuite shared_ptr_test_suite("SharedPtr");

TEST(empty_constructor, shared_ptr_test_suite) {
    kogan::SharedPtr<int> ptr;

    ASSERT(ptr.get() == nullptr);
    ASSERT(ptr.use_count() == 0);
}

TEST(constructor_from_pointer, shared_ptr_test_suite) {
    int* obj = new int(42);
    kogan::SharedPtr<int> ptr(obj);

    ASSERT(ptr.get() == obj);
    ASSERT(*ptr == 42);
    ASSERT(ptr.use_count() == 1);
}

TEST(copy_constructor, shared_ptr_test_suite) {
    int* obj = new int(42);
    kogan::SharedPtr<int> ptr1(obj);

    kogan::SharedPtr<int> ptr2(ptr1);

    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(*ptr1 == 42);
    ASSERT(ptr1.use_count() == ptr2.use_count());
    ASSERT(ptr1.use_count() == 2);
}

TEST(move_constructor, shared_ptr_test_suite) {
    int* obj = new int(42);
    kogan::SharedPtr<int> ptr1(obj);

    kogan::SharedPtr<int> ptr2(std::move(ptr1));

    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr1.use_count() == 0);
    ASSERT(ptr2.get() == obj);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(*ptr2 == 42);
}

TEST(copy_assignment, shared_ptr_test_suite) {
    int* obj1 = new int(42);
    int* obj2 = new int(43);
    kogan::SharedPtr<int> ptr1(obj1);
    kogan::SharedPtr<int> ptr2(obj2);

    ptr2 = ptr1;

    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == ptr2.use_count());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(*ptr1 == 42);
}

TEST(move_assignment, shared_ptr_test_suite) {
    int* obj1 = new int(42);
    int* obj2 = new int(43);
    kogan::SharedPtr<int> ptr1(obj1);
    kogan::SharedPtr<int> ptr2(obj2);

    ptr2 = std::move(ptr1);

    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr1.use_count() == 0);
    ASSERT(ptr2.get() == obj1);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(*ptr2 == 42);
}

TEST(bool_operator, shared_ptr_test_suite) {
    kogan::SharedPtr<int> ptr1(new int(42));
    kogan::SharedPtr<int> ptr2;

    ASSERT(ptr1);
    ASSERT(!ptr2);
}

TEST(get, shared_ptr_test_suite) {
    int* obj = new int(42);
    kogan::SharedPtr<int> ptr(obj);

    ASSERT(ptr.get() == obj);
}

TEST(arrow_operator, shared_ptr_test_suite) {
    struct Foo {
        int value;
        int get_value() const { return value; }
    };
    Foo* obj = new Foo{42};
    kogan::SharedPtr<Foo> ptr(obj);

    ASSERT(ptr->get_value() == obj->get_value());
    ASSERT(ptr->get_value() == 42);
}

TEST(start_operator, shared_ptr_test_suite) {
    kogan::SharedPtr<int> ptr(new int(42));

    ASSERT(*ptr == 42);
}

TEST(use_count, shared_ptr_test_suite) {
    kogan::SharedPtr<int> ptr1(new int(42));

    ASSERT(ptr1.use_count() == 1);

    kogan::SharedPtr<int> ptr2(ptr1);

    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
}

kogan::TestSuite get_shared_ptr_test_suite() { return shared_ptr_test_suite; }
