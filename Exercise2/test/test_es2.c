#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "header_es2.h"

/*
* Test suite for SkipList data structure and algorithms
*/

//function used to compare item (string)
static int precedes_string (void * item_1 , void* item_2 ){
	char * string_item_1 = (char*)item_1;
	char * string_item_2 = (char*)item_2;
	return strcmp((char*)string_item_1 , (char*)string_item_2);
}
 
// Data elements that are initialized before each test 
static char *s1;
static char* s2;
static char* s3;
static char* s4;

Skiplist*  setUp_string (Skiplist* list, int (*precedes_string)(void*, void*)) {
	s1 = "casa" ;
	s2 = "famiglia";
	s3 = "nonna";
	s4 = "cane";
	Skiplist_init(list, precedes_string);
	return list;
}

static void tearDoWn (Skiplist* list) {
	deleteSkipList(list);
}

static void test_SkipList_empty_zero_el(void) {
	Skiplist list;
	setUp_string(&list,precedes_string);
	TEST_ASSERT_TRUE(Skiplist_is_empty(&list));
	tearDoWn(&list);
}

static void test_SkipList_empty_one_el(void) {
	Skiplist list;
	setUp_string(&list, precedes_string);
	insertSkipList(&list, &s1);
	TEST_ASSERT_FALSE(Skiplist_is_empty(&list));
	tearDoWn(&list);
}

static void test_SkipList_empty_two_el(void) {
	Skiplist list;
	setUp_string(&list, precedes_string);
	insertSkipList(&list, &s1);
	insertSkipList(&list, &s2);
	TEST_ASSERT_FALSE(Skiplist_is_empty(&list));
	tearDoWn (&list);
}

static void test_SkipList_search_element(void) {
	Skiplist list;
	setUp_string(&list,precedes_string);
	insertSkipList(&list, &s1);
	TEST_ASSERT_EQUAL_PTR(&s1, searchSkipList(&list, &s1));
	tearDoWn(&list);
}

static void test_SkipList_search_two_element(void) {
	Skiplist list;
	setUp_string(&list,precedes_string);
	insertSkipList(&list, &s1);
	insertSkipList(&list, &s2);
	TEST_ASSERT_EQUAL_PTR(&s2, searchSkipList(&list, &s2));
	tearDoWn(&list);
}

static void test_SkipList_search_three_element(void) {
	Skiplist list;
	setUp_string(&list,precedes_string);
	insertSkipList(&list, &s1);
	insertSkipList(&list, &s2);
	insertSkipList(&list, &s3);
	TEST_ASSERT_EQUAL_PTR(&s3, searchSkipList(&list, &s3));
	tearDoWn(&list);
}

static void skipList_get_elem_test(void) {
	Skiplist list;
	setUp_string(&list,precedes_string);
	insertSkipList(&list, &s1);
	insertSkipList(&list, &s2);
	insertSkipList(&list, &s3);
	TEST_ASSERT_EQUAL_PTR(&s2, (char*)SkipList_get_elem(&list, 1));
	tearDoWn(&list);
}

int main(void) {
	// TEST SESSION
	UNITY_BEGIN();
	RUN_TEST(test_SkipList_empty_zero_el);
	RUN_TEST(test_SkipList_empty_one_el);
	RUN_TEST(test_SkipList_empty_two_el);
	RUN_TEST(test_SkipList_search_element);
	RUN_TEST(test_SkipList_search_two_element);
	RUN_TEST(test_SkipList_search_three_element);
	RUN_TEST(skipList_get_elem_test);
	UNITY_END();
}
