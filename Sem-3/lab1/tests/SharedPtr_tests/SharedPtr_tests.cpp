#include "SharedPtr_tests.hpp"

kogan::TestSuite shared_ptr_test_suite("SharedPtr");

struct TestObject {
    int value;
    TestObject() : value(0) {}
    TestObject(int value) : value(value) {}
};

TEST(default_constructor, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr;
    ASSERT(ptr.get() == nullptr);
    ASSERT(ptr.use_count() == 0);
}

TEST(default_constructor_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr;
    ASSERT(ptr.get() == nullptr);
    ASSERT(ptr.use_count() == 0);
}

TEST(constructor_from_pointer, shared_ptr_test_suite) {
    TestObject* obj = new TestObject(42);
    kogan::SharedPtr<TestObject> ptr(obj);
    ASSERT(ptr.get() == obj);
    ASSERT(ptr->value == 42);
    ASSERT(ptr.use_count() == 1);
}

TEST(constructor_from_pointer_array, shared_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> ptr(obj);
    ASSERT(ptr.get() == obj);
    ASSERT(ptr[0].value == 1);
    ASSERT(ptr[1].value == 2);
    ASSERT(ptr[2].value == 3);
    ASSERT(ptr.use_count() == 1);
}

TEST(copy_constructor, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
}

TEST(copy_constructor_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2(ptr1);
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
}

TEST(move_constructor, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2(std::move(ptr1));
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2->value == 42);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr1.use_count() == 0);
}

TEST(move_constructor_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2(std::move(ptr1));
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2[0].value == 1);
    ASSERT(ptr2[1].value == 2);
    ASSERT(ptr2[2].value == 3);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr1.use_count() == 0);
}

TEST(copy_assignment, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2;
    ptr2 = ptr1;
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr1->value == 42);
}

TEST(copy_assignment_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2;
    ptr2 = ptr1;
    ASSERT(ptr1.get() == ptr2.get());
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr1[0].value == 1);
    ASSERT(ptr1[1].value == 2);
    ASSERT(ptr1[2].value == 3);
}

TEST(move_assignment, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2;
    ptr2 = std::move(ptr1);
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2.get()->value == 42);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr1.use_count() == 0);
}

TEST(move_assignment_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2;
    ptr2 = std::move(ptr1);
    ASSERT(ptr1.get() == nullptr);
    ASSERT(ptr2[0].value == 1);
    ASSERT(ptr2[1].value == 2);
    ASSERT(ptr2[2].value == 3);
    ASSERT(ptr2.use_count() == 1);
    ASSERT(ptr1.use_count() == 0);
}

TEST(make_shared, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr = kogan::make_shared<TestObject>(42);
    ASSERT(ptr.get()->value == 42);
    ASSERT(ptr.use_count() == 1);
}

TEST(make_shared_with_custom_constructor, shared_ptr_test_suite) {
    kogan::SharedPtr<std::string> ptr = kogan::make_shared<std::string>("Hello World!");
    ASSERT(ptr->compare("Hello World!") == 0);
    ASSERT(ptr.use_count() == 1);
}

TEST(make_shared_with_multiple_arguments, shared_ptr_test_suite) {
    std::vector<int> expected = {1, 2, 3};
    kogan::SharedPtr<std::vector<int>> ptr = kogan::make_shared<std::vector<int>>(expected.begin(), expected.end());
    ASSERT(*ptr == expected);
    ASSERT(ptr.use_count() == 1);
    ASSERT(ptr->size() == 3);
    ASSERT(ptr->at(0) == 1);
    ASSERT(ptr->at(1) == 2);
    ASSERT(ptr->at(2) == 3);
}

TEST(make_shared_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr = kogan::make_shared<TestObject[]>(3);
    ptr[0].value = 1;
    ptr[1].value = 2;
    ptr[2].value = 3;
    ASSERT(ptr[0].value == 1);
    ASSERT(ptr[1].value == 2);
    ASSERT(ptr[2].value == 3);
    ASSERT(ptr.use_count() == 1);
}

TEST(operator_bool, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1;
    kogan::SharedPtr<TestObject> ptr2(new TestObject(42));
    ASSERT(!ptr1);
    ASSERT(ptr2);
}

TEST(operator_bool_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1;
    kogan::SharedPtr<TestObject[]> ptr2(new TestObject[3]{1, 2, 3});
    ASSERT(!ptr1);
    ASSERT(ptr2);
}

TEST(get, shared_ptr_test_suite) {
    TestObject* obj = new TestObject(42);
    kogan::SharedPtr<TestObject> ptr(obj);
    ASSERT(ptr.get() == obj);
}

TEST(get_array, shared_ptr_test_suite) {
    TestObject* obj = new TestObject[3]{1, 2, 3};
    kogan::SharedPtr<TestObject[]> ptr(obj);
    ASSERT(ptr.get() == obj);
}

TEST(operator_arrow, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr(new TestObject(42));
    ASSERT(ptr->value == 42);
}

TEST(operator_arrow_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr(new TestObject[3]{1, 2, 3});
    ASSERT(ptr->value == 1);
    ASSERT(ptr[0].value == 1);
}

TEST(operator_star, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr(new TestObject(42));
    ASSERT((*ptr).value == 42);
}

TEST(operator_star_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr(new TestObject[3]{1, 2, 3});
    ASSERT((*ptr).value == 1);
    ASSERT(ptr[0].value == 1);
}

TEST(use_count, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject> ptr1(new TestObject(42));
    kogan::SharedPtr<TestObject> ptr2(ptr1);
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    kogan::SharedPtr<TestObject> ptr3(std::move(ptr1));
    ASSERT(ptr1.use_count() == 0);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr3.use_count() == 2);
}

TEST(use_count_array, shared_ptr_test_suite) {
    kogan::SharedPtr<TestObject[]> ptr1(new TestObject[3]{1, 2, 3});
    kogan::SharedPtr<TestObject[]> ptr2(ptr1);
    ASSERT(ptr1.use_count() == 2);
    ASSERT(ptr2.use_count() == 2);
    kogan::SharedPtr<TestObject[]> ptr3(std::move(ptr1));
    ASSERT(ptr1.use_count() == 0);
    ASSERT(ptr2.use_count() == 2);
    ASSERT(ptr3.use_count() == 2);
}

kogan::TestSuite get_shared_ptr_test_suite() { return shared_ptr_test_suite; }
