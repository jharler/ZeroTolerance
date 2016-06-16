/**************************************************************************************************
 ** Copyright (c) Joshua Harler
 **
 ** file: zt_tests.cpp
 **
 **************************************************************************************************
 **
 ** implementation notes:
 ** 
 ** Unit tests for the ZeroTolerance single header file libraries.
 ** 
 **************************************************************************************************/

// headers ========================================================================================

#define ZT_TOOLS_IMPLEMENTATION
#include "zt_tools.h"

#include <stdio.h>


// types/enums/defines ============================================================================

#define ztTest_results(test)	if (!(test)) { test_failure(#test, __LINE__); } else test_success(#test)


// structs/classes ================================================================================

// variables ======================================================================================

int32 g_tests_success = 0;
int32 g_tests_failure = 0;

// private functions ==============================================================================

bool test_failure(const char* test, int line)
{
	g_tests_failure += 1;
	printf("** FAIL: %s (line %d)\n", test, line);
	return false;
}

// ------------------------------------------------------------------------------------------------

void test_success(const char* test)
{
	g_tests_success += 1;
//	printf("success: %s\n", test);
}

// ------------------------------------------------------------------------------------------------

bool test_dataTypes()
{
	ztTest_results(sizeof(byte) == 1);
	ztTest_results(sizeof(i8) == 1);
	ztTest_results(sizeof(i16) == 2);
	ztTest_results(sizeof(i32) == 4);
	ztTest_results(sizeof(i64) == 8);
	ztTest_results(sizeof(u8) == 1);
	ztTest_results(sizeof(u16) == 2);
	ztTest_results(sizeof(u32) == 4);
	ztTest_results(sizeof(u64) == 8);
	ztTest_results(sizeof(r32) == 4);
	ztTest_results(sizeof(r64) == 8);
	ztTest_results(sizeof(b32) == 4);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool test_strings()
{
	ztTest_results(zt_strEquals("test string", "test string", true) == true);
	ztTest_results(zt_strEquals("test string", "test string", false) == true);
	ztTest_results(zt_strEquals("test string", "not equal", true) == false);
	ztTest_results(zt_strEquals("test string", "not equal", false) == false);
	ztTest_results(zt_strEquals("Test String", "test string", true) == false);
	ztTest_results(zt_strEquals("Test String", "test string", false) == true);
	ztTest_results(zt_strEquals("Test String", nullptr, true) == false);
	ztTest_results(zt_strEquals(nullptr, "Test String", true) == false);
	ztTest_results(zt_strEquals(nullptr, nullptr, true) == true);
	ztTest_results(zt_strEquals(nullptr, nullptr, false) == true);

	ztTest_results(zt_strLen("test string") == 11);
	ztTest_results(zt_strLen(nullptr) == 0);
	ztTest_results(zt_strLen("test string\0test") == 11);

	// zt_strEquals uses zt_strCmp and zt_striCmp, so we don't need to test them here

	const char *haystack_one = "This is a long, long string to test with";
	const char *needle_1 = "This", *needle_2 = "long ", *needle_3 = "with", *needle_4 = "this", *needle_5 = "LONG ", *needle_6 = "WITH", *needle_x = "does not exist";

	ztTest_results(zt_strFind(haystack_one, needle_1) == haystack_one);
	ztTest_results(zt_strFind(haystack_one, needle_2) == haystack_one + 16);
	ztTest_results(zt_strFind(haystack_one, needle_3) == haystack_one + 36);
	ztTest_results(zt_strFind(haystack_one, needle_x) == nullptr);
	ztTest_results(zt_striFind(haystack_one, needle_4) == haystack_one);
	ztTest_results(zt_striFind(haystack_one, needle_5) == haystack_one + 16);
	ztTest_results(zt_striFind(haystack_one, needle_6) == haystack_one + 36);
	ztTest_results(zt_striFind(haystack_one, needle_x) == nullptr);

	ztTest_results(zt_strFindPos(haystack_one, needle_1) == 0);
	ztTest_results(zt_strFindPos(haystack_one, needle_2) == 16);
	ztTest_results(zt_strFindPos(haystack_one, needle_3) == 36);
	ztTest_results(zt_strFindPos(haystack_one, needle_x) == -1);
	ztTest_results(zt_striFindPos(haystack_one, needle_4) == 0);
	ztTest_results(zt_striFindPos(haystack_one, needle_5) == 16);
	ztTest_results(zt_striFindPos(haystack_one, needle_6) == 36);
	ztTest_results(zt_striFindPos(haystack_one, needle_x) == -1);

	const char *token_search = "one, two, three, four";
	const char *token_2 = token_search + 3, *token_3 = token_search + 4, *token_4 = token_search + 8, *token_5 = token_search + 9, *token_6 = token_search + 15, *token_7 = token_search + 16, *token_8 = nullptr;

	ztTest_results(zt_strReadToNextToken(token_search) == token_2);
	ztTest_results(zt_strReadToNextToken(token_2) == token_3);
	ztTest_results(zt_strReadToNextToken(token_3) == token_4);
	ztTest_results(zt_strReadToNextToken(token_4) == token_5);
	ztTest_results(zt_strReadToNextToken(token_5) == token_6);
	ztTest_results(zt_strReadToNextToken(token_7) == token_8);

	return true;
}

// functions ======================================================================================

int main(char** argv, int argc)
{
	printf("running zt library unit tests\n");

	test_dataTypes();
	test_strings();

	printf("\nresults: %d out of %d tests passed.\n\n", g_tests_success, g_tests_success + g_tests_failure);

	return 0;
}

// ------------------------------------------------------------------------------------------------
