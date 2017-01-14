/**************************************************************************************************
 ** file: zt_tools.h v 0.00 (active initial development)
 **
 ** This software is dual-licensed to the public domain and under the following
 ** license: you are granted a perpetual, irrevocable license to copy, modify,
 ** publish, and distribute this file as you see fit.
 **
 ** No warranty is offered or implied.  Use this at your own risk.
 **
 **************************************************************************************************
   
    Zero Tolerance Tools Library

	In exactly one c/cpp source file of your project, you must:

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

 **************************************************************************************************/

#ifndef __zt_tools_h_included__
#define __zt_tools_h_included__

// ------------------------------------------------------------------------------------------------
// compiler defines

#if defined(_MSC_VER)
#	define ZT_COMPILER_MSVC
#	if defined(_DEBUG)
#		define ZT_DEBUG
#	endif
#	if defined(_WIN64)
#		define ZT_WIN64
#		define ZT_64BIT
#	elif defined(_WIN32)
#		define ZT_WIN32
#		define ZT_32BIT
#	endif
#	if defined(_UNICODE)
#		define ZT_UNICODE
#	endif

#	define ZT_WINDOWS

#	define ztReal32Max		3.402823466e+38F
#	define ztReal32Min		1.175494351e-38F
#	define ztReal32Epsilon	1.192092896e-07F

#	define ztReal64Max		1.7976931348623158e+308
#	define ztReal64Min		2.2250738585072014e-308
#	define ztReal64Epsilon	2.2204460492503131e-016

#	define ztInt32Max       2147483647
#	define ztInt32Min      -2147483648
#	define ztUint32Max      4294967295
#	define ztUint32Min      0
#	define ztInt64Max       9223372036854775807
#	define ztInt64Min      -9223372036854775808
#	define ztUint64Max      18446744073709551615 
#	define ztUint64Min      0

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

// ------------------------------------------------------------------------------------------------
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

#if defined(ZT_WINDOWS)
#	define zt_winOnly(code)	code
#else
#	define zt_winOnly(code)
#endif

#if defined(ZT_64BIT)
#	define zt_64bitOnly(code) code
#	define ztPointerSize 8
#else
#	define zt_64bitOnly(code)
#endif

#if defined(ZT_32BIT)
#	define zt_32bitOnly(code) code
#	define ztPointerSize 4
#else
#	define zt_32bitOnly(code)
#endif


// ------------------------------------------------------------------------------------------------
// DLL defines

// Use ZT_DLLEXPORT before any function inside a DLL that needs called externally

#if defined(ZT_DLL)
#	if defined(ZT_COMPILER_MSVC)
#		define ZT_DLLEXPORT   extern "C" __declspec(dllexport)
#	else
#		define ZT_DLLEXPORT
#	endif
#else
#	define ZT_DLLEXPORT
#endif


// ------------------------------------------------------------------------------------------------
// useful macros

#define zt_elementsOf(native_array)	((int)(sizeof(native_array) / sizeof((native_array)[0])))
#define zt_sizeof(type) ((i32)sizeof(type))

#if defined(ZT_DEBUG)
#	define zt_assert(cond)	                      if(!(cond)) { zt_assert_raw(#cond, __FILE__, __LINE__); }
#	define zt_assertReturnOnFail(cond)            if(!(cond)) { zt_assert_raw(#cond, __FILE__, __LINE__); return; }
#	define zt_assertReturnValOnFail(cond, retval) if(!(cond)) { zt_assert_raw(#cond, __FILE__, __LINE__); return (retval); }

#	define zt_debugOnly(code)	code
#	define zt_releaseOnly(code)
#else
#	define zt_assert(cond)
#	define zt_assertReturnOnFail(cond)            if(!(cond)) { return; }
#	define zt_assertReturnValOnFail(cond, retval) if(!(cond)) { return (retval); }

#	define zt_debugOnly(code)
#	define zt_releaseOnly(code)	code
#endif

#define zt_assertAlways(cond)                  if(!(cond)) { zt_assert_raw(#cond, __FILE__, __LINE__); }
#define zt_staticAssert(cond)                  typedef char _zt_static_assertion_##__COUNTER__[(cond)?1:-1]

#define ztInline        inline
#define ztInternal      static
#define ztPersistent    static
#define ztGlobal        static

#define zt_kilobytes(kb)	((kb) * 1024LL)
#define zt_megabytes(mb)	(zt_kilobytes(mb) * 1024LL)
#define zt_gigabytes(gb)	(zt_megabytes(gb) * 1024LL)
#define zt_terabytes(tb)	(zt_gigabytes(tb) * 1024LL)

#define zt_bit(num)             (1<<(num))
#define zt_bitAdd(var, flag)    ((var) |= (flag))
#define zt_bitRemove(var, flag) ((var) &= ~(flag))
#define zt_bitIsSet(var, flag)  (((var) & (flag)) != 0)

#define zt_max(val1, val2) ( (val1) > (val2) ? (val1) : (val2) )
#define zt_min(val1, val2) ( (val1) < (val2) ? (val1) : (val2) )
#define zt_clamp(val, min, max) ( zt_min(max, (zt_max(min, val))) )
#define zt_abs(val) ( (val) < 0 ? -(val) : (val) )
#define zt_swap(val1, val2) {auto temp = val1; val1 = val2; val2 = temp;}

#define zt_real32Eq(val1, val2) (zt_max(val1, val2) - zt_min(val1, val2) < ztReal32Epsilon)
#define zt_real64Eq(val1, val2) (zt_max(val1, val2) - zt_min(val1, val2) < ztReal64Epsilon)

// yes, shamelessly "borrowed" from Shawn McGrath
#define zt_fiz(end) for(int i = 0; i < (int)(end); ++i)
#define zt_fjz(end) for(int j = 0; j < (int)(end); ++j)
#define zt_fkz(end) for(int k = 0; k < (int)(end); ++k)
#define zt_fxz(end) for(int x = 0; x < (int)(end); ++x)
#define zt_fyz(end) for(int y = 0; y < (int)(end); ++y)
#define zt_fzz(end) for(int z = 0; z < (int)(end); ++z)
#define zt_fize(end) for(int i = 0; i < (int)zt_elementsOf((end)); ++i)
#define zt_fjze(end) for(int j = 0; j < (int)zt_elementsOf((end)); ++j)
#define zt_fkze(end) for(int k = 0; k < (int)zt_elementsOf((end)); ++k)
#define zt_fxze(end) for(int x = 0; x < (int)zt_elementsOf((end)); ++x)
#define zt_fyze(end) for(int y = 0; y < (int)zt_elementsOf((end)); ++y)
#define zt_fzze(end) for(int z = 0; z < (int)zt_elementsOf((end)); ++z)
#define zt_fizr(beg) for(int i = (int)(beg); i >= 0; --i)
#define zt_fjzr(beg) for(int j = (int)(beg); j >= 0; --j)
#define zt_fkzr(beg) for(int k = (int)(beg); k >= 0; --k)
#define zt_fxzr(beg) for(int x = (int)(beg); x >= 0; --x)
#define zt_fyzr(beg) for(int y = (int)(beg); y >= 0; --y)
#define zt_fzzr(beg) for(int z = (int)(beg); z >= 0; --z)
#define zt_fizre(beg) for(int i = (int)zt_elementsOf((beg)); i >= 0; --i)
#define zt_fjzre(beg) for(int j = (int)zt_elementsOf((beg)); j >= 0; --j)
#define zt_fkzre(beg) for(int k = (int)zt_elementsOf((beg)); k >= 0; --k)
#define zt_fxzre(beg) for(int x = (int)zt_elementsOf((beg)); x >= 0; --x)
#define zt_fyzre(beg) for(int y = (int)zt_elementsOf((beg)); y >= 0; --y)
#define zt_fzzre(beg) for(int z = (int)zt_elementsOf((beg)); z >= 0; --z)
#define zt_flink(var,start) for(auto *var = start; var != nullptr; var = var->next)
#define zt_flinknext(var,start,next_var) for(auto *var = start; var != nullptr; var = var->next_var)

#define ztMathPi		 3.14159626f
#define ztMathPi2		 6.28319252f
#define ztMathPi180		 0.01745331f
#define ztMath180Pi		57.29571374f

#define zt_degreesToRadians(degrees) ((degrees) * ztMathPi180)
#define zt_radiansToDegrees(radians) ((radians) * ztMath180Pi)

#if !defined(ZT_TOOLS_RETURN_ON_NULLPTR_NO_ASSERT)
#	define zt_returnOnNull(ptr) if (ptr == nullptr) { zt_assert(false); return; }
#	define zt_returnValOnNull(ptr, retval) if (ptr == nullptr) { zt_assert(false); return retval; };
#else
#	define zt_returnOnNull(ptr) if (ptr == nullptr) { return; }
#	define zt_returnValOnNull(ptr, retval) if (ptr == nullptr) { return retval; };
#endif

// ------------------------------------------------------------------------------------------------
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

#if defined(ZT_64BIT)
typedef uint64 pointer;
#else
typedef uint32 pointer;
#endif

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

// ------------------------------------------------------------------------------------------------
// math

struct ztPoint2
{
	union {
		struct {
			i32 x;
			i32 y;
		};
		i32 values[2];
	};

	ztPoint2() {}
	ztPoint2(i32 _x, i32 _y) :x(_x), y(_y) {}
};

// ------------------------------------------------------------------------------------------------

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

	ztVec2() {}
	ztVec2(r32 _x, r32 _y) :x(_x), y(_y) {}

	ztVec2& operator+=(const ztVec2& v) { x += v.x; y += v.y; return *this;}
	ztVec2& operator-=(const ztVec2& v) { x -= v.x; y -= v.y; return *this;}
	ztVec2& operator*=(r32 v) { x *= v; y *= v; return *this; }

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
	static const ztVec2 min;
	static const ztVec2 max;

#if defined(ZT_VEC2_EXTRAS)
	ZT_VEC2_EXTRAS	// use this to add conversions to and from your own classes
#endif
};

ztInline ztVec2 operator+(const ztVec2& v1, const ztVec2& v2);
ztInline ztVec2 operator-(const ztVec2& v1, const ztVec2& v2);
ztInline ztVec2 operator*(const ztVec2& v1, const ztVec2& v2);
ztInline ztVec2 operator*(const ztVec2& v1, r32 scale);
ztInline ztVec2 operator*(r32 scale, const ztVec2& v1);

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

	ztVec3() {}
	ztVec3(r32 _x, r32 _y, r32 _z) :x(_x), y(_y), z(_z) {}
	ztVec3(const ztVec2& vec2, r32 _z) : x(vec2.x), y(vec2.y), z(_z) {}

	ztVec3& operator+=(const ztVec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	ztVec3& operator-=(const ztVec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	ztVec3& operator*=(r32 v) { x *= v; y *= v; z *= v; return *this; }
	ztVec3& operator*=(const ztVec3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }

	bool operator==(const ztVec3& v) const { return x == v.x && y == v.y && z == v.z; }
	bool operator!=(const ztVec3& v) const { return x != v.x || y != v.y || z != v.z; }

	bool equalsClose(const ztVec3& v) const { return zt_real32Eq(x, v.x) && zt_real32Eq(y, v.y) && zt_real32Eq(z, v.z); }

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
	static const ztVec3 min;
	static const ztVec3 max;

#if defined(ZT_VEC3_EXTRAS)
	ZT_VEC3_EXTRAS	// use this to add conversions to and from your own classes
#endif
};

ztInline ztVec3 operator+(const ztVec3& v1, const ztVec3& v2);
ztInline ztVec3 operator-(const ztVec3& v1, const ztVec3& v2);
ztInline ztVec3 operator*(const ztVec3& v1, const ztVec3& v2);
ztInline ztVec3 operator*(const ztVec3& v1, r32 scale);
ztInline ztVec3 operator*(r32 scale, const ztVec3& v1);

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
			ztVec2 zw;
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

	ztVec4() {}
	ztVec4(r32 _x, r32 _y, r32 _z, r32 _w) :x(_x), y(_y), z(_z), w(_w) {}
	ztVec4(const ztVec2& vec2a, const ztVec2& vec2b) : x(vec2a.x), y(vec2a.y), z(vec2b.x), w(vec2b.y) {}
	ztVec4(const ztVec3& vec3, r32 _w) : x(vec3.x), y(vec3.y), z(vec3.z), w(_w) {}

	ztVec4& operator+=(const ztVec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this;}
	ztVec4& operator-=(const ztVec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this;}
	ztVec4& operator*=(r32 v) { x *= v; y *= v; z *= v; w *= v; return *this; }
	ztVec4& operator*=(const ztVec4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }

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
	static const ztVec4 min;
	static const ztVec4 max;

#if defined(ZT_VEC4_EXTRAS)
	ZT_VEC4_EXTRAS	// use this to add conversions to and from your own classes
#endif
};

ztInline ztVec4 operator+(const ztVec4& v1, const ztVec4& v2);
ztInline ztVec4 operator-(const ztVec4& v1, const ztVec4& v2);
ztInline ztVec4 operator*(const ztVec4& v1, const ztVec4& v2);
ztInline ztVec4 operator*(const ztVec4& v1, r32 scale);
ztInline ztVec4 operator*(r32 scale, const ztVec4& v1);

typedef ztVec4 ztColor;
#define ztColour ztColor;	// pick your favorite (favourite?)

#define ztColor_White          ztColor(1.0f, 1.0f, 1.0f, 1.f)
#define ztColor_Black          ztColor( .0f,  .0f,  .0f, 1.f)
#define ztColor_Gray           ztColor(.50f, .50f, .50f, 1.f)
#define ztColor_LightGray      ztColor(.83f, .83f, .83f, 1.f)
#define ztColor_DarkGray       ztColor(.66f, .66f, .66f, 1.f)
#define ztColor_Red            ztColor(1.0f,  .0f,  .0f, 1.f)
#define ztColor_LightRed       ztColor(1.0f, .75f, .80f, 1.f)
#define ztColor_DarkRed        ztColor(.55f,  .0f,  .0f, 1.f)
#define ztColor_Green          ztColor( .0f, 1.0f,  .0f, 1.f)
#define ztColor_LightGreen     ztColor(.56f, .93f, .56f, 1.f)
#define ztColor_DarkGreen      ztColor( .0f, .20f, .13f, 1.f)
#define ztColor_Blue           ztColor( .0f,  .0f, 1.0f, 1.f)
#define ztColor_LightBlue      ztColor(.68f, .85f, .90f, 1.f)
#define ztColor_DarkBlue       ztColor( .0f,  .0f, .55f, 1.f)
#define ztColor_Purple         ztColor(.50f,  .0f, .50f, 1.f)
#define ztColor_LightPurple    ztColor(.59f, .48f, .71f, 1.f)
#define ztColor_DarkPurple     ztColor(.19f, .10f, .20f, 1.f)
#define ztColor_Cyan           ztColor( .0f, 1.0f, 1.0f, 1.f)
#define ztColor_Yellow         ztColor(1.0f, 1.0f,  .0f, 1.f)
#define ztColor_LightYellow    ztColor(1.0f, 1.0f, .88f, 1.f)
#define ztColor_DarkYellow     ztColor(.61f, .53f, .50f, 1.f)
#define ztColor_Orange         ztColor(1.0f, .50f,  .0f, 1.f)
#define ztColor_LightOrange    ztColor(1.0f, .60f, .40f, 1.f)
#define ztColor_DarkOrange     ztColor(1.0f, .55f,  .0f, 1.f)


// ------------------------------------------------------------------------------------------------

enum ztMat4_Enum
{
	ztMat4_Col0Row0 = 0, 
	ztMat4_Col0Row1 = 1,
	ztMat4_Col0Row2 = 2,
	ztMat4_Col0Row3 = 3,
	ztMat4_Col1Row0 = 4,
	ztMat4_Col1Row1 = 5,
	ztMat4_Col1Row2 = 6,
	ztMat4_Col1Row3 = 7,
	ztMat4_Col2Row0 = 8,
	ztMat4_Col2Row1 = 9,
	ztMat4_Col2Row2 = 10,
	ztMat4_Col2Row3 = 11,
	ztMat4_Col3Row0 = 12,
	ztMat4_Col3Row1 = 13,
	ztMat4_Col3Row2 = 14,
	ztMat4_Col3Row3 = 15,

	ztMat4_Row0Col0 = 0,
	ztMat4_Row1Col0 = 1,
	ztMat4_Row2Col0 = 2,
	ztMat4_Row3Col0 = 3,
	ztMat4_Row0Col1 = 4,
	ztMat4_Row1Col1 = 5,
	ztMat4_Row2Col1 = 6,
	ztMat4_Row3Col1 = 7,
	ztMat4_Row0Col2 = 8,
	ztMat4_Row1Col2 = 9,
	ztMat4_Row2Col2 = 10,
	ztMat4_Row3Col2 = 11,
	ztMat4_Row0Col3 = 12,
	ztMat4_Row1Col3 = 13,
	ztMat4_Row2Col3 = 14,
	ztMat4_Row3Col3 = 15,
};

struct ztMat4
{
	union {
		r32 values[16];

		struct {
			ztVec4 cols[4];
		};
	};

	ztMat4() {}
	ztMat4(r32 v[16]) { zt_fiz(16) values[i] = v[i]; }
	ztMat4(r32 c0r0, r32 c0r1, r32 c0r2, r32 c0r3, r32 c1r0, r32 c1r1, r32 c1r2, r32 c1r3, r32 c2r0, r32 c2r1, r32 c2r2, r32 c2r3, r32 c3r0, r32 c3r1, r32 c3r2, r32 c3r3) { values[0] = c0r0; values[1] = c0r1; values[2] = c0r2; values[3] = c0r3; values[4] = c1r0; values[5] = c1r1; values[6] = c1r2; values[7] = c1r3; values[8] = c2r0; values[9] = c2r1; values[10] = c2r2; values[11] = c2r3; values[12] = c3r0; values[13] = c3r1; values[14] = c3r2; values[15] = c3r3; }
	ztMat4(const ztMat4& copy) { zt_fiz(16) values[i] = copy.values[i]; }

	void translate(const ztVec3& position)                   { values[ztMat4_Col3Row0] = position.x; values[ztMat4_Col3Row1] = position.y; values[ztMat4_Col3Row2] = position.z; }
	void translate(r32 x, r32 y, r32 z)                      { values[ztMat4_Col3Row0] = x; values[ztMat4_Col3Row1] = y; values[ztMat4_Col3Row2] = z; }
	ztMat4 getTranslate(const ztVec3& position) const        { ztMat4 copy(*this); copy.translate(position); return copy; }
	ztMat4 getTranslate(r32 x, r32 y, r32 z) const           { ztMat4 copy(*this); copy.translate(x, y, z); return copy; }

	void scale(const ztVec3& scale)                          { values[ztMat4_Col0Row0] = scale.x; values[ztMat4_Col1Row1] = scale.y; values[ztMat4_Col2Row2] = scale.z; }
	void scale(r32 x, r32 y, r32 z)                          { values[ztMat4_Col0Row0] = x; values[ztMat4_Col1Row1] = y; values[ztMat4_Col2Row2] = z; }
	ztMat4 getScale(const ztVec3& scale) const               { ztMat4 copy(*this); copy.scale(scale); return copy; }
	ztMat4 getScale(r32 x, r32 y, r32 z) const               { ztMat4 copy(*this); copy.scale(x, y, z); return copy; }

	void rotateEuler(const ztVec3& euler);
	void rotateEuler(r32 x, r32 y, r32 z);
	ztMat4 getRotateEuler(const ztVec3& euler) const;
	ztMat4 getRotateEuler(r32 x, r32 y, r32 z) const;

	void multiply(const ztMat4& mat);
	ztMat4 getMultiply(const ztMat4& mat) const;
	ztVec3 getMultiply(const ztVec3& vec) const;

	void transpose();
	ztMat4 getTranspose() const;

	void inverse();
	ztMat4 getInverse() const;

	void lookAt(ztVec3 eye_pos, ztVec3 target_pos, ztVec3 up_vec = ztVec3(0, 1, 0));
	ztMat4 getLookAt(ztVec3 eye_pos, ztVec3 target_pos, ztVec3 up_vec = ztVec3(0, 1, 0)) const;

	void extract(ztVec3 *position, ztVec3 *rotation, ztVec3 *scale); // does not work well with scaled matrices

	void removeTranslation();
	ztMat4 getRemoveTranslation();

	ztMat4& operator*=(const ztMat4& mat4);
	ztMat4& operator*=(const ztVec3& vec3);

	r32 operator[](int idx) const { return values[idx]; }
	r32& operator[](int idx) { return values[idx]; }

	bool operator==(const ztMat4& m) const { zt_fiz(16) if (!zt_real32Eq(values[i], m.values[i])) return false; return true; }
	bool operator!=(const ztMat4& m) const { return !(*this == m); }

	static ztMat4 makeOrthoProjection(r32 left, r32 right, r32 top, r32 bottom, r32 near_z, r32 far_z);
	static ztMat4 makePerspectiveProjection(r32 angle_of_view, r32 width, r32 height, r32 near_z, r32 far_z);

	static const ztMat4 zero;
	static const ztMat4 identity;

#if defined(ZT_MAT4_EXTRAS)
	ZT_MAT4_EXTRAS	// use this to add conversions to and from your own classes
#endif
};

// ------------------------------------------------------------------------------------------------

ztInline ztMat4 operator*(const ztMat4& m1, const ztMat4& m2);
ztInline ztVec3 operator*(const ztMat4& m, const ztVec3& v);

// ------------------------------------------------------------------------------------------------

struct ztQuat
{
	union {
		r32 values[4];

		struct {
			r32 x;
			r32 y;
			r32 z;
			r32 w;
		};

		struct {
			ztVec3 xyz;
			r32 w;
		};

		struct {
			ztVec4 xyzw;
		};
	};

	ztQuat() {}
	ztQuat(r32 v[4]) : x(v[0]), y(v[1]), z(v[2]), w(v[3]) {}
	ztQuat(r32 _x, r32 _y, r32 _z, r32 _w) : x(_x), y(_y), z(_z), w(_w) {}
	ztQuat(const ztVec3& _xyz, r32 _w) : xyz(_xyz), w(_w) {}
	ztQuat(const ztVec4& _xyzw) : xyzw(_xyzw) {}

	ztQuat& operator+=(const ztQuat& q);
	ztQuat& operator-=(const ztQuat& q);
	ztQuat& operator*=(const ztQuat& q);
	ztQuat& operator/=(const ztQuat& q);

	ztQuat& operator*=(r32 s);
	ztQuat& operator/=(r32 s);

	r32 dot(const ztQuat& q) const;
	r32 magnitude() const;

	void normalize();
	ztQuat getNormalize() const;

	void conjugate();
	ztQuat getConjugate() const;

	void inverse();
	ztQuat getInverse() const;

	ztVec3 axis() const;
	r32 angle() const;

	void axisAngle(ztVec3 *axis, r32 *angle) const;

	ztVec3 euler() const;

	void rotatePosition(ztVec3 *vec) const;
	ztVec3 rotatePosition(const ztVec3 &vec) const;
	ztVec3 rotatePosition(r32 x, r32 y, r32 z) const;
	void rotatePosition(r32 *x, r32 *y, r32 *z) const;

	ztMat4 convertToMat4() const;
	void convertToMat4(ztMat4 *mat) const;

	bool operator==(const ztQuat& q) const { return xyzw == q.xyzw; }
	bool operator!=(const ztQuat& q) const { return xyzw != q.xyzw; }

	static ztQuat makeFromAxisAngle(r32 axis_x, r32 axis_y, r32 axis_z, r32 angle);
	static ztQuat makeFromEuler(r32 pitch, r32 yaw, r32 roll);
	static ztQuat makeFromEuler(const ztVec3& euler) { return makeFromEuler(euler.x, euler.y, euler.z); }
	static ztQuat makeFromMat4(const ztMat4& mat);
	static ztQuat makeFromDirection(const ztVec3& dir, const ztVec3& up = ztVec3(0, 1, 0));

	static ztQuat lerp(const ztQuat& q1, const ztQuat& q2, r32 percent);
	static ztQuat nLerp(const ztQuat& q1, const ztQuat& q2, r32 percent);
	static ztQuat sLerp(const ztQuat& q1, const ztQuat&  q2, r32 percent);

	
	static const ztQuat identity;
};

// ------------------------------------------------------------------------------------------------

ztInline ztQuat operator+(const ztQuat& q1, const ztQuat& q2);
ztInline ztQuat operator-(const ztQuat& q1, const ztQuat& q2);
ztInline ztQuat operator*(const ztQuat& q1, const ztQuat& q2);
ztInline ztQuat operator/(const ztQuat& q1, const ztQuat& q2);
ztInline ztQuat operator*(const ztQuat& q1, r32 scale);
ztInline ztQuat operator/(const ztQuat& q1, r32 scale);

// ------------------------------------------------------------------------------------------------

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

r32 zt_sin(r32 x);
r32 zt_asin(r32 x);
r32 zt_cos(r32 y);
r32 zt_acos(r32 y);
r32 zt_tan(r32 r);
r32 zt_atan(r32 v);
r32 zt_atan2(r32 x, r32 y);
r32 zt_sqrt(r32 v);
r32 zt_pow(r32 v, r32 p);
r32 zt_exp(r32 v);

i32 zt_lerp(i32 v1, i32 v2, r32 percent);
i32 zt_unlerp(i32 v1, i32 v2, r32 percent);

// ------------------------------------------------------------------------------------------------

void zt_assert_raw(const char *condition_name, const char *file, int file_line);


// ------------------------------------------------------------------------------------------------
// Variant

enum ztVariant_Enum
{
	ztVariant_Invalid,

	ztVariant_i8,
	ztVariant_i16,
	ztVariant_i32,
	ztVariant_i64,
	ztVariant_u8,
	ztVariant_u16,
	ztVariant_u32,
	ztVariant_u64,
	ztVariant_r32,
	ztVariant_r64,
	ztVariant_voidp,
	ztVariant_vec2,
	ztVariant_vec3,
	ztVariant_vec4,
	ztVariant_mat4,
	ztVariant_quat,
};


struct ztVariant
{
	ztVariant_Enum type;

	union
	{
		i8    v_i8;
		i16   v_i16;
		i32   v_i32;
		i64   v_i64;
		u8    v_u8;
		u16   v_u16;
		u32   v_u32;
		u64   v_u64;
		r32   v_r32;
		r64   v_r64;
		void *v_voidp;
		r32   v_vec2[2];
		r32   v_vec3[3];
		r32   v_vec4[4];
		r32   v_mat4[16];
		r32   v_quat[4];
	};
};

struct ztVariantPointer
{
	ztVariant_Enum type;

	union
	{
		byte   *v_byte;
		i8     *v_i8;
		i16    *v_i16;
		i32    *v_i32;
		i64    *v_i64;
		u8     *v_u8;
		u16    *v_u16;
		u32    *v_u32;
		u64    *v_u64;
		r32    *v_r32;
		r64    *v_r64;
		void  **v_voidp;
		ztVec2 *v_vec2;
		ztVec3 *v_vec3;
		ztVec4 *v_vec4;
		ztMat4 *v_mat4;
		ztQuat *v_quat;
	};
};

ztInline ztVariant zt_variantMake_i8(i8 val);
ztInline ztVariant zt_variantMake_i16(i16 val);
ztInline ztVariant zt_variantMake_i32(i32 val);
ztInline ztVariant zt_variantMake_i64(i64 val);
ztInline ztVariant zt_variantMake_u8(u8 val);
ztInline ztVariant zt_variantMake_u16(u16 val);
ztInline ztVariant zt_variantMake_u32(u32 val);
ztInline ztVariant zt_variantMake_u64(u64 val);
ztInline ztVariant zt_variantMake_r32(r32 val);
ztInline ztVariant zt_variantMake_r64(r64 val);
ztInline ztVariant zt_variantMake_voidp(void *val);
ztInline ztVariant zt_variantMake_vec2(r32 val[2]);
ztInline ztVariant zt_variantMake_vec3(r32 val[3]);
ztInline ztVariant zt_variantMake_vec4(r32 val[4]);
ztInline ztVariant zt_variantMake_mat4(r32 val[16]);
ztInline ztVariant zt_variantMake_quat(r32 val[4]);

ztInline ztVariant zt_variantMake(ztVariantPointer *variant);

ztInline ztVariantPointer zt_variantPointerMake_i8(i8 *val);
ztInline ztVariantPointer zt_variantPointerMake_i16(i16 *val);
ztInline ztVariantPointer zt_variantPointerMake_i32(i32 *val);
ztInline ztVariantPointer zt_variantPointerMake_i64(i64 *val);
ztInline ztVariantPointer zt_variantPointerMake_u8(u8 *val);
ztInline ztVariantPointer zt_variantPointerMake_u16(u16 *val);
ztInline ztVariantPointer zt_variantPointerMake_u32(u32 *val);
ztInline ztVariantPointer zt_variantPointerMake_u64(u64 *val);
ztInline ztVariantPointer zt_variantPointerMake_r32(r32 *val);
ztInline ztVariantPointer zt_variantPointerMake_r64(r64 *val);
ztInline ztVariantPointer zt_variantPointerMake_voidp(void **val);
ztInline ztVariantPointer zt_variantPointerMake_vec2(r32 *val);
ztInline ztVariantPointer zt_variantPointerMake_vec3(r32 *val);
ztInline ztVariantPointer zt_variantPointerMake_vec4(r32 *val);
ztInline ztVariantPointer zt_variantPointerMake_mat4(r32 *val);
ztInline ztVariantPointer zt_variantPointerMake_quat(r32 *val);

ztInline i8     zt_variantGetAs_i8(ztVariant *variant);
ztInline i16    zt_variantGetAs_i16(ztVariant *variant);
ztInline i32    zt_variantGetAs_i32(ztVariant *variant);
ztInline i64    zt_variantGetAs_i64(ztVariant *variant);
ztInline u8     zt_variantGetAs_u8(ztVariant *variant);
ztInline u16    zt_variantGetAs_u16(ztVariant *variant);
ztInline u32    zt_variantGetAs_u32(ztVariant *variant);
ztInline u64    zt_variantGetAs_u64(ztVariant *variant);
ztInline r32    zt_variantGetAs_r32(ztVariant *variant);
ztInline r64    zt_variantGetAs_r64(ztVariant *variant);
ztInline void  *zt_variantGetAs_voidp(ztVariant *variant);
ztInline ztVec2 zt_variantGetAs_vec2(ztVariant *variant);
ztInline ztVec3 zt_variantGetAs_vec3(ztVariant *variant);
ztInline ztVec4 zt_variantGetAs_vec4(ztVariant *variant);
ztInline ztMat4 zt_variantGetAs_mat4(ztVariant *variant);
ztInline ztQuat zt_variantGetAs_quat(ztVariant *variant);

ztInline i8     *zt_variantGetAs_i8(ztVariantPointer *variant);
ztInline i16    *zt_variantGetAs_i16(ztVariantPointer *variant);
ztInline i32    *zt_variantGetAs_i32(ztVariantPointer *variant);
ztInline i64    *zt_variantGetAs_i64(ztVariantPointer *variant);
ztInline u8     *zt_variantGetAs_u8(ztVariantPointer *variant);
ztInline u16    *zt_variantGetAs_u16(ztVariantPointer *variant);
ztInline u32    *zt_variantGetAs_u32(ztVariantPointer *variant);
ztInline u64    *zt_variantGetAs_u64(ztVariantPointer *variant);
ztInline r32    *zt_variantGetAs_r32(ztVariantPointer *variant);
ztInline r64    *zt_variantGetAs_r64(ztVariantPointer *variant);
ztInline void  **zt_variantGetAs_voidp(ztVariantPointer *variant);
ztInline ztVec2 *zt_variantGetAs_vec2(ztVariantPointer *variant);
ztInline ztVec3 *zt_variantGetAs_vec3(ztVariantPointer *variant);
ztInline ztVec4 *zt_variantGetAs_vec4(ztVariantPointer *variant);
ztInline ztMat4 *zt_variantGetAs_mat4(ztVariantPointer *variant);
ztInline ztQuat *zt_variantGetAs_quat(ztVariantPointer *variant);

ztInline void zt_variantAssignValue(ztVariant *variant, ztVariant value);
ztInline void zt_variantAssignValue(ztVariantPointer *variant, ztVariant value);

ztInline ztVariant zt_variantLerp(ztVariant *beg, ztVariant *end, r32 pct);


// ------------------------------------------------------------------------------------------------
// function pointers

typedef i32 ztFunctionID;

ztFunctionID zt_registerFunctionPointer(const char *function_name, void *function);
void        *zt_functionPointer(ztFunctionID function_id);

#define ZT_FUNCTION_POINTER_REGISTER(function_name, function_decl)	\
        function_decl; \
        ztFunctionID function_name##_FunctionID = zt_registerFunctionPointer(#function_decl, function_name); \
        function_decl

// This must be accompanied by a call to ZT_FUNCTION_POINTER_REGISTER in a source file
#define ZT_FUNCTION_POINTER_REGISTER_EXTERN(function_name, function_decl)	\
        function_decl; \
        extern ztFunctionID function_name##_FunctionID; \
        function_decl

/*
	typedef void (myFunction_Func)(int, obj*);

	ZT_FUNCTION_POINTER_REGISTER(myFunction, void myFunction(int x, obj *o))
	{
		if(x > 0) {
			objFunction(x, o, myFunction_FunctionID);
		}
	}

	void objFunction(int x, obj *o, ztFunctionID function_id)
	{
		((myFunction_Func*)zt_functionPointer(function_id))(x - 1, o);
	}
*/


// ------------------------------------------------------------------------------------------------
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

#define ZT_FUNC_LOG_CALLBACK(name) void name(ztLogMessageLevel_Enum level, const char * message)
typedef ZT_FUNC_LOG_CALLBACK(zt_logCallback_Func);

void zt_logAddCallback(zt_logCallback_Func callback, ztLogMessageLevel_Enum min_level);
void zt_logRemoveCallback(zt_logCallback_Func callback);


// ------------------------------------------------------------------------------------------------
// memory

void zt_memSet(void *mem, i32 mem_len, byte value);
void zt_memCpy(void *dst, i32 dst_len, const void *src, i32 src_len);
int  zt_memCmp(const void *one, const void *two, i32 size);

// ------------------------------------------------------------------------------------------------

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

		const char *file;
		int file_line;

		allocation* next;
	};

	allocation *latest;
	ztMemoryArena *owner;
};

// ------------------------------------------------------------------------------------------------

ztMemoryArena *zt_memMakeArena(i32 total_size, ztMemoryArena *from = nullptr);
void zt_memFreeArena(ztMemoryArena *arena);

// arena can be null and if so, standard malloc/realloc/free will be used
void *zt_memAllocFromArena(ztMemoryArena *arena, i32 size);
void *zt_memAllocFromArena(ztMemoryArena *arena, i32 size, const char *file, int file_line);
void *zt_memRealloc(ztMemoryArena *arena, void *data, i32 size);
void zt_memFree(ztMemoryArena *arena, void *data);

void zt_memArenaClearAllocations(ztMemoryArena *arena, bool wipe_memory);

#define zt_memAlloc(arena, size) zt_memAllocFromArena(arena, size, __FILE__, __LINE__)

void zt_memDumpArena(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level = ztLogMessageLevel_Debug); // logs details including unfreed allocations
void zt_memDumpArenaDiagnostics(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level = ztLogMessageLevel_Debug);
bool zt_memArenaValidate(ztMemoryArena *arena);

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

#define zt_mallocStruct(type)				(type *)zt_memAllocGlobalFull(zt_sizeof(type), __FILE__, __LINE__)
#define zt_mallocStructArray(type, size)	(type *)zt_memAllocGlobalFull(zt_sizeof(type) * (size), __FILE__, __LINE__)

#define zt_mallocStructArena(type, arena)				(type *)zt_memAllocFromArena(arena, zt_sizeof(type), __FILE__, __LINE__)
#define zt_mallocStructArrayArena(type, size, arena)	(type *)zt_memAllocFromArena(arena, zt_sizeof(type) * (size), __FILE__, __LINE__)

#define zt_free(memory)	zt_memFree(zt_memGetGlobalArena(), (void*)memory)
#define zt_freeArena(memory, arena) zt_memFree(arena, (void*)memory)


// ------------------------------------------------------------------------------------------------
// string functions

#define ztStrPosNotFound	-1

#define zt_strMakePrintf(varname, varsize, format, ...)	char varname[varsize] = {0}; zt_strPrintf(varname, varsize, format, __VA_ARGS__);

bool zt_strValid(const char *s, const char **invalid_ch = nullptr);
const char *zt_strCodepoint(const char *s, i32* code_point);
i32 zt_strCodepoint(const char *s, int pos);

bool zt_strEquals(const char *s1, const char *s2, bool test_case = true);
bool zt_strEquals(const char *s1, int s1_len, const char *s2, int s2_len, bool test_case = true);
int zt_strLen(const char *s);
int zt_strSize(const char *s); // size in bytes including null terminator
const char *zt_strMoveForward(const char *s, int characters);

int zt_strCmp(const char *s1, const char *s2);
int zt_striCmp(const char *s1, const char *s2);

int zt_strCmp(const char *s1, int s1_len, const char *s2, int s2_len);
int zt_striCmp(const char *s1, int s1_len, const char *s2, int s2_len);

int zt_strCpy(char *scopy, int scopy_len, const char *sfrom);
int zt_strCpy(char *scopy, int scopy_len, const char *sfrom, int sfrom_len);

int zt_strCat(char *scopy, int scopy_len, const char *sfrom);
int zt_strCat(char *scopy, int scopy_len, const char *sfrom, int sfrom_len);

bool zt_strIsInt(char *s);
bool zt_strIsInt(char *s, int s_len);
bool zt_strIsIntHex(char *s);
bool zt_strIsIntHex(char *s, int s_len);
bool zt_strIsReal32(char *s);
bool zt_strIsReal32(char *s, int s_len);
bool zt_strIsReal64(char *s);
bool zt_strIsReal64(char *s, int s_len);

i32 zt_strToInt(const char *s, i32 def, bool *success = nullptr);
i32 zt_strToInt(const char *s, int s_len, i32 def, bool *success = nullptr);
u32 zt_strToIntHex(const char *s, u32 def, bool *success = nullptr);
u32 zt_strToIntHex(const char *s, int s_len, u32 def, bool *success = nullptr);

r32 zt_strToReal32(const char *s, r32 def, bool* success = nullptr);
r32 zt_strToReal32(const char *s, int s_len, r32 def, bool* success = nullptr);
r64 zt_strToReal64(const char *s, r64 def, bool* success = nullptr);
r64 zt_strToReal64(const char *s, int s_len, r64 def, bool* success = nullptr);

u32 zt_strHash(const char *s);

const char *zt_strFind(const char *haystack, const char *needle);
const char *zt_strFind(const char *haystack, int haystack_len, const char *needle);
int zt_strFindPos(const char *haystack, const char *needle, int start_pos);
int zt_strFindPos(const char *haystack, int haystack_len, const char *needle, int start_pos);

const char *zt_strFindLast(const char *haystack, const char *needle);
const char *zt_strFindLast(const char *haystack, int haystack_len, const char *needle);
int zt_strFindLastPos(const char *haystack, const char *needle, int start_pos = -1);
int zt_strFindLastPos(const char *haystack, int haystack_len, const char *needle, int start_pos = -1);

const char *zt_striFind(const char *haystack, const char *needle);
const char *zt_striFind(const char *haystack, int haystack_len, const char *needle);
int zt_striFindPos(const char *haystack, const char *needle, int start_pos);
int zt_striFindPos(const char *haystack, int haystack_len, const char *needle, int start_pos);

const char *zt_striFindLast(const char *haystack, const char *needle);
const char *zt_striFindLast(const char *haystack, int haystack_len, const char *needle);
int zt_striFindLastPos(const char *haystack, const char *needle, int start_pos = -1);
int zt_striFindLastPos(const char *haystack, int haystack_len, const char *needle, int start_pos = -1);

int zt_strCount(const char *haystack, const char *needle);
int zt_strCount(const char *haystack, int haystack_len, const char *needle);
int zt_striCount(const char *haystack, const char *needle);
int zt_striCount(const char *haystack, int haystack_len, const char *needle);

bool zt_strStartsWith(const char *s, const char *starts_with);
bool zt_strStartsWith(const char *s, int s_len, const char *starts_with, int sw_len);
bool zt_strEndsWith(const char *s, const char *ends_with);
bool zt_strEndsWith(const char *s, int s_len, const char *ends_with, int ew_len);

bool zt_striStartsWith(const char *s, const char *starts_with);
bool zt_striStartsWith(const char *s, int s_len, const char *starts_with, int sw_len);
bool zt_striEndsWith(const char *s, const char *ends_with);
bool zt_striEndsWith(const char *s, int s_len, const char *ends_with, int ew_len);

const char *zt_strJumpToNextToken(const char *s); // any non-alphanumeric character breaks up tokens
const char *zt_strJumpToNextToken(const char *s, int s_len);

int zt_strGetNextTokenPos(const char *s);
int zt_strGetNextTokenPos(const char *s, int s_len);

const char *zt_strJumpToNextLine(const char *s);
const char *zt_strJumpToNextLine(const char *s, int s_len);

int zt_strGetNextLinePos(const char *s);
int zt_strGetNextLinePos(const char *s, int s_len);

int zt_strGetBetween(char *buffer, int buffer_len, const char *s, const char *beg, const char *end, int beg_offset = 0, int end_offset = 0);
int zt_strGetBetween(char *buffer, int buffer_len, const char *s, int s_len, const char *beg, const char *end, int beg_offset = 0, int end_offset = 0);

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

int zt_strConvertToUTF16(const char* s, int s_len, u16* buffer, int buffer_size);

// ------------------------------------------------------------------------------------------------

// ztString is used to represent a string where the length of the string is inserted in memory right before the character pointer.
// ztStrings can be passed into all string functions, using zt_stringSize() to get the length of the string

typedef char* ztString;

ztString zt_stringMake(int size, ztMemoryArena *arena = nullptr);
ztString zt_stringResize(ztString string, int size, ztMemoryArena *arena = nullptr);
ztString zt_stringMakeFrom(const char *str, ztMemoryArena *arena = nullptr);
ztString zt_stringMakeFrom(const char *str, int s_len, ztMemoryArena *arena = nullptr);
ztString zt_stringOverwrite(ztString string, const char *str, ztMemoryArena *arena = nullptr);
void zt_stringFree(ztString string, ztMemoryArena *arena = nullptr);
int zt_stringSize(ztString string);


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

// ------------------------------------------------------------------------------------------------

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

// ------------------------------------------------------------------------------------------------

#define ztFileMaxPath	1024 * 4	// handy constant for path sizes on the stack

#if defined(ZT_WINDOWS)
#define ztFilePathSeparator	'\\'
#define ztFilePathSeparatorStr	"\\"
#else
#define ztFilePathSeparator '/'
#define ztFilePathSeparatorStr	"/"
#endif

// ------------------------------------------------------------------------------------------------

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
i32 zt_fileGetFileExt(const char *file_name, char *buffer, int buffer_size);	// file extension only

i32 zt_fileGetAppBin(char *buffer, int buffer_size);
i32 zt_fileGetAppPath(char *buffer, int buffer_size);
i32 zt_fileGetUserPath(char *buffer, int buffer_size, char *app_name);
i32 zt_fileGetCurrentPath(char *buffer, int buffer_size);
void zt_fileSetCurrentPath(const char *path);

i32 zt_fileGetFileInOtherFileDirectory(char * buffer, int buffer_size, char *file_only, char *other_file_full_path);	// will expand the file_only to a full path, using the path of the other_file_full_path
i32 zt_fileConcatFileToPath(char *buffer, int buffer_size, const char *path, const char *file);

bool zt_fileExists(const char *file_name);
bool zt_fileDelete(const char *file_name);
bool zt_fileCopy(const char *orig_file, const char *new_file);
bool zt_fileRename(const char *orig_file, const char *new_file);
i32 zt_fileSize(const char *file_name);
bool zt_fileModified(const char *file_name, i32 *year, i32 *month, i32 *day, i32 *hour, i32 *minute, i32 *second, i32 *ms);
bool zt_fileModified(const char *file_name, i64* date_time);

i32 zt_fileRead(ztFile *file, void *buffer, i32 buffer_size);
ztInline bool zt_fileRead(ztFile *file, i8 *value)		{ return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, i16 *value)		{ return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, i32 *value)		{ return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, i64 *value)		{ return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, u8 *value)		{ return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, u16 *value)		{ return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, u32 *value)		{ return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, u64 *value)		{ return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, r32 *value)		{ return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead(ztFile *file, r64 *value)		{ return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }

i32 zt_fileWrite(ztFile *file, const void *buffer, i32 buffer_size);
ztInline bool zt_fileWrite(ztFile *file, i8  value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, i16 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, i32 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, i64 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, u8  value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, u16 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, u32 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, u64 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, r32 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, r64 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite(ztFile *file, const char *value){ return zt_strLen(value) == zt_fileWrite(file,  value, zt_strLen(value)); }

bool zt_fileWritef(ztFile *file, const char *format, ...);

void zt_fileFlush(ztFile *file);

void *zt_readEntireFile(const char *file_name, i32 *file_size, bool discard_utf_bom = false, ztMemoryArena *arena = zt_memGetGlobalArena());
i32 zt_readEntireFile(const char *file_name, void *buffer, i32 buffer_size, bool discard_utf_bom = false);
i32 zt_writeEntireFile(const char *file_name, void *data, i32 data_size, ztMemoryArena *arena = zt_memGetGlobalArena());

bool zt_directoryExists(const char *dir);
bool zt_directoryMake(const char *dir);
bool zt_directoryDelete(const char *dir, bool force);

i32 zt_getDirectorySubs(const char *directory, char *buffer, i32 buffer_size, bool recursive); // returns \n delimited string of sub directories
i32 zt_getDirectoryFiles(const char *directory, char *buffer, i32 buffer_size, bool recursive); // returns \n delimited string of files


// ------------------------------------------------------------------------------------------------
// directory monitoring
//
// This allows directories to be monitored for new files and directories and modifications to files
// The most efficient method for doing so per platform is used
//

enum ztDirectoryMonitorFlags_Enum
{
	ztDirectoryMonitorFlags_New    = (1<<0),
	ztDirectoryMonitorFlags_Rename = (1<<1),
	ztDirectoryMonitorFlags_Modify = (1<<2),

	ztDirectoryMonitorFlags_All = ztDirectoryMonitorFlags_New | ztDirectoryMonitorFlags_Rename | ztDirectoryMonitorFlags_Modify,
};

struct ztDirectoryMonitor
{
#if defined(ZT_WINDOWS)
	pointer io;
	pointer file;
	i32     flags;
	byte    file_buffer[ztPointerSize + 12 * 256]; // ztPointerSize + 12 == sizeof(FILE_NOTIFY_INFORMATION)
	byte    overlapped[ztPointerSize * 3 + 8]; // sizeof(OVERLAPPED)
	bool    recursive;
#endif
};


bool zt_directoryMonitor(ztDirectoryMonitor *dir_mon, const char *directory, bool recursive, i32 flags = ztDirectoryMonitorFlags_All);
void zt_directoryStopMonitor(ztDirectoryMonitor *dir_mon);
bool zt_directoryMonitorHasChanged(ztDirectoryMonitor *dir_mon);


// ------------------------------------------------------------------------------------------------
// threading

typedef i32 ztThreadID;

// ------------------------------------------------------------------------------------------------

struct ztThread;

// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_THREAD_EXIT(name) bool (name)(void *user_data)
typedef ZT_FUNC_THREAD_EXIT(ztThreadExit_Func);

#define ZT_FUNC_THREAD(name)	int (name)(ztThreadID thread_id, void *user_data, ztThreadExit_Func *exit_test, void *exit_test_user_data)
typedef ZT_FUNC_THREAD(ztThread_Func);

// ------------------------------------------------------------------------------------------------

ztThread  *zt_threadMake(ztThread_Func *thread_func, void *user_data, ztThreadExit_Func *exit_test, void *exit_test_user_data, ztThreadID *out_thread_id);
void       zt_threadFree(ztThread *thread);
void       zt_threadJoin(ztThread *thread); // pause execution of the current thread until the given thread is complete
bool       zt_threadIsRunning(ztThread *thread);
ztThreadID zt_threadGetCurrentID();        // get the id of the current thread
void       zt_threadYield();

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

struct ztThreadMutex;

// ------------------------------------------------------------------------------------------------

ztThreadMutex *zt_threadMutexMake();
void           zt_threadMutexFree(ztThreadMutex *mutex);

void           zt_threadMutexLock(ztThreadMutex *mutex);
void           zt_threadMutexUnlock(ztThreadMutex *mutex);

// ------------------------------------------------------------------------------------------------

struct ztThreadMutexLocker
{
	ztThreadMutex *mutex;

	ztThreadMutexLocker(ztThreadMutex *_mutex) : mutex(_mutex) {
		zt_threadMutexLock(mutex);
	}

	~ztThreadMutexLocker() {
		zt_threadMutexUnlock(mutex);
	}
};


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

struct ztThreadMonitor;

// ------------------------------------------------------------------------------------------------

ztThreadMonitor *zt_threadMonitorMake();
void             zt_threadMonitorFree(ztThreadMonitor *monitor);

void             zt_threadMonitorWaitForSignal(ztThreadMonitor *monitor);
void             zt_threadMonitorTriggerSignal(ztThreadMonitor *monitor);
void             zt_threadMonitorReset(ztThreadMonitor *monitor);


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

typedef long volatile ztAtomicInt;

i32 zt_atomicIntInc(ztAtomicInt *atomic_int);
i32 zt_atomicIncDec(ztAtomicInt *atomic_int);
i32 zt_atomicIntSet(ztAtomicInt *atomic_int, i32 value);
i32 zt_atomicIntGet(ztAtomicInt *atomic_int);
i32 zt_atomicIntAnd(ztAtomicInt *atomic_int, i32 and_val);
i32 zt_atomicIntOr (ztAtomicInt *atomic_int, i32 or_val);
i32 zt_atomicIntXor(ztAtomicInt *atomic_int, i32 xor_val);

typedef long volatile ztAtomicBool;

bool zt_atomicBoolSet(ztAtomicBool *atomic_bool, bool value);
bool zt_atomicBoolGet(ztAtomicBool *atomic_bool);
bool zt_atomicBoolToggle(ztAtomicBool *atomic_bool);

// ------------------------------------------------------------------------------------------------


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

// ------------------------------------------------------------------------------------------------

#define ztSerialIdentifierMaxSize	128

// ------------------------------------------------------------------------------------------------

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

// ------------------------------------------------------------------------------------------------

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

	union {
		i32 mt_buffer[ztRandom_MTLen];

		struct {
			i32 _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100,
				_101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127, _128, _129, _130, _131, _132, _133, _134, _135, _136, _137, _138, _139, _140, _141, _142, _143, _144, _145, _146, _147, _148, _149, _150, _151, _152, _153, _154, _155, _156, _157, _158, _159, _160, _161, _162, _163, _164, _165, _166, _167, _168, _169, _170, _171, _172, _173, _174, _175, _176, _177, _178, _179, _180, _181, _182, _183, _184, _185, _186, _187, _188, _189, _190, _191, _192, _193, _194, _195, _196, _197, _198, _199, _200,
				_201, _202, _203, _204, _205, _206, _207, _208, _209, _210, _211, _212, _213, _214, _215, _216, _217, _218, _219, _220, _221, _222, _223, _224, _225, _226, _227, _228, _229, _230, _231, _232, _233, _234, _235, _236, _237, _238, _239, _240, _241, _242, _243, _244, _245, _246, _247, _248, _249, _250, _251, _252, _253, _254, _255, _256, _257, _258, _259, _260, _261, _262, _263, _264, _265, _266, _267, _268, _269, _270, _271, _272, _273, _274, _275, _276, _277, _278, _279, _280, _281, _282, _283, _284, _285, _286, _287, _288, _289, _290, _291, _292, _293, _294, _295, _296, _297, _298, _299, _300,
				_301, _302, _303, _304, _305, _306, _307, _308, _309, _310, _311, _312, _313, _314, _315, _316, _317, _318, _319, _320, _321, _322, _323, _324, _325, _326, _327, _328, _329, _330, _331, _332, _333, _334, _335, _336, _337, _338, _339, _340, _341, _342, _343, _344, _345, _346, _347, _348, _349, _350, _351, _352, _353, _354, _355, _356, _357, _358, _359, _360, _361, _362, _363, _364, _365, _366, _367, _368, _369, _370, _371, _372, _373, _374, _375, _376, _377, _378, _379, _380, _381, _382, _383, _384, _385, _386, _387, _388, _389, _390, _391, _392, _393, _394, _395, _396, _397, _398, _399, _400,
				_401, _402, _403, _404, _405, _406, _407, _408, _409, _410, _411, _412, _413, _414, _415, _416, _417, _418, _419, _420, _421, _422, _423, _424, _425, _426, _427, _428, _429, _430, _431, _432, _433, _434, _435, _436, _437, _438, _439, _440, _441, _442, _443, _444, _445, _446, _447, _448, _449, _450, _451, _452, _453, _454, _455, _456, _457, _458, _459, _460, _461, _462, _463, _464, _465, _466, _467, _468, _469, _470, _471, _472, _473, _474, _475, _476, _477, _478, _479, _480, _481, _482, _483, _484, _485, _486, _487, _488, _489, _490, _491, _492, _493, _494, _495, _496, _497, _498, _499, _500,
				_501, _502, _503, _504, _505, _506, _507, _508, _509, _510, _511, _512, _513, _514, _515, _516, _517, _518, _519, _520, _521, _522, _523, _524, _525, _526, _527, _528, _529, _530, _531, _532, _533, _534, _535, _536, _537, _538, _539, _540, _541, _542, _543, _544, _545, _546, _547, _548, _549, _550, _551, _552, _553, _554, _555, _556, _557, _558, _559, _560, _561, _562, _563, _564, _565, _566, _567, _568, _569, _570, _571, _572, _573, _574, _575, _576, _577, _578, _579, _580, _581, _582, _583, _584, _585, _586, _587, _588, _589, _590, _591, _592, _593, _594, _595, _596, _597, _598, _599, _600,
				_601, _602, _603, _604, _605, _606, _607, _608, _609, _610, _611, _612, _613, _614, _615, _616, _617, _618, _619, _620, _621, _622, _623, _624;
		};
	};
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
// external processes

int zt_processRun(const char *command);
int zt_processRun(const char *command, char *output_buffer, int output_buffer_size, int *output_buffer_written = nullptr);


// ------------------------------------------------------------------------------------------------
// time

r64 zt_getTime(); // seconds since app started
void zt_sleep(r32 seconds);

struct ztDate
{
	int year, month, day, hour, minute, second;
};

void zt_getDate(int *year, int *month, int *day, int *hour, int *minute, int *second);
ztDate zt_getDate();

bool operator<(ztDate& d1, ztDate& d2);
bool operator>(ztDate& d1, ztDate& d2);
bool operator==(ztDate& d1, ztDate& d2);
bool operator!=(ztDate& d1, ztDate& d2);

// ------------------------------------------------------------------------------------------------

class ztBlockProfiler
{
public:
	ztBlockProfiler(char *_block_name, ztLogMessageLevel_Enum _log_level = ztLogMessageLevel_Verbose) : block_name(_block_name), log_level(_log_level) {
		time_beg = zt_getTime();
	}

	~ztBlockProfiler() {
		zt_logMessage(log_level, "%s took %f ms to execute", block_name, (r32)(zt_getTime() - time_beg) * 1000.f);
	}

	char *block_name;
	ztLogMessageLevel_Enum log_level;
	r64 time_beg;
};


// ------------------------------------------------------------------------------------------------
// linked lists

#define zt_singleLinkAddToEnd(item_first_ptr, item_add_ptr) \
	{ \
		item_add_ptr->next = nullptr; \
		auto *prev = item_first_ptr; \
		while(prev != nullptr && prev->next != nullptr) { \
			prev = prev->next; \
						} \
		if(prev != nullptr) { \
			prev->next = item_add_ptr; \
		} \
		else { \
			item_first_ptr = item_add_ptr; \
		} \
	}

#define zt_singleLinkAddToBegin(item_first_ptr, item_add_ptr) \
	{ \
		item_add_ptr->next = item_first_ptr; \
		item_first_ptr = item_add_ptr; \
	}


#define zt_linkFind(item_first_ptr, item_find_ptr, condition) \
	{ \
		item_find_ptr = item_first_ptr; \
		while(item_find_ptr != nullptr) { \
			if(condition) { break; } \
			item_find_ptr = item_find_ptr->next; \
		} \
	}

#define zt_linkGetLast(item_first_ptr, item_find_ptr) \
	{ \
		item_find_ptr = item_first_ptr; \
		while(item_find_ptr != nullptr) { \
			if(item_find_ptr->next == nullptr) break; \
		} \
	}


// ------------------------------------------------------------------------------------------------
// arrays

#define zt_arrayResizeArenaCopy(arr, type, old_size, new_size, arena) \
	{ \
		type *resized = zt_mallocStructArrayArena(type, new_size, arena); \
		zt_memCpy(resized, new_size * zt_sizeof(type), arr, old_size * zt_sizeof(type)); \
		type *copy = arr; \
		arr = resized; \
		zt_freeArena(copy, arena); \
	}

// ------------------------------------------------------------------------------------------------

#define zt_arrayResizeArenaNoCopy(arr, type, new_size, arena) \
	{ \
		zt_freeArena(arr, arena); \
		arr = zt_mallocStructArrayArena(type, new_size, arena); \
	}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// inlined functions

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
	if (appr >= var) 
		return zt_min(var + by, appr);

	return zt_max(var - by, appr);
}

// ------------------------------------------------------------------------------------------------

ztInline i32 zt_lerp(i32 v1, i32 v2, r32 percent)
{
	return v1 + (i32)((v2 - v1) * percent);
}

// ------------------------------------------------------------------------------------------------

ztInline i32 zt_unlerp(i32 v1, i32 v2, r32 value)
{
	return (v2 - v1) == 0 ? 0 : (i32)((value - v1) / (r32)(v2 - v1));
}

// ------------------------------------------------------------------------------------------------

ztInline void zt_assert_raw(const char *condition_name, const char *file, int file_line)
{
	zt_logCritical("assert failed: '%s' in file %s (%d)", condition_name, file, file_line);
	//zt_debugOnly(__asm { int 3 });
	zt_debugOnly(__debugbreak());
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

ztInline ztVec2 operator*(r32 scale, const ztVec2& v1)
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
	r32 tx = x - v.x, ty = y - v.y, tz = z - v.z; 
	return zt_sqrt(tx * tx + ty * ty + tz * tz);
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
	return zt_real32Eq(len, 0) ? *this : ztVec3(x / len, y / len, z / len);
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

ztInline ztVec3 operator*(r32 scale, const ztVec3& v1)
{
	return ztVec3(v1.x * scale, v1.y * scale, v1.z * scale);
}

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

ztInline ztVec4 operator*(r32 scale, const ztVec4& v1)
{
	return ztVec4(v1.x * scale, v1.y * scale, v1.z * scale, v1.w * scale);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInline ztMat4 operator*(const ztMat4& m1, const ztMat4& m2)
{
	return m1.getMultiply(m2);
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec3 operator*(const ztMat4& m, const ztVec3& v)
{
	return m.getMultiply(v);
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInline ztQuat& ztQuat::operator+=(const ztQuat& q)
{
	xyzw += q.xyzw;
	return *this;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat& ztQuat::operator-=(const ztQuat& q)
{
	xyzw -= q.xyzw;
	return *this;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat& ztQuat::operator*=(const ztQuat& q)
{
	/*
	d->x = q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y;
	d->y = q0.w * q1.y - q0.x * q1.z + q0.y * q1.w + q0.z * q1.x;
	d->z = q0.w * q1.z + q0.x * q1.y - q0.y * q1.x + q0.z * q1.w;
	d->w = q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
	*/
	r32 tx = w * q.x + x * q.w + y * q.z - z * q.y;
	r32 ty = w * q.y - x * q.z + y * q.w + z * q.x;
	r32 tz = w * q.z + x * q.y - y * q.x + z * q.w;
	r32 tw = w * q.w - x * q.x - y * q.y - z * q.z;

	x = tx; y = ty; z = tz; w = tw;
	return *this;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat& ztQuat::operator/=(const ztQuat& q)
{
	ztQuat inv = q.getInverse();
	*this *= inv;
	return *this;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat& ztQuat::operator*=(r32 s)
{
	xyzw *= s;
	return *this;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat& ztQuat::operator/=(r32 s)
{
	xyzw *= 1.f / s;
	return *this;
}

// ------------------------------------------------------------------------------------------------

ztInline r32 ztQuat::dot(const ztQuat& q) const
{
	return xyz.dot(q.xyz) + (w * q.w);
}

// ------------------------------------------------------------------------------------------------

ztInline r32 ztQuat::magnitude() const
{
	return zt_sqrt(dot(*this));
}

// ------------------------------------------------------------------------------------------------

ztInline void ztQuat::normalize()
{
	*this /= magnitude();
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat ztQuat::getNormalize() const
{
	ztQuat q = *this;
	q.normalize();
	return q;
}

// ------------------------------------------------------------------------------------------------

ztInline void ztQuat::conjugate()
{
	x = -x;
	y = -y;
	z = -z;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat ztQuat::getConjugate() const
{
	return ztQuat(-x, -y, -z, w);
}

// ------------------------------------------------------------------------------------------------

ztInline void ztQuat::inverse()
{
	ztQuat conj = getConjugate();
	r32 d = dot(*this);
	if (d != 0) {
		conj /= d;
	}
	*this = conj;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat ztQuat::getInverse() const
{
	ztQuat q = *this;
	q.inverse();
	return q;
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec3 ztQuat::axis() const
{
	ztQuat n = getNormalize();
	r32 s = zt_sin(zt_acos(w));
	if (s == 0) {
		return ztVec3::zero;
	}
	return n.xyz * (1.f / s);
}

// ------------------------------------------------------------------------------------------------

ztInline r32 ztQuat::angle() const
{
	r32 mag = magnitude();
	if (mag == 0) {
		return 0;
	}

	r32 c = w * (1.f / mag);
	return w * zt_acos(c);
}

// ------------------------------------------------------------------------------------------------

ztInline void ztQuat::axisAngle(ztVec3 *_axis, r32 *_angle) const
{
	*_axis = axis();
	*_angle = angle();
}

// ------------------------------------------------------------------------------------------------
ztInline ztVec3 ztQuat::euler() const
{
	return ztVec3(zt_radiansToDegrees(zt_atan2(1.f * y * z + w * x, w * w - x * x - y * y + z * z)),
	              zt_radiansToDegrees(zt_asin(-1.f * (x * z - w * y))),
	              zt_radiansToDegrees(zt_atan2(1.f * x * y + z * w, x * x + w * w - y * y - z * z)));
}

ztInline void ztQuat::rotatePosition(ztVec3 *vec) const
{
	ztVec3 t = xyz.cross(*vec) * 2.f;
	ztVec3 p = xyz.cross(t);
	*vec = (t * w) + *vec + p;
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec3 ztQuat::rotatePosition(const ztVec3 &vec) const
{
	ztVec3 r = vec;
	rotatePosition(&r);
	return r;
}

// ------------------------------------------------------------------------------------------------

ztInline ztVec3 ztQuat::rotatePosition(r32 x, r32 y, r32 z) const
{
	ztVec3 r(x, y, z);
	rotatePosition(&r);
	return r;
}

// ------------------------------------------------------------------------------------------------

ztInline void ztQuat::rotatePosition(r32 *x, r32 *y, r32 *z) const
{
	ztVec3 r(*x, *y, *z);
	rotatePosition(&r);
	*x = r.x;
	*y = r.y;
	*z = r.z;
}

// ------------------------------------------------------------------------------------------------

ztInline ztMat4 ztQuat::convertToMat4() const
{
	ztMat4 r;
	convertToMat4(&r);
	return r;
}

// ------------------------------------------------------------------------------------------------

ztInline void ztQuat::convertToMat4(ztMat4 *mat) const
{
	r32 xx = x * x, yy = y * y, zz = z * z;
	r32 xy = x * y, xz = x * z, yz = y * z;
	r32 wx = w * x, wy = w * y, wz = w * z;

	mat->values[ztMat4_Col0Row0] = 1.f - 2.f * (yy + zz);
	mat->values[ztMat4_Col0Row1] =       2.f * (xy + wz);
	mat->values[ztMat4_Col0Row2] =       2.f * (xz - wy);
	mat->values[ztMat4_Col0Row3] = 0;

	mat->values[ztMat4_Col1Row0] =       2.f * (xy - wz);
	mat->values[ztMat4_Col1Row1] = 1.f - 2.f * (xx + zz);
	mat->values[ztMat4_Col1Row2] =       2.f * (yz + wx);
	mat->values[ztMat4_Col1Row3] = 0;

	mat->values[ztMat4_Col2Row0] =       2.f * (xz + wy);
	mat->values[ztMat4_Col2Row1] =       2.f * (yz - wx);
	mat->values[ztMat4_Col2Row2] = 1.f - 2.f * (xx + yy);
	mat->values[ztMat4_Col2Row3] = 0;

	mat->values[ztMat4_Col3Row0] = 0;
	mat->values[ztMat4_Col3Row1] = 0;
	mat->values[ztMat4_Col3Row2] = 0;
	mat->values[ztMat4_Col3Row3] = 1;
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztQuat ztQuat::lerp(const ztQuat& q1, const ztQuat& q2, r32 percent)
{
	return ztQuat(ztVec4::lerp(q1.xyzw, q2.xyzw, percent));
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztQuat ztQuat::nLerp(const ztQuat& q1, const ztQuat& q2, r32 percent)
{
	return lerp(q1, q2, percent).getNormalize();
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztQuat ztQuat::sLerp(const ztQuat& q1, const ztQuat&  q2, r32 percent)
{
	ztQuat z = q2;
	r32 cos_theta = q1.dot(q2);

	if (cos_theta < 0.f) {
		z = ztQuat(-q2.x, -q2.y, -q2.z, -q2.w);
		cos_theta = -cos_theta;
	}

	if (cos_theta > 1.0f) {
		return lerp(q1, q2, percent);
	}

	r32 angle = zt_acos(cos_theta);

	r32 s1 = zt_sin(1.f - percent * angle);
	r32 s0 = zt_sin(percent * angle);
	r32 sa = zt_sin(angle);
	r32 is = sa == 0 ? 0 : 1.f / sa;

	ztQuat x = z * s1;
	ztQuat y = z * s0;
	return (x + y) * is;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat operator+(const ztQuat& q1, const ztQuat& q2)
{
	ztQuat r = q1;
	r += q2;
	return r;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat operator-(const ztQuat& q1, const ztQuat& q2)
{
	ztQuat r = q1;
	r -= q2;
	return r;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat operator*(const ztQuat& q1, const ztQuat& q2)
{
	ztQuat r = q1;
	r *= q2;
	return r;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat operator/(const ztQuat& q1, const ztQuat& q2)
{
	ztQuat r = q1;
	r /= q2;
	return r;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat operator*(const ztQuat& q1, r32 scale)
{
	ztQuat r = q1;
	r *= scale;
	return r;
}

// ------------------------------------------------------------------------------------------------

ztInline ztQuat operator/(const ztQuat& q1, r32 scale)
{
	ztQuat r = q1;
	r /= scale;
	return r;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInline ztVariant        zt_variantMake_i8        (i8            val)          { ztVariant var; var.type = ztVariant_i8   ; var.v_i8    = val; return var; }
ztInline ztVariant        zt_variantMake_i16       (i16           val)          { ztVariant var; var.type = ztVariant_i16  ; var.v_i16   = val; return var; }
ztInline ztVariant        zt_variantMake_i32       (i32           val)          { ztVariant var; var.type = ztVariant_i32  ; var.v_i32   = val; return var; }
ztInline ztVariant        zt_variantMake_i64       (i64           val)          { ztVariant var; var.type = ztVariant_i64  ; var.v_i64   = val; return var; }
ztInline ztVariant        zt_variantMake_u8        (u8            val)          { ztVariant var; var.type = ztVariant_u8   ; var.v_u8    = val; return var; }
ztInline ztVariant        zt_variantMake_u16       (u16           val)          { ztVariant var; var.type = ztVariant_u16  ; var.v_u16   = val; return var; }
ztInline ztVariant        zt_variantMake_u32       (u32           val)          { ztVariant var; var.type = ztVariant_u32  ; var.v_u32   = val; return var; }
ztInline ztVariant        zt_variantMake_u64       (u64           val)          { ztVariant var; var.type = ztVariant_u64  ; var.v_u64   = val; return var; }
ztInline ztVariant        zt_variantMake_r32       (r32           val)          { ztVariant var; var.type = ztVariant_r32  ; var.v_r32   = val; return var; }
ztInline ztVariant        zt_variantMake_r64       (r64           val)          { ztVariant var; var.type = ztVariant_r64  ; var.v_r64   = val; return var; }
ztInline ztVariant        zt_variantMake_voidp     (void         *val)          { ztVariant var; var.type = ztVariant_voidp; var.v_voidp = val; return var; }
ztInline ztVariant        zt_variantMake_vec2      (const ztVec2& val)          { ztVariant var; var.type = ztVariant_vec2 ; zt_fize(val.values) var.v_vec2[i] = val.values[i]; return var; }
ztInline ztVariant        zt_variantMake_vec3      (const ztVec3& val)          { ztVariant var; var.type = ztVariant_vec3 ; zt_fize(val.values) var.v_vec3[i] = val.values[i]; return var; }
ztInline ztVariant        zt_variantMake_vec4      (const ztVec4& val)          { ztVariant var; var.type = ztVariant_vec4 ; zt_fize(val.values) var.v_vec4[i] = val.values[i]; return var; }
ztInline ztVariant        zt_variantMake_mat4      (const ztMat4& val)          { ztVariant var; var.type = ztVariant_mat4 ; zt_fize(val.values) var.v_mat4[i] = val.values[i]; return var; }
ztInline ztVariant        zt_variantMake_quat      (const ztQuat& val)          { ztVariant var; var.type = ztVariant_quat ; zt_fize(val.values) var.v_quat[i] = val.values[i]; return var; }

ztInline ztVariant        zt_variantMake(ztVariantPointer *variant)
{
	switch (variant->type)
	{
		case ztVariant_i8   : return zt_variantMake_i8   (*variant->v_i8);
		case ztVariant_i16  : return zt_variantMake_i16  (*variant->v_i16);
		case ztVariant_i32  : return zt_variantMake_i32  (*variant->v_i32);
		case ztVariant_i64  : return zt_variantMake_i64  (*variant->v_i64);
		case ztVariant_u8   : return zt_variantMake_u8   (*variant->v_u8);
		case ztVariant_u16  : return zt_variantMake_u16  (*variant->v_u16);
		case ztVariant_u32  : return zt_variantMake_u32  (*variant->v_u32);
		case ztVariant_u64  : return zt_variantMake_u64  (*variant->v_u64);
		case ztVariant_r32  : return zt_variantMake_r32  (*variant->v_r32);
		case ztVariant_r64  : return zt_variantMake_r64  (*variant->v_r64);
		case ztVariant_voidp: return zt_variantMake_voidp(*variant->v_voidp);
		case ztVariant_vec2 : return zt_variantMake_vec2 (*variant->v_vec2);
		case ztVariant_vec3 : return zt_variantMake_vec3 (*variant->v_vec3);
		case ztVariant_vec4 : return zt_variantMake_vec4 (*variant->v_vec4);
		case ztVariant_mat4 : return zt_variantMake_mat4 (*variant->v_mat4);
		case ztVariant_quat : return zt_variantMake_quat (*variant->v_quat);
	}

	ztVariant v = { ztVariant_Invalid }; return v;
}

ztInline ztVariantPointer zt_variantPointerMake_i8    (i8           *val)          { ztVariantPointer var; var.type = ztVariant_i8   ; var.v_i8    = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_i16   (i16          *val)          { ztVariantPointer var; var.type = ztVariant_i16  ; var.v_i16   = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_i32   (i32          *val)          { ztVariantPointer var; var.type = ztVariant_i32  ; var.v_i32   = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_i64   (i64          *val)          { ztVariantPointer var; var.type = ztVariant_i64  ; var.v_i64   = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_u8    (u8           *val)          { ztVariantPointer var; var.type = ztVariant_u8   ; var.v_u8    = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_u16   (u16          *val)          { ztVariantPointer var; var.type = ztVariant_u16  ; var.v_u16   = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_u32   (u32          *val)          { ztVariantPointer var; var.type = ztVariant_u32  ; var.v_u32   = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_u64   (u64          *val)          { ztVariantPointer var; var.type = ztVariant_u64  ; var.v_u64   = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_r32   (r32          *val)          { ztVariantPointer var; var.type = ztVariant_r32  ; var.v_r32   = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_r64   (r64          *val)          { ztVariantPointer var; var.type = ztVariant_r64  ; var.v_r64   = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_voidp (void        **val)          { ztVariantPointer var; var.type = ztVariant_voidp; var.v_voidp = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_vec2  (ztVec2       *val)          { ztVariantPointer var; var.type = ztVariant_vec2 ; var.v_vec2  = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_vec3  (ztVec3       *val)          { ztVariantPointer var; var.type = ztVariant_vec3 ; var.v_vec3  = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_vec4  (ztVec4       *val)          { ztVariantPointer var; var.type = ztVariant_vec4 ; var.v_vec4  = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_mat4  (ztMat4       *val)          { ztVariantPointer var; var.type = ztVariant_mat4 ; var.v_mat4  = val; return var; }
ztInline ztVariantPointer zt_variantPointerMake_quat  (ztQuat       *val)          { ztVariantPointer var; var.type = ztVariant_quat ; var.v_quat  = val; return var; }

ztInline i8               zt_variantGetAs_i8       (ztVariant *variant)         { zt_assert(variant->type == ztVariant_i8   ); return variant->v_i8; }
ztInline i16              zt_variantGetAs_i16      (ztVariant *variant)         { zt_assert(variant->type == ztVariant_i16  ); return variant->v_i16; }
ztInline i32              zt_variantGetAs_i32      (ztVariant *variant)         { zt_assert(variant->type == ztVariant_i32  ); return variant->v_i32; }
ztInline i64              zt_variantGetAs_i64      (ztVariant *variant)         { zt_assert(variant->type == ztVariant_i64  ); return variant->v_i64; }
ztInline u8               zt_variantGetAs_u8       (ztVariant *variant)         { zt_assert(variant->type == ztVariant_u8   ); return variant->v_u8; }
ztInline u16              zt_variantGetAs_u16      (ztVariant *variant)         { zt_assert(variant->type == ztVariant_u16  ); return variant->v_u16; }
ztInline u32              zt_variantGetAs_u32      (ztVariant *variant)         { zt_assert(variant->type == ztVariant_u32); return variant->v_u32; }
ztInline u64              zt_variantGetAs_u64      (ztVariant *variant)         { zt_assert(variant->type == ztVariant_u64); return variant->v_u64; }
ztInline r32              zt_variantGetAs_r32      (ztVariant *variant)         { zt_assert(variant->type == ztVariant_r32); return variant->v_r32; }
ztInline r64              zt_variantGetAs_r64      (ztVariant *variant)         { zt_assert(variant->type == ztVariant_r64); return variant->v_r64; }
ztInline void            *zt_variantGetAs_voidp    (ztVariant *variant)         { zt_assert(variant->type == ztVariant_voidp); return variant->v_voidp; }
ztInline ztVec2           zt_variantGetAs_vec2     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_vec2 ); return ztVec2(variant->v_vec2[0], variant->v_vec2[1]); }
ztInline ztVec3           zt_variantGetAs_vec3     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_vec3 ); return ztVec3(variant->v_vec3[0], variant->v_vec3[1], variant->v_vec3[2]); }
ztInline ztVec4           zt_variantGetAs_vec4     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_vec4 ); return ztVec4(variant->v_vec4[0], variant->v_vec4[1], variant->v_vec4[2], variant->v_vec4[3]); }
ztInline ztMat4           zt_variantGetAs_mat4     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_mat4 ); return ztMat4(variant->v_mat4); }
ztInline ztQuat           zt_variantGetAs_quat     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_quat ); return ztQuat(variant->v_quat); }

ztInline i8              *zt_variantGetAs_i8       (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_i8   ); return variant->v_i8; }
ztInline i16             *zt_variantGetAs_i16      (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_i16  ); return variant->v_i16; }
ztInline i32             *zt_variantGetAs_i32      (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_i32  ); return variant->v_i32; }
ztInline i64             *zt_variantGetAs_i64      (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_i64  ); return variant->v_i64; }
ztInline u8              *zt_variantGetAs_u8       (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_u8   ); return variant->v_u8; }
ztInline u16             *zt_variantGetAs_u16      (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_u16  ); return variant->v_u16; }
ztInline u32             *zt_variantGetAs_u32      (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_u32  ); return variant->v_u32; }
ztInline u64             *zt_variantGetAs_u64      (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_u64  ); return variant->v_u64; }
ztInline r32             *zt_variantGetAs_r32      (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_r32  ); return variant->v_r32; }
ztInline r64             *zt_variantGetAs_r64      (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_r64  ); return variant->v_r64; }
ztInline void           **zt_variantGetAs_voidp    (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_voidp); return variant->v_voidp; }
ztInline ztVec2          *zt_variantGetAs_vec2     (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_vec2 ); return variant->v_vec2; }
ztInline ztVec3          *zt_variantGetAs_vec3     (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_vec3 ); return variant->v_vec3; }
ztInline ztVec4          *zt_variantGetAs_vec4     (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_vec4 ); return variant->v_vec4; }
ztInline ztMat4          *zt_variantGetAs_mat4     (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_mat4 ); return variant->v_mat4; }
ztInline ztQuat          *zt_variantGetAs_quat     (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_quat ); return variant->v_quat; }

ztInline void zt_variantAssignValue(ztVariant *variant, ztVariant value) { variant->type = value.type; zt_memCpy(variant, zt_sizeof(ztVariant), &value, zt_sizeof(ztVariant)); }

ztInline void zt_variantAssignValue(ztVariantPointer *variant, ztVariant value)
{
	variant->type = value.type;
	switch (variant->type)
	{
		case ztVariant_i8: *variant->v_i8 = value.v_i8; break;
		case ztVariant_i16: *variant->v_i16 = value.v_i16; break;
		case ztVariant_i32: *variant->v_i32 = value.v_i32; break;
		case ztVariant_i64: *variant->v_i64 = value.v_i64; break;
		case ztVariant_u8: *variant->v_u8 = value.v_u8; break;
		case ztVariant_u16: *variant->v_u16 = value.v_u16; break;
		case ztVariant_u32: *variant->v_u32 = value.v_u32; break;
		case ztVariant_u64: *variant->v_u64 = value.v_u64; break;
		case ztVariant_r32: *variant->v_r32 = value.v_r32; break;
		case ztVariant_r64: *variant->v_r64 = value.v_r64; break;
		case ztVariant_voidp: *variant->v_voidp = value.v_voidp; break;
		case ztVariant_vec2: variant->v_vec2->x = value.v_vec2[0]; variant->v_vec2->y = value.v_vec2[1]; break;
		case ztVariant_vec3: variant->v_vec3->x = value.v_vec3[0]; variant->v_vec3->y = value.v_vec3[1]; variant->v_vec3->z = value.v_vec3[2]; break;
		case ztVariant_vec4: variant->v_vec4->x = value.v_vec4[0]; variant->v_vec4->y = value.v_vec4[1]; variant->v_vec4->z = value.v_vec4[2]; variant->v_vec4->w = value.v_vec4[3]; break;
		case ztVariant_mat4: zt_fiz(16) variant->v_mat4->values[i] = value.v_mat4[i]; break;
		case ztVariant_quat: variant->v_quat->x = value.v_quat[0]; variant->v_quat->y = value.v_quat[1]; variant->v_quat->z = value.v_quat[2]; variant->v_quat->w = value.v_quat[3]; break;
	}
}

ztInline ztVariant zt_variantLerp(ztVariant *beg, ztVariant *end, r32 pct)
{
	zt_assert(beg->type == end->type);
	switch (beg->type)
	{
		case ztVariant_i8   : return zt_variantMake_i8   (( i8)zt_lerp((i32)beg->v_i8 , (i32)end->v_i8 , pct));
		case ztVariant_i16  : return zt_variantMake_i16  ((i16)zt_lerp((i32)beg->v_i16, (i32)end->v_i16, pct));
		case ztVariant_i32  : return zt_variantMake_i32  ((i32)zt_lerp((i32)beg->v_i32, (i32)end->v_i32, pct));
		case ztVariant_i64  : return zt_variantMake_i64  ((i64)zt_lerp((i32)beg->v_i64, (i32)end->v_i64, pct));
		case ztVariant_u8   : return zt_variantMake_u8   (( u8)zt_lerp((i32)beg->v_u8 , (i32)end->v_u8 , pct));
		case ztVariant_u16  : return zt_variantMake_u16  ((u16)zt_lerp((i32)beg->v_u16, (i32)end->v_u16, pct));
		case ztVariant_u32: return zt_variantMake_u32((u32)zt_lerp((i32)beg->v_u32, (i32)end->v_u32, pct));
		case ztVariant_u64: return zt_variantMake_u64((u64)zt_lerp((i32)beg->v_u64, (i32)end->v_u64, pct));
		case ztVariant_r32: return zt_variantMake_r32((r32)zt_lerp((r32)beg->v_r32, (r32)end->v_r32, pct));
		case ztVariant_r64: return zt_variantMake_r64((r64)zt_lerp((r32)beg->v_r64, (r32)end->v_r64, pct));
		case ztVariant_voidp: zt_assert(false); // _voidpcan't lerp void pointers
		case ztVariant_vec2 : return zt_variantMake_vec2(ztVec2::lerp(ztVec2(beg->v_vec2[0], beg->v_vec2[1]), ztVec2(end->v_vec2[0], end->v_vec2[1]), pct));
		case ztVariant_vec3 : return zt_variantMake_vec3(ztVec3::lerp(ztVec3(beg->v_vec3[0], beg->v_vec3[1], beg->v_vec3[2]), ztVec3(end->v_vec3[0], end->v_vec3[1], end->v_vec3[2]), pct));
		case ztVariant_vec4 : return zt_variantMake_vec4(ztVec4::lerp(ztVec4(beg->v_vec4[0], beg->v_vec4[1], beg->v_vec4[2], beg->v_vec4[3]), ztVec4(end->v_vec4[0], end->v_vec4[1], end->v_vec4[2], end->v_vec4[3]), pct));
		case ztVariant_mat4 : zt_assert(false); // can't lerp mat4s... use quats instead
		case ztVariant_quat: return zt_variantMake_quat(ztQuat::lerp(ztQuat(beg->v_quat[0], beg->v_quat[1], beg->v_quat[2], beg->v_quat[3]), ztQuat(end->v_quat[0], end->v_quat[1], end->v_quat[2], end->v_quat[3]), pct));
	}

	ztVariant v = { ztVariant_Invalid }; return v;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_DLL_SET_GLOBALS(name) void name(void *memory, int version)
typedef ZT_FUNC_DLL_SET_GLOBALS(zt_dllSetGlobals_Func);

#if !defined(ZT_DLL)

void zt_dllSendGlobals(zt_dllSetGlobals_Func *set_globals);

#endif


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

#endif // include guard

#if defined(ZT_TOOLS_IMPLEMENTATION) || defined(ZT_TOOLS_INTERNAL_DECLARATIONS)

#ifndef __zt_tools_h_internal_included__
#define __zt_tools_h_internal_included__

// ------------------------------------------------------------------------------------------------

void *_zt_call_malloc(size_t);
void  _zt_call_free(void*);

// ------------------------------------------------------------------------------------------------

#ifndef ZT_MAX_LOG_CALLBACKS
#define ZT_MAX_LOG_CALLBACKS	8
#endif

#if !defined(ZT_MEM_GLOBAL_ARENA_STACK_SIZE)
#define ZT_MEM_GLOBAL_ARENA_STACK_SIZE	64
#endif

// ------------------------------------------------------------------------------------------------

struct ztGlobals
{
	zt_logCallback_Func   *log_callbacks[ZT_MAX_LOG_CALLBACKS];
	ztLogMessageLevel_Enum log_callbacks_minlevel[ZT_MAX_LOG_CALLBACKS];
	i32                    log_callbacks_count = 0;

	ztMemoryArena         *mem_global_arena_stack[ZT_MEM_GLOBAL_ARENA_STACK_SIZE];
	i32                    mem_global_arena_stack_count = 0;
	void                *(*mem_malloc)(size_t) = _zt_call_malloc;
	void                 (*mem_free)(void*)    = _zt_call_free;

	void *(*functionPointer)(ztFunctionID) = nullptr;
};

#define ZT_GLOBALS_VERSION	1 // update this any time ztGlobals is changed

extern ztGlobals *zt;

#endif // internal include guard
#endif // internal declarations

#if defined(ZT_TOOLS_IMPLEMENTATION)
#ifndef __zt_tools_implementation__
#define __zt_tools_implementation__

// headers (strive to avoid including anything if possible)
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#if defined(ZT_COMPILER_MSVC)
#	include <windows.h>
#	include <WinBase.h>
#	include <shlobj.h>
#	include <process.h>
#endif

ztGlobals zt_local = {};

#if defined(ZT_DLL)
	ztGlobals *zt = &zt_local;

	ZT_DLLEXPORT ZT_FUNC_DLL_SET_GLOBALS(zt_dllSetGlobals)
	{
		if(version == ZT_GLOBALS_VERSION) {
			zt = (ztGlobals *)memory;
		}
	}

#else
	ztGlobals *zt = &zt_local;

	void zt_dllSendGlobals(zt_dllSetGlobals_Func *set_globals)
	{
		if (set_globals) {
			zt->functionPointer = zt_functionPointer;
			set_globals(zt, ZT_GLOBALS_VERSION);
		}
	}
#endif

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#ifndef ZT_MAX_FUNCTION_POINTER_ENTRIES
#define ZT_MAX_FUNCTION_POINTER_ENTRIES  256
#endif

// ------------------------------------------------------------------------------------------------

#if defined(ZT_WINDOWS)

struct ztThread
{
	ztThreadID          thread_id;
	i64                 thread_handle;
	ztThread_Func      *thread;
	void               *thread_user_data;
	ztThreadExit_Func  *exit_test;
	void               *exit_test_user_data;
	bool                running;
};

// ------------------------------------------------------------------------------------------------

struct ztThreadMutex
{
	CRITICAL_SECTION cs;
};

// ------------------------------------------------------------------------------------------------

struct ztThreadMonitor
{
	i64 event_handle;
};

#endif

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//these aren't in ztGlobals because they must be process-specific:
ztInternal void *_zt_function_pointers[ZT_MAX_FUNCTION_POINTER_ENTRIES];
ztInternal i32   _zt_function_hashes  [ZT_MAX_FUNCTION_POINTER_ENTRIES];
ztInternal int   _zt_function_count = 0;

// ------------------------------------------------------------------------------------------------

ztFunctionID zt_registerFunctionPointer(const char *function_name, void *function)
{
	zt_assert(_zt_function_count < ZT_MAX_FUNCTION_POINTER_ENTRIES);

	i32 hash = zt_strHash(function_name);

	zt_fiz(_zt_function_count) {
		if (_zt_function_hashes[i] == hash) {
			return hash;
		}
	}

	int idx = _zt_function_count++;
	_zt_function_pointers[idx] = function;
	_zt_function_hashes[idx] = zt_strHash(function_name);

	return _zt_function_hashes[idx];
}

// ------------------------------------------------------------------------------------------------

void *zt_functionPointer(ztFunctionID function_id)
{
	zt_fiz(_zt_function_count) {
		if (_zt_function_hashes[i] == function_id) {
			return _zt_function_pointers[i];
		}
	}

#	if defined(ZT_DLL)
	if (zt->functionPointer) {
		return zt->functionPointer(function_id);
	}
#	endif

	zt_assert(false);
	return nullptr;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

void *_zt_call_malloc(size_t size)
{
	return malloc(size);
}

void  _zt_call_free(void* mem)
{
	free(mem);
}

// ------------------------------------------------------------------------------------------------

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
	if (level < ztLogMessageLevel_Verbose) {
		OutputDebugStringA(message);
		OutputDebugStringA("\n");
	}
#endif

	zt_fiz(zt->log_callbacks_count) {
		if (zt->log_callbacks_minlevel[i] >= level) {
			zt->log_callbacks[i](level, message);
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

#undef _zt_var_args

// ------------------------------------------------------------------------------------------------

void zt_logAddCallback(zt_logCallback_Func callback, ztLogMessageLevel_Enum min_level)
{
	zt_assert(zt->log_callbacks_count < ZT_MAX_LOG_CALLBACKS);

	int idx = zt->log_callbacks_count++;
	zt->log_callbacks[idx] = callback;
	zt->log_callbacks_minlevel[idx] = min_level;
}

// ------------------------------------------------------------------------------------------------

void zt_logRemoveCallback(zt_logCallback_Func callback)
{
	zt_fiz(zt->log_callbacks_count) {
		if (zt->log_callbacks[i] == callback) {
			for (int j = i; j < zt->log_callbacks_count - 1; ++j) {
				zt->log_callbacks[j] = zt->log_callbacks[j + 1];
				zt->log_callbacks_minlevel[j] = zt->log_callbacks_minlevel[j + 1];
			}
			zt->log_callbacks_count -= 1;
			break;
		}
	}
}

// ------------------------------------------------------------------------------------------------

void  zt_memSet(void *mem, int32 mem_len, byte value)
{
	byte* bmem = (byte*)mem;
	zt_fiz(mem_len) {
		bmem[i] = value;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_memCpy(void *dst, int32 dst_len, const void *src, int32 src_len)
{
	int max_idx = zt_min(dst_len, src_len);

//	for (int i = 0; i < max_idx; ++i) {
//		((byte*)dst)[i] = ((byte*)src)[i];
//	}

	if(max_idx % 4 == 0) {
		max_idx /= 4;
		u32 *udst = (u32*)dst;
		u32 *usrc = (u32*)src;
		while(max_idx--) {
			*udst++ = *usrc++;
		}
	}
	else if(max_idx % 2 == 0) {
		max_idx /= 2;
		u16 *udst = (u16*)dst;
		u16 *usrc = (u16*)src;
		while(max_idx--) {
			*udst++ = *usrc++;
		}
	}
	else {
		byte *bdst = (byte*)dst;
		byte *bsrc = (byte*)src;
		while(max_idx--) {
			*bdst++ = *bsrc++;
		}
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

ztMemoryArena *zt_memMakeArena(i32 total_size, ztMemoryArena *from)
{
	ztMemoryArena *arena = nullptr;
	if (from == nullptr) {
#if defined(ZT_COMPILER_MSVC)
		arena = (ztMemoryArena*)VirtualAlloc((VOID*)zt_gigabytes(1), total_size + zt_sizeof(ztMemoryArena), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
		arena = malloc(total_size + sizeof(ztMemoryArena));
#endif
	}
	else {
		arena = (ztMemoryArena*)zt_memAlloc(from, total_size + zt_sizeof(ztMemoryArena));
	}

	if (arena) {
		arena->memory = (byte*)(arena) + zt_sizeof(ztMemoryArena);
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
		VirtualFree(arena, arena->total_size + zt_sizeof(ztMemoryArena), MEM_DECOMMIT | MEM_RELEASE);
#else
		free(arena);
#endif

	}
}

// ------------------------------------------------------------------------------------------------

void zt_memArenaClearAllocations(ztMemoryArena *arena, bool wipe_memory)
{
	arena->current_used = 0;
	arena->peak_used = 0;
	arena->alloc_cnt = 0;
	arena->free_cnt = 0;
	arena->latest = nullptr;
	arena->freed_allocs = 0;

	if (wipe_memory) {
		zt_memSet(arena->memory, arena->total_size, 0);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_memValidateArena(ztMemoryArena *arena)
{
#if 1 || defined(ZT_DEBUG)
	{
		// the list of allocations need to be in ascending memory location order, test for that
		auto *prev = arena->latest;
		if (prev) {
			auto *alloc = prev->next;
			while (alloc) {
				zt_assertAlways(alloc < prev);
				prev = alloc;
				alloc = alloc->next;
			}
		}
	}
	{
		int freed = 0;
		auto *alloc = arena->latest;
		while (alloc) {
			if (alloc->freed) {
				freed += 1;
			}
			alloc = alloc->next;
		}

		zt_assertAlways(freed == arena->freed_allocs);
	}
	{
		int active = 0;
		auto *alloc = arena->latest;
		while (alloc) {
			if (alloc->freed == 0) {
				active += 1;
			}
			alloc = alloc->next;
		}

		zt_assertAlways(active == arena->alloc_cnt - arena->free_cnt);
	}
	{
		int padding = ztPointerSize;
		auto *alloc = arena->latest;
		auto *prev = alloc;
		while (alloc) {
			byte *end_of_mem = ((byte*)alloc->start + alloc->length) - 1;
			zt_fiz(padding) zt_assertAlways(*end_of_mem-- == 0xcd); // if you assert here, then you've written over more memory than was allocated
			prev = alloc;
			alloc = alloc->next;
		}
	}
	
#endif
}

// ------------------------------------------------------------------------------------------------

void zt_memDumpArenaDiagnostics(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level)
{
	zt_flink(alloc, arena->latest) {
		zt_debugOnly(zt_logMessage(log_level, "[%s] alloc: %llx; start: %llx; length: %d (%s:%d)", name, (i64)alloc, (i64)alloc->start, alloc->length, alloc->file, alloc->file_line));
		zt_releaseOnly(zt_logMessage(log_level, "[%s] alloc: %llx; start: %llx; length: %d", name, (i64)alloc, (i64)alloc->start, alloc->length));
	}
}

// ------------------------------------------------------------------------------------------------

void *zt_memAllocFromArena(ztMemoryArena *arena, i32 bytes)
{
	if (arena == nullptr) {
		return zt->mem_malloc(bytes);
	}

	const int byte_align = ztPointerSize;
	if (bytes % byte_align != 0) {
		bytes += byte_align - (bytes % byte_align);	// align the memory to 4/8 byte chunks
	}

	int padding = ztPointerSize;
	bytes += padding; // add for end of memory padding

	zt_memValidateArena(arena);

	ztMemoryArena::allocation *allocation = nullptr;
	if (arena->freed_allocs > 0) { // use pre-allocated memory if it exists before going to the end of the buffer
		allocation = arena->latest;
		ztMemoryArena::allocation *prev = nullptr;
		while (allocation) {
			if (allocation->freed == 1 && bytes <= allocation->length) {
				i32 remaining = allocation->length - (zt_sizeof(ztMemoryArena::allocation) + bytes);
				if (remaining > (zt_sizeof(ztMemoryArena::allocation))) {
					ztMemoryArena::allocation *original = allocation;
					original->length = remaining - (zt_sizeof(ztMemoryArena::allocation));
#					if defined(ZT_DLL)
					original->file = nullptr;
					original->file_line = 0;
#					else
					original->file = "original";
					original->file_line = 0;
#					endif

					byte *end_of_mem = ((byte*)original->start + original->length) - 1;
					zt_fiz(padding) *end_of_mem-- = 0xcd;

					ztMemoryArena::allocation *inserted = (ztMemoryArena::allocation *)((byte *)original->start + original->length);
					inserted->magic[0] = 'M';
					inserted->magic[1] = 'R';
					inserted->magic[2] = 'E';
					inserted->arena = arena;
					inserted->start = (byte *)inserted + zt_sizeof(ztMemoryArena::allocation);
					inserted->length = bytes;

#					if defined(ZT_DLL)
					inserted->file = nullptr;
					inserted->file_line = 0;
#					else
					inserted->file = "inserted";
					inserted->file_line = 0;
#					endif

					inserted->next = original;
					//allocation->next = alloc;

					if (prev) {
						prev->next = inserted;
					}
					else if (arena->latest == original) {
						arena->latest = inserted;
					}

					allocation = inserted;
				}
				else {
					arena->freed_allocs -= 1; // only change this count when we are using the entire previous allocation
				}

				byte *end_of_mem = ((byte*)allocation->start + allocation->length) - 1;
				zt_fiz(padding) *end_of_mem-- = 0xcd;

				arena->current_used += zt_sizeof(ztMemoryArena::allocation) + bytes;
				arena->peak_used = zt_max(arena->peak_used, arena->current_used);
				arena->alloc_cnt++;


				allocation->freed = 0;
				allocation->alloc_idx = arena->alloc_cnt;
				break;
			}
			prev = allocation;
			allocation = allocation->next;
		}
	}

	if (allocation == nullptr) {
		byte* next = arena->latest ? (byte*)arena->latest->start + arena->latest->length : arena->memory;
		zt_assert((next - arena->memory) + zt_sizeof(ztMemoryArena::allocation) + bytes <= arena->total_size);

		if ((next - arena->memory) + zt_sizeof(ztMemoryArena::allocation) + bytes > arena->total_size) {
			zt_logCritical("zt_memAllocFromArena: Attempted to allocate more memory than available");
			return nullptr;
		}

		allocation = (ztMemoryArena::allocation*)next;
		allocation->magic[0] = 'M';
		allocation->magic[1] = 'R';
		allocation->magic[2] = 'E';
		allocation->length = bytes;
		allocation->freed = 0;
		allocation->next = arena->latest;
		allocation->start = (next + zt_sizeof(ztMemoryArena::allocation));
		allocation->alloc_idx = arena->alloc_cnt++;
		allocation->arena = arena;

		byte *end_of_mem = ((byte*)allocation->start + allocation->length) - 1;
		zt_fiz(padding) *end_of_mem-- = 0xcd;

#		if defined(ZT_DLL)
		allocation->file = nullptr;
		allocation->file_line = 0;
#		else
		allocation->file = nullptr;
		allocation->file_line = 0;
#		endif

		arena->latest = allocation;

		arena->current_used += allocation->length + (zt_sizeof(ztMemoryArena::allocation));
		arena->peak_used = zt_max(arena->peak_used, arena->current_used);

#if defined(ZT_MEM_ARENA_ZERO_NEW_MEMORY)
		ztReleaseOnly(zt_memSet(allocation->start, allocation->length, 0));
#endif
	}

	zt_debugOnly(zt_memSet(allocation->start, allocation->length - padding, 0));
#if defined(ZT_MEM_ARENA_ZERO_NEW_MEMORY)
	ztReleaseOnly(zt_memSet(allocation->start, allocation->length - padding, 0));
#endif

	zt_logMemory("memory (%llx): allocated %d + %d bytes at location 0x%llx (%d)", (long long unsigned int)arena, allocation->length, zt_sizeof(ztMemoryArena::allocation), (long long unsigned int)next, arena->alloc_cnt);
	// conditional break: allocation->alloc_idx == 0 && allocation->start == 0x0
	//zt_memValidateArena(arena);
	return (void*)allocation->start;
}

// ------------------------------------------------------------------------------------------------

void *zt_memAllocFromArena(ztMemoryArena *arena, i32 size, const char *file, int file_line)
{
	void *result = zt_memAllocFromArena(arena, size);
	if (result && arena) {
		ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)(((byte*)result) - zt_sizeof(ztMemoryArena::allocation));
#if defined(ZT_DLL)
		allocation->file = nullptr;
		allocation->file_line = file_line;
#else
		allocation->file = file;
		allocation->file_line = file_line;
#endif

		zt_debugOnly(zt_logMemory("memory (%llx): %d bytes of memory at location 0x%llx (file: %s) (line: %d)", (long long unsigned int)arena, allocation->length, (long long unsigned int)allocation, file, file_line));
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

void *zt_memRealloc(ztMemoryArena *arena, void *data, i32 size)
{
	if (data == nullptr) {
		return zt_memAllocFromArena(arena, size);
	}

	ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)(((byte*)data) - zt_sizeof(ztMemoryArena::allocation));
	zt_assert(allocation->magic[0] == 'M' && allocation->magic[1] == 'R' && allocation->magic[2] == 'E');
	zt_logMemory("memory (%llx): reallocating %d bytes of memory at location 0x%llx", (long long unsigned int)arena, size, (long long unsigned int)allocation);

	int padding = ztPointerSize;

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

			byte *end_of_mem = ((byte*)allocation->start + allocation->length) - 1;
			zt_fiz(padding) *end_of_mem-- = 0xcd;

			return data;
		}
		else {
			void *nmem = zt_memAllocFromArena(arena, size);
			if (nmem == nullptr) {
				return nmem;
			}
			zt_memCpy(nmem, size, data, zt_min(size, allocation->length - padding));
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
		zt->mem_free(data);
		return;
	}

	ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)(((byte*)data) - zt_sizeof(ztMemoryArena::allocation));
	zt_assert(allocation->magic[0] == 'M' && allocation->magic[1] == 'R' && allocation->magic[2] == 'E');
	
	zt_assert(allocation->freed == 0);
	zt_assert(allocation >= (ztMemoryArena::allocation*)arena->memory && allocation <= (ztMemoryArena::allocation*)(arena->memory + arena->total_size));

	zt_debugOnly(zt_memSet((void*)allocation->start, 1, allocation->length));
	arena->current_used -= allocation->length + (zt_sizeof(ztMemoryArena::allocation) );

	allocation->freed = 1;

	arena->free_cnt += 1;
	arena->freed_allocs += 1;

	zt_logMemory("memory (%llx): freeing %d bytes of memory at location 0x%llx (%d)", (long long unsigned int)arena, allocation->length, (long long unsigned int)allocation, arena->free_cnt);

	while (arena->latest && arena->latest->freed) {
		arena->latest = arena->latest->next;
		arena->freed_allocs -= 1;
	}

	int padding = ztPointerSize;

	// consolidate any sequential allocations that might exist
	allocation = arena->latest;
	ztMemoryArena::allocation *prev = nullptr;
	while (allocation) {
		if (allocation->freed == 1) {
			auto* next = allocation->next;
			while (next) {
				if (next->freed == 1) {
					next->length += allocation->length + zt_sizeof(ztMemoryArena::allocation);

					byte *end_of_mem = ((byte*)next->start + next->length) - 1;
					zt_fiz(padding) *end_of_mem-- = 0xcd;

					if (prev) {
						prev->next = next;
					}
					else if (arena->latest == allocation) {
						arena->latest = next;
					}
					allocation = next;
					arena->freed_allocs -= 1;
				}
				else break;
				next = next->next;
			}
		}
		prev = allocation;
		allocation = allocation->next;
	}

	zt_memValidateArena(arena);
}

// ------------------------------------------------------------------------------------------------

void zt_memDumpArena(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level)
{
	zt_returnOnNull(arena);

	char avail[32] = { 0 };
	zt_strBytesToString(avail, zt_sizeof(avail), arena->total_size);

	char peak[32] = { 0 };
	zt_strBytesToString(peak, zt_sizeof(peak), arena->peak_used);

	zt_logMessage(log_level, "memory (%s): Total: %s; Peak used: %s", name, avail, peak);

	ztMemoryArena::allocation* alloc = arena->latest;
	while (alloc != nullptr) {
		if (alloc->freed == 0) {
			zt_logMessage(log_level, "memory (%s): unfreed memory at location 0x%llx (%d) (%d bytes)", name, (uint64)alloc->start, alloc->alloc_idx, alloc->length);
			zt_debugOnly(zt_logMessage(log_level, "   file: %s (%d)", alloc->file, alloc->file_line));
		}
		alloc = alloc->next;
	}
	if (arena->alloc_cnt != arena->free_cnt) {
		zt_logMessage(log_level, "memory(%s): alloc/free count mismatch: %d/%d", name, arena->alloc_cnt, arena->free_cnt);
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_memArenaValidate(ztMemoryArena *arena)
{
	ztMemoryArena::allocation *alloc = arena->latest;
	while (alloc != nullptr) {
		if (alloc->freed == 0) {
			byte *end_of_mem = (byte*)alloc->start + alloc->length;
			zt_fiz(4) {
				if (*end_of_mem++ != 0xcd) {
					zt_assert(false);
					return false;
				}
			}
		}
		alloc = alloc->next;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_memPushGlobalArena(ztMemoryArena *arena)
{
	zt_assert(zt->mem_global_arena_stack_count < ZT_MEM_GLOBAL_ARENA_STACK_SIZE);
	if (zt->mem_global_arena_stack_count >= ZT_MEM_GLOBAL_ARENA_STACK_SIZE) {
		return false;
	}

	zt->mem_global_arena_stack[zt->mem_global_arena_stack_count++] = arena;
	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_memPopGlobalArena()
{
	zt_assert(zt->mem_global_arena_stack_count > 0);
	zt->mem_global_arena_stack_count -= 1;
}

// ------------------------------------------------------------------------------------------------

ztMemoryArena* zt_memGetGlobalArena()
{
	if (zt->mem_global_arena_stack_count == 0) {
		return nullptr;
	}
	return zt->mem_global_arena_stack[zt->mem_global_arena_stack_count - 1];
}

// ------------------------------------------------------------------------------------------------

void zt_memSetDefaultMallocFree(void *(*malloc_func)(size_t), void(*free_func)(void*))
{
	zt->mem_malloc = malloc_func;
	zt->mem_free   = free_func;
}

// ------------------------------------------------------------------------------------------------

void *zt_memAllocGlobalFull(i32 size, const char *file, int file_line)
{
	ztMemoryArena* arena = zt_memGetGlobalArena();
	if (arena) {
		return zt_memAllocFromArena(arena, size, file, file_line);
	}
	else {
		return zt->mem_malloc(size);
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
		zt->mem_free(data);
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

/*static*/ const ztVec2 ztVec2::zero = ztVec2(0, 0);
/*static*/ const ztVec2 ztVec2::one  = ztVec2(1, 1);
/*static*/ const ztVec2 ztVec2::min  = ztVec2(ztReal32Min, ztReal32Min);
/*static*/ const ztVec2 ztVec2::max  = ztVec2(ztReal32Max, ztReal32Max);

/*static*/ const ztVec3 ztVec3::zero = ztVec3(0, 0, 0);
/*static*/ const ztVec3 ztVec3::one  = ztVec3(1, 1, 1);
/*static*/ const ztVec3 ztVec3::min  = ztVec3(ztReal32Min, ztReal32Min, ztReal32Min);
/*static*/ const ztVec3 ztVec3::max  = ztVec3(ztReal32Max, ztReal32Max, ztReal32Max);

/*static*/ const ztVec4 ztVec4::zero = ztVec4(0, 0, 0, 0);
/*static*/ const ztVec4 ztVec4::one  = ztVec4(1, 1, 1, 1);
/*static*/ const ztVec4 ztVec4::min  = ztVec4(ztReal32Min, ztReal32Min, ztReal32Min, ztReal32Min);
/*static*/ const ztVec4 ztVec4::max  = ztVec4(ztReal32Max, ztReal32Max, ztReal32Max, ztReal32Max);

/*static*/ const ztMat4 ztMat4::zero = ztMat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
/*static*/ const ztMat4 ztMat4::identity = ztMat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

/*static*/ const ztQuat ztQuat::identity = ztQuat(0, 0, 0, 1);

// ------------------------------------------------------------------------------------------------

r32 zt_sin(r32 x)
{
	return sinf(x);
}

// ------------------------------------------------------------------------------------------------

r32 zt_asin(r32 x)
{
	return asinf(x);
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

r32 zt_tan(r32 r)
{
	return tan(r);
}

// ------------------------------------------------------------------------------------------------

r32 zt_atan(r32 v)
{
	return atanf(v);
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

r32 zt_exp(r32 v)
{
	return expf(v);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

void ztMat4::rotateEuler(const ztVec3& euler)
{
	rotateEuler(euler.x, euler.y, euler.z);
}

// ------------------------------------------------------------------------------------------------

void ztMat4::rotateEuler(r32 x, r32 y, r32 z)
{
#if 0
	x = zt_degreesToRadians(x);
	y = zt_degreesToRadians(y);
	z = zt_degreesToRadians(z);

	r32 cr = zt_cos(x);
	r32 sr = zt_sin(x);
	r32 cy = zt_cos(z);
	r32 sy = zt_sin(z);
	r32 cp = zt_cos(y);
	r32 sp = zt_sin(y);

	ztMat4 m;
	m.values[ztMat4_Col0Row0] =  cp * cy + sp * sr * sy; m.values[ztMat4_Col1Row0] = -cp * sy + sp * sr * cy; m.values[ztMat4_Col2Row0] =  sp * cr; m.values[ztMat4_Col3Row0] = 0;
	m.values[ztMat4_Col0Row1] =  sy * cr;                m.values[ztMat4_Col1Row1] =  cy * cr;                m.values[ztMat4_Col2Row1] = -sr;      m.values[ztMat4_Col3Row1] = 0;
	m.values[ztMat4_Col0Row2] = -sp * cy + cp * sr * sy; m.values[ztMat4_Col1Row2] =  sy * sp + cp * sr * cy; m.values[ztMat4_Col2Row2] =  cp * cr; m.values[ztMat4_Col3Row2] = 0;
	m.values[ztMat4_Col0Row3] =  0;                      m.values[ztMat4_Col1Row3] =  0;                      m.values[ztMat4_Col2Row3] =  0;       m.values[ztMat4_Col3Row3] = 1;

	multiply(m);
#endif
#if 1
	// pitch = y, yaw = x, roll = z

	x = zt_degreesToRadians(x);
	y = zt_degreesToRadians(y);
	z = zt_degreesToRadians(z);

	ztMat4 rot_x(
		1, 0, 0, 0,
		0, cosf(x), -sinf(x), 0,
		0, sinf(x), cosf(x), 0,
		0, 0, 0, 1
		);

	ztMat4 rot_y(
		cosf(y), 0, sinf(y), 0,
		0, 1, 0, 0,
		-sinf(y), 0, cosf(y), 0,
		0, 0, 0, 1
		);

	ztMat4 rot_z(
		cosf(z), -sinf(z), 0, 0,
		sinf(z), cosf(z), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		);

	ztMat4 mult_xyz = (rot_z * rot_y) * rot_x;
	multiply(mult_xyz);
#endif
}

// ------------------------------------------------------------------------------------------------

ztMat4 ztMat4::getRotateEuler(const ztVec3& euler) const
{
	ztMat4 copy(*this);
	copy.rotateEuler(euler);
	return copy;
}

// ------------------------------------------------------------------------------------------------

ztMat4 ztMat4::getRotateEuler(r32 x, r32 y, r32 z) const
{
	ztMat4 copy(*this);
	copy.rotateEuler(x, y, z);
	return copy;
}

// ------------------------------------------------------------------------------------------------

void ztMat4::multiply(const ztMat4& m2)
{
	ztMat4 m1(*this);

	values[ztMat4_Col0Row0] = (m1.values[ztMat4_Col0Row0] * m2.values[ztMat4_Col0Row0]) + (m1.values[ztMat4_Col1Row0] * m2.values[ztMat4_Col0Row1]) + (m1.values[ztMat4_Col2Row0] * m2.values[ztMat4_Col0Row2]) + (m1.values[ztMat4_Col3Row0] * m2.values[ztMat4_Col0Row3]);
	values[ztMat4_Col0Row1] = (m1.values[ztMat4_Col0Row1] * m2.values[ztMat4_Col0Row0]) + (m1.values[ztMat4_Col1Row1] * m2.values[ztMat4_Col0Row1]) + (m1.values[ztMat4_Col2Row1] * m2.values[ztMat4_Col0Row2]) + (m1.values[ztMat4_Col3Row1] * m2.values[ztMat4_Col0Row3]);
	values[ztMat4_Col0Row2] = (m1.values[ztMat4_Col0Row2] * m2.values[ztMat4_Col0Row0]) + (m1.values[ztMat4_Col1Row2] * m2.values[ztMat4_Col0Row1]) + (m1.values[ztMat4_Col2Row2] * m2.values[ztMat4_Col0Row2]) + (m1.values[ztMat4_Col3Row2] * m2.values[ztMat4_Col0Row3]);
	values[ztMat4_Col0Row3] = (m1.values[ztMat4_Col0Row3] * m2.values[ztMat4_Col0Row0]) + (m1.values[ztMat4_Col1Row3] * m2.values[ztMat4_Col0Row1]) + (m1.values[ztMat4_Col2Row3] * m2.values[ztMat4_Col0Row2]) + (m1.values[ztMat4_Col3Row3] * m2.values[ztMat4_Col0Row3]);

	values[ztMat4_Col1Row0] = (m1.values[ztMat4_Col0Row0] * m2.values[ztMat4_Col1Row0]) + (m1.values[ztMat4_Col1Row0] * m2.values[ztMat4_Col1Row1]) + (m1.values[ztMat4_Col2Row0] * m2.values[ztMat4_Col1Row2]) + (m1.values[ztMat4_Col3Row0] * m2.values[ztMat4_Col1Row3]);
	values[ztMat4_Col1Row1] = (m1.values[ztMat4_Col0Row1] * m2.values[ztMat4_Col1Row0]) + (m1.values[ztMat4_Col1Row1] * m2.values[ztMat4_Col1Row1]) + (m1.values[ztMat4_Col2Row1] * m2.values[ztMat4_Col1Row2]) + (m1.values[ztMat4_Col3Row1] * m2.values[ztMat4_Col1Row3]);
	values[ztMat4_Col1Row2] = (m1.values[ztMat4_Col0Row2] * m2.values[ztMat4_Col1Row0]) + (m1.values[ztMat4_Col1Row2] * m2.values[ztMat4_Col1Row1]) + (m1.values[ztMat4_Col2Row2] * m2.values[ztMat4_Col1Row2]) + (m1.values[ztMat4_Col3Row2] * m2.values[ztMat4_Col1Row3]);
	values[ztMat4_Col1Row3] = (m1.values[ztMat4_Col0Row3] * m2.values[ztMat4_Col1Row0]) + (m1.values[ztMat4_Col1Row3] * m2.values[ztMat4_Col1Row1]) + (m1.values[ztMat4_Col2Row3] * m2.values[ztMat4_Col1Row2]) + (m1.values[ztMat4_Col3Row3] * m2.values[ztMat4_Col1Row3]);

	values[ztMat4_Col2Row0] = (m1.values[ztMat4_Col0Row0] * m2.values[ztMat4_Col2Row0]) + (m1.values[ztMat4_Col1Row0] * m2.values[ztMat4_Col2Row1]) + (m1.values[ztMat4_Col2Row0] * m2.values[ztMat4_Col2Row2]) + (m1.values[ztMat4_Col3Row0] * m2.values[ztMat4_Col2Row3]);
	values[ztMat4_Col2Row1] = (m1.values[ztMat4_Col0Row1] * m2.values[ztMat4_Col2Row0]) + (m1.values[ztMat4_Col1Row1] * m2.values[ztMat4_Col2Row1]) + (m1.values[ztMat4_Col2Row1] * m2.values[ztMat4_Col2Row2]) + (m1.values[ztMat4_Col3Row1] * m2.values[ztMat4_Col2Row3]);
	values[ztMat4_Col2Row2] = (m1.values[ztMat4_Col0Row2] * m2.values[ztMat4_Col2Row0]) + (m1.values[ztMat4_Col1Row2] * m2.values[ztMat4_Col2Row1]) + (m1.values[ztMat4_Col2Row2] * m2.values[ztMat4_Col2Row2]) + (m1.values[ztMat4_Col3Row2] * m2.values[ztMat4_Col2Row3]);
	values[ztMat4_Col2Row3] = (m1.values[ztMat4_Col0Row3] * m2.values[ztMat4_Col2Row0]) + (m1.values[ztMat4_Col1Row3] * m2.values[ztMat4_Col2Row1]) + (m1.values[ztMat4_Col2Row3] * m2.values[ztMat4_Col2Row2]) + (m1.values[ztMat4_Col3Row3] * m2.values[ztMat4_Col2Row3]);

	values[ztMat4_Col3Row0] = (m1.values[ztMat4_Col0Row0] * m2.values[ztMat4_Col3Row0]) + (m1.values[ztMat4_Col1Row0] * m2.values[ztMat4_Col3Row1]) + (m1.values[ztMat4_Col2Row0] * m2.values[ztMat4_Col3Row2]) + (m1.values[ztMat4_Col3Row0] * m2.values[ztMat4_Col3Row3]);
	values[ztMat4_Col3Row1] = (m1.values[ztMat4_Col0Row1] * m2.values[ztMat4_Col3Row0]) + (m1.values[ztMat4_Col1Row1] * m2.values[ztMat4_Col3Row1]) + (m1.values[ztMat4_Col2Row1] * m2.values[ztMat4_Col3Row2]) + (m1.values[ztMat4_Col3Row1] * m2.values[ztMat4_Col3Row3]);
	values[ztMat4_Col3Row2] = (m1.values[ztMat4_Col0Row2] * m2.values[ztMat4_Col3Row0]) + (m1.values[ztMat4_Col1Row2] * m2.values[ztMat4_Col3Row1]) + (m1.values[ztMat4_Col2Row2] * m2.values[ztMat4_Col3Row2]) + (m1.values[ztMat4_Col3Row2] * m2.values[ztMat4_Col3Row3]);
	values[ztMat4_Col3Row3] = (m1.values[ztMat4_Col0Row3] * m2.values[ztMat4_Col3Row0]) + (m1.values[ztMat4_Col1Row3] * m2.values[ztMat4_Col3Row1]) + (m1.values[ztMat4_Col2Row3] * m2.values[ztMat4_Col3Row2]) + (m1.values[ztMat4_Col3Row3] * m2.values[ztMat4_Col3Row3]);
}

// ------------------------------------------------------------------------------------------------

ztMat4 ztMat4::getMultiply(const ztMat4& mat) const
{
	ztMat4 copy(*this);
	copy.multiply(mat);
	return copy;
}

// ------------------------------------------------------------------------------------------------

ztVec3 ztMat4::getMultiply(const ztVec3& v) const
{
	return ztVec3((v.x * values[ztMat4_Col0Row0]) + (v.y * values[ztMat4_Col1Row0]) + (v.z * values[ztMat4_Col2Row0]) + values[ztMat4_Col3Row0],
	              (v.x * values[ztMat4_Col0Row1]) + (v.y * values[ztMat4_Col1Row1]) + (v.z * values[ztMat4_Col2Row1]) + values[ztMat4_Col3Row1],
	              (v.x * values[ztMat4_Col0Row2]) + (v.y * values[ztMat4_Col1Row2]) + (v.z * values[ztMat4_Col2Row2]) + values[ztMat4_Col3Row2]);
}

// ------------------------------------------------------------------------------------------------

void ztMat4::transpose()
{
	ztMat4 m(*this);
	values[0] = m.values[ 0]; values[4] = m.values[ 1]; values[ 8] = m.values[ 2]; values[12] = m.values[ 3];
	values[1] = m.values[ 4]; values[5] = m.values[ 5]; values[ 9] = m.values[ 6]; values[13] = m.values[ 7];
	values[2] = m.values[ 8]; values[6] = m.values[ 9]; values[10] = m.values[10]; values[14] = m.values[11];
	values[3] = m.values[12]; values[7] = m.values[13]; values[11] = m.values[14]; values[15] = m.values[15];
}

// ------------------------------------------------------------------------------------------------

ztMat4 ztMat4::getTranspose() const
{
	ztMat4 copy(*this);
	copy.transpose();
	return copy;
}

// ------------------------------------------------------------------------------------------------

void ztMat4::inverse()
{
	ztMat4 m(*this);

	values[ztMat4_Col0Row0] = m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row3] - m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row2] - m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row3] + m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row2] + m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row3] - m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row2];
	values[ztMat4_Col1Row0] = -m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row3] + m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row2] + m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row3] - m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row2] - m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row3] + m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row2];
	values[ztMat4_Col2Row0] = m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col3Row3] - m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row1] - m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col3Row3] + m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row1] + m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row3] - m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row1];
	values[ztMat4_Col3Row0] = -m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col3Row2] + m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row1] + m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col3Row2] - m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row1] - m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row2] + m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row1];

	values[ztMat4_Col0Row1] = -m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row3] + m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row2] + m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row3] - m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row2] - m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row3] + m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row2];
	values[ztMat4_Col1Row1] = m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row3] - m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row2] - m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row3] + m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row2] + m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row3] - m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row2];
	values[ztMat4_Col2Row1] = -m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col3Row3] + m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row1] + m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col3Row3] - m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row1] - m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row3] + m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row1];
	values[ztMat4_Col3Row1] = m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col3Row2] - m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row1] - m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col3Row2] + m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row1] + m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row2] - m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row1];

	values[ztMat4_Col0Row2] = m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row3] - m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row2] - m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row3] + m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row2] + m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row3] - m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row2];
	values[ztMat4_Col1Row2] = -m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row3] + m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row2] + m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row3] - m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row2] - m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row3] + m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row2];
	values[ztMat4_Col2Row2] = m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col3Row3] - m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row1] - m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col3Row3] + m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row1] + m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row3] - m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row1];
	values[ztMat4_Col3Row2] = -m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col3Row2] + m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row1] + m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col3Row2] - m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row1] - m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row2] + m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row1];

	values[ztMat4_Col0Row3] = -m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row3] + m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row2] + m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row3] - m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row2] - m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row3] + m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row2];
	values[ztMat4_Col1Row3] = m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row3] - m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row2] - m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row3] + m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row2] + m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row3] - m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row2];
	values[ztMat4_Col2Row3] = -m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row3] + m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row1] + m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row3] - m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row1] - m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row3] + m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row1];
	values[ztMat4_Col3Row3] = m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row2] - m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row1] - m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row2] + m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row1] + m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row2] - m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row1];

	r32 det = m.values[ztMat4_Col0Row0] * values[ztMat4_Col0Row0] +
		m.values[ztMat4_Col0Row1] * values[ztMat4_Col1Row0] +
		m.values[ztMat4_Col0Row2] * values[ztMat4_Col2Row0] +
		m.values[ztMat4_Col0Row3] * values[ztMat4_Col3Row0];

	if (zt_real32Eq(det, 0.f)) {
		*this = zero;
		return;
	}

	det = 1.f / det;
	zt_fiz(16)
		values[i] = values[i] * det;
}

// ------------------------------------------------------------------------------------------------

ztMat4 ztMat4::getInverse() const
{
	ztMat4 copy(*this);
	copy.inverse();
	return copy;
}

// ------------------------------------------------------------------------------------------------

void ztMat4::lookAt(ztVec3 eye_pos, ztVec3 target_pos, ztVec3 up_vec)
{
	ztVec3 d = target_pos - eye_pos;
	ztVec3 f = d.getNormal();
	ztVec3 s = f.cross(up_vec).getNormal();
	ztVec3 u = s.cross(f);

	r32 dot_s = 0;
	r32 dot_u = 0;
	r32 dot_f = 0;

	ztMat4 l;
	l.values[0] =  s.x; l.values[4] =  s.y; l.values[ 8] =  s.z; l.values[12] = 0;
	l.values[1] =  u.x; l.values[5] =  u.y; l.values[ 9] =  u.z; l.values[13] = 0;
	l.values[2] = -f.x; l.values[6] = -f.y; l.values[10] = -f.z; l.values[14] = 0;
	l.values[3] =    0; l.values[7] =    0; l.values[11] =    0; l.values[15] = 1;

	ztMat4 p = identity.getTranslate(-eye_pos.x, -eye_pos.y, -eye_pos.z);
	*this = l * p;
}

// ------------------------------------------------------------------------------------------------

ztMat4 ztMat4::getLookAt(ztVec3 eye_pos, ztVec3 target_pos, ztVec3 up_vec) const
{
	ztMat4 copy(*this);
	copy.lookAt(eye_pos, target_pos, up_vec);
	return copy;
}

// ------------------------------------------------------------------------------------------------

void ztMat4::extract(ztVec3 *position, ztVec3 *rotation, ztVec3 *scale) // does not work well with scaled matrices
{
	ztMat4 m(*this);

	if (position) {
		position->x = m.values[ztMat4_Col3Row0];
		position->y = m.values[ztMat4_Col3Row1];
		position->z = m.values[ztMat4_Col3Row2];
	}

	if (rotation) {
		r32 cos_y_angle = sqrtf(powf(m.values[ztMat4_Row0Col0], 2) +
		                        powf(m.values[ztMat4_Row0Col1], 2));

		rotation->x = atan2f(-m.values[ztMat4_Row1Col2], 
		                      m.values[ztMat4_Row2Col2]);

		r32 sin_x_angle = sinf(rotation->x);
		r32 cos_x_angle = cosf(rotation->x);

		rotation->y = atan2f(m.values[ztMat4_Row0Col2], cos_y_angle);
		rotation->z = atan2f(cos_x_angle * m.values[ztMat4_Row1Col0] +
		                     sin_x_angle * m.values[ztMat4_Row2Col0],
		                     cos_x_angle * m.values[ztMat4_Row1Col1] +
		                     sin_x_angle * m.values[ztMat4_Row2Col1]);

		rotation->x = zt_radiansToDegrees(rotation->x);
		rotation->y = zt_radiansToDegrees(rotation->y);
		rotation->z = zt_radiansToDegrees(rotation->z);
	}

	if (scale) {
		scale->x = ztVec3(m.values[ztMat4_Row0Col0], m.values[ztMat4_Row1Col0], m.values[ztMat4_Row2Col0]).length();
		scale->y = ztVec3(m.values[ztMat4_Row0Col1], m.values[ztMat4_Row1Col1], m.values[ztMat4_Row2Col1]).length();
		scale->z = ztVec3(m.values[ztMat4_Row0Col2], m.values[ztMat4_Row1Col2], m.values[ztMat4_Row2Col2]).length();
	}
}

// ------------------------------------------------------------------------------------------------

void ztMat4::removeTranslation()
{
	values[ztMat4_Col3Row0] = values[ztMat4_Col3Row1] = values[ztMat4_Col3Row2] = 0;
	//values[ztMat4_Col0Row3] = values[ztMat4_Col1Row3] = values[ztMat4_Col2Row3] = 0;
}

// ------------------------------------------------------------------------------------------------

ztMat4 ztMat4::getRemoveTranslation()
{
	ztMat4 copy(*this);
	copy.removeTranslation();
	return copy;
}

// ------------------------------------------------------------------------------------------------

ztMat4& ztMat4::operator*=(const ztMat4& mat4)
{
	multiply(mat4);
	return *this;
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztMat4 ztMat4::makeOrthoProjection(r32 left, r32 right, r32 top, r32 bottom, r32 near_z, r32 far_z)
{
	r32 m[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	m[ztMat4_Row0Col0] =  2.f / (right - left);
	m[ztMat4_Row1Col1] =  2.f / (top - bottom);
	m[ztMat4_Row2Col2] = -2.f / (far_z - near_z);
	m[ztMat4_Row2Col3] = -near_z / (far_z - near_z);
	m[ztMat4_Row3Col3] = 1;

	return ztMat4(m);
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztMat4 ztMat4::makePerspectiveProjection(r32 angle_of_view, r32 width, r32 height, r32 near_z, r32 far_z)
{
	const r32 k = 1.0f / tanf(angle_of_view / 2.0f);
	const r32 c = (near_z + far_z) / (far_z - near_z);

	r32 m[16];

	m[0] = k * height / width; m[4] = 0; m[ 8] =  0;  m[12] = 0;
	m[1] = 0;                  m[5] = k; m[ 9] =  0;  m[13] = 0;
	m[2] = 0;                  m[6] = 0; m[10] = -c;  m[14] = -((2 * near_z * far_z) / (far_z - near_z));
	m[3] = 0;                  m[7] = 0; m[11] = -1;  m[15] = 0;

	return ztMat4(m);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

/*static*/ ztInline ztQuat ztQuat::makeFromAxisAngle(r32 axis_x, r32 axis_y, r32 axis_z, r32 angle)
{
	r32 angle_rad = zt_degreesToRadians(angle);
	ztQuat quat(axis_x, axis_y, axis_z, 0);
	quat.xyz.normalize();
	quat.xyz *= zt_sin(.5f * angle_rad);
	quat.w = zt_cos(.5f * angle_rad);
	return quat;
}

// ------------------------------------------------------------------------------------------------

/*static*/ztInline  ztQuat ztQuat::makeFromEuler(r32 x, r32 y, r32 z)
{
	ztQuat qx = makeFromAxisAngle(1, 0, 0, x);
	ztQuat qy = makeFromAxisAngle(0, 1, 0, y);
	ztQuat qz = makeFromAxisAngle(0, 0, 1, z);

	ztQuat q = qy;
	q *= qx;
	q *= qz;

	return q;
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztQuat ztQuat::makeFromMat4(const ztMat4& mat)
{
	r32 four_x_squared_minus_1 = mat.values[ztMat4_Col0Row0] - mat.values[ztMat4_Col1Row1] - mat.values[ztMat4_Col2Row2];
	r32 four_y_squared_minus_1 = mat.values[ztMat4_Col1Row1] - mat.values[ztMat4_Col0Row0] - mat.values[ztMat4_Col2Row2];
	r32 four_z_squared_minus_1 = mat.values[ztMat4_Col2Row2] - mat.values[ztMat4_Col0Row0] - mat.values[ztMat4_Col1Row1];
	r32 four_w_squared_minus_1 = mat.values[ztMat4_Col0Row0] + mat.values[ztMat4_Col1Row1] + mat.values[ztMat4_Col2Row2];

	int biggest_index = 0;
	r32 four_biggest_squared_minus_1 = four_w_squared_minus_1;
	if (four_x_squared_minus_1 > four_biggest_squared_minus_1) { four_biggest_squared_minus_1 = four_x_squared_minus_1; biggest_index = 1; }
	if (four_y_squared_minus_1 > four_biggest_squared_minus_1) { four_biggest_squared_minus_1 = four_y_squared_minus_1; biggest_index = 2; }
	if (four_z_squared_minus_1 > four_biggest_squared_minus_1) { four_biggest_squared_minus_1 = four_z_squared_minus_1; biggest_index = 3; }

	r32 biggest_value = zt_sqrt(four_biggest_squared_minus_1 + 1.f) * .5f;
	r32 mult = .25f / biggest_value;

	const r32 *m = mat.values;
	switch (biggest_index) {
		case 0: return ztQuat((m[ztMat4_Col1Row2] - m[ztMat4_Col2Row1]) * mult, (m[ztMat4_Col2Row0] - m[ztMat4_Col0Row2]) * mult, (m[ztMat4_Col0Row1] - m[ztMat4_Col1Row0]) * mult, biggest_value);
		case 1: return ztQuat(biggest_value                                   , (m[ztMat4_Col0Row1] + m[ztMat4_Col1Row0]) * mult, (m[ztMat4_Col2Row0] + m[ztMat4_Col0Row2]) * mult, (m[ztMat4_Col1Row2] - m[ztMat4_Col2Row1]) * mult);
		case 2: return ztQuat((m[ztMat4_Col0Row1] + m[ztMat4_Col1Row0]) * mult, biggest_value                                   , (m[ztMat4_Col1Row2] + m[ztMat4_Col2Row1]) * mult, (m[ztMat4_Col2Row0] - m[ztMat4_Col0Row2]) * mult);
		case 3: return ztQuat((m[ztMat4_Col2Row0] + m[ztMat4_Col0Row2]) * mult, (m[ztMat4_Col1Row2] + m[ztMat4_Col2Row1]) * mult, biggest_value                                   , (m[ztMat4_Col0Row1] - m[ztMat4_Col1Row0]) * mult);
		default: zt_assert(false);
	}

	return ztQuat::identity;
}

// ------------------------------------------------------------------------------------------------

/*static*/ ztQuat ztQuat::makeFromDirection(const ztVec3& dir, const ztVec3& up)
{
	ztMat4 mat = ztMat4::identity;
	mat.lookAt(ztVec3::zero, ztVec3(dir.x, dir.y, -dir.z), up);

	return ztQuat::makeFromMat4(mat);
}

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

bool zt_strEquals(const char *s1, int s1_len, const char *s2, int s2_len, bool test_case)
{
	if (test_case) {
		return zt_strCmp(s1, s1_len, s2, s2_len) == 0;
	}
	else {
		return zt_striCmp(s1, s1_len, s2, s2_len) == 0;
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_strValid(const char *s, const char **invalid_ch)
{
	while ('\0' != *s) {
		if (0xf0 == (0xf8 & *s)) {
			// ensure each of the 3 following bytes in this 4-byte
			// utf8 codepoint began with 0b10xxxxxx
			if ((0x80 != (0xc0 & s[1])) || (0x80 != (0xc0 & s[2])) ||
				(0x80 != (0xc0 & s[3]))) {
				if (invalid_ch) *invalid_ch = s;
				return false;
			}

			// ensure that our utf8 codepoint ended after 4 bytes
			if (0x80 == (0xc0 & s[4])) {
				if (invalid_ch) *invalid_ch = s;
				return false;
			}

			// ensure that the top 5 bits of this 4-byte utf8
			// codepoint were not 0, as then we could have used
			// one of the smaller encodings
			if ((0 == (0x07 & s[0])) && (0 == (0x30 & s[1]))) {
				if (invalid_ch) *invalid_ch = s;
				return false;
			}

			// 4-byte utf8 code point (began with 0b11110xxx)
			s += 4;
		}
		else if (0xe0 == (0xf0 & *s)) {
			// ensure each of the 2 following bytes in this 3-byte
			// utf8 codepoint began with 0b10xxxxxx
			if ((0x80 != (0xc0 & s[1])) || (0x80 != (0xc0 & s[2]))) {
				if (invalid_ch) *invalid_ch = s;
				return false;
			}

			// ensure that our utf8 codepoint ended after 3 bytes
			if (0x80 == (0xc0 & s[3])) {
				if (invalid_ch) *invalid_ch = s;
				return false;
			}

			// ensure that the top 5 bits of this 3-byte utf8
			// codepoint were not 0, as then we could have used
			// one of the smaller encodings
			if ((0 == (0x0f & s[0])) && (0 == (0x20 & s[1]))) {
				if (invalid_ch) *invalid_ch = s;
				return false;
			}

			// 3-byte utf8 code point (began with 0b1110xxxx)
			s += 3;
		}
		else if (0xc0 == (0xe0 & *s)) {
			// ensure the 1 following byte in this 2-byte
			// utf8 codepoint began with 0b10xxxxxx
			if (0x80 != (0xc0 & s[1])) {
				if (invalid_ch) *invalid_ch = s;
				return false;
			}

			// ensure that our utf8 codepoint ended after 2 bytes
			if (0x80 == (0xc0 & s[2])) {
				if (invalid_ch) *invalid_ch = s;
				return false;
			}

			// ensure that the top 4 bits of this 2-byte utf8
			// codepoint were not 0, as then we could have used
			// one of the smaller encodings
			if (0 == (0x1e & s[0])) {
				if (invalid_ch) *invalid_ch = s;
				return false;
			}

			// 2-byte utf8 code point (began with 0b110xxxxx)
			s += 2;
		}
		else if (0x00 == (0x80 & *s)) {
			// 1-byte ascii (began with 0b0xxxxxxx)
			s += 1;
		}
		else {
			// we have an invalid 0b1xxxxxxx utf8 code point entry
			if (invalid_ch) *invalid_ch = s;
			return false;
		}
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------

const char *zt_strCodepoint(const char *s, i32* code_point)
{
	if (0xf0 == (0xf8 & s[0])) {
		// 4 byte utf8 codepoint
		*code_point = ((0x07 & s[0]) << 18) | ((0x3f & s[1]) << 12) |
			((0x3f & s[2]) << 6) | (0x3f & s[3]);
		s += 4;
	}
	else if (0xe0 == (0xf0 & s[0])) {
		// 3 byte utf8 codepoint
		*code_point =
			((0x0f & s[0]) << 12) | ((0x3f & s[1]) << 6) | (0x3f & s[2]);
		s += 3;
	}
	else if (0xc0 == (0xe0 & s[0])) {
		// 2 byte utf8 codepoint
		*code_point = ((0x1f & s[0]) << 6) | (0x3f & s[1]);
		s += 2;
	}
	else {
		// 1 byte utf8 codepoint otherwise
		*code_point = s[0];
		s += 1;
	}

	return s;
}

// ------------------------------------------------------------------------------------------------

i32 zt_strCodepoint(const char *s, int pos)
{
	i32 code_point = 0;
	s = zt_strMoveForward(s, pos);
	zt_strCodepoint(s, &code_point);
	return code_point;
}

// ------------------------------------------------------------------------------------------------

int zt_strLen(const char *s)
{
	if (!s) return 0;

	int len = 0;
	while (*s) {
		if (0xf0 == (0xf8 & *s)) { s += 4; } // 4-byte utf8 code point (began with 0b11110xxx)
		else if (0xe0 == (0xf0 & *s)) { s += 3; } // 3-byte utf8 code point (began with 0b1110xxxx)
		else if (0xc0 == (0xe0 & *s)) { s += 2; } // 2-byte utf8 code point (began with 0b110xxxxx)
		else { s += 1; } // if (0x00 == (0x80 & *s)) { // 1-byte ascii (began with 0b0xxxxxxx)
		++len;
	}
	return len;
}

// ------------------------------------------------------------------------------------------------

int zt_strSize(const char *s)
{
	if (!s) return 0;

	int size = 0;
	while (s[size]) {
		size++;
	}

	return ++size; // add null terminator
}

// ------------------------------------------------------------------------------------------------

#define _zt_strCmpIsEmpty(s) ((s) == nullptr || *(s) == 0)

int zt_strCmp(const char *s1, const char *s2)
{
	if (_zt_strCmpIsEmpty(s1) || _zt_strCmpIsEmpty(s2)) {
		if (_zt_strCmpIsEmpty(s1) && !_zt_strCmpIsEmpty(s2)) return -1;
		if (!_zt_strCmpIsEmpty(s1) && _zt_strCmpIsEmpty(s2)) return 1;
		return 0;
	}

	while (s1 && s2 && *s1 && *s2 && *s1 == *s2) { ++s1; ++s2; }
	if (*s1 == *s2) return 0;
	if (*s1 < *s2) return -1;
	return 1;
}

// ------------------------------------------------------------------------------------------------

int zt_strCmp(const char *s1, int s1_len, const char *s2, int s2_len)
{
	if (_zt_strCmpIsEmpty(s1) || _zt_strCmpIsEmpty(s2)) {
		if (_zt_strCmpIsEmpty(s1) && !_zt_strCmpIsEmpty(s2)) return -1;
		if (!_zt_strCmpIsEmpty(s1) && _zt_strCmpIsEmpty(s2)) return 1;
		return 0;
	}

	while (s1 && s2 && s1_len-- && s2_len-- && *s1 && *s2 && *s1 == *s2) { ++s1; ++s2; }
	if (*s1 == *s2) return 0;
	if (*s1 < *s2) return -1;
	return 1;
}

// ------------------------------------------------------------------------------------------------

int zt_striCmp(const char *s1, const char *s2)
{
	if (_zt_strCmpIsEmpty(s1) || _zt_strCmpIsEmpty(s2)) {
		if (_zt_strCmpIsEmpty(s1) && !_zt_strCmpIsEmpty(s2)) return -1;
		if (!_zt_strCmpIsEmpty(s1) && _zt_strCmpIsEmpty(s2)) return 1;
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

int zt_striCmp(const char *s1, int s1_len, const char *s2, int s2_len)
{
	if (_zt_strCmpIsEmpty(s1) || _zt_strCmpIsEmpty(s2)) {
		if (_zt_strCmpIsEmpty(s1) && !_zt_strCmpIsEmpty(s2)) return -1;
		if (!_zt_strCmpIsEmpty(s1) && _zt_strCmpIsEmpty(s2)) return 1;
		return 0;
	}

	while (*s1 && *s2 && s1_len-- && s2_len--) {
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

#undef _zt_strCmpIsEmpty

// ------------------------------------------------------------------------------------------------

const char *zt_strMoveForward(const char *s, int characters)
{
	if (!s || characters < 0) return nullptr;

	while (*s && characters-- > 0) {
		if (0xf0 == (0xf8 & *s)) { s += 4; } // 4-byte utf8 code point (began with 0b11110xxx)
		else if (0xe0 == (0xf0 & *s)) { s += 3; } // 3-byte utf8 code point (began with 0b1110xxxx)
		else if (0xc0 == (0xe0 & *s)) { s += 2; } // 2-byte utf8 code point (began with 0b110xxxxx)
		else { s += 1; } // if (0x00 == (0x80 & *s)) { // 1-byte ascii (began with 0b0xxxxxxx)
	}
	return s;
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

int zt_strCat(char *scopy, int scopy_len, const char *sfrom)
{
	return zt_strCat(scopy, scopy_len, sfrom, zt_strLen(sfrom));
}

// ------------------------------------------------------------------------------------------------

int zt_strCat(char *scopy, int scopy_len, const char *sfrom, int sfrom_len)
{
	if (!scopy || scopy_len <= 0) {
		return 0;
	}
	if (!sfrom || sfrom_len <= 0) {
		scopy[0] = 0;
		return 0;
	}

	int start = 0;
	while (*scopy) {
		start += 1;
		scopy++;
	}

	int max_idx = zt_min((scopy_len - start) - 1, sfrom_len);
	zt_fiz(max_idx) {
		scopy[i] = sfrom[i];
	}
	scopy[max_idx] = 0;
	return max_idx + start;
}

// ------------------------------------------------------------------------------------------------

bool zt_strIsInt(char *s)
{
	bool success = false;
	zt_strToInt(s, 0, &success);
	return success;
}

// ------------------------------------------------------------------------------------------------

bool zt_strIsInt(char *s, int s_len)
{
	bool success = false;
	zt_strToInt(s, s_len, 0, &success);
	return success;
}

// ------------------------------------------------------------------------------------------------

bool zt_strIsIntHex(char *s)
{
	bool success = false;
	zt_strToIntHex(s, 0, &success);
	return success;
}

// ------------------------------------------------------------------------------------------------

bool zt_strIsIntHex(char *s, int s_len)
{
	bool success = false;
	zt_strToIntHex(s, s_len, 0, &success);
	return success;
}

// ------------------------------------------------------------------------------------------------

bool zt_strIsReal32(char *s)
{
	bool success = false;
	zt_strToReal32(s, 0, &success);
	return success;
}

// ------------------------------------------------------------------------------------------------

bool zt_strIsReal32(char *s, int s_len)
{
	bool success = false;
	zt_strToReal32(s, s_len, 0, &success);
	return success;
}

// ------------------------------------------------------------------------------------------------

bool zt_strIsReal64(char *s)
{
	bool success = false;
	zt_strToReal64(s, 0, &success);
	return success;
}

// ------------------------------------------------------------------------------------------------

bool zt_strIsReal64(char *s, int s_len)
{
	bool success = false;
	zt_strToReal64(s, s_len, 0, &success);
	return success;
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
	return zt_strFind(haystack, haystack_len, needle);
}

// ------------------------------------------------------------------------------------------------

const char *zt_strFind(const char *haystack, int haystack_len, const char *needle)
{
	if (haystack_len == 0 || !haystack || !needle) return nullptr;

	while (*haystack && haystack_len-- >= -1) {
		const char *maybe_match = haystack;
		const char *n = (const char *)needle;

		while (*haystack && *n && *haystack == *n) {
			n++;
			haystack++;
		}

		if (!*n) {
			// we found the whole utf8 string for needle in haystack at maybeMatch, so return it
			return maybe_match;
		}
		else {
			// h could be in the middle of an unmatching utf8 codepoint, so we need to march it on to the next character beginning,
			if (*haystack) {
				do {
					haystack++;
				} while (0x80 == (0xc0 & *haystack));
			}
		}
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

int zt_strFindPos(const char *haystack, const char *needle, int start_pos)
{
	int haystack_len = zt_strLen(haystack);
	return zt_strFindPos(haystack, haystack_len, needle, start_pos);
}

// ------------------------------------------------------------------------------------------------

int zt_strFindPos(const char *haystack, int haystack_len, const char *needle, int start_pos)
{
	if (haystack_len == 0 || !haystack || !needle || start_pos < 0) return -1;

	const char *haystack_orig = haystack;
	haystack = zt_strMoveForward(haystack, start_pos);
	haystack_len -= start_pos;

	while (*haystack && haystack_len-- >= -1) {
		const char *maybe_match = haystack;
		const char *n = (const char *)needle;

		while (*haystack && *n && *haystack == *n) {
			n++;
			haystack++;
		}

		if (!*n) {
			// we found the whole utf8 string for needle in haystack at maybeMatch, so return it
			return (int)(maybe_match - haystack_orig);
		}
		else {
			// h could be in the middle of an unmatching utf8 codepoint, so we need to march it on to the next character beginning,
			if (*haystack) {
				do {
					haystack++;
				} while (0x80 == (0xc0 & *haystack));
			}
		}
	}

	return ztStrPosNotFound;
}

// ------------------------------------------------------------------------------------------------

const char *zt_strFindLast(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	return zt_strFindLast(haystack, haystack_len, needle);
}

// ------------------------------------------------------------------------------------------------

const char *zt_strFindLast(const char *haystack, int haystack_len, const char *needle)
{
	if (haystack_len == 0 || !haystack || !needle) return nullptr;

	const char *found = zt_strFind(haystack, haystack_len, needle);
	if (!found) return nullptr;

	while (found) {
		const char *next = zt_strFind(found + 1, (int)(haystack_len - ((found + 1) - haystack)), needle);
		if (!next) {
			return found;
		}
		found = next;
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

int zt_strFindLastPos(const char *haystack, const char *needle, int start_pos)
{
	int haystack_len = zt_strLen(haystack);
	return zt_strFindLastPos(haystack, haystack_len, needle, start_pos);
}

// ------------------------------------------------------------------------------------------------

int zt_strFindLastPos(const char *haystack, int haystack_len, const char *needle, int start_pos)
{
	if (haystack_len == 0 || !haystack || !needle) return -1;

	if (start_pos < 0) {
		start_pos = haystack_len - 1;
	}
	else if (start_pos > haystack_len) {
		start_pos = haystack_len - 1;
	}

	for (i32 i = start_pos; i >= 0; --i) {
		const char *h = zt_strMoveForward(haystack, i);
		const char *n = needle;

		while (*h && *n && *h == *n) {
			n++;
			h++;
		}

		if (!*n) {
			return i;
		}
	}

	return ztStrPosNotFound;
}

// ------------------------------------------------------------------------------------------------

#define _zt_to_upper(c)	((c) >= 97 && (c) <= 122 ? (c) - 32 : (c))

const char *zt_striFind(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	return zt_striFind(haystack, haystack_len, needle);
}

// ------------------------------------------------------------------------------------------------

const char *zt_striFind(const char *haystack, int haystack_len, const char *needle)
{
	if (haystack_len == 0 || !haystack || !needle) return nullptr;

	while (*haystack && haystack_len-- >= -1) {
		const char *maybe_match = haystack;
		const char *n = (const char *)needle;

		while (*haystack && *n && _zt_to_upper(*haystack) == _zt_to_upper(*n)) {
			n++;
			haystack++;
		}

		if (!*n) {
			// we found the whole utf8 string for needle in haystack at maybeMatch, so return it
			return maybe_match;
		}
		else {
			// h could be in the middle of an unmatching utf8 codepoint, so we need to march it on to the next character beginning,
			if (*haystack) {
				do {
					haystack++;
				} while (0x80 == (0xc0 & *haystack));
			}
		}
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

int zt_striFindPos(const char *haystack, const char *needle, int start_pos)
{
	int haystack_len = zt_strLen(haystack);
	return zt_striFindPos(haystack, haystack_len, needle, start_pos);
}

// ------------------------------------------------------------------------------------------------

int zt_striFindPos(const char *haystack, int haystack_len, const char *needle, int start_pos)
{
	if (haystack_len == 0 || !haystack || !needle || start_pos < 0) return -1;

	const char *haystack_orig = haystack;
	haystack = zt_strMoveForward(haystack, start_pos);
	haystack_len -= start_pos;

	while (*haystack && haystack_len-- >= -1) {
		const char *maybe_match = haystack;
		const char *n = (const char *)needle;

		while (*haystack && *n && _zt_to_upper(*haystack) == _zt_to_upper(*n)) {
			n++;
			haystack++;
		}

		if (!*n) {
			// we found the whole utf8 string for needle in haystack at maybeMatch, so return it
			return (int)(maybe_match - haystack_orig);
		}
		else {
			// h could be in the middle of an unmatching utf8 codepoint, so we need to march it on to the next character beginning,
			if (*haystack) {
				do {
					haystack++;
				} while (0x80 == (0xc0 & *haystack));
			}
		}
	}

	return -1;
}

// ------------------------------------------------------------------------------------------------

const char *zt_striFindLast(const char *haystack, const char *needle)
{
	int haystack_len = zt_strLen(haystack);
	return zt_striFindLast(haystack, haystack_len, needle);
}

// ------------------------------------------------------------------------------------------------

const char *zt_striFindLast(const char *haystack, int haystack_len, const char *needle)
{
	if (haystack_len == 0 || !haystack || !needle) return nullptr;

	const char *found = zt_striFind(haystack, haystack_len, needle);
	if (!found) return nullptr;

	while (found) {
		const char *next = zt_striFind(found + 1, (int)(haystack_len - ((found + 1) - haystack)), needle);
		if (!next) {
			return found;
		}
		found = next;
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

int zt_striFindLastPos(const char *haystack, const char *needle, int start_pos)
{
	int haystack_len = zt_strLen(haystack);
	return zt_striFindLastPos(haystack, haystack_len, needle, start_pos);
}

// ------------------------------------------------------------------------------------------------

int zt_striFindLastPos(const char *haystack, int haystack_len, const char *needle, int start_pos)
{
	if (haystack_len == 0 || !haystack || !needle) return -1;

	if (start_pos < 0) {
		start_pos = haystack_len - 1;
	}
	else if (start_pos > haystack_len) {
		start_pos = haystack_len - 1;
	}

	for (i32 i = start_pos; i >= 0; --i) {
		const char *h = zt_strMoveForward(haystack, i);
		const char *n = needle;

		while (*h && *n && _zt_to_upper(*h) == _zt_to_upper(*n)) {
			n++;
			h++;
		}

		if (!*n) {
			return i;
		}
	}

	return -1;
}

// ------------------------------------------------------------------------------------------------

int zt_strCount(const char *haystack, const char *needle)
{
	return zt_strCount(haystack, zt_strLen(haystack), needle);
}

// ------------------------------------------------------------------------------------------------

int zt_strCount(const char *haystack, int haystack_len, const char *needle)
{
	int count = 0;
	int pos = zt_strFindPos(haystack, haystack_len, needle, 0);
	while(pos != ztStrPosNotFound) {
		count += 1;
		pos = zt_strFindPos(haystack, haystack_len, needle, pos + 1);
	}

	return count;
}

// ------------------------------------------------------------------------------------------------

int zt_striCount(const char *haystack, const char *needle)
{
	return zt_striCount(haystack, zt_strLen(haystack), needle);
}

// ------------------------------------------------------------------------------------------------

int zt_striCount(const char *haystack, int haystack_len, const char *needle)
{
	int count = 0;
	int pos = zt_striFindPos(haystack, haystack_len, needle, 0);
	while(pos != ztStrPosNotFound) {
		count += 1;
		pos = zt_striFindPos(haystack, haystack_len, needle, pos + 1);
	}

	return count;
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

bool zt_striStartsWith(const char *s, const char *starts_with)
{
	return zt_striStartsWith(s, zt_strLen(s), starts_with, zt_strLen(starts_with));
}

// ------------------------------------------------------------------------------------------------

bool zt_striStartsWith(const char *s, int s_len, const char *starts_with, int sw_len)
{
	if (!s || !starts_with || s_len <= 0 || sw_len <= 0 || s_len < sw_len) return false;

	zt_fiz(sw_len) {
		if (_zt_to_upper(s[i]) != _zt_to_upper(starts_with[i]))
			return false;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_striEndsWith(const char *s, const char *ends_with)
{
	return zt_striEndsWith(s, zt_strLen(s), ends_with, zt_strLen(ends_with));
}

// ------------------------------------------------------------------------------------------------

bool zt_striEndsWith(const char *s, int s_len, const char *ends_with, int ew_len)
{
	if (!s || !ends_with || s_len <= 0 || ew_len <= 0 || s_len < ew_len) return false;

	for (int i = s_len - ew_len, e = 0; i < s_len; ++i, ++e) {
		if (_zt_to_upper(s[i]) != _zt_to_upper(ends_with[e]))
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

int zt_strGetBetween(char *buffer, int buffer_len, const char *s, const char *beg, const char *end, int beg_offset, int end_offset)
{
	return zt_strGetBetween(buffer, buffer_len, s, zt_strLen(s), beg, end, beg_offset, end_offset);
}

// ------------------------------------------------------------------------------------------------

int zt_strGetBetween(char *buffer, int buffer_len, const char *s, int s_len, const char *beg, const char *end, int beg_offset, int end_offset)
{
	if (buffer_len == 0 || !s || s_len <= 0) {
		return 0;
	}

	int beg_len = zt_strLen(beg);
	int end_len = zt_strLen(end);

	int beg_pos = beg_len == 0 ? 0 : zt_strFindPos(s, s_len, beg, 0);
	if (beg_pos == ztStrPosNotFound) {
		return 0;
	}
	beg_pos += beg_len + beg_offset;

	int end_pos = end_len == 0 ? s_len : zt_strFindPos(s, s_len, end, beg_pos);
	if (end_pos == ztStrPosNotFound) {
		return 0;
	}
	end_pos += end_offset;

	if (beg_pos >= end_pos || beg_pos >= s_len) {
		return 0;
	}

	const char *str_beg = zt_strMoveForward(s, beg_pos);
	return zt_strCpy(buffer, buffer_len, str_beg, end_pos - beg_pos);
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
	bool prev_was_escape = false;
	int whitespace_run = 0;
	int t_idx = 0;

	ztToken dummy_token;
	ztToken* ctok = t_idx < results_count ? &results[t_idx] : &dummy_token;
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

				ctok = t_idx < results_count ? &results[t_idx] : &dummy_token;
				if (ctok) {
					ctok->beg = i + 1;
					ctok->len = 0;
				}
				in_quotes = false;
			}
			else {
				if (ctok)  {
					ctok->len += 1;
				}
				prev_was_escape = s[i] == '\\';
			}
		}
		else {
			if (process_quotes && s[i] == '\"') {
				if (!keep_quotes) {
					if (!ctok || ctok->len != 0)
						t_idx += 1;

					ctok = t_idx < results_count ? &results[t_idx] : &dummy_token;
					if (ctok) {
						ctok->beg = i + (keep_quotes ? 0 : 1);
						ctok->len = keep_quotes ? 1 : 0;
					}
				}
				else if (ctok) {
					ctok->len += 1;
				}
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
						ctok = t_idx < results_count ? &results[t_idx] : &dummy_token;
						if (include_tokens) {
							if (ctok) {
								ctok->beg = i;
								ctok->len = 1;
							}
							t_idx += 1;
							ctok = t_idx < results_count ? &results[t_idx] : &dummy_token;
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
			if (*number >= div) {
				int64 num = *number / div;
				if (*first) {
					sprintf_s(*buffer, 5, "%lld,", num);
					*first = false;
				}
				else {
					sprintf_s(*buffer, 5, "%03lld,", num);
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
		return (int)((buffer_pos - buffer) + zt_strPrintf(buffer_pos, 4, "%lld", number));
	}

	return (int)((buffer_pos - buffer) + zt_strPrintf(buffer_pos, 4, "%03lld", number));
}

// ------------------------------------------------------------------------------------------------

int zt_strConvertToUTF16(const char* s, int s_len, u16* buffer, int buffer_size)
{
#if defined(ZT_WINDOWS)
	if (!s || s_len < 0 || !buffer || buffer_size <= 0)
		return 0;

	int len = MultiByteToWideChar(CP_ACP, 0, s, s_len, (LPWSTR)buffer, buffer_size);
	len = zt_clamp(len, 0, buffer_size - 1);

	buffer[len] = 0;

	return len; 
#else
#error zt_strConvertToUTF16 needs an implementation for this platform.
#endif
}

// ------------------------------------------------------------------------------------------------

ztString zt_stringMake(int size, ztMemoryArena *arena)
{
	if (size < 60) {
		size = 60;
	}

	size += zt_sizeof(i32);

	void *data = zt_memAlloc(arena, size);
	*((i32*)data) = size - zt_sizeof(i32);

	char *result = (char*)data + zt_sizeof(i32);
	*result = 0;

	return result;
}

// ------------------------------------------------------------------------------------------------

ztString zt_stringMakeFrom(const char *str, ztMemoryArena *arena)
{
	int size = zt_strSize(str);
	if (size == 0) {
		return nullptr;
	}

	ztString result = zt_stringMake(size, arena);
	zt_strCpy(result, size, str);
	return result;
}

// ------------------------------------------------------------------------------------------------

ztString zt_stringMakeFrom(const char *str, int s_len, ztMemoryArena *arena)
{
	int size = s_len;
	if (size == 0) {
		return nullptr;
	}
	size += 1;

	ztString result = zt_stringMake(size, arena);
	zt_strCpy(result, size, str);
	return result;
}

// ------------------------------------------------------------------------------------------------

ztString zt_stringOverwrite(ztString string, const char *str, ztMemoryArena *arena)
{
	int size = zt_strSize(str);
	if (size == 0) {
		return nullptr;
	}

	ztString result = zt_stringResize(string, size, arena);
	zt_strCpy(result, size, str);
	return result;
}

// ------------------------------------------------------------------------------------------------

ztString zt_stringResize(ztString string, int nsize, ztMemoryArena *arena)
{
	if (string == nullptr) {
		return zt_stringMake(nsize, arena);
	}

	i32 size = *((i32*)(string - zt_sizeof(i32)));
	if (size >= nsize) {
		return string;
	}

	zt_stringFree(string, arena);
	return zt_stringMake(nsize, arena);
}

// ------------------------------------------------------------------------------------------------

void zt_stringFree(ztString string, ztMemoryArena *arena)
{
	if (string) {
		void *data = (string - zt_sizeof(i32));
		zt_freeArena(data, arena);
	}
}

// ------------------------------------------------------------------------------------------------

int zt_stringSize(ztString string)
{
	if (string == nullptr) {
		return 0;
	}

	return *((i32*)(string - zt_sizeof(i32)));
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool zt_fileOpen(ztFile *file, const char *file_name, ztFileOpenMethod_Enum file_open_method, ztMemoryArena *arena)
{
	zt_returnValOnNull(file, false);
	zt_returnValOnNull(file_name, false);

	zt_memSet(file, zt_sizeof(ztFile), 0);

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
	zt_strCpy(file->full_name, path_len + 1, ofs.szPathName, path_len);
	file->arena = arena;

	file->open_method = file_open_method;
	file->size = GetFileSize((HANDLE)hfile, nullptr);

	file->win_file_handle = (i32)hfile;
	file->win_read_pos = 0;

	if (file_open_method == ztFileOpenMethod_WriteAppend) {
		zt_fileSetReadPos(file, file->size);
	}

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
	zt_memSet(file, zt_sizeof(ztFile), 0);
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

void zt_fileSetCurrentPath(const char *path)
{
#if defined(ZT_WINDOWS)
	SetCurrentDirectoryA(path);
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileGetFileInOtherFileDirectory(char * buffer, int buffer_size, char *file_only, char *other_file_full_path)
{
	int posEnd = zt_strFindLastPos(other_file_full_path, ztFilePathSeparatorStr);
	if (posEnd == ztStrPosNotFound) {
		posEnd = zt_strFindLastPos(other_file_full_path, "/");
		if (posEnd == ztStrPosNotFound) {
			posEnd = zt_strFindLastPos(other_file_full_path, "\\");
		}
	}
	if (posEnd == ztStrPosNotFound) {
		return zt_strCpy(buffer, buffer_size, file_only);
	}

	char path_only[ztFileMaxPath];
	zt_strCpy(path_only, ztFileMaxPath, other_file_full_path, posEnd + 1);

	return zt_strPrintf(buffer, buffer_size, "%s%s", path_only, file_only);
}

// ------------------------------------------------------------------------------------------------

i32 zt_fileConcatFileToPath(char *buffer, int buffer_size, const char *path, const char *cfile)
{
	char *file = (char*)cfile;

	int dirs_back = 0;
	while (zt_strStartsWith(file, "..")) {
		dirs_back += 1;
		file += 3;
	}

	int dir_end = zt_strLen(path);
	zt_fiz(dirs_back) {
		int pos_dir_sep = zt_max(zt_strFindLastPos(path, "\\", dir_end - 1), zt_strFindLastPos(path, "/", dir_end - 1));
		if (pos_dir_sep != ztStrPosNotFound) {
			dir_end = pos_dir_sep;
		}
	}

	int buffer_size_orig = buffer_size;
	zt_strCpy(buffer, buffer_size, path, dir_end);
	buffer += dir_end;
	buffer_size -= dir_end;
	if (!zt_strEndsWith(path, ztFilePathSeparatorStr) && !zt_strStartsWith(file, ztFilePathSeparatorStr)) {
		zt_strCpy(buffer, buffer_size, ztFilePathSeparatorStr, 1);
		buffer += 1;
		buffer_size -= 1;
	}
	zt_strCpy(buffer, buffer_size, file);

	return buffer_size_orig - buffer_size;
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

i32 zt_fileSize(const char *file_name)
{
#if defined(ZT_WINDOWS)
	OFSTRUCT ofs;
	u32 style = OF_READ;

	HFILE hfile = OpenFile(file_name, &ofs, style);
	if (hfile == HFILE_ERROR) {
		return 0;
	}

	DWORD size = GetFileSize((HANDLE)hfile, NULL);
	CloseHandle((HANDLE)hfile);

	return (i32)size;
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_fileModified(const char *file_name, i32 *year, i32 *month, i32 *day, i32 *hour, i32 *minute, i32 *second, i32 *ms)
{
#if defined(ZT_WINDOWS)
	OFSTRUCT ofs;
	u32 style = OF_READ;

	HFILE hfile = OpenFile(file_name, &ofs, style);
	if (hfile == HFILE_ERROR) {
		return 0;
	}
	FILETIME creation, access, write;
	BOOL result = GetFileTime((HANDLE)hfile, &creation, &access, &write);
	CloseHandle((HANDLE)hfile);

	SYSTEMTIME modified;
	if (result != FALSE && FileTimeToSystemTime(&write, &modified) != FALSE) {
		if (year) *year = modified.wYear;
		if (month) *month = modified.wMonth;
		if (day) *day = modified.wDay;
		if (hour) *hour = modified.wHour;
		if (minute) *minute = modified.wMinute;
		if (second) *second = modified.wSecond;
		if (ms) *ms = modified.wMilliseconds;
		return true;
	}

	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_fileModified(const char *file_name, i64* date_time)
{
#if defined(ZT_WINDOWS)
	OFSTRUCT ofs;
	u32 style = OF_READ;

	HFILE hfile = OpenFile(file_name, &ofs, style);
	if (hfile == HFILE_ERROR) {
		return 0;
	}
	FILETIME creation, access, write;
	BOOL result = GetFileTime((HANDLE)hfile, &creation, &access, &write);
	CloseHandle((HANDLE)hfile);

	if (result != FALSE) {
		if (date_time) {
			i32* dt = (i32*)date_time;
			*dt++ = write.dwLowDateTime;
			*dt = write.dwHighDateTime;
		}
		return true;
	}

	return false;
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

i32 zt_fileWrite(ztFile *file, const void *buffer, i32 buffer_size)
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

bool zt_fileWritef(ztFile *file, const char *format, ...)
{
#if defined(ZT_WINDOWS)
	va_list arg_ptr;
	va_start(arg_ptr, format);
	char buffer[1024 * 16];
	vsnprintf_s(buffer, zt_elementsOf(buffer), zt_elementsOf(buffer), format, arg_ptr);

	return zt_fileWrite(file, buffer);
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

void *zt_readEntireFile(const char *file_name, i32 *file_size, bool discard_utf_bom, ztMemoryArena *arena)
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

	if (discard_utf_bom && bytes_read >= 3) {
		char *bytes = (char*)data;
		if ((byte)bytes[0] == 0xEF && (byte)bytes[1] == 0xBB && (byte)bytes[2] == 0xBF) {
			zt_fiz(bytes_read - 3) {
				bytes[i] = bytes[i + 3];
			}
			bytes_read -= 3;
		}
	}

	return data;
}

// ------------------------------------------------------------------------------------------------

i32 zt_readEntireFile(const char *file_name, void *buffer, i32 buffer_size, bool discard_utf_bom)
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

	if (discard_utf_bom && bytes_read >= 3) {
		char *bytes = (char*)buffer;
		if ((byte)bytes[0] == 0xEF && (byte)bytes[1] == 0xBB && (byte)bytes[2] == 0xBF) {
			zt_fiz(bytes_read - 3) {
				bytes[i] = bytes[i + 3];
			}
			bytes_read -= 3;
		}
	}

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

bool zt_directoryExists(const char *dir)
{
#if defined(ZT_WINDOWS)
	DWORD attribs = GetFileAttributesA(dir);
	return (attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY));
#else
#error zt_directoryExists needs an implementation for this platform
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_directoryMake(const char *dir)
{
#if defined(ZT_WINDOWS)
	return FALSE != CreateDirectoryA(dir, NULL);
#else
#error zt_directoryMake needs an implementation for this platform
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_directoryDelete(const char *dir, bool force)
{
#if defined(ZT_WINDOWS)
	if (RemoveDirectoryA(dir) == TRUE) {
		return true;
	}
	if (!force) {
		return false;
	}

	int dir_list_size = 1024 * 1024;
	char *dir_list_buff = zt_mallocStructArray(char, dir_list_size);
	zt_getDirectoryFiles(dir, dir_list_buff, dir_list_size, true);

	const char *dir_list = zt_strFind(dir_list_buff, "\n");
	while (dir_list) {
		char file[ztFileMaxPath];
		int pos_end = zt_strFindPos(dir_list, "\n", 0);
		zt_strCpy(file, zt_elementsOf(file), dir_list, pos_end - 1);

		zt_fileDelete(file);

		dir_list = zt_strMoveForward(dir_list, pos_end);
	}

	zt_getDirectorySubs(dir, dir_list_buff, dir_list_size, true);
	dir_list = zt_strFind(dir_list_buff, "\n");
	while (dir_list) {
		char file[ztFileMaxPath];
		int pos_end = zt_strFindPos(dir_list, "\n", 0);
		zt_strCpy(file, zt_elementsOf(file), dir_list, pos_end - 1);

		zt_directoryDelete(file, false);

		dir_list = zt_strMoveForward(dir_list, pos_end);
	}

	zt_free(dir_list);

	return FALSE != RemoveDirectoryA(dir);
#else
#error zt_directoryMake needs an implementation for this platform
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_getDirectorySubs(const char *directory, char *buffer, i32 buffer_size, bool recursive)
{
#if defined(ZT_WINDOWS)
	i32 buffer_used = 0;

	bool end_sep = zt_strEndsWith(directory, ztFilePathSeparatorStr);
	char *dir_full = (char *)zt_memAllocGlobal(ztFileMaxPath);
	int dir_len = zt_strLen(directory);

	if (!end_sep) {
		zt_strPrintf(dir_full, ztFileMaxPath, "%s%c*", directory, ztFilePathSeparator);
		dir_len += 1;
	}
	else {
		zt_strPrintf(dir_full, ztFileMaxPath, "%s*", directory);
	}

	WIN32_FIND_DATAA file_data;
	HANDLE hfile = FindFirstFileA(dir_full, &file_data);
	while(hfile != INVALID_HANDLE_VALUE) {
		if (zt_bitIsSet(file_data.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY)) {
			i32 len = zt_strLen(file_data.cFileName);
			if (dir_len + len + buffer_used >= buffer_size) {
				break;
			}
			if (!(len == 1 && file_data.cFileName[0] == '.' || len == 2 && file_data.cFileName[0] == '.' && file_data.cFileName[1] == '.')) {
				int buff_before = buffer_used;
				if (!end_sep) {
					buffer_used += zt_strPrintf(buffer + buffer_used, buffer_size - buffer_used, "%s%c%s", directory, ztFilePathSeparator, file_data.cFileName);
				}
				else {
					buffer_used += zt_strPrintf(buffer + buffer_used, buffer_size - buffer_used, "%s%s", directory, ztFilePathSeparator, file_data.cFileName);
				}
				buffer[buffer_used++] = '\n';

				if (recursive) {
					char* dir_buffer = (char *)zt_memAllocGlobal(ztFileMaxPath);
					zt_strCpy(dir_buffer, ztFileMaxPath, buffer + buff_before, (buffer_used - 1) - buff_before);

					int used = zt_getDirectorySubs(dir_buffer, buffer + buffer_used, buffer_size - buffer_used, true);
					if (used != 0) {
						buffer_used += used;
						buffer[buffer_used] = '\n';
					}

					zt_free(dir_buffer);
				}
			}
		}
		if (!FindNextFileA(hfile, &file_data)) break;
	}

	zt_free(dir_full);

	buffer[buffer_used] = 0;
	return buffer_used;
#else
#error zt_getDirectorySubs needs an implementation for this platform
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_getDirectoryFiles(const char *directory, char *buffer, i32 buffer_size, bool recursive)
{
#if defined(ZT_WINDOWS)
	i32 buffer_used = 0;

	bool end_sep = zt_strEndsWith(directory, ztFilePathSeparatorStr);
	char *dir_full = (char *)zt_memAllocGlobal(ztFileMaxPath);
	int dir_len = zt_strLen(directory);

	if (!end_sep) {
		zt_strPrintf(dir_full, ztFileMaxPath, "%s%c*", directory, ztFilePathSeparator);
		dir_len += 1;
	}
	else {
		zt_strPrintf(dir_full, ztFileMaxPath, "%s*", directory);
	}

	WIN32_FIND_DATAA file_data;
	HANDLE hfile = FindFirstFileA(dir_full, &file_data);
	while (hfile != INVALID_HANDLE_VALUE) {
		if (recursive && zt_bitIsSet(file_data.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY)) {
			i32 len = zt_strLen(file_data.cFileName);
			if (!(len == 1 && file_data.cFileName[0] == '.' || len == 2 && file_data.cFileName[0] == '.' && file_data.cFileName[1] == '.')) {
				char* dir_buffer = (char *)zt_memAllocGlobal(ztFileMaxPath);
				if (!end_sep) {
					zt_strPrintf(dir_buffer, ztFileMaxPath, "%s%c%s", directory, ztFilePathSeparator, file_data.cFileName);
				}
				else {
					zt_strPrintf(dir_buffer, ztFileMaxPath, "%s%s", directory, ztFilePathSeparator, file_data.cFileName);
				}

				int used = zt_getDirectoryFiles(dir_buffer, buffer + buffer_used, buffer_size - buffer_used, true);
				if (used != 0) {
					buffer_used += used;
					buffer[buffer_used] = '\n';
				}

				zt_free(dir_buffer);
			}
		}
		else {
			int buff_before = buffer_used;
			if (!end_sep) {
				buffer_used += zt_strPrintf(buffer + buffer_used, buffer_size - buffer_used, "%s%c%s", directory, ztFilePathSeparator, file_data.cFileName);
			}
			else {
				buffer_used += zt_strPrintf(buffer + buffer_used, buffer_size - buffer_used, "%s%s", directory, ztFilePathSeparator, file_data.cFileName);
			}
			buffer[buffer_used++] = '\n';
		}
		if (!FindNextFileA(hfile, &file_data)) break;
	}

	zt_free(dir_full);

	buffer[buffer_used] = 0;
	return buffer_used;
#else
#error zt_getDirectoryFiles needs an implementation for this platform
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_directoryMonitor(ztDirectoryMonitor *dir_mon, const char *directory, bool recursive, i32 flags)
{
	zt_returnValOnNull(dir_mon, false);
	zt_returnValOnNull(directory, false);

#if defined(ZT_WINDOWS)
	zt_memSet(dir_mon, zt_sizeof(ztDirectoryMonitor), 0);

	dir_mon->io = (pointer)CreateIoCompletionPort((HANDLE)INVALID_HANDLE_VALUE, NULL, 0, 1);
	if (dir_mon->io == NULL) {
		zt_logCritical("Unable to monitor directory (completion port) (%s). Error: %d", directory, GetLastError());
		goto on_error;
	}

	dir_mon->file = (pointer)CreateFileA(directory, FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
	if (dir_mon->file == NULL) {
		zt_logCritical("Unable to monitor directory (open directory) (%s). Error: %d", directory, GetLastError());
		goto on_error;
	}

	dir_mon->flags = flags;
	dir_mon->recursive = recursive;

	if (NULL == CreateIoCompletionPort((HANDLE)dir_mon->file, (HANDLE)dir_mon->io, (ULONG_PTR)dir_mon->file, 0)) {
		zt_logCritical("Unable to monitor directory (associate port) (%s). Error: %d", directory, GetLastError());
		goto on_error;
	}

	DWORD notify_filter = 0;
	if (zt_bitIsSet(flags, ztDirectoryMonitorFlags_New   )) notify_filter |= FILE_NOTIFY_CHANGE_CREATION;
	if (zt_bitIsSet(flags, ztDirectoryMonitorFlags_Rename)) notify_filter |= FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME;
	if (zt_bitIsSet(flags, ztDirectoryMonitorFlags_Modify)) notify_filter |= FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_SECURITY;

	if (!ReadDirectoryChangesW((HANDLE)dir_mon->file, (void*)dir_mon->file_buffer, zt_elementsOf(dir_mon->file_buffer), recursive, notify_filter, NULL, (LPOVERLAPPED)dir_mon->overlapped, NULL)) {
		zt_logCritical("Unable to monitor directory (read directory) (%s). Error: %d", directory, GetLastError());
		goto on_error;
	}

	return true;

on_error:
	CancelIo((HANDLE)dir_mon->file);
	CloseHandle((HANDLE)dir_mon->file);
	CloseHandle((HANDLE)dir_mon->io);
	zt_memSet(dir_mon, zt_sizeof(ztDirectoryMonitor), 0);
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

void zt_directoryStopMonitor(ztDirectoryMonitor *dir_mon)
{
	zt_returnOnNull(dir_mon);

#if defined(ZT_WINDOWS)
	if (dir_mon->file != NULL) {
		CancelIo((HANDLE)dir_mon->file);
		CloseHandle((HANDLE)dir_mon->file);
		CloseHandle((HANDLE)dir_mon->io);
		zt_memSet(dir_mon, zt_sizeof(ztDirectoryMonitor), 0);
	}
#endif
}

// ------------------------------------------------------------------------------------------------

bool zt_directoryMonitorHasChanged(ztDirectoryMonitor *dir_mon)
{
	zt_returnValOnNull(dir_mon, false);

#if defined(ZT_WINDOWS)
	if (dir_mon->io == NULL) {
		return false;
	}

	DWORD bytes_read = 0;
	ULONG_PTR key = NULL;
	OVERLAPPED* overlapped = NULL;

	if (!GetQueuedCompletionStatus((HANDLE)dir_mon->io, &bytes_read, &key, &overlapped, 0)) {
		return false;
	}

	DWORD notify_filter = 0;
	if (zt_bitIsSet(dir_mon->flags, ztDirectoryMonitorFlags_New   )) notify_filter |= FILE_NOTIFY_CHANGE_CREATION;
	if (zt_bitIsSet(dir_mon->flags, ztDirectoryMonitorFlags_Rename)) notify_filter |= FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME;
	if (zt_bitIsSet(dir_mon->flags, ztDirectoryMonitorFlags_Modify)) notify_filter |= FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_SECURITY;

	if (!ReadDirectoryChangesW((HANDLE)dir_mon->file, (void*)dir_mon->file_buffer, zt_elementsOf(dir_mon->file_buffer), dir_mon->recursive, notify_filter, NULL, (LPOVERLAPPED)dir_mon->overlapped, NULL)) {
		zt_directoryStopMonitor(dir_mon);
		return false;
	}

	return key != NULL;
#endif
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#if defined(ZT_WINDOWS)

unsigned int __stdcall _zt_threadProc(LPVOID param)
{
	ztThread *thread = (ztThread*)param;

	if(thread == nullptr || thread->thread == nullptr) {
		return 1;
	}

	int result = thread->thread(thread->thread_id, thread->thread_user_data, thread->exit_test, thread->exit_test_user_data);
	thread->running = false;
	return result;
}

// ------------------------------------------------------------------------------------------------

ztThread *zt_threadMake(ztThread_Func *thread_func, void *user_data, ztThreadExit_Func *exit_test, void *exit_test_user_data, ztThreadID *out_thread_id)
{
	ztThread *thread = zt_mallocStruct(ztThread);
	thread->thread              = thread_func;
	thread->thread_user_data    = user_data;
	thread->exit_test           = exit_test;
	thread->exit_test_user_data = exit_test_user_data;
	thread->running             = true;

	unsigned int thread_id = 0;
	thread->thread_handle = _beginthreadex(nullptr, 0, &_zt_threadProc, thread, 0, &thread_id);
	thread->thread_id = (ztThreadID)thread_id;

	if (out_thread_id) {
		*out_thread_id = thread_id;
	}

	return thread;
}

// ------------------------------------------------------------------------------------------------

void zt_threadFree(ztThread *thread)
{
	if(thread == nullptr) {
		return;
	}

	if(thread->running) {
		zt_threadJoin(thread);
	}

	zt_free(thread);
}

// ------------------------------------------------------------------------------------------------

void zt_threadJoin(ztThread *thread)
{
	zt_returnOnNull(thread);
	WaitForSingleObject((HANDLE)thread->thread_handle, INFINITE);
}

// ------------------------------------------------------------------------------------------------

bool zt_threadIsRunning(ztThread *thread)
{
	zt_returnValOnNull(thread, false);
	return thread->running;
}

// ------------------------------------------------------------------------------------------------

ztThreadID zt_threadGetCurrentID()
{
	return GetCurrentThreadId();
}

// ------------------------------------------------------------------------------------------------

void zt_threadYield()
{
	zt_sleep(0);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztThreadMutex *zt_threadMutexMake()
{
	ztThreadMutex *mutex = zt_mallocStruct(ztThreadMutex);
	InitializeCriticalSection(&mutex->cs);
	return mutex;
}

// ------------------------------------------------------------------------------------------------

void zt_threadMutexFree(ztThreadMutex *mutex)
{
	if(mutex == nullptr) {
		return;
	}

	DeleteCriticalSection(&mutex->cs);
	zt_free(mutex);
}

// ------------------------------------------------------------------------------------------------

void zt_threadMutexLock(ztThreadMutex *mutex)
{
	zt_returnOnNull(mutex);
	EnterCriticalSection(&mutex->cs);
}

// ------------------------------------------------------------------------------------------------

void zt_threadMutexUnlock(ztThreadMutex *mutex)
{
	zt_returnOnNull(mutex);
	LeaveCriticalSection(&mutex->cs);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztThreadMonitor *zt_threadMonitorMake()
{
	ztThreadMonitor *monitor = zt_mallocStruct(ztThreadMonitor);
	monitor->event_handle = (i32)CreateEvent(NULL, TRUE, FALSE, NULL);
	return monitor;
}

// ------------------------------------------------------------------------------------------------

void zt_threadMonitorFree(ztThreadMonitor *monitor)
{
	if(monitor == nullptr) {
		return;
	}

	CloseHandle((HANDLE)monitor->event_handle);
	zt_free(monitor);
}

// ------------------------------------------------------------------------------------------------

void zt_threadMonitorWaitForSignal(ztThreadMonitor *monitor)
{
	zt_returnOnNull(monitor);
	WaitForSingleObject((HANDLE)monitor->event_handle, INFINITE);
}

// ------------------------------------------------------------------------------------------------

void zt_threadMonitorTriggerSignal(ztThreadMonitor *monitor)
{
	zt_returnOnNull(monitor);
	SetEvent((HANDLE)monitor->event_handle);
}

// ------------------------------------------------------------------------------------------------

void zt_threadMonitorReset(ztThreadMonitor *monitor)
{
	zt_returnOnNull(monitor);
	ResetEvent((HANDLE)monitor->event_handle);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

i32 zt_atomicIntInc(ztAtomicInt *atomic_int)
{
	return InterlockedIncrement(atomic_int);
}

// ------------------------------------------------------------------------------------------------

i32 zt_atomicIncDec(ztAtomicInt *atomic_int)
{
	return InterlockedDecrement(atomic_int);
}

// ------------------------------------------------------------------------------------------------

i32 zt_atomicIntSet(ztAtomicInt *atomic_int, i32 value)
{
	return InterlockedExchange(atomic_int, value);
}

// ------------------------------------------------------------------------------------------------

i32 zt_atomicIntGet(ztAtomicInt *atomic_int)
{
	return InterlockedExchange(atomic_int, *atomic_int);
}

// ------------------------------------------------------------------------------------------------

i32 zt_atomicIntAnd(ztAtomicInt *atomic_int, i32 and_val)
{
	return InterlockedAnd(atomic_int, and_val);
}

// ------------------------------------------------------------------------------------------------

i32 zt_atomicIntOr(ztAtomicInt *atomic_int, i32 or_val)
{
	return InterlockedOr(atomic_int, or_val);
}

// ------------------------------------------------------------------------------------------------

i32 zt_atomicIntXor(ztAtomicInt *atomic_int, i32 xor_val)
{
	return InterlockedXor(atomic_int, xor_val);
}

// ------------------------------------------------------------------------------------------------

bool zt_atomicBoolSet(ztAtomicBool *atomic_bool, bool value)
{
	return InterlockedExchange(atomic_bool, value ? 1 : 0) != 0;
}

// ------------------------------------------------------------------------------------------------

bool zt_atomicBoolGet(ztAtomicBool *atomic_bool)
{
	return InterlockedExchange(atomic_bool, *atomic_bool) != 0;
}

// ------------------------------------------------------------------------------------------------

bool zt_atomicBoolToggle(ztAtomicBool *atomic_bool)
{
	return zt_atomicBoolSet(atomic_bool, !zt_atomicBoolGet(atomic_bool));
}

#endif

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

	if (zt_fileWrite(&serial->file, _zt_serial_header, zt_sizeof(_zt_serial_header)) != zt_sizeof(_zt_serial_header))
		return false;

	_zt_serialAddToChecksum(serial, _zt_serial_header, zt_sizeof(_zt_serial_header));

	if (zt_fileWrite(&serial->file, serial->identifier, zt_sizeof(serial->identifier)) != zt_sizeof(serial->identifier))
		return false;

	_zt_serialAddToChecksum(serial, serial->identifier, zt_sizeof(serial->identifier));

	if (!zt_fileWrite(&serial->file, version))
		return false;

	_zt_serialAddToChecksum(serial, &version, zt_sizeof(version));

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

	if (_zt_readData(serial, header, zt_sizeof(header)) != zt_sizeof(header))
		goto on_error;

	if (zt_memCmp(header, _zt_serial_header, zt_sizeof(header)) != 0)
		goto on_error;

	if (_zt_readData(serial, serial->identifier, zt_sizeof(serial->identifier)) != zt_sizeof(serial->identifier))
		goto on_error;

	if (!zt_strEquals(serial->identifier, identifier))
		goto on_error;

	if (_zt_readData(serial, &serial->version, zt_sizeof(serial->version)) != zt_sizeof(serial->version))
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

bool zt_serialMakeWriter(ztSerial *serial, const char *file_name, const char *identifier, i32 version)
{
	zt_returnValOnNull(serial, false);
	zt_returnValOnNull(file_name, false);
	zt_returnValOnNull(identifier, false);

	zt_memSet(serial, zt_sizeof(ztSerial), 0);

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

	zt_memSet(serial, zt_sizeof(ztSerial), 0);

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

	zt_memSet(serial, zt_sizeof(ztSerial), 0);

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

	zt_memSet(serial, zt_sizeof(ztSerial), 0);

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

	zt_memSet(serial, zt_sizeof(ztSerial), 0);

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
		zt_memSet(&serial, zt_sizeof(serial), 0);
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

	zt_memSet(&serial, zt_sizeof(serial), 0);
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
				case ztSerialEntryType_String: { char value[1]; if (!zt_serialRead(serial, value, zt_sizeof(value), nullptr)) return false; break; }
				case ztSerialEntryType_Binary: { char value[1]; if (!zt_serialRead(serial, (void*)value, zt_sizeof(value), nullptr)) return false; break; }

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

bool zt_serialWrite(ztSerial *serial, i8 value) { return _zt_writeData(serial, ztSerialEntryType_i8, &value, zt_sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, i16 value) { return _zt_writeData(serial, ztSerialEntryType_i16, &value, zt_sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, i32 value) { return _zt_writeData(serial, ztSerialEntryType_i32, &value, zt_sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, i64 value) { return _zt_writeData(serial, ztSerialEntryType_i64, &value, zt_sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, u8 value) { return _zt_writeData(serial, ztSerialEntryType_u8, &value, zt_sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, u16 value) { return _zt_writeData(serial, ztSerialEntryType_u16, &value, zt_sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, u32 value) { return _zt_writeData(serial, ztSerialEntryType_u32, &value, zt_sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, u64 value) { return _zt_writeData(serial, ztSerialEntryType_u64, &value, zt_sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, r32 value) { return _zt_writeData(serial, ztSerialEntryType_r32, &value, zt_sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, r64 value) { return _zt_writeData(serial, ztSerialEntryType_r64, &value, zt_sizeof(value)); }
bool zt_serialWrite(ztSerial *serial, bool value) { i8 v = (value ? 1 : 0);  return _zt_writeData(serial, ztSerialEntryType_i8, &v, 1); }

// ------------------------------------------------------------------------------------------------

bool zt_serialWrite(ztSerial *serial, const char *value, i32 value_len)
{
	if (!_zt_writeByte(serial, ztSerialEntryType_String))
		return false;

	if (zt_fileWrite(&serial->file, &value_len, zt_sizeof(value_len)) != zt_sizeof(value_len))
		return false;

	_zt_serialAddToChecksum(serial, &value_len, zt_sizeof(value_len));

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

	if (zt_fileWrite(&serial->file, &value_len, zt_sizeof(value_len)) != zt_sizeof(value_len))
		return false;

	_zt_serialAddToChecksum(serial, &value_len, zt_sizeof(value_len));

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

bool zt_serialRead(ztSerial *serial, i8 *value) { return _zt_readData(serial, ztSerialEntryType_i8, value, zt_sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, i16 *value) { return _zt_readData(serial, ztSerialEntryType_i16, value, zt_sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, i32 *value) { return _zt_readData(serial, ztSerialEntryType_i32, value, zt_sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, i64 *value) { return _zt_readData(serial, ztSerialEntryType_i64, value, zt_sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, u8 *value) { return _zt_readData(serial, ztSerialEntryType_u8, value, zt_sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, u16 *value) { return _zt_readData(serial, ztSerialEntryType_u16, value, zt_sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, u32 *value) { return _zt_readData(serial, ztSerialEntryType_u32, value, zt_sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, u64 *value) { return _zt_readData(serial, ztSerialEntryType_u64, value, zt_sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, r32 *value) { return _zt_readData(serial, ztSerialEntryType_r32, value, zt_sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, r64 *value) { return _zt_readData(serial, ztSerialEntryType_r64, value, zt_sizeof(*value)); }
bool zt_serialRead(ztSerial *serial, bool *value) { i8 ival = 0; if (_zt_readData(serial, ztSerialEntryType_i8, &ival, zt_sizeof(ival))) { *value = ival == 1; return true; } return false; }

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
	if (_zt_readData(serial, &stored_len, zt_sizeof(stored_len)) != zt_sizeof(stored_len))
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
	if (_zt_readData(serial, &stored_len, zt_sizeof(stored_len)) != zt_sizeof(stored_len))
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

	if (idx == ztRandom_MTLen * zt_sizeof(i32))
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
	random->mt_idx = idx + zt_sizeof(unsigned long);
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
	zt_strPrintf(dflt_buffer, zt_sizeof(dflt_buffer), "%d", dflt);
	int len = zt_iniFileGetValue(ini_file, section, key, dflt_buffer, value_buffer, zt_sizeof(value_buffer));
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
	zt_strPrintf(dflt_buffer, zt_sizeof(dflt_buffer), "%f", dflt);
	int len = zt_iniFileGetValue(ini_file, section, key, dflt_buffer, value_buffer, zt_sizeof(value_buffer));
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
// ------------------------------------------------------------------------------------------------
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
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

int zt_processRun(const char *command)
{
	return zt_processRun(command, nullptr, 0, nullptr);
}

// ------------------------------------------------------------------------------------------------

int zt_processRun(const char *command, char *output_buffer, int output_buffer_size, int *output_buffer_written)
{
#	if defined(ZT_WINDOWS)

	HANDLE pipe_read, pipe_write;

	SECURITY_ATTRIBUTES sec_attr = { sizeof(SECURITY_ATTRIBUTES) };
	sec_attr.bInheritHandle = TRUE;   //Pipe handles are inherited by child process.
	sec_attr.lpSecurityDescriptor = NULL;

	// Create a pipe to get results from child's stdout.
	if (!CreatePipe(&pipe_read, &pipe_write, &sec_attr, 0)) {
		return -100;
	}

	STARTUPINFOA si = { sizeof(STARTUPINFOA) };
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.hStdOutput = pipe_write;
	si.hStdError = pipe_write;
	si.wShowWindow = SW_HIDE;       // Prevents cmd window from flashing. Requires STARTF_USESHOWWINDOW in dwFlags.

	PROCESS_INFORMATION pi = { 0 };

	#pragma push_macro("GetEnvironmentStrings")
	#undef GetEnvironmentStrings
	char *curr_env = GetEnvironmentStrings();
	#pragma pop_macro("GetEnvironmentStrings")

	if (FALSE == CreateProcessA(NULL, (LPSTR)command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, curr_env, NULL, &si, &pi))
	{
		CloseHandle(pipe_write);
		CloseHandle(pipe_read);
		return -200;
	}

	bool process_ended = false;
	while(!process_ended) {
		// Give some timeslice (50ms), so we won't waste 100% cpu.
		process_ended = WaitForSingleObject(pi.hProcess, 50) == WAIT_OBJECT_0;

		// Even if process exited - we continue reading, if there is some data available over pipe.
		while (true) {
			char buffer[1024];
			DWORD read = 0, avail = 0;

			if (!PeekNamedPipe(pipe_read, NULL, 0, NULL, &avail, NULL)) {
				break;
			}

			if (avail == 0) { // no data available, return
				break;
			}

			if (!ReadFile(pipe_read, buffer, zt_min(zt_sizeof(buffer) - 1, avail), &read, NULL) || !read) {
				// error, the child process might ended
				break;
			}

			buffer[read] = 0;
			zt_strCpy(output_buffer, output_buffer_size, buffer, read);
			output_buffer += read;
			output_buffer_size -= read;
			if (output_buffer_written) *output_buffer_written += read;
		}
	}

	DWORD result = 0;
	GetExitCodeProcess(pi.hProcess, &result);

	CloseHandle(pipe_write);
	CloseHandle(pipe_read);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return result;
	#else
#		error zt_processRun needs an implementation for this platform
#	endif
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

r64 zt_getTime()
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

	return (((r64)current.QuadPart - start_time.QuadPart) * seconds_per_count);
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

void zt_getDate(int *year, int *month, int *day, int *hour, int *minute, int *second)
{
	time_t tt = time(nullptr);
	tm t;
	localtime_s(&t, &tt);

	if (year) *year = t.tm_year + 1900;
	if (month) *month = t.tm_mon + 1;
	if (day) *day = t.tm_mday;
	if (hour) *hour = t.tm_hour;
	if (minute) *minute = t.tm_min;
	if (second) *second = t.tm_sec;
}

// ------------------------------------------------------------------------------------------------

ztDate zt_getDate()
{
	ztDate dt;
	zt_getDate(&dt.year, &dt.month, &dt.day, &dt.hour, &dt.minute, &dt.second);
	return dt;
}

// ------------------------------------------------------------------------------------------------

bool operator<(ztDate& d1, ztDate& d2)
{
	if (d1.year < d2.year) return true;
	if (d1.year > d2.year) return false;

	if (d1.month < d2.month) return true;
	if (d1.month > d2.month) return false;

	if (d1.day < d2.day) return true;
	if (d1.day > d2.day) return false;

	if (d1.hour < d2.hour) return true;
	if (d1.hour > d2.hour) return false;

	if (d1.minute < d2.minute) return true;
	if (d1.minute > d2.minute) return false;

	if (d1.second < d2.second) return true;
	if (d1.second > d2.second) return false;

	return false;
}

// ------------------------------------------------------------------------------------------------

bool operator>(ztDate& d1, ztDate& d2)
{
	return !(d1 < d2) && !(d1 == d2);
}

// ------------------------------------------------------------------------------------------------

bool operator==(ztDate& d1, ztDate& d2)
{
	return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day && d1.hour == d2.hour && d1.minute == d2.minute && d1.second == d2.second;
}

// ------------------------------------------------------------------------------------------------

bool operator!=(ztDate& d1, ztDate& d2)
{
	return !(d1 == d2);
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#endif // ZT_TOOLS_IMPLEMENTATION

#endif // include guard