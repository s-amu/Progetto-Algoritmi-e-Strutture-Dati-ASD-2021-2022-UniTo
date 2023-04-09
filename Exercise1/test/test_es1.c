#include <stdlib.h>
#include "unity.h"
#include "header_es1.h"

static int* int_new(int n) {
  int* result = (int*) malloc(sizeof(int));
  *result = n;
  return result;
}

static int compare_ints(int* obj1, int* obj2) {
  return *obj1 - *obj2;
}

static SortedArray* create_test_objects() {
  SortedArray* sa = sorted_array_new((SortedArrayCmp) compare_ints);
  sorted_array_insert(sa, int_new(24));
  sorted_array_insert(sa, int_new(9));
  sorted_array_insert(sa, int_new(18));
  sorted_array_insert(sa, int_new(11));
  return sa;
}

static void delete_test_object(SortedArray* sa) {
  for(int i = 0; sorted_array_size(sa) > i; ++i) {
    free(sorted_array_get(sa, i));
  }
  sorted_array_free(sa);
}

static void sorted_zero_sized_array() {
  SortedArray* sa = sorted_array_new((SortedArrayCmp) compare_ints);

  quicksort(sa, 0, sorted_array_size(sa)-1);
  insertion_sort(sa);
  TEST_ASSERT_EQUAL(0, sorted_array_size(sa));
  sorted_array_free(sa);
}

static void sorted_one_sized_array() {
  SortedArray* sa = sorted_array_new((SortedArrayCmp) compare_ints);

  sorted_array_insert(sa, int_new(24));
  quicksort(sa, 0, sorted_array_size(sa)-1);
  insertion_sort(sa);
  TEST_ASSERT_EQUAL(1, sorted_array_size(sa));
  delete_test_object(sa);
}

static void sorted_multisized_array_insert_sort() {
  SortedArray* sa = create_test_objects();
  insertion_sort(sa);
  TEST_ASSERT_EQUAL(9, *(int*) sorted_array_get(sa, 0));
  TEST_ASSERT_EQUAL(11, *(int*) sorted_array_get(sa, 1));
  TEST_ASSERT_EQUAL(18, *(int*) sorted_array_get(sa, 2));
  TEST_ASSERT_EQUAL(24, *(int*) sorted_array_get(sa, 3));
  delete_test_object(sa);
}

static void sorted_multisized_array_quicksort() {
  SortedArray* sa = create_test_objects();
  quicksort(sa, 0, sorted_array_size(sa)-1);
  TEST_ASSERT_EQUAL(9, *(int*) sorted_array_get(sa, 0));
  TEST_ASSERT_EQUAL(11, *(int*) sorted_array_get(sa, 1));
  TEST_ASSERT_EQUAL(18, *(int*) sorted_array_get(sa, 2));
  TEST_ASSERT_EQUAL(24, *(int*) sorted_array_get(sa, 3));
  delete_test_object(sa);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(sorted_zero_sized_array);
  RUN_TEST(sorted_one_sized_array);
  RUN_TEST(sorted_multisized_array_insert_sort);
  RUN_TEST(sorted_multisized_array_quicksort);
  UNITY_END();
}
