#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <utility>

#include "smart_pointers/SharedPtr.hpp"
#include "smart_pointers/UniquePtr.hpp"

struct TestObject {
    int value;
    TestObject() : value(0) {}
    TestObject(int value) : value(value) {}
};

template <typename F, typename... Ts>
unsigned long long int time_it(F&& f, Ts&&... args);

kogan::SharedPtr<kogan::UniquePtr<TestObject>[]> create_smart_ptr_array(std::size_t size);
TestObject** create_raw_ptr_array(std::size_t size);
std::shared_ptr<std::unique_ptr<TestObject>[]> create_std_smart_ptr_array(std::size_t size);

void shuffle_smart_ptr_array(kogan::SharedPtr<kogan::UniquePtr<TestObject>[]> arr, std::size_t size);
void shuffle_raw_ptr_array(TestObject** arr, std::size_t size);
void shuffle_std_smart_ptr_array(std::shared_ptr<std::unique_ptr<TestObject>[]> arr, std::size_t size);

void sort_smart_ptr_array(kogan::SharedPtr<kogan::UniquePtr<TestObject>[]> arr, std::size_t size);
void sort_raw_ptr_array(TestObject** arr, std::size_t size);
void sort_std_smart_ptr_array(std::shared_ptr<std::unique_ptr<TestObject>[]> arr, std::size_t size);

unsigned long long int test_smart_ptr_array(std::size_t size);
unsigned long long int test_raw_ptr_array(std::size_t size);
unsigned long long int test_std_smart_ptr_array(std::size_t size);

int main() {
    srand(time(NULL));
    int max_power = 8;
    for (int i = 1; i <= max_power; ++i) {
        std::size_t size = pow(10, i);
        std::cout << "size: 10^" << i << std::endl;
        std::cout << "raw pointers:           " << test_raw_ptr_array(size) << " microseconds" << std::endl;
        std::cout << "kogan's smart pointers: " << test_smart_ptr_array(size) << " microseconds" << std::endl;
        std::cout << "std smart pointers:     " << test_std_smart_ptr_array(size) << " microseconds" << std::endl;
    }
    return 0;
}

template <typename F, typename... Ts>
unsigned long long int time_it(F&& f, Ts&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    std::forward<F>(f)(std::forward<Ts>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

kogan::SharedPtr<kogan::UniquePtr<TestObject>[]> create_smart_ptr_array(std::size_t size) {
    auto arr = kogan::make_shared<kogan::UniquePtr<TestObject>[]>(size);
    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = kogan::make_unique<TestObject>(i);
    }
    return arr;
}

TestObject** create_raw_ptr_array(std::size_t size) {
    auto arr = new TestObject*[size];
    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = new TestObject(i);
    }
    return arr;
}

std::shared_ptr<std::unique_ptr<TestObject>[]> create_std_smart_ptr_array(std::size_t size) {
    auto arr = std::shared_ptr<std::unique_ptr<TestObject>[]>(new std::unique_ptr<TestObject>[size]);
    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = std::make_unique<TestObject>(i);
    }
    return arr;
}

void shuffle_smart_ptr_array(kogan::SharedPtr<kogan::UniquePtr<TestObject>[]> arr, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        std::size_t j = rand() % size;
        std::swap(arr[i], arr[j]);
    }
}

void shuffle_raw_ptr_array(TestObject** arr, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        std::size_t j = rand() % size;
        std::swap(arr[i], arr[j]);
    }
}

void shuffle_std_smart_ptr_array(std::shared_ptr<std::unique_ptr<TestObject>[]> arr, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        std::size_t j = rand() % size;
        std::swap(arr[i], arr[j]);
    }
}

void sort_smart_ptr_array(kogan::SharedPtr<kogan::UniquePtr<TestObject>[]> arr, std::size_t size) {
    std::qsort(arr.get(), size, sizeof(kogan::UniquePtr<TestObject>), [](const void* a, const void* b) {
        return (*(kogan::UniquePtr<TestObject>*)a)->value - (*(kogan::UniquePtr<TestObject>*)b)->value;
    });
}

void sort_raw_ptr_array(TestObject** arr, std::size_t size) {
    std::qsort(arr, size, sizeof(TestObject*),
               [](const void* a, const void* b) { return (*(TestObject**)a)->value - (*(TestObject**)b)->value; });
    for (std::size_t i = 0; i < size; ++i) {
        delete arr[i];
    }
    delete[] arr;
}

void sort_std_smart_ptr_array(std::shared_ptr<std::unique_ptr<TestObject>[]> arr, std::size_t size) {
    std::qsort(arr.get(), size, sizeof(std::unique_ptr<TestObject>), [](const void* a, const void* b) {
        return (*(std::unique_ptr<TestObject>*)a)->value - (*(std::unique_ptr<TestObject>*)b)->value;
    });
}

unsigned long long int test_smart_ptr_array(std::size_t size) {
    auto arr = create_smart_ptr_array(size);
    shuffle_smart_ptr_array(arr, size);
    return time_it([&]() { sort_smart_ptr_array(arr, size); });
}

unsigned long long int test_raw_ptr_array(std::size_t size) {
    auto arr = create_raw_ptr_array(size);
    shuffle_raw_ptr_array(arr, size);
    return time_it([&]() { sort_raw_ptr_array(arr, size); });
}

unsigned long long int test_std_smart_ptr_array(std::size_t size) {
    auto arr = create_std_smart_ptr_array(size);
    shuffle_std_smart_ptr_array(arr, size);
    return time_it([&]() { sort_std_smart_ptr_array(arr, size); });
}
