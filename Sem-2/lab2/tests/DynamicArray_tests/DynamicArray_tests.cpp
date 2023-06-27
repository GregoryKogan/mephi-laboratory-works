//
// Created by Gregory Kogan on 11.05.2023.
//

#include "DynamicArray_tests.hpp"

kogan::TestSuite dynamic_array_suite("DynamicArray");

TEST(array_constructor, dynamic_array_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;

  kogan::DynamicArray<int> arr(values, 10);
  delete[] values;

  ASSERT(arr.get_length() == 10);
  ASSERT(arr.get(0) == 1);
  ASSERT(arr.get(2) == 3);
  ASSERT(arr.get(9) == 10);
}

TEST(length_constructor, dynamic_array_suite) {
  kogan::DynamicArray<int> arr(10);

  ASSERT(arr.get_length() == 10);
}

TEST(dynamic_array_constructor, dynamic_array_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;

  kogan::DynamicArray<int> init_arr(values, 10);
  kogan::DynamicArray<int> arr(
      init_arr); // NOLINT(performance-unnecessary-copy-initialization)
  delete[] values;

  ASSERT(arr.get_length() == init_arr.get_length());
  ASSERT(arr.get_length() == 10);
  ASSERT(arr.get(0) == 1);
  ASSERT(arr.get(2) == 3);
  ASSERT(arr.get(9) == 10);
  ASSERT(arr.get(0) == init_arr.get(0));
  ASSERT(arr.get(2) == init_arr.get(2));
  ASSERT(arr.get(9) == init_arr.get(9));
}

TEST(get, dynamic_array_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;
  kogan::DynamicArray<int> arr(values, 10);
  delete[] values;

  ASSERT(arr.get(0) == 1);
  ASSERT(arr.get(3) == 4);
  ASSERT(arr.get(7) == 8);
  ASSERT(arr.get(9) == 10);
  ASSERT(arr.get(arr.get_length() - 1) == 10);
}

TEST(get_single_item, dynamic_array_suite) {
  int *values = new int[1];
  values[0] = 42;
  kogan::DynamicArray<int> arr(values, 1);
  delete[] values;

  ASSERT(arr.get(0) == 42);
  ASSERT(arr.get(arr.get_length() - 1) == 42);
  ASSERT(arr.get_length() == 1);
}

TEST(get_negative_index_IndexOutOfRangeException, dynamic_array_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;
  kogan::DynamicArray<int> arr(values, 10);
  delete[] values;

  bool indexOutOfRangeExceptionThrown = false;
  try {
    arr.get(-1);
  } catch (kogan::IndexOutOfRangeException &e) {
    indexOutOfRangeExceptionThrown = true;
  }
  ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_big_index_IndexOutOfRangeException, dynamic_array_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;
  kogan::DynamicArray<int> arr(values, 10);
  delete[] values;

  bool indexOutOfRangeExceptionThrown = false;
  try {
    arr.get(10);
  } catch (kogan::IndexOutOfRangeException &e) {
    indexOutOfRangeExceptionThrown = true;
  }
  ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_length, dynamic_array_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;
  kogan::DynamicArray<int> arr(values, 10);
  delete[] values;

  ASSERT(arr.get_length() == 10);

  kogan::DynamicArray<int> arr_empty(0);
  ASSERT(arr_empty.get_length() == 0);
}

TEST(set, dynamic_array_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;
  kogan::DynamicArray<int> arr(values, 10);
  delete[] values;

  for (int i = 0; i < 10; ++i)
    arr.set(i, 10 - i);

  ASSERT(arr.get(0) == 10);
  ASSERT(arr.get(9) == 1);

  arr.set(0, -34);
  ASSERT(arr.get(0) == -34);
}

TEST(set_negative_index_IndexOutOfRangeException, dynamic_array_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;
  kogan::DynamicArray<int> arr(values, 10);
  delete[] values;

  bool indexOutOfRangeExceptionThrown = false;
  try {
    arr.set(-1, 0);
  } catch (kogan::IndexOutOfRangeException &e) {
    indexOutOfRangeExceptionThrown = true;
  }
  ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(set_big_index_IndexOutOfRangeException, dynamic_array_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;
  kogan::DynamicArray<int> arr(values, 10);
  delete[] values;

  bool indexOutOfRangeExceptionThrown = false;
  try {
    arr.set(10, 0);
  } catch (kogan::IndexOutOfRangeException &e) {
    indexOutOfRangeExceptionThrown = true;
  }
  ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(resize, dynamic_array_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;
  kogan::DynamicArray<int> arr(values, 10);
  delete[] values;

  arr.resize(5);
  ASSERT(arr.get_length() == 5);
  ASSERT(arr.get(0) == 1);
  ASSERT(arr.get(4) == 5);

  arr.resize(10);
  ASSERT(arr.get_length() == 10);
  ASSERT(arr.get(0) == 1);
  ASSERT(arr.get(4) == 5);
}

kogan::TestSuite get_dynamic_array_suite() { return dynamic_array_suite; }
