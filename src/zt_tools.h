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
    header file:

		#define ZT_TOOLS_IMPLEMENTATION
		#include "zt_tools.h"
    
 **************************************************************************************************

    Options:
   
    ZT_TOOLS_RETURN_ON_NULLPTR_NO_ASSERT
   		- Removes the assert on ztReturnOnNull and ztReturnValOnNull macros.
   

 **************************************************************************************************

	Implimentation Options: (only used with ZT_TOOLS_IMPLIMENTATION #include)

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
    
	ZT_MAX_LOG_CALLBACKS
		- Indicates the maximum number of logging callback functions can exit.

	ZT_MEM_GLOBAL_ARENA_STACK_SIZE
		- The size of the global memory arena stack.

	ZT_MEM_ARENA_LOG_DETAILS
		- Logs details about every single allocation.  Not recommended unless you're trying 
		  to find memory problems.

	ZT_MEM_ARENA_ZERO_NEW_MEMORY
		- Zeros out all allocations coming from memory arenas.  This is default in debug builds,
		  but absent in release for performance reasons.

 **************************************************************************************************

	What's with the name "Zero Tolerance?"
		I chose the name because my goal is to have a zero tolerance policy for slow, bloated
		software, slow compile times, and long development time.  I want this library to be
		fast in execution, fast in compile times and fast and easy to use.

	Special Thanks
		This library is inspired by the single file libraries by Sean Barrett.  Inspiration has
		also been drawn from Casey Muratori's Handmade Hero video series as well as Shawn
		McGrath's programming streams.

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

#	define ztReal32Max		3.402823466e+38F
#	define ztReal32Min		1.175494351e-38F
#	define ztReal32Epsilon	1.192092896e-07F

#	define ztReal64Max		1.7976931348623158e+308
#	define ztReal64Min		2.2250738585072014e-308
#	define ztReal64Epsilon	2.2204460492503131e-016

#	if !defined(_SIZE_T_DEFINED)
#		define _SIZE_T_DEFINED
#		if defined(ZT_WIN32)
			typedef unsigned int size_t;
#		else
			typedef unsigned long long size_t;
#		endif
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

#define ztInline		inline
#define ztInternal		static
#define ztPersistent	static
#define ztGlobal		static

#define ztKilobytes(kb)	((kb) * 1024LL)
#define ztMegabytes(mb)	(ztKilobytes(mb) * 1024LL)
#define ztGigabytes(gb)	(ztMegabytes(gb) * 1024LL)
#define ztTerabytes(tb)	(ztGigabytes(tb) * 1024LL)

#define ztBitAdd(var, flag)		((var) |= (flag))
#define ztBitRemove(var, flag)	((var) &= ~(flag))
#define ztBitIsSet(var, flag)	(((var) & (flag)) != 0)

#define ztMax(val1, val2) ( (val1) > (val2) ? (val1) : (val2) )
#define ztMin(val1, val2) ( (val1) < (val2) ? (val1) : (val2) )
#define ztClamp(val, min, max) ( val_min(max, (val_max(min, val))) )
#define ztAbs(val) ( (val) < 0 ? -(val) : (val) )
#define ztSwap(val1, val2) {auto temp = val1; val1 = val2; val2 = temp;}

#define ztReal32Eq(val1, val2) (ztAbs(val1 - val2) < ztReal32Epsilon)
#define ztReal64Eq(val1, val2) (ztAbs(val1 - val2) < ztReal64Epsilon)

// yes, shamelessly "borrowed" from Shawn McGrath
#define zt_fiz(end) for(int i = 0; i < (end); ++i)
#define zt_fjz(end) for(int j = 0; j < (end); ++j)
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

void zt_assert(bool condition, const char *condition_name, const char *file, int file_line);

enum ztLogMessageLevel_Enum
{
	ztLogMessageLevel_Fatal,
	ztLogMessageLevel_Critical,
	ztLogMessageLevel_Info,
	ztLogMessageLevel_Debug,
	ztLogMessageLevel_Verbose,

	ztLogMessageLevel_MAX,
};

void zt_logMessage(ztLogMessageLevel_Enum level, const char *message, ...);

void zt_logVerbose(const char *message, ...);
void zt_logDebug(const char *message, ...);
void zt_logInfo(const char *message, ...);
void zt_logCritical(const char *message, ...);
void zt_logFatal(const char *message, ...);

// add your own logging callback ... the message does not contain a newline by default
typedef void(*zt_logCallback_Func)(ztLogMessageLevel_Enum level, const char * message);
void zt_logAddCallback(zt_logCallback_Func callback, ztLogMessageLevel_Enum min_level);
void zt_logRemoveCallback(zt_logCallback_Func callback);

// memory functions
void zt_memSet(void *mem, i32 mem_len, byte value);
void zt_memCpy(void *dst, i32 dst_len, void *src, i32 src_len);

struct ztMemoryArena
{
	byte *memory;
	i32 total_size;
	i32 current_used;
	i32 peak_used;
	i32 alloc_cnt;
	i32 free_cnt;
	i32 freed_allocs;

	struct allocation
	{
		byte magic[3];
		void *start;
		i32 length;
		byte freed; // 0,1
		i32 alloc_idx;

		ztMemoryArena *arena;

		ztDebugOnly(const char *file);
		ztDebugOnly(int file_line);

		allocation* next;
	};

	allocation *latest;
	ztMemoryArena *owner;
};

ztMemoryArena *zt_memMakeArena(i32 total_size, ztMemoryArena *from = nullptr);
void zt_memFreeArena(ztMemoryArena *arena);

// arena can be null and if so, standard malloc/realloc/free will be used
void* zt_memAllocFromArena(ztMemoryArena *arena, i32 size);
void* zt_memAllocFromArena(ztMemoryArena *arena, i32 size, const char *file, int file_line);
void* zt_memRealloc(ztMemoryArena *arena, void* data, i32 size);
void zt_memFree(ztMemoryArena *arena, void *data);

#define zt_memAlloc(arena, size) zt_memAllocFromArena(arena, size, __FILE__, __LINE__)

void zt_memDumpArena(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level = ztLogMessageLevel_Debug); // logs details including unfreed allocations

// some systems will use the global arena stack to determine if it should use a memory arena
// note it's possible to push a null arena onto the stack to cause these systems to use malloc/free (or whatever default you set)

bool zt_memPushGlobalArena(ztMemoryArena *arena); // returns false if the stack is full, so check this
void zt_memPopGlobalArena(ztMemoryArena *arena);
ztMemoryArena* zt_memGetGlobalArena();

// by default, malloc and free are used when there are no overrides set
void zt_memSetDefaultMallocFree(void* (*malloc_func)(size_t), void(*free_func)(void*));

// be sure that the global arena stack is in the same state between calls to the following
void* zt_memAllocGlobalFull(i32 size, const char *file, int file_line);
void zt_memFreeGlobal(void* data);

#define zt_memAllocGlobal(size) zt_memAllocGlobalFull(size, __FILE__, __LINE__)

// string functions
#define zt_strPosNotFound	-1

bool zt_strEquals(const char *s1, const char *s2, bool test_case = true);
int zt_strLen(const char *s1);
int zt_strCmp(const char *s1, const char *s2);
int zt_striCmp(const char *s1, const char *s2);

int zt_strCpy(char *scopy, int scopy_len, const char *sfrom);
int zt_strCpy(char *scopy, int scopy_len, const char *sfrom, int sfrom_len);

i32 zt_strToInt(const char *s, i32 def, bool* success = nullptr);
i32 zt_strToInt(const char *s, int s_len, i32 def, bool* success = nullptr);
u32 zt_strToIntHex(const char *s, u32 def, bool* success = nullptr);
u32 zt_strToIntHex(const char *s, int s_len, u32 def, bool* success = nullptr);

r32 zt_strToReal32(const char *s, r32 def, bool* success = nullptr);
r32 zt_strToReal32(const char *s, int s_len, r32 def, bool* success = nullptr);
r64 zt_strToReal64(const char *s, r64 def, bool* success = nullptr);
r64 zt_strToReal64(const char *s, int s_len, r64 def, bool* success = nullptr);

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

const char *zt_strJumpToNextToken(const char *s); // any non-alphanumeric character breaks up tokens
const char *zt_strJumpToNextToken(const char *s, int s_len);

int zt_strGetNextTokenPos(const char *s);
int zt_strGetNextTokenPos(const char *s, int s_len);

const char *zt_strJumpToNextLine(const char *s);
const char *zt_strJumpToNextLine(const char *s, int s_len);

int zt_strGetNextLinePos(const char *s);
int zt_strGetNextLinePos(const char *s, int s_len);

enum ztStrTokenizeFlags_Enum
{
	ztStrTokenizeFlags_IncludeTokens  = (1<<0),
	ztStrTokenizeFlags_ProcessQuotes  = (1<<1),
	ztStrTokenizeFlags_KeepQuotes     = (1<<2),
	ztStrTokenizeFlags_TrimWhitespace = (1<<3),
};

struct ztToken
{
	i32 beg;
	i32 len;
};

// populates the given array of ztTokens with the parsed information
// if the given array isn't large enough, it populates as many as it cans and returns the required buffer size
// this allows for calling the function once with a null array to get the size, then allocating the required amount of memory before calling a second time

int zt_strTokenize(const char *s, const char *tokens, ztToken* results, int results_count, int32 flags = 0);
int zt_strTokenize(const char *s, int s_len, const char* tokens, ztToken* results, int results_count, int32 flags = 0);


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


ztInline void zt_assert(bool condition, const char *condition_name, const char *file, int file_line)
{
	if (!condition) {
		__asm { int 3 };
	}
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#if defined(ZT_TOOLS_IMPLEMENTATION)

// headers (strive to avoid including anything if possible)
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#if defined(ZT_COMPILER_MSVC)
#	include <windows.h>
#endif

// ------------------------------------------------------------------------------------------------

#ifndef ZT_MAX_LOG_CALLBACKS
#define ZT_MAX_LOG_CALLBACKS	8
#endif

ztInternal zt_logCallback_Func _zt_logCallbacks[ZT_MAX_LOG_CALLBACKS];
ztInternal ztLogMessageLevel_Enum _zt_logCallbacksMin[ZT_MAX_LOG_CALLBACKS];
ztInternal i32 _zt_logCallbacksCount = 0;

#if defined(ZT_COMPILER_MSVC)
#define _zt_var_args \
			va_list arg_ptr; \
			va_start(arg_ptr, message); \
			char buffer[1024 * 64]; \
			vsnprintf_s(buffer, ztElementsOf(buffer), message, arg_ptr);

#else
#	error "Unsupported compiler for zt_logMessage"
#endif

ztInternal
void _zt_logMessageRaw(ztLogMessageLevel_Enum level, const char *message)
{
#if defined(ZT_COMPILER_MSVC)
	OutputDebugStringA(message);
	OutputDebugStringA("\n");
#endif

	zt_fiz(_zt_logCallbacksCount) {
		if (_zt_logCallbacksMin[i] >= level) {
			_zt_logCallbacks[i](level, message);
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_logMessage(ztLogMessageLevel_Enum level, const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(level, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_logVerbose(const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(ztLogMessageLevel_Verbose, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_logDebug(const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(ztLogMessageLevel_Debug, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_logInfo(const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(ztLogMessageLevel_Info, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_logCritical(const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(ztLogMessageLevel_Critical, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_logFatal(const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(ztLogMessageLevel_Fatal, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_logAddCallback(zt_logCallback_Func callback, ztLogMessageLevel_Enum min_level)
{
	ztAssert(_zt_logCallbacksCount < ZT_MAX_LOG_CALLBACKS);

	int idx = _zt_logCallbacksCount++;
	_zt_logCallbacks[idx] = callback;
	_zt_logCallbacksMin[idx] = min_level;
}

// ------------------------------------------------------------------------------------------------

void zt_logRemoveCallback(zt_logCallback_Func callback)
{
	zt_fiz(_zt_logCallbacksCount) {
		if (_zt_logCallbacks[i] == callback) {
			for (int j = i; j < _zt_logCallbacksCount - 1; ++j) {
				_zt_logCallbacks[j] = _zt_logCallbacks[j + 1];
				_zt_logCallbacksMin[j] = _zt_logCallbacksMin[j + 1];
			}
			break;
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_memSet(void* mem, int32 mem_len, byte value)
{
	byte* bmem = (byte*)mem;
	zt_fiz(mem_len) {
		bmem[i] = value;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_memCpy(void* dst, int32 dst_len, void* src, int32 src_len)
{
	int max_idx = ztMin(dst_len, src_len);
	for (int i = 0; i < max_idx; ++i) {
		((byte*)dst)[i] = ((byte*)src)[i];
	}
}

// ------------------------------------------------------------------------------------------------

#if defined(ZT_MEM_ARENA_LOG_DETAILS)
#define zt_logMemory(...) zt_logVerbose(__VA_ARGS__)
#else
#define zt_logMemory(...)
#endif

// ------------------------------------------------------------------------------------------------

#if !defined(ZT_MEM_GLOBAL_ARENA_STACK_SIZE)
#define ZT_MEM_GLOBAL_ARENA_STACK_SIZE	64
#endif

ztInternal ztMemoryArena *_zt_memGlobalArenaStack[ZT_MEM_GLOBAL_ARENA_STACK_SIZE];
ztInternal i32 _zt_memGlobalArenaStackCount = 0;

ztInternal void* (*_zt_malloc)(size_t) = malloc;
ztInternal void(*_zt_free)(void*) = free;


ztMemoryArena *zt_memMakeArena(i32 total_size, ztMemoryArena *from)
{
	ztMemoryArena *arena = nullptr;
	if (from == nullptr) {
#if defined(ZT_COMPILER_MSVC)
		arena = (ztMemoryArena*)VirtualAlloc(0, total_size + sizeof(ztMemoryArena), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
		arena = malloc(total_size + sizeof(ztMemoryArena));
#endif
	}
	else {
		arena = (ztMemoryArena*)zt_memAlloc(from, total_size + sizeof(ztMemoryArena));
	}

	if (arena) {
		arena->memory = (byte*)(arena) + sizeof(ztMemoryArena);
		arena->total_size = total_size;
		arena->current_used = 0;
		arena->peak_used = 0;
		arena->alloc_cnt = 0;
		arena->free_cnt = 0;
		arena->latest = nullptr;
		arena->owner = from;
		arena->freed_allocs = 0;

		ztDebugOnly(zt_memSet(arena->memory, total_size, 0));
	}
	return arena;
}

// ------------------------------------------------------------------------------------------------

void zt_memFreeArena(ztMemoryArena *arena)
{
	if (arena == nullptr) {
		return;
	}
	if (arena->owner) {
		zt_memFree(arena->owner, arena);
	}
	else {
#if defined(ZT_COMPILER_MSVC)
		VirtualFree(arena, arena->total_size + sizeof(ztMemoryArena), MEM_DECOMMIT | MEM_RELEASE);
#else
		free(arena);
#endif

	}
}

// ------------------------------------------------------------------------------------------------

void* zt_memAllocFromArena(ztMemoryArena *arena, i32 bytes)
{
	if (bytes % 4 != 0) {
		bytes += 4 - (bytes % 4);	// align the memory to 4 byte chunks
	}

	if (arena->freed_allocs > 0) { // use pre-allocated memory if it exists before going to the end of the buffer
		auto *alloc = arena->latest;
		while (alloc) {
			if (alloc->freed == 1 && bytes <= alloc->length) {
				i32 remaining = alloc->length - (sizeof(ztMemoryArena::allocation) + bytes);
				if (remaining > sizeof(ztMemoryArena::allocation)) {
					ztMemoryArena::allocation *allocation = (ztMemoryArena::allocation *)((byte *)alloc->start + bytes);
					allocation->magic[0] = 'M';
					allocation->magic[1] = 'R';
					allocation->magic[2] = 'E';
					allocation->length = remaining - sizeof(ztMemoryArena::allocation);
					allocation->start = (byte *)allocation + sizeof(ztMemoryArena::allocation);
					allocation->freed = 1;
					allocation->alloc_idx = arena->alloc_cnt++;
					allocation->arena = arena;
					allocation->next = alloc->next;
					ztDebugOnly(allocation->file = nullptr);
					ztDebugOnly(allocation->file_line = 0);

					alloc->next = allocation;
					alloc->length = bytes;
				}

				arena->current_used += sizeof(ztMemoryArena::allocation) + bytes;
				arena->peak_used = ztMax(arena->peak_used, arena->current_used);

				alloc->freed = 0;
				return alloc->start;
			}
			alloc = alloc->next;
		}
	}

	byte* next = arena->latest ? (byte*)arena->latest->start + arena->latest->length : arena->memory;
	ztAssert((next - arena->memory) + (i32)sizeof(ztMemoryArena::allocation) + bytes <= arena->total_size);

	if ((next - arena->memory) + (i32)sizeof(ztMemoryArena::allocation) + bytes > arena->total_size) {
		zt_logCritical("zt_memAllocFromArena: Attempted to allocate more memory than available");
		return nullptr;
	}

	ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)next;
	allocation->magic[0] = 'M';
	allocation->magic[1] = 'R';
	allocation->magic[2] = 'E';
	allocation->length = bytes;
	allocation->freed = 0;
	allocation->next = arena->latest;
	allocation->start = (next + sizeof(ztMemoryArena::allocation));
	allocation->alloc_idx = arena->alloc_cnt++;
	allocation->arena = arena;

	ztDebugOnly(allocation->file = nullptr);
	ztDebugOnly(allocation->file_line = 0);

	arena->latest = allocation;

	arena->current_used += allocation->length + sizeof(ztMemoryArena::allocation);
	arena->peak_used = ztMax(arena->peak_used, arena->current_used);

	ztDebugOnly(zt_memSet(allocation->start, allocation->length, 0));

#if defined(ZT_MEM_ARENA_ZERO_NEW_MEMORY)
	ztReleaseOnly(zt_memSet(allocation->start, allocation->length, 0));
#endif

	zt_logMemory("memory (%s): allocated %d + %d bytes at location 0x%llx", chunk_name, allocation->length, sizeof(ztMemoryArena::allocation), (long long unsigned int)next);
	return (void*)allocation->start;

}

// ------------------------------------------------------------------------------------------------

void* zt_memAllocFromArena(ztMemoryArena *arena, i32 size, const char *file, int file_line)
{
	void* result = zt_memAllocFromArena(arena, size);
	if (result) {
		ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)(((byte*)result) - sizeof(ztMemoryArena::allocation));
		allocation->file = file;
		allocation->file_line = file_line;
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

void* zt_memRealloc(ztMemoryArena *arena, void* data, i32 size)
{
	if (data == nullptr) {
		return zt_memAllocFromArena(arena, size);
	}

	ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)(((byte*)data) - sizeof(ztMemoryArena::allocation));
	ztAssert(allocation->magic[0] == 'M' && allocation->magic[1] == 'R' && allocation->magic[2] == 'E');
	zt_logMemory("memory (%s): reallocating %d bytes of memory at location 0x%llx", chunk_name, bytes, (long long unsigned int)allocation);

	if (size <= allocation->length) {
		return data;
	}
	else {
		if (allocation == arena->latest) {
			ztAssert(((byte*)allocation->start - arena->memory) + size <= arena->total_size);
			if (((byte*)allocation->start - arena->memory) + size > arena->total_size) {
				zt_logCritical("realloc_from: Attempted to allocate more memory than available");
				return nullptr;
			}
			allocation->length = size;
			return data;
		}
		else {
			void* nmem = zt_memAllocFromArena(arena, size);
			if (nmem == nullptr) {
				return nmem;
			}
			zt_memCpy(nmem, size, data, ztMin(size, allocation->length));
			zt_memFree(allocation->arena, data);
			return nmem;
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_memFree(ztMemoryArena *arena, void *data)
{
	if (data == nullptr) {
		return;
	}

	ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)(((byte*)data) - sizeof(ztMemoryArena::allocation));
	ztAssert(allocation->magic[0] == 'M' && allocation->magic[1] == 'R' && allocation->magic[2] == 'E');
	zt_logMemory("memory (%s): freeing %d bytes of memory at location 0x%llx", chunk_name, allocation->length, (long long unsigned int)allocation);
	
	ztAssert(allocation->freed == 0);
	ztAssert(allocation >= (ztMemoryArena::allocation*)arena->memory && allocation <= (ztMemoryArena::allocation*)(arena->memory + arena->total_size));

	ztDebugOnly(zt_memSet((void*)allocation->start, 1, allocation->length));
	arena->current_used -= allocation->length + sizeof(ztMemoryArena::allocation);

	allocation->freed = 1;

	arena->free_cnt += 1;
	arena->freed_allocs += 1;

	while (arena->latest && arena->latest->freed) {
		arena->latest = arena->latest->next;
		arena->freed_allocs -= 1;
	}

	// consolidate any sequential allocations that might exist
	allocation = arena->latest;
	while (allocation) {
		if (allocation->freed == 1) {
			auto* next = allocation->next;
			while (next) {
				if (next->freed == 1) {
					allocation->length += next->length + sizeof(ztMemoryArena::allocation);
					allocation->next = next->next;
					arena->freed_allocs -= 1;
				}
				else break;
				next = next->next;
			}
		}
		allocation = allocation->next;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_memDumpArena(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level)
{
	if (arena->peak_used < 1024) {
		zt_logMessage(log_level, "memory (%s): Peak used: %.2f b", name, arena->peak_used / 1.0f);
	}
	else if (arena->peak_used < 1024 * 1024) {
		zt_logMessage(log_level, "memory (%s): Peak used: %.2f kb", name, arena->peak_used / 1024.0f);
	}
	else if (arena->peak_used < 1024 * 1024 * 1024) {
		zt_logMessage(log_level, "memory (%s): Peak used: %.2f mb", name, arena->peak_used / (1024.0f * 1024.0f));
	}
	else {
		zt_logMessage(log_level, "memory (%s): Peak used: %.2f gb", name, arena->peak_used / (1024.0f * 1024.0f * 1024.0f));
	}

	ztMemoryArena::allocation* alloc = arena->latest;
	while (alloc != nullptr) {
		if (alloc->freed == 0) {
			zt_logMessage(log_level, "memory (%s): unfreed memory at location 0x%llx (%d)", name, (uint64)alloc->start, alloc->alloc_idx);
			ztDebugOnly(zt_logMessage(log_level, "   file: %s (%d)", alloc->file, alloc->file_line));
		}
		alloc = alloc->next;
	}
	if (arena->alloc_cnt != arena->free_cnt) {
		zt_logMessage(log_level, "memory(%s): alloc/free count mismatch: %d/%d", name, arena->alloc_cnt, arena->free_cnt);
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_memPushGlobalArena(ztMemoryArena *arena)
{
	ztAssert(_zt_memGlobalArenaStackCount < ZT_MEM_GLOBAL_ARENA_STACK_SIZE);
	if (_zt_memGlobalArenaStackCount >= ZT_MEM_GLOBAL_ARENA_STACK_SIZE) {
		return false;
	}

	_zt_memGlobalArenaStack[_zt_memGlobalArenaStackCount++] = arena;
}

// ------------------------------------------------------------------------------------------------

void zt_memPopGlobalArena(ztMemoryArena *arena)
{
	ztAssert(_zt_memGlobalArenaStackCount > 0);
	_zt_memGlobalArenaStackCount -= 1;
}

// ------------------------------------------------------------------------------------------------

ztMemoryArena* zt_memGetGlobalArena()
{
	if (_zt_memGlobalArenaStackCount == 0) {
		return nullptr;
	}
	return _zt_memGlobalArenaStack[_zt_memGlobalArenaStackCount];
}

// ------------------------------------------------------------------------------------------------

void zt_memSetDefaultMallocFree(void* (*malloc_func)(size_t), void(*free_func)(void*))
{
	_zt_malloc = malloc_func;
	_zt_free = free_func;
}

// ------------------------------------------------------------------------------------------------

void* zt_memAllocGlobalFull(i32 size, const char *file, int file_line)
{
	ztMemoryArena* arena = zt_memGetGlobalArena();
	if (arena) {
		return zt_memAllocFromArena(arena, size, file, file_line);
	}
	else {
		return _zt_malloc(size);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_memFreeGlobal(void* data)
{
	ztMemoryArena* arena = zt_memGetGlobalArena();
	if (arena) {
		zt_memFree(arena, data);
	}
	else {
		_zt_free(data);
	}
}

// ------------------------------------------------------------------------------------------------

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

int zt_strCpy(char *scopy, int scopy_len, const char *sfrom)
{
	return zt_strCpy(scopy, scopy_len, sfrom, zt_strLen(sfrom));
}

// ------------------------------------------------------------------------------------------------

int zt_strCpy(char *scopy, int scopy_len, const char *sfrom, int sfrom_len)
{
	if (!scopy || scopy_len <= 0) {
		return 0;
	}
	if (!sfrom || sfrom_len <= 0) {
		scopy[0] = 0;
		return 0;
	}

	int max_idx = ztMin(scopy_len - 1, sfrom_len);
	zt_fiz(max_idx) {
		scopy[i] = sfrom[i];
	}
	scopy[max_idx] = 0;
	return max_idx;
}

// ------------------------------------------------------------------------------------------------

#define _zt_str_to_prepare_and_check \
	if (!s || s_len == 0) { \
		if (success) *success = false; \
		return def; \
	} \
	while (*s && (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')) { ++s; --s_len; }\
	for (int i = s_len - 1; i >= 0; --i) { \
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n') s_len -= 1; \
		else break; \
	} \
	if (s_len <= 0) { \
		if (success) *success = false; \
		return def; \
	}

// ------------------------------------------------------------------------------------------------

i32 zt_strToInt(const char *s, i32 def, bool* success)
{
	return zt_strToInt(s, zt_strLen(s), def, success);
}

// ------------------------------------------------------------------------------------------------

i32 zt_strToInt(const char *s, int s_len, i32 def, bool* success)
{
	_zt_str_to_prepare_and_check;

	zt_fiz(s_len) {
		if (s[i] < '0' || s[i] > '9') {
			if (s[i] != '-') {
				if (success) *success = false;
				return def;
			}
		}
	}

	if (success) *success = true;

	char buffer[128];
	zt_strCpy(buffer, ztElementsOf(buffer), s, s_len);

	return strtol(buffer, nullptr, 10);
}

// ------------------------------------------------------------------------------------------------

u32 zt_strToIntHex(const char *s, u32 def, bool* success)
{
	return zt_strToIntHex(s, zt_strLen(s), def, success);
}

// ------------------------------------------------------------------------------------------------

u32 zt_strToIntHex(const char *s, int s_len, u32 def, bool* success)
{
	_zt_str_to_prepare_and_check;

	zt_fiz(s_len) {
		if (s[i] < '0' || s[i] > '9') {
			if (s[i] < 'a' || s[i] > 'f') {
				if (s[i] < 'A' || s[i] > 'F') {
					if (s[i] != '-' && s[i] != 'x') {
						if (success) *success = false;
						return def;
					}
				}
			}
		}
	}
	if (success) *success = true;

	char buffer[128];
	zt_strCpy(buffer, ztElementsOf(buffer), s, s_len);

	return strtoul(buffer, nullptr, 16);
}

// ------------------------------------------------------------------------------------------------

r32 zt_strToReal32(const char *s, r32 def, bool* success)
{
	return zt_strToReal32(s, zt_strLen(s), def, success);
}

// ------------------------------------------------------------------------------------------------

r32 zt_strToReal32(const char *s, int s_len, r32 def, bool* success)
{
	_zt_str_to_prepare_and_check;

	char* end = nullptr;
	r32 result = strtof(s, &end);

	if (end == s) {
		if (success) *success = false;
		return def;
	}
	else {
		if (success) *success = true;
		return result;
	}
}

// ------------------------------------------------------------------------------------------------

r64 zt_strToReal64(const char *s, r64 def, bool* success)
{
	return zt_strToReal64(s, zt_strLen(s), def, success);
}

// ------------------------------------------------------------------------------------------------

r64 zt_strToReal64(const char *s, int s_len, r64 def, bool* success)
{
	_zt_str_to_prepare_and_check;

	char* end = nullptr;
	r64 result = strtod(s, &end);

	if (end == s) {
		if (success) *success = false;
		return def;
	}
	else {
		if (success) *success = true;
		return result;
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------

#undef _zt_str_to_prepare_and_check

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

const char *zt_strJumpToNextToken(const char *s)
{
	return zt_strJumpToNextToken(s, zt_strLen(s));
}

// ------------------------------------------------------------------------------------------------

const char *zt_strJumpToNextToken(const char *s, int s_len)
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

int zt_strGetNextTokenPos(const char *s)
{
	return zt_strGetNextTokenPos(s, zt_strLen(s));
}

// ------------------------------------------------------------------------------------------------

int zt_strGetNextTokenPos(const char *s, int s_len)
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

const char *zt_strJumpToNextLine(const char *s)
{
	return zt_strJumpToNextLine(s, zt_strLen(s));
}

// ------------------------------------------------------------------------------------------------

const char *zt_strJumpToNextLine(const char *s, int s_len)
{
	if (!s || s_len <= 0) return nullptr;

	for (int i = 1; i < s_len; ++i) {
		char ch = s[i];
		if (ch == '\n') {
			return s + (i + 1);
		}
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

int zt_strGetNextLinePos(const char *s)
{
	return zt_strGetNextLinePos(s, zt_strLen(s));
}

// ------------------------------------------------------------------------------------------------

int zt_strGetNextLinePos(const char *s, int s_len)
{
	if (!s || s_len <= 0) return zt_strPosNotFound;

	for (int i = 1; i < s_len; ++i) {
		char ch = s[i];
		if (ch == '\n') {
			return (i + 1);
		}
	}

	return zt_strPosNotFound;
}

// ------------------------------------------------------------------------------------------------

int zt_strTokenize(const char *s, const char *tokens, ztToken* results, int results_count, int32 flags)
{
	return zt_strTokenize(s, zt_strLen(s), tokens, results, results_count, flags);
}

// ------------------------------------------------------------------------------------------------

int zt_strTokenize(const char *s, int s_len, const char *tokens, ztToken* results, int results_count, int32 flags)
{
	if (!s || s_len == 0) return 0;

	int t_len = zt_strLen(tokens);
	if (t_len == 0) {
		if (results && results_count > 1) {
			results[0].beg = 0;
			results[0].len = s_len;
		}
		return 1;
	}

	bool include_tokens  = ztBitIsSet(flags, ztStrTokenizeFlags_IncludeTokens);
	bool process_quotes  = ztBitIsSet(flags, ztStrTokenizeFlags_ProcessQuotes);
	bool keep_quotes     = ztBitIsSet(flags, ztStrTokenizeFlags_KeepQuotes);
	bool trim_whitespace = ztBitIsSet(flags, ztStrTokenizeFlags_TrimWhitespace);

	bool in_quotes = false;
	int whitespace_run = 0;
	int t_idx = 0;

	ztToken* ctok = t_idx < results_count ? &results[t_idx] : nullptr;
	if (ctok) {
		ctok->beg = 0;
		ctok->len = 0;
	}

	zt_fiz(s_len) {
		if (in_quotes) {
			if (s[i] == '\"') {
				if (ctok) {
					if (keep_quotes)
						ctok->len += 1;
					if (ctok->len > 0)
						t_idx += 1;
				}
				else 
					t_idx += 1;

				ctok = t_idx < results_count ? &results[t_idx] : nullptr;
				if (ctok) {
					ctok->beg = i + 1;
					ctok->len = 0;
				}
				in_quotes = false;
			}
			else if (ctok)
				ctok->len += 1;
		}
		else {
			if (process_quotes && s[i] == '\"') {
				if (!keep_quotes) {
					if (!ctok || ctok->len != 0)
						t_idx += 1;

					ctok = t_idx < results_count ? &results[t_idx] : nullptr;
					if (ctok) {
						ctok->beg = i + (keep_quotes ? 0 : 1);
						ctok->len = keep_quotes ? 1 : 0;
					}
				}
				else if (ctok)
					ctok->len += 1;
				in_quotes = true;
			}
			else {
				bool is_token = false;
				for (int t = 0; t < t_len; ++t) {
					if (s[i] == tokens[t]) {
						is_token = true;

						if (ctok && trim_whitespace && whitespace_run) {
							ctok->len -= whitespace_run;
						}
						whitespace_run = 0;

						if (!ctok || ctok->len != 0)
							t_idx += 1;
						ctok = t_idx < results_count ? &results[t_idx] : nullptr;
						if (include_tokens) {
							if (ctok) {
								ctok->beg = i;
								ctok->len = 1;
							}
							t_idx += 1;
							ctok = t_idx < results_count ? &results[t_idx] : nullptr;
						}
						if (ctok) {
							ctok->beg = i + 1;
							ctok->len = 0;
						}
						break;
					}
				}

				if (!is_token) {
					if (trim_whitespace) {
						if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n')
							whitespace_run += 1;
						else
							whitespace_run = 0;
					}

					if (ctok) {
						if (!trim_whitespace || whitespace_run == 0)
							ctok->len += 1;
						else if (trim_whitespace && whitespace_run != 0 && ctok->len == 0)
							ctok->beg += 1;
						else
							ctok->len += 1;
					}
				}
			}
		}
	}

	if (ctok && ctok->len == 0)
		t_idx -= 1;

	return t_idx + 1;
}

// ------------------------------------------------------------------------------------------------

#if defined(ZT_TOOLS_PROVIDE_APP_LOOP)
 // ZT_TOOLS_APP_INIT
 // ZT_TOOLS_APP_LOOP
 // ZT_TOOLS_APP_CLEANUP

#if defined(ZT_PLATFORM_WIN32_CONSOLE) || defined(ZT_PLATFORM_WIN64_CONSOLE)
	int main( char **argv, int argc )
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