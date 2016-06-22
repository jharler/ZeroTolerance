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

#define zt_testResults(test)	if (!(test)) { test_failure(#test, __LINE__); } else test_success(#test)


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
	zt_testResults(sizeof(byte) == 1);
	zt_testResults(sizeof(i8) == 1);
	zt_testResults(sizeof(i16) == 2);
	zt_testResults(sizeof(i32) == 4);
	zt_testResults(sizeof(i64) == 8);
	zt_testResults(sizeof(u8) == 1);
	zt_testResults(sizeof(u16) == 2);
	zt_testResults(sizeof(u32) == 4);
	zt_testResults(sizeof(u64) == 8);
	zt_testResults(sizeof(r32) == 4);
	zt_testResults(sizeof(r64) == 8);
	zt_testResults(sizeof(b32) == 4);

	{
		ztVec3 vec3_array[128]; r32 r32_array[128 * 3]; r32_array[0]++;
		zt_testResults(sizeof(vec3_array) == sizeof(r32_array));
	}
	{
		ztVec2 vec2_array[128]; r32 r32_array[128 * 2]; r32_array[0]++;
		zt_testResults(sizeof(vec2_array) == sizeof(r32_array));
	}
	{
		ztVec4 vec4_array[128]; r32 r32_array[128 * 4]; r32_array[0]++;
		zt_testResults(sizeof(vec4_array) == sizeof(r32_array));
	}


	return true;
}

// ------------------------------------------------------------------------------------------------

bool test_memory()
{
	ztMemoryArena* memory_arena = zt_memMakeArena(1024);

	ztMemoryArena* sub_arena = zt_memMakeArena(128, memory_arena);
	zt_testResults(memory_arena->current_used == 128 + sizeof(ztMemoryArena) + sizeof(ztMemoryArena::allocation));

	char *temp = (char *)zt_memAlloc(memory_arena, 5);
	zt_strCpy(temp, 5, "test");

	zt_testResults(memory_arena->current_used == 128 + sizeof(ztMemoryArena) + 8 /* aligned to 4 bytes */ + sizeof(ztMemoryArena::allocation) * 2);
	zt_memFree(memory_arena, temp);
	zt_testResults(memory_arena->current_used == 128 + sizeof(ztMemoryArena) + sizeof(ztMemoryArena::allocation));
	zt_testResults(memory_arena->freed_allocs == 0);
	zt_testResults(memory_arena->free_cnt == 1);

	temp = (char *)zt_memAlloc(memory_arena, 32);
	zt_strCpy(temp, 32, "this is a longer string");
	zt_memFreeArena(sub_arena);

	zt_testResults(memory_arena->freed_allocs == 1);

	char *temp2 = (char *)zt_memAlloc(memory_arena, 16);
	zt_strCpy(temp2, 16, "123456789012345");
	zt_testResults(memory_arena->freed_allocs == 1);
	zt_testResults(memory_arena->latest && memory_arena->latest->length == 32);
	zt_testResults(memory_arena->latest && memory_arena->latest->next && memory_arena->latest->next->length == 16);
	zt_testResults(memory_arena->latest && memory_arena->latest->next && memory_arena->latest->next->next && memory_arena->latest->next->next->length == 76 zt_releaseOnly(+16));

	zt_memFree(memory_arena, temp);
	zt_memFree(memory_arena, temp2);

	zt_testResults(memory_arena->current_used == 0);
	zt_testResults(memory_arena->freed_allocs == 0);
	zt_testResults(memory_arena->latest == nullptr);

	zt_memFreeArena(memory_arena);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool test_strings()
{
	zt_testResults(zt_strEquals("test string", "test string", true) == true);
	zt_testResults(zt_strEquals("test string", "test string", false) == true);
	zt_testResults(zt_strEquals("test string", "not equal", true) == false);
	zt_testResults(zt_strEquals("test string", "not equal", false) == false);
	zt_testResults(zt_strEquals("Test String", "test string", true) == false);
	zt_testResults(zt_strEquals("Test String", "test string", false) == true);
	zt_testResults(zt_strEquals("Test String", nullptr, true) == false);
	zt_testResults(zt_strEquals(nullptr, "Test String", true) == false);
	zt_testResults(zt_strEquals(nullptr, nullptr, true) == true);
	zt_testResults(zt_strEquals(nullptr, nullptr, false) == true);
	zt_testResults(zt_strStartsWith("Test String", "Test "));
	zt_testResults(zt_strStartsWith("Test String", "test ") == false);
	zt_testResults(zt_strStartsWith("Test String", "Test String"));
	zt_testResults(zt_strEndsWith("Test String", " String"));
	zt_testResults(zt_strEndsWith("Test String", " string") == false);
	zt_testResults(zt_strEndsWith("Test String", "Test String"));

	zt_testResults(zt_strLen("test string") == 11);
	zt_testResults(zt_strLen(nullptr) == 0);
	zt_testResults(zt_strLen("test string\0test") == 11);

	// zt_strEquals uses zt_strCmp and zt_striCmp, so we don't need to test them here

	// yeah, I know these aren't very comprehensive tests
	// when more precision is needed, I will add better tests
	zt_testResults(zt_strToInt("1", 0) == 1);
	zt_testResults(zt_strToInt("12", 0) == 12);
	zt_testResults(zt_strToInt("123", 0) == 123);
	zt_testResults(zt_strToInt("1234", 0) == 1234);
	zt_testResults(zt_strToInt("-1234", 0) == -1234);
	zt_testResults(zt_strToInt("1.123", 0) == 0);
	zt_testResults(zt_strToInt("abcd", 0) == 0);
	zt_testResults(zt_strToInt(" 123 ", 0) == 123);
	zt_testResults(zt_strToInt("- 123 ", 0) == 0);

	zt_testResults(zt_strToIntHex("0x12345678", 0) == 0x12345678);
	zt_testResults(zt_strToIntHex("0x87654321", 0) == 0x87654321);
	zt_testResults(zt_strToIntHex("0xdeadbeef", 0) == 0xdeadbeef);
	zt_testResults(zt_strToIntHex("0xabcdef01", 0) == 0xabcdef01);
	zt_testResults(zt_strToIntHex("0xffffffff", 0) == 0xffffffff);
	zt_testResults(zt_strToIntHex("0xffff0000", 0) == 0xffff0000);
	zt_testResults(zt_strToIntHex("0x0000ffff", 0) == 0x0000ffff);
	zt_testResults(zt_strToIntHex("0xgjh", 0) == 0);
	zt_testResults(zt_strToIntHex("nope", 0) == 0);

	zt_testResults(zt_real32Eq(zt_strToReal32("1.1", 0), 1.1f));
	zt_testResults(zt_real32Eq(zt_strToReal32("12.2", 0), 12.2f));
	zt_testResults(zt_real32Eq(zt_strToReal32("123.3", 0), 123.3f));
	zt_testResults(zt_real32Eq(zt_strToReal32("1234.4", 0), 1234.4f));
	zt_testResults(zt_real32Eq(zt_strToReal32("-1234.4", 0), -1234.4f));
	zt_testResults(zt_real32Eq(zt_strToReal32("1.123", 0), 1.123f));
	zt_testResults(zt_real32Eq(zt_strToReal32("abcd", 0), 0));
	zt_testResults(zt_real32Eq(zt_strToReal32(" 123.1 ", 0), 123.1f));
	zt_testResults(zt_real32Eq(zt_strToReal32("- 123 ", 0), 0));

	zt_testResults(zt_real64Eq(zt_strToReal64("1.1", 0), 1.1));
	zt_testResults(zt_real64Eq(zt_strToReal64("12.2", 0), 12.2));
	zt_testResults(zt_real64Eq(zt_strToReal64("123.3", 0), 123.3));
	zt_testResults(zt_real64Eq(zt_strToReal64("1234.4", 0), 1234.4));
	zt_testResults(zt_real64Eq(zt_strToReal64("-1234.4", 0), -1234.4));
	zt_testResults(zt_real64Eq(zt_strToReal64("1.123", 0), 1.123));
	zt_testResults(zt_real64Eq(zt_strToReal64("abcd", 0), 0));
	zt_testResults(zt_real64Eq(zt_strToReal64(" 123.1 ", 0), 123.1));
	zt_testResults(zt_real64Eq(zt_strToReal64("- 123 ", 0), 0));


	const char *haystack_one = "This is a long, long string to test with";
	const char *needle_1 = "This", *needle_2 = "long ", *needle_3 = "with", *needle_4 = "this", *needle_5 = "LONG ", *needle_6 = "WITH", *needle_x = "does not exist";

	zt_testResults(zt_strFind(haystack_one, needle_1) == haystack_one);
	zt_testResults(zt_strFind(haystack_one, needle_2) == haystack_one + 16);
	zt_testResults(zt_strFind(haystack_one, needle_3) == haystack_one + 36);
	zt_testResults(zt_strFind(haystack_one, needle_x) == nullptr);
	zt_testResults(zt_striFind(haystack_one, needle_4) == haystack_one);
	zt_testResults(zt_striFind(haystack_one, needle_5) == haystack_one + 16);
	zt_testResults(zt_striFind(haystack_one, needle_6) == haystack_one + 36);
	zt_testResults(zt_striFind(haystack_one, needle_x) == nullptr);

	zt_testResults(zt_strFindPos(haystack_one, needle_1, 0) == 0);
	zt_testResults(zt_strFindPos(haystack_one, needle_2, 0) == 16);
	zt_testResults(zt_strFindPos(haystack_one, needle_3, 0) == 36);
	zt_testResults(zt_strFindPos(haystack_one, needle_x, 0) == -1);
	zt_testResults(zt_striFindPos(haystack_one, needle_4, 0) == 0);
	zt_testResults(zt_striFindPos(haystack_one, needle_5, 0) == 16);
	zt_testResults(zt_striFindPos(haystack_one, needle_6, 0) == 36);
	zt_testResults(zt_striFindPos(haystack_one, needle_x, 0) == -1);

	const char *token_search = "one, two, three, four";
	const char *token_2 = token_search + 3, *token_3 = token_search + 4, *token_4 = token_search + 8, *token_5 = token_search + 9, *token_6 = token_search + 15, *token_7 = token_search + 16, *token_8 = nullptr;

	zt_testResults(zt_strJumpToNextToken(token_search) == token_2);
	zt_testResults(zt_strJumpToNextToken(token_2) == token_3);
	zt_testResults(zt_strJumpToNextToken(token_3) == token_4);
	zt_testResults(zt_strJumpToNextToken(token_4) == token_5);
	zt_testResults(zt_strJumpToNextToken(token_5) == token_6);
	zt_testResults(zt_strJumpToNextToken(token_7) == token_8);

	zt_testResults(zt_strGetNextTokenPos(token_search) == (int)token_2 - (int)token_search);
	zt_testResults(zt_strGetNextTokenPos(token_2) == (int)token_3 - (int)token_2);
	zt_testResults(zt_strGetNextTokenPos(token_3) == (int)token_4 - (int)token_3);
	zt_testResults(zt_strGetNextTokenPos(token_4) == (int)token_5 - (int)token_4);
	zt_testResults(zt_strGetNextTokenPos(token_5) == (int)token_6 - (int)token_5);
	zt_testResults(zt_strGetNextTokenPos(token_7) == ztStrPosNotFound);

	const char* multi_lines = "line one\r\nline two\r\nline three\r\n\"line four\"";
	const char* line_2 = multi_lines + 10;
	const char* line_3 = multi_lines + 20;
	const char* line_4 = multi_lines + 32;
	const char* line_5 = nullptr;

	zt_testResults(zt_strJumpToNextLine(multi_lines) == line_2);
	zt_testResults(zt_strJumpToNextLine(line_2) == line_3);
	zt_testResults(zt_strJumpToNextLine(line_3) == line_4);
	zt_testResults(zt_strJumpToNextLine(line_4) == line_5);

	zt_testResults(zt_strGetNextLinePos(multi_lines) == (int)line_2 - (int)multi_lines);
	zt_testResults(zt_strGetNextLinePos(line_2) == (int)line_3 - (int)line_2);
	zt_testResults(zt_strGetNextLinePos(line_3) == (int)line_4 - (int)line_3);
	zt_testResults(zt_strGetNextLinePos(line_4) == ztStrPosNotFound);

	ztToken tokens[32];
	zt_memSet(tokens, sizeof(ztToken) * zt_elementsOf(tokens), 0);

	const char* tokenize_1 = "line one\r\nline two\r\nline three\r\n\"line four\"";
	zt_testResults(zt_strTokenize(tokenize_1, " \r\n", tokens, zt_elementsOf(tokens), ztStrTokenizeFlags_IncludeTokens | ztStrTokenizeFlags_ProcessQuotes | ztStrTokenizeFlags_KeepQuotes) == 16);
	zt_testResults(tokens[0].beg ==  0 && tokens[0].len == 4);
	zt_testResults(tokens[1].beg ==  4 && tokens[1].len == 1);
	zt_testResults(tokens[2].beg ==  5 && tokens[2].len == 3);
	zt_testResults(tokens[3].beg ==  8 && tokens[3].len == 1);
	zt_testResults(tokens[4].beg ==  9 && tokens[4].len == 1);
	zt_testResults(tokens[5].beg == 10 && tokens[5].len == 4);
	zt_testResults(tokens[6].beg == 14 && tokens[6].len == 1);
	zt_testResults(tokens[7].beg == 15 && tokens[7].len == 3);
	zt_testResults(tokens[8].beg == 18 && tokens[8].len == 1);
	zt_testResults(tokens[9].beg == 19 && tokens[9].len == 1);
	zt_testResults(tokens[10].beg == 20 && tokens[10].len == 4);
	zt_testResults(tokens[11].beg == 24 && tokens[11].len == 1);
	zt_testResults(tokens[12].beg == 25 && tokens[12].len == 5);
	zt_testResults(tokens[13].beg == 30 && tokens[13].len == 1);
	zt_testResults(tokens[14].beg == 31 && tokens[14].len == 1);
	zt_testResults(tokens[15].beg == 32 && tokens[15].len == 11);

	zt_memSet(tokens, sizeof(ztToken) * zt_elementsOf(tokens), 0);
	const char* tokenize_2 = "line one\r\nline two\r\nline three\r\n\" line four \"";
	zt_testResults(zt_strTokenize(tokenize_2, " \r\n", tokens, zt_elementsOf(tokens), ztStrTokenizeFlags_ProcessQuotes) == 7);
	zt_testResults(tokens[0].beg == 0 && tokens[0].len == 4);
	zt_testResults(tokens[1].beg == 5 && tokens[1].len == 3);
	zt_testResults(tokens[2].beg == 10 && tokens[2].len == 4);
	zt_testResults(tokens[3].beg == 15 && tokens[3].len == 3);
	zt_testResults(tokens[4].beg == 20 && tokens[4].len == 4);
	zt_testResults(tokens[5].beg == 25 && tokens[5].len == 5);
	zt_testResults(tokens[6].beg == 33 && tokens[6].len == 11);

	zt_memSet(tokens, sizeof(ztToken) * zt_elementsOf(tokens), 0);
	const char* tokenize_3 = "line one\r\n line two\r\n line three \r\n\" line four \"";
	zt_testResults(zt_strTokenize(tokenize_3, "\r\n", tokens, zt_elementsOf(tokens), ztStrTokenizeFlags_ProcessQuotes | ztStrTokenizeFlags_TrimWhitespace) == 4);
	zt_testResults(tokens[0].beg ==  0 && tokens[0].len ==  8);
	zt_testResults(tokens[1].beg == 11 && tokens[1].len ==  8);
	zt_testResults(tokens[2].beg == 22 && tokens[2].len == 10);
	zt_testResults(tokens[3].beg == 36 && tokens[3].len == 11);


	//--test -t -fFLAG --flag=TEST "remaining arguments"
	const char* argv[] = {
		"--test",
		"-b",
		"-rFLAG",
		"--flag=TEST",
		"remaining arguments"
	};

	zt_testResults(zt_cmdHasArg(argv, zt_elementsOf(argv), "t", "test"));
	zt_testResults(zt_cmdHasArg(argv, zt_elementsOf(argv), "b", "best"));
	zt_testResults(zt_cmdHasArg(argv, zt_elementsOf(argv), "m", "missing") == false);
	zt_testResults(zt_cmdHasArg(argv, zt_elementsOf(argv), "f", "flag"));
	zt_testResults(zt_cmdHasArg(argv, zt_elementsOf(argv), "r", "rest"));

	char cmd_val[128];
	zt_testResults(zt_cmdGetArg(argv, zt_elementsOf(argv), "r", "rest", cmd_val, zt_elementsOf(cmd_val)));
	zt_testResults(zt_strEquals(cmd_val, "FLAG"));
	zt_testResults(zt_cmdGetArg(argv, zt_elementsOf(argv), "f", "flag", cmd_val, zt_elementsOf(cmd_val)));
	zt_testResults(zt_strEquals(cmd_val, "TEST"));
	zt_testResults(zt_cmdGetArg(argv, zt_elementsOf(argv), "m", "missing", cmd_val, zt_elementsOf(cmd_val)) == false);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool test_files()
{
	char app_name[ztFileMaxPath];
	zt_fileGetAppBin(app_name, zt_elementsOf(app_name));
	printf("app bin: %s\n", app_name);

	zt_testResults(zt_fileExists(app_name));

	char app_path[ztFileMaxPath];
	zt_fileGetAppPath(app_path, zt_elementsOf(app_path));
	printf("app path: %s\n", app_path);

	char temp_file[ztFileMaxPath];
	zt_strPrintf(temp_file, zt_elementsOf(temp_file), "%s%ctemp.txt", app_path, ztFilePathSeparator);
	printf("temp file: %s\n", temp_file);

	char temp_file_path[ztFileMaxPath];
	char temp_file_name[128];
	char temp_file_ext[128];

	zt_fileGetFullPath(temp_file, temp_file_path, zt_elementsOf(temp_file_path));
	zt_fileGetFileName(temp_file, temp_file_name, zt_elementsOf(temp_file_name));
	zt_fileGetFileExt (temp_file, temp_file_ext , zt_elementsOf(temp_file_ext));

	printf("temp file path: %s\n", temp_file_path);

	zt_testResults(zt_strEquals(temp_file_name, "temp.txt"));
	zt_testResults(zt_strEquals(temp_file_ext, "txt"));

	char temp_file_copy[ztFileMaxPath];
	zt_strPrintf(temp_file_copy, zt_elementsOf(temp_file_copy), "%s%ctemp_copy.txt", app_path, ztFilePathSeparator);
	printf("temp copy file: %s\n", temp_file);

	char *temp_file_data = "This is a test temp file.\n";
	zt_writeEntireFile(temp_file, temp_file_data, zt_strLen(temp_file_data) + 1);

	i32 data_size = 0;
	char *data = (char *)zt_readEntireFile(temp_file, &data_size);

	zt_testResults(zt_strEquals(temp_file_data, data));

	zt_memFree(nullptr, data);

	zt_testResults(zt_fileCopy(temp_file, temp_file_copy));
	zt_testResults(zt_fileExists(temp_file_copy));
	zt_testResults(zt_fileDelete(temp_file_copy));
	zt_testResults(zt_fileRename(temp_file, temp_file_copy));
	zt_testResults(zt_fileExists(temp_file) == false);
	zt_testResults(zt_fileDelete(temp_file_copy));
	zt_testResults(zt_fileExists(temp_file_copy) == false);

	char user_path[ztFileMaxPath];
	zt_fileGetUserPath(user_path, zt_elementsOf(user_path), "zt_tests");
	printf("user path: %s\n", user_path);


	char serial_file[ztFileMaxPath];
	zt_strPrintf(serial_file, ztFileMaxPath, "%s%cserial.dat", app_path, ztFilePathSeparator);
	char* serial_file_ident = "zt.test.serial.format";
	ztSerial serial;
	bool serial_valid = false;
	i32 version = 0x01002003;

	const char* serial_str = "This is a stored string.";
	u8 serial_data[16] = { 0x48, 0xa3, 0xf8, 0x8b, 0x01, 0x00, 0xce, 0xde, 0xad, 0xbe, 0xef, 0x19, 0x80, 0x04, 0x28, 0x29 };
	zt_testResults(serial_valid = zt_serialMakeWriter(&serial, serial_file, serial_file_ident, 0x01002003));
	if (serial_valid) {
		zt_serialGroupPush(&serial);
		{
			zt_serialWrite(&serial, (i8)1);
			zt_serialWrite(&serial, (i16)2);
			zt_serialWrite(&serial, (i32)3);
			zt_serialWrite(&serial, (i64)4);
			zt_serialGroupPush(&serial);
			{
				zt_serialWrite(&serial, (u8)5);
				zt_serialWrite(&serial, (u16)6);
				zt_serialWrite(&serial, (u32)7);
				zt_serialWrite(&serial, (u64)8);

				zt_serialGroupPush(&serial);
				{
					zt_serialWrite(&serial, serial_str, zt_strLen(serial_str));
					zt_serialWrite(&serial, serial_data, sizeof(serial_data));
				}
				zt_serialGroupPop(&serial);
			}
			zt_serialGroupPop(&serial);
		}
		zt_serialGroupPop(&serial);

		zt_serialClose(&serial);
	}

	zt_testResults(serial_valid = zt_serialMakeReader(&serial, serial_file, serial_file_ident));
	if (serial_valid) {
		zt_testResults(zt_serialGroupPush(&serial));
		{
			i8  t1; zt_testResults(zt_serialRead(&serial, &t1)); zt_testResults(t1 == 1);
			i16 t2; zt_testResults(zt_serialRead(&serial, &t2)); zt_testResults(t2 == 2);
			i32 t3; zt_testResults(zt_serialRead(&serial, &t3)); zt_testResults(t3 == 3);
			i64 t4; zt_testResults(zt_serialRead(&serial, &t4)); zt_testResults(t4 == 4);
			zt_testResults(zt_serialGroupPush(&serial));
			{
				u8  t5; zt_testResults(zt_serialRead(&serial, &t5)); zt_testResults(t5 == 5);
				u16 t6; zt_testResults(zt_serialRead(&serial, &t6)); zt_testResults(t6 == 6);
				u32 t7; zt_testResults(zt_serialRead(&serial, &t7)); zt_testResults(t7 == 7);
				u64 t8; zt_testResults(zt_serialRead(&serial, &t8)); zt_testResults(t8 == 8);

				zt_testResults(zt_serialGroupPush(&serial));
				{
					char string_buffer[256]; int string_buffer_read = 0;
					zt_testResults(zt_serialRead(&serial, string_buffer, zt_elementsOf(string_buffer), &string_buffer_read)); 
					zt_testResults(zt_strEquals(string_buffer, serial_str)); 
					zt_testResults(string_buffer_read == zt_strLen(serial_str));

					u8 data_buffer[32]; int data_buffer_read = 0;
					zt_testResults(zt_serialRead(&serial, (void*)data_buffer, sizeof(data_buffer), &data_buffer_read));
					zt_testResults(zt_memCmp(data_buffer, serial_data, data_buffer_read) == 0);
					zt_testResults(data_buffer_read == sizeof(serial_data));
				}
				zt_testResults(zt_serialGroupPop(&serial));
			}
			zt_testResults(zt_serialGroupPop(&serial));
		}
		zt_testResults(zt_serialGroupPop(&serial));

		zt_serialClose(&serial);
	}

	// now let's corrupt the file and see what happens
	byte serial_file_contents[1024];
	i32 serial_file_size = zt_readEntireFile(serial_file, serial_file_contents, sizeof(serial_file_contents));
	zt_testResults(serial_file_size > 0);
	if (serial_file_size > 0) {
		int idx = serial_file_size - 16;
		serial_file_contents[idx] = 0;
		serial_file_contents[idx + 1] = 0;
		serial_file_contents[idx + 2] = 0;
		zt_writeEntireFile(serial_file, serial_file_contents, serial_file_size);

		serial_valid = zt_serialMakeReader(&serial, serial_file, serial_file_ident);
		zt_testResults(!serial_valid);
		zt_testResults(serial.mode == ztSerialMode_Corrupt);

		zt_serialClose(&serial);
	}

	char ini_file[ztFileMaxPath] = { 0 };
	zt_strPrintf(ini_file, ztFileMaxPath, "%s%cinifile.ini", app_path, ztFilePathSeparator);
	char* test_value = "value";
	char test_value_buffer[128];

	zt_testResults(zt_iniFileSetValue(ini_file, "general", "test-key", test_value));
	zt_testResults(zt_iniFileGetValue(ini_file, "general", "test-key", "invalid", test_value_buffer, sizeof(test_value_buffer)) == zt_strLen(test_value));
	zt_testResults(zt_strEquals(test_value, test_value_buffer));
	

	return true;
}

// ------------------------------------------------------------------------------------------------

bool test_random()
{
	ztRandom random;
	zt_randomInit(&random, 123456);

	i32 ivalue = zt_randomInt(&random, 0, 999);
	zt_testResults(ivalue == 986);

	r32 rvalue = zt_randomVal(&random);
	zt_testResults(zt_real32Eq(0.281600f, rvalue));

	for (int i = 0; i < 10000; ++i) {
		ivalue = zt_randomInt(&random, 0, 999);
		if (!(ivalue >= 0 && ivalue < 999))
			zt_testResults(ivalue >= 0 && ivalue < 999);
	}

	for (int i = 0; i < 10000; ++i) {
		rvalue = zt_randomVal(&random);
		if (!(rvalue >= 0.00000f && rvalue <= 1.000000f))
			zt_testResults(rvalue >= 0.00000f && rvalue <= 1.000000f);
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

// functions ======================================================================================

int main(int argc, char** argv)
{
	printf("running zt library unit tests\n");

	test_dataTypes();
	test_memory();
	test_strings();
	test_files();
	test_random();

	printf("\nresults: %d out of %d tests passed.\n\n", g_tests_success, g_tests_success + g_tests_failure);

	return 0;
}

// ------------------------------------------------------------------------------------------------
