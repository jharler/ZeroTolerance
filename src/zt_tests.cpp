/**************************************************************************************************
 ** file: zt_tests.cpp
 **
 ** This library is in the public domain.  Do with it what you will.
 **
 **************************************************************************************************
 **
 ** implementation notes:
 ** 
 ** Unit tests for the ZeroTolerance single header file libraries.
 **
 ** These tests aren't comprehensive and are probably terrible.  Essentially, I'll use the library
 ** and add tests for edge cases that I run into so at least I won't re-introduce the same bugs once
 ** they've been fixed.
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

bool test_memory()
{
	ztMemoryArena* memory_arena = zt_memMakeArena(1024);

	ztMemoryArena* sub_arena = zt_memMakeArena(128, memory_arena);
	ztTest_results(memory_arena->current_used == 128 + sizeof(ztMemoryArena) + sizeof(ztMemoryArena::allocation));

	char *temp = (char *)zt_memAlloc(memory_arena, 5);
	zt_strCpy(temp, 5, "test");

	ztTest_results(memory_arena->current_used == 128 + sizeof(ztMemoryArena) + 8 /* aligned to 4 bytes */ + sizeof(ztMemoryArena::allocation) * 2);
	zt_memFree(memory_arena, temp);
	ztTest_results(memory_arena->current_used == 128 + sizeof(ztMemoryArena) + sizeof(ztMemoryArena::allocation));
	ztTest_results(memory_arena->freed_allocs == 0);
	ztTest_results(memory_arena->free_cnt == 1);

	temp = (char *)zt_memAlloc(memory_arena, 32);
	zt_strCpy(temp, 32, "this is a longer string");
	zt_memFreeArena(sub_arena);

	ztTest_results(memory_arena->freed_allocs == 1);

	char *temp2 = (char *)zt_memAlloc(memory_arena, 16);
	zt_strCpy(temp2, 16, "123456789012345");
	ztTest_results(memory_arena->freed_allocs == 1);
	ztTest_results(memory_arena->latest && memory_arena->latest->length == 32);
	ztTest_results(memory_arena->latest && memory_arena->latest->next && memory_arena->latest->next->length == 16);
	ztTest_results(memory_arena->latest && memory_arena->latest->next && memory_arena->latest->next->next && memory_arena->latest->next->next->length == 76 ztReleaseOnly(+16));

	zt_memFree(memory_arena, temp);
	zt_memFree(memory_arena, temp2);

	ztTest_results(memory_arena->current_used == 0);
	ztTest_results(memory_arena->freed_allocs == 0);
	ztTest_results(memory_arena->latest == nullptr);

	zt_memFreeArena(memory_arena);

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

	// yeah, I know these aren't very comprehensive tests
	// when more precision is needed, I will add better tests
	ztTest_results(zt_strToInt("1", 0) == 1);
	ztTest_results(zt_strToInt("12", 0) == 12);
	ztTest_results(zt_strToInt("123", 0) == 123);
	ztTest_results(zt_strToInt("1234", 0) == 1234);
	ztTest_results(zt_strToInt("-1234", 0) == -1234);
	ztTest_results(zt_strToInt("1.123", 0) == 0);
	ztTest_results(zt_strToInt("abcd", 0) == 0);
	ztTest_results(zt_strToInt(" 123 ", 0) == 123);
	ztTest_results(zt_strToInt("- 123 ", 0) == 0);

	ztTest_results(zt_strToIntHex("0x12345678", 0) == 0x12345678);
	ztTest_results(zt_strToIntHex("0x87654321", 0) == 0x87654321);
	ztTest_results(zt_strToIntHex("0xdeadbeef", 0) == 0xdeadbeef);
	ztTest_results(zt_strToIntHex("0xabcdef01", 0) == 0xabcdef01);
	ztTest_results(zt_strToIntHex("0xffffffff", 0) == 0xffffffff);
	ztTest_results(zt_strToIntHex("0xffff0000", 0) == 0xffff0000);
	ztTest_results(zt_strToIntHex("0x0000ffff", 0) == 0x0000ffff);
	ztTest_results(zt_strToIntHex("0xgjh", 0) == 0);
	ztTest_results(zt_strToIntHex("nope", 0) == 0);

	ztTest_results(ztReal32Eq(zt_strToReal32("1.1", 0), 1.1f));
	ztTest_results(ztReal32Eq(zt_strToReal32("12.2", 0), 12.2f));
	ztTest_results(ztReal32Eq(zt_strToReal32("123.3", 0), 123.3f));
	ztTest_results(ztReal32Eq(zt_strToReal32("1234.4", 0), 1234.4f));
	ztTest_results(ztReal32Eq(zt_strToReal32("-1234.4", 0), -1234.4f));
	ztTest_results(ztReal32Eq(zt_strToReal32("1.123", 0), 1.123f));
	ztTest_results(ztReal32Eq(zt_strToReal32("abcd", 0), 0));
	ztTest_results(ztReal32Eq(zt_strToReal32(" 123.1 ", 0), 123.1f));
	ztTest_results(ztReal32Eq(zt_strToReal32("- 123 ", 0), 0));

	ztTest_results(ztReal64Eq(zt_strToReal64("1.1", 0), 1.1));
	ztTest_results(ztReal64Eq(zt_strToReal64("12.2", 0), 12.2));
	ztTest_results(ztReal64Eq(zt_strToReal64("123.3", 0), 123.3));
	ztTest_results(ztReal64Eq(zt_strToReal64("1234.4", 0), 1234.4));
	ztTest_results(ztReal64Eq(zt_strToReal64("-1234.4", 0), -1234.4));
	ztTest_results(ztReal64Eq(zt_strToReal64("1.123", 0), 1.123));
	ztTest_results(ztReal64Eq(zt_strToReal64("abcd", 0), 0));
	ztTest_results(ztReal64Eq(zt_strToReal64(" 123.1 ", 0), 123.1));
	ztTest_results(ztReal64Eq(zt_strToReal64("- 123 ", 0), 0));


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

	ztTest_results(zt_strJumpToNextToken(token_search) == token_2);
	ztTest_results(zt_strJumpToNextToken(token_2) == token_3);
	ztTest_results(zt_strJumpToNextToken(token_3) == token_4);
	ztTest_results(zt_strJumpToNextToken(token_4) == token_5);
	ztTest_results(zt_strJumpToNextToken(token_5) == token_6);
	ztTest_results(zt_strJumpToNextToken(token_7) == token_8);

	ztTest_results(zt_strGetNextTokenPos(token_search) == (int)token_2 - (int)token_search);
	ztTest_results(zt_strGetNextTokenPos(token_2) == (int)token_3 - (int)token_2);
	ztTest_results(zt_strGetNextTokenPos(token_3) == (int)token_4 - (int)token_3);
	ztTest_results(zt_strGetNextTokenPos(token_4) == (int)token_5 - (int)token_4);
	ztTest_results(zt_strGetNextTokenPos(token_5) == (int)token_6 - (int)token_5);
	ztTest_results(zt_strGetNextTokenPos(token_7) == zt_strPosNotFound);

	const char* multi_lines = "line one\r\nline two\r\nline three\r\n\"line four\"";
	const char* line_2 = multi_lines + 10;
	const char* line_3 = multi_lines + 20;
	const char* line_4 = multi_lines + 32;
	const char* line_5 = nullptr;

	ztTest_results(zt_strJumpToNextLine(multi_lines) == line_2);
	ztTest_results(zt_strJumpToNextLine(line_2) == line_3);
	ztTest_results(zt_strJumpToNextLine(line_3) == line_4);
	ztTest_results(zt_strJumpToNextLine(line_4) == line_5);

	ztTest_results(zt_strGetNextLinePos(multi_lines) == (int)line_2 - (int)multi_lines);
	ztTest_results(zt_strGetNextLinePos(line_2) == (int)line_3 - (int)line_2);
	ztTest_results(zt_strGetNextLinePos(line_3) == (int)line_4 - (int)line_3);
	ztTest_results(zt_strGetNextLinePos(line_4) == zt_strPosNotFound);

	ztToken tokens[32];
	zt_memSet(tokens, sizeof(ztToken) * ztElementsOf(tokens), 0);

	const char* tokenize_1 = "line one\r\nline two\r\nline three\r\n\"line four\"";
	ztTest_results(zt_strTokenize(tokenize_1, " \r\n", tokens, ztElementsOf(tokens), ztStrTokenizeFlags_IncludeTokens | ztStrTokenizeFlags_ProcessQuotes | ztStrTokenizeFlags_KeepQuotes) == 16);
	ztTest_results(tokens[0].beg ==  0 && tokens[0].len == 4);
	ztTest_results(tokens[1].beg ==  4 && tokens[1].len == 1);
	ztTest_results(tokens[2].beg ==  5 && tokens[2].len == 3);
	ztTest_results(tokens[3].beg ==  8 && tokens[3].len == 1);
	ztTest_results(tokens[4].beg ==  9 && tokens[4].len == 1);
	ztTest_results(tokens[5].beg == 10 && tokens[5].len == 4);
	ztTest_results(tokens[6].beg == 14 && tokens[6].len == 1);
	ztTest_results(tokens[7].beg == 15 && tokens[7].len == 3);
	ztTest_results(tokens[8].beg == 18 && tokens[8].len == 1);
	ztTest_results(tokens[9].beg == 19 && tokens[9].len == 1);
	ztTest_results(tokens[10].beg == 20 && tokens[10].len == 4);
	ztTest_results(tokens[11].beg == 24 && tokens[11].len == 1);
	ztTest_results(tokens[12].beg == 25 && tokens[12].len == 5);
	ztTest_results(tokens[13].beg == 30 && tokens[13].len == 1);
	ztTest_results(tokens[14].beg == 31 && tokens[14].len == 1);
	ztTest_results(tokens[15].beg == 32 && tokens[15].len == 11);

	zt_memSet(tokens, sizeof(ztToken) * ztElementsOf(tokens), 0);
	const char* tokenize_2 = "line one\r\nline two\r\nline three\r\n\" line four \"";
	ztTest_results(zt_strTokenize(tokenize_2, " \r\n", tokens, ztElementsOf(tokens), ztStrTokenizeFlags_ProcessQuotes) == 7);
	ztTest_results(tokens[0].beg == 0 && tokens[0].len == 4);
	ztTest_results(tokens[1].beg == 5 && tokens[1].len == 3);
	ztTest_results(tokens[2].beg == 10 && tokens[2].len == 4);
	ztTest_results(tokens[3].beg == 15 && tokens[3].len == 3);
	ztTest_results(tokens[4].beg == 20 && tokens[4].len == 4);
	ztTest_results(tokens[5].beg == 25 && tokens[5].len == 5);
	ztTest_results(tokens[6].beg == 33 && tokens[6].len == 11);

	zt_memSet(tokens, sizeof(ztToken) * ztElementsOf(tokens), 0);
	const char* tokenize_3 = "line one\r\n line two\r\n line three \r\n\" line four \"";
	ztTest_results(zt_strTokenize(tokenize_3, "\r\n", tokens, ztElementsOf(tokens), ztStrTokenizeFlags_ProcessQuotes | ztStrTokenizeFlags_TrimWhitespace) == 4);
	ztTest_results(tokens[0].beg ==  0 && tokens[0].len ==  8);
	ztTest_results(tokens[1].beg == 11 && tokens[1].len ==  8);
	ztTest_results(tokens[2].beg == 22 && tokens[2].len == 10);
	ztTest_results(tokens[3].beg == 36 && tokens[3].len == 11);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool test_files()
{
	char app_name[ztFileMaxPath];
	zt_fileGetAppBin(app_name, ztElementsOf(app_name));
	printf("app bin: %s\n", app_name);

	ztTest_results(zt_fileExists(app_name));

	char app_path[ztFileMaxPath];
	zt_fileGetAppPath(app_path, ztElementsOf(app_path));
	printf("app path: %s\n", app_path);

	char temp_file[ztFileMaxPath];
	zt_strPrintf(temp_file, ztElementsOf(temp_file), "%s%ctemp.txt", app_path, ztFilePathSeparator);
	printf("temp file: %s\n", temp_file);

	char temp_file_path[ztFileMaxPath];
	char temp_file_name[128];
	char temp_file_ext[128];

	zt_fileGetFullPath(temp_file, temp_file_path, ztElementsOf(temp_file_path));
	zt_fileGetFileName(temp_file, temp_file_name, ztElementsOf(temp_file_name));
	zt_fileGetFileExt (temp_file, temp_file_ext , ztElementsOf(temp_file_ext));

	printf("temp file path: %s\n", temp_file_path);

	ztTest_results(zt_strEquals(temp_file_name, "temp.txt"));
	ztTest_results(zt_strEquals(temp_file_ext, "txt"));

	char temp_file_copy[ztFileMaxPath];
	zt_strPrintf(temp_file_copy, ztElementsOf(temp_file_copy), "%s%ctemp_copy.txt", app_path, ztFilePathSeparator);
	printf("temp copy file: %s\n", temp_file);

	char *temp_file_data = "This is a test temp file.\n";
	zt_fileWriteEntireFile(temp_file, temp_file_data, zt_strLen(temp_file_data) + 1);

	i32 data_size = 0;
	char *data = (char *)zt_fileReadEntireFile(temp_file, &data_size);

	ztTest_results(zt_strEquals(temp_file_data, data));

	zt_memFree(nullptr, data);

	ztTest_results(zt_fileCopy(temp_file, temp_file_copy));
	ztTest_results(zt_fileExists(temp_file_copy));
	ztTest_results(zt_fileDelete(temp_file_copy));
	ztTest_results(zt_fileRename(temp_file, temp_file_copy));
	ztTest_results(zt_fileExists(temp_file) == false);
	ztTest_results(zt_fileDelete(temp_file_copy));
	ztTest_results(zt_fileExists(temp_file_copy) == false);

	char user_path[ztFileMaxPath];
	zt_fileGetUserPath(user_path, ztElementsOf(user_path), "zt_tests");
	printf("user path: %s\n", user_path);


	return true;
}

// ------------------------------------------------------------------------------------------------

// functions ======================================================================================

int main(char** argv, int argc)
{
	printf("running zt library unit tests\n");

	test_dataTypes();
	test_memory();
	test_strings();
	test_files();

	printf("\nresults: %d out of %d tests passed.\n\n", g_tests_success, g_tests_success + g_tests_failure);

	return 0;
}

// ------------------------------------------------------------------------------------------------
