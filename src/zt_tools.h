/**************************************************************************************************
 ** file: zt_tools.h v 0.00 (active initial development)
 **
 ** This library is in the public domain.  Do with it what you will.
 **
 **************************************************************************************************
   
    Zero Tolerance Tools Library
   
    Single header library collection of powerful and easy to use utilities.  The goal is to be able
    to use this header file to easily create programs with access to a wide variety of useful tools.
   
    Be sure that #define ZT_TOOLS_IMPLEMENTATION is used in one cpp file before including this
    header file.

	#define ZT_TOOLS_IMPLEMENTATION
	#include "zt_tools.h"
    
    Options:
   
    ZT_TOOLS_RETURN_ON_NULLPTR_NO_ASSERT
   		- Removes the assert on ztReturnOnNull and ztReturnValOnNull macros.
   
    ZT_TOOLS_PROVIDE_APP_LOOP
		- Provides an app loop that consists of an initialization function, a loop function and a
		  cleanup function.  You must provide the following functions, using the #defines to 
		  identify them in the file that defines ZT_TOOLS_IMPLEMENTATION:

		  b32 zt_appInit();
		  #define ZT_TOOLS_APP_INIT	zt_appInit

		  b32 zt_appLoop(r32 dt);
		  #define ZT_TOOLS_APP_LOOP	zt_appLoop

		  void zt_appCleanup();
		  #define ZT_TOOLS_APP_CLEANUP	zt_appCleanup

		  The init and cleanup functions are optional.
    

	What's with the name "Zero Tolerance?"
		I chose the name because my goal is to have a zero tolerance policy for slow, bloated
		software, slow compile times, and long development time.  I want this library to be
		fast in execution, fast in compile times and fast and easy to use.

 **************************************************************************************************/

#ifndef __zt_tools_h_included__
#define __zt_tools_h_included__

// headers ========================================================================================

// forward declarations ===========================================================================

// types/enums/defines ============================================================================

// compiler defines
#if defined(_MSC_VER)
#	define ZT_COMPILER_MSVC
#	if defined(_WIN32)
#		define ZT_WIN32
#	elif defined(_WIN64)
#		define ZT_WIN64
#	endif
#else 
#	error "This compiler is currently unsupported."
#endif


// platform defines
#if defined(ZT_WIN32)
#	if defined(_CONSOLE)
#		define ZT_PLATFORM_STR	"Win32 Console"
#		define ZT_PLATFORM_WIN32_CONSOLE
#	else
#		define ZT_PLATFORM_STR	"Win32"
#		define ZT_PLATFORM_WIN32
#	endif
#elif defined(ZT_WIN64)
#	if defined(_CONSOLE)
#		define ZT_PLATFORM_STR	"Win64"
#		define ZT_PLATFORM_WIN64_CONSOLE
#	else
#		define ZT_PLATFORM_STR	"Win64"
#		define ZT_PLATFORM_WIN64
#	endif
#else
#	error "This platform is currently upsupported."
#endif


// useful macros
#define ztAssert(cond)	zt_assert(cond, #cond, __FILE__, __LINE__)
#define ztElementsOf(native_array)	((int)(sizeof(native_array) / sizeof((native_array)[0])))

#if _DEBUG
#define ztDebugOnly(code)	code
#define ztReleaseOnly(code)
#else
#define ztDebugOnly(code)
#define ztReleaseOnly(code)	code
#endif

#define ztKilobytes(kb)	((kb) * 1024LL)
#define ztMegabytes(mb)	(ztKilobytes(mb) * 1024LL)
#define ztGigabytes(gb)	(ztMegabytes(gb) * 1024LL)
#define ztTerabytes(tb)	(ztGigabytes(tb) * 1024LL)

#define ztBitAdd(var, flag)		((var) |= (flag))
#define ztBitRemove(var, flag)	((var) &= ~(flag))
#define ztBitIsSet(var, flag)	((var) & (flag))

#define ztMax(val1, val2) ( (val1) > (val2) ? (val1) : (val2) )
#define ztMin(val1, val2) ( (val1) < (val2) ? (val1) : (val2) )
#define ztClamp(val, min, max) ( val_min(max, (val_max(min, val))) )
#define ztAbs(val) ( (val) < 0 ? -(val) : (val) )
#define ztSwap(val1, val2) {auto temp = val1; val1 = val2; val2 = temp;}

#define zt_fiz(end)	for(int i = 0; i < (end); ++i)
#define zt_fjz(end)	for(int j = 0; j < (end); ++j)
#define zt_fkz(end) for(int k = 0; k < (end); ++k)

#if !defined(ZT_TOOLS_RETURN_ON_NULLPTR_NO_ASSERT)
#	define ztReturnOnNull(ptr) if (ptr == nullptr) { ztAssert(false && "Null pointer encountered: " ##ptr); return; }
#	define ztReturnValOnNull(ptr, retval) if (ptr == nullptr) { ztAssert(false && "Null pointer encountered: " ##ptr); return retval; };
#else
#	define ztReturnOnNull(ptr) if (ptr == nullptr) { return; }
#	define ztReturnValOnNull(ptr, retval) if (ptr == nullptr) { return retval; };
#endif


// types
#if defined(ZT_COMPILER_MSVC)
	typedef unsigned char      byte;
	typedef signed char        int8;
	typedef short              int16;
	typedef int                int32;
	typedef long long          int64;
	typedef unsigned char      uint8;
	typedef unsigned short     uint16;
	typedef unsigned int       uint32;
	typedef unsigned long long uint64;

	typedef float real32;
	typedef double real64;

	typedef uint64 pointer;

	typedef int8	i8;
	typedef int16	i16;
	typedef int32	i32;
	typedef int64	i64;
	typedef uint8	u8;
	typedef uint16	u16;
	typedef uint32	u32;
	typedef uint64	u64;
	typedef real32	r32;
	typedef real64	r64;
	typedef int32	b32;
#endif

// structures/classes =============================================================================

// functions ======================================================================================

// string functions
#define zt_strPosNotFound	-1

bool zt_strEquals(const char *s1, const char *s2, bool test_case = true);
int zt_strLen(const char *s1);
int zt_strCmp(const char *s1, const char *s2);
int zt_striCmp(const char *s1, const char *s2);

i32 zt_strToInt(const char *s, int def, bool* success = nullptr);
i32 zt_strToIntHex(const char *s, int def, bool* success = nullptr);
r32 zt_strToReal32(const char *s, r32 def, bool* success = nullptr);
r64 zt_strToReal64(const char *s, r64 def, bool* success = nullptr);

const char *zt_strFind(const char *haystack, const char *needle);
const char *zt_strFind(const char *haystack, const char *needle, int needle_len);
const char *zt_strFind(const char *haystack, int haystack_len, const char *needle, int needle_len);

int zt_strFindPos(const char *haystack, const char *needle);
int zt_strFindPos(const char *haystack, const char *needle, int needle_len);
int zt_strFindPos(const char *haystack, int haystack_len, const char *needle, int needle_len);

const char *zt_striFind(const char *haystack, const char *needle);
const char *zt_striFind(const char *haystack, const char *needle, int needle_len);
const char *zt_striFind(const char *haystack, int haystack_len, const char *needle, int needle_len);

int zt_striFindPos(const char *haystack, const char *needle);
int zt_striFindPos(const char *haystack, const char *needle, int needle_len);
int zt_striFindPos(const char *haystack, int haystack_len, const char *needle, int needle_len);

const char *zt_strReadToNextToken(const char *s);
const char *zt_strReadToNextToken(const char *s, int s_len);

int zt_strReadToNextTokenPos(const char *s);
int zt_strReadToNextTokenPos(const char *s, int s_len);



// ------------------------------------------------------------------------------------------------

#if defined(ZT_TOOLS_IMPLEMENTATION)

bool zt_strEquals(const char *s1, const char *s2, bool test_case)
{
	if (test_case) {
		return zt_strCmp(s1, s2) == 0;
	}
	else {
		return zt_striCmp(s1, s2) == 0;
	}
}

// ------------------------------------------------------------------------------------------------

int zt_strLen(const char *s1)
{
	int len = 0;
	while (s1 && *s1++) ++len;
	return len;
}

// ------------------------------------------------------------------------------------------------

int zt_strCmp(const char *s1, const char *s2)
{
	if (!s1 || !s2) {
		if (!s1 && s2) return -1;
		if (s1 && !s2) return 1;
		return 0;
	}

	while (s1 && s2 && *s1 && *s2 && *s1 == *s2) { ++s1; ++s2; }
	if (*s1 == *s2) return 0;
	if (*s1 < *s2) return -1;
	return 1;
}

// ------------------------------------------------------------------------------------------------

int zt_striCmp(const char *s1, const char *s2)
{
	if (!s1 || !s2) {
		if (!s1 && s2) return -1;
		if (s1 && !s2) return 1;
		return 0;
	}

	while (*s1 && *s2) {
		char c1 = *s1++;
		char c2 = *s2++;

		if (c1 >= 97 && c1 <= 122) c1 -= 32;
		if (c2 >= 97 && c2 <= 122) c2 -= 32;

		if (c1 != c2) {
			return c1 < c2 ? -1 : 1;
		}
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------

const char *zt_strFind(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	int needle_len = zt_strLen(needle);

	return zt_strFind(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

const char *zt_strFind(const char *haystack, const char *needle, int needle_len)
{
	int haystack_len = zt_strLen(haystack);
	return zt_strFind(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

const char *zt_strFind(const char *haystack, int haystack_len, const char *needle, int needle_len)
{
	if (haystack_len == 0 || needle_len == 0 || !haystack || !needle) return nullptr;

	zt_fiz((haystack_len - needle_len) + 1) {
		zt_fjz(needle_len) {
			if (haystack[i + j] != needle[j]) goto no_match;
		}
		return haystack + i;
		no_match:;
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

int zt_strFindPos(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	int needle_len = zt_strLen(needle);

	return zt_strFindPos(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

int zt_strFindPos(const char *haystack, const char *needle, int needle_len)
{
	int haystack_len = zt_strLen(haystack);
	return zt_strFindPos(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

int zt_strFindPos(const char *haystack, int haystack_len, const char *needle, int needle_len)
{
	if (haystack_len == 0 || needle_len == 0 || !haystack || !needle) return -1;

	zt_fiz((haystack_len - needle_len) + 1) {
		zt_fjz(needle_len) {
			if (haystack[i + j] != needle[j]) goto no_match;
		}
		return i;
	no_match:;
	}

	return zt_strPosNotFound;
}

// ------------------------------------------------------------------------------------------------

#define _zt_to_upper(c)	((c) >= 97 && (c) <= 122 ? (c) - 32 : (c))

const char *zt_striFind(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	int needle_len = zt_strLen(needle);

	return zt_striFind(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

const char *zt_striFind(const char *haystack, const char *needle, int needle_len)
{
	int haystack_len = zt_strLen(haystack);
	return zt_striFind(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

const char *zt_striFind(const char *haystack, int haystack_len, const char *needle, int needle_len)
{
	if (haystack_len == 0 || needle_len == 0 || !haystack || !needle) return nullptr;

	zt_fiz((haystack_len - needle_len) + 1) {
		zt_fjz(needle_len) {
			if (_zt_to_upper(haystack[i + j]) != _zt_to_upper(needle[j])) goto no_match;
		}
		return haystack + i;
	no_match:;
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

int zt_striFindPos(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	int needle_len = zt_strLen(needle);

	return zt_striFindPos(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

int zt_striFindPos(const char *haystack, const char *needle, int needle_len)
{
	int haystack_len = zt_strLen(haystack);
	return zt_striFindPos(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

int zt_striFindPos(const char *haystack, int haystack_len, const char *needle, int needle_len)
{
	if (haystack_len == 0 || needle_len == 0 || !haystack || !needle) return -1;

	zt_fiz((haystack_len - needle_len) + 1) {
		zt_fjz(needle_len) {
			if (_zt_to_upper(haystack[i + j]) != _zt_to_upper(needle[j])) goto no_match;
		}
		return i;
	no_match:;
	}

	return -1;
}

// ------------------------------------------------------------------------------------------------

const char* zt_strReadToNextToken(const char *s)
{
	return zt_strReadToNextToken(s, zt_strLen(s));
}

// ------------------------------------------------------------------------------------------------

const char* zt_strReadToNextToken(const char *s, int s_len)
{
	if (!s || s_len <= 0) return nullptr;

	for (int i = 1; i < s_len; ++i) {
		char ch = s[i];
		if (!(ch >= 48 && ch <= 57) && !(ch >= 65 && ch <= 90) && !(ch >= 97 && ch <= 122)) {
			return s + i;
		}
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

int zt_strReadToNextTokenPos(const char *s)
{
	return zt_strReadToNextTokenPos(s, zt_strLen(s));
}

// ------------------------------------------------------------------------------------------------

int zt_strReadToNextTokenPos(const char *s, int s_len)
{
	if (!s || s_len <= 0) return zt_strPosNotFound;

	for (int i = 1; i < s_len; ++i) {
		char ch = s[i];
		if (!(ch >= 48 && ch <= 57) && !(ch >= 65 && ch <= 90) && !(ch >= 97 && ch <= 122)) {
			return i;
		}
	}

	return zt_strPosNotFound;
}

// ------------------------------------------------------------------------------------------------

#if defined(ZT_TOOLS_PROVIDE_APP_LOOP)
 // ZT_TOOLS_APP_INIT
 // ZT_TOOLS_APP_LOOP
 // ZT_TOOLS_APP_CLEANUP

#if defined(ZT_PLATFORM_WIN32_CONSOLE) || defined(ZT_PLATFORM_WIN64_CONSOLE)
	int main( char** argv, int argc )
	{
		#if defined(ZT_TOOLS_APP_INIT)
			if(!ZT_TOOLS_APP_INIT())
				return 1;
		#endif

		while(ZT_TOOLS_APP_LOOP(0.0f)) {
		}

		#if defined(ZT_TOOLS_APP_CLEANUP)
			ZT_TOOLS_APP_CLEANUP();
		#endif

		return 0;
	}
#else

#endif // CONSOLE

#endif // ZT_TOOLS_PROVIDE_APP_LOOP

#endif // ZT_TOOLS_IMPLEMENTATION


#endif // include guard