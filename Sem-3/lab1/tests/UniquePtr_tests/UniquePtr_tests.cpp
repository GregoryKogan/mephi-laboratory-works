#include "UniquePtr_tests.hpp"

kogan::TestSuite unique_ptr_test_suite("UniquePtr");

struct TestObject {
    int value;
    TestObject(int value) : value(value) {}
};

TEST(default_constructor, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr;
    ASSERT(ptr.get() == nullptr);
}

TEST(constructor_from_pointer, unique_ptr_test_suite) {
    TestObject* obj = new TestObject(42);
    kogan::UniquePtr<TestObject> ptr(obj);
    ASSERT(ptr.get() == obj);
}

TEST(move_constructor, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1(new TestObject(42));
    kogan::UniquePtr<TestObject> ptr2(std::move(ptr1));
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2.get()->value == 42);
}

TEST(move_assignment, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1(new TestObject(42));
    kogan::UniquePtr<TestObject> ptr2;
    ptr2 = std::move(ptr1);
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2.get()->value == 42);
}

TEST(copy_constructor, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1(new TestObject(42));
    // kogan::UniquePtr<TestObject> ptr2(ptr1); // should not compile
}

TEST(copy_assignment, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1(new TestObject(42));
    kogan::UniquePtr<TestObject> ptr2;
    // ptr2 = ptr1; // should not compile
}

TEST(make_unique, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr = kogan::make_unique<TestObject>(42);
    ASSERT(ptr.get()->value == 42);
}

TEST(make_unique_with_custom_constructor, unique_ptr_test_suite) {
    kogan::UniquePtr<std::string> ptr = kogan::make_unique<std::string>("Hello World!");
    ASSERT(ptr->compare("Hello World!") == 0);
}

TEST(make_unique_with_multiple_arguments, unique_ptr_test_suite) {
    std::vector<int> expected = {1, 2, 3};
    kogan::UniquePtr<std::vector<int>> ptr = kogan::make_unique<std::vector<int>>(expected.begin(), expected.end());
    ASSERT(*ptr == expected);
}

TEST(release, unique_ptr_test_suite) {
    TestObject* obj = new TestObject(42);
    kogan::UniquePtr<TestObject> ptr(obj);
    TestObject* released_obj = ptr.release();
    ASSERT(ptr.get() == nullptr);
    ASSERT(released_obj == obj);
    delete released_obj;
}

TEST(reset, unique_ptr_test_suite) {
    TestObject* obj1 = new TestObject(42);
    TestObject* obj2 = new TestObject(43);
    kogan::UniquePtr<TestObject> ptr(obj1);
    ptr.reset(obj2);
    ASSERT(ptr.get() == obj2);
}

TEST(operator_bool, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr1;
    kogan::UniquePtr<TestObject> ptr2(new TestObject(42));
    ASSERT(!ptr1);
    ASSERT(ptr2);
}

TEST(operator_arrow, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr(new TestObject(42));
    ASSERT(ptr->value == 42);
}

TEST(operator_star, unique_ptr_test_suite) {
    kogan::UniquePtr<TestObject> ptr(new TestObject(42));
    ASSERT((*ptr).value == 42);
}

kogan::TestSuite get_unique_ptr_test_suite() { return unique_ptr_test_suite; }
