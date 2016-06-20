/**************************************************************************************************
 ** file: zt_tools.h v 0.00 (active initial development)
 **
 ** This library is in the public domain.  Do with it what you will.  No waranty implied.
 **
 ** There is no guarantee that this code works as intended.  Use it at your own risk.
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
   		- Removes the assert on zt_returnOnNull and zt_returnValOnNull macros.
   

 **************************************************************************************************

	Implimentation Options: (only used with ZT_TOOLS_IMPLIMENTATION #include)

	ZT_MAX_LOG_CALLBACKS
		- Indicates the maximum number of logging callback functions can exist.

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
#	define ZT_WINDOWS

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
#define zt_assert(cond)	zt_assert_raw(cond, #cond, __FILE__, __LINE__)
#define zt_elementsOf(native_array)	((int)(sizeof(native_array) / sizeof((native_array)[0])))

#if _DEBUG
#define zt_debugOnly(code)	code
#define zt_releaseOnly(code)
#else
#define zt_debugOnly(code)
#define zt_releaseOnly(code)	code
#endif

#define ztInline		inline
#define ztInternal		static
#define ztPersistent	static
#define ztGlobal		static

#define zt_kilobytes(kb)	((kb) * 1024LL)
#define zt_megabytes(mb)	(zt_kilobytes(mb) * 1024LL)
#define zt_gigabytes(gb)	(zt_megabytes(gb) * 1024LL)
#define zt_terabytes(tb)	(zt_gigabytes(tb) * 1024LL)

#define zt_bitAdd(var, flag)		((var) |= (flag))
#define zt_bitRemove(var, flag)	((var) &= ~(flag))
#define zt_bitIsSet(var, flag)	(((var) & (flag)) != 0)

#define zt_max(val1, val2) ( (val1) > (val2) ? (val1) : (val2) )
#define zt_min(val1, val2) ( (val1) < (val2) ? (val1) : (val2) )
#define zt_clamp(val, min, max) ( val_min(max, (val_max(min, val))) )
#define zt_abs(val) ( (val) < 0 ? -(val) : (val) )
#define zt_swap(val1, val2) {auto temp = val1; val1 = val2; val2 = temp;}

#define zt_real32Eq(val1, val2) (zt_abs(val1 - val2) < ztReal32Epsilon)
#define zt_real64Eq(val1, val2) (zt_abs(val1 - val2) < ztReal64Epsilon)

// yes, shamelessly "borrowed" from Shawn McGrath
#define zt_fiz(end) for(int i = 0; i < (end); ++i)
#define zt_fjz(end) for(int j = 0; j < (end); ++j)
#define zt_fkz(end) for(int k = 0; k < (end); ++k)

#define ztMathPi		 3.14159626f
#define ztMathPi2		 6.28319252f
#define ztMathPi180		 0.01745331f
#define ztMath180Pi		57.29571374f

#define zt_degreesToRadians(degrees) ((degrees) * ztMathPi180)
#define zt_radiansToDegrees(radians) ((radians) * ztMath180Pi)

#if !defined(ZT_TOOLS_RETURN_ON_NULLPTR_NO_ASSERT)
#	define zt_returnOnNull(ptr) if (ptr == nullptr) { zt_assert(false && "Null pointer encountered: " #ptr); return; }
#	define zt_returnValOnNull(ptr, retval) if (ptr == nullptr) { zt_assert(false && "Null pointer encountered: " #ptr); return retval; };
#else
#	define zt_returnOnNull(ptr) if (ptr == nullptr) { return; }
#	define zt_returnValOnNull(ptr, retval) if (ptr == nullptr) { return retval; };
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

struct ztVec2
{
	union {
		struct {
			r32 x;
			r32 y;
		};
		struct {
			r32 u;
			r32 v;
		};

		r32 values[2];
	};

	ztVec2(r32 _x = 0, r32 _y = 0) :x(_x), y(_y) {}

	ztVec2& operator+=(const ztVec2& v) { x += v.x; y += v.y; }
	ztVec2& operator-=(const ztVec2& v) { x -= v.x; y -= v.y; }
	ztVec2& operator*=(r32 v) { x *= v; y *= v; }

	bool operator==(const ztVec2& v) const { return zt_real32Eq(x, v.x) && zt_real32Eq(y, v.y); }
	bool operator!=(const ztVec2& v) const { return !zt_real32Eq(x, v.x) || !zt_real32Eq(y, v.y); }

	r32 length() const;
	r32 dot(const ztVec2& v) const;
	r32 cross(const ztVec2& v) const;
	r32 angle(const ztVec2& v) const;
	r32 distance(const ztVec2& v) const;

	static ztVec2 fromAngle(r32 angle);
	static ztVec2 lerp(const ztVec2& v1, const ztVec2& v2, r32 percent);
	static ztVec2 lerpHermite(const ztVec2& v1, const ztVec2& v2, r32 percent);
	static ztVec2 lerpSinerp(const ztVec2& v1, const ztVec2& v2, r32 percent);
	static ztVec2 lerpCoserp(const ztVec2& v1, const ztVec2& v2, r32 percent);
	static ztVec2 lerpBerp(const ztVec2& v1, const ztVec2& v2, r32 percent);

	static ztVec2 linearRemap(const ztVec2& val, const ztVec2& v1a, const ztVec2& v1b, const ztVec2& v2a, const ztVec2& v2b);

	void normalize();
	ztVec2 getNormal() const;

	void rotate(r32 angle);
	ztVec2 getRotated(r32 angle) const;

	static const ztVec2 zero;
	static const ztVec2 one;

#if defined(ZT_VEC2_EXTRAS)
	ZT_VEC2_EXTRAS	// use this to add conversions to and from your own classes
#endif
};

ztInline ztVec2 operator+(const ztVec2& v1, const ztVec2& v2);
ztInline ztVec2 operator-(const ztVec2& v1, const ztVec2& v2);
ztInline ztVec2 operator*(const ztVec2& v1, const ztVec2& v2);
ztInline ztVec2 operator*(const ztVec2& v1, r32 scale);

// ------------------------------------------------------------------------------------------------

struct ztVec3
{
	union {
		struct {
			r32 x;
			r32 y;
			r32 z;
		};

		struct {
			r32 r;
			r32 g;
			r32 b;
		};

		struct {
			ztVec2 xy;
			r32 z;
		};

		r32 values[3];
	};

	ztVec3(r32 _x = 0, r32 _y = 0, r32 _z = 0) :x(_x), y(_y), z(_z) {}
	ztVec3(const ztVec2& vec2, r32 _z = 0) : x(vec2.x), y(vec2.y), z(_z) {}

	ztVec3& operator+=(const ztVec3& v) { x += v.x; y += v.y; z += v.z; }
	ztVec3& operator-=(const ztVec3& v) { x -= v.x; y -= v.y; z -= v.z; }
	ztVec3& operator*=(r32 v) { x *= v; y *= v; z *= v; }
	ztVec3& operator*=(const ztVec3& v) { x *= v.x; y *= v.y; z *= v.z; }

	bool operator==(const ztVec3& v) const { return zt_real32Eq(x, v.x) && zt_real32Eq(y, v.y) && zt_real32Eq(z, v.z); }
	bool operator!=(const ztVec3& v) const { return !zt_real32Eq(x, v.x) || !zt_real32Eq(y, v.y) || !zt_real32Eq(z, v.z); }

	r32 length() const;
	r32 dot(const ztVec3& v) const;
	r32 angle(const ztVec3& v) const;
	r32 distance(const ztVec3& v) const;
	r32 multInner(const ztVec3& v) const;
	ztVec3 cross(const ztVec3& v) const;

	static ztVec3 lerp(const ztVec3& v1, const ztVec3& v2, r32 percent);
	static ztVec3 lerpHermite(const ztVec3& v1, const ztVec3& v2, r32 percent);
	static ztVec3 lerpSinerp(const ztVec3& v1, const ztVec3& v2, r32 percent);
	static ztVec3 lerpCoserp(const ztVec3& v1, const ztVec3& v2, r32 percent);
	static ztVec3 lerpBerp(const ztVec3& v1, const ztVec3& v2, r32 percent);

	static ztVec3 linearRemap(const ztVec3& val, const ztVec3& v1a, const ztVec3& v1b, const ztVec3& v2a, const ztVec3& v2b);

	void normalize();
	ztVec3 getNormal() const;

	static const ztVec3 zero;
	static const ztVec3 one;

#if defined(ZT_VEC3_EXTRAS)
	ZT_VEC3_EXTRAS	// use this to add conversions to and from your own classes
#endif
};

ztInline ztVec3 operator+(const ztVec3& v1, const ztVec3& v2);
ztInline ztVec3 operator-(const ztVec3& v1, const ztVec3& v2);
ztInline ztVec3 operator*(const ztVec3& v1, const ztVec3& v2);
ztInline ztVec3 operator*(const ztVec3& v1, r32 scale);

// ------------------------------------------------------------------------------------------------

struct ztVec4
{
	union {
		struct {
			r32 x;
			r32 y;
			r32 z;
			r32 w;
		};

		struct {
			r32 r;
			r32 g;
			r32 b;
			r32 a;
		};

		struct {
			ztVec2 xy;
			r32 zw;
		};

		struct {
			ztVec3 xyz;
			r32 w;
		};

		struct {
			ztVec3 rgb;
			r32 a;
		};

		r32 values[4];
	};

	ztVec4(r32 _x = 0, r32 _y = 0, r32 _z = 0, r32 _w = 0) :x(_x), y(_y), z(_z), w(_w) {}
	ztVec4(const ztVec2& vec2a, const ztVec2& vec2b) : x(vec2a.x), y(vec2a.y), z(vec2b.x), w(vec2b.y) {}
	ztVec4(const ztVec3& vec3, r32 _w) : x(vec3.x), y(vec3.y), z(vec3.z), w(_w) {}

	ztVec4& operator+=(const ztVec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; }
	ztVec4& operator-=(const ztVec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; }
	ztVec4& operator*=(r32 v) { x *= v; y *= v; z *= v; w *= v; }
	ztVec4& operator*=(const ztVec4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; }

	bool operator==(const ztVec4& v) const { return zt_real32Eq(x, v.x) && zt_real32Eq(y, v.y) && zt_real32Eq(z, v.z) && zt_real32Eq(w, v.w); }
	bool operator!=(const ztVec4& v) const { return !zt_real32Eq(x, v.x) || !zt_real32Eq(y, v.y) || !zt_real32Eq(z, v.z) || !zt_real32Eq(w, v.w); }

	static ztVec4 lerp(const ztVec4& v1, const ztVec4& v2, r32 percent);
	static ztVec4 lerpHermite(const ztVec4& v1, const ztVec4& v2, r32 percent);
	static ztVec4 lerpSinerp(const ztVec4& v1, const ztVec4& v2, r32 percent);
	static ztVec4 lerpCoserp(const ztVec4& v1, const ztVec4& v2, r32 percent);
	static ztVec4 lerpBerp(const ztVec4& v1, const ztVec4& v2, r32 percent);

	static ztVec4 linearRemap(const ztVec4& val, const ztVec4& v1a, const ztVec4& v1b, const ztVec4& v2a, const ztVec4& v2b);

	void normalize();
	ztVec3 getNormal() const;

	static const ztVec4 zero;
	static const ztVec4 one;

#if defined(ZT_VEC4_EXTRAS)
	ZT_VEC4_EXTRAS	// use this to add conversions to and from your own classes
#endif
};

ztInline ztVec4 operator+(const ztVec4& v1, const ztVec4& v2);
ztInline ztVec4 operator-(const ztVec4& v1, const ztVec4& v2);
ztInline ztVec4 operator*(const ztVec4& v1, const ztVec4& v2);
ztInline ztVec4 operator*(const ztVec4& v1, r32 scale);

typedef ztVec4 ztColor;
#define ztColour ztColor;	// pick your favorite (favourite?)


// inlined functions ==============================================================================

bool zt_isPow2(i32 number);
i32 zt_nextPow2(i32 number);

i32 zt_convertToi32Ceil(r32 number);
i32 zt_convertToi32Floor(r32 number);

r32 zt_lerp(r32 v1, r32 v2, r32 percent);
r32 zt_unlerp(r32 v1, r32 v2, r32 value);

r32 zt_lerpHermite(r32 v1, r32 v2, r32 percent);
r32 zt_lerpSinerp(r32 v1, r32 v2, r32 percent);
r32 zt_lerpCoserp(r32 v1, r32 v2, r32 percent);
r32 zt_lerpBerp(r32 v1, r32 v2, r32 percent, r32 power = 2.5f);
r32 zt_lerpCircle(r32 ang1, r32 ang2, r32 percent);

r32 zt_linearRemap(r32 val, r32 v1a, r32 v1b, r32 v2a, r32 v2b);
r32 zt_normalize(r32 val, r32 min, r32 max);
r32 zt_approach(r32 var, r32 appr, r32 by);

void zt_assert_raw(bool condition, const char *condition_name, const char *file, int file_line);

// they are inlined below
// ------------------------------------------------------------------------------------------------

// functions ======================================================================================

// logging
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

// ------------------------------------------------------------------------------------------------

// memory functions
void zt_memSet(void *mem, i32 mem_len, byte value);
void zt_memCpy(void *dst, i32 dst_len, const void *src, i32 src_len);
int  zt_memCmp(const void *one, const void *two, i32 size);

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

		zt_debugOnly(const char *file);
		zt_debugOnly(int file_line);

		allocation* next;
	};

	allocation *latest;
	ztMemoryArena *owner;
};

ztMemoryArena *zt_memMakeArena(i32 total_size, ztMemoryArena *from = nullptr);
void zt_memFreeArena(ztMemoryArena *arena);

// arena can be null and if so, standard malloc/realloc/free will be used
void *zt_memAllocFromArena(ztMemoryArena *arena, i32 size);
void *zt_memAllocFromArena(ztMemoryArena *arena, i32 size, const char *file, int file_line);
void *zt_memRealloc(ztMemoryArena *arena, void *data, i32 size);
void zt_memFree(ztMemoryArena *arena, void *data);

#define zt_memAlloc(arena, size) zt_memAllocFromArena(arena, size, __FILE__, __LINE__)

void zt_memDumpArena(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level = ztLogMessageLevel_Debug); // logs details including unfreed allocations

// some systems will use the global arena stack to determine if it should use a memory arena
// note it's possible to push a null arena onto the stack to cause these systems to use malloc/free (or whatever default you set)

bool zt_memPushGlobalArena(ztMemoryArena *arena); // returns false if the stack is full, so check this
void zt_memPopGlobalArena();
ztMemoryArena* zt_memGetGlobalArena();

// by default, malloc and free are used when there are no overrides set
void zt_memSetDefaultMallocFree(void *(*malloc_func)(size_t), void(*free_func)(void*));

// be sure that the global arena stack is in the same state between calls to the following
void *zt_memAllocGlobalFull(i32 size, const char *file, int file_line);
void zt_memFreeGlobal(void *data);

#define zt_memAllocGlobal(size) zt_memAllocGlobalFull(size, __FILE__, __LINE__)

#define zt_malloc_struct(type)				(type *)zt_memAllocGlobalFull(sizeof(type), __FILE__, __LINE__)
#define zt_malloc_struct_array(type, size)	(type *)zt_memAllocGlobalFull(sizeof(type) * (size), __FILE__, __LINE__)

#define zt_malloc_struct_arena(type, arena)				(type *)zt_memAllocFromArena(arena, sizeof(type), __FILE__, __LINE__)
#define zt_malloc_struct_array_arena(type, size, arena)	(type *)zt_memAllocFromArena(arena, sizeof(type) * (size), __FILE__, __LINE__)

#define zt_free(memory)	zt_memFree(zt_memGetGlobalArena(), memory)

// ------------------------------------------------------------------------------------------------

// math functions
r32 zt_sin(r32 x);
r32 zt_cos(r32 y);
r32 zt_acos(r32 y);
r32 zt_atan2(r32 x, r32 y);
r32 zt_sqrt(r32 v);
r32 zt_pow(r32 v, r32 p);

// ------------------------------------------------------------------------------------------------

// string functions
#define ztStrPosNotFound	-1

#define zt_strMakePrintf(varname, varsize, format, ...)	char varname[varsize] = {0}; zt_strPrintf(varname, varsize, format, __VA_ARGS__);

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

u32 zt_strHash(const char *s);

const char *zt_strFind(const char *haystack, const char *needle);
const char *zt_strFind(const char *haystack, const char *needle, int needle_len);
const char *zt_strFind(const char *haystack, int haystack_len, const char *needle, int needle_len);
int zt_strFindPos(const char *haystack, const char *needle);
int zt_strFindPos(const char *haystack, const char *needle, int needle_len);
int zt_strFindPos(const char *haystack, int haystack_len, const char *needle, int needle_len);

const char *zt_strFindLast(const char *haystack, const char *needle);
const char *zt_strFindLast(const char *haystack, const char *needle, int needle_len);
const char *zt_strFindLast(const char *haystack, int haystack_len, const char *needle, int needle_len);
int zt_strFindLastPos(const char *haystack, const char *needle);
int zt_strFindLastPos(const char *haystack, const char *needle, int needle_len);
int zt_strFindLastPos(const char *haystack, int haystack_len, const char *needle, int needle_len);

const char *zt_striFind(const char *haystack, const char *needle);
const char *zt_striFind(const char *haystack, const char *needle, int needle_len);
const char *zt_striFind(const char *haystack, int haystack_len, const char *needle, int needle_len);
int zt_striFindPos(const char *haystack, const char *needle);
int zt_striFindPos(const char *haystack, const char *needle, int needle_len);
int zt_striFindPos(const char *haystack, int haystack_len, const char *needle, int needle_len);

const char *zt_striFindLast(const char *haystack, const char *needle);
const char *zt_striFindLast(const char *haystack, const char *needle, int needle_len);
const char *zt_striFindLast(const char *haystack, int haystack_len, const char *needle, int needle_len);
int zt_striFindLastPos(const char *haystack, const char *needle);
int zt_striFindLastPos(const char *haystack, const char *needle, int needle_len);
int zt_striFindLastPos(const char *haystack, int haystack_len, const char *needle, int needle_len);

bool zt_strStartsWith(const char *s, const char *starts_with);
bool zt_strStartsWith(const char *s, int s_len, const char *starts_with, int sw_len);
bool zt_strEndsWith(const char *s, const char *ends_with);
bool zt_strEndsWith(const char *s, int s_len, const char *ends_with, int ew_len);

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
int zt_strTokenize(const char *s, int s_len, const char *tokens, ztToken* results, int results_count, int32 flags = 0);

int zt_strPrintf(char *buffer, int buffer_size, const char *format, ...);

int zt_strBytesToString(char *buffer, int buffer_size, i32 bytes);
int zt_strNumberToString(char *buffer, int buffer_size, i64 number);

// ------------------------------------------------------------------------------------------------

// file operations
enum ztFileOpenMethod_Enum
{
	ztFileOpenMethod_Closed,
	ztFileOpenMethod_ReadOnly,
	ztFileOpenMethod_WriteOver,
	ztFileOpenMethod_WriteAppend,

	ztFileOpenMethod_MAX,
};


struct ztFile
{
	ztFileOpenMethod_Enum open_method;
	i32 size;

	char *full_name; // full file name, path and file with extension

#if defined(ZT_WINDOWS)
	i32 win_file_handle; // HFILE
	i32 win_read_pos;
#else
#	error "ztFile needs an implementation for this platform"
#endif

	ztMemoryArena* arena;
};

#define ztFileMaxPath	1024 * 4	// handy constant for path sizes on the stack

#if defined(ZT_WINDOWS)
#define ztFilePathSeparator	'\\'
#else
#define ztFilePathSeparator '/'
#endif

bool zt_fileOpen(ztFile *file, const char *file_name, ztFileOpenMethod_Enum file_open_method, ztMemoryArena *arena = zt_memGetGlobalArena());
void zt_fileClose(ztFile *file);

i32 zt_fileGetReadPos(ztFile *file);
bool zt_fileSetReadPos(ztFile *file, i32 pos);

// returns length of string, or -1 in case of error
i32 zt_fileGetFullPath(ztFile *file, char *buffer, int buffer_size);	// full path only, file name not included
i32 zt_fileGetFileName(ztFile *file, char *buffer, int buffer_size);	// file name only, no path details
i32 zt_fileGetFileExt(ztFile *file, char *buffer, int buffer_size);		// file extension only

i32 zt_fileGetFullPath(const char *file_name, char *buffer, int buffer_size);	// full path only, file name not included
i32 zt_fileGetFileName(const char *file_name, char *buffer, int buffer_size);	// file name only, no path details
i32 zt_fileGetFileExt(const char *file_name, char *buffer, int buffer_size);		// file extension only

i32 zt_fileGetAppBin(char *buffer, int buffer_size);
i32 zt_fileGetAppPath(char *buffer, int buffer_size);
i32 zt_fileGetUserPath(char *buffer, int buffer_size, char *app_name);
i32 zt_fileGetCurrentPath(char *buffer, int buffer_size);

bool zt_fileExists(const char *file_name);
bool zt_fileDelete(const char *file_name);
bool zt_fileCopy(const char *orig_file, const char *new_file);
bool zt_fileRename(const char *orig_file, const char *new_file);

i32 zt_fileRead(ztFile *file, void *buffer, i32 buffer_size);
ztInline bool zt_fileRead(ztFile *file, i8 *value)		{ return sizeof(*value) == zt_fileRead(file, value, sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, i16 *value)		{ return sizeof(*value) == zt_fileRead(file, value, sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, i32 *value)		{ return sizeof(*value) == zt_fileRead(file, value, sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, i64 *value)		{ return sizeof(*value) == zt_fileRead(file, value, sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, u8 *value)		{ return sizeof(*value) == zt_fileRead(file, value, sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, u16 *value)		{ return sizeof(*value) == zt_fileRead(file, value, sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, u32 *value)		{ return sizeof(*value) == zt_fileRead(file, value, sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, u64 *value)		{ return sizeof(*value) == zt_fileRead(file, value, sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, r32 *value)		{ return sizeof(*value) == zt_fileRead(file, value, sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, r64 *value)		{ return sizeof(*value) == zt_fileRead(file, value, sizeof(*value)); }

i32 zt_fileWrite(ztFile *file, void *buffer, i32 buffer_size);
ztInline bool zt_fileWrite(ztFile *file, i8 value)		{ return sizeof(value) == zt_fileWrite(file, &value, sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, i16 value)		{ return sizeof(value) == zt_fileWrite(file, &value, sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, i32 value)		{ return sizeof(value) == zt_fileWrite(file, &value, sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, i64 value)		{ return sizeof(value) == zt_fileWrite(file, &value, sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, u8 value)		{ return sizeof(value) == zt_fileWrite(file, &value, sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, u16 value)		{ return sizeof(value) == zt_fileWrite(file, &value, sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, u32 value)		{ return sizeof(value) == zt_fileWrite(file, &value, sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, u64 value)		{ return sizeof(value) == zt_fileWrite(file, &value, sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, r32 value)		{ return sizeof(value) == zt_fileWrite(file, &value, sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, r64 value)		{ return sizeof(value) == zt_fileWrite(file, &value, sizeof(value)); }

void zt_fileFlush(ztFile *file);

void *zt_readEntireFile(const char *file_name, i32 *file_size, ztMemoryArena *arena = zt_memGetGlobalArena());
i32 zt_readEntireFile(const char *file_name, void *buffer, i32 buffer_size);
i32 zt_writeEntireFile(const char *file_name, void *data, i32 data_size, ztMemoryArena *arena = zt_memGetGlobalArena());

// ------------------------------------------------------------------------------------------------

// serialization

// This serializer allows for storage formats to change without completely breaking old versions and to allow for new code
// to read old formats.  The way this is accomplished is through groups.  Basically, think of your data as heirarchical.  When
// a new section of data is written, it should be in a group.  When new data needs to be stored, it's added at the end of the
// group.  When reading back from an old file that doesn't have the new data, when the read is called, the serializer will see
// that there's a group end and will just return so the default value is used.  An example:
//
// // original code:
// zt_serialGroupPush(serial);
//     zt_serialWrite(serial, my_var->val1);
//     zt_serialWrite(serial, my_var->val2);
// zt_serialGroupPop(serial);
//
// zt_serialWrite(serial, other_var->val1);
//
// // new read code:
// zt_serialGroupPush(serial);
//     zt_serialRead(serial, &my_var->val1);
//     zt_serialRead(serial, &my_var->val2);
//     zt_serialRead(serial, &my_var->val3); // if reading the old format that didn't have this field, my_var->val3 will remain unchanged
// zt_serialGroupPop(serial);
//
// zt_serialRead(serial, &other_var->val1); // works as expected, both with new formats and old formats
//
// If you add a field between the writing of my_var->val1 and my_var->val2, you will break old formats.  You can do this, but you
// will need to read the serial->version number in order to determine how to read your data.
//
// This serializer also contains data integrity checks.  When writing data to the file, it calculates a checksum for the data.  When
// writing is complete, the checksum is appended to the end of the file.  When loading the file, this checksum is read and the data
// is checked.  If this checksum doesn't add up, the zt_serialMakeReader call will fail and the serial->mode variable will be set to
// ztSerialMode_Corrupt.


enum ztSerialMode_Enum
{
	ztSerialMode_Closed,
	ztSerialMode_Reading,
	ztSerialMode_Writing,
	ztSerialMode_Corrupt,

	ztSerialMode_MAX,
};


#define ztSerialIdentifierMaxSize	128

struct ztSerial
{
	ztSerialMode_Enum mode;
	ztFile file;
	bool close_file;

	void *file_data;
	i32 file_data_size;

	char identifier[ztSerialIdentifierMaxSize];
	i32 version;

	i32 group_level;
	i8 next_entry;

	i16 _checksum1, _checksum2;
};

bool zt_serialMakeWriter(ztSerial *serial, const char *file_name, const char *identifier, i32 version);
bool zt_serialMakeWriter(ztSerial *serial, ztFile *file, const char *identifier, i32 version);

// if opening a reader fails, check the mode in the ztSerial instance.  if it's ztSerialMode_Corrupt, then the file's checksum did not match
bool zt_serialMakeReader(ztSerial *serial, const char *file_name, const char *identifier);
bool zt_serialMakeReader(ztSerial *serial, void *data, i32 data_size, const char *identifier);
bool zt_serialMakeReader(ztSerial *serial, ztFile *file, const char *identifier);

void zt_serialClose(ztSerial *serial);

bool zt_serialGroupPush(ztSerial *serial);
bool zt_serialGroupPop(ztSerial *serial);

bool zt_serialWrite(ztSerial *serial, i8 value);
bool zt_serialWrite(ztSerial *serial, i16 value);
bool zt_serialWrite(ztSerial *serial, i32 value);
bool zt_serialWrite(ztSerial *serial, i64 value);
bool zt_serialWrite(ztSerial *serial, u8 value);
bool zt_serialWrite(ztSerial *serial, u16 value);
bool zt_serialWrite(ztSerial *serial, u32 value);
bool zt_serialWrite(ztSerial *serial, u64 value);
bool zt_serialWrite(ztSerial *serial, r32 value);
bool zt_serialWrite(ztSerial *serial, r64 value);
bool zt_serialWrite(ztSerial *serial, bool value);
bool zt_serialWrite(ztSerial *serial, const char *value, i32 value_len);
bool zt_serialWrite(ztSerial *serial, void *value, i32 value_len);

bool zt_serialRead(ztSerial *serial, i8 *value);
bool zt_serialRead(ztSerial *serial, i16 *value);
bool zt_serialRead(ztSerial *serial, i32 *value);
bool zt_serialRead(ztSerial *serial, i64 *value);
bool zt_serialRead(ztSerial *serial, u8 *value);
bool zt_serialRead(ztSerial *serial, u16 *value);
bool zt_serialRead(ztSerial *serial, u32 *value);
bool zt_serialRead(ztSerial *serial, u64 *value);
bool zt_serialRead(ztSerial *serial, r32 *value);
bool zt_serialRead(ztSerial *serial, r64 *value);
bool zt_serialRead(ztSerial *serial, bool *value);
bool zt_serialRead(ztSerial *serial, char *value, i32 value_len, i32 *read_len);
bool zt_serialRead(ztSerial *serial, void *value, i32 value_len, i32 *read_len);


// ------------------------------------------------------------------------------------------------
// random numbers

#define ztRandom_MTLen	624

struct ztRandom
{
	i32 mt_idx;
	i32 mt_buffer[ztRandom_MTLen];
};

void zt_randomInit(ztRandom *random, i32 seed);

i32 zt_randomInt(ztRandom *random, i32 min, i32 max);
r32 zt_randomVal(ztRandom *random); // between 0 and 1
r32 zt_randomVal(ztRandom *random, r32 min, r32 max);


// ------------------------------------------------------------------------------------------------
// configuration files

// these are really slow
i32 zt_iniFileGetValue(const char *ini_file, const char *section, const char *key, const char* dflt, char* buffer, i32 buffer_size);
i32 zt_iniFileGetValue(const char *ini_file, const char *section, const char *key, i32 dflt);
r32 zt_iniFileGetValue(const char *ini_file, const char *section, const char *key, r32 dflt);
bool zt_iniFileSetValue(const char *ini_file, const char *section, const char *key, const char *value);



// ------------------------------------------------------------------------------------------------
// command line

bool zt_cmdHasArg(const char** argv, int argc, const char* arg_short, const char* arg_long);
bool zt_cmdGetArg(const char** argv, int argc, const char* arg_short, const char* arg_long, char* buffer, int buffer_size);


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


ztInline bool zt_isPow2(i32 number)
{
	return ((number != 0) && ((number & (~number + 1)) == number));
}

// ------------------------------------------------------------------------------------------------

ztInline i32 zt_nextPow2(i32 number)
{
	i32 nval = 2;
	while (nval < number) nval *= 2;
	return nval;
}

// ------------------------------------------------------------------------------------------------

ztInline i32 zt_convertToi32Ceil(r32 number)
{
	return (int32)(number + (number > 0 ? 0.5f : -0.5f));
}

// ------------------------------------------------------------------------------------------------

ztInline i32 zt_convertToi32Floor(r32 number)
{
	return (int32)(number);
}

// ------------------------------------------------------------------------------------------------

ztInline r32 zt_lerp(r32 v1, r32 v2, r32 percent)
{
	return v1 + ((v2 - v1) * percent);
}

// ------------------------------------------------------------------------------------------------

ztInline r32 zt_unlerp(r32 v1, r32 v2, r32 value)
{
	return (v2 - v1) == 0 ? 0 : (value - v1) / (v2 - v1);
}

// ------------------------------------------------------------------------------------------------

ztInline r32 zt_lerpHermite(r32 v1, r32 v2, r32 percent)
{
	return zt_lerp(v1, v2, percent * percent * (3.0f - 2.0f * percent));
}

// ------------------------------------------------------------------------------------------------

ztInline r32 zt_lerpSinerp(r32 v1, r32 v2, r32 percent)
{
	return zt_lerp(v1, v2, zt_sin(percent * ztMathPi * 0.5f));
}

// ------------------------------------------------------------------------------------------------

ztInline r32 zt_lerpCoserp(r32 v1, r32 v2, r32 percent)
{
	return zt_lerp(v1, v2, 1.0f - zt_cos(percent * ztMathPi * 0.5f));
}

// ------------------------------------------------------------------------------------------------

ztInline r32 zt_lerpBerp(r32 v1, r32 v2, r32 percent, r32 power)
{
	return zt_lerp(v1, v2, zt_sin(percent * ztMathPi * (0.2f + power * percent * percent * percent)) * zt_pow(1.0f - percent, 2.2f) + percent) * (1.0f + (1.2f * (1.0f - percent)));
}

// ------------------------------------------------------------------------------------------------

ztInline r32 zt_lerpCircle(r32 ang1, r32 ang2, r32 percent)
{
	r32 min_ang = 0.0f;
	r32 max_ang = 360.0f;
	r32 half = zt_abs((max_ang - min_ang) / 2.0f); //half the distance between min and max

	r32 retval;
	r32 diff;

	if ((ang2 - ang1) < -half){
		diff = ((max_ang - ang1) + ang2) * percent;
		retval = ang1 + diff;
	}
	else if ((ang2 - ang1) > half){
		diff = -((max_ang - ang2) + ang1) * percent;
		retval = ang1 + diff;
	}
	else retval = ang1 + (ang2 - ang1) * percent;

	return retval;
}

// ------------------------------------------------------------------------------------------------

ztInline r32 zt_linearRemap(r32 val, r32 v1a, r32 v1b, r32 v2a, r32 v2b)
{
	return zt_lerp(v2a, v2b, zt_unlerp(v1a, v1b, val));
}

// ------------------------------------------------------------------------------------------------

ztInline r32 zt_normalize(r32 val, r32 min, r32 max)
{
	return (val - min) / (max - min);
}

// ------------------------------------------------------------------------------------------------

ztInline r32 zt_approach(r32 var, r32 appr, r32 by)
{
	if (var >= var) 
		return zt_min(var + by, appr);

	return zt_max(var - by, appr);
}

// ------------------------------------------------------------------------------------------------

ztInline void zt_assert_raw(bool condition, const char *condition_name, const char *file, int file_line)
{
	if (!condition) {
		zt_logCritical("assert failed: '%s' in file %s (%d)", condition_name, file, file_line);
		zt_debugOnly(__asm { int 3 });
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInline r32 ztVec2::length() const
{
	return zt_sqrt(x * x + y * y);
}

// ------------------------------------------------------------------------------------------------

ztInline r32 ztVec2::dot(const ztVec2& v) const
{
	return x * v.x + y * v.y;
}

// ------------------------------------------------------------------------------------------------

ztInline r32 ztVec2::cross(const ztVec2& v) const
{
	return x * v.x + y * v.y;
}

// ------------------------------------------------------------------------------------------------

ztInline r32 ztVec2::angle(const ztVec2& v) const
{
	return zt_radiansToDegrees(zt_atan2(v.y - y, v.x - x));
}

// ------------------------------------------------------------------------------------------------

ztInline r32 ztVec2::distance(const ztVec2& v) const
{
	return zt_sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec2 ztVec2::fromAngle(r32 angle)
{
	return ztVec2(zt_cos(angle), zt_sin(angle));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec2 ztVec2::lerp(const ztVec2& v1, const ztVec2& v2, r32 percent)
{
	return ztVec2(v1.x + ((v2.x - v1.x) * percent), v1.y + ((v2.y - v1.y) * percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec2 ztVec2::lerpHermite(const ztVec2& v1, const ztVec2& v2, r32 percent)
{
	return ztVec2(zt_lerpHermite(v1.x, v2.x, percent), zt_lerpHermite(v1.y, v2.y, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec2 ztVec2::lerpSinerp(const ztVec2& v1, const ztVec2& v2, r32 percent)
{
	return ztVec2(zt_lerpSinerp(v1.x, v2.x, percent), zt_lerpSinerp(v1.y, v2.y, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec2 ztVec2::lerpCoserp(const ztVec2& v1, const ztVec2& v2, r32 percent)
{
	return ztVec2(zt_lerpCoserp(v1.x, v2.x, percent), zt_lerpCoserp(v1.y, v2.y, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec2 ztVec2::lerpBerp(const ztVec2& v1, const ztVec2& v2, r32 percent)
{
	return ztVec2(zt_lerpBerp(v1.x, v2.x, percent), zt_lerpBerp(v1.y, v2.y, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec2 ztVec2::linearRemap(const ztVec2& val, const ztVec2& v1a, const ztVec2& v1b, const ztVec2& v2a, const ztVec2& v2b)
{
	return ztVec2(zt_lerp(v2a.x, v2b.x, zt_unlerp(v1a.x, v1b.x, val.x)), zt_lerp(v2a.y, v2b.y, zt_unlerp(v1a.y, v1b.y, val.y)));
}

// ------------------------------------------------------------------------------------------------

ztInline void ztVec2::normalize()
{
	r32 len = length();
	if (!zt_real32Eq(len, 0)) {
		x = x / len;
		y = y / len;
	}
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec2 ztVec2::getNormal() const
{
	r32 len = length();
	return zt_real32Eq(len, 0) ? *this : ztVec2(x / len, y / len);
}

// ------------------------------------------------------------------------------------------------

ztInline void ztVec2::rotate(r32 angle)
{
	r32 vsin = zt_sin(angle);
	r32 vcos = zt_cos(angle);

	r32 tx = x;
	r32 ty = y;

	x = vcos * tx - vsin * ty;
	y = vsin * tx + vcos * ty;
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec2 ztVec2::getRotated(r32 angle) const
{
	r32 vsin = zt_sin(angle);
	r32 vcos = zt_cos(angle);

	return ztVec2(vcos * x - vsin * y, vsin * x + vcos * y);
}

ztInline ztVec2 operator+(const ztVec2& v1, const ztVec2& v2)
{
	return ztVec2(v1.x + v2.x, v1.y + v2.y);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec2 operator-(const ztVec2& v1, const ztVec2& v2)
{
	return ztVec2(v1.x - v2.x, v1.y - v2.y);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec2 operator*(const ztVec2& v1, const ztVec2& v2)
{
	return ztVec2(v1.x * v2.x, v1.y * v2.y);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec2 operator*(const ztVec2& v1, r32 scale)
{
	return ztVec2(v1.x * scale, v1.y * scale);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInline r32 ztVec3::length() const
{
	return zt_sqrt(x * x + y * y + z * z);
}

// ------------------------------------------------------------------------------------------------

ztInline r32 ztVec3::dot(const ztVec3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec3 ztVec3::cross(const ztVec3& v) const
{
	return ztVec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

// ------------------------------------------------------------------------------------------------

ztInline r32 ztVec3::angle(const ztVec3& v) const
{
	ztVec3 v1n = getNormal();
	ztVec3 v2n = v.getNormal();
	r32 v1len = v1n.length();
	
	return (zt_real32Eq(v1len, 0) || zt_real32Eq(v2n.length(), 0)) ? v1len : zt_acos(dot(v));
}

// ------------------------------------------------------------------------------------------------

ztInline r32 ztVec3::distance(const ztVec3& v) const
{
	r32 x = x - v.x, y = y - v.y, z = z - v.z; 
	return zt_sqrt(x * x + y * y + z * z);
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec3 ztVec3::lerp(const ztVec3& v1, const ztVec3& v2, r32 percent)
{
	return ztVec3(v1.x + ((v2.x - v1.x) * percent), v1.y + ((v2.y - v1.y) * percent), v1.z + ((v2.z - v1.z) * percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec3 ztVec3::lerpHermite(const ztVec3& v1, const ztVec3& v2, r32 percent)
{
	return ztVec3(zt_lerpHermite(v1.x, v2.x, percent), zt_lerpHermite(v1.y, v2.y, percent), zt_lerpHermite(v1.z, v2.z, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec3 ztVec3::lerpSinerp(const ztVec3& v1, const ztVec3& v2, r32 percent)
{
	return ztVec3(zt_lerpSinerp(v1.x, v2.x, percent), zt_lerpSinerp(v1.y, v2.y, percent), zt_lerpSinerp(v1.z, v2.z, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec3 ztVec3::lerpCoserp(const ztVec3& v1, const ztVec3& v2, r32 percent)
{
	return ztVec3(zt_lerpCoserp(v1.x, v2.x, percent), zt_lerpCoserp(v1.y, v2.y, percent), zt_lerpCoserp(v1.z, v2.z, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec3 ztVec3::lerpBerp(const ztVec3& v1, const ztVec3& v2, r32 percent)
{
	return ztVec3(zt_lerpBerp(v1.x, v2.x, percent), zt_lerpBerp(v1.y, v2.y, percent), zt_lerpBerp(v1.z, v2.z, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec3 ztVec3::linearRemap(const ztVec3& val, const ztVec3& v1a, const ztVec3& v1b, const ztVec3& v2a, const ztVec3& v2b)
{
	return ztVec3(zt_lerp(v2a.x, v2b.x, zt_unlerp(v1a.x, v1b.x, val.x)), zt_lerp(v2a.y, v2b.y, zt_unlerp(v1a.y, v1b.y, val.y)), zt_lerp(v2a.z, v2b.z, zt_unlerp(v1a.z, v1b.z, val.z)));
}

// ------------------------------------------------------------------------------------------------

ztInline void ztVec3::normalize()
{
	r32 len = length();
	if (!zt_real32Eq(len, 0)) {
		x = x / len;
		y = y / len;
		z = z / len;
	}
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec3 ztVec3::getNormal() const
{
	r32 len = length();
	return zt_real32Eq(len, 0) ? *this : ztVec3(x / len, y / len);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec3 operator+(const ztVec3& v1, const ztVec3& v2)
{
	return ztVec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec3 operator-(const ztVec3& v1, const ztVec3& v2)
{
	return ztVec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec3 operator*(const ztVec3& v1, const ztVec3& v2)
{
	return ztVec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec3 operator*(const ztVec3& v1, r32 scale)
{
	return ztVec3(v1.x * scale, v1.y * scale, v1.z * scale);
}

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec4 ztVec4::lerp(const ztVec4& v1, const ztVec4& v2, r32 percent)
{
	return ztVec4(v1.x + ((v2.x - v1.x) * percent), v1.y + ((v2.y - v1.y) * percent), v1.z + ((v2.z - v1.z) * percent), v1.w + ((v2.w - v1.w) * percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec4 ztVec4::lerpHermite(const ztVec4& v1, const ztVec4& v2, r32 percent)
{
	return ztVec4(zt_lerpHermite(v1.x, v2.x, percent), zt_lerpHermite(v1.y, v2.y, percent), zt_lerpHermite(v1.z, v2.z, percent), zt_lerpHermite(v1.w, v2.w, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec4 ztVec4::lerpSinerp(const ztVec4& v1, const ztVec4& v2, r32 percent)
{
	return ztVec4(zt_lerpSinerp(v1.x, v2.x, percent), zt_lerpSinerp(v1.y, v2.y, percent), zt_lerpSinerp(v1.z, v2.z, percent), zt_lerpSinerp(v1.w, v2.w, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec4 ztVec4::lerpCoserp(const ztVec4& v1, const ztVec4& v2, r32 percent)
{
	return ztVec4(zt_lerpCoserp(v1.x, v2.x, percent), zt_lerpCoserp(v1.y, v2.y, percent), zt_lerpCoserp(v1.z, v2.z, percent), zt_lerpCoserp(v1.w, v2.w, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec4 ztVec4::lerpBerp(const ztVec4& v1, const ztVec4& v2, r32 percent)
{
	return ztVec4(zt_lerpBerp(v1.x, v2.x, percent), zt_lerpBerp(v1.y, v2.y, percent), zt_lerpBerp(v1.z, v2.z, percent), zt_lerpBerp(v1.w, v2.w, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztVec4 ztVec4::linearRemap(const ztVec4& val, const ztVec4& v1a, const ztVec4& v1b, const ztVec4& v2a, const ztVec4& v2b)
{
	return ztVec4(zt_lerp(v2a.x, v2b.x, zt_unlerp(v1a.x, v1b.x, val.x)), zt_lerp(v2a.y, v2b.y, zt_unlerp(v1a.y, v1b.y, val.y)), zt_lerp(v2a.z, v2b.z, zt_unlerp(v1a.z, v1b.z, val.z)), zt_lerp(v2a.w, v2b.w, zt_unlerp(v1a.w, v1b.w, val.w)));
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec4 operator+(const ztVec4& v1, const ztVec4& v2)
{
	return ztVec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec4 operator-(const ztVec4& v1, const ztVec4& v2)
{
	return ztVec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec4 operator*(const ztVec4& v1, const ztVec4& v2)
{
	return ztVec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec4 operator*(const ztVec4& v1, r32 scale)
{
	return ztVec4(v1.x * scale, v1.y * scale, v1.z * scale, v1.w * scale);
}

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// time

r32 zt_getTime(); // seconds since app started
void zt_sleep(r32 seconds);


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#if defined(ZT_TOOLS_IMPLEMENTATION)

// headers (strive to avoid including anything if possible)
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>

#if defined(ZT_COMPILER_MSVC)
#	include <windows.h>
#	include <shlobj.h>
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
			vsnprintf_s(buffer, zt_elementsOf(buffer), message, arg_ptr);

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
	zt_assert(_zt_logCallbacksCount < ZT_MAX_LOG_CALLBACKS);

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
			_zt_logCallbacksCount -= 1;
			break;
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_memSet(void *mem, int32 mem_len, byte value)
{
	byte* bmem = (byte*)mem;
	zt_fiz(mem_len) {
		bmem[i] = value;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_memCpy(void *dst, int32 dst_len, void *src, int32 src_len)
{
	int max_idx = zt_min(dst_len, src_len);
	for (int i = 0; i < max_idx; ++i) {
		((byte*)dst)[i] = ((byte*)src)[i];
	}
}

// ------------------------------------------------------------------------------------------------

int zt_memCmp(const void *one, const void *two, i32 size)
{
	byte *bone = (byte*)one;
	byte *btwo = (byte*)two;
	zt_fiz(size) {
		if (bone[i] < btwo[i]) return -1;
		if (bone[i] > btwo[i]) return  1;
	}

	return 0;
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

ztInternal void *(*_zt_malloc)(size_t) = malloc;
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

		zt_debugOnly(zt_memSet(arena->memory, total_size, 0));
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

void *zt_memAllocFromArena(ztMemoryArena *arena, i32 bytes)
{
	if (arena == nullptr) {
		return _zt_malloc(bytes);
	}

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
					zt_debugOnly(allocation->file = nullptr);
					zt_debugOnly(allocation->file_line = 0);

					alloc->next = allocation;
					alloc->length = bytes;
				}

				arena->current_used += sizeof(ztMemoryArena::allocation) + bytes;
				arena->peak_used = zt_max(arena->peak_used, arena->current_used);

				alloc->freed = 0;
				return alloc->start;
			}
			alloc = alloc->next;
		}
	}

	byte* next = arena->latest ? (byte*)arena->latest->start + arena->latest->length : arena->memory;
	zt_assert((next - arena->memory) + (i32)sizeof(ztMemoryArena::allocation) + bytes <= arena->total_size);

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

	zt_debugOnly(allocation->file = nullptr);
	zt_debugOnly(allocation->file_line = 0);

	arena->latest = allocation;

	arena->current_used += allocation->length + sizeof(ztMemoryArena::allocation);
	arena->peak_used = zt_max(arena->peak_used, arena->current_used);

	zt_debugOnly(zt_memSet(allocation->start, allocation->length, 0));

#if defined(ZT_MEM_ARENA_ZERO_NEW_MEMORY)
	ztReleaseOnly(zt_memSet(allocation->start, allocation->length, 0));
#endif

	zt_logMemory("memory (%s): allocated %d + %d bytes at location 0x%llx", chunk_name, allocation->length, sizeof(ztMemoryArena::allocation), (long long unsigned int)next);
	return (void*)allocation->start;
}

// ------------------------------------------------------------------------------------------------

void *zt_memAllocFromArena(ztMemoryArena *arena, i32 size, const char *file, int file_line)
{
	void *result = zt_memAllocFromArena(arena, size);
	if (result) {
		ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)(((byte*)result) - sizeof(ztMemoryArena::allocation));
		zt_debugOnly(allocation->file = file);
		zt_debugOnly(allocation->file_line = file_line);
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

void *zt_memRealloc(ztMemoryArena *arena, void *data, i32 size)
{
	if (data == nullptr) {
		return zt_memAllocFromArena(arena, size);
	}

	ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)(((byte*)data) - sizeof(ztMemoryArena::allocation));
	zt_assert(allocation->magic[0] == 'M' && allocation->magic[1] == 'R' && allocation->magic[2] == 'E');
	zt_logMemory("memory (%s): reallocating %d bytes of memory at location 0x%llx", chunk_name, bytes, (long long unsigned int)allocation);

	if (size <= allocation->length) {
		return data;
	}
	else {
		if (allocation == arena->latest) {
			zt_assert(((byte*)allocation->start - arena->memory) + size <= arena->total_size);
			if (((byte*)allocation->start - arena->memory) + size > arena->total_size) {
				zt_logCritical("realloc_from: Attempted to allocate more memory than available");
				return nullptr;
			}
			allocation->length = size;
			return data;
		}
		else {
			void *nmem = zt_memAllocFromArena(arena, size);
			if (nmem == nullptr) {
				return nmem;
			}
			zt_memCpy(nmem, size, data, zt_min(size, allocation->length));
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

	if (arena == nullptr) {
		_zt_free(data);
		return;
	}

	ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)(((byte*)data) - sizeof(ztMemoryArena::allocation));
	zt_assert(allocation->magic[0] == 'M' && allocation->magic[1] == 'R' && allocation->magic[2] == 'E');
	zt_logMemory("memory (%s): freeing %d bytes of memory at location 0x%llx", chunk_name, allocation->length, (long long unsigned int)allocation);
	
	zt_assert(allocation->freed == 0);
	zt_assert(allocation >= (ztMemoryArena::allocation*)arena->memory && allocation <= (ztMemoryArena::allocation*)(arena->memory + arena->total_size));

	zt_debugOnly(zt_memSet((void*)allocation->start, 1, allocation->length));
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
	zt_returnOnNull(arena);

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
			zt_debugOnly(zt_logMessage(log_level, "   file: %s (%d)", alloc->file, alloc->file_line));
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
	zt_assert(_zt_memGlobalArenaStackCount < ZT_MEM_GLOBAL_ARENA_STACK_SIZE);
	if (_zt_memGlobalArenaStackCount >= ZT_MEM_GLOBAL_ARENA_STACK_SIZE) {
		return false;
	}

	_zt_memGlobalArenaStack[_zt_memGlobalArenaStackCount++] = arena;
	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_memPopGlobalArena()
{
	zt_assert(_zt_memGlobalArenaStackCount > 0);
	_zt_memGlobalArenaStackCount -= 1;
}

// ------------------------------------------------------------------------------------------------

ztMemoryArena* zt_memGetGlobalArena()
{
	if (_zt_memGlobalArenaStackCount == 0) {
		return nullptr;
	}
	return _zt_memGlobalArenaStack[_zt_memGlobalArenaStackCount - 1];
}

// ------------------------------------------------------------------------------------------------

void zt_memSetDefaultMallocFree(void *(*malloc_func)(size_t), void(*free_func)(void*))
{
	_zt_malloc = malloc_func;
	_zt_free = free_func;
}

// ------------------------------------------------------------------------------------------------

void *zt_memAllocGlobalFull(i32 size, const char *file, int file_line)
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

void zt_memFreeGlobal(void *data)
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
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

/*static*/ const ztVec2 ztVec2::zero = ztVec2(0, 0);
/*static*/ const ztVec2 ztVec2::one = ztVec2(1, 1);

/*static*/ const ztVec3 ztVec3::zero = ztVec3(0, 0, 0);
/*static*/ const ztVec3 ztVec3::one = ztVec3(1, 1, 1);

// ------------------------------------------------------------------------------------------------

r32 zt_sin(r32 x)
{
	return sinf(x);
}

// ------------------------------------------------------------------------------------------------

r32 zt_cos(r32 y)
{
	return cosf(y);
}

// ------------------------------------------------------------------------------------------------

r32 zt_acos(r32 y)
{
	return acosf(y);
}

// ------------------------------------------------------------------------------------------------

r32 zt_atan2(r32 x, r32 y)
{
	return atan2f(x, y);
}

// ------------------------------------------------------------------------------------------------

r32 zt_sqrt(r32 v)
{
	return sqrtf(v);
}

// ------------------------------------------------------------------------------------------------

r32 zt_pow(r32 v, r32 p)
{
	return powf(v, p);
}

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
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

	int max_idx = zt_min(scopy_len - 1, sfrom_len);
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
	zt_strCpy(buffer, zt_elementsOf(buffer), s, s_len);

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
	zt_strCpy(buffer, zt_elementsOf(buffer), s, s_len);

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

	char *end = nullptr;
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

	char *end = nullptr;
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

u32 zt_strHash(const char *s)
{
	// MurmurHash2, by Austin Appleby
	// Note - This code makes a few assumptions about how your machine behaves -
	// 1. We can read a 4-byte value from any address without crashing
	// 2. sizeof(int) == 4
	// And it has a few limitations -
	// 1. It will not work incrementally.
	// 2. It will not produce the same results on little-endian and big-endian
	//    machines.

	// 'm' and 'r' are mixing constants generated offline.
	// They're not really 'magic', they just happen to work well.
	const u32 m = 0x5bd1e995;
	const int r = 24;

	u32 s_len = s == nullptr ? 0 : zt_strLen(s);
	u32 seed = s_len + 1;

	// Initialize the hash to a 'random' value
	u32 h = seed ^ s_len;

	// Mix 4 bytes at a time into the hash
	const u8 * data = (const u8*)s;

	while (s_len >= 4) {
		u32 k = *(u32 *)data;

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		data += 4;
		s_len -= 4;
	}

	// Handle the last few bytes of the input array
	switch (s_len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
		h *= m;
	};

	// Do a few final mixes of the hash to ensure the last few
	// bytes are well-incorporated.
	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
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

	return ztStrPosNotFound;
}

// ------------------------------------------------------------------------------------------------

const char *zt_strFindLast(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	int needle_len = zt_strLen(needle);

	return zt_strFindLast(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

const char *zt_strFindLast(const char *haystack, const char *needle, int needle_len)
{
	int haystack_len = zt_strLen(haystack);
	return zt_strFindLast(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

const char *zt_strFindLast(const char *haystack, int haystack_len, const char *needle, int needle_len)
{
	if (haystack_len == 0 || needle_len == 0 || !haystack || !needle) return nullptr;

	for (i32 i = (haystack_len - needle_len); i >= 0; --i) {
		zt_fjz(needle_len) {
			if (haystack[i + j] != needle[j]) goto no_match;
		}
		return haystack + i;
	no_match:;
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

int zt_strFindLastPos(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	int needle_len = zt_strLen(needle);

	return zt_strFindLastPos(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

int zt_strFindLastPos(const char *haystack, const char *needle, int needle_len)
{
	int haystack_len = zt_strLen(haystack);
	return zt_strFindLastPos(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

int zt_strFindLastPos(const char *haystack, int haystack_len, const char *needle, int needle_len)
{
	if (haystack_len == 0 || needle_len == 0 || !haystack || !needle) return -1;

	for (i32 i = (haystack_len - needle_len); i >= 0; --i) {
			zt_fjz(needle_len) {
			if (haystack[i + j] != needle[j]) goto no_match;
		}
		return i;
	no_match:;
	}

	return ztStrPosNotFound;
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

const char *zt_striFindLast(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	int needle_len = zt_strLen(needle);

	return zt_striFindLast(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

const char *zt_striFindLast(const char *haystack, const char *needle, int needle_len)
{
	int haystack_len = zt_strLen(haystack);
	return zt_striFindLast(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

const char *zt_striFindLast(const char *haystack, int haystack_len, const char *needle, int needle_len)
{
	if (haystack_len == 0 || needle_len == 0 || !haystack || !needle) return nullptr;

	for (i32 i = (haystack_len - needle_len); i >= 0; --i) {
		zt_fjz(needle_len) {
			if (_zt_to_upper(haystack[i + j]) != _zt_to_upper(needle[j])) goto no_match;
		}
		return haystack + i;
	no_match:;
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

int zt_striFindLastPos(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	int needle_len = zt_strLen(needle);

	return zt_striFindPos(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

int zt_striFindLastPos(const char *haystack, const char *needle, int needle_len)
{
	int haystack_len = zt_strLen(haystack);
	return zt_striFindPos(haystack, haystack_len, needle, needle_len);
}

// ------------------------------------------------------------------------------------------------

int zt_striFindLastPos(const char *haystack, int haystack_len, const char *needle, int needle_len)
{
	if (haystack_len == 0 || needle_len == 0 || !haystack || !needle) return -1;

	for (i32 i = (haystack_len - needle_len); i >= 0; --i) {
		zt_fjz(needle_len) {
			if (_zt_to_upper(haystack[i + j]) != _zt_to_upper(needle[j])) goto no_match;
		}
		return i;
	no_match:;
	}

	return -1;
}

// ------------------------------------------------------------------------------------------------

bool zt_strStartsWith(const char *s, const char *starts_with)
{
	return zt_strStartsWith(s, zt_strLen(s), starts_with, zt_strLen(starts_with));
}

// ------------------------------------------------------------------------------------------------

bool zt_strStartsWith(const char *s, int s_len, const char *starts_with, int sw_len)
{
	if (!s || !starts_with || s_len <= 0 || sw_len <= 0 || s_len < sw_len) return false;

	zt_fiz(sw_len) {
		if (s[i] != starts_with[i])
			return false;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_strEndsWith(const char *s, const char *ends_with)
{
	return zt_strEndsWith(s, zt_strLen(s), ends_with, zt_strLen(ends_with));
}

// ------------------------------------------------------------------------------------------------

bool zt_strEndsWith(const char *s, int s_len, const char *ends_with, int ew_len)
{
	if (!s || !ends_with || s_len <= 0 || ew_len <= 0 || s_len < ew_len) return false;

	for (int i = s_len - ew_len, e = 0; i < s_len; ++i, ++e) {
		if (s[i] != ends_with[e])
			return false;
	}

	return true;
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
	if (!s || s_len <= 0) return ztStrPosNotFound;

	for (int i = 1; i < s_len; ++i) {
		char ch = s[i];
		if (!(ch >= 48 && ch <= 57) && !(ch >= 65 && ch <= 90) && !(ch >= 97 && ch <= 122)) {
			return i;
		}
	}

	return ztStrPosNotFound;
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
	if (!s || s_len <= 0) return ztStrPosNotFound;

	for (int i = 1; i < s_len; ++i) {
		char ch = s[i];
		if (ch == '\n') {
			return (i + 1);
		}
	}

	return ztStrPosNotFound;
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

	bool include_tokens  = zt_bitIsSet(flags, ztStrTokenizeFlags_IncludeTokens);
	bool process_quotes  = zt_bitIsSet(flags, ztStrTokenizeFlags_ProcessQuotes);
	bool keep_quotes     = zt_bitIsSet(flags, ztStrTokenizeFlags_KeepQuotes);
	bool trim_whitespace = zt_bitIsSet(flags, ztStrTokenizeFlags_TrimWhitespace);

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

int zt_strPrintf(char *buffer, int buffer_size, const char *format, ...)
{
#if defined(ZT_WINDOWS)
	va_list arg_ptr;
	va_start(arg_ptr, format);
	return vsnprintf_s(buffer, buffer_size, buffer_size, format, arg_ptr);
#else
#	error "zt_strPrintf needs an implementation for this platform"
#endif
}

// ------------------------------------------------------------------------------------------------

int zt_strBytesToString(char *buffer, int buffer_size, i32 bytes)
{
	if (bytes < 1024) {
		return zt_strPrintf(buffer, buffer_size, "%d b", bytes);
	}
	else if (bytes < 1024 * 1024) {
		return zt_strPrintf(buffer, buffer_size, "%.2f kb", bytes / 1024.f);
	}
	else if (bytes < 1024 * 1024 * 1024) {
		return zt_strPrintf(buffer, buffer_size, "%.2f mb", bytes / (1024.f * 1024.f));
	}

	return zt_strPrintf(buffer, buffer_size, "%.2f gb", bytes / (1024.f * 1024.f * 1024.f));
}

// ------------------------------------------------------------------------------------------------

int zt_strNumberToString(char *buffer, int buffer_size, i64 number)
{
	if (buffer_size < 64) return 0;

	char* buffer_pos = buffer;

	int64 abs_number = abs(number);

	struct local
	{
		static void process(i64* number, char** buffer, bool* first, int64 div)
		{
			if (*number > div) {
				int64 num = *number / div;
				if (*first) {
					sprintf_s(*buffer, 5, "%d,", num);
					*first = false;
				}
				else {
					sprintf_s(*buffer, 5, "%03d,", num);
				}

				++(*buffer);
				++(*buffer);
				if (num > 9) ++(*buffer);
				if (num > 99) ++ (*buffer);
				*number -= num * div;
			}
		}
	};

	if (number < 0) {
		*buffer_pos = '-';
		++buffer_pos;
		number *= -1;
	}
	bool first = true;
	local::process(&number, &buffer_pos, &first, 1000000000000000000);
	local::process(&number, &buffer_pos, &first, 1000000000000000);
	local::process(&number, &buffer_pos, &first, 1000000000000);
	local::process(&number, &buffer_pos, &first, 1000000000);
	local::process(&number, &buffer_pos, &first, 1000000);
	local::process(&number, &buffer_pos, &first, 1000);

	if (first) {
		return (buffer_pos - buffer) + zt_strPrintf(buffer_pos, 4, "%d", number);
	}

	return (buffer_pos - buffer) + zt_strPrintf(buffer_pos, 4, "%03d", number);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool zt_fileOpen(ztFile *file, const char *file_name, ztFileOpenMethod_Enum file_open_method, ztMemoryArena *arena)
{
	zt_returnValOnNull(file, false);
	zt_returnValOnNull(file_name, false);

	zt_memSet(file, sizeof(ztFile), 0);

#if defined(ZT_WINDOWS)
	OFSTRUCT ofs;
	u32 style = 0;

	switch (file_open_method)
	{
	case ztFileOpenMethod_ReadOnly    : style |= OF_READ; break;
	case ztFileOpenMethod_WriteAppend : style |= OF_WRITE; break;
	case ztFileOpenMethod_WriteOver   : style |= OF_CREATE; break;
	}

	HFILE hfile = OpenFile(file_name, &ofs, style);
	if (hfile == HFILE_ERROR) {
		zt_logCritical("zt_fileOpen: unable to open file: %s (error code: %d)", file_name, (i32)ofs.nErrCode);
		return false;
	}

	i32 path_len = zt_strLen(ofs.szPathName);

	file->full_name = (char *)zt_memAllocFromArena(arena, path_len + 1);
	if (file->full_name == nullptr) {
		zt_logCritical("zt_fileOpen: unable to allocate memory for file information (file: %s)", file_name);
		CloseHandle((HANDLE)hfile);
		return false;
	}
	zt_strCpy(file->full_name, path_len, ofs.szPathName);
	file->arena = arena;

	file->open_method = file_open_method;
	file->size = GetFileSize((HANDLE)hfile, nullptr);

	file->win_file_handle = (i32)hfile;
	file->win_read_pos = 0;

	return true;
#endif
}

// ------------------------------------------------------------------------------------------------

void zt_fileClose(ztFile *file)
{
	zt_returnOnNull(file);

#if defined(ZT_WINDOWS)
	switch (file->open_method)
	{
		case ztFileOpenMethod_ReadOnly:
		case ztFileOpenMethod_WriteAppend:
		case ztFileOpenMethod_WriteOver: {
			CloseHandle((HANDLE)file->win_file_handle);
		}break;
	}

	zt_memFree(file->arena, file->full_name);
	zt_memSet(file, sizeof(ztFile), 0);
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetReadPos(ztFile *file)
{
	zt_returnValOnNull(file, 0);

#if defined(ZT_WINDOWS)
	return file->win_read_pos;
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_fileSetReadPos(ztFile *file, i32 pos)
{
	zt_returnValOnNull(file, false);

	if (pos > file->size) {
		zt_logDebug("zt_fileSetReadPos: attempting to set position beyond file size (%s)", file->full_name);
		return false;
	}

#if defined(ZT_WINDOWS)
	if (INVALID_SET_FILE_POINTER == SetFilePointer((HANDLE)file->win_file_handle, pos, NULL, FILE_BEGIN)) {
		zt_logCritical("zt_fileSetReadPos: SetFilePointer call failed (error %d)", GetLastError());
		return false;
	}

	file->win_read_pos = pos;
#endif

	return true;
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetFullPath(ztFile *file, char *buffer, int buffer_size)
{
	zt_returnValOnNull(file, 0);
	return zt_fileGetFullPath(file->full_name, buffer, buffer_size);
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetFileName(ztFile *file, char *buffer, int buffer_size)
{
	zt_returnValOnNull(file, 0);
	return zt_fileGetFileName(file->full_name, buffer, buffer_size);
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetFileExt(ztFile *file, char *buffer, int buffer_size)
{
	zt_returnValOnNull(file, 0);
	return zt_fileGetFileExt(file->full_name, buffer, buffer_size);
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetFullPath(const char *file_name, char *buffer, int buffer_size)
{
	if (file_name == nullptr) {
		return 0;
	}

	i32 pos_last_path = ztStrPosNotFound;

#if defined(ZT_WINDOWS)
	i32 pos_last_path_one = zt_strFindLastPos(file_name, "/");
	i32 pos_last_path_two = zt_strFindLastPos(file_name, "\\");
	pos_last_path = zt_max(pos_last_path_one, pos_last_path_two);
#endif

	if (pos_last_path == ztStrPosNotFound) {
		return 0;
	}

	zt_strCpy(buffer, buffer_size, file_name, pos_last_path);
	return pos_last_path;
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetFileName(const char *file_name, char *buffer, int buffer_size)
{
	if (file_name == nullptr) {
		return 0;
	}

	i32 pos_last_path = ztStrPosNotFound;

#if defined(ZT_WINDOWS)
	i32 pos_last_path_one = zt_strFindLastPos(file_name, "/");
	i32 pos_last_path_two = zt_strFindLastPos(file_name, "\\");
	pos_last_path = zt_max(pos_last_path_one, pos_last_path_two);
#endif

	if (pos_last_path == ztStrPosNotFound) {
		return 0;
	}

	i32 len = zt_strLen(file_name);

	zt_strCpy(buffer, buffer_size, file_name + pos_last_path + 1);
	return len - (pos_last_path + 1);
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetFileExt(const char *file_name, char *buffer, int buffer_size)
{
	if (file_name == nullptr) {
		return 0;
	}

	i32 pos = zt_strFindLastPos(file_name, ".");
	if (pos == ztStrPosNotFound) {
		return 0;
	}

	i32 len = zt_strLen(file_name);

	zt_strCpy(buffer, buffer_size, file_name + pos + 1);
	return len - (pos + 1);
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetAppBin(char *buffer, int buffer_size)
{
	zt_returnValOnNull(buffer, 0);

#if defined(ZT_WINDOWS)
	i32 len = GetModuleFileNameA(NULL, buffer, buffer_size);
	if (ERROR_INSUFFICIENT_BUFFER == GetLastError()) {
		zt_logCritical("zt_fileGetAppBin: GetModuleFileName returned ERROR_INSUFFICIENT_BUFFER for buffer size of %d", buffer_size);
	}

	return len;
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetAppPath(char *buffer, int buffer_size)
{
	zt_returnValOnNull(buffer, 0);

#if defined(ZT_WINDOWS)
	i32 len = GetModuleFileNameA(NULL, buffer, buffer_size);
	if (ERROR_INSUFFICIENT_BUFFER == GetLastError()) {
		zt_logCritical("zt_fileGetAppPath: GetModuleFileName returned ERROR_INSUFFICIENT_BUFFER for buffer size of %d", buffer_size);
	}

	int pos = zt_strFindLastPos(buffer, "\\");
	if (pos != ztStrPosNotFound) {
		buffer[pos] = 0;
		len = pos;
	}

	return len;
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetUserPath(char *buffer, int buffer_size, char *app_name)
{
	zt_returnValOnNull(buffer, 0);

#if defined(ZT_WINDOWS)
	char temp[ztFileMaxPath] = { 0 };
	SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, temp);

	int len_path = zt_strLen(temp);
	int len_name = zt_strLen(app_name);

	zt_assert(len_path + len_name + 1 < ztFileMaxPath); // as big as ztFileMaxPath is, this should never happen
	
	temp[len_path] = '\\';
	zt_strCpy(temp + len_path + 1, ztFileMaxPath - (len_path + 1), app_name);

	return zt_strCpy(buffer, buffer_size, temp, len_path + len_name + 1);
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetCurrentPath(char *buffer, int buffer_size)
{
	zt_returnValOnNull(buffer, 0);

#if defined(ZT_WINDOWS)
	return GetCurrentDirectoryA(buffer_size, buffer);
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_fileExists(const char *file_name)
{
#if defined(ZT_WINDOWS)
	OFSTRUCT ofs;

	HFILE hfile = OpenFile(file_name, &ofs, OF_READ);
	if (hfile == HFILE_ERROR) {
		return false;
	}
	CloseHandle((HANDLE)hfile);
	return true;
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_fileDelete(const char *file_name)
{
#if defined(ZT_WINDOWS)
	if (DeleteFileA(file_name) == FALSE) {
		zt_logCritical("zt_fileDelete: unable to delete file '%s' (error: %d)", file_name, GetLastError());
		return false;
	}

	return true;
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_fileCopy(const char *orig_file, const char *new_file)
{
#if defined(ZT_WINDOWS)
	if (CopyFileA(orig_file, new_file, TRUE) == FALSE) {
		zt_logCritical("zt_fileCopy: unable to copy file '%s' to '%s' (error: %d)", orig_file, new_file, GetLastError());
		return false;
	}

	return true;
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_fileRename(const char *orig_file, const char *new_file)
{
#if defined(ZT_WINDOWS)
	if (MoveFileA(orig_file, new_file) == FALSE) {
		zt_logCritical("zt_fileRename: unable to rename file '%s' to '%s' (error: %d)", orig_file, new_file, GetLastError());
		return false;
	}

	return true;
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileRead(ztFile *file, void *buffer, i32 buffer_size)
{
	zt_returnValOnNull(file, 0);
	zt_returnValOnNull(buffer, 0);

	if (buffer_size <= 0) {
		return 0;
	}

#if defined(ZT_WINDOWS)
	DWORD bytes_read = 0;
	if (FALSE == ReadFile((HANDLE)file->win_file_handle, (LPVOID)buffer, buffer_size, &bytes_read, nullptr)) {
		zt_logCritical("zt_fileRead: failure reading file: '%s'  (error: %d)", file->full_name, GetLastError());
		return 0;
	}

	file->win_read_pos += bytes_read;
	return (i32)bytes_read;
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileWrite(ztFile *file, void *buffer, i32 buffer_size)
{
	zt_returnValOnNull(file, 0);
	zt_returnValOnNull(buffer, 0);

	if (buffer_size <= 0) {
		return 0;
	}

#if defined(ZT_WINDOWS)
	DWORD bytes_written = 0;
	if (FALSE == WriteFile((HANDLE)file->win_file_handle, (LPVOID)buffer, buffer_size, &bytes_written, nullptr)) {
		zt_logCritical("zt_fileWrite: failure reading file: '%s'  (error: %d)", file->full_name, GetLastError());
		return 0;
	}

	file->win_read_pos += bytes_written;
	file->size += bytes_written;

	return (i32)bytes_written;
#endif
}

// ------------------------------------------------------------------------------------------------

void zt_fileFlush(ztFile *file)
{
	zt_returnOnNull(file);

#if defined(ZT_WINDOWS)
	FlushFileBuffers((HANDLE)file->win_file_handle);
#endif
}

// ------------------------------------------------------------------------------------------------

void *zt_readEntireFile(const char *file_name, i32 *file_size, ztMemoryArena *arena)
{
	zt_returnValOnNull(file_name, nullptr);
	zt_returnValOnNull(file_size, nullptr);

	ztFile file;
	if (!zt_fileOpen(&file, file_name, ztFileOpenMethod_ReadOnly, arena)) {
		return nullptr;
	}

	void *data = zt_memAllocFromArena(arena, file.size);
	if (data == nullptr) {
		return nullptr;
	}

	i32 bytes_read = zt_fileRead(&file, data, file.size);
	if (bytes_read != file.size) {
		zt_logCritical("zt_fileReadEntireFile: unable to read entire file '%s'.  requested %d bytes, received %d bytes", file_name, file.size, bytes_read);
		zt_memFree(arena, data);
		data = nullptr;
	}

	*file_size = file.size;
	zt_fileClose(&file);

	return data;
}

// ------------------------------------------------------------------------------------------------

i32 zt_readEntireFile(const char *file_name, void *buffer, i32 buffer_size)
{
	zt_returnValOnNull(file_name, 0);
	zt_returnValOnNull(buffer, 0);

	ztFile file;
	if (!zt_fileOpen(&file, file_name, ztFileOpenMethod_ReadOnly)) {
		return 0;
	}

	i32 to_read = zt_min(buffer_size, file.size);
	i32 bytes_read = zt_fileRead(&file, buffer, to_read);
	if (bytes_read != file.size) {
		zt_logCritical("zt_fileReadEntireFile: unable to read entire file '%s'.  requested %d bytes, received %d bytes", file_name, to_read, bytes_read);
	}

	zt_fileClose(&file);

	return bytes_read;
}

// ------------------------------------------------------------------------------------------------

i32 zt_writeEntireFile(const char *file_name, void *data, i32 data_size, ztMemoryArena *arena)
{
	zt_returnValOnNull(file_name, 0);
	zt_returnValOnNull(data, 0);

	ztFile file;
	if(!zt_fileOpen(&file, file_name, ztFileOpenMethod_WriteOver, arena)) {
		return 0;
	}

	i32 bytes_written = zt_fileWrite(&file, data, data_size);
	if (bytes_written != data_size) {
		zt_logCritical("zt_fileWriteEntireFile: unable to write entire file '%s'.  sent %d bytes, wrote %d bytes", file_name, file.size, bytes_written);
	}

	zt_fileClose(&file);

	return bytes_written;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

enum ztSerialEntryType_Enum
{
	ztSerialEntryType_Unknown,
	ztSerialEntryType_i8,
	ztSerialEntryType_i16,
	ztSerialEntryType_i32,
	ztSerialEntryType_i64,
	ztSerialEntryType_u8,
	ztSerialEntryType_u16,
	ztSerialEntryType_u32,
	ztSerialEntryType_u64,
	ztSerialEntryType_r32,
	ztSerialEntryType_r64,
	ztSerialEntryType_String,
	ztSerialEntryType_Binary,
	ztSerialEntryType_GroupBeg,
	ztSerialEntryType_GroupEnd,
	ztSerialEntryType_DataEnd,
	ztSerialEntryType_FileEnd,
};

// ------------------------------------------------------------------------------------------------

ztInternal i32 _zt_serial_header[5] = { 0x7e751c, 0xba7e20, 0x3d8601, 0x41569b, 0xac4d6d };
ztInternal const int _zt_mod_adler = 65521;

// ------------------------------------------------------------------------------------------------

// adler checksum... we aren't going for national security here, just general corruption detection

static int byte_idx = 0;

ztInternal ztInline void _zt_serialAddToChecksum(ztSerial *serial, byte data)
{
	serial->_checksum1 = (serial->_checksum1 + data) % _zt_mod_adler;
	serial->_checksum2 = (serial->_checksum2 + serial->_checksum1) % _zt_mod_adler;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline void _zt_serialAddToChecksum(ztSerial *serial, void *data, i32 data_len)
{
	zt_fiz(data_len) {
		serial->_checksum1 = (serial->_checksum1 + ((byte*)data)[i]) % _zt_mod_adler;
		serial->_checksum2 = (serial->_checksum2 + serial->_checksum1) % _zt_mod_adler;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline bool _zt_validateChecksum(ztSerial *serial)
{
	bool is_valid = false;

	i16 sum1 = 1, sum2 = 0;
	i32 checksum_save = 0;

	if (serial->file_data) {
		byte* chunk = (byte*)serial->file_data;
		zt_fiz(serial->file_data_size - 4) { // remove the final 4 bytes, which is the checksum
			sum1 = (sum1 + chunk[i]) % _zt_mod_adler;
			sum2 = (sum2 + sum1) % _zt_mod_adler;
		}
		zt_memCpy(&checksum_save, 4, chunk + (serial->file_data_size - 4), 4);
	}
	else {
		i32 pos = zt_fileGetReadPos(&serial->file);
		i32 size = serial->file.size;
		const i32 chunk_size = 1024 * 16;
		byte chunk[chunk_size];

		while (size) {
			i32 to_read = zt_min(size, chunk_size);
			if (to_read < chunk_size) {
				to_read -= 4; // remove the final 4 bytes, which is the checksum
			}
			if (zt_fileRead(&serial->file, chunk, to_read) != to_read)
				break;

			zt_fiz(to_read) {
				sum1 = (sum1 + chunk[i]) % _zt_mod_adler;
				sum2 = (sum2 + sum1) % _zt_mod_adler;
			}

			size -= to_read;
			if (size == 4) {
				zt_fileRead(&serial->file, &checksum_save);
				break;
			}
		}

		zt_fileSetReadPos(&serial->file, pos);
	}
	i32 checksum_calc = (sum2 << 16) | sum1;
	return checksum_calc == checksum_save;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline bool _zt_writeByte(ztSerial *serial, byte b)
{
	if (serial->mode != ztSerialMode_Writing) {
		return false;
	}

	_zt_serialAddToChecksum(serial, b);

	return 1 == zt_fileWrite(&serial->file, &b, 1);
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline bool _zt_writeData(ztSerial *serial, ztSerialEntryType_Enum entry_type, void *data, int data_size)
{
	if (serial->mode != ztSerialMode_Writing) {
		return false;
	}

	byte entry_type_byte = (byte)entry_type;
	if (1 != zt_fileWrite(&serial->file, &entry_type_byte, 1))
		return false;

	_zt_serialAddToChecksum(serial, entry_type);

	if (data_size != zt_fileWrite(&serial->file, data, data_size))
		return false;

	_zt_serialAddToChecksum(serial, data, data_size);

	byte data_end = ztSerialEntryType_DataEnd;
	if (1 != zt_fileWrite(&serial->file, &data_end, 1))
		return false;

	_zt_serialAddToChecksum(serial, data_end);

	return true;
}	

// ------------------------------------------------------------------------------------------------

ztInternal ztInline i32 _zt_readData(ztSerial *serial, void *data, i32 data_size)
{
	if (serial->file_data) {
		if (serial->file_data_size < data_size)
			return false;

		zt_memCpy(data, data_size, serial->file_data, data_size);

		serial->file_data = ((byte*)serial->file_data) + data_size;
		serial->file_data_size -= data_size;
		return true;
	}
	else {
		return zt_fileRead(&serial->file, data, data_size);
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline bool _zt_readByte(ztSerial *serial, byte *byte)
{
	if (serial->mode != ztSerialMode_Reading) {
		return false;
	}

	return _zt_readData(serial, byte, 1) == 1;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline bool _zt_readData(ztSerial *serial, ztSerialEntryType_Enum expected_type, void *data, int data_size)
{
	if (serial->mode != ztSerialMode_Reading) {
		return false;
	}

	if (serial->next_entry != expected_type) {
		if (serial->next_entry == ztSerialEntryType_GroupEnd || serial->next_entry == ztSerialEntryType_GroupBeg) {
			return true;
		}
		return false;
	}

	if (serial->file_data != nullptr) {
		if (serial->file_data_size < data_size)
			return false;

		zt_memCpy(data, data_size, serial->file_data, data_size);

		serial->file_data = ((byte*)serial->file_data) + data_size;
		serial->file_data_size -= data_size;
	}
	else {
		i32 bytes_read = zt_fileRead(&serial->file, data, data_size);
		if (bytes_read != data_size)
			return false;

		byte data_end = ztSerialEntryType_Unknown;
		if (1 != zt_fileRead(&serial->file, &data_end, 1))
			return false;

		byte next_entry = 0;
		if (1 != zt_fileRead(&serial->file, &next_entry, 1))
			return false;

		serial->next_entry = next_entry;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool _zt_serialMakeWriterDoHeader(ztSerial *serial, const char *identifier, i32 version)
{
	serial->mode = ztSerialMode_Writing;
	serial->_checksum1 = 1;
	serial->_checksum2 = 0;

	zt_strCpy(serial->identifier, zt_elementsOf(serial->identifier), identifier);
	serial->version = version;

	if (zt_fileWrite(&serial->file, _zt_serial_header, sizeof(_zt_serial_header)) != sizeof(_zt_serial_header))
		return false;

	_zt_serialAddToChecksum(serial, _zt_serial_header, sizeof(_zt_serial_header));

	if (zt_fileWrite(&serial->file, serial->identifier, sizeof(serial->identifier)) != sizeof(serial->identifier))
		return false;

	_zt_serialAddToChecksum(serial, serial->identifier, sizeof(serial->identifier));

	if (!zt_fileWrite(&serial->file, version))
		return false;

	_zt_serialAddToChecksum(serial, &version, sizeof(version));

	return true;
}

// ------------------------------------------------------------------------------------------------

bool _zt_serialMakeReaderDoHeader(ztSerial *serial, const char *identifier)
{
	if (!_zt_validateChecksum(serial)) {
		serial->mode = ztSerialMode_Corrupt;
		return false;
	}

	serial->mode = ztSerialMode_Reading;

	i32 header[zt_elementsOf(_zt_serial_header)] = { 0 };

	if (_zt_readData(serial, header, sizeof(header)) != sizeof(header))
		goto on_error;

	if (zt_memCmp(header, _zt_serial_header, sizeof(header)) != 0)
		goto on_error;

	if (_zt_readData(serial, serial->identifier, sizeof(serial->identifier)) != sizeof(serial->identifier))
		goto on_error;

	if (!zt_strEquals(serial->identifier, identifier))
		goto on_error;

	if (_zt_readData(serial, &serial->version, sizeof(serial->version)) != sizeof(serial->version))
		goto on_error;

	byte next_entry = ztSerialEntryType_Unknown;
	if (1 != _zt_readData(serial, &next_entry, 1))
		goto on_error;

	serial->next_entry = next_entry;

	return true;

on_error:
	serial->mode = ztSerialMode_Closed;
	return false;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool zt_serialMakeWriter(ztSerial *serial, const char *file_name, const char *identifier, i32 version)
{
	zt_returnValOnNull(serial, false);
	zt_returnValOnNull(file_name, false);
	zt_returnValOnNull(identifier, false);

	zt_memSet(serial, sizeof(ztSerial), 0);

	if (!zt_fileOpen(&serial->file, file_name, ztFileOpenMethod_WriteOver))
		return false;

	serial->close_file = true;

	return _zt_serialMakeWriterDoHeader(serial, identifier, version);
}

// ------------------------------------------------------------------------------------------------

bool zt_serialMakeWriter(ztSerial *serial, ztFile *file, const char *identifier, i32 version)
{
	zt_returnValOnNull(serial, false);
	zt_returnValOnNull(file, false);
	zt_returnValOnNull(identifier, false);

	zt_memSet(serial, sizeof(ztSerial), 0);

	if (file->open_method != ztFileOpenMethod_WriteOver || file->open_method != ztFileOpenMethod_WriteAppend)
		return false;

	serial->file = *file;
	serial->close_file = false;

	return _zt_serialMakeWriterDoHeader(serial, identifier, version);
}

// ------------------------------------------------------------------------------------------------

bool zt_serialMakeReader(ztSerial *serial, const char *file_name, const char *identifier)
{
	zt_returnValOnNull(serial, false);
	zt_returnValOnNull(file_name, false);
	zt_returnValOnNull(identifier, false);

	zt_memSet(serial, sizeof(ztSerial), 0);

	if (!zt_fileOpen(&serial->file, file_name, ztFileOpenMethod_ReadOnly))
		return false;

	serial->close_file = true;

	return _zt_serialMakeReaderDoHeader(serial, identifier);
}

// ------------------------------------------------------------------------------------------------

bool zt_serialMakeReader(ztSerial *serial, void *data, i32 data_size, const char *identifier)
{
	zt_returnValOnNull(serial, false);
	zt_returnValOnNull(data, false);
	zt_returnValOnNull(identifier, false);

	zt_memSet(serial, sizeof(ztSerial), 0);

	serial->close_file = false;
	serial->file_data = data;
	serial->file_data_size = data_size;

	return _zt_serialMakeReaderDoHeader(serial, identifier);
}

// ------------------------------------------------------------------------------------------------

bool zt_serialMakeReader(ztSerial *serial, ztFile *file, const char *identifier)
{
	zt_returnValOnNull(serial, false);
	zt_returnValOnNull(file, false);
	zt_returnValOnNull(identifier, false);

	zt_memSet(serial, sizeof(ztSerial), 0);

	if (file->open_method != ztFileOpenMethod_ReadOnly)
		return false;

	serial->file = *file;
	serial->close_file = false;

	return _zt_serialMakeReaderDoHeader(serial, identifier);
}

// ------------------------------------------------------------------------------------------------

void zt_serialClose(ztSerial *serial)
{
	zt_returnOnNull(serial);

	if (serial->mode != ztSerialMode_Reading && serial->mode != ztSerialMode_Writing) {
		zt_memSet(&serial, sizeof(serial), 0);
		return;
	}

	if (serial->mode == ztSerialMode_Writing) {
		_zt_writeByte(serial, ztSerialEntryType_FileEnd);

		i32 checksum = (serial->_checksum2 << 16) | serial->_checksum1;
		zt_fileWrite(&serial->file, checksum);
	}

	if (serial->close_file) {
		zt_fileClose(&serial->file);
	}

	zt_memSet(&serial, sizeof(serial), 0);
}

// ------------------------------------------------------------------------------------------------

bool zt_serialGroupPush(ztSerial *serial)
{
	if (serial->mode == ztSerialMode_Writing) {
		if (!_zt_writeByte(serial, ztSerialEntryType_GroupBeg))
			return false;

		serial->group_level += 1;
		return true;
	}
	else {
		while (serial->next_entry != ztSerialEntryType_GroupBeg && serial->next_entry != ztSerialEntryType_FileEnd) {
			// ok, the read is expecting a group to begin, but the previous group still has data to read
			// we need to just skip forward until we get to the group beginning
			// this is useful for allowing older versions of the reader to not fail miserably when given
			// a new file format

			/*
			ztSerialEntryType_Bool,
			ztSerialEntryType_GroupBeg,
			ztSerialEntryType_GroupEnd,
			ztSerialEntryType_DataEnd,
			ztSerialEntryType_FileEnd,
			*/
			switch (serial->next_entry) {
				case ztSerialEntryType_i8:     { i8  value; if (!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_i16:    { i16 value; if (!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_i32:    { i32 value; if (!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_i64:    { i64 value; if (!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_u8:     { u8  value; if (!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_u16:    { u16 value; if (!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_u32:    { u32 value; if (!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_u64:    { u64 value; if (!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_r32:    { r32 value; if (!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_r64:    { r64 value; if (!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_String: { char value[1]; if (!zt_serialRead(serial, value, zt_elementsOf(value), nullptr)) return false; break; }
				case ztSerialEntryType_Binary: { byte value[1]; if (!zt_serialRead(serial, (void*)value, zt_elementsOf(value), nullptr)) return false; break; }
			}
		}

		if (serial->next_entry != ztSerialEntryType_FileEnd) {
			byte next_entry = ztSerialEntryType_Unknown;
			if (!_zt_readByte(serial, &next_entry))
				return false;

			serial->next_entry = next_entry;
			return true;
		}
		return true;
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_serialGroupPop(ztSerial *serial)
{
	if (serial->mode == ztSerialMode_Writing) {
		if (!_zt_writeByte(serial, ztSerialEntryType_GroupEnd))
			return false;

		if (serial->group_level <= 0)
			return false;

		serial->group_level -= 1;
		return true;
	}
	else {
		int group_level = 0;
		while ((group_level != 0 || serial->next_entry != ztSerialEntryType_GroupEnd) && serial->next_entry != ztSerialEntryType_FileEnd) {
			// ok, the read is expecting a group to end, but the group still has data to read
			// we need to just skip forward until we get to the group end
			// this is useful for allowing older versions of the reader to not fail miserably when given
			// a new file format

			switch (serial->next_entry) {
				case ztSerialEntryType_i8:     { i8  value; if(!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_i16:    { i16 value; if(!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_i32:    { i32 value; if(!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_i64:    { i64 value; if(!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_u8:     { u8  value; if(!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_u16:    { u16 value; if(!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_u32:    { u32 value; if(!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_u64:    { u64 value; if(!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_r32:    { r32 value; if(!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_r64:    { r64 value; if(!zt_serialRead(serial, &value)) return false; break; }
				case ztSerialEntryType_String: { char value[1]; if (!zt_serialRead(serial, value, sizeof(value), nullptr)) return false; break; }
				case ztSerialEntryType_Binary: { char value[1]; if (!zt_serialRead(serial, (void*)value, sizeof(value), nullptr)) return false; break; }

				case ztSerialEntryType_GroupBeg: {
					group_level += 1;
					if (!zt_serialGroupPush(serial))
						return false;
					break;
				}

				case ztSerialEntryType_GroupEnd: {
					group_level -= 1;
					if (!zt_serialGroupPop(serial))
						return false;
					break;
				}
			}
		}

		if (serial->next_entry != ztSerialEntryType_FileEnd) {
			byte next_entry = ztSerialEntryType_Unknown;
			if (!_zt_readByte(serial, &next_entry))
				return false;

			serial->next_entry = next_entry;
			return true;
		}

		return false;
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_serialWrite(ztSerial *serial, i8 value) { return _zt_writeData(serial, ztSerialEntryType_i8, &value, sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, i16 value) { return _zt_writeData(serial, ztSerialEntryType_i16, &value, sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, i32 value) { return _zt_writeData(serial, ztSerialEntryType_i32, &value, sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, i64 value) { return _zt_writeData(serial, ztSerialEntryType_i64, &value, sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, u8 value) { return _zt_writeData(serial, ztSerialEntryType_u8, &value, sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, u16 value) { return _zt_writeData(serial, ztSerialEntryType_u16, &value, sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, u32 value) { return _zt_writeData(serial, ztSerialEntryType_u32, &value, sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, u64 value) { return _zt_writeData(serial, ztSerialEntryType_u64, &value, sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, r32 value) { return _zt_writeData(serial, ztSerialEntryType_r32, &value, sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, r64 value) { return _zt_writeData(serial, ztSerialEntryType_r64, &value, sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, bool value) { i8 v = (value ? 1 : 0);  return _zt_writeData(serial, ztSerialEntryType_i8, &v, 1); }
// ------------------------------------------------------------------------------------------------

bool zt_serialWrite(ztSerial *serial, const char *value, i32 value_len)
{
	if (!_zt_writeByte(serial, ztSerialEntryType_String))
		return false;

	if (zt_fileWrite(&serial->file, &value_len, sizeof(value_len)) != sizeof(value_len))
		return false;

	_zt_serialAddToChecksum(serial, &value_len, sizeof(value_len));

	zt_fiz(value_len) {
		if (!_zt_writeByte(serial, value[i]))
			return false;
	}

	if (!_zt_writeByte(serial, ztSerialEntryType_DataEnd))
		return false;
	
	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_serialWrite(ztSerial *serial, void *value, i32 value_len)
{
	if (!_zt_writeByte(serial, ztSerialEntryType_Binary))
		return false;

	if (zt_fileWrite(&serial->file, &value_len, sizeof(value_len)) != sizeof(value_len))
		return false;

	_zt_serialAddToChecksum(serial, &value_len, sizeof(value_len));

	byte* bvalue = (byte*)value;
	zt_fiz(value_len) {
		if (!_zt_writeByte(serial, bvalue[i]))
			return false;
	}

	if (!_zt_writeByte(serial, ztSerialEntryType_DataEnd))
		return false;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_serialRead(ztSerial *serial, i8 *value) { return _zt_readData(serial, ztSerialEntryType_i8, value, sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, i16 *value) { return _zt_readData(serial, ztSerialEntryType_i16, value, sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, i32 *value) { return _zt_readData(serial, ztSerialEntryType_i32, value, sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, i64 *value) { return _zt_readData(serial, ztSerialEntryType_i64, value, sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, u8 *value) { return _zt_readData(serial, ztSerialEntryType_u8, value, sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, u16 *value) { return _zt_readData(serial, ztSerialEntryType_u16, value, sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, u32 *value) { return _zt_readData(serial, ztSerialEntryType_u32, value, sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, u64 *value) { return _zt_readData(serial, ztSerialEntryType_u64, value, sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, r32 *value) { return _zt_readData(serial, ztSerialEntryType_r32, value, sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, r64 *value) { return _zt_readData(serial, ztSerialEntryType_r64, value, sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, bool *value) { i8 ival = 0; if (_zt_readData(serial, ztSerialEntryType_i8, &ival, sizeof(ival))) { *value = ival == 1; return true; } return false; }

// ------------------------------------------------------------------------------------------------

bool zt_serialRead(ztSerial *serial, char *value, i32 value_len, i32 *read_len)
{
	if (serial->next_entry != ztSerialEntryType_String) {
		if (serial->next_entry == ztSerialEntryType_GroupEnd || serial->next_entry == ztSerialEntryType_GroupBeg) {
			return true;
		}
		return false;
	}

	i32 stored_len = 0;
	if (_zt_readData(serial, &stored_len, sizeof(stored_len)) != sizeof(stored_len))
		return false;
	
	int to_read = zt_min((int)stored_len, value_len - 1);
	int leftover = stored_len - to_read;

	if (_zt_readData(serial, value, to_read) != to_read)
		return false;

	value[to_read] = 0;

	byte waste;
	for (int i = 0; i < leftover; ++i) {
		if (!_zt_readByte(serial, &waste))
			return false;
	}

	byte end_entry = 0;
	if (!_zt_readByte(serial, &end_entry))
		return false;

	if (end_entry != ztSerialEntryType_DataEnd)
		return false;

	byte next_entry = 0;
	if (!_zt_readByte(serial, &next_entry))
		return false;

	serial->next_entry = next_entry;

	if (read_len) *read_len = stored_len;
	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_serialRead(ztSerial *serial, void *value, i32 value_len, i32 *read_len)
{
	if (serial->next_entry != ztSerialEntryType_Binary) {
		if (serial->next_entry == ztSerialEntryType_GroupEnd || serial->next_entry == ztSerialEntryType_GroupBeg) {
			return true;
		}
		return false;
	}

	i32 stored_len = 0;
	if (_zt_readData(serial, &stored_len, sizeof(stored_len)) != sizeof(stored_len))
		return false;

	int to_read = zt_min(stored_len, value_len);
	int leftover = stored_len - to_read;

	if (_zt_readData(serial, value, to_read) != to_read)
		return false;

	byte waste;
	for (int i = 0; i < leftover; ++i) {
		if (!_zt_readByte(serial, &waste))
			return false;
	}

	byte end_entry = 0;
	if (!_zt_readByte(serial, &end_entry))
		return false;

	if (end_entry != ztSerialEntryType_DataEnd)
		return false;

	byte next_entry = 0;
	if (!_zt_readByte(serial, &next_entry))
		return false;

	serial->next_entry = next_entry;

	if (read_len) *read_len = stored_len;
	return true;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// this was adapted from: http://en.literateprograms.org/Mersenne_twister_(C)

#define ztRandom_MT_IA           397
#define ztRandom_MT_IB           (ztRandom_MTLen - ztRandom_MT_IA)
#define ztRandom_UpperMask       0x80000000
#define ztRandom_LowerMask       0x7fffffff
#define ztRandom_MatrixA         0x9908b0df
#define ztRandom_Twist(b,i,j)    ((b)[i] & ztRandom_UpperMask) | ((b)[j] & ztRandom_LowerMask)
#define ztRandom_Magic(s)        (((s)&1) * ztRandom_MatrixA)

// ------------------------------------------------------------------------------------------------

void zt_randomInit(ztRandom *random, i32 seed)
{
	srand(seed);
	for (int i = 0; i < ztRandom_MTLen; ++i) {
		random->mt_buffer[i] = rand();
	}
	random->mt_idx = 0;
}

// ------------------------------------------------------------------------------------------------

i32 zt_randomInt(ztRandom *random, i32 min, i32 max)
{
	i32 *b = random->mt_buffer;
	i32 idx = random->mt_idx;
	i32 s;
	i32 i;

	if (idx == ztRandom_MTLen * sizeof(i32))
	{
		idx = 0;
		i = 0;
		for (; i < ztRandom_MT_IB; i++) {
			s = ztRandom_Twist(b, i, i + 1);
			b[i] = b[i + ztRandom_MT_IA] ^ (s >> 1) ^ ztRandom_Magic(s);
		}
		for (; i < ztRandom_MTLen - 1; i++) {
			s = ztRandom_Twist(b, i, i + 1);
			b[i] = b[i - ztRandom_MT_IB] ^ (s >> 1) ^ ztRandom_Magic(s);
		}

		s = ztRandom_Twist(b, ztRandom_MTLen - 1, 0);
		b[ztRandom_MTLen - 1] = b[ztRandom_MT_IA - 1] ^ (s >> 1) ^ ztRandom_Magic(s);
	}
	random->mt_idx = idx + sizeof(unsigned long);
	i32 rv = *(unsigned long *)((unsigned char *)b + idx);

	return (zt_abs(rv) % (min - max)) + min;
}

// ------------------------------------------------------------------------------------------------

r32 zt_randomVal(ztRandom *random)
{
	return zt_randomInt(random, 0, 10001) / 10000.f;
}

// ------------------------------------------------------------------------------------------------

r32 zt_randomVal(ztRandom *random, r32 min, r32 max)
{
	return zt_randomVal(random) * (max - min) + min;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

i32 zt_iniFileGetValue(const char *ini_file, const char *section, const char *key, const char* dflt, char* buffer, i32 buffer_size)
{
#if defined(ZT_WINDOWS)
	return GetPrivateProfileStringA(section, key, dflt, buffer, buffer_size, ini_file);
#else
#	error "zt_iniFileGetValue needs an implementation for this platform"
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_iniFileGetValue(const char *ini_file, const char *section, const char *key, i32 dflt)
{
	char value_buffer[128] = { 0 };
	char dflt_buffer[128] = { 0 };
	zt_strPrintf(dflt_buffer, sizeof(dflt_buffer), "%d", dflt);
	int len = zt_iniFileGetValue(ini_file, section, key, dflt_buffer, value_buffer, sizeof(value_buffer));
	if (len <= 0) {
		return dflt;
	}

	bool success = false;
	i32 result = zt_strToInt(value_buffer, dflt, &success);
	if (!success) {
		result = zt_strToIntHex(value_buffer, dflt);
	}
	return result;
}

// ------------------------------------------------------------------------------------------------

r32 zt_iniFileGetValue(const char *ini_file, const char *section, const char *key, r32 dflt)
{
	char value_buffer[128] = { 0 };
	char dflt_buffer[128] = { 0 };
	zt_strPrintf(dflt_buffer, sizeof(dflt_buffer), "%f", dflt);
	int len = zt_iniFileGetValue(ini_file, section, key, dflt_buffer, value_buffer, sizeof(value_buffer));
	if (len <= 0) {
		return dflt;
	}

	return zt_strToReal32(value_buffer, dflt);
}

// ------------------------------------------------------------------------------------------------

bool zt_iniFileSetValue(const char *ini_file, const char *section, const char *key, const char *value)
{
#if defined(ZT_WINDOWS)
	return FALSE != WritePrivateProfileStringA(section, key, value, ini_file);
#else
#	error "zt_iniFileSetValue needs an implementation for this platform"
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_cmdHasArg(const char** argv, int argc, const char* arg_short, const char* arg_long)
{
	zt_fiz(argc) {
		if (zt_strStartsWith(argv[i], "--") && zt_strStartsWith(argv[i] + 2, arg_long)) {
			return true;
		}
		else if (zt_strStartsWith(argv[i], "-") && zt_strStartsWith(argv[i] + 1, arg_short)) {
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------------------------------------

bool zt_cmdGetArg(const char** argv, int argc, const char* arg_short, const char* arg_long, char* buffer, int buffer_size)
{
	zt_fiz(argc) {
		int data_pos = -1;
		if (zt_strStartsWith(argv[i], "--") && zt_strStartsWith(argv[i] + 2, arg_long)) {
			data_pos = 2 + zt_strLen(arg_long);
		}
		else if ((zt_strStartsWith(argv[i], "-") || zt_strStartsWith(argv[i], "/")) && zt_strStartsWith(argv[i] + 1, arg_short)) {
			data_pos = 1 + zt_strLen(arg_short);
		}

		if (data_pos != -1) {
			int argv_len = zt_strLen(argv[i]);
			if (data_pos + 1 < argv_len) {
				if (argv[i][data_pos] == '=') {
					data_pos += 1;
				}
				if (data_pos + 1 < argv_len) {
					zt_strCpy(buffer, buffer_size, argv[i] + data_pos, argv_len - data_pos);
					return true;
				}
			}
			return false; // no data to be had
		}
	}
	return false;
}

// ------------------------------------------------------------------------------------------------

r32 zt_getTime()
{
	struct local_init
	{
		local_init(LARGE_INTEGER *large_integer, r64 *seconds_per_count, LARGE_INTEGER *start_time)
		{
			QueryPerformanceFrequency(large_integer);
			*seconds_per_count = 1.0 / large_integer->QuadPart;

			QueryPerformanceFrequency(start_time);
		}
	};

	static LARGE_INTEGER large_integer;
	static r64 seconds_per_count;
	static LARGE_INTEGER start_time;
	static local_init local(&large_integer, &seconds_per_count, &start_time);

	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);

	return ((r32)(((r64)current.QuadPart - start_time.QuadPart) * seconds_per_count));
}

// ------------------------------------------------------------------------------------------------

void zt_sleep(r32 seconds)
{
#if defined(ZT_WINDOWS)
	Sleep(zt_convertToi32Floor(seconds * 1000.f));
#else
#error zt_sleep needs an implementation for this platform
#endif
}

// ------------------------------------------------------------------------------------------------

#endif // ZT_TOOLS_IMPLEMENTATION

#endif // include guard