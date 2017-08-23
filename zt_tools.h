/***************************************************************************************************************************************************************************************************
	file: zt_tools.h v 0.00 (active initial development)
	
	This software is dual-licensed to the public domain and under the following
	license: you are granted a perpetual, irrevocable license to copy, modify,
	publish, and distribute this file as you see fit.
	
	No warranty is offered or implied.  Use this at your own risk.
	
 ***************************************************************************************************************************************************************************************************
   
    Zero Tolerance Tools Library

	In exactly one cpp source file of your project, you must:

		#define ZT_TOOLS_IMPLEMENTATION
		#include "zt_tools.h"
    
 ***************************************************************************************************************************************************************************************************

    Options:
   
    ZT_TOOLS_RETURN_ON_NULLPTR_NO_ASSERT
   		- Removes the assert on zt_returnOnNull and zt_returnValOnNull macros.
   

 ***************************************************************************************************************************************************************************************************

	Implimentation Options: (only used with ZT_TOOLS_IMPLIMENTATION #include)

	ZT_MAX_LOG_CALLBACKS
		Indicates the maximum number of logging callback functions can exist.

	ZT_MEM_GLOBAL_ARENA_STACK_SIZE
		The size of the global memory arena stack.

	ZT_MEM_ARENA_LOG_DETAILS
		Logs details about every single allocation.  Not recommended unless you're trying to find memory problems.

 ***************************************************************************************************************************************************************************************************/

#ifndef __zt_tools_h_included__
#define __zt_tools_h_included__

// ================================================================================================================================================================================================
// compiler defines
// ================================================================================================================================================================================================

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

#	define ztReal32Max      3.402823466e+38F
#	define ztReal32Min     -3.402823466e+38F
#	define ztReal32Epsilon  1.192092896e-07F

#	define ztReal64Max      1.7976931348623158e+308
#	define ztReal64Min     -1.7976931348623158e+308
#	define ztReal64Epsilon	2.2204460492503131e-016

#	define ztInt32Max       2147483647
#	define ztInt32Min      -2147483647
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


// ================================================================================================================================================================================================
// platform defines
// ================================================================================================================================================================================================

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
#		define ZT_PLATFORM_STR	"Win64 Console"
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


// ================================================================================================================================================================================================
// DLL defines
// ================================================================================================================================================================================================

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


// ================================================================================================================================================================================================
// useful macros
// ================================================================================================================================================================================================

#define zt_elementsOf(native_array)	              ((int)(sizeof(native_array) / sizeof((native_array)[0])))
#define zt_sizeof(type)                           ((i32)sizeof(type))

#if defined(ZT_DEBUG)
#	define zt_assert(cond)	                      if (!(cond)) { zt_assert_raw(#cond, __FILE__, __LINE__); }
#	define zt_assertReturnOnFail(cond)            if (!(cond)) { zt_assert_raw(#cond, __FILE__, __LINE__); return; }
#	define zt_assertReturnValOnFail(cond, retval) if (!(cond)) { zt_assert_raw(#cond, __FILE__, __LINE__); return (retval); }

#	define zt_debugOnly(code)	                  code
#	define zt_releaseOnly(code)
#else
#	define zt_assert(cond)
#	define zt_assertReturnOnFail(cond)            if (!(cond)) { return; }
#	define zt_assertReturnValOnFail(cond, retval) if (!(cond)) { return (retval); }

#	define zt_debugOnly(code)
#	define zt_releaseOnly(code)	code
#endif

#define zt_assertAlways(cond)                     if (!(cond)) { zt_assert_raw(#cond, __FILE__, __LINE__); }
#define zt_staticAssert(cond)                     typedef char _zt_static_assertion_##__COUNTER__[(cond)?1:-1]

#define ztInline                                  inline
#define ztInternal                                static
#define ztPersistent                              static
#define ztGlobal                                  static

#define zt_kilobytes(kb)	                      ((kb) * 1024LL)
#define zt_megabytes(mb)	                      (zt_kilobytes(mb) * 1024LL)
#define zt_gigabytes(gb)	                      (zt_megabytes(gb) * 1024LL)
#define zt_terabytes(tb)	                      (zt_gigabytes(tb) * 1024LL)

#define zt_bit(num)                               (1<<(num))
#define zt_bitAdd(var, flag)                      ((var) |= (flag))
#define zt_bitRemove(var, flag)                   ((var) &= ~(flag))
#define zt_bitIsSet(var, flag)                    (((var) & (flag)) != 0)

#define zt_max(val1, val2)                        ( (val1) > (val2) ? (val1) : (val2) )
#define zt_min(val1, val2)                        ( (val1) < (val2) ? (val1) : (val2) )
#define zt_clamp(val, min, max)                   ( zt_min(max, (zt_max(min, val))) )
#define zt_abs(val)                               ( (val) < 0 ? -(val) : (val) )
#define zt_swap(val1, val2)                       {auto temp = val1; val1 = val2; val2 = temp;}
#define zt_between(val, beg, end)                 (val >= beg && val <= end)

#define zt_real32Eq(val1, val2)                   (zt_max(val1, val2) - zt_min(val1, val2) < ztReal32Epsilon)
#define zt_real64Eq(val1, val2)                   (zt_max(val1, val2) - zt_min(val1, val2) < ztReal64Epsilon)

#define zt_real32Close(val1, val2)                (zt_max(val1, val2) - zt_min(val1, val2) < 0.0001f)
#define zt_real64Close(val1, val2)                (zt_max(val1, val2) - zt_min(val1, val2) < 0.0001f)

// yes, shamelessly "borrowed" from Shawn McGrath
#define zt_fiz(end)                               for (int i = 0; i < (int)(end); ++i)
#define zt_fjz(end)                               for (int j = 0; j < (int)(end); ++j)
#define zt_fkz(end)                               for (int k = 0; k < (int)(end); ++k)
#define zt_fxz(end)                               for (int x = 0; x < (int)(end); ++x)
#define zt_fyz(end)                               for (int y = 0; y < (int)(end); ++y)
#define zt_fzz(end)                               for (int z = 0; z < (int)(end); ++z)
#define zt_fize(end)                              for (int i = 0; i < (int)zt_elementsOf((end)); ++i)
#define zt_fjze(end)                              for (int j = 0; j < (int)zt_elementsOf((end)); ++j)
#define zt_fkze(end)                              for (int k = 0; k < (int)zt_elementsOf((end)); ++k)
#define zt_fxze(end)                              for (int x = 0; x < (int)zt_elementsOf((end)); ++x)
#define zt_fyze(end)                              for (int y = 0; y < (int)zt_elementsOf((end)); ++y)
#define zt_fzze(end)                              for (int z = 0; z < (int)zt_elementsOf((end)); ++z)
#define zt_fizr(beg)                              for (int i = (int)(beg); i >= 0; --i)
#define zt_fjzr(beg)                              for (int j = (int)(beg); j >= 0; --j)
#define zt_fkzr(beg)                              for (int k = (int)(beg); k >= 0; --k)
#define zt_fxzr(beg)                              for (int x = (int)(beg); x >= 0; --x)
#define zt_fyzr(beg)                              for (int y = (int)(beg); y >= 0; --y)
#define zt_fzzr(beg)                              for (int z = (int)(beg); z >= 0; --z)
#define zt_fizre(beg)                             for (int i = (int)zt_elementsOf((beg)); i >= 0; --i)
#define zt_fjzre(beg)                             for (int j = (int)zt_elementsOf((beg)); j >= 0; --j)
#define zt_fkzre(beg)                             for (int k = (int)zt_elementsOf((beg)); k >= 0; --k)
#define zt_fxzre(beg)                             for (int x = (int)zt_elementsOf((beg)); x >= 0; --x)
#define zt_fyzre(beg)                             for (int y = (int)zt_elementsOf((beg)); y >= 0; --y)
#define zt_fzzre(beg)                             for (int z = (int)zt_elementsOf((beg)); z >= 0; --z)
#define zt_flink(var,start)                       for (auto *var = start; var != nullptr; var = var->next)
#define zt_flinknext(var,start,next_var)          for (auto *var = start; var != nullptr; var = var->next_var)

#define ztMathPi                                   3.14159626f
#define ztMathPi2                                  6.28319252f
#define ztMathPi180                                0.01745331f
#define ztMath180Pi                               57.29571374f

#define zt_degreesToRadians(degrees)              ((degrees) * ztMathPi180)
#define zt_radiansToDegrees(radians)              ((radians) * ztMath180Pi)

#if !defined(ZT_TOOLS_RETURN_ON_NULLPTR_NO_ASSERT)
#	define zt_returnOnNull(ptr)                   if (ptr == nullptr) { zt_assert(false); return; }
#	define zt_returnValOnNull(ptr, retval)        if (ptr == nullptr) { zt_assert(false); return retval; };
#else
#	define zt_returnOnNull(ptr)                   if (ptr == nullptr) { return; }
#	define zt_returnValOnNull(ptr, retval)        if (ptr == nullptr) { return retval; };
#endif


// ================================================================================================================================================================================================
// types
// ================================================================================================================================================================================================

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

typedef float              real32;
typedef double             real64;

#if defined(ZT_64BIT)
typedef uint64             pointer;
#else
typedef uint32             pointer;
#endif

typedef int8	           i8;
typedef int16	           i16;
typedef int32	           i32;
typedef int64	           i64;
typedef uint8	           u8;
typedef uint16	           u16;
typedef uint32	           u32;
typedef uint64	           u64;
typedef real32	           r32;
typedef real64	           r64;
typedef int32	           b32;

#endif


// ================================================================================================================================================================================================
// math
// ================================================================================================================================================================================================

struct ztVec2i
{
	union {
		struct {
			i32 x;
			i32 y;
		};
		i32 values[2];
	};

	bool operator==(const ztVec2i& v) const { return x == v.x && y == v.y; }
	bool operator!=(const ztVec2i& v) const { return x != v.x || y != v.y; }
};

ztInline ztVec2i zt_vec2i(i32 x, i32 y) { return { x, y }; }


// ================================================================================================================================================================================================

struct ztVec3i
{
	union {
		struct {
			i32 x;
			i32 y;
			i32 z;
		};
		i32 values[3];
	};

	bool operator==(const ztVec3i& v) const { return x == v.x && y == v.y && z == v.z; }
	bool operator!=(const ztVec3i& v) const { return x != v.x || y != v.y || z != v.z; }
};

ztInline ztVec3i zt_vec3i(i32 x, i32 y, i32 z) { return { x, y, z }; }


// ================================================================================================================================================================================================

struct ztVec4i
{
	union {
		struct {
			i32 x;
			i32 y;
			i32 z;
			i32 w;
		};
		i32 values[4];
	};

	bool operator==(const ztVec4i& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
	bool operator!=(const ztVec4i& v) const { return x != v.x || y != v.y || z != v.z || w != v.w; }
};

ztInline ztVec4i zt_vec4i(i32 x, i32 y, i32 z, i32 w) { return { x, y, z, w }; }


// ================================================================================================================================================================================================

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
	static ztVec2 lerpBerp(const ztVec2& v1, const ztVec2& v2, r32 percent, r32 power);

	static ztVec2 linearRemap(const ztVec2& val, const ztVec2& v1a, const ztVec2& v1b, const ztVec2& v2a, const ztVec2& v2b);

	void normalize();
	ztVec2 getNormal() const;

	void rotate(r32 angle);
	ztVec2 getRotated(r32 angle) const;

	static const ztVec2 zero;
	static const ztVec2 one;
	static const ztVec2 min;
	static const ztVec2 max;
};

ztInline ztVec2 zt_vec2(r32 x, r32 y) { return{ x, y }; }
ztInline ztVec2 zt_vec2(r32 v[2]) { return{ v[0], v[1] }; }

ztInline ztVec2 operator+(const ztVec2& v1, const ztVec2& v2);
ztInline ztVec2 operator-(const ztVec2& v1, const ztVec2& v2);
ztInline ztVec2 operator*(const ztVec2& v1, const ztVec2& v2);
ztInline ztVec2 operator*(const ztVec2& v1, r32 scale);
ztInline ztVec2 operator*(r32 scale, const ztVec2& v1);


// ================================================================================================================================================================================================

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

	ztVec3& operator+=(const ztVec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	ztVec3& operator-=(const ztVec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	ztVec3& operator*=(r32 v) { x *= v; y *= v; z *= v; return *this; }
	ztVec3& operator*=(const ztVec3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }

	bool operator==(const ztVec3& v) const { return x == v.x && y == v.y && z == v.z; }
	bool operator!=(const ztVec3& v) const { return x != v.x || y != v.y || z != v.z; }

	bool equalsClose(const ztVec3& v) const { return zt_real32Close(x, v.x) && zt_real32Close(y, v.y) && zt_real32Close(z, v.z); }

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
	static ztVec3 lerpBerp(const ztVec3& v1, const ztVec3& v2, r32 percent, r32 power);

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


ztInline ztVec3 zt_vec3(r32 x, r32 y, r32 z) { return { x, y, z }; }
ztInline ztVec3 zt_vec3(const ztVec2& v, r32 z) { return { v.x, v.y, z }; }
ztInline ztVec3 zt_vec3(r32 v[3]) { return { v[0], v[1], v[2] }; }

ztInline ztVec3 operator+(const ztVec3& v1, const ztVec3& v2);
ztInline ztVec3 operator-(const ztVec3& v1, const ztVec3& v2);
ztInline ztVec3 operator*(const ztVec3& v1, const ztVec3& v2);
ztInline ztVec3 operator*(const ztVec3& v1, r32 scale);
ztInline ztVec3 operator*(r32 scale, const ztVec3& v1);


// ================================================================================================================================================================================================

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
	static ztVec4 lerpBerp(const ztVec4& v1, const ztVec4& v2, r32 percent, r32 power);

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

ztInline ztVec4 zt_vec4(r32 x, r32 y, r32 z, r32 w) { return { x, y, z, w }; }
ztInline ztVec4 zt_vec4(const ztVec2& v2a, const ztVec2& v2b) { return { v2a.x, v2a.y, v2b.x, v2b.y }; }
ztInline ztVec4 zt_vec4(const ztVec3& v3, r32 w) { return { v3.x, v3.y, v3.z, w }; }
ztInline ztVec4 zt_vec4(r32 v[4]) { return { v[0], v[1], v[2], v[3] }; }


ztInline ztVec4 operator+(const ztVec4& v1, const ztVec4& v2);
ztInline ztVec4 operator-(const ztVec4& v1, const ztVec4& v2);
ztInline ztVec4 operator*(const ztVec4& v1, const ztVec4& v2);
ztInline ztVec4 operator*(const ztVec4& v1, r32 scale);
ztInline ztVec4 operator*(r32 scale, const ztVec4& v1);

typedef ztVec4                 ztColor;
#define ztColour               ztColor;       // pick your favorite (favourite?)

ztInline ztColor zt_color(r32 x, r32 y, r32 z, r32 w) { return { x, y, z, w }; }

ztInline ztColor               zt_colorRgb(int r, int g, int b, int a = 255) { return zt_vec4(r / 255.f, g / 255.f, b / 255.f, a / 255.f); }

ztInline ztColor               zt_colorRgbToHsv(ztColor rgba);
ztInline ztColor               zt_colorHsvToRgb(ztColor hsva);

#define ztColor_White          zt_color(1.0f, 1.0f, 1.0f, 1.f)
#define ztColor_Black          zt_color( .0f,  .0f,  .0f, 1.f)
#define ztColor_Gray           zt_color(.50f, .50f, .50f, 1.f)
#define ztColor_LightGray      zt_color(.73f, .73f, .73f, 1.f)
#define ztColor_DarkGray       zt_color(.26f, .26f, .26f, 1.f)
#define ztColor_Red            zt_color(1.0f,  .0f,  .0f, 1.f)
#define ztColor_LightRed       zt_color(1.0f, .75f, .80f, 1.f)
#define ztColor_DarkRed        zt_color(.55f,  .0f,  .0f, 1.f)
#define ztColor_Green          zt_color( .0f, 1.0f,  .0f, 1.f)
#define ztColor_LightGreen     zt_color(.56f, .93f, .56f, 1.f)
#define ztColor_DarkGreen      zt_color( .0f, .20f, .13f, 1.f)
#define ztColor_Blue           zt_color( .0f,  .0f, 1.0f, 1.f)
#define ztColor_LightBlue      zt_color(.68f, .85f, .90f, 1.f)
#define ztColor_DarkBlue       zt_color( .0f,  .0f, .55f, 1.f)
#define ztColor_Purple         zt_color(.50f,  .0f, .50f, 1.f)
#define ztColor_LightPurple    zt_color(.59f, .48f, .71f, 1.f)
#define ztColor_DarkPurple     zt_color(.19f, .10f, .20f, 1.f)
#define ztColor_Cyan           zt_color( .0f, 1.0f, 1.0f, 1.f)
#define ztColor_Yellow         zt_color(1.0f, 1.0f,  .0f, 1.f)
#define ztColor_LightYellow    zt_color(1.0f, 1.0f, .88f, 1.f)
#define ztColor_DarkYellow     zt_color(.61f, .53f,  .0f, 1.f)
#define ztColor_Orange         zt_color(1.0f, .50f,  .0f, 1.f)
#define ztColor_LightOrange    zt_color(1.0f, .60f, .40f, 1.f)
#define ztColor_DarkOrange     zt_color(1.0f, .55f,  .0f, 1.f)


// ================================================================================================================================================================================================
// Matrix multiplication notes:
//
// If you want to have the object rotated around its center, then moved:
//     matrix = translation_matrix;
//     matrix = rotation_matrix * matrix (put the rotation into the existing matrix)
//     (scaling anywhere doesn't seem to make much difference)
//
// If you want to have the object rotated around the axis at the position distance (like the surface of a ball):
//     matrix = rotation_matrix;
//     matrix = translation_matrix * matrix (put the translation into the existing matrix)
//     matrix = scale_matrix * matrix
//
//     scaling before translation affects the translation only
//
// So basically, whichever matrix is on the right side of the multiplication is the "container" and that
// effect applies first, then the effect on the left takes place
// ================================================================================================================================================================================================

struct ztQuat;

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


// ================================================================================================================================================================================================

struct ztMat4
{
	union {
		struct {
			r32 c0r0;
			r32 c0r1;
			r32 c0r2;
			r32 c0r3;
			r32 c1r0;
			r32 c1r1;
			r32 c1r2;
			r32 c1r3;
			r32 c2r0;
			r32 c2r1;
			r32 c2r2;
			r32 c2r3;
			r32 c3r0;
			r32 c3r1;
			r32 c3r2;
			r32 c3r3;
		};

		struct {
			ztVec4 cols[4];
		};

		r32 values[16];
	};


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

	void lookAt(ztVec3 eye_pos, ztVec3 target_pos, ztVec3 up_vec = zt_vec3(0, 1, 0));
	ztMat4 getLookAt(ztVec3 eye_pos, ztVec3 target_pos, ztVec3 up_vec = zt_vec3(0, 1, 0)) const;

	void extract(ztVec3 *position, ztVec3 *rotation, ztVec3 *scale) const; // does not work well with scaled matrices
	void extract(ztVec3 *position, ztQuat *rotation, ztVec3 *scale) const; // does not work well with scaled matrices

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


	void cleanup(int digits);


#if defined(ZT_MAT4_EXTRAS)
	ZT_MAT4_EXTRAS	// use this to add conversions to and from your own classes
#endif
};


// ================================================================================================================================================================================================

ztInline ztMat4 zt_mat4(r32 v[16]) { return{ v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11], v[12], v[13], v[14], v[15] }; }
ztInline ztMat4 zt_mat4(r32 c0r0, r32 c0r1, r32 c0r2, r32 c0r3, r32 c1r0, r32 c1r1, r32 c1r2, r32 c1r3, r32 c2r0, r32 c2r1, r32 c2r2, r32 c2r3, r32 c3r0, r32 c3r1, r32 c3r2, r32 c3r3) { return { c0r0, c0r1, c0r2, c0r3, c1r0, c1r1, c1r2, c1r3, c2r0, c2r1, c2r2, c2r3, c3r0, c3r1, c3r2, c3r3 }; }
ztInline ztMat4 zt_mat4(const ztMat4& m) { return{ m.values[0], m.values[1], m.values[2], m.values[3], m.values[4], m.values[5], m.values[6], m.values[7], m.values[8], m.values[9], m.values[10], m.values[11], m.values[12], m.values[13], m.values[14], m.values[15] }; }

ztInline ztMat4 operator*(const ztMat4& m1, const ztMat4& m2);
ztInline ztVec3 operator*(const ztMat4& m, const ztVec3& v);


// ================================================================================================================================================================================================

struct ztQuat
{
	union {
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

		r32 values[4];
	};

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

	bool equalsClose(const ztQuat& q) const { return zt_real32Close(x, q.x) && zt_real32Close(y, q.y) && zt_real32Close(z, q.z) && zt_real32Close(w, q.w); }

	bool operator==(const ztQuat& q) const { return xyzw == q.xyzw; }
	bool operator!=(const ztQuat& q) const { return xyzw != q.xyzw; }

	static ztQuat makeFromAxisAngle(r32 axis_x, r32 axis_y, r32 axis_z, r32 angle);
	static ztQuat makeFromAxisAngle(const ztVec3& axis, r32 angle);
	static ztQuat makeFromEuler(r32 pitch, r32 yaw, r32 roll);
	static ztQuat makeFromEuler(const ztVec3& euler) { return makeFromEuler(euler.x, euler.y, euler.z); }
	static ztQuat makeFromMat4(const ztMat4& mat);
	static ztQuat makeFromDirection(const ztVec3& dir, const ztVec3& up = zt_vec3(0, 1, 0));
	static ztQuat makeFromPoints(const ztVec3& p1, const ztVec3 p2);

	static ztQuat lerp(const ztQuat& q1, const ztQuat& q2, r32 percent);
	static ztQuat nLerp(const ztQuat& q1, const ztQuat& q2, r32 percent);
	static ztQuat sLerp(const ztQuat& q1, const ztQuat&  q2, r32 percent);

	
	static const ztQuat identity;
};


// ================================================================================================================================================================================================

ztInline ztQuat zt_quat(r32 v[4]) { return { v[0], v[1], v[2], v[3] }; }
ztInline ztQuat zt_quat(r32 x, r32 y, r32 z, r32 w) { return { x, y, z, w }; }
ztInline ztQuat zt_quat(const ztVec3& xyz, r32 w) { return { xyz.x, xyz.y, xyz.z, w }; }
ztInline ztQuat zt_quat(const ztVec4& xyzw) { return { xyzw.x, xyzw.y, xyzw.z, xyzw.w }; }


ztInline ztQuat operator+(const ztQuat& q1, const ztQuat& q2);
ztInline ztQuat operator-(const ztQuat& q1, const ztQuat& q2);
ztInline ztQuat operator*(const ztQuat& q1, const ztQuat& q2);
ztInline ztQuat operator/(const ztQuat& q1, const ztQuat& q2);
ztInline ztQuat operator*(const ztQuat& q1, r32 scale);
ztInline ztQuat operator/(const ztQuat& q1, r32 scale);


// ================================================================================================================================================================================================

bool zt_isPow2              (i32 number);
i32  zt_nextPow2            (i32 number);

i32  zt_convertToi32Ceil    (r32 number);
i32  zt_convertToi32Floor   (r32 number);

r32  zt_lerp                (r32 v1, r32 v2, r32 percent);
r32  zt_unlerp              (r32 v1, r32 v2, r32 value);

r32  zt_lerpHermite         (r32 v1, r32 v2, r32 percent);
r32  zt_lerpSinerp          (r32 v1, r32 v2, r32 percent);
r32  zt_lerpCoserp          (r32 v1, r32 v2, r32 percent);
r32  zt_lerpBerp            (r32 v1, r32 v2, r32 percent, r32 power = 2.5f);
r32  zt_lerpCircle          (r32 ang1, r32 ang2, r32 percent);

r32  zt_linearRemap         (r32 val, r32 v1a, r32 v1b, r32 v2a, r32 v2b);
r32  zt_linearRemapAndClamp (r32 val, r32 v1a, r32 v1b, r32 v2a, r32 v2b);
r32  zt_normalize           (r32 val, r32 min, r32 max);
r32  zt_approach            (r32 var, r32 appr, r32 by);

r32  zt_sin                 (r32 x);
r32  zt_asin                (r32 x);
r32  zt_cos                 (r32 y);
r32  zt_acos                (r32 y);
r32  zt_tan                 (r32 r);
r32  zt_atan                (r32 v);
r32  zt_atan2               (r32 x, r32 y);
r32  zt_sqrt                (r32 v);
r32  zt_pow                 (r32 v, r32 p);
r32  zt_exp                 (r32 v);
r32  zt_fmod                (r32 v, r32 d);

i32  zt_lerp                (i32 v1, i32 v2, r32 percent);
i32  zt_unlerp              (i32 v1, i32 v2, r32 percent);


// ================================================================================================================================================================================================

void zt_assert_raw          (const char *condition_name, const char *file, int file_line);


// ================================================================================================================================================================================================
// GUID
// ================================================================================================================================================================================================

struct ztGuid
{
	union {
		u64 guid[2];
		u32 guid_32[4];
	};
};


// ================================================================================================================================================================================================

ztInline ztGuid  zt_guidMake(u32 part1, u32 part2, u32 part3, u32 part4);
ztInline bool    zt_guidEquals(const ztGuid& guid1, const ztGuid& guid2);

ztInline bool    operator==(const ztGuid& guid1, const ztGuid& guid2);
ztInline bool    operator!=(const ztGuid& guid1, const ztGuid& guid2);

ztInline void    zt_guidToString(const ztGuid& guid, char *buffer, int buffer_size);


// ================================================================================================================================================================================================
// Variant
// ================================================================================================================================================================================================

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
	ztVariant_bool,
};


// ================================================================================================================================================================================================

struct ztVariant
{
	ztVariant_Enum type;

	union
	{
		i8     v_i8;
		i16    v_i16;
		i32    v_i32;
		i64    v_i64;
		u8     v_u8;
		u16    v_u16;
		u32    v_u32;
		u64    v_u64;
		r32    v_r32;
		r64    v_r64;
		void  *v_voidp;
		ztVec2 v_vec2;
		ztVec3 v_vec3;
		ztVec4 v_vec4;
		ztMat4 v_mat4;
		ztQuat v_quat;
		bool  v_bool;
	};
};


// ================================================================================================================================================================================================

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
		bool   *v_bool;
	};
};


// ================================================================================================================================================================================================

ztInline ztVariant        zt_variantMake_i8(i8 val);
ztInline ztVariant        zt_variantMake_i16(i16 val);
ztInline ztVariant        zt_variantMake_i32(i32 val);
ztInline ztVariant        zt_variantMake_i64(i64 val);
ztInline ztVariant        zt_variantMake_u8(u8 val);
ztInline ztVariant        zt_variantMake_u16(u16 val);
ztInline ztVariant        zt_variantMake_u32(u32 val);
ztInline ztVariant        zt_variantMake_u64(u64 val);
ztInline ztVariant        zt_variantMake_r32(r32 val);
ztInline ztVariant        zt_variantMake_r64(r64 val);
ztInline ztVariant        zt_variantMake_voidp(void *val);
ztInline ztVariant        zt_variantMake_vec2(r32 val[2]);
ztInline ztVariant        zt_variantMake_vec3(r32 val[3]);
ztInline ztVariant        zt_variantMake_vec4(r32 val[4]);
ztInline ztVariant        zt_variantMake_mat4(r32 val[16]);
ztInline ztVariant        zt_variantMake_quat(r32 val[4]);
ztInline ztVariant        zt_variantMake_bool(bool val);

ztInline ztVariant        zt_variantMake(ztVariantPointer *variant);

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
ztInline ztVariantPointer zt_variantPointerMake_bool(bool *val);

ztInline i8               zt_variantGetAs_i8(ztVariant *variant);
ztInline i16              zt_variantGetAs_i16(ztVariant *variant);
ztInline i32              zt_variantGetAs_i32(ztVariant *variant);
ztInline i64              zt_variantGetAs_i64(ztVariant *variant);
ztInline u8               zt_variantGetAs_u8(ztVariant *variant);
ztInline u16              zt_variantGetAs_u16(ztVariant *variant);
ztInline u32              zt_variantGetAs_u32(ztVariant *variant);
ztInline u64              zt_variantGetAs_u64(ztVariant *variant);
ztInline r32              zt_variantGetAs_r32(ztVariant *variant);
ztInline r64              zt_variantGetAs_r64(ztVariant *variant);
ztInline void            *zt_variantGetAs_voidp(ztVariant *variant);
ztInline ztVec2           zt_variantGetAs_vec2(ztVariant *variant);
ztInline ztVec3           zt_variantGetAs_vec3(ztVariant *variant);
ztInline ztVec4           zt_variantGetAs_vec4(ztVariant *variant);
ztInline ztMat4           zt_variantGetAs_mat4(ztVariant *variant);
ztInline ztQuat           zt_variantGetAs_quat(ztVariant *variant);
ztInline bool             zt_variantGetAs_bool(ztVariant *variant);

ztInline i8              *zt_variantGetAs_i8(ztVariantPointer *variant);
ztInline i16             *zt_variantGetAs_i16(ztVariantPointer *variant);
ztInline i32             *zt_variantGetAs_i32(ztVariantPointer *variant);
ztInline i64             *zt_variantGetAs_i64(ztVariantPointer *variant);
ztInline u8              *zt_variantGetAs_u8(ztVariantPointer *variant);
ztInline u16             *zt_variantGetAs_u16(ztVariantPointer *variant);
ztInline u32             *zt_variantGetAs_u32(ztVariantPointer *variant);
ztInline u64             *zt_variantGetAs_u64(ztVariantPointer *variant);
ztInline r32             *zt_variantGetAs_r32(ztVariantPointer *variant);
ztInline r64             *zt_variantGetAs_r64(ztVariantPointer *variant);
ztInline void           **zt_variantGetAs_voidp(ztVariantPointer *variant);
ztInline ztVec2          *zt_variantGetAs_vec2(ztVariantPointer *variant);
ztInline ztVec3          *zt_variantGetAs_vec3(ztVariantPointer *variant);
ztInline ztVec4          *zt_variantGetAs_vec4(ztVariantPointer *variant);
ztInline ztMat4          *zt_variantGetAs_mat4(ztVariantPointer *variant);
ztInline ztQuat          *zt_variantGetAs_quat(ztVariantPointer *variant);
ztInline bool            *zt_variantGetAs_bool(ztVariantPointer *variant);

ztInline void             zt_variantAssignValue(ztVariant *variant, ztVariant value);
ztInline void             zt_variantAssignValue(ztVariantPointer *variant, ztVariant value);

ztInline ztVariant        zt_variantLerp(ztVariant *beg, ztVariant *end, r32 pct);


// ================================================================================================================================================================================================
// function pointers
// ================================================================================================================================================================================================

typedef i32                 ztFunctionID;

ztFunctionID                zt_registerFunctionPointer(const char *function_name, void *function);
void                       *zt_functionPointer(ztFunctionID function_id);

#define                     ZT_FUNCTION_POINTER_REGISTER(function_name, function_decl)	\
                            function_decl; \
                            ztFunctionID function_name##_FunctionID = zt_registerFunctionPointer(#function_decl, function_name); \
                            function_decl

//                          This must be accompanied by a call to ZT_FUNCTION_POINTER_REGISTER in a source file
#define                     ZT_FUNCTION_POINTER_REGISTER_EXTERN(function_name, function_decl)	\
                            function_decl; \
                            extern ztFunctionID function_name##_FunctionID; \
                            function_decl

/*
							typedef void (myFunction_Func)(int, obj*);
						
							ZT_FUNCTION_POINTER_REGISTER(myFunction, void myFunction(int x, obj *o))
							{
								if (x > 0) {
									objFunction(x, o, myFunction_FunctionID);
								}
							}
						
							void objFunction(int x, obj *o, ztFunctionID function_id)
							{
								((myFunction_Func*)zt_functionPointer(function_id))(x - 1, o);
							}
*/


// ================================================================================================================================================================================================
// logging
// ================================================================================================================================================================================================

enum ztLogMessageLevel_Enum
{
	ztLogMessageLevel_Fatal,
	ztLogMessageLevel_Critical,
	ztLogMessageLevel_Info,
	ztLogMessageLevel_Debug,
	ztLogMessageLevel_Verbose,

	ztLogMessageLevel_MAX,
};

void    zt_logMessage       (ztLogMessageLevel_Enum level, const char *message, ...);

void    zt_logVerbose       (const char *message, ...);
void    zt_logDebug         (const char *message, ...);
void    zt_logInfo          (const char *message, ...);
void    zt_logCritical      (const char *message, ...);
void    zt_logFatal         (const char *message, ...);

// add your own logging callback ... the message does not contain a newline by default

#define ZT_FUNC_LOG_CALLBACK(name) void name(ztLogMessageLevel_Enum level, const char * message)
typedef ZT_FUNC_LOG_CALLBACK(zt_logCallback_Func);

void    zt_logAddCallback   (zt_logCallback_Func callback, ztLogMessageLevel_Enum min_level);
void    zt_logRemoveCallback(zt_logCallback_Func callback);


// ================================================================================================================================================================================================
// memory
// ================================================================================================================================================================================================

void zt_memSet               (void *mem, i32 mem_len, byte value);
void zt_memCpy               (void *dst, i32 dst_len, const void *src, i32 src_len);
int  zt_memCmp               (const void *one, const void *two, i32 size);


// ================================================================================================================================================================================================

enum ztMemoryArenaFlags_Enum
{
	ztMemoryArenaFlags_ClearMem = (1 << 0), // clear the memory to zero with every allocation
	ztMemoryArenaFlags_Validate = (1 << 1), // validate the contents of the arena after every allocation/free
};


// ================================================================================================================================================================================================

struct ztMemoryArena
{
	byte *memory;
	i32 total_size;
	i32 current_used;
	i32 peak_used;
	i32 alloc_cnt;
	i32 free_cnt;
	i32 freed_allocs;
	i32 flags;

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

	char  file_name_buffer[1024];
	int   file_name_buffer_pos;
	char *file_names[256];
	i32   file_names_hashes[256];
};


// ================================================================================================================================================================================================

ztMemoryArena *zt_memMakeArena(i32 total_size, ztMemoryArena *from = nullptr, i32 flags = ztMemoryArenaFlags_ClearMem);
void           zt_memFreeArena(ztMemoryArena *arena);

//             arena can be null and if so, standard malloc/realloc/free will be used
void          *zt_memAllocFromArena(ztMemoryArena *arena, i32 size);
void          *zt_memAllocFromArena(ztMemoryArena *arena, i32 size, const char *file, int file_line);
void          *zt_memRealloc(ztMemoryArena *arena, void *data, i32 size);
void           zt_memFree(ztMemoryArena *arena, void *data);

bool           zt_memBelongsTo(ztMemoryArena *arena, void *data);

void           zt_memArenaClearAllocations(ztMemoryArena *arena, bool wipe_memory);

#define        zt_memAlloc(arena, size) zt_memAllocFromArena(arena, size, __FILE__, __LINE__)

void           zt_memDumpArena(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level = ztLogMessageLevel_Debug); // logs details including unfreed allocations
void           zt_memDumpArenaDiagnostics(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level = ztLogMessageLevel_Debug);
bool           zt_memArenaValidate(ztMemoryArena *arena);

//             some systems will use the global arena stack to determine if it should use a memory arena
//             note it's possible to push a null arena onto the stack to cause these systems to use malloc/free (or whatever default you set)

bool           zt_memPushGlobalArena(ztMemoryArena *arena); // returns false if the stack is full, so check this
void           zt_memPopGlobalArena();
ztMemoryArena *zt_memGetGlobalArena();

//             by default, malloc and free are used when there are no overrides set
void           zt_memSetDefaultMallocFree(void *(*malloc_func)(size_t), void(*free_func)(void*));

//             be sure that the global arena stack is in the same state between calls to the following
void          *zt_memAllocGlobalFull(i32 size, const char *file, int file_line);
void           zt_memFreeGlobal(void *data);

#define        zt_memAllocGlobal(size) zt_memAllocGlobalFull(size, __FILE__, __LINE__)

#define        zt_mallocStruct(type)				(type *)zt_memAllocGlobalFull(zt_sizeof(type), __FILE__, __LINE__)
#define        zt_mallocStructArray(type, size)	(type *)zt_memAllocGlobalFull(zt_sizeof(type) * (size), __FILE__, __LINE__)

#define        zt_mallocStructArena(type, arena)				(type *)zt_memAllocFromArena(arena, zt_sizeof(type), __FILE__, __LINE__)
#define        zt_mallocStructArrayArena(type, size, arena)	(type *)zt_memAllocFromArena(arena, zt_sizeof(type) * (size), __FILE__, __LINE__)

#define        zt_free(memory)	zt_memFree(zt_memGetGlobalArena(), (void*)memory)
#define        zt_freeArena(memory, arena) zt_memFree(arena, (void*)memory)


// ================================================================================================================================================================================================
// string functions
// ================================================================================================================================================================================================

#define               ztStrPosNotFound     -1

#define               zt_strMakePrintf(varname, varsize, format, ...)  char varname[varsize] = {0}; zt_strPrintf(varname, varsize, format, __VA_ARGS__);

bool                  zt_strValid          (const char *s, const char **invalid_ch = nullptr);

ztInline const char  *zt_strCodepoint      (const char *s, i32* code_point);
ztInline i32          zt_strCodepoint      (const char *s, int pos);

bool                  zt_strEquals         (const char *s1, const char *s2);
bool                  zt_strEquals         (const char *s1, int s1_len, const char *s2);
bool                  zt_strEquals         (const char *s1, int s1_len, const char *s2, int s2_len);
bool                  zt_striEquals        (const char *s1, const char *s2);
bool                  zt_striEquals        (const char *s1, int s1_len, const char *s2);
bool                  zt_striEquals        (const char *s1, int s1_len, const char *s2, int s2_len);
int                   zt_strLen            (const char *s);
int                   zt_strSize           (const char *s); // size in bytes including null terminator
const char           *zt_strMoveForward    (const char *s, int characters);

int                   zt_strCmp            (const char *s1, const char *s2);
int                   zt_striCmp           (const char *s1, const char *s2);

int                   zt_strCmp            (const char *s1, int s1_len, const char *s2, int s2_len);
int                   zt_striCmp           (const char *s1, int s1_len, const char *s2, int s2_len);

int                   zt_strCpy            (char *scopy, int scopy_len, const char *sfrom);
int                   zt_strCpy            (char *scopy, int scopy_len, const char *sfrom, int sfrom_len);

int                   zt_strCat            (char *scat, int scat_len, const char *scopy);
int                   zt_strCat            (char *scat, int scat_len, const char *scopy, int scopy_len);

int                   zt_strCatf           (char *scopy, int scopy_len, const char *format, ...);

bool                  zt_strIsInt          (char *s);
bool                  zt_strIsInt          (char *s, int s_len);
bool                  zt_strIsIntHex       (char *s);
bool                  zt_strIsIntHex       (char *s, int s_len);
bool                  zt_strIsReal32       (char *s);
bool                  zt_strIsReal32       (char *s, int s_len);
bool                  zt_strIsReal64       (char *s);
bool                  zt_strIsReal64       (char *s, int s_len);

i32                   zt_strToInt          (const char *s, i32 def, bool *success = nullptr);
i32                   zt_strToInt          (const char *s, int s_len, i32 def, bool *success = nullptr);
u32                   zt_strToUint         (const char *s, u32 def, bool *success = nullptr);
u32                   zt_strToUint         (const char *s, int s_len, u32 def, bool *success = nullptr);
u32                   zt_strToIntHex       (const char *s, u32 def, bool *success = nullptr);
u32                   zt_strToIntHex       (const char *s, int s_len, u32 def, bool *success = nullptr);
i64                   zt_strToInt64        (const char *s, i64 def, bool *success = nullptr);
i64                   zt_strToInt64        (const char *s, int s_len, i64 def, bool *success = nullptr);
u64                   zt_strToUint64       (const char *s, u64 def, bool *success = nullptr);
u64                   zt_strToUint64       (const char *s, int s_len, u64 def, bool *success = nullptr);

r32                   zt_strToReal32       (const char *s, r32 def, bool* success = nullptr);
r32                   zt_strToReal32       (const char *s, int s_len, r32 def, bool* success = nullptr);
r64                   zt_strToReal64       (const char *s, r64 def, bool* success = nullptr);
r64                   zt_strToReal64       (const char *s, int s_len, r64 def, bool* success = nullptr);

u32                   zt_strHash           (const char *s);

const char           *zt_strFind           (const char *haystack, const char *needle);
const char           *zt_strFind           (const char *haystack, int haystack_len, const char *needle);
int                   zt_strFindPos        (const char *haystack, const char *needle, int start_pos);
int                   zt_strFindPos        (const char *haystack, int haystack_len, const char *needle, int start_pos);

const char           *zt_strFindLast       (const char *haystack, const char *needle);
const char           *zt_strFindLast       (const char *haystack, int haystack_len, const char *needle);
int                   zt_strFindLastPos    (const char *haystack, const char *needle, int start_pos = -1);
int                   zt_strFindLastPos    (const char *haystack, int haystack_len, const char *needle, int start_pos = -1);

const char           *zt_striFind          (const char *haystack, const char *needle);
const char           *zt_striFind          (const char *haystack, int haystack_len, const char *needle);
int                   zt_striFindPos       (const char *haystack, const char *needle, int start_pos);
int                   zt_striFindPos       (const char *haystack, int haystack_len, const char *needle, int start_pos);

const char           *zt_striFindLast      (const char *haystack, const char *needle);
const char           *zt_striFindLast      (const char *haystack, int haystack_len, const char *needle);
int                   zt_striFindLastPos   (const char *haystack, const char *needle, int start_pos = -1);
int                   zt_striFindLastPos   (const char *haystack, int haystack_len, const char *needle, int start_pos = -1);

const char           *zt_strFindFirstOf    (const char *haystack, const char **needles, int needles_count);
const char           *zt_strFindFirstOf    (const char *haystack, int haystack_len, const char **needles, int needles_count);
int                   zt_strFindFirstOfPos (const char *haystack, const char **needles, int needles_count);
int                   zt_strFindFirstOfPos (const char *haystack, int haystack_len, const char **needles, int needles_count);

int                   zt_strCount          (const char *haystack, const char *needle);
int                   zt_strCount          (const char *haystack, int haystack_len, const char *needle);
int                   zt_striCount         (const char *haystack, const char *needle);
int                   zt_striCount         (const char *haystack, int haystack_len, const char *needle);

bool                  zt_strStartsWith     (const char *s, const char *starts_with);
bool                  zt_strStartsWith     (const char *s, int s_len, const char *starts_with, int sw_len);
bool                  zt_strEndsWith       (const char *s, const char *ends_with);
bool                  zt_strEndsWith       (const char *s, int s_len, const char *ends_with, int ew_len);

bool                  zt_striStartsWith    (const char *s, const char *starts_with);
bool                  zt_striStartsWith    (const char *s, int s_len, const char *starts_with, int sw_len);
bool                  zt_striEndsWith      (const char *s, const char *ends_with);
bool                  zt_striEndsWith      (const char *s, int s_len, const char *ends_with, int ew_len);

const char           *zt_strJumpToNextToken(const char *s); // any non-alphanumeric character breaks up tokens
const char           *zt_strJumpToNextToken(const char *s, int s_len);

int                   zt_strGetNextTokenPos(const char *s);
int                   zt_strGetNextTokenPos(const char *s, int s_len);

const char           *zt_strJumpToNextLine (const char *s);
const char           *zt_strJumpToNextLine (const char *s, int s_len);

int                   zt_strGetNextLinePos (const char *s);
int                   zt_strGetNextLinePos (const char *s, int s_len);

int                   zt_strGetBetween     (char *buffer, int buffer_len, const char *s, const char *beg, const char *end, int beg_offset = 0, int end_offset = 0);
int                   zt_strGetBetween     (char *buffer, int buffer_len, const char *s, int s_len, const char *beg, const char *end, int beg_offset = 0, int end_offset = 0);


// ================================================================================================================================================================================================

enum ztStrTokenizeFlags_Enum
{
	ztStrTokenizeFlags_IncludeTokens  = (1<<0),
	ztStrTokenizeFlags_ProcessQuotes  = (1<<1),
	ztStrTokenizeFlags_KeepQuotes     = (1<<2),
	ztStrTokenizeFlags_TrimWhitespace = (1<<3),
};


// ================================================================================================================================================================================================

struct ztToken
{
	i32 beg;
	i32 len;
};


// ================================================================================================================================================================================================

// populates the given array of ztTokens with the parsed information
// if the given array isn't large enough, it populates as many as it cans and returns the required buffer size
// this allows for calling the function once with a null array to get the size, then allocating the required amount of memory before calling a second time

int zt_strTokenize       (const char *s, const char *tokens, ztToken* results, int results_count, int32 flags = 0);
int zt_strTokenize       (const char *s, int s_len, const char *tokens, ztToken* results, int results_count, int32 flags = 0);

int zt_strPrintf         (char *buffer, int buffer_size, const char *format, ...);

int zt_strBytesToString  (char *buffer, int buffer_size, i32 bytes);
int zt_strNumberToString (char *buffer, int buffer_size, i64 number);

int zt_strConvertToUTF16 (const char* s, int s_len, u16* buffer, int buffer_size);


// ================================================================================================================================================================================================

// ztString is used to represent a string where the length of the string is inserted in memory right before the character pointer.
// ztStrings can be passed into all string functions, using zt_stringSize() to get the length of the string

typedef char* ztString;

ztString  zt_stringMake      (int size, ztMemoryArena *arena = nullptr);
ztString  zt_stringResize    (ztString string, int size, ztMemoryArena *arena = nullptr);
ztString  zt_stringMakeFrom  (const char *str, ztMemoryArena *arena = nullptr);
ztString  zt_stringMakeFrom  (const char *str, int s_len, ztMemoryArena *arena = nullptr);
ztString  zt_stringOverwrite (ztString string, const char *str, ztMemoryArena *arena = nullptr);
void      zt_stringFree      (ztString string, ztMemoryArena *arena = nullptr);
int       zt_stringSize      (ztString string);


// ================================================================================================================================================================================================

struct ztStringPool
{
	ztString       *strings = nullptr;
	bool           *used    = nullptr;
	int             size    = 0;
	ztMemoryArena  *arena   = nullptr;
};


// ================================================================================================================================================================================================

// string pools are used to pre-allocate strings for instances where strings will potentially be created/destroyed often.
// the prealloacted strings can be variable sizes using the sizes and proportions paramters. example:
//
//      int sizes[] = {16, 32, 64, 128};
//      int props[] = {10,  5,  2,   1};
//
//      ztStringPool pool = zt_stringPoolMake(100, sizes, props, zt_elementsOf(sizes));
//
// out of the 100 allocated strings, 55 of them will be 16 characters (10/18), 27 will be 32 characters (5/18), 11 will be 64 characters (2/18), 7 will be 128 characters (1/18 + remainder)
// if the pool has no available entries, it will allocate them from the arena given

ztStringPool zt_stringPoolMake        (int total_strings, int *sizes, int *proportions, int sizes_count, ztMemoryArena *arena = nullptr);
void         zt_stringPoolFree        (ztStringPool *pool);
i32          zt_stringPoolBytesNeeded (int total_strings, int *sizes, int *proportions, int sizes_count);

ztString     zt_stringMake            (ztStringPool *pool, int size);
ztString     zt_stringMakeFrom        (ztStringPool *pool, const char* str);
ztString     zt_stringMakeFrom        (ztStringPool *pool, const char* str, int s_len);
ztString     zt_stringResize          (ztStringPool *pool, ztString string, int size);
ztString     zt_stringOverwrite       (ztStringPool *pool, ztString string, const char *str);
void         zt_stringFreeFrom        (ztStringPool *pool, ztString string);


// ================================================================================================================================================================================================
// file operations
// ================================================================================================================================================================================================

enum ztFileOpenMethod_Enum
{
	ztFileOpenMethod_Closed,
	ztFileOpenMethod_ReadOnly,
	ztFileOpenMethod_WriteOver,
	ztFileOpenMethod_WriteAppend,

	ztFileOpenMethod_MAX,
};


// ================================================================================================================================================================================================

struct ztFile
{
	ztFileOpenMethod_Enum open_method;
	i32                   size;

	char                 *full_name; // full file name, path and file with extension

#if defined(ZT_WINDOWS)
	i32                   win_file_handle; // HFILE
	i32                   win_read_pos;
#else
#	error "ztFile needs an implementation for this platform"
#endif

	ztMemoryArena        *arena;
};


// ================================================================================================================================================================================================

#define ztFileMaxPath	1024 * 4	// handy constant for path sizes on the stack

#if defined(ZT_WINDOWS)
#	define ztFilePathSeparator	'\\'
#	define ztFilePathSeparatorStr	"\\"
#else
#	define ztFilePathSeparator '/'
#	define ztFilePathSeparatorStr	"/"
#endif

// ================================================================================================================================================================================================

bool          zt_fileOpen                        (ztFile *file, const char *file_name, ztFileOpenMethod_Enum file_open_method, ztMemoryArena *arena = zt_memGetGlobalArena());
void          zt_fileClose                       (ztFile *file);

i32           zt_fileGetReadPos                  (ztFile *file);
bool          zt_fileSetReadPos                  (ztFile *file, i32 pos);
bool          zt_fileEof                         (ztFile *file);

//            returns length of string, or -1 in case of error
i32           zt_fileGetFullPath                 (ztFile *file, char *buffer, int buffer_size);	// full path only, file name not included
i32           zt_fileGetFileName                 (ztFile *file, char *buffer, int buffer_size);	// file name only, no path details
i32           zt_fileGetFileExt                  (ztFile *file, char *buffer, int buffer_size);		// file extension only

i32           zt_fileGetFullPath                 (const char *file_name, char *buffer, int buffer_size);	// full path only, file name not included
i32           zt_fileGetFileName                 (const char *file_name, char *buffer, int buffer_size);	// file name only, no path details
i32           zt_fileGetFileExt                  (const char *file_name, char *buffer, int buffer_size);	// file extension only

i32           zt_fileGetAppBin                   (char *buffer, int buffer_size);
i32           zt_fileGetAppPath                  (char *buffer, int buffer_size);
i32           zt_fileGetUserPath                 (char *buffer, int buffer_size, char *app_name);
i32           zt_fileGetCurrentPath              (char *buffer, int buffer_size);
void          zt_fileSetCurrentPath              (const char *path);

i32           zt_fileGetFileInOtherFileDirectory (char * buffer, int buffer_size, char *file_only, char *other_file_full_path);	// will expand the file_only to a full path, using the path of the other_file_full_path
i32           zt_fileConcatFileToPath            (char *buffer, int buffer_size, const char *path, const char *file);
i32           zt_fileConcatFileToPath            (char *buffer, int buffer_size, const char *path, int path_len, const char *file, int file_len);

bool          zt_fileExists                      (const char *file_name);
bool          zt_fileDelete                      (const char *file_name);
bool          zt_fileCopy                        (const char *orig_file, const char *new_file);
bool          zt_fileRename                      (const char *orig_file, const char *new_file);
i32           zt_fileSize                        (const char *file_name);
bool          zt_fileModified                    (const char *file_name, i32 *year, i32 *month, i32 *day, i32 *hour, i32 *minute, i32 *second, i32 *ms);
bool          zt_fileModified                    (const char *file_name, i64* date_time);

i32           zt_fileRead                        (ztFile *file, void *buffer, i32 buffer_size);
ztInline bool zt_fileRead                        (ztFile *file, i8 *value)  { return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead                        (ztFile *file, i16 *value) { return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead                        (ztFile *file, i32 *value) { return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead                        (ztFile *file, i64 *value) { return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead                        (ztFile *file, u8 *value)  { return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead                        (ztFile *file, u16 *value) { return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead                        (ztFile *file, u32 *value) { return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead                        (ztFile *file, u64 *value) { return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead                        (ztFile *file, r32 *value) { return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }
ztInline bool zt_fileRead                        (ztFile *file, r64 *value) { return zt_sizeof(*value) == zt_fileRead(file, value, zt_sizeof(*value)); }

i32           zt_fileWrite                       (ztFile *file, const void *buffer, i32 buffer_size);
ztInline bool zt_fileWrite                       (ztFile *file, i8  value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite                       (ztFile *file, i16 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite                       (ztFile *file, i32 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite                       (ztFile *file, i64 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite                       (ztFile *file, u8  value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite                       (ztFile *file, u16 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite                       (ztFile *file, u32 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite                       (ztFile *file, u64 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite                       (ztFile *file, r32 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite                       (ztFile *file, r64 value)        { return zt_sizeof(value) == zt_fileWrite(file, &value, zt_sizeof(value)); }
ztInline bool zt_fileWrite                       (ztFile *file, const char *value){ return zt_strLen(value) == zt_fileWrite(file,  value, zt_strLen(value)); }

bool          zt_fileWritef                      (ztFile *file, const char *format, ...);

void          zt_fileFlush                       (ztFile *file);

void         *zt_readEntireFile                  (const char *file_name, i32 *file_size, bool discard_utf_bom = false, ztMemoryArena *arena = zt_memGetGlobalArena());
i32           zt_readEntireFile                  (const char *file_name, void *buffer, i32 buffer_size, bool discard_utf_bom = false);
i32           zt_writeEntireFile                 (const char *file_name, void *data, i32 data_size, ztMemoryArena *arena = zt_memGetGlobalArena());

bool          zt_directoryExists                 (const char *dir);
bool          zt_directoryMake                   (const char *dir);
bool          zt_directoryDelete                 (const char *dir, bool force);

i32           zt_getDirectorySubs                (const char *directory, char *buffer, i32 buffer_size, bool recursive); // returns \n delimited string of sub directories
i32           zt_getDirectoryFiles               (const char *directory, char *buffer, i32 buffer_size, bool recursive); // returns \n delimited string of files


// ================================================================================================================================================================================================
// directory monitoring
//
// This allows directories to be monitored for new files and directories and modifications to files
// The most efficient method for doing so per platform is used
// ================================================================================================================================================================================================


enum ztDirectoryMonitorFlags_Enum
{
	ztDirectoryMonitorFlags_New    = (1<<0),
	ztDirectoryMonitorFlags_Rename = (1<<1),
	ztDirectoryMonitorFlags_Modify = (1<<2),

	ztDirectoryMonitorFlags_All = ztDirectoryMonitorFlags_New | ztDirectoryMonitorFlags_Rename | ztDirectoryMonitorFlags_Modify,
};


// ================================================================================================================================================================================================

struct ztDirectoryMonitor
{
#if defined(ZT_WINDOWS)
	pointer   io;
	pointer   file;
	i32       flags;
	byte      file_buffer [ztPointerSize + 12 * 256]; // ztPointerSize + 12 == sizeof(FILE_NOTIFY_INFORMATION)
	byte      overlapped  [ztPointerSize * 3 + 8]; // sizeof(OVERLAPPED)
	bool      recursive;
#endif
};


// ================================================================================================================================================================================================

bool zt_directoryMonitor           (ztDirectoryMonitor *dir_mon, const char *directory, bool recursive, i32 flags = ztDirectoryMonitorFlags_All);
void zt_directoryStopMonitor       (ztDirectoryMonitor *dir_mon);
bool zt_directoryMonitorHasChanged (ztDirectoryMonitor *dir_mon);


// ================================================================================================================================================================================================
// threading
// ================================================================================================================================================================================================

typedef i32 ztThreadID;


// ================================================================================================================================================================================================

struct ztThread;


// ================================================================================================================================================================================================

#define ZT_FUNC_THREAD_EXIT(name) bool (name)(void *user_data)
typedef ZT_FUNC_THREAD_EXIT(ztThreadExit_Func);

#define ZT_FUNC_THREAD(name)	int (name)(ztThreadID thread_id, void *user_data, ztThreadExit_Func *exit_test, void *exit_test_user_data)
typedef ZT_FUNC_THREAD(ztThread_Func);


// ================================================================================================================================================================================================

ztThread  *zt_threadMake         (ztThread_Func *thread_func, void *user_data, ztThreadExit_Func *exit_test, void *exit_test_user_data, ztThreadID *out_thread_id);
void       zt_threadFree         (ztThread *thread);
void       zt_threadJoin         (ztThread *thread); // pause execution of the current thread until the given thread is complete
bool       zt_threadIsRunning    (ztThread *thread);
ztThreadID zt_threadGetCurrentID ();        // get the id of the current thread
void       zt_threadYield        ();


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztThreadMutex;


// ================================================================================================================================================================================================

ztThreadMutex *zt_threadMutexMake   ();
void           zt_threadMutexFree   (ztThreadMutex *mutex);

void           zt_threadMutexLock   (ztThreadMutex *mutex);
void           zt_threadMutexUnlock (ztThreadMutex *mutex);


// ================================================================================================================================================================================================

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


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztThreadMonitor;


// ================================================================================================================================================================================================

ztThreadMonitor *zt_threadMonitorMake();
void             zt_threadMonitorFree(ztThreadMonitor *monitor);

void             zt_threadMonitorWaitForSignal(ztThreadMonitor *monitor);
void             zt_threadMonitorTriggerSignal(ztThreadMonitor *monitor);
void             zt_threadMonitorReset(ztThreadMonitor *monitor);


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

typedef long volatile ztAtomicInt;

i32                   zt_atomicIntInc     (ztAtomicInt *atomic_int);
i32                   zt_atomicIncDec     (ztAtomicInt *atomic_int);
i32                   zt_atomicIntSet     (ztAtomicInt *atomic_int, i32 value);
i32                   zt_atomicIntGet     (ztAtomicInt *atomic_int);
i32                   zt_atomicIntAnd     (ztAtomicInt *atomic_int, i32 and_val);
i32                   zt_atomicIntOr      (ztAtomicInt *atomic_int, i32 or_val);
i32                   zt_atomicIntXor     (ztAtomicInt *atomic_int, i32 xor_val);

typedef long volatile ztAtomicBool;

bool                  zt_atomicBoolSet    (ztAtomicBool *atomic_bool, bool value);
bool                  zt_atomicBoolGet    (ztAtomicBool *atomic_bool);
bool                  zt_atomicBoolToggle (ztAtomicBool *atomic_bool);


// ================================================================================================================================================================================================

struct ztDisplay
{
	ztVec4i screen_area;
	ztVec4i work_area; // excludes task bars
	i32     refresh_rate_in_hz;
	i32     index;
	bool    primary;
	char    name[64];
	i64     platform_id;
};

i32 zt_displayGetDetails(ztDisplay *display, i32 display_count);


// ================================================================================================================================================================================================


// ================================================================================================================================================================================================
// serialization
// ================================================================================================================================================================================================

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


// ================================================================================================================================================================================================

#define ztSerialIdentifierMaxSize	128


// ================================================================================================================================================================================================

struct ztSerial
{
	ztSerialMode_Enum mode;
	ztFile            file;
	bool              close_file;

	void             *file_data;
	i32               file_data_size;

	char              identifier[ztSerialIdentifierMaxSize];
	i32               version;

	i32               group_level;
	i8                next_entry;

	i16               _checksum1, _checksum2;
};


// ================================================================================================================================================================================================

bool zt_serialMakeWriter (ztSerial *serial, const char *file_name, const char *identifier, i32 version);
bool zt_serialMakeWriter (ztSerial *serial, ztFile *file, const char *identifier, i32 version);

// if opening a reader fails, check the mode in the ztSerial instance.  if it's ztSerialMode_Corrupt, then the file's checksum did not match
bool zt_serialMakeReader (ztSerial *serial, const char *file_name, const char *identifier);
bool zt_serialMakeReader (ztSerial *serial, void *data, i32 data_size, const char *identifier);
bool zt_serialMakeReader (ztSerial *serial, ztFile *file, const char *identifier);

void zt_serialClose      (ztSerial *serial);

bool zt_serialGroupPush  (ztSerial *serial);
bool zt_serialGroupPop   (ztSerial *serial);

bool zt_serialWrite      (ztSerial *serial, i8 value);
bool zt_serialWrite      (ztSerial *serial, i16 value);
bool zt_serialWrite      (ztSerial *serial, i32 value);
bool zt_serialWrite      (ztSerial *serial, i64 value);
bool zt_serialWrite      (ztSerial *serial, u8 value);
bool zt_serialWrite      (ztSerial *serial, u16 value);
bool zt_serialWrite      (ztSerial *serial, u32 value);
bool zt_serialWrite      (ztSerial *serial, u64 value);
bool zt_serialWrite      (ztSerial *serial, r32 value);
bool zt_serialWrite      (ztSerial *serial, r64 value);
bool zt_serialWrite      (ztSerial *serial, bool value);
bool zt_serialWrite      (ztSerial *serial, const char *value, i32 value_len);
bool zt_serialWrite      (ztSerial *serial, void *value, i32 value_len);
bool zt_serialWrite      (ztSerial *serial, ztVariant *variant);
bool zt_serialWrite      (ztSerial *serial, ztGuid guid);
bool zt_serialWrite      (ztSerial *serial, ztVec2 vec);
bool zt_serialWrite      (ztSerial *serial, ztVec3 vec);
bool zt_serialWrite      (ztSerial *serial, ztVec4 vec);
bool zt_serialWrite      (ztSerial *serial, ztVec2i vec);
bool zt_serialWrite      (ztSerial *serial, ztMat4 mat);
bool zt_serialWrite      (ztSerial *serial, ztQuat quat);


bool zt_serialRead       (ztSerial *serial, i8 *value);
bool zt_serialRead       (ztSerial *serial, i16 *value);
bool zt_serialRead       (ztSerial *serial, i32 *value);
bool zt_serialRead       (ztSerial *serial, i64 *value);
bool zt_serialRead       (ztSerial *serial, u8 *value);
bool zt_serialRead       (ztSerial *serial, u16 *value);
bool zt_serialRead       (ztSerial *serial, u32 *value);
bool zt_serialRead       (ztSerial *serial, u64 *value);
bool zt_serialRead       (ztSerial *serial, r32 *value);
bool zt_serialRead       (ztSerial *serial, r64 *value);
bool zt_serialRead       (ztSerial *serial, bool *value);
bool zt_serialRead       (ztSerial *serial, char *value, i32 value_len, i32 *read_len);
bool zt_serialRead       (ztSerial *serial, void *value, i32 value_len, i32 *read_len);
bool zt_serialRead       (ztSerial *serial, ztVariant *variant);
bool zt_serialRead       (ztSerial *serial, ztGuid *guid);
bool zt_serialRead       (ztSerial *serial, ztVec2 *vec);
bool zt_serialRead       (ztSerial *serial, ztVec3 *vec);
bool zt_serialRead       (ztSerial *serial, ztVec4 *vec);
bool zt_serialRead       (ztSerial *serial, ztVec2i *vec);
bool zt_serialRead       (ztSerial *serial, ztVec3i *vec);
bool zt_serialRead       (ztSerial *serial, ztMat4 *mat);
bool zt_serialRead       (ztSerial *serial, ztQuat *quat);


// ================================================================================================================================================================================================
// base64 encoding/decoding
// ================================================================================================================================================================================================

#define zt_base64GetEncodedSize(bytes_to_encode) ((((bytes_to_encode) / 3) * 4) + 3 + 1) // includes null terminator

int     zt_base64Encode        (byte *data_to_encode, int data_len, char *encoded_data_buffer, int encoded_data_buffer_size);
int     zt_base64Decode        (char *data_to_decode, int data_len, byte *decoded_data_buffer, int decoded_data_buffer_size);


// ================================================================================================================================================================================================
// random numbers
// ================================================================================================================================================================================================

#define ztRandom_MTLen	624

struct ztRandom
{
	i32 seed;
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

void zt_randomInit (ztRandom *random, i32 seed);

i32  zt_randomInt  (ztRandom *random, i32 min, i32 max);
r32  zt_randomVal  (ztRandom *random); // between 0 and 1
r32  zt_randomVal  (ztRandom *random, r32 min, r32 max);


// ================================================================================================================================================================================================
// simplex noise
// ================================================================================================================================================================================================

struct ztSimplexNoise
{
	i16 *perm;
	i16 *perm_grad_index_3d;
};


ztSimplexNoise *zt_simplexNoiseMake (i64 seed);
void            zt_simplexNoiseFree (ztSimplexNoise *noise);

r32             zt_simplexNoise2D   (ztSimplexNoise *noise, r32 x, r32 y);
r32             zt_simplexNoise3D   (ztSimplexNoise *noise, r32 x, r32 y, r32 z);
r32             zt_simplexNoise4D   (ztSimplexNoise *noise, r32 x, r32 y, r32 z, r32 w);


// ================================================================================================================================================================================================
// configuration files
// ================================================================================================================================================================================================

// these are really slow
i32  zt_iniFileGetValue (const char *ini_file, const char *section, const char *key, const char* dflt, char* buffer, i32 buffer_size);
i32  zt_iniFileGetValue (const char *ini_file, const char *section, const char *key, i32 dflt);
r32  zt_iniFileGetValue (const char *ini_file, const char *section, const char *key, r32 dflt);
bool zt_iniFileSetValue (const char *ini_file, const char *section, const char *key, const char *value);



// ================================================================================================================================================================================================
// command line
// ================================================================================================================================================================================================

bool zt_cmdHasArg (const char** argv, int argc, const char* arg_short, const char* arg_long);
bool zt_cmdGetArg (const char** argv, int argc, const char* arg_short, const char* arg_long, char* buffer, int buffer_size);


// ================================================================================================================================================================================================
// external processes
// ================================================================================================================================================================================================

int zt_processRun (const char *command);
int zt_processRun (const char *command, char *output_buffer, int output_buffer_size, int *output_buffer_written = nullptr);


// ================================================================================================================================================================================================
// time
// ================================================================================================================================================================================================

r64  zt_getTime (); // seconds since app started
void zt_sleep   (r32 seconds);

struct ztDate
{
	int year, month, day, hour, minute, second;
};

void   zt_getDate (int *year, int *month, int *day, int *hour, int *minute, int *second);
ztDate zt_getDate ();

bool   operator<  (ztDate& d1, ztDate& d2);
bool   operator>  (ztDate& d1, ztDate& d2);
bool   operator== (ztDate& d1, ztDate& d2);
bool   operator!= (ztDate& d1, ztDate& d2);


// ================================================================================================================================================================================================

class ztBlockProfiler
{
public:
	ztBlockProfiler(char *_block_name, ztLogMessageLevel_Enum _log_level = ztLogMessageLevel_Verbose) : block_name(_block_name), log_level(_log_level) {
		time_beg = zt_getTime();
	}

	~ztBlockProfiler() {
		zt_logMessage(log_level, "%s took %f ms to execute", block_name, (r32)(zt_getTime() - time_beg) * 1000.f);
	}

	char                  *block_name;
	ztLogMessageLevel_Enum log_level;
	r64                    time_beg;
};


// ================================================================================================================================================================================================
// linked lists
// ================================================================================================================================================================================================

#define zt_singleLinkAddToEnd(item_first_ptr, item_add_ptr) \
	{ \
		item_add_ptr->next = nullptr; \
		auto *prev = item_first_ptr; \
		while (prev != nullptr && prev->next != nullptr) { \
			prev = prev->next; \
		} \
		if (prev != nullptr) { \
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


#define zt_singleLinkAddToEndVar(item_first_ptr, var_name, item_add_ptr) \
	{ \
		item_add_ptr->var_name = nullptr; \
		auto *prev = item_first_ptr; \
		while (prev != nullptr && prev->var_name != nullptr) { \
			prev = prev->var_name; \
		} \
		if (prev != nullptr) { \
			prev->var_name = item_add_ptr; \
		} \
		else { \
			item_first_ptr = item_add_ptr; \
		} \
	}

#define zt_singleLinkAddToBeginVar(item_first_ptr, var_name, item_add_ptr) \
	{ \
		item_add_ptr->var_name = item_first_ptr; \
		item_first_ptr = item_add_ptr; \
	}


#define zt_linkFind(item_first_ptr, item_find_ptr, condition) \
	{ \
		item_find_ptr = item_first_ptr; \
		while (item_find_ptr != nullptr) { \
			if (condition) { break; } \
			item_find_ptr = item_find_ptr->next; \
		} \
	}

#define zt_linkGetLast(item_first_ptr, item_find_ptr) \
	{ \
		item_find_ptr = item_first_ptr; \
		while (item_find_ptr != nullptr) { \
			if (item_find_ptr->next == nullptr) break; \
		} \
	}

#define zt_linkGetCount(count, item_first_ptr) \
	int count = 0; \
	zt_flink(link, item_first_ptr) count += 1;


// ================================================================================================================================================================================================
// arrays
// ================================================================================================================================================================================================

#define zt_arrayResizeArenaCopy(arr, type, old_size, new_size, arena) \
	{ \
		type *resized = zt_mallocStructArrayArena(type, new_size, arena); \
		zt_memCpy(resized, new_size * zt_sizeof(type), arr, old_size * zt_sizeof(type)); \
		type *copy = arr; \
		arr = resized; \
		zt_freeArena(copy, arena); \
	}


#define zt_arrayResizeArenaNoCopy(arr, type, new_size, arena) \
	{ \
		zt_freeArena(arr, arena); \
		arr = zt_mallocStructArrayArena(type, new_size, arena); \
	}


// ================================================================================================================================================================================================
// memory reader
// ================================================================================================================================================================================================

struct ztMemoryReader
{
	void *memory;
	i32   memory_size;
	i32   current;
};

ztInline ztMemoryReader zt_memoryReaderMake(void *memory, i32 memory_size);

ztInline i8             zt_memoryRead_i8  (ztMemoryReader *reader);
ztInline i16            zt_memoryRead_i16 (ztMemoryReader *reader);
ztInline i32            zt_memoryRead_i32 (ztMemoryReader *reader);
ztInline i64            zt_memoryRead_i64 (ztMemoryReader *reader);
ztInline u8             zt_memoryRead_u8  (ztMemoryReader *reader);
ztInline u16            zt_memoryRead_u16 (ztMemoryReader *reader);
ztInline u32            zt_memoryRead_u32 (ztMemoryReader *reader);
ztInline u64            zt_memoryRead_u64 (ztMemoryReader *reader);
ztInline r32            zt_memoryRead_r32 (ztMemoryReader *reader);
ztInline r64            zt_memoryRead_r64 (ztMemoryReader *reader);

ztInline i32            zt_memoryRead     (ztMemoryReader *reader, void *buffer, i32 max_read);
ztInline void          *zt_memoryPointTo  (ztMemoryReader *reader, i32 move_forward); // returns a pointer to the current point in memory and moves the cursor forward

ztInline i32            zt_memoryLeft     (ztMemoryReader *reader);


// ================================================================================================================================================================================================
// fast memory allocations
// ================================================================================================================================================================================================

struct ztMemoryChunk
{
	void *memory;
	i32   memory_size;
	i32   current;
};

ztInline ztMemoryChunk zt_memoryChunkMake                           (void *memory, i32 memory_size);

ztInline void         *zt_memoryChunkAlloc                          (ztMemoryChunk *chunk, i32 bytes);
ztInline int           zt_memoryChunkRemaining                      (ztMemoryChunk *chunk);

#define                zt_mallocStructChunk(type, chunk)            (type *)zt_memoryChunkAlloc(chunk, zt_sizeof(type))
#define                zt_mallocStructArrayChunk(type, size, chunk) (type *)zt_memoryChunkAlloc(chunk, zt_sizeof(type) * (size))


// ================================================================================================================================================================================================
// memory deltas
//
// This allows for the comparison of two blocks of memory and storing the deltas.  This can be used
// to save input deltas for replay features or for sending state over the network.
// ================================================================================================================================================================================================

i32  zt_memoryDeltaGet   (void *chunk1, void *chunk2, int chunk_size, void *data, int data_size);
void zt_memoryDeltaApply (void *chunk, int chunk_size, void *diff, int diff_size);


// ================================================================================================================================================================================================
// compression
// ================================================================================================================================================================================================


//i32 zt_compressDeflate(void *data, i32 data_size, void *buffer, i32 buffer_size); // not yet implemented
i32 zt_compressInflate (void *compressed, i32 compressed_size, void *buffer, i32 buffer_size);



// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// inlined functions

ztInline bool zt_isPow2(i32 number)
{
	return ((number != 0) && ((number & (~number + 1)) == number));
}

// ================================================================================================================================================================================================

ztInline i32 zt_nextPow2(i32 number)
{
	i32 nval = 2;
	while (nval < number) nval *= 2;
	return nval;
}

// ================================================================================================================================================================================================

ztInline i32 zt_convertToi32Ceil(r32 number)
{
	return (int32)(number + (number > 0 ? 0.5f : -0.5f));
}

// ================================================================================================================================================================================================

ztInline i32 zt_convertToi32Floor(r32 number)
{
	return (int32)(number);
}

// ================================================================================================================================================================================================

ztInline r32 zt_lerp(r32 v1, r32 v2, r32 percent)
{
	return v1 + ((v2 - v1) * percent);
}

// ================================================================================================================================================================================================

ztInline r32 zt_unlerp(r32 v1, r32 v2, r32 value)
{
	return (v2 - v1) == 0 ? 0 : (value - v1) / (v2 - v1);
}

// ================================================================================================================================================================================================

ztInline r32 zt_lerpHermite(r32 v1, r32 v2, r32 percent)
{
	return zt_lerp(v1, v2, percent * percent * (3.0f - 2.0f * percent));
}

// ================================================================================================================================================================================================

ztInline r32 zt_lerpSinerp(r32 v1, r32 v2, r32 percent)
{
	return zt_lerp(v1, v2, zt_sin(percent * ztMathPi * 0.5f));
}

// ================================================================================================================================================================================================

ztInline r32 zt_lerpCoserp(r32 v1, r32 v2, r32 percent)
{
	return zt_lerp(v1, v2, 1.0f - zt_cos(percent * ztMathPi * 0.5f));
}

// ================================================================================================================================================================================================

ztInline r32 zt_lerpBerp(r32 v1, r32 v2, r32 percent, r32 power)
{
	return zt_lerp(v1, v2, zt_sin(percent * ztMathPi * (0.2f + power * percent * percent * percent)) * zt_pow(1.0f - percent, 2.2f) + percent) * (1.0f + (1.2f * (1.0f - percent)));
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ztInline r32 zt_linearRemap(r32 val, r32 v1a, r32 v1b, r32 v2a, r32 v2b)
{
	return zt_lerp(v2a, v2b, zt_unlerp(v1a, v1b, val));
}

// ================================================================================================================================================================================================

ztInline r32 zt_linearRemapAndClamp(r32 val, r32 v1a, r32 v1b, r32 v2a, r32 v2b)
{
	return zt_clamp(zt_linearRemap(val, v1a, v1b, v2a, v2b), zt_min(v2a, v2b), zt_max(v2a, v2b));
}

// ================================================================================================================================================================================================

ztInline r32 zt_normalize(r32 val, r32 min, r32 max)
{
	return (val - min) / (max - min);
}

// ================================================================================================================================================================================================

ztInline r32 zt_approach(r32 var, r32 appr, r32 by)
{
	if (appr >= var) 
		return zt_min(var + by, appr);

	return zt_max(var - by, appr);
}

// ================================================================================================================================================================================================

ztInline i32 zt_lerp(i32 v1, i32 v2, r32 percent)
{
	return v1 + (i32)((v2 - v1) * percent);
}

// ================================================================================================================================================================================================

ztInline i32 zt_unlerp(i32 v1, i32 v2, r32 value)
{
	return (v2 - v1) == 0 ? 0 : (i32)((value - v1) / (r32)(v2 - v1));
}

// ================================================================================================================================================================================================

ztInline void zt_assert_raw(const char *condition_name, const char *file, int file_line)
{
	zt_debugOnly(__debugbreak());
	zt_logCritical("assert failed: '%s' in file %s (%d)", condition_name, file, file_line);
	//zt_debugOnly(__asm { int 3 });
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInline r32 ztVec2::length() const
{
	return zt_sqrt(x * x + y * y);
}

// ================================================================================================================================================================================================

ztInline r32 ztVec2::dot(const ztVec2& v) const
{
	return x * v.x + y * v.y;
}

// ================================================================================================================================================================================================

ztInline r32 ztVec2::cross(const ztVec2& v) const
{
	return x * v.x + y * v.y;
}

// ================================================================================================================================================================================================

ztInline r32 ztVec2::angle(const ztVec2& v) const
{
	return zt_radiansToDegrees(zt_atan2(v.y - y, v.x - x));
}

// ================================================================================================================================================================================================

ztInline r32 ztVec2::distance(const ztVec2& v) const
{
	return zt_sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec2 ztVec2::fromAngle(r32 angle)
{
	return zt_vec2(zt_cos(angle), zt_sin(angle));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec2 ztVec2::lerp(const ztVec2& v1, const ztVec2& v2, r32 percent)
{
	return zt_vec2(v1.x + ((v2.x - v1.x) * percent), v1.y + ((v2.y - v1.y) * percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec2 ztVec2::lerpHermite(const ztVec2& v1, const ztVec2& v2, r32 percent)
{
	return zt_vec2(zt_lerpHermite(v1.x, v2.x, percent), zt_lerpHermite(v1.y, v2.y, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec2 ztVec2::lerpSinerp(const ztVec2& v1, const ztVec2& v2, r32 percent)
{
	return zt_vec2(zt_lerpSinerp(v1.x, v2.x, percent), zt_lerpSinerp(v1.y, v2.y, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec2 ztVec2::lerpCoserp(const ztVec2& v1, const ztVec2& v2, r32 percent)
{
	return zt_vec2(zt_lerpCoserp(v1.x, v2.x, percent), zt_lerpCoserp(v1.y, v2.y, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec2 ztVec2::lerpBerp(const ztVec2& v1, const ztVec2& v2, r32 percent)
{
	return zt_vec2(zt_lerpBerp(v1.x, v2.x, percent), zt_lerpBerp(v1.y, v2.y, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec2 ztVec2::lerpBerp(const ztVec2& v1, const ztVec2& v2, r32 percent, r32 power)
{
	return zt_vec2(zt_lerpBerp(v1.x, v2.x, percent, power), zt_lerpBerp(v1.y, v2.y, percent, power));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec2 ztVec2::linearRemap(const ztVec2& val, const ztVec2& v1a, const ztVec2& v1b, const ztVec2& v2a, const ztVec2& v2b)
{
	return zt_vec2(zt_lerp(v2a.x, v2b.x, zt_unlerp(v1a.x, v1b.x, val.x)), zt_lerp(v2a.y, v2b.y, zt_unlerp(v1a.y, v1b.y, val.y)));
}

// ================================================================================================================================================================================================

ztInline void ztVec2::normalize()
{
	r32 len = length();
	if (!zt_real32Eq(len, 0)) {
		x = x / len;
		y = y / len;
	}
}

// ================================================================================================================================================================================================

ztInline ztVec2 ztVec2::getNormal() const
{
	r32 len = length();
	return zt_real32Eq(len, 0) ? *this : zt_vec2(x / len, y / len);
}

// ================================================================================================================================================================================================

ztInline void ztVec2::rotate(r32 angle)
{
	r32 vsin = zt_sin(angle);
	r32 vcos = zt_cos(angle);

	r32 tx = x;
	r32 ty = y;

	x = vcos * tx - vsin * ty;
	y = vsin * tx + vcos * ty;
}

// ================================================================================================================================================================================================

ztInline ztVec2 ztVec2::getRotated(r32 angle) const
{
	r32 vsin = zt_sin(angle);
	r32 vcos = zt_cos(angle);

	return zt_vec2(vcos * x - vsin * y, vsin * x + vcos * y);
}

ztInline ztVec2 operator+(const ztVec2& v1, const ztVec2& v2)
{
	return zt_vec2(v1.x + v2.x, v1.y + v2.y);
}

// ================================================================================================================================================================================================

ztInline ztVec2 operator-(const ztVec2& v1, const ztVec2& v2)
{
	return zt_vec2(v1.x - v2.x, v1.y - v2.y);
}

// ================================================================================================================================================================================================

ztInline ztVec2 operator*(const ztVec2& v1, const ztVec2& v2)
{
	return zt_vec2(v1.x * v2.x, v1.y * v2.y);
}

// ================================================================================================================================================================================================

ztInline ztVec2 operator*(const ztVec2& v1, r32 scale)
{
	return zt_vec2(v1.x * scale, v1.y * scale);
}

// ================================================================================================================================================================================================

ztInline ztVec2 operator*(r32 scale, const ztVec2& v1)
{
	return zt_vec2(v1.x * scale, v1.y * scale);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInline r32 ztVec3::length() const
{
	return zt_sqrt(x * x + y * y + z * z);
}

// ================================================================================================================================================================================================

ztInline r32 ztVec3::dot(const ztVec3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

// ================================================================================================================================================================================================

ztInline ztVec3 ztVec3::cross(const ztVec3& v) const
{
	return zt_vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

// ================================================================================================================================================================================================

ztInline r32 ztVec3::angle(const ztVec3& v) const
{
	ztVec3 v1n = getNormal();
	ztVec3 v2n = v.getNormal();
	r32 v1len = v1n.length();
	
	return (zt_real32Eq(v1len, 0) || zt_real32Eq(v2n.length(), 0)) ? v1len : zt_acos(dot(v));
}

// ================================================================================================================================================================================================

ztInline r32 ztVec3::distance(const ztVec3& v) const
{
	r32 tx = x - v.x, ty = y - v.y, tz = z - v.z; 
	return zt_sqrt(tx * tx + ty * ty + tz * tz);
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec3 ztVec3::lerp(const ztVec3& v1, const ztVec3& v2, r32 percent)
{
	return zt_vec3(v1.x + ((v2.x - v1.x) * percent), v1.y + ((v2.y - v1.y) * percent), v1.z + ((v2.z - v1.z) * percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec3 ztVec3::lerpHermite(const ztVec3& v1, const ztVec3& v2, r32 percent)
{
	return zt_vec3(zt_lerpHermite(v1.x, v2.x, percent), zt_lerpHermite(v1.y, v2.y, percent), zt_lerpHermite(v1.z, v2.z, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec3 ztVec3::lerpSinerp(const ztVec3& v1, const ztVec3& v2, r32 percent)
{
	return zt_vec3(zt_lerpSinerp(v1.x, v2.x, percent), zt_lerpSinerp(v1.y, v2.y, percent), zt_lerpSinerp(v1.z, v2.z, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec3 ztVec3::lerpCoserp(const ztVec3& v1, const ztVec3& v2, r32 percent)
{
	return zt_vec3(zt_lerpCoserp(v1.x, v2.x, percent), zt_lerpCoserp(v1.y, v2.y, percent), zt_lerpCoserp(v1.z, v2.z, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec3 ztVec3::lerpBerp(const ztVec3& v1, const ztVec3& v2, r32 percent)
{
	return zt_vec3(zt_lerpBerp(v1.x, v2.x, percent), zt_lerpBerp(v1.y, v2.y, percent), zt_lerpBerp(v1.z, v2.z, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec3 ztVec3::lerpBerp(const ztVec3& v1, const ztVec3& v2, r32 percent, r32 power)
{
	return zt_vec3(zt_lerpBerp(v1.x, v2.x, percent, power), zt_lerpBerp(v1.y, v2.y, percent, power), zt_lerpBerp(v1.z, v2.z, percent, power));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec3 ztVec3::linearRemap(const ztVec3& val, const ztVec3& v1a, const ztVec3& v1b, const ztVec3& v2a, const ztVec3& v2b)
{
	return zt_vec3(zt_lerp(v2a.x, v2b.x, zt_unlerp(v1a.x, v1b.x, val.x)), zt_lerp(v2a.y, v2b.y, zt_unlerp(v1a.y, v1b.y, val.y)), zt_lerp(v2a.z, v2b.z, zt_unlerp(v1a.z, v1b.z, val.z)));
}

// ================================================================================================================================================================================================

ztInline void ztVec3::normalize()
{
	r32 len = length();
	if (!zt_real32Eq(len, 0)) {
		x = x / len;
		y = y / len;
		z = z / len;
	}
}

// ================================================================================================================================================================================================

ztInline ztVec3 ztVec3::getNormal() const
{
	r32 len = length();
	return zt_real32Eq(len, 0) ? *this : zt_vec3(x / len, y / len, z / len);
}

// ================================================================================================================================================================================================

ztInline ztVec3 operator+(const ztVec3& v1, const ztVec3& v2)
{
	return zt_vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

// ================================================================================================================================================================================================

ztInline ztVec3 operator-(const ztVec3& v1, const ztVec3& v2)
{
	return zt_vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

// ================================================================================================================================================================================================

ztInline ztVec3 operator*(const ztVec3& v1, const ztVec3& v2)
{
	return zt_vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

// ================================================================================================================================================================================================

ztInline ztVec3 operator*(const ztVec3& v1, r32 scale)
{
	return zt_vec3(v1.x * scale, v1.y * scale, v1.z * scale);
}

// ================================================================================================================================================================================================

ztInline ztVec3 operator*(r32 scale, const ztVec3& v1)
{
	return zt_vec3(v1.x * scale, v1.y * scale, v1.z * scale);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

/*static*/ ztInline ztVec4 ztVec4::lerp(const ztVec4& v1, const ztVec4& v2, r32 percent)
{
	return zt_vec4(v1.x + ((v2.x - v1.x) * percent), v1.y + ((v2.y - v1.y) * percent), v1.z + ((v2.z - v1.z) * percent), v1.w + ((v2.w - v1.w) * percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec4 ztVec4::lerpHermite(const ztVec4& v1, const ztVec4& v2, r32 percent)
{
	return zt_vec4(zt_lerpHermite(v1.x, v2.x, percent), zt_lerpHermite(v1.y, v2.y, percent), zt_lerpHermite(v1.z, v2.z, percent), zt_lerpHermite(v1.w, v2.w, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec4 ztVec4::lerpSinerp(const ztVec4& v1, const ztVec4& v2, r32 percent)
{
	return zt_vec4(zt_lerpSinerp(v1.x, v2.x, percent), zt_lerpSinerp(v1.y, v2.y, percent), zt_lerpSinerp(v1.z, v2.z, percent), zt_lerpSinerp(v1.w, v2.w, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec4 ztVec4::lerpCoserp(const ztVec4& v1, const ztVec4& v2, r32 percent)
{
	return zt_vec4(zt_lerpCoserp(v1.x, v2.x, percent), zt_lerpCoserp(v1.y, v2.y, percent), zt_lerpCoserp(v1.z, v2.z, percent), zt_lerpCoserp(v1.w, v2.w, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec4 ztVec4::lerpBerp(const ztVec4& v1, const ztVec4& v2, r32 percent)
{
	return zt_vec4(zt_lerpBerp(v1.x, v2.x, percent), zt_lerpBerp(v1.y, v2.y, percent), zt_lerpBerp(v1.z, v2.z, percent), zt_lerpBerp(v1.w, v2.w, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec4 ztVec4::lerpBerp(const ztVec4& v1, const ztVec4& v2, r32 percent, r32 power)
{
	return zt_vec4(zt_lerpBerp(v1.x, v2.x, percent, power), zt_lerpBerp(v1.y, v2.y, percent, power), zt_lerpBerp(v1.z, v2.z, percent, power), zt_lerpBerp(v1.w, v2.w, percent, power));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztVec4 ztVec4::linearRemap(const ztVec4& val, const ztVec4& v1a, const ztVec4& v1b, const ztVec4& v2a, const ztVec4& v2b)
{
	return zt_vec4(zt_lerp(v2a.x, v2b.x, zt_unlerp(v1a.x, v1b.x, val.x)), zt_lerp(v2a.y, v2b.y, zt_unlerp(v1a.y, v1b.y, val.y)), zt_lerp(v2a.z, v2b.z, zt_unlerp(v1a.z, v1b.z, val.z)), zt_lerp(v2a.w, v2b.w, zt_unlerp(v1a.w, v1b.w, val.w)));
}

// ================================================================================================================================================================================================

ztInline ztVec4 operator+(const ztVec4& v1, const ztVec4& v2)
{
	return zt_vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

// ================================================================================================================================================================================================

ztInline ztVec4 operator-(const ztVec4& v1, const ztVec4& v2)
{
	return zt_vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

// ================================================================================================================================================================================================

ztInline ztVec4 operator*(const ztVec4& v1, const ztVec4& v2)
{
	return zt_vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

// ================================================================================================================================================================================================

ztInline ztVec4 operator*(const ztVec4& v1, r32 scale)
{
	return zt_vec4(v1.x * scale, v1.y * scale, v1.z * scale, v1.w * scale);
}

// ================================================================================================================================================================================================

ztInline ztVec4 operator*(r32 scale, const ztVec4& v1)
{
	return zt_vec4(v1.x * scale, v1.y * scale, v1.z * scale, v1.w * scale);
}

// ================================================================================================================================================================================================

ztColor zt_colorRgbToHsv(ztColor rgba)
{
	r32 min = zt_min(rgba.r, zt_min(rgba.g, rgba.b));
	r32 max = zt_max(rgba.r, zt_max(rgba.g, rgba.b));
	r32 delta = max - min;

	r32 r = rgba.r;
	r32 g = rgba.g;
	r32 b = rgba.b;

	rgba.b = max;
	rgba.g = delta / (max + 1e-20f);

	if (r == max) {
		rgba.r = (g - b) / (delta + 1e-20f);
	}
	else if (g == max) {
		rgba.r = 2 + (b - r) / (delta + 1e-20f);
	}
	else {
		rgba.r = 4 + (r - g) / (delta + 1e-20f);
	}

	rgba.r *= 60;
	if (rgba.r < 0) {
		rgba.r += 360;
	}

	return rgba;
}

// ================================================================================================================================================================================================

ztColor zt_colorHsvToRgb(ztColor hsva)
{
	if (hsva.g == 0) {
		hsva.r = hsva.g = hsva.b = hsva.b / 255;
		return hsva;
	}

	r32 temp_h = hsva.r / 60.0f;
	int i = zt_convertToi32Floor(temp_h);
	r32 f = temp_h - i;
	r32 p = hsva.b * (1.0f - hsva.g);
	r32 q = hsva.b * (1.0f - hsva.g * f);
	r32 t = hsva.b * (1.0f - hsva.g * (1.0f - f));
	r32 v = hsva.b;

	switch (i)
	{
		case  0: { hsva.r = v; hsva.g = t; hsva.b = p; } break;
		case  1: { hsva.r = q; hsva.g = v; hsva.b = p; } break;
		case  2: { hsva.r = p; hsva.g = v; hsva.b = t; } break;
		case  3: { hsva.r = p; hsva.g = q; hsva.b = v; } break;
		case  4: { hsva.r = t; hsva.g = p; hsva.b = v; } break;
		default: { hsva.r = v; hsva.g = p; hsva.b = q; } break;
	}

	return hsva;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInline ztMat4 operator*(const ztMat4& m1, const ztMat4& m2)
{
	return m1.getMultiply(m2);
}

// ================================================================================================================================================================================================

ztInline ztVec3 operator*(const ztMat4& m, const ztVec3& v)
{
	return m.getMultiply(v);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInline ztQuat& ztQuat::operator+=(const ztQuat& q)
{
	xyzw += q.xyzw;
	return *this;
}

// ================================================================================================================================================================================================

ztInline ztQuat& ztQuat::operator-=(const ztQuat& q)
{
	xyzw -= q.xyzw;
	return *this;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ztInline ztQuat& ztQuat::operator/=(const ztQuat& q)
{
	ztQuat inv = q.getInverse();
	*this *= inv;
	return *this;
}

// ================================================================================================================================================================================================

ztInline ztQuat& ztQuat::operator*=(r32 s)
{
	xyzw *= s;
	return *this;
}

// ================================================================================================================================================================================================

ztInline ztQuat& ztQuat::operator/=(r32 s)
{
	xyzw *= 1.f / s;
	return *this;
}

// ================================================================================================================================================================================================

ztInline r32 ztQuat::dot(const ztQuat& q) const
{
	return xyz.dot(q.xyz) + (w * q.w);
}

// ================================================================================================================================================================================================

ztInline r32 ztQuat::magnitude() const
{
	return zt_sqrt(dot(*this));
}

// ================================================================================================================================================================================================

ztInline void ztQuat::normalize()
{
	*this /= magnitude();
}

// ================================================================================================================================================================================================

ztInline ztQuat ztQuat::getNormalize() const
{
	ztQuat q = *this;
	q.normalize();
	return q;
}

// ================================================================================================================================================================================================

ztInline void ztQuat::conjugate()
{
	x = -x;
	y = -y;
	z = -z;
}

// ================================================================================================================================================================================================

ztInline ztQuat ztQuat::getConjugate() const
{
	return zt_quat(-x, -y, -z, w);
}

// ================================================================================================================================================================================================

ztInline void ztQuat::inverse()
{
	ztQuat conj = getConjugate();
	r32 d = dot(*this);
	if (d != 0) {
		conj /= d;
	}
	*this = conj;
}

// ================================================================================================================================================================================================

ztInline ztQuat ztQuat::getInverse() const
{
	ztQuat q = *this;
	q.inverse();
	return q;
}

// ================================================================================================================================================================================================

ztInline ztVec3 ztQuat::axis() const
{
	ztQuat n = getNormalize();
	r32 s = zt_sin(zt_acos(w));
	if (s == 0) {
		return ztVec3::zero;
	}
	return n.xyz * (1.f / s);
}

// ================================================================================================================================================================================================

ztInline r32 ztQuat::angle() const
{
	r32 mag = magnitude();
	if (mag == 0) {
		return 0;
	}

	r32 c = w * (1.f / mag);
	return w * zt_acos(c);
}

// ================================================================================================================================================================================================

ztInline void ztQuat::axisAngle(ztVec3 *_axis, r32 *_angle) const
{
	*_axis = axis();
	*_angle = angle();
}

// ================================================================================================================================================================================================

ztInline ztVec3 ztQuat::euler() const
{
	r32 yy = y * y;

	r32 t0 = 2.f * (w * x + y * z);
	r32 t1 = 1.f - 2.f * (x * x + yy);
	r32 roll = zt_atan2(t0, t1);

	// pitch (y-axis rotation)
	r32 t2 = 2.f * (w * y - z * x);
	t2 = t2 > 1.f ? 1.f : t2;
	t2 = t2 < -1.f ? -1.f : t2;
	r32 pitch = zt_asin(t2);

	// yaw (z-axis rotation)
	r32 t3 = 2.f * (w * z + x * y);
	r32 t4 = 1.f - 2.f * (yy + z * z);
	r32 yaw = zt_atan2(t3, t4);

	return zt_vec3(zt_radiansToDegrees(roll), zt_radiansToDegrees(pitch), zt_radiansToDegrees(yaw));
}

// ================================================================================================================================================================================================

ztInline void ztQuat::rotatePosition(ztVec3 *vec) const
{
	ztVec3 t = xyz.cross(*vec) * 2.f;
	ztVec3 p = xyz.cross(t);
	*vec = (t * w) + *vec + p;
}

// ================================================================================================================================================================================================

ztInline ztVec3 ztQuat::rotatePosition(const ztVec3 &vec) const
{
	ztVec3 r = vec;
	rotatePosition(&r);
	return r;
}

// ================================================================================================================================================================================================

ztInline ztVec3 ztQuat::rotatePosition(r32 x, r32 y, r32 z) const
{
	ztVec3 r = zt_vec3(x, y, z);
	rotatePosition(&r);
	return r;
}

// ================================================================================================================================================================================================

ztInline void ztQuat::rotatePosition(r32 *x, r32 *y, r32 *z) const
{
	ztVec3 r = zt_vec3(*x, *y, *z);
	rotatePosition(&r);
	*x = r.x;
	*y = r.y;
	*z = r.z;
}

// ================================================================================================================================================================================================

ztInline ztMat4 ztQuat::convertToMat4() const
{
	ztMat4 r;
	convertToMat4(&r);
	return r;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

/*static*/ ztInline ztQuat ztQuat::lerp(const ztQuat& q1, const ztQuat& q2, r32 percent)
{
	return zt_quat(ztVec4::lerp(q1.xyzw, q2.xyzw, percent));
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztQuat ztQuat::nLerp(const ztQuat& q1, const ztQuat& q2, r32 percent)
{
	return lerp(q1, q2, percent).getNormalize();
}

// ================================================================================================================================================================================================

/*static*/ ztInline ztQuat ztQuat::sLerp(const ztQuat& q1, const ztQuat&  q2, r32 percent)
{
	ztQuat z = q2;
	r32 cos_theta = q1.dot(q2);

	if (cos_theta < 0.f) {
		z = zt_quat(-q2.x, -q2.y, -q2.z, -q2.w);
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

// ================================================================================================================================================================================================

ztInline ztQuat operator+(const ztQuat& q1, const ztQuat& q2)
{
	ztQuat r = q1;
	r += q2;
	return r;
}

// ================================================================================================================================================================================================

ztInline ztQuat operator-(const ztQuat& q1, const ztQuat& q2)
{
	ztQuat r = q1;
	r -= q2;
	return r;
}

// ================================================================================================================================================================================================

ztInline ztQuat operator*(const ztQuat& q1, const ztQuat& q2)
{
	ztQuat r = q1;
	r *= q2;
	return r;
}

// ================================================================================================================================================================================================

ztInline ztQuat operator/(const ztQuat& q1, const ztQuat& q2)
{
	ztQuat r = q1;
	r /= q2;
	return r;
}

// ================================================================================================================================================================================================

ztInline ztQuat operator*(const ztQuat& q1, r32 scale)
{
	ztQuat r = q1;
	r *= scale;
	return r;
}

// ================================================================================================================================================================================================

ztInline ztQuat operator/(const ztQuat& q1, r32 scale)
{
	ztQuat r = q1;
	r /= scale;
	return r;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInline ztGuid zt_guidMake(u32 part1, u32 part2, u32 part3, u32 part4)
{
	ztGuid guid = { (((u64)part1) << 32) | (part2), (((u64)part3) << 32) | (part4) };
	return guid;
}

// ================================================================================================================================================================================================

ztInline bool zt_guidEquals(const ztGuid& guid1, const ztGuid& guid2)
{
	return (guid1.guid[0] == guid2.guid[0] && guid1.guid[1] == guid2.guid[1]);
}

// ================================================================================================================================================================================================

ztInline bool operator==(const ztGuid& guid1, const ztGuid& guid2)
{
	return (guid1.guid[0] == guid2.guid[0] && guid1.guid[1] == guid2.guid[1]);
}

// ================================================================================================================================================================================================

ztInline bool operator!=(const ztGuid& guid1, const ztGuid& guid2)
{
	return (guid1.guid[0] != guid2.guid[0] || guid1.guid[1] != guid2.guid[1]);
}

// ================================================================================================================================================================================================

ztInline void zt_guidToString(const ztGuid& guid, char *buffer, int buffer_size)
{
	// {163986ff-3ff8-429c-8f1f-de2a4735e171}
	if (buffer_size < 39) {
		return;
	}

	zt_strPrintf(buffer, buffer_size, "{%08x%08x%08x%08x}", guid.guid_32[1], guid.guid_32[0], guid.guid_32[3], guid.guid_32[2]);

	int slen = 35;
	for (int i = slen; i > 9; --i) {
		buffer[i] = buffer[i - 1];
	}
	buffer[9] = '-';
	slen += 1;
	for (int i = slen; i > 14; --i) {
		buffer[i] = buffer[i - 1];
	}
	buffer[14] = '-';
	slen += 1;
	for (int i = slen; i > 19; --i) {
		buffer[i] = buffer[i - 1];
	}
	buffer[19] = '-';
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

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
ztInline ztVariant        zt_variantMake_vec2      (const ztVec2& val)          { ztVariant var; var.type = ztVariant_vec2 ; var.v_vec2  = val; return var; }
ztInline ztVariant        zt_variantMake_vec3      (const ztVec3& val)          { ztVariant var; var.type = ztVariant_vec3 ; var.v_vec3  = val; return var; }
ztInline ztVariant        zt_variantMake_vec4      (const ztVec4& val)          { ztVariant var; var.type = ztVariant_vec4 ; var.v_vec4  = val; return var; }
ztInline ztVariant        zt_variantMake_mat4      (const ztMat4& val)          { ztVariant var; var.type = ztVariant_mat4 ; var.v_mat4  = val; return var; }
ztInline ztVariant        zt_variantMake_quat      (const ztQuat& val)          { ztVariant var; var.type = ztVariant_quat ; var.v_quat  = val; return var; }
ztInline ztVariant        zt_variantMake_bool      (const bool    val)          { ztVariant var; var.type = ztVariant_bool ; var.v_bool  = val; return var; }

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
		case ztVariant_bool : return zt_variantMake_bool (*variant->v_bool);
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
ztInline ztVariantPointer zt_variantPointerMake_bool  (bool         *val)          { ztVariantPointer var; var.type = ztVariant_bool ; var.v_bool  = val; return var; }

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
ztInline ztVec2           zt_variantGetAs_vec2     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_vec2 ); return variant->v_vec2; }
ztInline ztVec3           zt_variantGetAs_vec3     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_vec3 ); return variant->v_vec3; }
ztInline ztVec4           zt_variantGetAs_vec4     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_vec4 ); return variant->v_vec4; }
ztInline ztMat4           zt_variantGetAs_mat4     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_mat4 ); return variant->v_mat4; }
ztInline ztQuat           zt_variantGetAs_quat     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_quat ); return variant->v_quat; }
ztInline bool             zt_variantGetAs_bool     (ztVariant *variant)         { zt_assert(variant->type == ztVariant_bool ); return variant->v_bool; }

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
ztInline ztQuat          *zt_variantGetAs_quat     (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_quat); return variant->v_quat; }
ztInline bool            *zt_variantGetAs_bool     (ztVariantPointer *variant)  { zt_assert(variant->type == ztVariant_bool); return variant->v_bool; }

ztInline void zt_variantAssignValue(ztVariant *variant, ztVariant value) { variant->type = value.type; zt_memCpy(variant, zt_sizeof(ztVariant), &value, zt_sizeof(ztVariant)); }

ztInline void zt_variantAssignValue(ztVariantPointer *variant, ztVariant value)
{
	variant->type = value.type;
	switch (variant->type)
	{
		case ztVariant_i8:    *variant->v_i8    = value.v_i8;    break;
		case ztVariant_i16:   *variant->v_i16   = value.v_i16;   break;
		case ztVariant_i32:   *variant->v_i32   = value.v_i32;   break;
		case ztVariant_i64:   *variant->v_i64   = value.v_i64;   break;
		case ztVariant_u8:    *variant->v_u8    = value.v_u8;    break;
		case ztVariant_u16:   *variant->v_u16   = value.v_u16;   break;
		case ztVariant_u32:   *variant->v_u32   = value.v_u32;   break;
		case ztVariant_u64:   *variant->v_u64   = value.v_u64;   break;
		case ztVariant_r32:   *variant->v_r32   = value.v_r32;   break;
		case ztVariant_r64:   *variant->v_r64   = value.v_r64;   break;
		case ztVariant_voidp: *variant->v_voidp = value.v_voidp; break;
		case ztVariant_vec2:  *variant->v_vec2  = value.v_vec2;  break;
		case ztVariant_vec3:  *variant->v_vec3  = value.v_vec3;  break;
		case ztVariant_vec4:  *variant->v_vec4  = value.v_vec4;  break;
		case ztVariant_mat4:  *variant->v_mat4  = value.v_mat4;  break;
		case ztVariant_quat:  *variant->v_quat  = value.v_quat;  break;
		case ztVariant_bool:  *variant->v_bool  = value.v_bool;  break;
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
		case ztVariant_u32  : return zt_variantMake_u32  ((u32)zt_lerp((i32)beg->v_u32, (i32)end->v_u32, pct));
		case ztVariant_u64  : return zt_variantMake_u64  ((u64)zt_lerp((i32)beg->v_u64, (i32)end->v_u64, pct));
		case ztVariant_r32  : return zt_variantMake_r32  ((r32)zt_lerp((r32)beg->v_r32, (r32)end->v_r32, pct));
		case ztVariant_r64  : return zt_variantMake_r64  ((r64)zt_lerp((r32)beg->v_r64, (r32)end->v_r64, pct));
		case ztVariant_voidp: zt_assert(false); // _voidpcan't lerp void pointers
		case ztVariant_vec2 : return zt_variantMake_vec2(ztVec2::lerp(beg->v_vec2, end->v_vec2, pct));
		case ztVariant_vec3 : return zt_variantMake_vec3(ztVec3::lerp(beg->v_vec3, end->v_vec3, pct));
		case ztVariant_vec4 : return zt_variantMake_vec4(ztVec4::lerp(beg->v_vec4, end->v_vec4, pct));
		case ztVariant_mat4 : zt_assert(false); // can't lerp mat4s... use quats instead
		case ztVariant_quat : return zt_variantMake_quat(ztQuat::lerp(beg->v_quat, end->v_quat, pct));
		case ztVariant_bool : return zt_variantMake_bool(pct < .5 ? beg->v_bool : end->v_bool);
	}

	ztVariant v = { ztVariant_Invalid }; return v;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInline ztMemoryReader zt_memoryReaderMake(void *memory, i32 memory_size)
{
	ztMemoryReader reader;
	reader.memory = memory;
	reader.memory_size = memory_size;
	reader.current = 0;
	return reader;
}

// ================================================================================================================================================================================================

ztInline i8 zt_memoryRead_i8(ztMemoryReader *reader)
{
	i8 var = 0;
	zt_memoryRead(reader, &var, zt_sizeof(var));
	return var;
}

// ================================================================================================================================================================================================

ztInline i16 zt_memoryRead_i16(ztMemoryReader *reader)
{
	i16 var = 0;
	zt_memoryRead(reader, &var, zt_sizeof(var));
	return var;
}

// ================================================================================================================================================================================================

ztInline i32 zt_memoryRead_i32(ztMemoryReader *reader)
{
	i32 var = 0;
	zt_memoryRead(reader, &var, zt_sizeof(var));
	return var;
}

// ================================================================================================================================================================================================

ztInline i64 zt_memoryRead_i64(ztMemoryReader *reader)
{
	i64 var = 0;
	zt_memoryRead(reader, &var, zt_sizeof(var));
	return var;
}

// ================================================================================================================================================================================================

ztInline u8  zt_memoryRead_u8(ztMemoryReader *reader)
{
	u8 var = 0;
	zt_memoryRead(reader, &var, zt_sizeof(var));
	return var;
}

// ================================================================================================================================================================================================

ztInline u16 zt_memoryRead_u16(ztMemoryReader *reader)
{
	u16 var = 0;
	zt_memoryRead(reader, &var, zt_sizeof(var));
	return var;
}

// ================================================================================================================================================================================================

ztInline u32 zt_memoryRead_u32(ztMemoryReader *reader)
{
	u32 var = 0;
	zt_memoryRead(reader, &var, zt_sizeof(var));
	return var;
}

// ================================================================================================================================================================================================

ztInline u64 zt_memoryRead_u64(ztMemoryReader *reader)
{
	u64 var = 0;
	zt_memoryRead(reader, &var, zt_sizeof(var));
	return var;
}

// ================================================================================================================================================================================================

ztInline r32 zt_memoryRead_r32(ztMemoryReader *reader)
{
	r32 var = 0;
	zt_memoryRead(reader, &var, zt_sizeof(var));
	return var;
}

// ================================================================================================================================================================================================

ztInline r64 zt_memoryRead_r64(ztMemoryReader *reader)
{
	r64 var = 0;
	zt_memoryRead(reader, &var, zt_sizeof(var));
	return var;
}

// ================================================================================================================================================================================================

ztInline i32 zt_memoryRead(ztMemoryReader *reader, void *buffer, i32 max_read)
{
	i32 max = zt_min(max_read, reader->memory_size - reader->current);
	zt_memCpy(buffer, max, ((byte*)reader->memory) + reader->current, max);
	reader->current += max;
	return max;
}

// ================================================================================================================================================================================================

ztInline void *zt_memoryPointTo(ztMemoryReader *reader, i32 move_forward)
{
	if (move_forward == 0) {
		return nullptr;
	}

	i32 max = zt_min(move_forward, reader->memory_size - reader->current);
	i32 current = reader->current;
	reader->current += max;
	return ((byte*)reader->memory) + current;
}

// ================================================================================================================================================================================================

ztInline i32 zt_memoryLeft(ztMemoryReader *reader)
{
	return reader->memory_size - reader->current;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInline ztMemoryChunk zt_memoryChunkMake(void *memory, i32 memory_size)
{
	ztMemoryChunk chunk;
	chunk.memory      = memory;
	chunk.memory_size = memory_size;
	chunk.current     = 0;
	return chunk;
}

// ================================================================================================================================================================================================

void *zt_memoryChunkAlloc(ztMemoryChunk *chunk, i32 bytes)
{
	zt_assertReturnValOnFail(chunk->memory_size - chunk->current >= bytes, nullptr);

	i32 current = chunk->current;
	chunk->current += bytes;
	return (void*)(((byte*)chunk->memory) + current);
}

// ================================================================================================================================================================================================

ztInline int zt_memoryChunkRemaining(ztMemoryChunk *chunk)
{
	return chunk->memory_size - chunk->current;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInline const char *zt_strCodepoint(const char *s, i32* code_point)
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

// ================================================================================================================================================================================================

ztInline i32 zt_strCodepoint(const char *s, int pos)
{
	i32 code_point = 0;
	s = zt_strMoveForward(s, pos);
	zt_strCodepoint(s, &code_point);
	return code_point;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_FUNC_DLL_SET_GLOBALS(name) void name(void *memory, int version)
typedef ZT_FUNC_DLL_SET_GLOBALS(zt_dllSetGlobals_Func);

#if !defined(ZT_DLL)

void zt_dllSendGlobals(zt_dllSetGlobals_Func *set_globals);

#endif


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // include guard


#if defined(ZT_TOOLS_IMPLEMENTATION) || defined(ZT_TOOLS_INTERNAL_DECLARATIONS)

#ifndef __zt_tools_h_internal_included__
#define __zt_tools_h_internal_included__


// ================================================================================================================================================================================================

void *_zt_call_malloc(size_t);
void  _zt_call_free(void*);


// ================================================================================================================================================================================================

#ifndef ZT_MAX_LOG_CALLBACKS
#define ZT_MAX_LOG_CALLBACKS	8
#endif

#if !defined(ZT_MEM_GLOBAL_ARENA_STACK_SIZE)
#define ZT_MEM_GLOBAL_ARENA_STACK_SIZE	64
#endif


// ================================================================================================================================================================================================

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


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifdef ZT_PROFILE
#define ZT_SYSTEM_INTRINSICS          "Intrinsics"
#define ZT_PROFILE_TOOLS(section)     ZT_PROFILE((section), ZT_SYSTEM_INTRINSICS)
#else
#define ZT_PROFILE_TOOLS(section)
#endif

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
		if (version == ZT_GLOBALS_VERSION) {
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


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifndef ZT_MAX_FUNCTION_POINTER_ENTRIES
#define ZT_MAX_FUNCTION_POINTER_ENTRIES  256
#endif


// ================================================================================================================================================================================================

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


// ================================================================================================================================================================================================

struct ztThreadMutex
{
	CRITICAL_SECTION cs;
};


// ================================================================================================================================================================================================

struct ztThreadMonitor
{
	i64 event_handle;
};

#endif


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

//these aren't in ztGlobals because they must be process-specific:
ztInternal void *_zt_function_pointers[ZT_MAX_FUNCTION_POINTER_ENTRIES];
ztInternal i32   _zt_function_hashes  [ZT_MAX_FUNCTION_POINTER_ENTRIES];
ztInternal int   _zt_function_count = 0;


// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void *zt_functionPointer(ztFunctionID function_id)
{
	ZT_PROFILE_TOOLS("zt_functionPointer");

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


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void *_zt_call_malloc(size_t size)
{
	return malloc(size);
}

void  _zt_call_free(void* mem)
{
	free(mem);
}

// ================================================================================================================================================================================================

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
	ZT_PROFILE_TOOLS("_zt_logMessageRaw");

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

// ================================================================================================================================================================================================

void zt_logMessage(ztLogMessageLevel_Enum level, const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(level, (const char *)buffer);
}

// ================================================================================================================================================================================================

void zt_logVerbose(const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(ztLogMessageLevel_Verbose, (const char *)buffer);
}

// ================================================================================================================================================================================================

void zt_logDebug(const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(ztLogMessageLevel_Debug, (const char *)buffer);
}

// ================================================================================================================================================================================================

void zt_logInfo(const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(ztLogMessageLevel_Info, (const char *)buffer);
}

// ================================================================================================================================================================================================

void zt_logCritical(const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(ztLogMessageLevel_Critical, (const char *)buffer);
}

// ================================================================================================================================================================================================

void zt_logFatal(const char *message, ...)
{
	_zt_var_args;
	_zt_logMessageRaw(ztLogMessageLevel_Fatal, (const char *)buffer);
}

// ================================================================================================================================================================================================

#undef _zt_var_args

// ================================================================================================================================================================================================

void zt_logAddCallback(zt_logCallback_Func callback, ztLogMessageLevel_Enum min_level)
{
	zt_assert(zt->log_callbacks_count < ZT_MAX_LOG_CALLBACKS);

	int idx = zt->log_callbacks_count++;
	zt->log_callbacks[idx] = callback;
	zt->log_callbacks_minlevel[idx] = min_level;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void  zt_memSet(void *mem, int32 mem_len, byte value)
{
	ZT_PROFILE_TOOLS("zt_memSet");

	int max_idx = mem_len;

	if (max_idx % 4 == 0) {
		max_idx /= 4;
		u32 *umem = (u32*)mem;
		while (max_idx--) {
			*umem++ = 0;
		}
	}
	else if (max_idx % 2 == 0) {
		max_idx /= 2;
		u16 *umem = (u16*)mem;
		while (max_idx--) {
			*umem++ = 0;
		}
	}
	else {
		byte *bmem = (byte*)mem;
		while (max_idx--) {
			*bmem++ = 0;
		}
	}
}

// ================================================================================================================================================================================================

void zt_memCpy(void *dst, int32 dst_len, const void *src, int32 src_len)
{
	ZT_PROFILE_TOOLS("zt_memCpy");

	int max_idx = zt_min(dst_len, src_len);

//	for (int i = 0; i < max_idx; ++i) {
//		((byte*)dst)[i] = ((byte*)src)[i];
//	}

	if (max_idx % 4 == 0) {
		max_idx /= 4;
		u32 *udst = (u32*)dst;
		u32 *usrc = (u32*)src;
		while (max_idx--) {
			*udst++ = *usrc++;
		}
	}
	else if (max_idx % 2 == 0) {
		max_idx /= 2;
		u16 *udst = (u16*)dst;
		u16 *usrc = (u16*)src;
		while (max_idx--) {
			*udst++ = *usrc++;
		}
	}
	else {
		byte *bdst = (byte*)dst;
		byte *bsrc = (byte*)src;
		while (max_idx--) {
			*bdst++ = *bsrc++;
		}
	}
}

// ================================================================================================================================================================================================

int zt_memCmp(const void *one, const void *two, i32 size)
{
	ZT_PROFILE_TOOLS("zt_memCmp");

	byte *bone = (byte*)one;
	byte *btwo = (byte*)two;
	zt_fiz(size) {
		if (bone[i] < btwo[i]) return -1;
		if (bone[i] > btwo[i]) return  1;
	}

	return 0;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#if defined(ZT_MEM_ARENA_LOG_DETAILS)
#	define zt_logMemory(...) zt_logVerbose(__VA_ARGS__)
#else
#	define zt_logMemory(...)
#endif

// ================================================================================================================================================================================================

ztMemoryArena *zt_memMakeArena(i32 total_size, ztMemoryArena *from, i32 flags)
{
	ZT_PROFILE_TOOLS("zt_memMakeArena");

	ztMemoryArena *arena = nullptr;
	if (from == nullptr) {
#if defined(ZT_COMPILER_MSVC)
		arena = (ztMemoryArena*)VirtualAlloc((VOID*)zt_gigabytes(1), total_size + zt_sizeof(ztMemoryArena), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (arena == nullptr) {
			zt_strMakePrintf(error, 1024, "VirtualAlloc failed with code: %d\n", GetLastError());
			OutputDebugStringA(error);

			arena = (ztMemoryArena*)VirtualAlloc((VOID*)0, total_size + zt_sizeof(ztMemoryArena), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			if (arena == nullptr) {
				zt_strMakePrintf(error, 1024, "VirtualAlloc failed again with code: %d\n", GetLastError());
				OutputDebugStringA(error);

				arena = (ztMemoryArena*)(total_size + sizeof(ztMemoryArena));
			}
		}
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
		arena->flags = flags;

		arena->file_name_buffer_pos = 0;
		zt_fize(arena->file_names) {
			arena->file_names[0] = nullptr;
			arena->file_names_hashes[0] = 0;
		}

		zt_memSet(arena->memory, total_size, 0);
	}
	return arena;
}

// ================================================================================================================================================================================================

void zt_memFreeArena(ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_memFreeArena");

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

// ================================================================================================================================================================================================

void zt_memArenaClearAllocations(ztMemoryArena *arena, bool wipe_memory)
{
	ZT_PROFILE_TOOLS("zt_memArenaClearAllocations");

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

// ================================================================================================================================================================================================

void zt_memValidateArena(ztMemoryArena *arena)
{
#	if 1 || defined(ZT_DEBUG)
	ZT_PROFILE_TOOLS("zt_memValidateArena");

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
#	endif
}

// ================================================================================================================================================================================================

void zt_memDumpArenaDiagnostics(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level)
{
	ZT_PROFILE_TOOLS("zt_memDumpArenaDiagnostics");

	zt_flink(alloc, arena->latest) {
		zt_debugOnly(zt_logMessage(log_level, "[%s] alloc: %llx; start: %llx; length: %d (%s:%d)", name, (i64)alloc, (i64)alloc->start, alloc->length, alloc->file, alloc->file_line));
		zt_releaseOnly(zt_logMessage(log_level, "[%s] alloc: %llx; start: %llx; length: %d", name, (i64)alloc, (i64)alloc->start, alloc->length));
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_memAllocSetFileName(ztMemoryArena *arena, ztMemoryArena::allocation *alloc, const char *file_name)
{
	ZT_PROFILE_TOOLS("_zt_memAllocSetFileName");

	alloc->file = nullptr;
	if (file_name == nullptr) {
		return;
	}

	const char *file_name_only = zt_strFindLast(file_name, ztFilePathSeparatorStr);
	i32 file_name_hash = zt_strHash(file_name_only);

	int idx = -1;
	zt_fize(arena->file_names_hashes) {
		if (arena->file_names_hashes[i] == 0 || arena->file_names_hashes[i] == file_name_hash) {
			idx = i;
			break;
		}
	}

	if (arena->file_names_hashes[idx] == 0) {
		int len = zt_strLen(file_name_only);

		if (arena->file_name_buffer_pos + len + 1 >= zt_elementsOf(arena->file_name_buffer)) {
			return;
		}

		arena->file_names[idx] = arena->file_name_buffer + arena->file_name_buffer_pos;
		zt_strCpy(arena->file_names[idx], len + 1, file_name_only);

		arena->file_name_buffer_pos += len + 1;
		arena->file_names_hashes[idx] = file_name_hash;
	}

	alloc->file = arena->file_names[idx];
}

// ================================================================================================================================================================================================

void *zt_memAllocFromArena(ztMemoryArena *arena, i32 bytes)
{
	ZT_PROFILE_TOOLS("zt_memAllocFromArena");

	if (arena == nullptr) {
		return zt->mem_malloc(bytes);
	}

	const int byte_align = ztPointerSize;
	if (bytes % byte_align != 0) {
		bytes += byte_align - (bytes % byte_align);	// align the memory to 4/8 byte chunks
	}

	int padding = ztPointerSize;
	bytes += padding; // add for end of memory padding

	if (zt_bitIsSet(arena->flags, ztMemoryArenaFlags_Validate)) {
		zt_memValidateArena(arena);
	}

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

					_zt_memAllocSetFileName(arena, original, "original");
					original->file_line = 0;

					byte *end_of_mem = ((byte*)original->start + original->length) - 1;
					zt_fiz(padding) *end_of_mem-- = 0xcd;

					ztMemoryArena::allocation *inserted = (ztMemoryArena::allocation *)((byte *)original->start + original->length);
					inserted->magic[0] = 'M';
					inserted->magic[1] = 'R';
					inserted->magic[2] = 'E';
					inserted->arena = arena;
					inserted->start = (byte *)inserted + zt_sizeof(ztMemoryArena::allocation);
					inserted->length = bytes;


					_zt_memAllocSetFileName(arena, inserted, "inserted");
					inserted->file_line = 0;

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

		_zt_memAllocSetFileName(arena, allocation, nullptr);
		allocation->file_line = 0;

		arena->latest = allocation;

		arena->current_used += allocation->length + (zt_sizeof(ztMemoryArena::allocation));
		arena->peak_used = zt_max(arena->peak_used, arena->current_used);

		if (zt_bitIsSet(arena->flags, ztMemoryArenaFlags_ClearMem)) {
			zt_memSet(allocation->start, allocation->length - padding, 0);
		}
	}
	else {
		if (zt_bitIsSet(arena->flags, ztMemoryArenaFlags_ClearMem)) {
			zt_memSet(allocation->start, allocation->length - padding, 0);
		}
	}

	zt_logMemory("memory (%llx): allocated %d + %d bytes at location 0x%llx (%d)", (long long unsigned int)arena, allocation->length, zt_sizeof(ztMemoryArena::allocation), (long long unsigned int)next, arena->alloc_cnt);
	// conditional break: allocation->alloc_idx == 0 && allocation->start == 0x0
	//zt_memValidateArena(arena);
	return (void*)allocation->start;
}

// ================================================================================================================================================================================================

void *zt_memAllocFromArena(ztMemoryArena *arena, i32 size, const char *file, int file_line)
{
	ZT_PROFILE_TOOLS("zt_memAllocFromArena");

	void *result = zt_memAllocFromArena(arena, size);
	if (result && arena) {
		ztMemoryArena::allocation* allocation = (ztMemoryArena::allocation*)(((byte*)result) - zt_sizeof(ztMemoryArena::allocation));
		_zt_memAllocSetFileName(arena, allocation, file);
		allocation->file_line = file_line;

		zt_debugOnly(zt_logMemory("memory (%llx): %d bytes of memory at location 0x%llx (file: %s) (line: %d)", (long long unsigned int)arena, allocation->length, (long long unsigned int)allocation, file, file_line));
	}

	return result;
}

// ================================================================================================================================================================================================

void *zt_memRealloc(ztMemoryArena *arena, void *data, i32 size)
{
	ZT_PROFILE_TOOLS("zt_memRealloc");

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

// ================================================================================================================================================================================================

void zt_memFree(ztMemoryArena *arena, void *data)
{
	ZT_PROFILE_TOOLS("zt_memFree");

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

	if (zt_bitIsSet(arena->flags, ztMemoryArenaFlags_Validate)) {
		zt_memValidateArena(arena);
	}
}

// ================================================================================================================================================================================================

bool zt_memBelongsTo(ztMemoryArena *arena, void *data)
{
	zt_returnValOnNull(arena, false);
	zt_returnValOnNull(data, false);

	return (data >= arena->memory && data <= (arena->memory + arena->total_size));
}

// ================================================================================================================================================================================================

void zt_memDumpArena(ztMemoryArena *arena, const char *name, ztLogMessageLevel_Enum log_level)
{
	ZT_PROFILE_TOOLS("zt_memDumpArena");

	if (arena == nullptr) {
		zt_logMessage(log_level, "memory: no arena was allocated");
		return;
	}

	char avail[32] = { 0 };
	zt_strBytesToString(avail, zt_sizeof(avail), arena->total_size);

	char peak[32] = { 0 };
	zt_strBytesToString(peak, zt_sizeof(peak), arena->peak_used);

	zt_logMessage(log_level, "memory (%s): Total: %s; Peak used: %s", name, avail, peak);

	ztMemoryArena::allocation* alloc = arena->latest;
	while (alloc != nullptr) {
		if (alloc->freed == 0) {
			zt_releaseOnly(zt_logMessage(log_level, "memory (%s): unfreed memory at location 0x%llx (%d) (%d bytes)", name, (uint64)alloc->start, alloc->alloc_idx, alloc->length));
			zt_debugOnly(zt_logMessage(log_level, "memory (%s): unfreed memory at location 0x%llx (%d) (%d bytes) file: %s (%d)", name, (uint64)alloc->start, alloc->alloc_idx, alloc->length, alloc->file, alloc->file_line));
		}
		alloc = alloc->next;
	}
	if (arena->alloc_cnt != arena->free_cnt) {
		zt_logMessage(log_level, "memory(%s): alloc/free count mismatch: %d/%d", name, arena->alloc_cnt, arena->free_cnt);
	}
}

// ================================================================================================================================================================================================

bool zt_memArenaValidate(ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_memArenaValidate");

	ztMemoryArena::allocation *alloc = arena->latest;
	bool failed = false;
	while (alloc != nullptr) {
		if (alloc->freed == 0) {
			byte *end_of_mem = ((byte*)alloc->start + alloc->length) - 4;
			zt_fiz(4) {
				if (*end_of_mem++ != 0xcd) {
					zt_assert(false);
					failed = true;
				}
			}
		}
		alloc = alloc->next;
	}

	return !failed;
}

// ================================================================================================================================================================================================

bool zt_memPushGlobalArena(ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_memPushGlobalArena");

	zt_assert(zt->mem_global_arena_stack_count < ZT_MEM_GLOBAL_ARENA_STACK_SIZE);
	if (zt->mem_global_arena_stack_count >= ZT_MEM_GLOBAL_ARENA_STACK_SIZE) {
		return false;
	}

	zt->mem_global_arena_stack[zt->mem_global_arena_stack_count++] = arena;
	return true;
}

// ================================================================================================================================================================================================

void zt_memPopGlobalArena()
{
	ZT_PROFILE_TOOLS("zt_memPopGlobalArena");

	zt_assert(zt->mem_global_arena_stack_count > 0);
	zt->mem_global_arena_stack_count -= 1;
}

// ================================================================================================================================================================================================

ztMemoryArena* zt_memGetGlobalArena()
{
	if (zt->mem_global_arena_stack_count == 0) {
		return nullptr;
	}
	return zt->mem_global_arena_stack[zt->mem_global_arena_stack_count - 1];
}

// ================================================================================================================================================================================================

void zt_memSetDefaultMallocFree(void *(*malloc_func)(size_t), void(*free_func)(void*))
{
	zt->mem_malloc = malloc_func;
	zt->mem_free   = free_func;
}

// ================================================================================================================================================================================================

void *zt_memAllocGlobalFull(i32 size, const char *file, int file_line)
{
	ZT_PROFILE_TOOLS("zt_memAllocGlobalFull");

	ztMemoryArena* arena = zt_memGetGlobalArena();
	if (arena) {
		return zt_memAllocFromArena(arena, size, file, file_line);
	}
	else {
		void *mem = zt->mem_malloc(size);
		zt_memSet(mem, size, 0);
		return mem;
	}
}

// ================================================================================================================================================================================================

void zt_memFreeGlobal(void *data)
{
	ZT_PROFILE_TOOLS("zt_memFreeGlobal");

	ztMemoryArena* arena = zt_memGetGlobalArena();
	if (arena) {
		zt_memFree(arena, data);
	}
	else {
		zt->mem_free(data);
	}
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

/*static*/ const ztVec2 ztVec2::zero = zt_vec2(0, 0);
/*static*/ const ztVec2 ztVec2::one  = zt_vec2(1, 1);
/*static*/ const ztVec2 ztVec2::min  = zt_vec2(ztReal32Min, ztReal32Min);
/*static*/ const ztVec2 ztVec2::max  = zt_vec2(ztReal32Max, ztReal32Max);

/*static*/ const ztVec3 ztVec3::zero = zt_vec3(0, 0, 0);
/*static*/ const ztVec3 ztVec3::one  = zt_vec3(1, 1, 1);
/*static*/ const ztVec3 ztVec3::min  = zt_vec3(ztReal32Min, ztReal32Min, ztReal32Min);
/*static*/ const ztVec3 ztVec3::max  = zt_vec3(ztReal32Max, ztReal32Max, ztReal32Max);

/*static*/ const ztVec4 ztVec4::zero = zt_vec4(0, 0, 0, 0);
/*static*/ const ztVec4 ztVec4::one  = zt_vec4(1, 1, 1, 1);
/*static*/ const ztVec4 ztVec4::min  = zt_vec4(ztReal32Min, ztReal32Min, ztReal32Min, ztReal32Min);
/*static*/ const ztVec4 ztVec4::max  = zt_vec4(ztReal32Max, ztReal32Max, ztReal32Max, ztReal32Max);

/*static*/ const ztMat4 ztMat4::zero = zt_mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
/*static*/ const ztMat4 ztMat4::identity = zt_mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

/*static*/ const ztQuat ztQuat::identity = zt_quat(0, 0, 0, 1);

// ================================================================================================================================================================================================

r32 zt_sin(r32 x)
{
	ZT_PROFILE_TOOLS("zt_sin");

	return sinf(x);
}

// ================================================================================================================================================================================================

r32 zt_asin(r32 x)
{
	ZT_PROFILE_TOOLS("zt_asin");

	return asinf(x);
}

// ================================================================================================================================================================================================

r32 zt_cos(r32 y)
{
	ZT_PROFILE_TOOLS("zt_cos");

	return cosf(y);
}

// ================================================================================================================================================================================================

r32 zt_acos(r32 y)
{
	ZT_PROFILE_TOOLS("zt_acos");

	return acosf(y);
}

// ================================================================================================================================================================================================

r32 zt_tan(r32 r)
{
	ZT_PROFILE_TOOLS("zt_tan");

	return tan(r);
}

// ================================================================================================================================================================================================

r32 zt_atan(r32 v)
{
	ZT_PROFILE_TOOLS("zt_atan");

	return atanf(v);
}

// ================================================================================================================================================================================================

r32 zt_atan2(r32 x, r32 y)
{
	ZT_PROFILE_TOOLS("zt_atan2");

	return atan2f(x, y);
}

// ================================================================================================================================================================================================

r32 zt_sqrt(r32 v)
{
	ZT_PROFILE_TOOLS("zt_sqrt");

	return sqrtf(v);
}

// ================================================================================================================================================================================================

r32 zt_pow(r32 v, r32 p)
{
	ZT_PROFILE_TOOLS("zt_pow");

	return powf(v, p);
}

// ================================================================================================================================================================================================

r32 zt_exp(r32 v)
{
	ZT_PROFILE_TOOLS("zt_exp");

	return expf(v);
}

// ================================================================================================================================================================================================

r32 zt_fmod(r32 v, r32 d)
{
	ZT_PROFILE_TOOLS("zt_fmod");

	return fmodf(v, d);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void ztMat4::rotateEuler(const ztVec3& euler)
{
	rotateEuler(euler.x, euler.y, euler.z);
}

// ================================================================================================================================================================================================

void ztMat4::rotateEuler(r32 x, r32 y, r32 z)
{
	ZT_PROFILE_TOOLS("ztMat4::rotateEuler");

#	if 0
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
#	endif
#	if 1
	// pitch = y, yaw = x, roll = z

	x = zt_degreesToRadians(x);
	y = zt_degreesToRadians(y);
	z = zt_degreesToRadians(z);

	ztMat4 rot_x = zt_mat4(
		1, 0, 0, 0,
		0, cosf(x), -sinf(x), 0,
		0, sinf(x), cosf(x), 0,
		0, 0, 0, 1
		);

	ztMat4 rot_y = zt_mat4(
		cosf(y), 0, sinf(y), 0,
		0, 1, 0, 0,
		-sinf(y), 0, cosf(y), 0,
		0, 0, 0, 1
		);

	ztMat4 rot_z = zt_mat4(
		cosf(z), -sinf(z), 0, 0,
		sinf(z), cosf(z), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		);

	ztMat4 mult_xyz = (rot_z * rot_y) * rot_x;
	multiply(mult_xyz);
#	endif
}

// ================================================================================================================================================================================================

ztMat4 ztMat4::getRotateEuler(const ztVec3& euler) const
{
	ZT_PROFILE_TOOLS("ztMat4::getRotateEuler");

	ztMat4 copy(*this);
	copy.rotateEuler(euler);
	return copy;
}

// ================================================================================================================================================================================================

ztMat4 ztMat4::getRotateEuler(r32 x, r32 y, r32 z) const
{
	ZT_PROFILE_TOOLS("ztMat4::getRotateEuler");

	ztMat4 copy(*this);
	copy.rotateEuler(x, y, z);
	return copy;
}

// ================================================================================================================================================================================================

void ztMat4::multiply(const ztMat4& m2)
{
	ZT_PROFILE_TOOLS("ztMat4::multiply");

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

// ================================================================================================================================================================================================

ztMat4 ztMat4::getMultiply(const ztMat4& mat) const
{
	ZT_PROFILE_TOOLS("ztMat4::getMultiply");

	ztMat4 copy(*this);
	copy.multiply(mat);
	return copy;
}

// ================================================================================================================================================================================================

ztVec3 ztMat4::getMultiply(const ztVec3& v) const
{
	ZT_PROFILE_TOOLS("ztMat4::getMultiply");

	return zt_vec3((v.x * values[ztMat4_Col0Row0]) + (v.y * values[ztMat4_Col1Row0]) + (v.z * values[ztMat4_Col2Row0]) + values[ztMat4_Col3Row0],
	              (v.x * values[ztMat4_Col0Row1]) + (v.y * values[ztMat4_Col1Row1]) + (v.z * values[ztMat4_Col2Row1]) + values[ztMat4_Col3Row1],
	              (v.x * values[ztMat4_Col0Row2]) + (v.y * values[ztMat4_Col1Row2]) + (v.z * values[ztMat4_Col2Row2]) + values[ztMat4_Col3Row2]);
}

// ================================================================================================================================================================================================

void ztMat4::transpose()
{
	ZT_PROFILE_TOOLS("ztMat4::transpose");

	ztMat4 m(*this);
	values[0] = m.values[ 0]; values[4] = m.values[ 1]; values[ 8] = m.values[ 2]; values[12] = m.values[ 3];
	values[1] = m.values[ 4]; values[5] = m.values[ 5]; values[ 9] = m.values[ 6]; values[13] = m.values[ 7];
	values[2] = m.values[ 8]; values[6] = m.values[ 9]; values[10] = m.values[10]; values[14] = m.values[11];
	values[3] = m.values[12]; values[7] = m.values[13]; values[11] = m.values[14]; values[15] = m.values[15];
}

// ================================================================================================================================================================================================

ztMat4 ztMat4::getTranspose() const
{
	ZT_PROFILE_TOOLS("ztMat4::getTranspose");

	ztMat4 copy(*this);
	copy.transpose();
	return copy;
}

// ================================================================================================================================================================================================

void ztMat4::inverse()
{
	ZT_PROFILE_TOOLS("ztMat4::inverse");

	ztMat4 m(*this);

	values[ztMat4_Col0Row0] = ( m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row3]) - (m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row2]) - (m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row3]) + (m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row2]) + (m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row3]) - (m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row2]);
	values[ztMat4_Col1Row0] = (-m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row3]) + (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row2]) + (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row3]) - (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row2]) - (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row3]) + (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row2]);
	values[ztMat4_Col2Row0] = ( m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col3Row3]) - (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row1]) - (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col3Row3]) + (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row1]) + (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row3]) - (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row1]);
	values[ztMat4_Col3Row0] = (-m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col3Row2]) + (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row1]) + (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col3Row2]) - (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row1]) - (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row2]) + (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row1]);

	values[ztMat4_Col0Row1] = (-m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row3]) + (m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row2]) + (m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row3]) - (m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row2]) - (m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row3]) + (m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row2]);
	values[ztMat4_Col1Row1] = ( m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row3]) - (m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row2]) - (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row3]) + (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row2]) + (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row3]) - (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row2]);
	values[ztMat4_Col2Row1] = (-m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col3Row3]) + (m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row3] * m.values[ztMat4_Col3Row1]) + (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col3Row3]) - (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row1]) - (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row3]) + (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row1]);
	values[ztMat4_Col3Row1] = ( m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col3Row2]) - (m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col2Row2] * m.values[ztMat4_Col3Row1]) - (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col3Row2]) + (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row1]) + (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row2]) - (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row1]);

	values[ztMat4_Col0Row2] = ( m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row3]) - (m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row2]) - (m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row3]) + (m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row2]) + (m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row3]) - (m.values[ztMat4_Col3Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row2]);
	values[ztMat4_Col1Row2] = (-m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row3]) + (m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row2]) + (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row3]) - (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row2]) - (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row3]) + (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row2]);
	values[ztMat4_Col2Row2] = ( m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col3Row3]) - (m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col3Row1]) - (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col3Row3]) + (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col3Row1]) + (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row3]) - (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row1]);
	values[ztMat4_Col3Row2] = (-m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col3Row2]) + (m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col3Row1]) + (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col3Row2]) - (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col3Row1]) - (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row2]) + (m.values[ztMat4_Col3Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row1]);

	values[ztMat4_Col0Row3] = (-m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row3]) + (m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row2]) + (m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row3]) - (m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row2]) - (m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row3]) + (m.values[ztMat4_Col2Row1] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row2]);
	values[ztMat4_Col1Row3] = ( m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row3]) - (m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row2]) - (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row3]) + (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row2]) + (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row3]) - (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row2]);
	values[ztMat4_Col2Row3] = (-m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row3]) + (m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row3] * m.values[ztMat4_Col2Row1]) + (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row3]) - (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col2Row1]) - (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row3]) + (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row3] * m.values[ztMat4_Col1Row1]);
	values[ztMat4_Col3Row3] = ( m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row1] * m.values[ztMat4_Col2Row2]) - (m.values[ztMat4_Col0Row0] * m.values[ztMat4_Col1Row2] * m.values[ztMat4_Col2Row1]) - (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col2Row2]) + (m.values[ztMat4_Col1Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col2Row1]) + (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row1] * m.values[ztMat4_Col1Row2]) - (m.values[ztMat4_Col2Row0] * m.values[ztMat4_Col0Row2] * m.values[ztMat4_Col1Row1]);

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

// ================================================================================================================================================================================================

ztMat4 ztMat4::getInverse() const
{
	ZT_PROFILE_TOOLS("ztMat4::getInverse");

	ztMat4 copy(*this);
	copy.inverse();
	return copy;
}

// ================================================================================================================================================================================================

void ztMat4::lookAt(ztVec3 eye_pos, ztVec3 target_pos, ztVec3 up_vec)
{
	ZT_PROFILE_TOOLS("ztMat4::lookAt");

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

	ztMat4 p = identity.getTranslate(eye_pos.x, eye_pos.y, eye_pos.z);
	//*this = l * p;
	*this = p * l;
}

// ================================================================================================================================================================================================

ztMat4 ztMat4::getLookAt(ztVec3 eye_pos, ztVec3 target_pos, ztVec3 up_vec) const
{
	ZT_PROFILE_TOOLS("ztMat4::getLookAt");

	ztMat4 copy(*this);
	copy.lookAt(eye_pos, target_pos, up_vec);
	return copy;
}

// ================================================================================================================================================================================================

void ztMat4::extract(ztVec3 *position, ztVec3 *rotation, ztVec3 *scale) const // does not work well with scaled matrices
{
	ZT_PROFILE_TOOLS("ztMat4::extract");

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
		scale->x = zt_vec3(m.values[ztMat4_Row0Col0], m.values[ztMat4_Row1Col0], m.values[ztMat4_Row2Col0]).length();
		scale->y = zt_vec3(m.values[ztMat4_Row0Col1], m.values[ztMat4_Row1Col1], m.values[ztMat4_Row2Col1]).length();
		scale->z = zt_vec3(m.values[ztMat4_Row0Col2], m.values[ztMat4_Row1Col2], m.values[ztMat4_Row2Col2]).length();
	}
}

// ================================================================================================================================================================================================

void ztMat4::extract(ztVec3 *position, ztQuat *rotation, ztVec3 *scale) const
{
	ZT_PROFILE_TOOLS("ztMat4::extract");

	if (position) {
		position->x = values[ztMat4_Col3Row0];
		position->y = values[ztMat4_Col3Row1];
		position->z = values[ztMat4_Col3Row2];
	}

	if (rotation) {
		*rotation = ztQuat::makeFromMat4(*this);
	}

	if (scale) {
		scale->x = zt_vec3(values[ztMat4_Row0Col0], values[ztMat4_Row1Col0], values[ztMat4_Row2Col0]).length();
		scale->y = zt_vec3(values[ztMat4_Row0Col1], values[ztMat4_Row1Col1], values[ztMat4_Row2Col1]).length();
		scale->z = zt_vec3(values[ztMat4_Row0Col2], values[ztMat4_Row1Col2], values[ztMat4_Row2Col2]).length();
	}
}

// ================================================================================================================================================================================================

void ztMat4::removeTranslation()
{
	ZT_PROFILE_TOOLS("ztMat4::removeTranslation");

	values[ztMat4_Col3Row0] = values[ztMat4_Col3Row1] = values[ztMat4_Col3Row2] = 0;
	//values[ztMat4_Col0Row3] = values[ztMat4_Col1Row3] = values[ztMat4_Col2Row3] = 0;
}

// ================================================================================================================================================================================================

ztMat4 ztMat4::getRemoveTranslation()
{
	ZT_PROFILE_TOOLS("ztMat4::::getRemoveTranslation");

	ztMat4 copy(*this);
	copy.removeTranslation();
	return copy;
}

// ================================================================================================================================================================================================

ztMat4& ztMat4::operator*=(const ztMat4& mat4)
{
	ZT_PROFILE_TOOLS("ztMat4::operator*=");

	multiply(mat4);
	return *this;
}

// ================================================================================================================================================================================================

/*static*/ ztMat4 ztMat4::makeOrthoProjection(r32 left, r32 right, r32 top, r32 bottom, r32 near_z, r32 far_z)
{
	ZT_PROFILE_TOOLS("ztMat4::makeOrthoProjection");

	r32 m[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	m[ztMat4_Row0Col0] =  2.f / (right - left);
	m[ztMat4_Row1Col1] =  2.f / (top - bottom);
	m[ztMat4_Row2Col2] = -2.f / (far_z - near_z);
	m[ztMat4_Row2Col3] = -near_z / (far_z - near_z);
	m[ztMat4_Row3Col3] = 1;

	return zt_mat4(m);
}

// ================================================================================================================================================================================================

/*static*/ ztMat4 ztMat4::makePerspectiveProjection(r32 angle_of_view, r32 width, r32 height, r32 near_z, r32 far_z)
{
	ZT_PROFILE_TOOLS("ztMat4::makePerspectiveProjection");

	const r32 k = 1.0f / tanf(angle_of_view / 2.0f);
	const r32 c = (near_z + far_z) / (far_z - near_z);

	r32 m[16];

	m[0] = k * height / width; m[4] = 0; m[ 8] =  0;  m[12] = 0;
	m[1] = 0;                  m[5] = k; m[ 9] =  0;  m[13] = 0;
	m[2] = 0;                  m[6] = 0; m[10] = -c;  m[14] = -((2 * near_z * far_z) / (far_z - near_z));
	m[3] = 0;                  m[7] = 0; m[11] = -1;  m[15] = 0;

	return zt_mat4(m);
}

// ================================================================================================================================================================================================

void ztMat4::cleanup(int digits)
{
	ZT_PROFILE_TOOLS("ztMat4::cleanup");

	r32 pow = zt_pow(10.f, (r32)digits);
	zt_fize(values) {
		values[i] = (zt_convertToi32Ceil(values[i] * pow)) / pow;
	}
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

/*static*/ ztInline ztQuat ztQuat::makeFromAxisAngle(r32 axis_x, r32 axis_y, r32 axis_z, r32 angle)
{
	ZT_PROFILE_TOOLS("ztQuat::makeFromAxisAngle");

	r32 angle_rad = zt_degreesToRadians(angle);
	ztQuat quat = zt_quat(axis_x, axis_y, axis_z, 0);
	quat.xyz.normalize();
	quat.xyz *= zt_sin(.5f * angle_rad);
	quat.w = zt_cos(.5f * angle_rad);
	return quat;
}

// ================================================================================================================================================================================================

ztQuat ztQuat::makeFromAxisAngle(const ztVec3& axis, r32 angle)
{
	return makeFromAxisAngle(axis.x, axis.y, axis.z, angle);
}

// ================================================================================================================================================================================================
/*static*/ztInline  ztQuat ztQuat::makeFromEuler(r32 x, r32 y, r32 z)
{
	ZT_PROFILE_TOOLS("ztQuat::makeFromEuler");

	x = zt_degreesToRadians(x) * .5f;
	y = zt_degreesToRadians(y) * .5f;
	z = zt_degreesToRadians(z) * .5f;

	r32 t0 = zt_cos(z);
	r32 t1 = zt_sin(z);
	r32 t2 = zt_cos(x);
	r32 t3 = zt_sin(x);
	r32 t4 = zt_cos(y);
	r32 t5 = zt_sin(y);

	r32 qw = t0 * t2 * t4 + t1 * t3 * t5;
	r32 qx = t0 * t3 * t4 - t1 * t2 * t5;
	r32 qy = t0 * t2 * t5 + t1 * t3 * t4;
	r32 qz = t1 * t2 * t4 - t0 * t3 * t5;

	return zt_quat(qx, qy, qz, qw);
}

// ================================================================================================================================================================================================

/*static*/ ztQuat ztQuat::makeFromMat4(const ztMat4& mat)
{
	ZT_PROFILE_TOOLS("ztQuat::makeFromMat4");

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
		case 0: return zt_quat((m[ztMat4_Col1Row2] - m[ztMat4_Col2Row1]) * mult, (m[ztMat4_Col2Row0] - m[ztMat4_Col0Row2]) * mult, (m[ztMat4_Col0Row1] - m[ztMat4_Col1Row0]) * mult, biggest_value);
		case 1: return zt_quat(biggest_value                                   , (m[ztMat4_Col0Row1] + m[ztMat4_Col1Row0]) * mult, (m[ztMat4_Col2Row0] + m[ztMat4_Col0Row2]) * mult, (m[ztMat4_Col1Row2] - m[ztMat4_Col2Row1]) * mult);
		case 2: return zt_quat((m[ztMat4_Col0Row1] + m[ztMat4_Col1Row0]) * mult, biggest_value                                   , (m[ztMat4_Col1Row2] + m[ztMat4_Col2Row1]) * mult, (m[ztMat4_Col2Row0] - m[ztMat4_Col0Row2]) * mult);
		case 3: return zt_quat((m[ztMat4_Col2Row0] + m[ztMat4_Col0Row2]) * mult, (m[ztMat4_Col1Row2] + m[ztMat4_Col2Row1]) * mult, biggest_value                                   , (m[ztMat4_Col0Row1] - m[ztMat4_Col1Row0]) * mult);
		default: zt_assert(false);
	}

	return ztQuat::identity;
}

// ================================================================================================================================================================================================

/*static*/ ztQuat ztQuat::makeFromDirection(const ztVec3& dir, const ztVec3& up)
{
	ZT_PROFILE_TOOLS("ztQuat::makeFromDirection");

	ztMat4 mat = ztMat4::identity;
	mat.lookAt(ztVec3::zero, dir, up);

	return ztQuat::makeFromMat4(mat);
}

// ================================================================================================================================================================================================

/*static*/ ztQuat ztQuat::makeFromPoints(const ztVec3& p1, const ztVec3 p2)
{
	ZT_PROFILE_TOOLS("ztQuat::makeFromPoints");

	ztQuat quat;
	quat.xyz = p1.cross(p2);
	quat.w = zt_sqrt(zt_pow(p1.length(), 2) * zt_pow(p2.length(), 2)) + p1.dot(p2);
	quat.normalize();
	return quat;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool zt_strEquals(const char *s1, const char *s2)
{
	ZT_PROFILE_TOOLS("zt_strEquals");

	return zt_strCmp(s1, s2) == 0;
}

// ================================================================================================================================================================================================

bool zt_strEquals(const char *s1, int s1_len, const char *s2)
{
	ZT_PROFILE_TOOLS("zt_strEquals");

	return zt_strCmp(s1, s1_len, s2, zt_strLen(s2)) == 0;
}

// ================================================================================================================================================================================================

bool zt_strEquals(const char *s1, int s1_len, const char *s2, int s2_len)
{
	ZT_PROFILE_TOOLS("zt_strEquals");

	return zt_strCmp(s1, s1_len, s2, s2_len) == 0;
}

// ================================================================================================================================================================================================

bool zt_striEquals(const char *s1, const char *s2)
{
	ZT_PROFILE_TOOLS("zt_striEquals");

	return zt_striCmp(s1, s2) == 0;
}

// ================================================================================================================================================================================================

bool zt_striEquals(const char *s1, int s1_len, const char *s2)
{
	ZT_PROFILE_TOOLS("zt_striEquals");

	return zt_striCmp(s1, s1_len, s2, zt_strLen(s2)) == 0;
}

// ================================================================================================================================================================================================

bool zt_striEquals(const char *s1, int s1_len, const char *s2, int s2_len)
{
	ZT_PROFILE_TOOLS("zt_striEquals");

	return zt_striCmp(s1, s1_len, s2, s2_len) == 0;
}

// ================================================================================================================================================================================================

bool zt_strValid(const char *s, const char **invalid_ch)
{
	ZT_PROFILE_TOOLS("zt_strValid");

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

// ================================================================================================================================================================================================

int zt_strLen(const char *s)
{
	ZT_PROFILE_TOOLS("zt_strLen");

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

// ================================================================================================================================================================================================

int zt_strSize(const char *s)
{
	ZT_PROFILE_TOOLS("zt_strSize");

	if (!s) return 0;

	int size = 0;
	while (s[size]) {
		size++;
	}

	return ++size; // add null terminator
}

// ================================================================================================================================================================================================

#define _zt_strCmpIsEmpty(s) ((s) == nullptr || *(s) == 0)

int zt_strCmp(const char *s1, const char *s2)
{
	ZT_PROFILE_TOOLS("zt_strCmp");

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

// ================================================================================================================================================================================================

int zt_strCmp(const char *s1, int s1_len, const char *s2, int s2_len)
{
	ZT_PROFILE_TOOLS("zt_strCmp");

	if (_zt_strCmpIsEmpty(s1) || _zt_strCmpIsEmpty(s2)) {
		if (_zt_strCmpIsEmpty(s1) && !_zt_strCmpIsEmpty(s2)) return -1;
		if (!_zt_strCmpIsEmpty(s1) && _zt_strCmpIsEmpty(s2)) return 1;
		return 0;
	}

	while (s1 && s2 && s1_len && s2_len && *s1 && *s2 && *s1 == *s2) { ++s1; ++s2; --s1_len; --s2_len; }

	if (s1_len + s2_len == 0) return 0;

	if (*s1 == *s2) return 0;
	if (*s1 < *s2) return -1;
	return 1;
}

// ================================================================================================================================================================================================

int zt_striCmp(const char *s1, const char *s2)
{
	ZT_PROFILE_TOOLS("zt_striCmp");

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

	if (*s1 == *s2) return 0;
	if (*s1 < *s2) return -1;
	return 1;
}

// ================================================================================================================================================================================================

int zt_striCmp(const char *s1, int s1_len, const char *s2, int s2_len)
{
	ZT_PROFILE_TOOLS("zt_striCmp");

	if (_zt_strCmpIsEmpty(s1) || _zt_strCmpIsEmpty(s2)) {
		if (_zt_strCmpIsEmpty(s1) && !_zt_strCmpIsEmpty(s2)) return -1;
		if (!_zt_strCmpIsEmpty(s1) && _zt_strCmpIsEmpty(s2)) return 1;
		return 0;
	}

	while (*s1 && *s2 && s1_len && s2_len) {
		char c1 = *s1++;
		char c2 = *s2++;

		if (c1 >= 97 && c1 <= 122) c1 -= 32;
		if (c2 >= 97 && c2 <= 122) c2 -= 32;

		if (c1 != c2) {
			return c1 < c2 ? -1 : 1;
		}

		--s1_len; --s2_len;
	}

	if (*s1 == *s2) return 0;
	if (*s1 < *s2) return -1;
	return 1;
}

#undef _zt_strCmpIsEmpty

// ================================================================================================================================================================================================

const char *zt_strMoveForward(const char *s, int characters)
{
	ZT_PROFILE_TOOLS("zt_strMoveForward");

	if (!s || characters < 0) return nullptr;

	while (*s && characters-- > 0) {
		if (0xf0 == (0xf8 & *s)) { s += 4; } // 4-byte utf8 code point (began with 0b11110xxx)
		else if (0xe0 == (0xf0 & *s)) { s += 3; } // 3-byte utf8 code point (began with 0b1110xxxx)
		else if (0xc0 == (0xe0 & *s)) { s += 2; } // 2-byte utf8 code point (began with 0b110xxxxx)
		else { s += 1; } // if (0x00 == (0x80 & *s)) { // 1-byte ascii (began with 0b0xxxxxxx)
	}
	return s;
}

// ================================================================================================================================================================================================

int zt_strCpy(char *scopy, int scopy_len, const char *sfrom)
{
	return zt_strCpy(scopy, scopy_len, sfrom, zt_strLen(sfrom));
}

// ================================================================================================================================================================================================

int zt_strCpy(char *scopy, int scopy_len, const char *sfrom, int sfrom_len)
{
	ZT_PROFILE_TOOLS("zt_strCpy");

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

// ================================================================================================================================================================================================

int zt_strCat(char *scat, int scat_len, const char *scopy)
{
	return zt_strCat(scat, scat_len, scopy, zt_strLen(scopy));
}

// ================================================================================================================================================================================================

int zt_strCat(char *scat, int scat_len, const char *scopy, int scopy_len)
{
	ZT_PROFILE_TOOLS("zt_strCat");

	if (!scat || scat_len <= 0) {
		return 0;
	}
	if (!scopy || scopy_len <= 0) {
		scat[0] = 0;
		return 0;
	}

	int start = 0;
	while (*scat) {
		start += 1;
		scat++;
	}

	int max_idx = zt_min((scat_len - start) - 1, scopy_len);
	zt_fiz(max_idx) {
		scat[i] = scopy[i];
	}
	scat[max_idx] = 0;
	return max_idx + start;
}

// ================================================================================================================================================================================================

int zt_strCatf(char *scat, int scat_len, const char *format, ...)
{
	ZT_PROFILE_TOOLS("zt_strCatf");

	if (!scat || scat_len <= 0) {
		return 0;
	}

	int start = 0;
	while (*scat) {
		start += 1;
		scat++;
	}

	int max_idx = (scat_len - start) - 1;

#	if defined(ZT_WINDOWS)
	va_list arg_ptr;
	va_start(arg_ptr, format);
	return vsnprintf_s(scat, max_idx, max_idx, format, arg_ptr);
#	else
#	error "zt_strCatf needs an implementation for this platform"
#	endif
}

// ================================================================================================================================================================================================

bool zt_strIsInt(char *s)
{
	ZT_PROFILE_TOOLS("zt_strIsInt");

	bool success = false;
	zt_strToInt(s, 0, &success);
	return success;
}

// ================================================================================================================================================================================================

bool zt_strIsInt(char *s, int s_len)
{
	ZT_PROFILE_TOOLS("zt_strIsInt");

	bool success = false;
	zt_strToInt(s, s_len, 0, &success);
	return success;
}

// ================================================================================================================================================================================================

bool zt_strIsIntHex(char *s)
{
	ZT_PROFILE_TOOLS("zt_strIsIntHex");

	bool success = false;
	zt_strToIntHex(s, 0, &success);
	return success;
}

// ================================================================================================================================================================================================

bool zt_strIsIntHex(char *s, int s_len)
{
	ZT_PROFILE_TOOLS("zt_strIsIntHex");

	bool success = false;
	zt_strToIntHex(s, s_len, 0, &success);
	return success;
}

// ================================================================================================================================================================================================

bool zt_strIsReal32(char *s)
{
	ZT_PROFILE_TOOLS("zt_strIsReal32");

	bool success = false;
	zt_strToReal32(s, 0, &success);
	return success;
}

// ================================================================================================================================================================================================

bool zt_strIsReal32(char *s, int s_len)
{
	ZT_PROFILE_TOOLS("zt_strIsReal32");

	bool success = false;
	zt_strToReal32(s, s_len, 0, &success);
	return success;
}

// ================================================================================================================================================================================================

bool zt_strIsReal64(char *s)
{
	ZT_PROFILE_TOOLS("zt_strIsReal64");

	bool success = false;
	zt_strToReal64(s, 0, &success);
	return success;
}

// ================================================================================================================================================================================================

bool zt_strIsReal64(char *s, int s_len)
{
	ZT_PROFILE_TOOLS("zt_strIsReal64");

	bool success = false;
	zt_strToReal64(s, s_len, 0, &success);
	return success;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

i32 zt_strToInt(const char *s, i32 def, bool* success)
{
	return zt_strToInt(s, zt_strLen(s), def, success);
}

// ================================================================================================================================================================================================

i32 zt_strToInt(const char *s, int s_len, i32 def, bool* success)
{
	ZT_PROFILE_TOOLS("zt_strToInt");

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

// ================================================================================================================================================================================================

u32 zt_strToUint(const char *s, u32 def, bool* success)
{
	return zt_strToUint(s, zt_strLen(s), def, success);
}

// ================================================================================================================================================================================================

u32 zt_strToUint(const char *s, int s_len, u32 def, bool* success)
{
	ZT_PROFILE_TOOLS("zt_strToUint");

	_zt_str_to_prepare_and_check;

	zt_fiz(s_len) {
		if (s[i] < '0' || s[i] > '9') {
			if (success) *success = false;
			return def;
		}
	}

	if (success) *success = true;

	char buffer[128];
	zt_strCpy(buffer, zt_elementsOf(buffer), s, s_len);

	return strtoul(buffer, nullptr, 10);
}

// ================================================================================================================================================================================================

u32 zt_strToIntHex(const char *s, u32 def, bool* success)
{
	return zt_strToIntHex(s, zt_strLen(s), def, success);
}

// ================================================================================================================================================================================================

u32 zt_strToIntHex(const char *s, int s_len, u32 def, bool* success)
{
	ZT_PROFILE_TOOLS("zt_strToIntHex");

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

// ================================================================================================================================================================================================

i64 zt_strToInt64(const char *s, i64 def, bool *success)
{
	return zt_strToInt64(s, zt_strLen(s), def, success);
}

// ================================================================================================================================================================================================

i64 zt_strToInt64(const char *s, int s_len, i64 def, bool *success)
{
	ZT_PROFILE_TOOLS("zt_strToInt64");

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

#	if defined(ZT_COMPILER_MSVC)
	return _strtoi64(buffer, nullptr, 10);
#	else
	return strtoll(buffer, nullptr, 10);
#	endif
}

// ================================================================================================================================================================================================

u64 zt_strToUint64(const char *s, u64 def, bool *success)
{
	return zt_strToUint64(s, zt_strLen(s), def, success);
}

// ================================================================================================================================================================================================

u64 zt_strToUint64(const char *s, int s_len, u64 def, bool *success)
{
	ZT_PROFILE_TOOLS("zt_strToUint64");

	_zt_str_to_prepare_and_check;

	zt_fiz(s_len) {
		if (s[i] < '0' || s[i] > '9') {
			if (success) *success = false;
			return def;
		}
	}

	if (success) *success = true;

	char buffer[128];
	zt_strCpy(buffer, zt_elementsOf(buffer), s, s_len);

#	if defined(ZT_COMPILER_MSVC)
	return _strtoui64(buffer, nullptr, 10);
#	else
	return strtoull(buffer, nullptr, 10);
#	endif
}

// ================================================================================================================================================================================================

r32 zt_strToReal32(const char *s, r32 def, bool* success)
{
	return zt_strToReal32(s, zt_strLen(s), def, success);
}

// ================================================================================================================================================================================================

r32 zt_strToReal32(const char *s, int s_len, r32 def, bool* success)
{
	ZT_PROFILE_TOOLS("zt_strToReal32");

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

// ================================================================================================================================================================================================

r64 zt_strToReal64(const char *s, r64 def, bool* success)
{
	return zt_strToReal64(s, zt_strLen(s), def, success);
}

// ================================================================================================================================================================================================

r64 zt_strToReal64(const char *s, int s_len, r64 def, bool* success)
{
	ZT_PROFILE_TOOLS("zt_strToReal64");

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

// ================================================================================================================================================================================================

#undef _zt_str_to_prepare_and_check

// ================================================================================================================================================================================================

u32 zt_strHash(const char *s)
{
	//ZT_PROFILE_TOOLS("zt_strHash"); this is called in the profiling code

	if (s == nullptr) {
		return 0;
	}

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

	u32 s_len = 0;
	const char *sc = s;
	while (*sc) {
		if (0xf0 == (0xf8 & *sc)) { sc += 4; } // 4-byte utf8 code point (began with 0b11110xxx)
		else if (0xe0 == (0xf0 & *sc)) { sc += 3; } // 3-byte utf8 code point (began with 0b1110xxxx)
		else if (0xc0 == (0xe0 & *sc)) { sc += 2; } // 2-byte utf8 code point (began with 0b110xxxxx)
		else { sc += 1; } // if (0x00 == (0x80 & *s)) { // 1-byte ascii (began with 0b0xxxxxxx)
		++s_len;
	}

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

// ================================================================================================================================================================================================

const char *zt_strFind(const char *haystack, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_strFind");

	int haystack_len = zt_strLen(haystack);
	return zt_strFind(haystack, haystack_len, needle);
}

// ================================================================================================================================================================================================

const char *zt_strFind(const char *haystack, int haystack_len, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_strFind");

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

// ================================================================================================================================================================================================

int zt_strFindPos(const char *haystack, const char *needle, int start_pos)
{
	ZT_PROFILE_TOOLS("zt_strFindPos");

	int haystack_len = zt_strLen(haystack);
	return zt_strFindPos(haystack, haystack_len, needle, start_pos);
}

// ================================================================================================================================================================================================

int zt_strFindPos(const char *haystack, int haystack_len, const char *needle, int start_pos)
{
	ZT_PROFILE_TOOLS("zt_strFindPos");

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

// ================================================================================================================================================================================================

const char *zt_strFindLast(const char *haystack, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_strFindLast");

	int haystack_len = zt_strLen(haystack);
	return zt_strFindLast(haystack, haystack_len, needle);
}

// ================================================================================================================================================================================================

const char *zt_strFindLast(const char *haystack, int haystack_len, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_strFindLast");

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

// ================================================================================================================================================================================================

int zt_strFindLastPos(const char *haystack, const char *needle, int start_pos)
{
	ZT_PROFILE_TOOLS("zt_strFindLastPos");

	int haystack_len = zt_strLen(haystack);
	return zt_strFindLastPos(haystack, haystack_len, needle, start_pos);
}

// ================================================================================================================================================================================================

int zt_strFindLastPos(const char *haystack, int haystack_len, const char *needle, int start_pos)
{
	ZT_PROFILE_TOOLS("zt_strFindLastPos");

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

// ================================================================================================================================================================================================

#define _zt_to_upper(c)	((c) >= 97 && (c) <= 122 ? (c) - 32 : (c))

// ================================================================================================================================================================================================

const char *zt_striFind(const char *haystack, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_striFind");

	int haystack_len = zt_strLen(haystack);
	return zt_striFind(haystack, haystack_len, needle);
}

// ================================================================================================================================================================================================

const char *zt_striFind(const char *haystack, int haystack_len, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_striFind");

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

// ================================================================================================================================================================================================

int zt_striFindPos(const char *haystack, const char *needle, int start_pos)
{
	ZT_PROFILE_TOOLS("zt_striFindPos");

	int haystack_len = zt_strLen(haystack);
	return zt_striFindPos(haystack, haystack_len, needle, start_pos);
}

// ================================================================================================================================================================================================

int zt_striFindPos(const char *haystack, int haystack_len, const char *needle, int start_pos)
{
	ZT_PROFILE_TOOLS("zt_striFindPos");

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

// ================================================================================================================================================================================================

const char *zt_striFindLast(const char *haystack, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_striFindLast");

	int haystack_len = zt_strLen(haystack);
	return zt_striFindLast(haystack, haystack_len, needle);
}

// ================================================================================================================================================================================================

const char *zt_striFindLast(const char *haystack, int haystack_len, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_striFindLast");

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

// ================================================================================================================================================================================================

int zt_striFindLastPos(const char *haystack, const char *needle, int start_pos)
{
	ZT_PROFILE_TOOLS("zt_striFindLastPos");

	int haystack_len = zt_strLen(haystack);
	return zt_striFindLastPos(haystack, haystack_len, needle, start_pos);
}

// ================================================================================================================================================================================================

int zt_striFindLastPos(const char *haystack, int haystack_len, const char *needle, int start_pos)
{
	ZT_PROFILE_TOOLS("zt_striFindLastPos");

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

// ================================================================================================================================================================================================

const char *zt_strFindFirstOf(const char *haystack, const char **needles, int needles_count)
{
	ZT_PROFILE_TOOLS("zt_strFindFirstOf");

	return zt_strFindFirstOf(haystack, zt_strLen(haystack), needles, needles_count);
}

// ================================================================================================================================================================================================

const char *zt_strFindFirstOf(const char *haystack, int haystack_len, const char **needles, int needles_count)
{
	ZT_PROFILE_TOOLS("zt_strFindFirstOf");

	const char *result = nullptr;
	zt_fiz(needles_count) {
		const char *found = zt_strFind(haystack, haystack_len, needles[i]);
		if (found && (result == nullptr || found < result)) {
			result = found;
		}
	}

	return result;
}

// ================================================================================================================================================================================================

int zt_strFindFirstOfPos(const char *haystack, const char **needles, int needles_count)
{
	ZT_PROFILE_TOOLS("zt_strFindFirstOfPos");

	return zt_strFindFirstOfPos(haystack, zt_strLen(haystack), needles, needles_count);
}

// ================================================================================================================================================================================================

int zt_strFindFirstOfPos(const char *haystack, int haystack_len, const char **needles, int needles_count)
{
	ZT_PROFILE_TOOLS("zt_strFindFirstOfPos");

	int result = ztStrPosNotFound;
	zt_fiz(needles_count) {
		int found = zt_strFindPos(haystack, haystack_len, needles[i], 0);
		if (found != ztStrPosNotFound && (result == ztStrPosNotFound || found < result)) {
			result = found;
		}
	}

	return result;

}

// ================================================================================================================================================================================================

int zt_strCount(const char *haystack, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_strCount");

	return zt_strCount(haystack, zt_strLen(haystack), needle);
}

// ================================================================================================================================================================================================

int zt_strCount(const char *haystack, int haystack_len, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_strCount");

	int count = 0;
	int pos = zt_strFindPos(haystack, haystack_len, needle, 0);
	while (pos != ztStrPosNotFound) {
		count += 1;
		pos = zt_strFindPos(haystack, haystack_len, needle, pos + 1);
	}

	return count;
}

// ================================================================================================================================================================================================

int zt_striCount(const char *haystack, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_striCount");

	return zt_striCount(haystack, zt_strLen(haystack), needle);
}

// ================================================================================================================================================================================================

int zt_striCount(const char *haystack, int haystack_len, const char *needle)
{
	ZT_PROFILE_TOOLS("zt_striCount");

	int count = 0;
	int pos = zt_striFindPos(haystack, haystack_len, needle, 0);
	while (pos != ztStrPosNotFound) {
		count += 1;
		pos = zt_striFindPos(haystack, haystack_len, needle, pos + 1);
	}

	return count;
}

// ================================================================================================================================================================================================

bool zt_strStartsWith(const char *s, const char *starts_with)
{
	ZT_PROFILE_TOOLS("zt_strStartsWith");

	return zt_strStartsWith(s, zt_strLen(s), starts_with, zt_strLen(starts_with));
}

// ================================================================================================================================================================================================

bool zt_strStartsWith(const char *s, int s_len, const char *starts_with, int sw_len)
{
	ZT_PROFILE_TOOLS("zt_strStartsWith");

	if (!s || !starts_with || s_len <= 0 || sw_len <= 0 || s_len < sw_len) return false;

	zt_fiz(sw_len) {
		if (s[i] != starts_with[i])
			return false;
	}

	return true;
}

// ================================================================================================================================================================================================

bool zt_strEndsWith(const char *s, const char *ends_with)
{
	ZT_PROFILE_TOOLS("zt_strEndsWith");

	return zt_strEndsWith(s, zt_strLen(s), ends_with, zt_strLen(ends_with));
}

// ================================================================================================================================================================================================

bool zt_strEndsWith(const char *s, int s_len, const char *ends_with, int ew_len)
{
	ZT_PROFILE_TOOLS("zt_strEndsWith");

	if (!s || !ends_with || s_len <= 0 || ew_len <= 0 || s_len < ew_len) return false;

	for (int i = s_len - ew_len, e = 0; i < s_len; ++i, ++e) {
		if (s[i] != ends_with[e])
			return false;
	}

	return true;
}

// ================================================================================================================================================================================================

bool zt_striStartsWith(const char *s, const char *starts_with)
{
	ZT_PROFILE_TOOLS("zt_striStartsWith");

	return zt_striStartsWith(s, zt_strLen(s), starts_with, zt_strLen(starts_with));
}

// ================================================================================================================================================================================================

bool zt_striStartsWith(const char *s, int s_len, const char *starts_with, int sw_len)
{
	ZT_PROFILE_TOOLS("zt_striStartsWith");

	if (!s || !starts_with || s_len <= 0 || sw_len <= 0 || s_len < sw_len) return false;

	zt_fiz(sw_len) {
		if (_zt_to_upper(s[i]) != _zt_to_upper(starts_with[i]))
			return false;
	}

	return true;
}

// ================================================================================================================================================================================================

bool zt_striEndsWith(const char *s, const char *ends_with)
{
	ZT_PROFILE_TOOLS("zt_striEndsWith");

	return zt_striEndsWith(s, zt_strLen(s), ends_with, zt_strLen(ends_with));
}

// ================================================================================================================================================================================================

bool zt_striEndsWith(const char *s, int s_len, const char *ends_with, int ew_len)
{
	ZT_PROFILE_TOOLS("zt_striEndsWith");

	if (!s || !ends_with || s_len <= 0 || ew_len <= 0 || s_len < ew_len) return false;

	for (int i = s_len - ew_len, e = 0; i < s_len; ++i, ++e) {
		if (_zt_to_upper(s[i]) != _zt_to_upper(ends_with[e]))
			return false;
	}

	return true;
}

// ================================================================================================================================================================================================

const char *zt_strJumpToNextToken(const char *s)
{
	ZT_PROFILE_TOOLS("zt_strJumpToNextToken");

	return zt_strJumpToNextToken(s, zt_strLen(s));
}

// ================================================================================================================================================================================================

const char *zt_strJumpToNextToken(const char *s, int s_len)
{
	ZT_PROFILE_TOOLS("zt_strJumpToNextToken");

	if (!s || s_len <= 0) return nullptr;

	for (int i = 1; i < s_len; ++i) {
		char ch = s[i];
		if (!(ch >= 48 && ch <= 57) && !(ch >= 65 && ch <= 90) && !(ch >= 97 && ch <= 122)) {
			return s + i;
		}
	}

	return nullptr;
}

// ================================================================================================================================================================================================

int zt_strGetNextTokenPos(const char *s)
{
	ZT_PROFILE_TOOLS("zt_strGetNextTokenPos");

	return zt_strGetNextTokenPos(s, zt_strLen(s));
}

// ================================================================================================================================================================================================

int zt_strGetNextTokenPos(const char *s, int s_len)
{
	ZT_PROFILE_TOOLS("zt_strGetNextTokenPos");

	if (!s || s_len <= 0) return ztStrPosNotFound;

	for (int i = 1; i < s_len; ++i) {
		char ch = s[i];
		if (!(ch >= 48 && ch <= 57) && !(ch >= 65 && ch <= 90) && !(ch >= 97 && ch <= 122)) {
			return i;
		}
	}

	return ztStrPosNotFound;
}

// ================================================================================================================================================================================================

const char *zt_strJumpToNextLine(const char *s)
{
	ZT_PROFILE_TOOLS("zt_strJumpToNextLine");

	return zt_strJumpToNextLine(s, zt_strLen(s));
}

// ================================================================================================================================================================================================

const char *zt_strJumpToNextLine(const char *s, int s_len)
{
	ZT_PROFILE_TOOLS("zt_strJumpToNextLine");

	if (!s || s_len <= 0) return nullptr;

	for (int i = 1; i < s_len; ++i) {
		char ch = s[i];
		if (ch == '\n') {
			return s + (i + 1);
		}
	}

	return nullptr;
}

// ================================================================================================================================================================================================

int zt_strGetNextLinePos(const char *s)
{
	ZT_PROFILE_TOOLS("zt_strGetNextLinePos");

	return zt_strGetNextLinePos(s, zt_strLen(s));
}

// ================================================================================================================================================================================================

int zt_strGetNextLinePos(const char *s, int s_len)
{
	ZT_PROFILE_TOOLS("zt_strGetNextLinePos");

	if (!s || s_len <= 0) return ztStrPosNotFound;

	for (int i = 1; i < s_len; ++i) {
		char ch = s[i];
		if (ch == '\n') {
			return (i + 1);
		}
	}

	return ztStrPosNotFound;
}

// ================================================================================================================================================================================================

int zt_strGetBetween(char *buffer, int buffer_len, const char *s, const char *beg, const char *end, int beg_offset, int end_offset)
{
	ZT_PROFILE_TOOLS("zt_strGetBetween");

	return zt_strGetBetween(buffer, buffer_len, s, zt_strLen(s), beg, end, beg_offset, end_offset);
}

// ================================================================================================================================================================================================

int zt_strGetBetween(char *buffer, int buffer_len, const char *s, int s_len, const char *beg, const char *end, int beg_offset, int end_offset)
{
	ZT_PROFILE_TOOLS("zt_strGetBetween");

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

// ================================================================================================================================================================================================

int zt_strTokenize(const char *s, const char *tokens, ztToken* results, int results_count, int32 flags)
{
	ZT_PROFILE_TOOLS("zt_strTokenize");

	return zt_strTokenize(s, zt_strLen(s), tokens, results, results_count, flags);
}

// ================================================================================================================================================================================================

int zt_strTokenize(const char *s, int s_len, const char *tokens, ztToken* results, int results_count, int32 flags)
{
	ZT_PROFILE_TOOLS("zt_strTokenize");

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

// ================================================================================================================================================================================================

int zt_strPrintf(char *buffer, int buffer_size, const char *format, ...)
{
	ZT_PROFILE_TOOLS("zt_strPrintf");

#if defined(ZT_WINDOWS)
	va_list arg_ptr;
	va_start(arg_ptr, format);
	return vsnprintf_s(buffer, buffer_size, buffer_size, format, arg_ptr);
#else
#	error "zt_strPrintf needs an implementation for this platform"
#endif
}

// ================================================================================================================================================================================================

int zt_strBytesToString(char *buffer, int buffer_size, i32 bytes)
{
	ZT_PROFILE_TOOLS("zt_strBytesToString");

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

// ================================================================================================================================================================================================

int zt_strNumberToString(char *buffer, int buffer_size, i64 number)
{
	ZT_PROFILE_TOOLS("zt_strNumberToString");

	if (buffer_size < 64) return 0;

	zt_strPrintf(buffer, buffer_size, "%lld", number);

	int neg_offset = number < 0 ? 1 : 0;

	int str_len = zt_strLen(buffer);

	int offsets[] = { 3, 7, 12, 18 };

	zt_fize(offsets) {
		if (str_len - neg_offset > offsets[i]) {
			for (int j = str_len; j > str_len - offsets[i]; --j) {
				buffer[j] = buffer[j - 1];
			}
			buffer[str_len - offsets[i]] = ',';
			buffer[++str_len] = 0;
		}
		else break;
	}

	return str_len;
}

// ================================================================================================================================================================================================

int zt_strConvertToUTF16(const char* s, int s_len, u16* buffer, int buffer_size)
{
	ZT_PROFILE_TOOLS("zt_strConvertToUTF16");

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

// ================================================================================================================================================================================================

ztString zt_stringMake(int size, ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_stringMake");

	if (size < 16) {
		size = 16;
	}

	size += zt_sizeof(i32);

	void *data = zt_memAlloc(arena, size);
	*((i32*)data) = size - zt_sizeof(i32);

	char *result = (char*)data + zt_sizeof(i32);
	*result = 0;

	return result;
}

// ================================================================================================================================================================================================

ztString zt_stringMakeFrom(const char *str, ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_stringMakeFrom");

	int size = zt_strSize(str);
	if (size == 0) {
		return nullptr;
	}

	ztString result = zt_stringMake(size, arena);
	zt_strCpy(result, size, str);
	return result;
}

// ================================================================================================================================================================================================

ztString zt_stringMakeFrom(const char *str, int s_len, ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_stringMakeFrom");

	int size = s_len;
	if (size == 0) {
		return nullptr;
	}
	size += 1;

	ztString result = zt_stringMake(size, arena);
	zt_strCpy(result, size, str);
	return result;
}

// ================================================================================================================================================================================================

ztString zt_stringOverwrite(ztString string, const char *str, ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_stringOverwrite");

	int size = zt_strSize(str);
	if (size == 0) {
		return nullptr;
	}

	ztString result = zt_stringResize(string, size, arena);
	zt_strCpy(result, size, str);
	return result;
}

// ================================================================================================================================================================================================

ztString zt_stringResize(ztString string, int nsize, ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_stringResize");

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

// ================================================================================================================================================================================================

void zt_stringFree(ztString string, ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_stringFree");

	if (string) {
		void *data = (string - zt_sizeof(i32));
		zt_freeArena(data, arena);
	}
}

// ================================================================================================================================================================================================

#define _zt_stringSizeFast(STR)  (*((i32*)(STR - zt_sizeof(i32))))

// ================================================================================================================================================================================================

int zt_stringSize(ztString string)
{
	ZT_PROFILE_TOOLS("zt_stringSize");

	if (string == nullptr) {
		return 0;
	}

	//return *((i32*)(string - zt_sizeof(i32)));
	return _zt_stringSizeFast(string);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztStringPool zt_stringPoolMake(int total_strings, int *sizes, int *proportions, int sizes_count, ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_stringPoolMake");
	zt_assert(sizes != nullptr && proportions != nullptr);
	zt_assert(total_strings > 0 && sizes_count > 0);

	ztStringPool pool = {};
	pool.arena   = arena ? arena : zt_memGetGlobalArena();
	pool.size    = total_strings;
	pool.strings = zt_mallocStructArrayArena(ztString, total_strings, pool.arena);
	pool.used    = zt_mallocStructArrayArena(bool, total_strings, pool.arena);

	r32 total_prop = 0;
	zt_fiz(sizes_count) {
		total_prop += (r32)proportions[i];
	}

	int idx = 0;
	zt_fiz(sizes_count) {
		int count_this_entry = zt_convertToi32Floor((proportions[i] / total_prop) * total_strings);
		if (i == sizes_count - 1) {
			count_this_entry = total_strings - idx;
		}

		zt_fjz(count_this_entry) {
			pool.strings[idx] = zt_stringMake(sizes[i], pool.arena);
			pool.used   [idx] = false;
			idx += 1;
		}
	}

	return pool;
}

// ================================================================================================================================================================================================

void zt_stringPoolFree(ztStringPool *pool)
{
	ZT_PROFILE_TOOLS("zt_stringPoolFree");
	zt_returnOnNull(pool);

	zt_fiz(pool->size) {
		zt_stringFree(pool->strings[i], pool->arena);
	}

	zt_freeArena(pool->used, pool->arena);
	zt_freeArena(pool->strings, pool->arena);

	pool->used    = nullptr;
	pool->strings = nullptr;
	pool->size    = 0;
}

// ================================================================================================================================================================================================

i32 zt_stringPoolBytesNeeded(int total_strings, int *sizes, int *proportions, int sizes_count)
{
	r32 total_prop = 0;
	zt_fiz(sizes_count) {
		total_prop += (r32)proportions[i];
	}

	i32 bytes_needed = 0;

	int idx = 0;
	zt_fiz(sizes_count) {
		int count_this_entry = zt_convertToi32Floor(proportions[i] / total_prop);
		if (i == sizes_count - 1) {
			count_this_entry = total_strings - idx;
		}

		zt_fjz(count_this_entry) {
			bytes_needed += zt_max(16, sizes[i]) + zt_sizeof(i32);
			idx += 1;
		}
	}

	i32 buffer_per_alloc = 16;

	bytes_needed += total_strings * (zt_sizeof(ztMemoryArena::allocation) + zt_sizeof(ztPointerSize) + buffer_per_alloc);

	return bytes_needed;
}

// ================================================================================================================================================================================================

ztString zt_stringMake(ztStringPool *pool, int size)
{
	ZT_PROFILE_TOOLS("zt_stringMakeFromPool");
	zt_returnValOnNull(pool, zt_stringMake(size));

	zt_fiz(pool->size) {
		if (!pool->used[i] && _zt_stringSizeFast(pool->strings[i]) >= size) {
			pool->used[i] = true;
			return pool->strings[i];
		}
	}

	if ((pool->arena->total_size - pool->arena->current_used) < size + zt_sizeof(ztMemoryArena::allocation) + ztPointerSize + 16) {
		return zt_stringMake(size);
	}

	return zt_stringMake(size, pool->arena);
}

// ================================================================================================================================================================================================

ztString zt_stringMakeFrom(ztStringPool *pool, const char* str)
{
	return zt_stringMakeFrom(pool, str, zt_strLen(str));
}

// ================================================================================================================================================================================================

ztString zt_stringMakeFrom(ztStringPool *pool, const char* str, int s_len)
{
	ZT_PROFILE_TOOLS("zt_stringMakeFromFromPool");

	int size = s_len;
	if (size == 0) {
		return nullptr;
	}
	size += 1;

	ztString result = zt_stringMake(pool, size);
	if (result) {
		zt_strCpy(result, size, str);
	}
	return result;
}

// ================================================================================================================================================================================================

ztString zt_stringResize(ztStringPool *pool, ztString string, int size)
{
	ZT_PROFILE_TOOLS("zt_stringResizeFromPool");
	zt_returnValOnNull(pool, zt_stringResize(string, size));

	if (string == nullptr) {
		return zt_stringMake(pool, size);
	}

	int str_size = _zt_stringSizeFast(string);
	if (str_size >= size) {
		return string;
	}

	zt_fiz(pool->size) {
		if (pool->strings[i] == string) {
			pool->used[i] = false;
			break;
		}
	}

	return zt_stringMake(pool, size);
}

// ================================================================================================================================================================================================

ztString zt_stringOverwrite(ztStringPool *pool, ztString string, const char *str)
{
	ZT_PROFILE_TOOLS("zt_stringOverwrite");
	zt_returnValOnNull(pool, zt_stringOverwrite(string, str));

	int size = zt_strSize(str);
	if (size == 0) {
		return nullptr;
	}

	ztString result = zt_stringResize(pool, string, size);
	zt_strCpy(result, size, str);
	return result;
}

// ================================================================================================================================================================================================

void zt_stringFree(ztStringPool *pool, ztString string)
{
	ZT_PROFILE_TOOLS("zt_stringFreeFromPool");
	if (pool == nullptr) {
		zt_assert(false);
		zt_stringFree(string);
		return;
	}

	zt_fiz(pool->size) {
		if (pool->strings[i] == string) {
			pool->used[i] = false;
			return;
		}
	}

	if (zt_memBelongsTo(pool->arena, string)) {
		zt_stringFree(string, pool->arena);
	}
	else {
		zt_stringFree(string);
	}
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool zt_fileOpen(ztFile *file, const char *file_name, ztFileOpenMethod_Enum file_open_method, ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_fileOpen");

	zt_returnValOnNull(file, false);
	zt_returnValOnNull(file_name, false);

	zt_memSet(file, zt_sizeof(ztFile), 0);

#	if defined(ZT_WINDOWS)
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
		zt_logCritical("zt_fileOpen: unable to open file: '%s' (error code: %d)", file_name, (i32)ofs.nErrCode);
		return false;
	}

	i32 path_len = zt_strLen(ofs.szPathName);

	file->full_name = (char *)zt_memAllocFromArena(arena, path_len + 1);
	if (file->full_name == nullptr) {
		zt_logCritical("zt_fileOpen: unable to allocate memory for file information (file: '%s')", file_name);
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
#	endif
}

// ================================================================================================================================================================================================

void zt_fileClose(ztFile *file)
{
	ZT_PROFILE_TOOLS("zt_fileClose");

	zt_returnOnNull(file);

#	if defined(ZT_WINDOWS)
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
#	endif
}

// ================================================================================================================================================================================================

i32 zt_fileGetReadPos(ztFile *file)
{
	ZT_PROFILE_TOOLS("zt_fileGetReadPos");

	zt_returnValOnNull(file, 0);

#if defined(ZT_WINDOWS)
	return file->win_read_pos;
#endif
}

// ================================================================================================================================================================================================

bool zt_fileSetReadPos(ztFile *file, i32 pos)
{
	ZT_PROFILE_TOOLS("zt_fileSetReadPos");

	zt_returnValOnNull(file, false);

	if (pos > file->size) {
		zt_logDebug("zt_fileSetReadPos: attempting to set position beyond file size (%s)", file->full_name);
		return false;
	}

#	if defined(ZT_WINDOWS)
	if (INVALID_SET_FILE_POINTER == SetFilePointer((HANDLE)file->win_file_handle, pos, NULL, FILE_BEGIN)) {
		zt_logCritical("zt_fileSetReadPos: SetFilePointer call failed (error %d)", GetLastError());
		return false;
	}

	file->win_read_pos = pos;
#	endif

	return true;
}

// ================================================================================================================================================================================================

bool zt_fileEof(ztFile *file)
{
	ZT_PROFILE_TOOLS("zt_fileEof");

	zt_returnValOnNull(file, true);

#	if defined(ZT_WINDOWS)
	return (file->win_read_pos >= file->size);
#	endif
}

// ================================================================================================================================================================================================

i32 zt_fileGetFullPath(ztFile *file, char *buffer, int buffer_size)
{
	zt_returnValOnNull(file, 0);
	return zt_fileGetFullPath(file->full_name, buffer, buffer_size);
}

// ================================================================================================================================================================================================

i32 zt_fileGetFileName(ztFile *file, char *buffer, int buffer_size)
{
	zt_returnValOnNull(file, 0);
	return zt_fileGetFileName(file->full_name, buffer, buffer_size);
}

// ================================================================================================================================================================================================

i32 zt_fileGetFileExt(ztFile *file, char *buffer, int buffer_size)
{
	zt_returnValOnNull(file, 0);
	return zt_fileGetFileExt(file->full_name, buffer, buffer_size);
}

// ================================================================================================================================================================================================

i32 zt_fileGetFullPath(const char *file_name, char *buffer, int buffer_size)
{
	ZT_PROFILE_TOOLS("zt_fileGetFullPath");

	if (file_name == nullptr) {
		return 0;
	}

	i32 pos_last_path = ztStrPosNotFound;

#	if defined(ZT_WINDOWS)
	i32 pos_last_path_one = zt_strFindLastPos(file_name, "/");
	i32 pos_last_path_two = zt_strFindLastPos(file_name, "\\");
	pos_last_path = zt_max(pos_last_path_one, pos_last_path_two);
#	endif

	if (pos_last_path == ztStrPosNotFound) {
		return 0;
	}

	zt_strCpy(buffer, buffer_size, file_name, pos_last_path);
	return pos_last_path;
}

// ================================================================================================================================================================================================

i32 zt_fileGetFileName(const char *file_name, char *buffer, int buffer_size)
{
	ZT_PROFILE_TOOLS("zt_fileGetFileName");

	if (file_name == nullptr) {
		return 0;
	}

	i32 pos_last_path = ztStrPosNotFound;

#	if defined(ZT_WINDOWS)
	i32 pos_last_path_one = zt_strFindLastPos(file_name, "/");
	i32 pos_last_path_two = zt_strFindLastPos(file_name, "\\");
	pos_last_path = zt_max(pos_last_path_one, pos_last_path_two);
#	endif

	if (pos_last_path == ztStrPosNotFound) {
		return 0;
	}

	i32 len = zt_strLen(file_name);

	zt_strCpy(buffer, buffer_size, file_name + pos_last_path + 1);
	return len - (pos_last_path + 1);
}

// ================================================================================================================================================================================================

i32 zt_fileGetFileExt(const char *file_name, char *buffer, int buffer_size)
{
	ZT_PROFILE_TOOLS("zt_fileGetFileExt");

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

// ================================================================================================================================================================================================

i32 zt_fileGetAppBin(char *buffer, int buffer_size)
{
	ZT_PROFILE_TOOLS("zt_fileGetAppBin");

	zt_returnValOnNull(buffer, 0);

#	if defined(ZT_WINDOWS)
	i32 len = GetModuleFileNameA(NULL, buffer, buffer_size);
	if (ERROR_INSUFFICIENT_BUFFER == GetLastError()) {
		zt_logCritical("zt_fileGetAppBin: GetModuleFileName returned ERROR_INSUFFICIENT_BUFFER for buffer size of %d", buffer_size);
	}

	return len;
#	endif
}

// ================================================================================================================================================================================================

i32 zt_fileGetAppPath(char *buffer, int buffer_size)
{
	ZT_PROFILE_TOOLS("zt_fileGetAppPath");

	zt_returnValOnNull(buffer, 0);

#	if defined(ZT_WINDOWS)
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
#	endif
}

// ================================================================================================================================================================================================

i32 zt_fileGetUserPath(char *buffer, int buffer_size, char *app_name)
{
	ZT_PROFILE_TOOLS("zt_fileGetUserPath");

	zt_returnValOnNull(buffer, 0);

#	if defined(ZT_WINDOWS)
	char temp[ztFileMaxPath] = { 0 };
	SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, temp);

	int len_path = zt_strLen(temp);
	int len_name = zt_strLen(app_name);

	zt_assert(len_path + len_name + 1 < ztFileMaxPath); // as big as ztFileMaxPath is, this should never happen
	
	temp[len_path] = '\\';
	zt_strCpy(temp + len_path + 1, ztFileMaxPath - (len_path + 1), app_name);

	return zt_strCpy(buffer, buffer_size, temp, len_path + len_name + 1);
#	endif
}

// ================================================================================================================================================================================================

i32 zt_fileGetCurrentPath(char *buffer, int buffer_size)
{
	ZT_PROFILE_TOOLS("zt_fileGetCurrentPath");

	zt_returnValOnNull(buffer, 0);

#	if defined(ZT_WINDOWS)
	return GetCurrentDirectoryA(buffer_size, buffer);
#	endif
}

// ================================================================================================================================================================================================

void zt_fileSetCurrentPath(const char *path)
{
	ZT_PROFILE_TOOLS("zt_fileSetCurrentPath");

#	if defined(ZT_WINDOWS)
	SetCurrentDirectoryA(path);
#	endif
}

// ================================================================================================================================================================================================

i32 zt_fileGetFileInOtherFileDirectory(char * buffer, int buffer_size, char *file_only, char *other_file_full_path)
{
	ZT_PROFILE_TOOLS("zt_fileGetFileInOtherFileDirectory");

	int posEnd = zt_max(zt_strFindLastPos(other_file_full_path, "/"), zt_strFindLastPos(other_file_full_path, "\\"));
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

// ================================================================================================================================================================================================

i32 zt_fileConcatFileToPath(char *buffer, int buffer_size, const char *path, const char *cfile)
{
	ZT_PROFILE_TOOLS("zt_fileConcatFileToPath");

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

// ================================================================================================================================================================================================

i32 zt_fileConcatFileToPath(char *buffer, int buffer_size, const char *path, int path_len, const char *cfile, int cfile_len)
{
	ZT_PROFILE_TOOLS("zt_fileConcatFileToPath");

	char *file = (char*)cfile;

	int dirs_back = 0;
	while (zt_strStartsWith(file, "..")) {
		dirs_back += 1;
		file += 3;
	}

	int dir_end = path_len;
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
	if (!zt_strEndsWith(path, path_len, ztFilePathSeparatorStr, zt_strLen(ztFilePathSeparatorStr)) && !zt_strStartsWith(file, ztFilePathSeparatorStr)) {
		zt_strCpy(buffer, buffer_size, ztFilePathSeparatorStr, 1);
		buffer += 1;
		buffer_size -= 1;
	}
	zt_strCpy(buffer, buffer_size, file, cfile_len - (int)(file - cfile));

	return buffer_size_orig - buffer_size;
}

// ================================================================================================================================================================================================

bool zt_fileExists(const char *file_name)
{
	ZT_PROFILE_TOOLS("zt_fileExists");

#	if defined(ZT_WINDOWS)
	OFSTRUCT ofs;

	HFILE hfile = OpenFile(file_name, &ofs, OF_READ);
	if (hfile == HFILE_ERROR) {
		return false;
	}
	CloseHandle((HANDLE)hfile);
	return true;
#	endif
}

// ================================================================================================================================================================================================

bool zt_fileDelete(const char *file_name)
{
	ZT_PROFILE_TOOLS("zt_fileDelete");

#	if defined(ZT_WINDOWS)
	if (DeleteFileA(file_name) == FALSE) {
		zt_logCritical("zt_fileDelete: unable to delete file '%s' (error: %d)", file_name, GetLastError());
		return false;
	}

	return true;
#	endif
}

// ================================================================================================================================================================================================

bool zt_fileCopy(const char *orig_file, const char *new_file)
{
	ZT_PROFILE_TOOLS("zt_fileCopy");

#	if defined(ZT_WINDOWS)
	if (CopyFileA(orig_file, new_file, TRUE) == FALSE) {
		zt_logCritical("zt_fileCopy: unable to copy file '%s' to '%s' (error: %d)", orig_file, new_file, GetLastError());
		return false;
	}

	return true;
#	endif
}

// ================================================================================================================================================================================================

bool zt_fileRename(const char *orig_file, const char *new_file)
{
	ZT_PROFILE_TOOLS("zt_fileRename");

#	if defined(ZT_WINDOWS)
	if (MoveFileA(orig_file, new_file) == FALSE) {
		zt_logCritical("zt_fileRename: unable to rename file '%s' to '%s' (error: %d)", orig_file, new_file, GetLastError());
		return false;
	}

	return true;
#	endif
}

// ================================================================================================================================================================================================

i32 zt_fileSize(const char *file_name)
{
	ZT_PROFILE_TOOLS("zt_fileSize");

#	if defined(ZT_WINDOWS)
	OFSTRUCT ofs;
	u32 style = OF_READ;

	HFILE hfile = OpenFile(file_name, &ofs, style);
	if (hfile == HFILE_ERROR) {
		return 0;
	}

	DWORD size = GetFileSize((HANDLE)hfile, NULL);
	CloseHandle((HANDLE)hfile);

	return (i32)size;
#	endif
}

// ================================================================================================================================================================================================

bool zt_fileModified(const char *file_name, i32 *year, i32 *month, i32 *day, i32 *hour, i32 *minute, i32 *second, i32 *ms)
{
	ZT_PROFILE_TOOLS("zt_fileModified");

#	if defined(ZT_WINDOWS)
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
#	endif
}

// ================================================================================================================================================================================================

bool zt_fileModified(const char *file_name, i64* date_time)
{
	ZT_PROFILE_TOOLS("zt_fileModified");

#	if defined(ZT_WINDOWS)
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
#	endif
}

// ================================================================================================================================================================================================

i32 zt_fileRead(ztFile *file, void *buffer, i32 buffer_size)
{
	ZT_PROFILE_TOOLS("zt_fileRead");

	zt_returnValOnNull(file, 0);
	zt_returnValOnNull(buffer, 0);

	if (buffer_size <= 0) {
		return 0;
	}

#	if defined(ZT_WINDOWS)
	DWORD bytes_read = 0;
	if (FALSE == ReadFile((HANDLE)file->win_file_handle, (LPVOID)buffer, buffer_size, &bytes_read, nullptr)) {
		zt_logCritical("zt_fileRead: failure reading file: '%s'  (error: %d)", file->full_name, GetLastError());
		return 0;
	}

	file->win_read_pos += bytes_read;
	return (i32)bytes_read;
#	endif
}

// ================================================================================================================================================================================================

i32 zt_fileWrite(ztFile *file, const void *buffer, i32 buffer_size)
{
	ZT_PROFILE_TOOLS("zt_fileWrite");

	zt_returnValOnNull(file, 0);
	zt_returnValOnNull(buffer, 0);

	if (buffer_size <= 0) {
		return 0;
	}

#	if defined(ZT_WINDOWS)
	DWORD bytes_written = 0;
	if (FALSE == WriteFile((HANDLE)file->win_file_handle, (LPVOID)buffer, buffer_size, &bytes_written, nullptr)) {
		zt_logCritical("zt_fileWrite: failure reading file: '%s'  (error: %d)", file->full_name, GetLastError());
		return 0;
	}

	file->win_read_pos += bytes_written;
	file->size += bytes_written;

	return (i32)bytes_written;
#	endif
}

// ================================================================================================================================================================================================

bool zt_fileWritef(ztFile *file, const char *format, ...)
{
	ZT_PROFILE_TOOLS("zt_fileWritef");

#	if defined(ZT_WINDOWS)
	va_list arg_ptr;
	va_start(arg_ptr, format);
	char buffer[1024 * 16];
	vsnprintf_s(buffer, zt_elementsOf(buffer), zt_elementsOf(buffer), format, arg_ptr);

	return zt_fileWrite(file, buffer);
#	endif
}

// ================================================================================================================================================================================================

void zt_fileFlush(ztFile *file)
{
	ZT_PROFILE_TOOLS("zt_fileFlush");

	zt_returnOnNull(file);

#	if defined(ZT_WINDOWS)
	FlushFileBuffers((HANDLE)file->win_file_handle);
#	endif
}

// ================================================================================================================================================================================================

void *zt_readEntireFile(const char *file_name, i32 *file_size, bool discard_utf_bom, ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_readEntireFile");

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

// ================================================================================================================================================================================================

i32 zt_readEntireFile(const char *file_name, void *buffer, i32 buffer_size, bool discard_utf_bom)
{
	ZT_PROFILE_TOOLS("zt_readEntireFile");

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

// ================================================================================================================================================================================================

i32 zt_writeEntireFile(const char *file_name, void *data, i32 data_size, ztMemoryArena *arena)
{
	ZT_PROFILE_TOOLS("zt_writeEntireFile");

	zt_returnValOnNull(file_name, 0);
	zt_returnValOnNull(data, 0);

	ztFile file;
	if (!zt_fileOpen(&file, file_name, ztFileOpenMethod_WriteOver, arena)) {
		return 0;
	}

	i32 bytes_written = zt_fileWrite(&file, data, data_size);
	if (bytes_written != data_size) {
		zt_logCritical("zt_fileWriteEntireFile: unable to write entire file '%s'.  sent %d bytes, wrote %d bytes", file_name, file.size, bytes_written);
	}

	zt_fileClose(&file);

	return bytes_written;
}

// ================================================================================================================================================================================================

bool zt_directoryExists(const char *dir)
{
	ZT_PROFILE_TOOLS("zt_directoryExists");

#	if defined(ZT_WINDOWS)
	DWORD attribs = GetFileAttributesA(dir);
	return (attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY));
#	else
#	error zt_directoryExists needs an implementation for this platform
#	endif
}

// ================================================================================================================================================================================================

bool zt_directoryMake(const char *dir)
{
	ZT_PROFILE_TOOLS("zt_directoryMake");

#	if defined(ZT_WINDOWS)
	return FALSE != CreateDirectoryA(dir, NULL);
#	else
#	error zt_directoryMake needs an implementation for this platform
#	endif
}

// ================================================================================================================================================================================================

bool zt_directoryDelete(const char *dir, bool force)
{
	ZT_PROFILE_TOOLS("zt_directoryDelete");

#	if defined(ZT_WINDOWS)
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
#	else
#	error zt_directoryMake needs an implementation for this platform
#	endif
}

// ================================================================================================================================================================================================

i32 zt_getDirectorySubs(const char *directory, char *buffer, i32 buffer_size, bool recursive)
{
	ZT_PROFILE_TOOLS("zt_getDirectorySubs");

#	if defined(ZT_WINDOWS)
	i32 buffer_used = 0;

	bool end_sep = zt_strEndsWith(directory, ztFilePathSeparatorStr);
	char *dir_full = (char *)zt_memAllocGlobal(ztFileMaxPath); // these are created on the heap due to stack overflow dangers with the recursion of this function
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
#	else
#	error zt_getDirectorySubs needs an implementation for this platform
#	endif
}

// ================================================================================================================================================================================================

i32 zt_getDirectoryFiles(const char *directory, char *buffer, i32 buffer_size, bool recursive)
{
	ZT_PROFILE_TOOLS("zt_getDirectoryFiles");

#	if defined(ZT_WINDOWS)
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
#	else
#	error zt_getDirectoryFiles needs an implementation for this platform
#	endif
}

// ================================================================================================================================================================================================

bool zt_directoryMonitor(ztDirectoryMonitor *dir_mon, const char *directory, bool recursive, i32 flags)
{
	ZT_PROFILE_TOOLS("zt_directoryMonitor");

	zt_returnValOnNull(dir_mon, false);
	zt_returnValOnNull(directory, false);

#	if defined(ZT_WINDOWS)
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
#	endif
}

// ================================================================================================================================================================================================

void zt_directoryStopMonitor(ztDirectoryMonitor *dir_mon)
{
	ZT_PROFILE_TOOLS("zt_directoryStopMonitor");

	zt_returnOnNull(dir_mon);

#	if defined(ZT_WINDOWS)
	if (dir_mon->file != NULL) {
		CancelIo((HANDLE)dir_mon->file);
		CloseHandle((HANDLE)dir_mon->file);
		CloseHandle((HANDLE)dir_mon->io);
		zt_memSet(dir_mon, zt_sizeof(ztDirectoryMonitor), 0);
	}
#	endif
}

// ================================================================================================================================================================================================

bool zt_directoryMonitorHasChanged(ztDirectoryMonitor *dir_mon)
{
	ZT_PROFILE_TOOLS("zt_directoryMonitorHasChanged");

	zt_returnValOnNull(dir_mon, false);

#	if defined(ZT_WINDOWS)
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
#	endif
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#if defined(ZT_WINDOWS)

unsigned int __stdcall _zt_threadProc(LPVOID param)
{
	ztThread *thread = (ztThread*)param;

	if (thread == nullptr || thread->thread == nullptr) {
		return 1;
	}

	int result = thread->thread(thread->thread_id, thread->thread_user_data, thread->exit_test, thread->exit_test_user_data);
	thread->running = false;
	return result;
}

// ================================================================================================================================================================================================

ztThread *zt_threadMake(ztThread_Func *thread_func, void *user_data, ztThreadExit_Func *exit_test, void *exit_test_user_data, ztThreadID *out_thread_id)
{
	ZT_PROFILE_TOOLS("zt_threadMake");

	ztThread *thread = zt_mallocStruct(ztThread);
	thread->thread              = thread_func;
	thread->thread_user_data    = user_data;
	thread->exit_test           = exit_test;
	thread->exit_test_user_data = exit_test_user_data;
	thread->running             = true;

	unsigned int thread_id      = 0;
	thread->thread_handle       = _beginthreadex(nullptr, 0, &_zt_threadProc, thread, 0, &thread_id);
	thread->thread_id           = (ztThreadID)thread_id;

	if (out_thread_id) {
		*out_thread_id = thread_id;
	}

	return thread;
}

// ================================================================================================================================================================================================

void zt_threadFree(ztThread *thread)
{
	ZT_PROFILE_TOOLS("zt_threadFree");

	if (thread == nullptr) {
		return;
	}

	if (thread->running) {
		zt_threadJoin(thread);
	}

	zt_free(thread);
}

// ================================================================================================================================================================================================

void zt_threadJoin(ztThread *thread)
{
	ZT_PROFILE_TOOLS("zt_threadJoin");

	zt_returnOnNull(thread);
	WaitForSingleObject((HANDLE)thread->thread_handle, INFINITE);
}

// ================================================================================================================================================================================================

bool zt_threadIsRunning(ztThread *thread)
{
	ZT_PROFILE_TOOLS("zt_threadIsRunning");

	zt_returnValOnNull(thread, false);
	return thread->running;
}

// ================================================================================================================================================================================================

ztThreadID zt_threadGetCurrentID()
{
	//ZT_PROFILE_TOOLS("zt_threadGetCurrentID"); called by profiling code, can't use here

	return GetCurrentThreadId();
}

// ================================================================================================================================================================================================

void zt_threadYield()
{
	ZT_PROFILE_TOOLS("zt_threadYield");

	zt_sleep(0);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztThreadMutex *zt_threadMutexMake()
{
	ZT_PROFILE_TOOLS("zt_threadMutexMake");

	ztThreadMutex *mutex = zt_mallocStruct(ztThreadMutex);
	InitializeCriticalSection(&mutex->cs);
	return mutex;
}

// ================================================================================================================================================================================================

void zt_threadMutexFree(ztThreadMutex *mutex)
{
	ZT_PROFILE_TOOLS("zt_threadMutexFree");

	if (mutex == nullptr) {
		return;
	}

	DeleteCriticalSection(&mutex->cs);
	zt_free(mutex);
}

// ================================================================================================================================================================================================

void zt_threadMutexLock(ztThreadMutex *mutex)
{
	ZT_PROFILE_TOOLS("zt_threadMutexLock");

	zt_returnOnNull(mutex);
	EnterCriticalSection(&mutex->cs);
}

// ================================================================================================================================================================================================

void zt_threadMutexUnlock(ztThreadMutex *mutex)
{
	ZT_PROFILE_TOOLS("zt_threadMutexUnlock");

	zt_returnOnNull(mutex);
	LeaveCriticalSection(&mutex->cs);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztThreadMonitor *zt_threadMonitorMake()
{
	ZT_PROFILE_TOOLS("zt_threadMonitorMake");

	ztThreadMonitor *monitor = zt_mallocStruct(ztThreadMonitor);
	monitor->event_handle = (i32)CreateEvent(NULL, TRUE, FALSE, NULL);
	return monitor;
}

// ================================================================================================================================================================================================

void zt_threadMonitorFree(ztThreadMonitor *monitor)
{
	ZT_PROFILE_TOOLS("zt_threadMonitorFree");

	if (monitor == nullptr) {
		return;
	}

	CloseHandle((HANDLE)monitor->event_handle);
	zt_free(monitor);
}

// ================================================================================================================================================================================================

void zt_threadMonitorWaitForSignal(ztThreadMonitor *monitor)
{
	ZT_PROFILE_TOOLS("zt_threadMonitorWaitForSignal");

	zt_returnOnNull(monitor);
	WaitForSingleObject((HANDLE)monitor->event_handle, INFINITE);
}

// ================================================================================================================================================================================================

void zt_threadMonitorTriggerSignal(ztThreadMonitor *monitor)
{
	ZT_PROFILE_TOOLS("zt_threadMonitorTriggerSignal");

	zt_returnOnNull(monitor);
	SetEvent((HANDLE)monitor->event_handle);
}

// ================================================================================================================================================================================================

void zt_threadMonitorReset(ztThreadMonitor *monitor)
{
	ZT_PROFILE_TOOLS("zt_threadMonitorReset");

	zt_returnOnNull(monitor);
	ResetEvent((HANDLE)monitor->event_handle);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

i32 zt_atomicIntInc(ztAtomicInt *atomic_int)
{
	ZT_PROFILE_TOOLS("zt_atomicIntInc");

	return InterlockedIncrement(atomic_int);
}

// ================================================================================================================================================================================================

i32 zt_atomicIncDec(ztAtomicInt *atomic_int)
{
	ZT_PROFILE_TOOLS("zt_atomicIncDec");

	return InterlockedDecrement(atomic_int);
}

// ================================================================================================================================================================================================

i32 zt_atomicIntSet(ztAtomicInt *atomic_int, i32 value)
{
	ZT_PROFILE_TOOLS("zt_atomicIntSet");

	return InterlockedExchange(atomic_int, value);
}

// ================================================================================================================================================================================================

i32 zt_atomicIntGet(ztAtomicInt *atomic_int)
{
	ZT_PROFILE_TOOLS("zt_atomicIntGet");

	return InterlockedExchange(atomic_int, *atomic_int);
}

// ================================================================================================================================================================================================

i32 zt_atomicIntAnd(ztAtomicInt *atomic_int, i32 and_val)
{
	ZT_PROFILE_TOOLS("zt_atomicIntAnd");

	return InterlockedAnd(atomic_int, and_val);
}

// ================================================================================================================================================================================================

i32 zt_atomicIntOr(ztAtomicInt *atomic_int, i32 or_val)
{
	ZT_PROFILE_TOOLS("zt_atomicIntOr");

	return InterlockedOr(atomic_int, or_val);
}

// ================================================================================================================================================================================================

i32 zt_atomicIntXor(ztAtomicInt *atomic_int, i32 xor_val)
{
	ZT_PROFILE_TOOLS("zt_atomicIntXor");

	return InterlockedXor(atomic_int, xor_val);
}

// ================================================================================================================================================================================================

bool zt_atomicBoolSet(ztAtomicBool *atomic_bool, bool value)
{
	ZT_PROFILE_TOOLS("zt_atomicBoolSet");

	return InterlockedExchange(atomic_bool, value ? 1 : 0) != 0;
}

// ================================================================================================================================================================================================

bool zt_atomicBoolGet(ztAtomicBool *atomic_bool)
{
	ZT_PROFILE_TOOLS("zt_atomicBoolGet");

	return InterlockedExchange(atomic_bool, *atomic_bool) != 0;
}

// ================================================================================================================================================================================================

bool zt_atomicBoolToggle(ztAtomicBool *atomic_bool)
{
	ZT_PROFILE_TOOLS("zt_atomicBoolToggle");

	return zt_atomicBoolSet(atomic_bool, !zt_atomicBoolGet(atomic_bool));
}

#endif // ZT_WINDOWS

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifdef ZT_WINDOWS

i32 zt_displayGetDetails(ztDisplay *display, i32 display_count)
{
	struct DisplayInfo
	{
		ztDisplay *display;
		i32        display_count;
		i32        index;
	};

	struct local
	{
		static BOOL CALLBACK monitorEnumProc(HMONITOR h_monitor, HDC hdc_monitor, LPRECT rect, LPARAM data)
		{
			DisplayInfo *display_info = (DisplayInfo*)data;

			zt_assertReturnValOnFail(display_info->index < display_info->display_count, FALSE);

			ztDisplay *display = &display_info->display[display_info->index++];

			MONITORINFOEXA monitor_info;
			zt_memSet(&monitor_info, zt_sizeof(monitor_info), 0);
			monitor_info.cbSize = zt_sizeof(monitor_info);

			if (FALSE == GetMonitorInfoA(h_monitor, &monitor_info)) {
				zt_logCritical("Unable to get monitor information (monitor index: %d)", --display_info->index);
				return FALSE;
			}

			display->index       = display_info->index - 1;
			display->screen_area = zt_vec4i(monitor_info.rcMonitor.left, monitor_info.rcMonitor.top, monitor_info.rcMonitor.right - monitor_info.rcMonitor.left, monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top);
			display->work_area   = zt_vec4i(monitor_info.rcWork.left, monitor_info.rcWork.top, monitor_info.rcWork.right - monitor_info.rcWork.left, monitor_info.rcWork.bottom - monitor_info.rcWork.top);
			display->primary     = zt_bitIsSet(monitor_info.dwFlags, MONITORINFOF_PRIMARY);
			display->platform_id = (i64)h_monitor;

			zt_strCpy(display->name, zt_elementsOf(display->name), monitor_info.szDevice, zt_elementsOf(monitor_info.szDevice));

			return TRUE;
		}
	};

	DisplayInfo display_info = {display, display_count, 0};

	if (FALSE == EnumDisplayMonitors(NULL, NULL, local::monitorEnumProc, (LPARAM)&display_info)) {
		return display_info.index;
	}

	return display_info.index;
}

#endif // ZT_WINDOWS

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ztInternal i32 _zt_serial_header[5] = { 0x7e751c, 0xba7e20, 0x3d8601, 0x41569b, 0xac4d6d };
ztInternal const int _zt_mod_adler = 65521;

// ================================================================================================================================================================================================

// adler checksum... we aren't going for national security here, just general corruption detection

static int byte_idx = 0;

ztInternal ztInline void _zt_serialAddToChecksum(ztSerial *serial, byte data)
{
	ZT_PROFILE_TOOLS("_zt_serialAddToChecksum");

	serial->_checksum1 = (serial->_checksum1 + data) % _zt_mod_adler;
	serial->_checksum2 = (serial->_checksum2 + serial->_checksum1) % _zt_mod_adler;
}

// ================================================================================================================================================================================================

ztInternal ztInline void _zt_serialAddToChecksum(ztSerial *serial, void *data, i32 data_len)
{
	ZT_PROFILE_TOOLS("_zt_serialAddToChecksum");

	zt_fiz(data_len) {
		serial->_checksum1 = (serial->_checksum1 + ((byte*)data)[i]) % _zt_mod_adler;
		serial->_checksum2 = (serial->_checksum2 + serial->_checksum1) % _zt_mod_adler;
	}
}

// ================================================================================================================================================================================================

ztInternal ztInline bool _zt_validateChecksum(ztSerial *serial)
{
	ZT_PROFILE_TOOLS("_zt_validateChecksum");

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

// ================================================================================================================================================================================================

ztInternal ztInline bool _zt_writeByte(ztSerial *serial, byte b)
{
	ZT_PROFILE_TOOLS("_zt_writeByte");

	if (serial->mode != ztSerialMode_Writing) {
		return false;
	}

	_zt_serialAddToChecksum(serial, b);

	return 1 == zt_fileWrite(&serial->file, &b, 1);
}

// ================================================================================================================================================================================================

ztInternal ztInline bool _zt_writeData(ztSerial *serial, ztSerialEntryType_Enum entry_type, void *data, int data_size)
{
	ZT_PROFILE_TOOLS("_zt_writeData");

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

// ================================================================================================================================================================================================

ztInternal ztInline i32 _zt_readData(ztSerial *serial, void *data, i32 data_size)
{
	ZT_PROFILE_TOOLS("_zt_readData");

	if (serial->file_data) {
		if (serial->file_data_size < data_size)
			return 0;

		if (data_size == 1) {
			*((byte*)data) = *((byte*)serial->file_data);
		}
		else {
			zt_memCpy(data, data_size, serial->file_data, data_size);
		}

		serial->file_data = ((byte*)serial->file_data) + data_size;
		serial->file_data_size -= data_size;
		return data_size;
	}
	else {
		return zt_fileRead(&serial->file, data, data_size);
	}
}

// ================================================================================================================================================================================================

ztInternal ztInline bool _zt_readByte(ztSerial *serial, byte *byte)
{
	ZT_PROFILE_TOOLS("_zt_readByte");

	if (serial->mode != ztSerialMode_Reading) {
		return false;
	}

	return _zt_readData(serial, byte, 1) == 1;
}

// ================================================================================================================================================================================================

ztInternal ztInline bool _zt_readData(ztSerial *serial, ztSerialEntryType_Enum expected_type, void *data, int data_size)
{
	ZT_PROFILE_TOOLS("_zt_readData");

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

		if (_zt_readData(serial, data, data_size) != data_size) {
			return false;
		}

		byte data_end = ztSerialEntryType_Unknown;
		if (_zt_readData(serial, &data_end, 1) != 1) {
			return false;
		}

		byte next_entry = 0;
		if (_zt_readData(serial, &next_entry, 1) != 1) {
			return false;
		}

		serial->next_entry = next_entry;
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

// ================================================================================================================================================================================================

bool _zt_serialMakeWriterDoHeader(ztSerial *serial, const char *identifier, i32 version)
{
	ZT_PROFILE_TOOLS("_zt_serialMakeWriterDoHeader");

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

// ================================================================================================================================================================================================

bool _zt_serialMakeReaderDoHeader(ztSerial *serial, const char *identifier)
{
	ZT_PROFILE_TOOLS("_zt_serialMakeReaderDoHeader");

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

// ================================================================================================================================================================================================

bool zt_serialMakeWriter(ztSerial *serial, const char *file_name, const char *identifier, i32 version)
{
	ZT_PROFILE_TOOLS("zt_serialMakeWriter");

	zt_returnValOnNull(serial, false);
	zt_returnValOnNull(file_name, false);
	zt_returnValOnNull(identifier, false);

	zt_memSet(serial, zt_sizeof(ztSerial), 0);

	if (!zt_fileOpen(&serial->file, file_name, ztFileOpenMethod_WriteOver))
		return false;

	serial->close_file = true;

	return _zt_serialMakeWriterDoHeader(serial, identifier, version);
}

// ================================================================================================================================================================================================

bool zt_serialMakeWriter(ztSerial *serial, ztFile *file, const char *identifier, i32 version)
{
	ZT_PROFILE_TOOLS("zt_serialMakeWriter");

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

// ================================================================================================================================================================================================

bool zt_serialMakeReader(ztSerial *serial, const char *file_name, const char *identifier)
{
	ZT_PROFILE_TOOLS("zt_serialMakeReader");

	zt_returnValOnNull(serial, false);
	zt_returnValOnNull(file_name, false);
	zt_returnValOnNull(identifier, false);

	zt_memSet(serial, zt_sizeof(ztSerial), 0);

	if (!zt_fileOpen(&serial->file, file_name, ztFileOpenMethod_ReadOnly))
		return false;

	serial->close_file = true;

	return _zt_serialMakeReaderDoHeader(serial, identifier);
}

// ================================================================================================================================================================================================

bool zt_serialMakeReader(ztSerial *serial, void *data, i32 data_size, const char *identifier)
{
	ZT_PROFILE_TOOLS("zt_serialMakeReader");

	zt_returnValOnNull(serial, false);
	zt_returnValOnNull(data, false);
	zt_returnValOnNull(identifier, false);

	zt_memSet(serial, zt_sizeof(ztSerial), 0);

	serial->close_file = false;
	serial->file_data = data;
	serial->file_data_size = data_size;

	return _zt_serialMakeReaderDoHeader(serial, identifier);
}

// ================================================================================================================================================================================================

bool zt_serialMakeReader(ztSerial *serial, ztFile *file, const char *identifier)
{
	ZT_PROFILE_TOOLS("zt_serialMakeReader");

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

// ================================================================================================================================================================================================

void zt_serialClose(ztSerial *serial)
{
	ZT_PROFILE_TOOLS("zt_serialClose");

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

// ================================================================================================================================================================================================

bool zt_serialGroupPush(ztSerial *serial)
{
	ZT_PROFILE_TOOLS("zt_serialGroupPush");

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

// ================================================================================================================================================================================================

bool zt_serialGroupPop(ztSerial *serial)
{
	ZT_PROFILE_TOOLS("zt_serialGroupPop");

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

// ================================================================================================================================================================================================

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
bool zt_serialWrite(ztSerial *serial, ztGuid guid) { if (!zt_serialWrite(serial, guid.guid[0])) return false; if (!zt_serialWrite(serial, guid.guid[1])) return false; return true; }
bool zt_serialWrite(ztSerial *serial, ztVec2  vec) { zt_fize(vec.values) { if (!zt_serialWrite(serial, vec.values[i])) return false; } return true; }
bool zt_serialWrite(ztSerial *serial, ztVec3  vec) { zt_fize(vec.values) { if (!zt_serialWrite(serial, vec.values[i])) return false; } return true; }
bool zt_serialWrite(ztSerial *serial, ztVec4  vec) { zt_fize(vec.values) { if (!zt_serialWrite(serial, vec.values[i])) return false; } return true; }
bool zt_serialWrite(ztSerial *serial, ztVec2i vec) { zt_fize(vec.values) { if (!zt_serialWrite(serial, vec.values[i])) return false; } return true; }
bool zt_serialWrite(ztSerial *serial, ztVec3i vec) { zt_fize(vec.values) { if (!zt_serialWrite(serial, vec.values[i])) return false; } return true; }
bool zt_serialWrite(ztSerial *serial, ztMat4 mat)  { zt_fize(mat.values) { if (!zt_serialWrite(serial, mat.values[i])) return false; } return true; }
bool zt_serialWrite(ztSerial *serial, ztQuat quat)  { zt_fize(quat.values) { if (!zt_serialWrite(serial, quat.values[i])) return false; } return true; }

// ================================================================================================================================================================================================

bool zt_serialWrite(ztSerial *serial, ztVariant *variant)
{
	ZT_PROFILE_TOOLS("zt_serialWrite");

	if (!zt_serialWrite(serial, (i32)variant->type)) {
		return false;
	}
	
	switch (variant->type)
	{
		case ztVariant_i8    : if (!zt_serialWrite(serial, variant->v_i8 )) { return false; } break;
		case ztVariant_i16   : if (!zt_serialWrite(serial, variant->v_i16)) { return false; } break;
		case ztVariant_i32   : if (!zt_serialWrite(serial, variant->v_i32)) { return false; } break;
		case ztVariant_i64   : if (!zt_serialWrite(serial, variant->v_i64)) { return false; } break;
		case ztVariant_u8    : if (!zt_serialWrite(serial, variant->v_u8 )) { return false; } break;
		case ztVariant_u16   : if (!zt_serialWrite(serial, variant->v_u16)) { return false; } break;
		case ztVariant_u32   : if (!zt_serialWrite(serial, variant->v_u32)) { return false; } break;
		case ztVariant_u64   : if (!zt_serialWrite(serial, variant->v_u64)) { return false; } break;
		case ztVariant_r32   : if (!zt_serialWrite(serial, variant->v_r32)) { return false; } break;
		case ztVariant_r64   : if (!zt_serialWrite(serial, variant->v_r64)) { return false; } break;
		case ztVariant_voidp : zt_assert(false); break;
		case ztVariant_vec2  : if (!zt_serialWrite(serial, variant->v_vec2)) { return false; } break;
		case ztVariant_vec3  : if (!zt_serialWrite(serial, variant->v_vec3)) { return false; } break;
		case ztVariant_vec4  : if (!zt_serialWrite(serial, variant->v_vec4)) { return false; } break;
		case ztVariant_mat4  : if (!zt_serialWrite(serial, variant->v_mat4)) { return false; } break;
		case ztVariant_quat  : if (!zt_serialWrite(serial, variant->v_quat)) { return false; } break;
		case ztVariant_bool  : if (!zt_serialWrite(serial, variant->v_bool)) { return false; } break;
		default: zt_assert(false);
	}

	return true;
}

// ================================================================================================================================================================================================

bool zt_serialWrite(ztSerial *serial, const char *value, i32 value_len)
{
	ZT_PROFILE_TOOLS("zt_serialWrite");

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

// ================================================================================================================================================================================================

bool zt_serialWrite(ztSerial *serial, void *value, i32 value_len)
{
	ZT_PROFILE_TOOLS("zt_serialWrite");

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

// ================================================================================================================================================================================================

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
bool zt_serialRead(ztSerial *serial, ztGuid *guid) { if (!zt_serialRead(serial, &guid->guid[0])) return false; if (!zt_serialRead(serial, &guid->guid[1])) return false; return true; }
bool zt_serialRead(ztSerial *serial, ztVec2  *vec) { zt_fize(vec->values) { if (!zt_serialRead(serial, &vec->values[i])) return false; } return true; }
bool zt_serialRead(ztSerial *serial, ztVec3  *vec) { zt_fize(vec->values) { if (!zt_serialRead(serial, &vec->values[i])) return false; } return true; }
bool zt_serialRead(ztSerial *serial, ztVec4  *vec) { zt_fize(vec->values) { if (!zt_serialRead(serial, &vec->values[i])) return false; } return true; }
bool zt_serialRead(ztSerial *serial, ztVec2i *vec) { zt_fize(vec->values) { if (!zt_serialRead(serial, &vec->values[i])) return false; } return true; }
bool zt_serialRead(ztSerial *serial, ztVec3i *vec) { zt_fize(vec->values) { if (!zt_serialRead(serial, &vec->values[i])) return false; } return true; }
bool zt_serialRead(ztSerial *serial, ztMat4 *mat) { zt_fize(mat->values) { if (!zt_serialRead(serial, &mat->values[i])) return false; } return true; }
bool zt_serialRead(ztSerial *serial, ztQuat *quat) { zt_fize(quat->values) { if (!zt_serialRead(serial, &quat->values[i])) return false; } return true; }

// ================================================================================================================================================================================================

bool zt_serialRead(ztSerial *serial, ztVariant *variant)
{
	ZT_PROFILE_TOOLS("zt_serialRead");

	i32 type = 0;
	if (!zt_serialRead(serial, &type)) {
		return false;
	}
	variant->type = (ztVariant_Enum)type;

	switch (variant->type)
	{
		case ztVariant_i8    : if (!zt_serialRead(serial, &variant->v_i8  )) { return false; } break;
		case ztVariant_i16   : if (!zt_serialRead(serial, &variant->v_i16 )) { return false; } break;
		case ztVariant_i32   : if (!zt_serialRead(serial, &variant->v_i32 )) { return false; } break;
		case ztVariant_i64   : if (!zt_serialRead(serial, &variant->v_i64 )) { return false; } break;
		case ztVariant_u8    : if (!zt_serialRead(serial, &variant->v_u8  )) { return false; } break;
		case ztVariant_u16   : if (!zt_serialRead(serial, &variant->v_u16 )) { return false; } break;
		case ztVariant_u32   : if (!zt_serialRead(serial, &variant->v_u32 )) { return false; } break;
		case ztVariant_u64   : if (!zt_serialRead(serial, &variant->v_u64 )) { return false; } break;
		case ztVariant_r32   : if (!zt_serialRead(serial, &variant->v_r32 )) { return false; } break;
		case ztVariant_r64   : if (!zt_serialRead(serial, &variant->v_r64 )) { return false; } break;
		case ztVariant_voidp : zt_assert(false); break;
		case ztVariant_vec2  : if (!zt_serialRead(serial, &variant->v_vec2)) { return false; } break;
		case ztVariant_vec3  : if (!zt_serialRead(serial, &variant->v_vec3)) { return false; } break;
		case ztVariant_vec4  : if (!zt_serialRead(serial, &variant->v_vec4)) { return false; } break;
		case ztVariant_mat4  : if (!zt_serialRead(serial, &variant->v_mat4)) { return false; } break;
		case ztVariant_quat  : if (!zt_serialRead(serial, &variant->v_quat)) { return false; } break;
		case ztVariant_bool  : if (!zt_serialRead(serial, &variant->v_bool)) { return false; } break;
		default: zt_assert(false);
	}

	return true;
}

// ================================================================================================================================================================================================

bool zt_serialRead(ztSerial *serial, char *value, i32 value_len, i32 *read_len)
{
	ZT_PROFILE_TOOLS("zt_serialRead");

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

// ================================================================================================================================================================================================

bool zt_serialRead(ztSerial *serial, void *value, i32 value_len, i32 *read_len)
{
	ZT_PROFILE_TOOLS("zt_serialRead");

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


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

int zt_base64Encode(byte *data_to_encode, int data_len, char *encoded_data_buffer, int encoded_data_buffer_size)
{
#	define b64_encode(B) (B < 26 ? ('A' + B) : (B < 52 ? ('a' + (B - 26)) : (B < 62 ? ('0' + (B - 52)) : (B == 62 ? '+' : '/'))))

	zt_returnValOnNull(data_to_encode, 0);
	zt_returnValOnNull(encoded_data_buffer, 0);
	zt_assertReturnValOnFail(encoded_data_buffer_size >= zt_base64GetEncodedSize(data_len), 0);

	char *result = encoded_data_buffer;

	for (int i = 0; i < data_len; i += 3) {
		byte b1 = data_to_encode[i];
		byte b2 = (i + 1 < data_len ? data_to_encode[i + 1] : 0);
		byte b3 = (i + 2 < data_len ? data_to_encode[i + 2] : 0);

		byte e1 = b1 >> 2;
		byte e2 = ((b1 & 0x3) << 4) | (b2 >> 4);
		byte e3 = ((b2 & 0xf) << 2) | (b3 >> 6);
		byte e4 = b3 & 0x3f;

		*result++ = b64_encode(e1);
		*result++ = b64_encode(e2);
		*result++ = (i + 1 < data_len ? b64_encode(e3) : '=');
		*result++ = (i + 2 < data_len ? b64_encode(e4) : '=');
	}

	*result++ = '\0';

	return (int)(result - encoded_data_buffer);

#	undef b64_encode
}

// ================================================================================================================================================================================================

int zt_base64Decode(char *data_to_decode, int data_len, byte *decoded_data_buffer, int decoded_data_buffer_size)
{
#	define b64_decode(C) (C >= 'A' && C <= 'Z') ? (C - 'A') : ((C >= 'a' && C <= 'z') ? (C - 'a' + 26) : ((C >= '0' && C <= '9') ? (C - '0' + 52) : ((C == '+' ? 62 : 63))))
#	define b64_find_next_char(VAR) \
		while (true) { \
			if (i >= data_len) { \
				VAR = 'A'; break; \
			} else if (data_to_decode[i] == '\n' || data_to_decode[i] == '\r' || data_to_decode[i] == '\t' || data_to_decode[i] == ' ') { \
				++i; \
			} else { \
				VAR = data_to_decode[i]; ++i; break; \
			}\
		}

	while (data_to_decode[data_len - 1] == '\0') {
		data_len -= 1;
	}

	byte *result = decoded_data_buffer;

	int i = 0;
	char c1, c2, c3, c4;
	while (i < data_len) {
		b64_find_next_char(c1);
		b64_find_next_char(c2);
		b64_find_next_char(c3);
		b64_find_next_char(c4);

		byte u1 = b64_decode(c1);
		byte u2 = b64_decode(c2);
		byte u3 = b64_decode(c3);
		byte u4 = b64_decode(c4);

		*result++ = (u1 << 2) | (u2 >> 4);

		if (c3 != '=') {
			*result++ = ((u2 & 0xf) << 4) | (u3 >> 2);
		}
		else break;

		if (c4 != '=') {
			*result++ = ((u3 & 0x3) << 6) | u4;
		}
		else break;
	}

	return (int)(result - decoded_data_buffer);

#	undef b64_find_next_char
#	undef b64_decode
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// this was adapted from: http://en.literateprograms.org/Mersenne_twister_(C)

#define ztRandom_MT_IA           397
#define ztRandom_MT_IB           (ztRandom_MTLen - ztRandom_MT_IA)
#define ztRandom_UpperMask       0x80000000
#define ztRandom_LowerMask       0x7fffffff
#define ztRandom_MatrixA         0x9908b0df
#define ztRandom_Twist(b,i,j)    ((b)[i] & ztRandom_UpperMask) | ((b)[j] & ztRandom_LowerMask)
#define ztRandom_Magic(s)        (((s)&1) * ztRandom_MatrixA)

// ================================================================================================================================================================================================

void zt_randomInit(ztRandom *random, i32 seed)
{
	ZT_PROFILE_TOOLS("zt_randomInit");

	srand(seed);
	for (int i = 0; i < ztRandom_MTLen; ++i) {
		random->mt_buffer[i] = rand();
	}
	random->mt_idx = 0;
	random->seed = seed;
}

// ================================================================================================================================================================================================

i32 zt_randomInt(ztRandom *random, i32 min, i32 max)
{
	ZT_PROFILE_TOOLS("zt_randomInt");

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

	return (zt_abs(rv) % (max - min)) + min;
}

// ================================================================================================================================================================================================

r32 zt_randomVal(ztRandom *random)
{
	ZT_PROFILE_TOOLS("zt_randomVal");

	return zt_randomInt(random, 0, 10001) / 10000.f;
}

// ================================================================================================================================================================================================

r32 zt_randomVal(ztRandom *random, r32 min, r32 max)
{
	ZT_PROFILE_TOOLS("zt_randomVal");

	return zt_randomVal(random) * (max - min) + min;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// OpenSimplex noise implementation from public domain source found here :
// https ://github.com/smcameron/open-simplex-noise-in-c/blob/master/open-simplex-noise.c

#define ZTSN_STRETCH_CONSTANT_2D (-0.211324865405187)    // (1 / sqrt(2 + 1) - 1 ) / 2;
#define ZTSN_SQUISH_CONSTANT_2D  (0.366025403784439)     // (sqrt(2 + 1) -1) / 2;
#define ZTSN_STRETCH_CONSTANT_3D (-1.0 / 6.0)            // (1 / sqrt(3 + 1) - 1) / 3;
#define ZTSN_SQUISH_CONSTANT_3D  (1.0 / 3.0)             // (sqrt(3+1)-1)/3;
#define ZTSN_STRETCH_CONSTANT_4D (-0.138196601125011)    // (1 / sqrt(4 + 1) - 1) / 4;
#define ZTSN_SQUISH_CONSTANT_4D  (0.309016994374947)     // (sqrt(4 + 1) - 1) / 4;

#define ZTSN_NORM_CONSTANT_2D (47.0)
#define ZTSN_NORM_CONSTANT_3D (103.0)
#define ZTSN_NORM_CONSTANT_4D (30.0)

#define ZTSN_DEFAULT_SEED (0LL)

ztInternal const i8 _zt_gradients_2d[] = {
	5, 2, 2, 5,
	-5, 2, -2, 5,
	5, -2, 2, -5,
	-5, -2, -2, -5,
};

/*
* Gradients for 3D. They approximate the directions to the
* vertices of a rhombicuboctahedron from the center, skewed so
* that the triangular and square facets can be inscribed inside
* circles of the same radius.
*/
ztInternal const signed char _zt_gradients_3d[] = {
	-11, 4, 4, -4, 11, 4, -4, 4, 11,
	11, 4, 4, 4, 11, 4, 4, 4, 11,
	-11, -4, 4, -4, -11, 4, -4, -4, 11,
	11, -4, 4, 4, -11, 4, 4, -4, 11,
	-11, 4, -4, -4, 11, -4, -4, 4, -11,
	11, 4, -4, 4, 11, -4, 4, 4, -11,
	-11, -4, -4, -4, -11, -4, -4, -4, -11,
	11, -4, -4, 4, -11, -4, 4, -4, -11,
};

/*
* Gradients for 4D. They approximate the directions to the
* vertices of a disprismatotesseractihexadecachoron from the center,
* skewed so that the tetrahedral and cubic facets can be inscribed inside
* spheres of the same radius.
*/
ztInternal const signed char _zt_gradients_4d[] = {
	3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3,
	-3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3,
	3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3,
	-3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3,
	3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3,
	-3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3,
	3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3,
	-3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3,
	3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3,
	-3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3,
	3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3,
	-3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3,
	3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3,
	-3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3,
	3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3,
	-3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3,
};

// ================================================================================================================================================================================================

ztSimplexNoise *zt_simplexNoiseMake(i64 seed)
{
	ZT_PROFILE_TOOLS("zt_simplexNoiseMake");

	ztSimplexNoise *noise = zt_mallocStruct(ztSimplexNoise);

	int nperm = 256;
	int ngrad = 256;

	noise->perm = zt_mallocStructArray(i16, nperm);
	noise->perm_grad_index_3d = zt_mallocStructArray(i16, ngrad);

	i16 source[256];
	zt_fiz(256) {
		source[i] = (i16)i;
	}

	seed = seed * 6364136223846793005LL + 1442695040888963407LL;
	seed = seed * 6364136223846793005LL + 1442695040888963407LL;
	seed = seed * 6364136223846793005LL + 1442695040888963407LL;

	zt_fizr(255) {
		seed = seed * 6364136223846793005LL + 1442695040888963407LL;
		int r = (int)((seed + 31) % (i + 1));
		if (r < 0) r += (i + 1);
		noise->perm[i] = source[r];
		noise->perm_grad_index_3d[i] = (i16)((noise->perm[i] % (zt_elementsOf(_zt_gradients_3d) / 3)) * 3);
		source[r] = source[i];
	}

	return noise;
}

// ================================================================================================================================================================================================

void zt_simplexNoiseFree(ztSimplexNoise *noise)
{
	ZT_PROFILE_TOOLS("zt_simplexNoiseFree");

	if (noise == nullptr) {
		return;
	}

	zt_free(noise->perm);
	zt_free(noise->perm_grad_index_3d);
	zt_free(noise);
}

// ================================================================================================================================================================================================

ztInternal ztInline int zt_fastFloor(r64 x)
{
	int xi = (int)x;
	return x < xi ? xi - 1 : xi;
}

r32 zt_simplexNoise2D(ztSimplexNoise *noise, r32 x, r32 y)
{
	ZT_PROFILE_TOOLS("zt_simplexNoise2D");

#	define extrapolate2(noise, xsb, ysb, dx, dy) \
		(_zt_gradients_2d[noise->perm[(noise->perm[xsb & 0xFF] + ysb) & 0xFF] & 0x0E] * dx + _zt_gradients_2d[(noise->perm[(noise->perm[xsb & 0xFF] + ysb) & 0xFF] & 0x0E) + 1] * dy)

	zt_returnValOnNull(noise, 0);

	//Place input coordinates onto grid.
	r64 stretchOffset = (x + y) * ZTSN_STRETCH_CONSTANT_2D;
	r64 xs = x + stretchOffset;
	r64 ys = y + stretchOffset;

	//Floor to get grid coordinates of rhombus (stretched square) super-cell origin.
	int xsb = zt_fastFloor(xs);
	int ysb = zt_fastFloor(ys);

	//Skew out to get actual coordinates of rhombus origin. We'll need these later.
	r64 squishOffset = (xsb + ysb) * ZTSN_SQUISH_CONSTANT_2D;
	r64 xb = xsb + squishOffset;
	r64 yb = ysb + squishOffset;

	//Compute grid coordinates relative to rhombus origin.
	r64 xins = xs - xsb;
	r64 yins = ys - ysb;

	//Sum those together to get a value that determines which region we're in.
	r64 inSum = xins + yins;

	//Positions relative to origin point.
	r64 dx0 = x - xb;
	r64 dy0 = y - yb;

	//We'll be defining these inside the next block and using them afterwards.
	r64 dx_ext, dy_ext;
	int xsv_ext, ysv_ext;

	r64 value = 0;

	//Contribution (1,0)
	r64 dx1 = dx0 - 1 - ZTSN_SQUISH_CONSTANT_2D;
	r64 dy1 = dy0 - 0 - ZTSN_SQUISH_CONSTANT_2D;
	r64 attn1 = 2 - dx1 * dx1 - dy1 * dy1;
	if (attn1 > 0) {
		attn1 *= attn1;
		value += attn1 * attn1 * extrapolate2(noise, xsb + 1, ysb + 0, dx1, dy1);
	}

	//Contribution (0,1)
	r64 dx2 = dx0 - 0 - ZTSN_SQUISH_CONSTANT_2D;
	r64 dy2 = dy0 - 1 - ZTSN_SQUISH_CONSTANT_2D;
	r64 attn2 = 2 - dx2 * dx2 - dy2 * dy2;
	if (attn2 > 0) {
		attn2 *= attn2;
		value += attn2 * attn2 * extrapolate2(noise, xsb + 0, ysb + 1, dx2, dy2);
	}

	if (inSum <= 1) { //We're inside the triangle (2-Simplex) at (0,0)
		r64 zins = 1 - inSum;
		if (zins > xins || zins > yins) { //(0,0) is one of the closest two triangular vertices
			if (xins > yins) {
				xsv_ext = xsb + 1;
				ysv_ext = ysb - 1;
				dx_ext = dx0 - 1;
				dy_ext = dy0 + 1;
			}
			else {
				xsv_ext = xsb - 1;
				ysv_ext = ysb + 1;
				dx_ext = dx0 + 1;
				dy_ext = dy0 - 1;
			}
		}
		else { //(1,0) and (0,1) are the closest two vertices.
			xsv_ext = xsb + 1;
			ysv_ext = ysb + 1;
			dx_ext = dx0 - 1 - 2 * ZTSN_SQUISH_CONSTANT_2D;
			dy_ext = dy0 - 1 - 2 * ZTSN_SQUISH_CONSTANT_2D;
		}
	}
	else { //We're inside the triangle (2-Simplex) at (1,1)
		r64 zins = 2 - inSum;
		if (zins < xins || zins < yins) { //(0,0) is one of the closest two triangular vertices
			if (xins > yins) {
				xsv_ext = xsb + 2;
				ysv_ext = ysb + 0;
				dx_ext = dx0 - 2 - 2 * ZTSN_SQUISH_CONSTANT_2D;
				dy_ext = dy0 + 0 - 2 * ZTSN_SQUISH_CONSTANT_2D;
			}
			else {
				xsv_ext = xsb + 0;
				ysv_ext = ysb + 2;
				dx_ext = dx0 + 0 - 2 * ZTSN_SQUISH_CONSTANT_2D;
				dy_ext = dy0 - 2 - 2 * ZTSN_SQUISH_CONSTANT_2D;
			}
		}
		else { //(1,0) and (0,1) are the closest two vertices.
			dx_ext = dx0;
			dy_ext = dy0;
			xsv_ext = xsb;
			ysv_ext = ysb;
		}
		xsb += 1;
		ysb += 1;
		dx0 = dx0 - 1 - 2 * ZTSN_SQUISH_CONSTANT_2D;
		dy0 = dy0 - 1 - 2 * ZTSN_SQUISH_CONSTANT_2D;
	}

	//Contribution (0,0) or (1,1)
	r64 attn0 = 2 - dx0 * dx0 - dy0 * dy0;
	if (attn0 > 0) {
		attn0 *= attn0;
		value += attn0 * attn0 * extrapolate2(noise, xsb, ysb, dx0, dy0);
	}

	//Extra Vertex
	r64 attn_ext = 2 - dx_ext * dx_ext - dy_ext * dy_ext;
	if (attn_ext > 0) {
		attn_ext *= attn_ext;
		value += attn_ext * attn_ext * extrapolate2(noise, xsv_ext, ysv_ext, dx_ext, dy_ext);
	}

	return (r32)(value / ZTSN_NORM_CONSTANT_2D);
}

// ================================================================================================================================================================================================

r32 zt_simplexNoise3D(ztSimplexNoise *noise, r32 x, r32 y, r32 z)
{
	zt_returnValOnNull(noise, 0);
	zt_assert(false);
	return 0;
}

// ================================================================================================================================================================================================

r32 zt_simplexNoise4D(ztSimplexNoise *noise, r32 x, r32 y, r32 z, r32 w)
{
	zt_returnValOnNull(noise, 0);
	zt_assert(false);
	return 0;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

i32 zt_iniFileGetValue(const char *ini_file, const char *section, const char *key, const char* dflt, char* buffer, i32 buffer_size)
{
	ZT_PROFILE_TOOLS("zt_iniFileGetValue");

#if defined(ZT_WINDOWS)
	return GetPrivateProfileStringA(section, key, dflt, buffer, buffer_size, ini_file);
#else
#	error "zt_iniFileGetValue needs an implementation for this platform"
#endif
}

// ================================================================================================================================================================================================

i32 zt_iniFileGetValue(const char *ini_file, const char *section, const char *key, i32 dflt)
{
	ZT_PROFILE_TOOLS("zt_iniFileGetValue");

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

// ================================================================================================================================================================================================

r32 zt_iniFileGetValue(const char *ini_file, const char *section, const char *key, r32 dflt)
{
	ZT_PROFILE_TOOLS("zt_iniFileGetValue");

	char value_buffer[128] = { 0 };
	char dflt_buffer[128] = { 0 };
	zt_strPrintf(dflt_buffer, zt_sizeof(dflt_buffer), "%f", dflt);
	int len = zt_iniFileGetValue(ini_file, section, key, dflt_buffer, value_buffer, zt_sizeof(value_buffer));
	if (len <= 0) {
		return dflt;
	}

	return zt_strToReal32(value_buffer, dflt);
}

// ================================================================================================================================================================================================

bool zt_iniFileSetValue(const char *ini_file, const char *section, const char *key, const char *value)
{
	ZT_PROFILE_TOOLS("zt_iniFileSetValue");

#if defined(ZT_WINDOWS)
	return FALSE != WritePrivateProfileStringA(section, key, value, ini_file);
#else
#	error "zt_iniFileSetValue needs an implementation for this platform"
#endif
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool zt_cmdHasArg(const char** argv, int argc, const char* arg_short, const char* arg_long)
{
	ZT_PROFILE_TOOLS("zt_cmdHasArg");

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

// ================================================================================================================================================================================================

bool zt_cmdGetArg(const char** argv, int argc, const char* arg_short, const char* arg_long, char* buffer, int buffer_size)
{
	ZT_PROFILE_TOOLS("zt_cmdGetArg");

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
					if (*(argv[i] + data_pos) == '\"') {
						data_pos += 1;
					}
					zt_strCpy(buffer, buffer_size, argv[i] + data_pos, argv_len - data_pos);

					int str_len = zt_strLen(buffer);
					if (str_len > 0) {
						if (buffer[str_len - 1] == '\"') {
							buffer[str_len - 1] = 0;
						}
					}
					return true;
				}
			}
			return false; // no data to be had
		}
	}
	return false;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

int zt_processRun(const char *command)
{
	return zt_processRun(command, nullptr, 0, nullptr);
}

// ================================================================================================================================================================================================

int zt_processRun(const char *command, char *output_buffer, int output_buffer_size, int *output_buffer_written)
{
	ZT_PROFILE_TOOLS("zt_processRun");

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
	while (!process_ended) {
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


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

r64 zt_getTime()
{
	//ZT_PROFILE_TOOLS("zt_getTime"); called in profiling code, so can't use here

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

// ================================================================================================================================================================================================

void zt_sleep(r32 seconds)
{
	ZT_PROFILE_TOOLS("zt_sleep");

#	if defined(ZT_WINDOWS)
	Sleep(zt_convertToi32Floor(seconds * 1000.f));
#	else
#	error zt_sleep needs an implementation for this platform
#	endif
}

// ================================================================================================================================================================================================

void zt_getDate(int *year, int *month, int *day, int *hour, int *minute, int *second)
{
	ZT_PROFILE_TOOLS("zt_getDate");

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

// ================================================================================================================================================================================================

ztDate zt_getDate()
{
	ztDate dt;
	zt_getDate(&dt.year, &dt.month, &dt.day, &dt.hour, &dt.minute, &dt.second);
	return dt;
}

// ================================================================================================================================================================================================

bool operator<(ztDate& d1, ztDate& d2)
{
	ZT_PROFILE_TOOLS("operator< (ztDate)");

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

// ================================================================================================================================================================================================

bool operator>(ztDate& d1, ztDate& d2)
{
	ZT_PROFILE_TOOLS("operator> (ztDate)");

	return !(d1 < d2) && !(d1 == d2);
}

// ================================================================================================================================================================================================

bool operator==(ztDate& d1, ztDate& d2)
{
	ZT_PROFILE_TOOLS("operator== (ztDate)");

	return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day && d1.hour == d2.hour && d1.minute == d2.minute && d1.second == d2.second;
}

// ================================================================================================================================================================================================

bool operator!=(ztDate& d1, ztDate& d2)
{
	ZT_PROFILE_TOOLS("operator!= (ztDate)");

	return !(d1 == d2);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

i32 zt_memoryDeltaGet(void *chunk1, void *chunk2, int chunk_size, void *data, int data_size)
{
	ZT_PROFILE_TOOLS("zt_memoryDeltaGet");

	ztMemoryChunk memChunk = zt_memoryChunkMake(data, data_size);

	byte *bchunk1 = (byte*)chunk1;
	byte *bchunk2 = (byte*)chunk2;

	i32 byte_idx = 0;
	while (byte_idx < chunk_size) {
		while (bchunk1[byte_idx] == bchunk2[byte_idx] && byte_idx < chunk_size) {
			byte_idx += 1;
		}

		if (byte_idx < chunk_size) {
			// we've hit a difference, so now tally up the total different bytes
			i32 diff_bytes = 0;
			while (bchunk1[byte_idx] != bchunk2[byte_idx] && byte_idx < chunk_size) {
				byte_idx += 1;
				diff_bytes += 1;
			}

			if (byte_idx < chunk_size) {
				i32 *p_diff_start = zt_mallocStructChunk(i32, &memChunk);
				if (p_diff_start == nullptr) {
					return -1;
				}

				i32 *p_diff_bytes = zt_mallocStructChunk(i32, &memChunk);
				if (p_diff_bytes == nullptr) {
					return -1;
				}

				byte *p_bytes = zt_mallocStructArrayChunk(byte, diff_bytes, &memChunk);
				if (p_bytes == nullptr) {
					return -1;
				}

				*p_diff_start = byte_idx - diff_bytes;
				*p_diff_bytes = diff_bytes;

				zt_assert(*p_diff_start + *p_diff_bytes <= chunk_size);
				for (i32 i = byte_idx - diff_bytes; i < byte_idx; ++i) {
					*p_bytes++ = bchunk1[i];
				}
			}
		}
	}

	return memChunk.current;
}

// ================================================================================================================================================================================================

void zt_memoryDeltaApply(void *chunk, int chunk_size, void *diff, int diff_size)
{
	ZT_PROFILE_TOOLS("zt_memoryDeltaApply");

	ztMemoryReader memReader = zt_memoryReaderMake(diff, diff_size);

	byte *bchunk = (byte*)chunk;

	while (memReader.current < memReader.memory_size) {
		i32 diff_start = zt_memoryRead_i32(&memReader);
		i32 diff_bytes = zt_memoryRead_i32(&memReader);

		if (diff_bytes > 0) {
			zt_fiz(diff_bytes) {
				byte by = zt_memoryRead_u8(&memReader);
				zt_assert(diff_start + i <= chunk_size);
				bchunk[diff_start + i] = by;
			}
		}
	}
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// embedded miniz.c
/* miniz.c v1.15 - public domain deflate/inflate, zlib-subset, ZIP reading/writing/appending, PNG writing
See "unlicense" statement at the end of this file.
Rich Geldreich <richgel99@gmail.com>, last updated Oct. 13, 2013
Implements RFC 1950: http://www.ietf.org/rfc/rfc1950.txt and RFC 1951: http://www.ietf.org/rfc/rfc1951.txt

Most API's defined in miniz.c are optional. For example, to disable the archive related functions just define
MINIZ_NO_ARCHIVE_APIS, or to get rid of all stdio usage define MINIZ_NO_STDIO (see the list below for more macros).

* Change History
10/13/13 v1.15 r4 - Interim bugfix release while I work on the next major release with Zip64 support (almost there!):
- Critical fix for the MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY bug (thanks kahmyong.moon@hp.com) which could cause locate files to not find files. This bug
would only have occured in earlier versions if you explicitly used this flag, OR if you used mz_zip_extract_archive_file_to_heap() or mz_zip_add_mem_to_archive_file_in_place()
(which used this flag). If you can't switch to v1.15 but want to fix this bug, just remove the uses of this flag from both helper funcs (and of course don't use the flag).
- Bugfix in mz_zip_reader_extract_to_mem_no_alloc() from kymoon when pUser_read_buf is not NULL and compressed size is > uncompressed size
- Fixing mz_zip_reader_extract_*() funcs so they don't try to extract compressed data from directory entries, to account for weird zipfiles which contain zero-size compressed data on dir entries.
Hopefully this fix won't cause any issues on weird zip archives, because it assumes the low 16-bits of zip external attributes are DOS attributes (which I believe they always are in practice).
- Fixing mz_zip_reader_is_file_a_directory() so it doesn't check the internal attributes, just the filename and external attributes
- mz_zip_reader_init_file() - missing MZ_FCLOSE() call if the seek failed
- Added cmake support for Linux builds which builds all the examples, tested with clang v3.3 and gcc v4.6.
- Clang fix for tdefl_write_image_to_png_file_in_memory() from toffaletti
- Merged MZ_FORCEINLINE fix from hdeanclark
- Fix <time.h> include before config #ifdef, thanks emil.brink
- Added tdefl_write_image_to_png_file_in_memory_ex(): supports Y flipping (super useful for OpenGL apps), and explicit control over the compression level (so you can
set it to 1 for real-time compression).
- Merged in some compiler fixes from paulharris's github repro.
- Retested this build under Windows (VS 2010, including static analysis), tcc  0.9.26, gcc v4.6 and clang v3.3.
- Added example6.c, which dumps an image of the mandelbrot set to a PNG file.
- Modified example2 to help test the MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY flag more.
- In r3: Bugfix to mz_zip_writer_add_file() found during merge: Fix possible src file fclose() leak if alignment bytes+local header file write faiiled
- In r4: Minor bugfix to mz_zip_writer_add_from_zip_reader(): Was pushing the wrong central dir header offset, appears harmless in this release, but it became a problem in the zip64 branch
5/20/12 v1.14 - MinGW32/64 GCC 4.6.1 compiler fixes: added MZ_FORCEINLINE, #include <time.h> (thanks fermtect).
5/19/12 v1.13 - From jason@cornsyrup.org and kelwert@mtu.edu - Fix mz_crc32() so it doesn't compute the wrong CRC-32's when mz_ulong is 64-bit.
- Temporarily/locally slammed in "typedef unsigned long mz_ulong" and re-ran a randomized regression test on ~500k files.
- Eliminated a bunch of warnings when compiling with GCC 32-bit/64.
- Ran all examples, miniz.c, and tinfl.c through MSVC 2008's /analyze (static analysis) option and fixed all warnings (except for the silly
"Use of the comma-operator in a tested expression.." analysis warning, which I purposely use to work around a MSVC compiler warning).
- Created 32-bit and 64-bit Codeblocks projects/workspace. Built and tested Linux executables. The codeblocks workspace is compatible with Linux+Win32/x64.
- Added miniz_tester solution/project, which is a useful little app derived from LZHAM's tester app that I use as part of the regression test.
- Ran miniz.c and tinfl.c through another series of regression testing on ~500,000 files and archives.
- Modified example5.c so it purposely disables a bunch of high-level functionality (MINIZ_NO_STDIO, etc.). (Thanks to corysama for the MINIZ_NO_STDIO bug report.)
- Fix ftell() usage in examples so they exit with an error on files which are too large (a limitation of the examples, not miniz itself).
4/12/12 v1.12 - More comments, added low-level example5.c, fixed a couple minor level_and_flags issues in the archive API's.
level_and_flags can now be set to MZ_DEFAULT_COMPRESSION. Thanks to Bruce Dawson <bruced@valvesoftware.com> for the feedback/bug report.
5/28/11 v1.11 - Added statement from unlicense.org
5/27/11 v1.10 - Substantial compressor optimizations:
- Level 1 is now ~4x faster than before. The L1 compressor's throughput now varies between 70-110MB/sec. on a
- Core i7 (actual throughput varies depending on the type of data, and x64 vs. x86).
- Improved baseline L2-L9 compression perf. Also, greatly improved compression perf. issues on some file types.
- Refactored the compression code for better readability and maintainability.
- Added level 10 compression level (L10 has slightly better ratio than level 9, but could have a potentially large
drop in throughput on some files).
5/15/11 v1.09 - Initial stable release.

* Low-level Deflate/Inflate implementation notes:

Compression: Use the "tdefl" API's. The compressor supports raw, static, and dynamic blocks, lazy or
greedy parsing, match length filtering, RLE-only, and Huffman-only streams. It performs and compresses
approximately as well as zlib.

Decompression: Use the "tinfl" API's. The entire decompressor is implemented as a single function
coroutine: see tinfl_decompress(). It supports decompression into a 32KB (or larger power of 2) wrapping buffer, or into a memory
block large enough to hold the entire file.

The low-level tdefl/tinfl API's do not make any use of dynamic memory allocation.

* zlib-style API notes:

miniz.c implements a fairly large subset of zlib. There's enough functionality present for it to be a drop-in
zlib replacement in many apps:
The z_stream struct, optional memory allocation callbacks
deflateInit/deflateInit2/deflate/deflateReset/deflateEnd/deflateBound
inflateInit/inflateInit2/inflate/inflateEnd
compress, compress2, compressBound, uncompress
CRC-32, Adler-32 - Using modern, minimal code size, CPU cache friendly routines.
Supports raw deflate streams or standard zlib streams with adler-32 checking.

Limitations:
The callback API's are not implemented yet. No support for gzip headers or zlib static dictionaries.
I've tried to closely emulate zlib's various flavors of stream flushing and return status codes, but
there are no guarantees that miniz.c pulls this off perfectly.

* PNG writing: See the tdefl_write_image_to_png_file_in_memory() function, originally written by
Alex Evans. Supports 1-4 bytes/pixel images.

* ZIP archive API notes:

The ZIP archive API's where designed with simplicity and efficiency in mind, with just enough abstraction to
get the job done with minimal fuss. There are simple API's to retrieve file information, read files from
existing archives, create new archives, append new files to existing archives, or clone archive data from
one archive to another. It supports archives located in memory or the heap, on disk (using stdio.h),
or you can specify custom file read/write callbacks.

- Archive reading: Just call this function to read a single file from a disk archive:

void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename, const char *pArchive_name,
size_t *pSize, mz_uint zip_flags);

For more complex cases, use the "mz_zip_reader" functions. Upon opening an archive, the entire central
directory is located and read as-is into memory, and subsequent file access only occurs when reading individual files.

- Archives file scanning: The simple way is to use this function to scan a loaded archive for a specific file:

int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName, const char *pComment, mz_uint flags);

The locate operation can optionally check file comments too, which (as one example) can be used to identify
multiple versions of the same file in an archive. This function uses a simple linear search through the central
directory, so it's not very fast.

Alternately, you can iterate through all the files in an archive (using mz_zip_reader_get_num_files()) and
retrieve detailed info on each file by calling mz_zip_reader_file_stat().

- Archive creation: Use the "mz_zip_writer" functions. The ZIP writer immediately writes compressed file data
to disk and builds an exact image of the central directory in memory. The central directory image is written
all at once at the end of the archive file when the archive is finalized.

The archive writer can optionally align each file's local header and file data to any power of 2 alignment,
which can be useful when the archive will be read from optical media. Also, the writer supports placing
arbitrary data blobs at the very beginning of ZIP archives. Archives written using either feature are still
readable by any ZIP tool.

- Archive appending: The simple way to add a single file to an archive is to call this function:

mz_bool mz_zip_add_mem_to_archive_file_in_place(const char *pZip_filename, const char *pArchive_name,
const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags);

The archive will be created if it doesn't already exist, otherwise it'll be appended to.
Note the appending is done in-place and is not an atomic operation, so if something goes wrong
during the operation it's possible the archive could be left without a central directory (although the local
file headers and file data will be fine, so the archive will be recoverable).

For more complex archive modification scenarios:
1. The safest way is to use a mz_zip_reader to read the existing archive, cloning only those bits you want to
preserve into a new archive using using the mz_zip_writer_add_from_zip_reader() function (which compiles the
compressed file data as-is). When you're done, delete the old archive and rename the newly written archive, and
you're done. This is safe but requires a bunch of temporary disk space or heap memory.

2. Or, you can convert an mz_zip_reader in-place to an mz_zip_writer using mz_zip_writer_init_from_reader(),
append new files as needed, then finalize the archive which will write an updated central directory to the
original archive. (This is basically what mz_zip_add_mem_to_archive_file_in_place() does.) There's a
possibility that the archive's central directory could be lost with this method if anything goes wrong, though.

- ZIP archive support limitations:
No zip64 or spanning support. Extraction functions can only handle unencrypted, stored or deflated files.
Requires streams capable of seeking.

* This is a header file library, like stb_image.c. To get only a header file, either cut and paste the
below header, or create miniz.h, #define MINIZ_HEADER_FILE_ONLY, and then include miniz.c from it.

* Important: For best perf. be sure to customize the below macros for your target platform:
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#define MINIZ_LITTLE_ENDIAN 1
#define MINIZ_HAS_64BIT_REGISTERS 1

* On platforms using glibc, Be sure to "#define _LARGEFILE64_SOURCE 1" before including miniz.c to ensure miniz
uses the 64-bit variants: fopen64(), stat64(), etc. Otherwise you won't be able to process large files
(i.e. 32-bit stat() fails for me on files > 0x7FFFFFFF bytes).
*/

#ifndef MINIZ_HEADER_INCLUDED
#define MINIZ_HEADER_INCLUDED

#include <stdlib.h>

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
//#define MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
//#define MINIZ_NO_TIME

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
//#define MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
//#define MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
//#define MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
//#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC

#if defined(__TINYC__) && (defined(__linux) || defined(__linux__))
// TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
#define MINIZ_NO_TIME
#endif

#if !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_ARCHIVE_APIS)
#include <time.h>
#endif

#if defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#define MINIZ_X86_OR_X64_CPU 1
#endif

#if (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#define MINIZ_LITTLE_ENDIAN 1
#endif

#if MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#endif

#if defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#define MINIZ_HAS_64BIT_REGISTERS 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

	// ------------------- zlib-style API Definitions.

	// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
	typedef unsigned long mz_ulong;

	// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
	void mz_free(void *p);

#define MZ_ADLER32_INIT (1)
	// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
	mz_ulong mz_adler32(mz_ulong adler, const unsigned char *ptr, size_t buf_len);

#define MZ_CRC32_INIT (0)
	// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
	mz_ulong mz_crc32(mz_ulong crc, const unsigned char *ptr, size_t buf_len);

	// Compression strategies.
	enum { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

	// Method
#define MZ_DEFLATED 8

#ifndef MINIZ_NO_ZLIB_APIS

	// Heap allocation callbacks.
	// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
	typedef void *(*mz_alloc_func)(void *opaque, size_t items, size_t size);
	typedef void(*mz_free_func)(void *opaque, void *address);
	typedef void *(*mz_realloc_func)(void *opaque, void *address, size_t items, size_t size);

#define MZ_VERSION          "9.1.15"
#define MZ_VERNUM           0x91F0
#define MZ_VER_MAJOR        9
#define MZ_VER_MINOR        1
#define MZ_VER_REVISION     15
#define MZ_VER_SUBREVISION  0

	// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
	enum { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_FULL_FLUSH = 3, MZ_FINISH = 4, MZ_BLOCK = 5 };

	// Return status codes. MZ_PARAM_ERROR is non-standard.
	enum { MZ_OK = 0, MZ_STREAM_END = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_STREAM_ERROR = -2, MZ_DATA_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_VERSION_ERROR = -6, MZ_PARAM_ERROR = -10000 };

	// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
	enum { MZ_NO_COMPRESSION = 0, MZ_BEST_SPEED = 1, MZ_BEST_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

	// Window bits
#define MZ_DEFAULT_WINDOW_BITS 15

	struct mz_internal_state;

	// Compression/decompression stream struct.
	typedef struct mz_stream_s
	{
		const unsigned char *next_in;     // pointer to next byte to read
		unsigned int avail_in;            // number of bytes available at next_in
		mz_ulong total_in;                // total number of bytes consumed so far

		unsigned char *next_out;          // pointer to next byte to write
		unsigned int avail_out;           // number of bytes that can be written to next_out
		mz_ulong total_out;               // total number of bytes produced so far

		char *msg;                        // error msg (unused)
		struct mz_internal_state *state;  // internal state, allocated by zalloc/zfree

		mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
		mz_free_func zfree;               // optional heap free function (defaults to free)
		void *opaque;                     // heap alloc function user pointer

		int data_type;                    // data_type (unused)
		mz_ulong adler;                   // adler32 of the source or uncompressed data
		mz_ulong reserved;                // not used
	} mz_stream;

	typedef mz_stream *mz_streamp;

	// Returns the version string of miniz.c.
	const char *mz_version(void);

	// mz_deflateInit() initializes a compressor with default options:
	// Parameters:
	//  pStream must point to an initialized mz_stream struct.
	//  level must be between [MZ_NO_COMPRESSION, MZ_BEST_COMPRESSION].
	//  level 1 enables a specially optimized compression function that's been optimized purely for performance, not ratio.
	//  (This special func. is currently only enabled when MINIZ_USE_UNALIGNED_LOADS_AND_STORES and MINIZ_LITTLE_ENDIAN are defined.)
	// Return values:
	//  MZ_OK on success.
	//  MZ_STREAM_ERROR if the stream is bogus.
	//  MZ_PARAM_ERROR if the input parameters are bogus.
	//  MZ_MEM_ERROR on out of memory.
	int mz_deflateInit(mz_streamp pStream, int level);

	// mz_deflateInit2() is like mz_deflate(), except with more control:
	// Additional parameters:
	//   method must be MZ_DEFLATED
	//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
	//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
	int mz_deflateInit2(mz_streamp pStream, int level, int method, int window_bits, int mem_level, int strategy);

	// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
	int mz_deflateReset(mz_streamp pStream);

	// mz_deflate() compresses the input to output, consuming as much of the input and producing as much output as possible.
	// Parameters:
	//   pStream is the stream to read from and write to. You must initialize/update the next_in, avail_in, next_out, and avail_out members.
	//   flush may be MZ_NO_FLUSH, MZ_PARTIAL_FLUSH/MZ_SYNC_FLUSH, MZ_FULL_FLUSH, or MZ_FINISH.
	// Return values:
	//   MZ_OK on success (when flushing, or if more input is needed but not available, and/or there's more output to be written but the output buffer is full).
	//   MZ_STREAM_END if all input has been consumed and all output bytes have been written. Don't call mz_deflate() on the stream anymore.
	//   MZ_STREAM_ERROR if the stream is bogus.
	//   MZ_PARAM_ERROR if one of the parameters is invalid.
	//   MZ_BUF_ERROR if no forward progress is possible because the input and/or output buffers are empty. (Fill up the input buffer or free up some output space and try again.)
	int mz_deflate(mz_streamp pStream, int flush);

	// mz_deflateEnd() deinitializes a compressor:
	// Return values:
	//  MZ_OK on success.
	//  MZ_STREAM_ERROR if the stream is bogus.
	int mz_deflateEnd(mz_streamp pStream);

	// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
	mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len);

	// Single-call compression functions mz_compress() and mz_compress2():
	// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
	int mz_compress(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len);
	int mz_compress2(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len, int level);

	// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
	mz_ulong mz_compressBound(mz_ulong source_len);

	// Initializes a decompressor.
	int mz_inflateInit(mz_streamp pStream);

	// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
	// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
	int mz_inflateInit2(mz_streamp pStream, int window_bits);

	// Decompresses the input stream to the output, consuming only as much of the input as needed, and writing as much to the output as possible.
	// Parameters:
	//   pStream is the stream to read from and write to. You must initialize/update the next_in, avail_in, next_out, and avail_out members.
	//   flush may be MZ_NO_FLUSH, MZ_SYNC_FLUSH, or MZ_FINISH.
	//   On the first call, if flush is MZ_FINISH it's assumed the input and output buffers are both sized large enough to decompress the entire stream in a single call (this is slightly faster).
	//   MZ_FINISH implies that there are no more source bytes available beside what's already in the input buffer, and that the output buffer is large enough to hold the rest of the decompressed data.
	// Return values:
	//   MZ_OK on success. Either more input is needed but not available, and/or there's more output to be written but the output buffer is full.
	//   MZ_STREAM_END if all needed input has been consumed and all output bytes have been written. For zlib streams, the adler-32 of the decompressed data has also been verified.
	//   MZ_STREAM_ERROR if the stream is bogus.
	//   MZ_DATA_ERROR if the deflate stream is invalid.
	//   MZ_PARAM_ERROR if one of the parameters is invalid.
	//   MZ_BUF_ERROR if no forward progress is possible because the input buffer is empty but the inflater needs more input to continue, or if the output buffer is not large enough. Call mz_inflate() again
	//   with more input data, or with more room in the output buffer (except when using single call decompression, described above).
	int mz_inflate(mz_streamp pStream, int flush);

	// Deinitializes a decompressor.
	int mz_inflateEnd(mz_streamp pStream);

	// Single-call decompression.
	// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
	int mz_uncompress(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len);

	// Returns a string description of the specified error code, or NULL if the error code is invalid.
	const char *mz_error(int err);

	// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
	// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES
	typedef unsigned char Byte;
	typedef unsigned int uInt;
	typedef mz_ulong uLong;
	typedef Byte Bytef;
	typedef uInt uIntf;
	typedef char charf;
	typedef int intf;
	typedef void *voidpf;
	typedef uLong uLongf;
	typedef void *voidp;
	typedef void *const voidpc;
#define Z_NULL                0
#define Z_NO_FLUSH            MZ_NO_FLUSH
#define Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
#define Z_SYNC_FLUSH          MZ_SYNC_FLUSH
#define Z_FULL_FLUSH          MZ_FULL_FLUSH
#define Z_FINISH              MZ_FINISH
#define Z_BLOCK               MZ_BLOCK
#define Z_OK                  MZ_OK
#define Z_STREAM_END          MZ_STREAM_END
#define Z_NEED_DICT           MZ_NEED_DICT
#define Z_ERRNO               MZ_ERRNO
#define Z_STREAM_ERROR        MZ_STREAM_ERROR
#define Z_DATA_ERROR          MZ_DATA_ERROR
#define Z_MEM_ERROR           MZ_MEM_ERROR
#define Z_BUF_ERROR           MZ_BUF_ERROR
#define Z_VERSION_ERROR       MZ_VERSION_ERROR
#define Z_PARAM_ERROR         MZ_PARAM_ERROR
#define Z_NO_COMPRESSION      MZ_NO_COMPRESSION
#define Z_BEST_SPEED          MZ_BEST_SPEED
#define Z_BEST_COMPRESSION    MZ_BEST_COMPRESSION
#define Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
#define Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
#define Z_FILTERED            MZ_FILTERED
#define Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
#define Z_RLE                 MZ_RLE
#define Z_FIXED               MZ_FIXED
#define Z_DEFLATED            MZ_DEFLATED
#define Z_DEFAULT_WINDOW_BITS MZ_DEFAULT_WINDOW_BITS
#define alloc_func            mz_alloc_func
#define free_func             mz_free_func
#define internal_state        mz_internal_state
#define z_stream              mz_stream
#define deflateInit           mz_deflateInit
#define deflateInit2          mz_deflateInit2
#define deflateReset          mz_deflateReset
#define deflate               mz_deflate
#define deflateEnd            mz_deflateEnd
#define deflateBound          mz_deflateBound
#define compress              mz_compress
#define compress2             mz_compress2
#define compressBound         mz_compressBound
#define inflateInit           mz_inflateInit
#define inflateInit2          mz_inflateInit2
#define inflate               mz_inflate
#define inflateEnd            mz_inflateEnd
#define uncompress            mz_uncompress
#define crc32                 mz_crc32
#define adler32               mz_adler32
#define MAX_WBITS             15
#define MAX_MEM_LEVEL         9
#define zError                mz_error
#define ZLIB_VERSION          MZ_VERSION
#define ZLIB_VERNUM           MZ_VERNUM
#define ZLIB_VER_MAJOR        MZ_VER_MAJOR
#define ZLIB_VER_MINOR        MZ_VER_MINOR
#define ZLIB_VER_REVISION     MZ_VER_REVISION
#define ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
#define zlibVersion           mz_version
#define zlib_version          mz_version()
#endif // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#endif // MINIZ_NO_ZLIB_APIS

	// ------------------- Types and macros

	typedef unsigned char mz_uint8;
	typedef signed short mz_int16;
	typedef unsigned short mz_uint16;
	typedef unsigned int mz_uint32;
	typedef unsigned int mz_uint;
	typedef long long mz_int64;
	typedef unsigned long long mz_uint64;
	typedef int mz_bool;

#define MZ_FALSE (0)
#define MZ_TRUE (1)

	// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#ifdef _MSC_VER
#define MZ_MACRO_END while (0, 0)
#else
#define MZ_MACRO_END while (0)
#endif

	// ------------------- ZIP archive reading/writing

#ifndef MINIZ_NO_ARCHIVE_APIS

	enum
	{
		MZ_ZIP_MAX_IO_BUF_SIZE = 64 * 1024,
		MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE = 260,
		MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE = 256
	};

	typedef struct
	{
		mz_uint32 m_file_index;
		mz_uint32 m_central_dir_ofs;
		mz_uint16 m_version_made_by;
		mz_uint16 m_version_needed;
		mz_uint16 m_bit_flag;
		mz_uint16 m_method;
#ifndef MINIZ_NO_TIME
		time_t m_time;
#endif
		mz_uint32 m_crc32;
		mz_uint64 m_comp_size;
		mz_uint64 m_uncomp_size;
		mz_uint16 m_internal_attr;
		mz_uint32 m_external_attr;
		mz_uint64 m_local_header_ofs;
		mz_uint32 m_comment_size;
		char m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE];
		char m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE];
	} mz_zip_archive_file_stat;

	typedef size_t(*mz_file_read_func)(void *pOpaque, mz_uint64 file_ofs, void *pBuf, size_t n);
	typedef size_t(*mz_file_write_func)(void *pOpaque, mz_uint64 file_ofs, const void *pBuf, size_t n);

	struct mz_zip_internal_state_tag;
	typedef struct mz_zip_internal_state_tag mz_zip_internal_state;

	typedef enum
	{
		MZ_ZIP_MODE_INVALID = 0,
		MZ_ZIP_MODE_READING = 1,
		MZ_ZIP_MODE_WRITING = 2,
		MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED = 3
	} mz_zip_mode;

	typedef struct mz_zip_archive_tag
	{
		mz_uint64 m_archive_size;
		mz_uint64 m_central_directory_file_ofs;
		mz_uint m_total_files;
		mz_zip_mode m_zip_mode;

		mz_uint m_file_offset_alignment;

		mz_alloc_func m_pAlloc;
		mz_free_func m_pFree;
		mz_realloc_func m_pRealloc;
		void *m_pAlloc_opaque;

		mz_file_read_func m_pRead;
		mz_file_write_func m_pWrite;
		void *m_pIO_opaque;

		mz_zip_internal_state *m_pState;

	} mz_zip_archive;

	typedef enum
	{
		MZ_ZIP_FLAG_CASE_SENSITIVE = 0x0100,
		MZ_ZIP_FLAG_IGNORE_PATH = 0x0200,
		MZ_ZIP_FLAG_COMPRESSED_DATA = 0x0400,
		MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY = 0x0800
	} mz_zip_flags;

	// ZIP archive reading

	// Inits a ZIP archive reader.
	// These functions read and validate the archive's central directory.
	mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size, mz_uint32 flags);
	mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, const void *pMem, size_t size, mz_uint32 flags);

#ifndef MINIZ_NO_STDIO
	mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, const char *pFilename, mz_uint32 flags);
#endif

	// Returns the total number of files in the archive.
	mz_uint mz_zip_reader_get_num_files(mz_zip_archive *pZip);

	// Returns detailed information about an archive file entry.
	mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index, mz_zip_archive_file_stat *pStat);

	// Determines if an archive file entry is a directory entry.
	mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_index);
	mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_index);

	// Retrieves the filename of an archive file entry.
	// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
	mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index, char *pFilename, mz_uint filename_buf_size);

	// Attempts to locates a file in the archive's central directory.
	// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
	// Returns -1 if the file cannot be found.
	int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName, const char *pComment, mz_uint flags);

	// Extracts a archive file to a memory buffer using no memory allocation.
	mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_index, void *pBuf, size_t buf_size, mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size);
	mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size, mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size);

	// Extracts a archive file to a memory buffer.
	mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index, void *pBuf, size_t buf_size, mz_uint flags);
	mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size, mz_uint flags);

	// Extracts a archive file to a dynamically allocated heap buffer.
	void *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index, size_t *pSize, mz_uint flags);
	void *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, const char *pFilename, size_t *pSize, mz_uint flags);

	// Extracts a archive file using a callback function to output the file's data.
	mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_index, mz_file_write_func pCallback, void *pOpaque, mz_uint flags);
	mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, const char *pFilename, mz_file_write_func pCallback, void *pOpaque, mz_uint flags);

#ifndef MINIZ_NO_STDIO
	// Extracts a archive file to a disk file and sets its last accessed and modified times.
	// This function only extracts files, not archive directory records.
	mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index, const char *pDst_filename, mz_uint flags);
	mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, const char *pArchive_filename, const char *pDst_filename, mz_uint flags);
#endif

	// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
	mz_bool mz_zip_reader_end(mz_zip_archive *pZip);

	// ZIP archive writing

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

	// Inits a ZIP archive writer.
	mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size);
	mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t size_to_reserve_at_beginning, size_t initial_allocation_size);

#ifndef MINIZ_NO_STDIO
	mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, const char *pFilename, mz_uint64 size_to_reserve_at_beginning);
#endif

	// Converts a ZIP archive reader object into a writer object, to allow efficient in-place file appends to occur on an existing archive.
	// For archives opened using mz_zip_reader_init_file, pFilename must be the archive's filename so it can be reopened for writing. If the file can't be reopened, mz_zip_reader_end() will be called.
	// For archives opened using mz_zip_reader_init_mem, the memory block must be growable using the realloc callback (which defaults to realloc unless you've overridden it).
	// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's user provided m_pWrite function cannot be NULL.
	// Note: In-place archive modification is not recommended unless you know what you're doing, because if execution stops or something goes wrong before
	// the archive is finalized the file's central directory will be hosed.
	mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, const char *pFilename);

	// Adds the contents of a memory buffer to an archive. These functions record the current local time into the archive.
	// To add a directory entry, call this method with an archive name ending in a forwardslash with empty buffer.
	// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
	mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf, size_t buf_size, mz_uint level_and_flags);
	mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32);

#ifndef MINIZ_NO_STDIO
	// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
	// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
	mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, const char *pArchive_name, const char *pSrc_filename, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags);
#endif

	// Adds a file to an archive by fully cloning the data from another archive.
	// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
	mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_index);

	// Finalizes the archive by writing the central directory records followed by the end of central directory record.
	// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
	// An archive must be manually finalized by calling this function for it to be valid.
	mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
	mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, void **pBuf, size_t *pSize);

	// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
	// Note for the archive to be valid, it must have been finalized before ending.
	mz_bool mz_zip_writer_end(mz_zip_archive *pZip);

	// Misc. high-level helper functions:

	// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
	// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
	mz_bool mz_zip_add_mem_to_archive_file_in_place(const char *pZip_filename, const char *pArchive_name, const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags);

	// Reads a single file from an archive into a heap block.
	// Returns NULL on failure.
	void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename, const char *pArchive_name, size_t *pSize, mz_uint zip_flags);

#endif // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #ifndef MINIZ_NO_ARCHIVE_APIS

	// ------------------- Low-level Decompression API Definitions

	// Decompression flags used by tinfl_decompress().
	// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
	// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
	// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
	// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
	enum
	{
		TINFL_FLAG_PARSE_ZLIB_HEADER = 1,
		TINFL_FLAG_HAS_MORE_INPUT = 2,
		TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF = 4,
		TINFL_FLAG_COMPUTE_ADLER32 = 8
	};

	// High level decompression functions:
	// tinfl_decompress_mem_to_heap() decompresses a block in memory to a heap block allocated via malloc().
	// On entry:
	//  pSrc_buf, src_buf_len: Pointer and size of the Deflate or zlib source data to decompress.
	// On return:
	//  Function returns a pointer to the decompressed data, or NULL on failure.
	//  *pOut_len will be set to the decompressed data's size, which could be larger than src_buf_len on uncompressible data.
	//  The caller must call mz_free() on the returned block when it's no longer needed.
	void *tinfl_decompress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len, size_t *pOut_len, int flags);

	// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
	// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#define TINFL_DECOMPRESS_MEM_TO_MEM_FAILED ((size_t)(-1))
	size_t tinfl_decompress_mem_to_mem(void *pOut_buf, size_t out_buf_len, const void *pSrc_buf, size_t src_buf_len, int flags);

	// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
	// Returns 1 on success or 0 on failure.
	typedef int(*tinfl_put_buf_func_ptr)(const void* pBuf, int len, void *pUser);
	int tinfl_decompress_mem_to_callback(const void *pIn_buf, size_t *pIn_buf_size, tinfl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags);

	struct tinfl_decompressor_tag; typedef struct tinfl_decompressor_tag tinfl_decompressor;

	// Max size of LZ dictionary.
#define TINFL_LZ_DICT_SIZE 32768

	// Return status.
	typedef enum
	{
		TINFL_STATUS_BAD_PARAM = -3,
		TINFL_STATUS_ADLER32_MISMATCH = -2,
		TINFL_STATUS_FAILED = -1,
		TINFL_STATUS_DONE = 0,
		TINFL_STATUS_NEEDS_MORE_INPUT = 1,
		TINFL_STATUS_HAS_MORE_OUTPUT = 2
	} tinfl_status;

	// Initializes the decompressor to its initial state.
#define tinfl_init(r) do { (r)->m_state = 0; } MZ_MACRO_END
#define tinfl_get_adler32(r) (r)->m_check_adler32

	// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
	// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
	tinfl_status tinfl_decompress(tinfl_decompressor *r, const mz_uint8 *pIn_buf_next, size_t *pIn_buf_size, mz_uint8 *pOut_buf_start, mz_uint8 *pOut_buf_next, size_t *pOut_buf_size, const mz_uint32 decomp_flags);

	// Internal/private bits follow.
	enum
	{
		TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
		TINFL_FAST_LOOKUP_BITS = 10, TINFL_FAST_LOOKUP_SIZE = 1 << TINFL_FAST_LOOKUP_BITS
	};

	typedef struct
	{
		mz_uint8 m_code_size[TINFL_MAX_HUFF_SYMBOLS_0];
		mz_int16 m_look_up[TINFL_FAST_LOOKUP_SIZE], m_tree[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
	} tinfl_huff_table;

#if MINIZ_HAS_64BIT_REGISTERS
#define TINFL_USE_64BIT_BITBUF 1
#endif

#if TINFL_USE_64BIT_BITBUF
	typedef mz_uint64 tinfl_bit_buf_t;
#define TINFL_BITBUF_SIZE (64)
#else
	typedef mz_uint32 tinfl_bit_buf_t;
#define TINFL_BITBUF_SIZE (32)
#endif

	struct tinfl_decompressor_tag
	{
		mz_uint32 m_state, m_num_bits, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_num_extra, m_table_sizes[TINFL_MAX_HUFF_TABLES];
		tinfl_bit_buf_t m_bit_buf;
		size_t m_dist_from_out_buf_start;
		tinfl_huff_table m_tables[TINFL_MAX_HUFF_TABLES];
		mz_uint8 m_raw_header[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
	};

	// ------------------- Low-level Compression API Definitions

	// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#define TDEFL_LESS_MEMORY 0

	// tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search):
	// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression).
	enum
	{
		TDEFL_HUFFMAN_ONLY = 0, TDEFL_DEFAULT_MAX_PROBES = 128, TDEFL_MAX_PROBES_MASK = 0xFFF
	};

	// TDEFL_WRITE_ZLIB_HEADER: If set, the compressor outputs a zlib header before the deflate data, and the Adler-32 of the source data at the end. Otherwise, you'll get raw deflate data.
	// TDEFL_COMPUTE_ADLER32: Always compute the adler-32 of the input data (even when not writing zlib headers).
	// TDEFL_GREEDY_PARSING_FLAG: Set to use faster greedy parsing, instead of more efficient lazy parsing.
	// TDEFL_NONDETERMINISTIC_PARSING_FLAG: Enable to decrease the compressor's initialization time to the minimum, but the output may vary from run to run given the same input (depending on the contents of memory).
	// TDEFL_RLE_MATCHES: Only look for RLE matches (matches with a distance of 1)
	// TDEFL_FILTER_MATCHES: Discards matches <= 5 chars if enabled.
	// TDEFL_FORCE_ALL_STATIC_BLOCKS: Disable usage of optimized Huffman tables.
	// TDEFL_FORCE_ALL_RAW_BLOCKS: Only use raw (uncompressed) deflate blocks.
	// The low 12 bits are reserved to control the max # of hash probes per dictionary lookup (see TDEFL_MAX_PROBES_MASK).
	enum
	{
		TDEFL_WRITE_ZLIB_HEADER = 0x01000,
		TDEFL_COMPUTE_ADLER32 = 0x02000,
		TDEFL_GREEDY_PARSING_FLAG = 0x04000,
		TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
		TDEFL_RLE_MATCHES = 0x10000,
		TDEFL_FILTER_MATCHES = 0x20000,
		TDEFL_FORCE_ALL_STATIC_BLOCKS = 0x40000,
		TDEFL_FORCE_ALL_RAW_BLOCKS = 0x80000
	};

	// High level compression functions:
	// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
	// On entry:
	//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
	//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
	// On return:
	//  Function returns a pointer to the compressed data, or NULL on failure.
	//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
	//  The caller must free() the returned block when it's no longer needed.
	void *tdefl_compress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len, size_t *pOut_len, int flags);

	// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
	// Returns 0 on failure.
	size_t tdefl_compress_mem_to_mem(void *pOut_buf, size_t out_buf_len, const void *pSrc_buf, size_t src_buf_len, int flags);

	// Compresses an image to a compressed PNG file in memory.
	// On entry:
	//  pImage, w, h, and num_chans describe the image to compress. num_chans may be 1, 2, 3, or 4. 
	//  The image pitch in bytes per scanline will be w*num_chans. The leftmost pixel on the top scanline is stored first in memory.
	//  level may range from [0,10], use MZ_NO_COMPRESSION, MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc. or a decent default is MZ_DEFAULT_LEVEL
	//  If flip is true, the image will be flipped on the Y axis (useful for OpenGL apps).
	// On return:
	//  Function returns a pointer to the compressed data, or NULL on failure.
	//  *pLen_out will be set to the size of the PNG image file.
	//  The caller must mz_free() the returned heap block (which will typically be larger than *pLen_out) when it's no longer needed.
	void *tdefl_write_image_to_png_file_in_memory_ex(const void *pImage, int w, int h, int num_chans, size_t *pLen_out, mz_uint level, mz_bool flip);
	void *tdefl_write_image_to_png_file_in_memory(const void *pImage, int w, int h, int num_chans, size_t *pLen_out);

	// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
	typedef mz_bool(*tdefl_put_buf_func_ptr)(const void* pBuf, int len, void *pUser);

	// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
	mz_bool tdefl_compress_mem_to_output(const void *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags);

	enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };

	// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#if TDEFL_LESS_MEMORY
	enum { TDEFL_LZ_CODE_BUF_SIZE = 24 * 1024, TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 12, TDEFL_LEVEL1_HASH_SIZE_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS };
#else
	enum { TDEFL_LZ_CODE_BUF_SIZE = 64 * 1024, TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 15, TDEFL_LEVEL1_HASH_SIZE_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS };
#endif

	// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
	typedef enum
	{
		TDEFL_STATUS_BAD_PARAM = -2,
		TDEFL_STATUS_PUT_BUF_FAILED = -1,
		TDEFL_STATUS_OKAY = 0,
		TDEFL_STATUS_DONE = 1,
	} tdefl_status;

	// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
	typedef enum
	{
		TDEFL_NO_FLUSH = 0,
		TDEFL_SYNC_FLUSH = 2,
		TDEFL_FULL_FLUSH = 3,
		TDEFL_FINISH = 4
	} tdefl_flush;

	// tdefl's compression state structure.
	typedef struct
	{
		tdefl_put_buf_func_ptr m_pPut_buf_func;
		void *m_pPut_buf_user;
		mz_uint m_flags, m_max_probes[2];
		int m_greedy_parsing;
		mz_uint m_adler32, m_lookahead_pos, m_lookahead_size, m_dict_size;
		mz_uint8 *m_pLZ_code_buf, *m_pLZ_flags, *m_pOutput_buf, *m_pOutput_buf_end;
		mz_uint m_num_flags_left, m_total_lz_bytes, m_lz_code_buf_dict_pos, m_bits_in, m_bit_buffer;
		mz_uint m_saved_match_dist, m_saved_match_len, m_saved_lit, m_output_flush_ofs, m_output_flush_remaining, m_finished, m_block_index, m_wants_to_finish;
		tdefl_status m_prev_return_status;
		const void *m_pIn_buf;
		void *m_pOut_buf;
		size_t *m_pIn_buf_size, *m_pOut_buf_size;
		tdefl_flush m_flush;
		const mz_uint8 *m_pSrc;
		size_t m_src_buf_left, m_out_buf_ofs;
		mz_uint8 m_dict[TDEFL_LZ_DICT_SIZE + TDEFL_MAX_MATCH_LEN - 1];
		mz_uint16 m_huff_count[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
		mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
		mz_uint8 m_huff_code_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
		mz_uint8 m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE];
		mz_uint16 m_next[TDEFL_LZ_DICT_SIZE];
		mz_uint16 m_hash[TDEFL_LZ_HASH_SIZE];
		mz_uint8 m_output_buf[TDEFL_OUT_BUF_SIZE];
	} tdefl_compressor;

	// Initializes the compressor.
	// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
	// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
	// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
	// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
	tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags);

	// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
	tdefl_status tdefl_compress(tdefl_compressor *d, const void *pIn_buf, size_t *pIn_buf_size, void *pOut_buf, size_t *pOut_buf_size, tdefl_flush flush);

	// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
	// tdefl_compress_buffer() always consumes the entire input buffer.
	tdefl_status tdefl_compress_buffer(tdefl_compressor *d, const void *pIn_buf, size_t in_buf_size, tdefl_flush flush);

	tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d);
	mz_uint32 tdefl_get_adler32(tdefl_compressor *d);

	// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#ifndef MINIZ_NO_ZLIB_APIS
	// Create tdefl_compress() flags given zlib-style compression parameters.
	// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
	// window_bits may be -15 (raw deflate) or 15 (zlib)
	// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
	mz_uint tdefl_create_comp_flags_from_zip_params(int level, int window_bits, int strategy);
#endif // #ifndef MINIZ_NO_ZLIB_APIS

#ifdef __cplusplus
}
#endif

#endif // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#ifndef MINIZ_HEADER_FILE_ONLY

typedef unsigned char mz_validate_uint16[sizeof(mz_uint16) == 2 ? 1 : -1];
typedef unsigned char mz_validate_uint32[sizeof(mz_uint32) == 4 ? 1 : -1];
typedef unsigned char mz_validate_uint64[sizeof(mz_uint64) == 8 ? 1 : -1];

#include <string.h>
#include <assert.h>

#define MZ_ASSERT(x) assert(x)

#ifdef MINIZ_NO_MALLOC
#define MZ_MALLOC(x) NULL
#define MZ_FREE(x) (void)x, ((void)0)
#define MZ_REALLOC(p, x) NULL
#else
#define MZ_MALLOC(x) malloc(x)
#define MZ_FREE(x) free(x)
#define MZ_REALLOC(p, x) realloc(p, x)
#endif

#define MZ_MAX(a,b) (((a)>(b))?(a):(b))
#define MZ_MIN(a,b) (((a)<(b))?(a):(b))
#define MZ_CLEAR_OBJ(obj) memset(&(obj), 0, sizeof(obj))

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
#define MZ_READ_LE16(p) *((const mz_uint16 *)(p))
#define MZ_READ_LE32(p) *((const mz_uint32 *)(p))
#else
#define MZ_READ_LE16(p) ((mz_uint32)(((const mz_uint8 *)(p))[0]) | ((mz_uint32)(((const mz_uint8 *)(p))[1]) << 8U))
#define MZ_READ_LE32(p) ((mz_uint32)(((const mz_uint8 *)(p))[0]) | ((mz_uint32)(((const mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((const mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((const mz_uint8 *)(p))[3]) << 24U))
#endif

#ifdef _MSC_VER
#define MZ_FORCEINLINE __forceinline
#elif defined(__GNUC__)
#define MZ_FORCEINLINE inline __attribute__((__always_inline__))
#else
#define MZ_FORCEINLINE inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

	// ------------------- zlib-style API's

	mz_ulong mz_adler32(mz_ulong adler, const unsigned char *ptr, size_t buf_len)
	{
		mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t block_len = buf_len % 5552;
		if (!ptr) return MZ_ADLER32_INIT;
		while (buf_len) {
			for (i = 0; i + 7 < block_len; i += 8, ptr += 8) {
				s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
				s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
			}
			for (; i < block_len; ++i) s1 += *ptr++, s2 += s1;
			s1 %= 65521U, s2 %= 65521U; buf_len -= block_len; block_len = 5552;
		}
		return (s2 << 16) + s1;
	}

	// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
	mz_ulong mz_crc32(mz_ulong crc, const mz_uint8 *ptr, size_t buf_len)
	{
		static const mz_uint32 s_crc32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
			0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
		mz_uint32 crcu32 = (mz_uint32)crc;
		if (!ptr) return MZ_CRC32_INIT;
		crcu32 = ~crcu32; while (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b >> 4)]; }
		return ~crcu32;
	}

	void mz_free(void *p)
	{
		MZ_FREE(p);
	}

#ifndef MINIZ_NO_ZLIB_APIS

	static void *def_alloc_func(void *opaque, size_t items, size_t size) { (void)opaque, (void)items, (void)size; return MZ_MALLOC(items * size); }
	static void def_free_func(void *opaque, void *address) { (void)opaque, (void)address; MZ_FREE(address); }
	static void *def_realloc_func(void *opaque, void *address, size_t items, size_t size) { (void)opaque, (void)address, (void)items, (void)size; return MZ_REALLOC(address, items * size); }

	const char *mz_version(void)
	{
		return MZ_VERSION;
	}

	int mz_deflateInit(mz_streamp pStream, int level)
	{
		return mz_deflateInit2(pStream, level, MZ_DEFLATED, MZ_DEFAULT_WINDOW_BITS, 9, MZ_DEFAULT_STRATEGY);
	}

	int mz_deflateInit2(mz_streamp pStream, int level, int method, int window_bits, int mem_level, int strategy)
	{
		tdefl_compressor *pComp;
		mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, window_bits, strategy);

		if (!pStream) return MZ_STREAM_ERROR;
		if ((method != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((window_bits != MZ_DEFAULT_WINDOW_BITS) && (-window_bits != MZ_DEFAULT_WINDOW_BITS))) return MZ_PARAM_ERROR;

		pStream->data_type = 0;
		pStream->adler = MZ_ADLER32_INIT;
		pStream->msg = NULL;
		pStream->reserved = 0;
		pStream->total_in = 0;
		pStream->total_out = 0;
		if (!pStream->zalloc) pStream->zalloc = def_alloc_func;
		if (!pStream->zfree) pStream->zfree = def_free_func;

		pComp = (tdefl_compressor *)pStream->zalloc(pStream->opaque, 1, sizeof(tdefl_compressor));
		if (!pComp)
			return MZ_MEM_ERROR;

		pStream->state = (struct mz_internal_state *)pComp;

		if (tdefl_init(pComp, NULL, NULL, comp_flags) != TDEFL_STATUS_OKAY)
		{
			mz_deflateEnd(pStream);
			return MZ_PARAM_ERROR;
		}

		return MZ_OK;
	}

	int mz_deflateReset(mz_streamp pStream)
	{
		if ((!pStream) || (!pStream->state) || (!pStream->zalloc) || (!pStream->zfree)) return MZ_STREAM_ERROR;
		pStream->total_in = pStream->total_out = 0;
		tdefl_init((tdefl_compressor*)pStream->state, NULL, NULL, ((tdefl_compressor*)pStream->state)->m_flags);
		return MZ_OK;
	}

	int mz_deflate(mz_streamp pStream, int flush)
	{
		size_t in_bytes, out_bytes;
		mz_ulong orig_total_in, orig_total_out;
		int mz_status = MZ_OK;

		if ((!pStream) || (!pStream->state) || (flush < 0) || (flush > MZ_FINISH) || (!pStream->next_out)) return MZ_STREAM_ERROR;
		if (!pStream->avail_out) return MZ_BUF_ERROR;

		if (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

		if (((tdefl_compressor*)pStream->state)->m_prev_return_status == TDEFL_STATUS_DONE)
			return (flush == MZ_FINISH) ? MZ_STREAM_END : MZ_BUF_ERROR;

		orig_total_in = pStream->total_in; orig_total_out = pStream->total_out;
		for (;;)
		{
			tdefl_status defl_status;
			in_bytes = pStream->avail_in; out_bytes = pStream->avail_out;

			defl_status = tdefl_compress((tdefl_compressor*)pStream->state, pStream->next_in, &in_bytes, pStream->next_out, &out_bytes, (tdefl_flush)flush);
			pStream->next_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes;
			pStream->total_in += (mz_uint)in_bytes; pStream->adler = tdefl_get_adler32((tdefl_compressor*)pStream->state);

			pStream->next_out += (mz_uint)out_bytes; pStream->avail_out -= (mz_uint)out_bytes;
			pStream->total_out += (mz_uint)out_bytes;

			if (defl_status < 0)
			{
				mz_status = MZ_STREAM_ERROR;
				break;
			}
			else if (defl_status == TDEFL_STATUS_DONE)
			{
				mz_status = MZ_STREAM_END;
				break;
			}
			else if (!pStream->avail_out)
				break;
			else if ((!pStream->avail_in) && (flush != MZ_FINISH))
			{
				if ((flush) || (pStream->total_in != orig_total_in) || (pStream->total_out != orig_total_out))
					break;
				return MZ_BUF_ERROR; // Can't make forward progress without some input.
			}
		}
		return mz_status;
	}

	int mz_deflateEnd(mz_streamp pStream)
	{
		if (!pStream) return MZ_STREAM_ERROR;
		if (pStream->state)
		{
			pStream->zfree(pStream->opaque, pStream->state);
			pStream->state = NULL;
		}
		return MZ_OK;
	}

	mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len)
	{
		(void)pStream;
		// This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
		return MZ_MAX(128 + (source_len * 110) / 100, 128 + source_len + ((source_len / (31 * 1024)) + 1) * 5);
	}

	int mz_compress2(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len, int level)
	{
		int status;
		mz_stream stream;
		memset(&stream, 0, sizeof(stream));

		// In case mz_ulong is 64-bits (argh I hate longs).
		if ((source_len | *pDest_len) > 0xFFFFFFFFU) return MZ_PARAM_ERROR;

		stream.next_in = pSource;
		stream.avail_in = (mz_uint32)source_len;
		stream.next_out = pDest;
		stream.avail_out = (mz_uint32)*pDest_len;

		status = mz_deflateInit(&stream, level);
		if (status != MZ_OK) return status;

		status = mz_deflate(&stream, MZ_FINISH);
		if (status != MZ_STREAM_END)
		{
			mz_deflateEnd(&stream);
			return (status == MZ_OK) ? MZ_BUF_ERROR : status;
		}

		*pDest_len = stream.total_out;
		return mz_deflateEnd(&stream);
	}

	int mz_compress(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len)
	{
		return mz_compress2(pDest, pDest_len, pSource, source_len, MZ_DEFAULT_COMPRESSION);
	}

	mz_ulong mz_compressBound(mz_ulong source_len)
	{
		return mz_deflateBound(NULL, source_len);
	}

	typedef struct
	{
		tinfl_decompressor m_decomp;
		mz_uint m_dict_ofs, m_dict_avail, m_first_call, m_has_flushed; int m_window_bits;
		mz_uint8 m_dict[TINFL_LZ_DICT_SIZE];
		tinfl_status m_last_status;
	} inflate_state;

	int mz_inflateInit2(mz_streamp pStream, int window_bits)
	{
		inflate_state *pDecomp;
		if (!pStream) return MZ_STREAM_ERROR;
		if ((window_bits != MZ_DEFAULT_WINDOW_BITS) && (-window_bits != MZ_DEFAULT_WINDOW_BITS)) return MZ_PARAM_ERROR;

		pStream->data_type = 0;
		pStream->adler = 0;
		pStream->msg = NULL;
		pStream->total_in = 0;
		pStream->total_out = 0;
		pStream->reserved = 0;
		if (!pStream->zalloc) pStream->zalloc = def_alloc_func;
		if (!pStream->zfree) pStream->zfree = def_free_func;

		pDecomp = (inflate_state*)pStream->zalloc(pStream->opaque, 1, sizeof(inflate_state));
		if (!pDecomp) return MZ_MEM_ERROR;

		pStream->state = (struct mz_internal_state *)pDecomp;

		tinfl_init(&pDecomp->m_decomp);
		pDecomp->m_dict_ofs = 0;
		pDecomp->m_dict_avail = 0;
		pDecomp->m_last_status = TINFL_STATUS_NEEDS_MORE_INPUT;
		pDecomp->m_first_call = 1;
		pDecomp->m_has_flushed = 0;
		pDecomp->m_window_bits = window_bits;

		return MZ_OK;
	}

	int mz_inflateInit(mz_streamp pStream)
	{
		return mz_inflateInit2(pStream, MZ_DEFAULT_WINDOW_BITS);
	}

	int mz_inflate(mz_streamp pStream, int flush)
	{
		inflate_state* pState;
		mz_uint n, first_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
		size_t in_bytes, out_bytes, orig_avail_in;
		tinfl_status status;

		if ((!pStream) || (!pStream->state)) return MZ_STREAM_ERROR;
		if (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
		if ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_FINISH)) return MZ_STREAM_ERROR;

		pState = (inflate_state*)pStream->state;
		if (pState->m_window_bits > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_HEADER;
		orig_avail_in = pStream->avail_in;

		first_call = pState->m_first_call; pState->m_first_call = 0;
		if (pState->m_last_status < 0) return MZ_DATA_ERROR;

		if (pState->m_has_flushed && (flush != MZ_FINISH)) return MZ_STREAM_ERROR;
		pState->m_has_flushed |= (flush == MZ_FINISH);

		if ((flush == MZ_FINISH) && (first_call))
		{
			// MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
			decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
			in_bytes = pStream->avail_in; out_bytes = pStream->avail_out;
			status = tinfl_decompress(&pState->m_decomp, pStream->next_in, &in_bytes, pStream->next_out, pStream->next_out, &out_bytes, decomp_flags);
			pState->m_last_status = status;
			pStream->next_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes; pStream->total_in += (mz_uint)in_bytes;
			pStream->adler = tinfl_get_adler32(&pState->m_decomp);
			pStream->next_out += (mz_uint)out_bytes; pStream->avail_out -= (mz_uint)out_bytes; pStream->total_out += (mz_uint)out_bytes;

			if (status < 0)
				return MZ_DATA_ERROR;
			else if (status != TINFL_STATUS_DONE)
			{
				pState->m_last_status = TINFL_STATUS_FAILED;
				return MZ_BUF_ERROR;
			}
			return MZ_STREAM_END;
		}
		// flush != MZ_FINISH then we must assume there's more input.
		if (flush != MZ_FINISH) decomp_flags |= TINFL_FLAG_HAS_MORE_INPUT;

		if (pState->m_dict_avail)
		{
			n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
			memcpy(pStream->next_out, pState->m_dict + pState->m_dict_ofs, n);
			pStream->next_out += n; pStream->avail_out -= n; pStream->total_out += n;
			pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_SIZE - 1);
			return ((pState->m_last_status == TINFL_STATUS_DONE) && (!pState->m_dict_avail)) ? MZ_STREAM_END : MZ_OK;
		}

		for (;;)
		{
			in_bytes = pStream->avail_in;
			out_bytes = TINFL_LZ_DICT_SIZE - pState->m_dict_ofs;

			status = tinfl_decompress(&pState->m_decomp, pStream->next_in, &in_bytes, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &out_bytes, decomp_flags);
			pState->m_last_status = status;

			pStream->next_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes;
			pStream->total_in += (mz_uint)in_bytes; pStream->adler = tinfl_get_adler32(&pState->m_decomp);

			pState->m_dict_avail = (mz_uint)out_bytes;

			n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
			memcpy(pStream->next_out, pState->m_dict + pState->m_dict_ofs, n);
			pStream->next_out += n; pStream->avail_out -= n; pStream->total_out += n;
			pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_SIZE - 1);

			if (status < 0)
				return MZ_DATA_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
			else if ((status == TINFL_STATUS_NEEDS_MORE_INPUT) && (!orig_avail_in))
				return MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
			else if (flush == MZ_FINISH)
			{
				// The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
				if (status == TINFL_STATUS_DONE)
					return pState->m_dict_avail ? MZ_BUF_ERROR : MZ_STREAM_END;
				// status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
				else if (!pStream->avail_out)
					return MZ_BUF_ERROR;
			}
			else if ((status == TINFL_STATUS_DONE) || (!pStream->avail_in) || (!pStream->avail_out) || (pState->m_dict_avail))
				break;
		}

		return ((status == TINFL_STATUS_DONE) && (!pState->m_dict_avail)) ? MZ_STREAM_END : MZ_OK;
	}

	int mz_inflateEnd(mz_streamp pStream)
	{
		if (!pStream)
			return MZ_STREAM_ERROR;
		if (pStream->state)
		{
			pStream->zfree(pStream->opaque, pStream->state);
			pStream->state = NULL;
		}
		return MZ_OK;
	}

	int mz_uncompress(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len)
	{
		mz_stream stream;
		int status;
		memset(&stream, 0, sizeof(stream));

		// In case mz_ulong is 64-bits (argh I hate longs).
		if ((source_len | *pDest_len) > 0xFFFFFFFFU) return MZ_PARAM_ERROR;

		stream.next_in = pSource;
		stream.avail_in = (mz_uint32)source_len;
		stream.next_out = pDest;
		stream.avail_out = (mz_uint32)*pDest_len;

		status = mz_inflateInit(&stream);
		if (status != MZ_OK)
			return status;

		status = mz_inflate(&stream, MZ_FINISH);
		if (status != MZ_STREAM_END)
		{
			mz_inflateEnd(&stream);
			return ((status == MZ_BUF_ERROR) && (!stream.avail_in)) ? MZ_DATA_ERROR : status;
		}
		*pDest_len = stream.total_out;

		return mz_inflateEnd(&stream);
	}

	const char *mz_error(int err)
	{
		static struct { int m_err; const char *m_pDesc; } s_error_descs[] =
		{
			{ MZ_OK, "" }, { MZ_STREAM_END, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_STREAM_ERROR, "stream error" },
			{ MZ_DATA_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_VERSION_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
		};
		mz_uint i; for (i = 0; i < sizeof(s_error_descs) / sizeof(s_error_descs[0]); ++i) if (s_error_descs[i].m_err == err) return s_error_descs[i].m_pDesc;
		return NULL;
	}

#endif //MINIZ_NO_ZLIB_APIS

	// ------------------- Low-level Decompression (completely independent from all compression API's)

#define TINFL_MEMCPY(d, s, l) memcpy(d, s, l)
#define TINFL_MEMSET(p, c, l) memset(p, c, l)

#define TINFL_CR_BEGIN switch(r->m_state) { case 0:
#define TINFL_CR_RETURN(state_index, result) do { status = result; r->m_state = state_index; goto common_exit; case state_index:; } MZ_MACRO_END
#define TINFL_CR_RETURN_FOREVER(state_index, result) do { for ( ; ; ) { TINFL_CR_RETURN(state_index, result); } } MZ_MACRO_END
#define TINFL_CR_FINISH }

	// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
	// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#define TINFL_GET_BYTE(state_index, c) do { \
  if (pIn_buf_cur >= pIn_buf_end) { \
    for ( ; ; ) { \
      if (decomp_flags & TINFL_FLAG_HAS_MORE_INPUT) { \
        TINFL_CR_RETURN(state_index, TINFL_STATUS_NEEDS_MORE_INPUT); \
        if (pIn_buf_cur < pIn_buf_end) { \
          c = *pIn_buf_cur++; \
          break; \
				        } \
	  	        } else { \
        c = 0; \
        break; \
	  	        } \
		    } \
      } else c = *pIn_buf_cur++; } MZ_MACRO_END

#define TINFL_NEED_BITS(state_index, n) do { mz_uint c; TINFL_GET_BYTE(state_index, c); bit_buf |= (((tinfl_bit_buf_t)c) << num_bits); num_bits += 8; } while (num_bits < (mz_uint)(n))
#define TINFL_SKIP_BITS(state_index, n) do { if (num_bits < (mz_uint)(n)) { TINFL_NEED_BITS(state_index, n); } bit_buf >>= (n); num_bits -= (n); } MZ_MACRO_END
#define TINFL_GET_BITS(state_index, b, n) do { if (num_bits < (mz_uint)(n)) { TINFL_NEED_BITS(state_index, n); } b = bit_buf & ((1 << (n)) - 1); bit_buf >>= (n); num_bits -= (n); } MZ_MACRO_END

	// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
	// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
	// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
	// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#define TINFL_HUFF_BITBUF_FILL(state_index, pHuff) \
  do { \
    temp = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]; \
    if (temp >= 0) { \
      code_len = temp >> 9; \
      if ((code_len) && (num_bits >= code_len)) \
      break; \
		    } else if (num_bits > TINFL_FAST_LOOKUP_BITS) { \
       code_len = TINFL_FAST_LOOKUP_BITS; \
       do { \
          temp = (pHuff)->m_tree[~temp + ((bit_buf >> code_len++) & 1)]; \
	   	          } while ((temp < 0) && (num_bits >= (code_len + 1))); if (temp >= 0) break; \
		    } TINFL_GET_BYTE(state_index, c); bit_buf |= (((tinfl_bit_buf_t)c) << num_bits); num_bits += 8; \
      } while (num_bits < 15);

	// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
	// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
	// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
	// The slow path is only executed at the very end of the input buffer.
#define TINFL_HUFF_DECODE(state_index, sym, pHuff) do { \
  int temp; mz_uint code_len, c; \
  if (num_bits < 15) { \
    if ((pIn_buf_end - pIn_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_index, pHuff); \
		    } else { \
       bit_buf |= (((tinfl_bit_buf_t)pIn_buf_cur[0]) << num_bits) | (((tinfl_bit_buf_t)pIn_buf_cur[1]) << (num_bits + 8)); pIn_buf_cur += 2; num_bits += 16; \
		    } \
      } \
  if ((temp = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= 0) \
    code_len = temp >> 9, temp &= 511; \
	    else { \
    code_len = TINFL_FAST_LOOKUP_BITS; do { temp = (pHuff)->m_tree[~temp + ((bit_buf >> code_len++) & 1)]; } while (temp < 0); \
		  } sym = temp; bit_buf >>= code_len; num_bits -= code_len; } MZ_MACRO_END

	tinfl_status tinfl_decompress(tinfl_decompressor *r, const mz_uint8 *pIn_buf_next, size_t *pIn_buf_size, mz_uint8 *pOut_buf_start, mz_uint8 *pOut_buf_next, size_t *pOut_buf_size, const mz_uint32 decomp_flags)
	{
		static const int s_length_base[31] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0 };
		static const int s_length_extra[31] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0 };
		static const int s_dist_base[32] = { 1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 0, 0 };
		static const int s_dist_extra[32] = { 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13 };
		static const mz_uint8 s_length_dezigzag[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
		static const int s_min_table_sizes[3] = { 257, 1, 4 };

		tinfl_status status = TINFL_STATUS_FAILED; mz_uint32 num_bits, dist, counter, num_extra; tinfl_bit_buf_t bit_buf;
		const mz_uint8 *pIn_buf_cur = pIn_buf_next, *const pIn_buf_end = pIn_buf_next + *pIn_buf_size;
		mz_uint8 *pOut_buf_cur = pOut_buf_next, *const pOut_buf_end = pOut_buf_next + *pOut_buf_size;
		size_t out_buf_size_mask = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((pOut_buf_next - pOut_buf_start) + *pOut_buf_size) - 1, dist_from_out_buf_start;

		// Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
		if (((out_buf_size_mask + 1) & out_buf_size_mask) || (pOut_buf_next < pOut_buf_start)) { *pIn_buf_size = *pOut_buf_size = 0; return TINFL_STATUS_BAD_PARAM; }

		num_bits = r->m_num_bits; bit_buf = r->m_bit_buf; dist = r->m_dist; counter = r->m_counter; num_extra = r->m_num_extra; dist_from_out_buf_start = r->m_dist_from_out_buf_start;
		TINFL_CR_BEGIN

			bit_buf = num_bits = dist = counter = num_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
		if (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER)
		{
			TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
			counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
			if (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((out_buf_size_mask + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
			if (counter) { TINFL_CR_RETURN_FOREVER(36, TINFL_STATUS_FAILED); }
		}

		do
		{
			TINFL_GET_BITS(3, r->m_final, 3); r->m_type = r->m_final >> 1;
			if (r->m_type == 0)
			{
				TINFL_SKIP_BITS(5, num_bits & 7);
				for (counter = 0; counter < 4; ++counter) { if (num_bits) TINFL_GET_BITS(6, r->m_raw_header[counter], 8); else TINFL_GET_BYTE(7, r->m_raw_header[counter]); }
				if ((counter = (r->m_raw_header[0] | (r->m_raw_header[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_header[2] | (r->m_raw_header[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_STATUS_FAILED); }
				while ((counter) && (num_bits))
				{
					TINFL_GET_BITS(51, dist, 8);
					while (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(52, TINFL_STATUS_HAS_MORE_OUTPUT); }
					*pOut_buf_cur++ = (mz_uint8)dist;
					counter--;
				}
				while (counter)
				{
					size_t n; while (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(9, TINFL_STATUS_HAS_MORE_OUTPUT); }
					while (pIn_buf_cur >= pIn_buf_end)
					{
						if (decomp_flags & TINFL_FLAG_HAS_MORE_INPUT)
						{
							TINFL_CR_RETURN(38, TINFL_STATUS_NEEDS_MORE_INPUT);
						}
						else
						{
							TINFL_CR_RETURN_FOREVER(40, TINFL_STATUS_FAILED);
						}
					}
					n = MZ_MIN(MZ_MIN((size_t)(pOut_buf_end - pOut_buf_cur), (size_t)(pIn_buf_end - pIn_buf_cur)), counter);
					TINFL_MEMCPY(pOut_buf_cur, pIn_buf_cur, n); pIn_buf_cur += n; pOut_buf_cur += n; counter -= (mz_uint)n;
				}
			}
			else if (r->m_type == 3)
			{
				TINFL_CR_RETURN_FOREVER(10, TINFL_STATUS_FAILED);
			}
			else
			{
				if (r->m_type == 1)
				{
					mz_uint8 *p = r->m_tables[0].m_code_size; mz_uint i;
					r->m_table_sizes[0] = 288; r->m_table_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_code_size, 5, 32);
					for (i = 0; i <= 143; ++i) *p++ = 8; for (; i <= 255; ++i) *p++ = 9; for (; i <= 279; ++i) *p++ = 7; for (; i <= 287; ++i) *p++ = 8;
				}
				else
				{
					for (counter = 0; counter < 3; counter++) { TINFL_GET_BITS(11, r->m_table_sizes[counter], "\05\05\04"[counter]); r->m_table_sizes[counter] += s_min_table_sizes[counter]; }
					MZ_CLEAR_OBJ(r->m_tables[2].m_code_size); for (counter = 0; counter < r->m_table_sizes[2]; counter++) { mz_uint s; TINFL_GET_BITS(14, s, 3); r->m_tables[2].m_code_size[s_length_dezigzag[counter]] = (mz_uint8)s; }
					r->m_table_sizes[2] = 19;
				}
				for (; (int)r->m_type >= 0; r->m_type--)
				{
					int tree_next, tree_cur; tinfl_huff_table *pTable;
					mz_uint i, j, used_syms, total, sym_index, next_code[17], total_syms[16]; pTable = &r->m_tables[r->m_type]; MZ_CLEAR_OBJ(total_syms); MZ_CLEAR_OBJ(pTable->m_look_up); MZ_CLEAR_OBJ(pTable->m_tree);
					for (i = 0; i < r->m_table_sizes[r->m_type]; ++i) total_syms[pTable->m_code_size[i]]++;
					used_syms = 0, total = 0; next_code[0] = next_code[1] = 0;
					for (i = 1; i <= 15; ++i) { used_syms += total_syms[i]; next_code[i + 1] = (total = ((total + total_syms[i]) << 1)); }
					if ((65536 != total) && (used_syms > 1))
					{
						TINFL_CR_RETURN_FOREVER(35, TINFL_STATUS_FAILED);
					}
					for (tree_next = -1, sym_index = 0; sym_index < r->m_table_sizes[r->m_type]; ++sym_index)
					{
						mz_uint rev_code = 0, l, cur_code, code_size = pTable->m_code_size[sym_index]; if (!code_size) continue;
						cur_code = next_code[code_size]++; for (l = code_size; l > 0; l--, cur_code >>= 1) rev_code = (rev_code << 1) | (cur_code & 1);
						if (code_size <= TINFL_FAST_LOOKUP_BITS) { mz_int16 k = (mz_int16)((code_size << 9) | sym_index); while (rev_code < TINFL_FAST_LOOKUP_SIZE) { pTable->m_look_up[rev_code] = k; rev_code += (1 << code_size); } continue; }
						if (0 == (tree_cur = pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_SIZE - 1)])) { pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_SIZE - 1)] = (mz_int16)tree_next; tree_cur = tree_next; tree_next -= 2; }
						rev_code >>= (TINFL_FAST_LOOKUP_BITS - 1);
						for (j = code_size; j >(TINFL_FAST_LOOKUP_BITS + 1); j--)
						{
							tree_cur -= ((rev_code >>= 1) & 1);
							if (!pTable->m_tree[-tree_cur - 1]) { pTable->m_tree[-tree_cur - 1] = (mz_int16)tree_next; tree_cur = tree_next; tree_next -= 2; }
							else tree_cur = pTable->m_tree[-tree_cur - 1];
						}
						tree_cur -= ((rev_code >>= 1) & 1); pTable->m_tree[-tree_cur - 1] = (mz_int16)sym_index;
					}
					if (r->m_type == 2)
					{
						for (counter = 0; counter < (r->m_table_sizes[0] + r->m_table_sizes[1]);)
						{
							mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); if (dist < 16) { r->m_len_codes[counter++] = (mz_uint8)dist; continue; }
							if ((dist == 16) && (!counter))
							{
								TINFL_CR_RETURN_FOREVER(17, TINFL_STATUS_FAILED);
							}
							num_extra = "\02\03\07"[dist - 16]; TINFL_GET_BITS(18, s, num_extra); s += "\03\03\013"[dist - 16];
							TINFL_MEMSET(r->m_len_codes + counter, (dist == 16) ? r->m_len_codes[counter - 1] : 0, s); counter += s;
						}
						if ((r->m_table_sizes[0] + r->m_table_sizes[1]) != counter)
						{
							TINFL_CR_RETURN_FOREVER(21, TINFL_STATUS_FAILED);
						}
						TINFL_MEMCPY(r->m_tables[0].m_code_size, r->m_len_codes, r->m_table_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_code_size, r->m_len_codes + r->m_table_sizes[0], r->m_table_sizes[1]);
					}
				}
				for (;;)
				{
					mz_uint8 *pSrc;
					for (;;)
					{
						if (((pIn_buf_end - pIn_buf_cur) < 4) || ((pOut_buf_end - pOut_buf_cur) < 2))
						{
							TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
							if (counter >= 256)
								break;
							while (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(24, TINFL_STATUS_HAS_MORE_OUTPUT); }
							*pOut_buf_cur++ = (mz_uint8)counter;
						}
						else
						{
							int sym2; mz_uint code_len;
#if TINFL_USE_64BIT_BITBUF
							if (num_bits < 30) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE32(pIn_buf_cur)) << num_bits); pIn_buf_cur += 4; num_bits += 32; }
#else
							if (num_bits < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << num_bits); pIn_buf_cur += 2; num_bits += 16; }
#endif
							if ((sym2 = r->m_tables[0].m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= 0)
								code_len = sym2 >> 9;
							else
							{
								code_len = TINFL_FAST_LOOKUP_BITS; do { sym2 = r->m_tables[0].m_tree[~sym2 + ((bit_buf >> code_len++) & 1)]; } while (sym2 < 0);
							}
							counter = sym2; bit_buf >>= code_len; num_bits -= code_len;
							if (counter & 256)
								break;

#if !TINFL_USE_64BIT_BITBUF
							if (num_bits < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << num_bits); pIn_buf_cur += 2; num_bits += 16; }
#endif
							if ((sym2 = r->m_tables[0].m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= 0)
								code_len = sym2 >> 9;
							else
							{
								code_len = TINFL_FAST_LOOKUP_BITS; do { sym2 = r->m_tables[0].m_tree[~sym2 + ((bit_buf >> code_len++) & 1)]; } while (sym2 < 0);
							}
							bit_buf >>= code_len; num_bits -= code_len;

							pOut_buf_cur[0] = (mz_uint8)counter;
							if (sym2 & 256)
							{
								pOut_buf_cur++;
								counter = sym2;
								break;
							}
							pOut_buf_cur[1] = (mz_uint8)sym2;
							pOut_buf_cur += 2;
						}
					}
					if ((counter &= 511) == 256) break;

					num_extra = s_length_extra[counter - 257]; counter = s_length_base[counter - 257];
					if (num_extra) { mz_uint extra_bits; TINFL_GET_BITS(25, extra_bits, num_extra); counter += extra_bits; }

					TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
					num_extra = s_dist_extra[dist]; dist = s_dist_base[dist];
					if (num_extra) { mz_uint extra_bits; TINFL_GET_BITS(27, extra_bits, num_extra); dist += extra_bits; }

					dist_from_out_buf_start = pOut_buf_cur - pOut_buf_start;
					if ((dist > dist_from_out_buf_start) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
					{
						TINFL_CR_RETURN_FOREVER(37, TINFL_STATUS_FAILED);
					}

					pSrc = pOut_buf_start + ((dist_from_out_buf_start - dist) & out_buf_size_mask);

					if ((MZ_MAX(pOut_buf_cur, pSrc) + counter) > pOut_buf_end)
					{
						while (counter--)
						{
							while (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(53, TINFL_STATUS_HAS_MORE_OUTPUT); }
							*pOut_buf_cur++ = pOut_buf_start[(dist_from_out_buf_start++ - dist) & out_buf_size_mask];
						}
						continue;
					}
#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES
					else if ((counter >= 9) && (counter <= dist))
					{
						const mz_uint8 *pSrc_end = pSrc + (counter & ~7);
						do
						{
							((mz_uint32 *)pOut_buf_cur)[0] = ((const mz_uint32 *)pSrc)[0];
							((mz_uint32 *)pOut_buf_cur)[1] = ((const mz_uint32 *)pSrc)[1];
							pOut_buf_cur += 8;
						} while ((pSrc += 8) < pSrc_end);
						if ((counter &= 7) < 3)
						{
							if (counter)
							{
								pOut_buf_cur[0] = pSrc[0];
								if (counter > 1)
									pOut_buf_cur[1] = pSrc[1];
								pOut_buf_cur += counter;
							}
							continue;
						}
					}
#endif
					do
					{
						pOut_buf_cur[0] = pSrc[0];
						pOut_buf_cur[1] = pSrc[1];
						pOut_buf_cur[2] = pSrc[2];
						pOut_buf_cur += 3; pSrc += 3;
					} while ((int)(counter -= 3) > 2);
					if ((int)counter > 0)
					{
						pOut_buf_cur[0] = pSrc[0];
						if ((int)counter > 1)
							pOut_buf_cur[1] = pSrc[1];
						pOut_buf_cur += counter;
					}
				}
			}
		} while (!(r->m_final & 1));
		if (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER)
		{
			TINFL_SKIP_BITS(32, num_bits & 7); for (counter = 0; counter < 4; ++counter) { mz_uint s; if (num_bits) TINFL_GET_BITS(41, s, 8); else TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
		}
		TINFL_CR_RETURN_FOREVER(34, TINFL_STATUS_DONE);
		TINFL_CR_FINISH

		common_exit :
		r->m_num_bits = num_bits; r->m_bit_buf = bit_buf; r->m_dist = dist; r->m_counter = counter; r->m_num_extra = num_extra; r->m_dist_from_out_buf_start = dist_from_out_buf_start;
		*pIn_buf_size = pIn_buf_cur - pIn_buf_next; *pOut_buf_size = pOut_buf_cur - pOut_buf_next;
		if ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_HEADER | TINFL_FLAG_COMPUTE_ADLER32)) && (status >= 0))
		{
			const mz_uint8 *ptr = pOut_buf_next; size_t buf_len = *pOut_buf_size;
			mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t block_len = buf_len % 5552;
			while (buf_len)
			{
				for (i = 0; i + 7 < block_len; i += 8, ptr += 8)
				{
					s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
					s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
				}
				for (; i < block_len; ++i) s1 += *ptr++, s2 += s1;
				s1 %= 65521U, s2 %= 65521U; buf_len -= block_len; block_len = 5552;
			}
			r->m_check_adler32 = (s2 << 16) + s1; if ((status == TINFL_STATUS_DONE) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) && (r->m_check_adler32 != r->m_z_adler32)) status = TINFL_STATUS_ADLER32_MISMATCH;
		}
		return status;
	}

	// Higher level helper functions.
	void *tinfl_decompress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len, size_t *pOut_len, int flags)
	{
		tinfl_decompressor decomp; void *pBuf = NULL, *pNew_buf; size_t src_buf_ofs = 0, out_buf_capacity = 0;
		*pOut_len = 0;
		tinfl_init(&decomp);
		for (;;)
		{
			size_t src_buf_size = src_buf_len - src_buf_ofs, dst_buf_size = out_buf_capacity - *pOut_len, new_out_buf_capacity;
			tinfl_status status = tinfl_decompress(&decomp, (const mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_size, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *pOut_len : NULL, &dst_buf_size,
				(flags & ~TINFL_FLAG_HAS_MORE_INPUT) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
			if ((status < 0) || (status == TINFL_STATUS_NEEDS_MORE_INPUT))
			{
				MZ_FREE(pBuf); *pOut_len = 0; return NULL;
			}
			src_buf_ofs += src_buf_size;
			*pOut_len += dst_buf_size;
			if (status == TINFL_STATUS_DONE) break;
			new_out_buf_capacity = out_buf_capacity * 2; if (new_out_buf_capacity < 128) new_out_buf_capacity = 128;
			pNew_buf = MZ_REALLOC(pBuf, new_out_buf_capacity);
			if (!pNew_buf)
			{
				MZ_FREE(pBuf); *pOut_len = 0; return NULL;
			}
			pBuf = pNew_buf; out_buf_capacity = new_out_buf_capacity;
		}
		return pBuf;
	}

	size_t tinfl_decompress_mem_to_mem(void *pOut_buf, size_t out_buf_len, const void *pSrc_buf, size_t src_buf_len, int flags)
	{
		tinfl_decompressor decomp; tinfl_status status; tinfl_init(&decomp);
		status = tinfl_decompress(&decomp, (const mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)pOut_buf, (mz_uint8*)pOut_buf, &out_buf_len, (flags & ~TINFL_FLAG_HAS_MORE_INPUT) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
		return (status != TINFL_STATUS_DONE) ? TINFL_DECOMPRESS_MEM_TO_MEM_FAILED : out_buf_len;
	}

	int tinfl_decompress_mem_to_callback(const void *pIn_buf, size_t *pIn_buf_size, tinfl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags)
	{
		int result = 0;
		tinfl_decompressor decomp;
		mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_SIZE); size_t in_buf_ofs = 0, dict_ofs = 0;
		if (!pDict)
			return TINFL_STATUS_FAILED;
		tinfl_init(&decomp);
		for (;;)
		{
			size_t in_buf_size = *pIn_buf_size - in_buf_ofs, dst_buf_size = TINFL_LZ_DICT_SIZE - dict_ofs;
			tinfl_status status = tinfl_decompress(&decomp, (const mz_uint8*)pIn_buf + in_buf_ofs, &in_buf_size, pDict, pDict + dict_ofs, &dst_buf_size,
				(flags & ~(TINFL_FLAG_HAS_MORE_INPUT | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
			in_buf_ofs += in_buf_size;
			if ((dst_buf_size) && (!(*pPut_buf_func)(pDict + dict_ofs, (int)dst_buf_size, pPut_buf_user)))
				break;
			if (status != TINFL_STATUS_HAS_MORE_OUTPUT)
			{
				result = (status == TINFL_STATUS_DONE);
				break;
			}
			dict_ofs = (dict_ofs + dst_buf_size) & (TINFL_LZ_DICT_SIZE - 1);
		}
		MZ_FREE(pDict);
		*pIn_buf_size = in_buf_ofs;
		return result;
	}

	// ------------------- Low-level Compression (independent from all decompression API's)

	// Purposely making these tables static for faster init and thread safety.
	static const mz_uint16 s_tdefl_len_sym[256] = {
		257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268, 269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272,
		273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274, 275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276,
		277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278,
		279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280,
		281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281,
		282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282,
		283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283,
		284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 285 };

	static const mz_uint8 s_tdefl_len_extra[256] = {
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0 };

	static const mz_uint8 s_tdefl_small_dist_sym[512] = {
		0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11,
		11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13,
		13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
		15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
		16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
		16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
		16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
		17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
		17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
		17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 };

	static const mz_uint8 s_tdefl_small_dist_extra[512] = {
		0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7 };

	static const mz_uint8 s_tdefl_large_dist_sym[128] = {
		0, 0, 18, 19, 20, 20, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
		26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
		28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29 };

	static const mz_uint8 s_tdefl_large_dist_extra[128] = {
		0, 0, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
		13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13 };

	// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
	typedef struct { mz_uint16 m_key, m_sym_index; } tdefl_sym_freq;
	static tdefl_sym_freq* tdefl_radix_sort_syms(mz_uint num_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
	{
		mz_uint32 total_passes = 2, pass_shift, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_OBJ(hist);
		for (i = 0; i < num_syms; i++) { mz_uint freq = pSyms0[i].m_key; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
		while ((total_passes > 1) && (num_syms == hist[(total_passes - 1) * 256])) total_passes--;
		for (pass_shift = 0, pass = 0; pass < total_passes; pass++, pass_shift += 8)
		{
			const mz_uint32* pHist = &hist[pass << 8];
			mz_uint offsets[256], cur_ofs = 0;
			for (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
			for (i = 0; i < num_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_key >> pass_shift) & 0xFF]++] = pCur_syms[i];
			{ tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
		}
		return pCur_syms;
	}

	// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
	static void tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, int n)
	{
		int root, leaf, next, avbl, used, dpth;
		if (n == 0) return; else if (n == 1) { A[0].m_key = 1; return; }
		A[0].m_key += A[1].m_key; root = 0; leaf = 2;
		for (next = 1; next < n - 1; next++)
		{
			if (leaf >= n || A[root].m_key<A[leaf].m_key) { A[next].m_key = A[root].m_key; A[root++].m_key = (mz_uint16)next; }
			else A[next].m_key = A[leaf++].m_key;
			if (leaf >= n || (root<next && A[root].m_key<A[leaf].m_key)) { A[next].m_key = (mz_uint16)(A[next].m_key + A[root].m_key); A[root++].m_key = (mz_uint16)next; }
			else A[next].m_key = (mz_uint16)(A[next].m_key + A[leaf++].m_key);
		}
		A[n - 2].m_key = 0; for (next = n - 3; next >= 0; next--) A[next].m_key = A[A[next].m_key].m_key + 1;
		avbl = 1; used = dpth = 0; root = n - 2; next = n - 1;
		while (avbl>0)
		{
			while (root >= 0 && (int)A[root].m_key == dpth) { used++; root--; }
			while (avbl>used) { A[next--].m_key = (mz_uint16)(dpth); avbl--; }
			avbl = 2 * used; dpth++; used = 0;
		}
	}

	// Limits canonical Huffman code table's max code size.
	enum { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
	static void tdefl_huffman_enforce_max_code_size(int *pNum_codes, int code_list_len, int max_code_size)
	{
		int i; mz_uint32 total = 0; if (code_list_len <= 1) return;
		for (i = max_code_size + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) pNum_codes[max_code_size] += pNum_codes[i];
		for (i = max_code_size; i > 0; i--) total += (((mz_uint32)pNum_codes[i]) << (max_code_size - i));
		while (total != (1UL << max_code_size))
		{
			pNum_codes[max_code_size]--;
			for (i = max_code_size - 1; i > 0; i--) if (pNum_codes[i]) { pNum_codes[i]--; pNum_codes[i + 1] += 2; break; }
			total--;
		}
	}

	static void tdefl_optimize_huffman_table(tdefl_compressor *d, int table_num, int table_len, int code_size_limit, int static_table)
	{
		int i, j, l, num_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint next_code[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_OBJ(num_codes);
		if (static_table)
		{
			for (i = 0; i < table_len; i++) num_codes[d->m_huff_code_sizes[table_num][i]]++;
		}
		else
		{
			tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
			int num_used_syms = 0;
			const mz_uint16 *pSym_count = &d->m_huff_count[table_num][0];
			for (i = 0; i < table_len; i++) if (pSym_count[i]) { syms0[num_used_syms].m_key = (mz_uint16)pSym_count[i]; syms0[num_used_syms++].m_sym_index = (mz_uint16)i; }

			pSyms = tdefl_radix_sort_syms(num_used_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, num_used_syms);

			for (i = 0; i < num_used_syms; i++) num_codes[pSyms[i].m_key]++;

			tdefl_huffman_enforce_max_code_size(num_codes, num_used_syms, code_size_limit);

			MZ_CLEAR_OBJ(d->m_huff_code_sizes[table_num]); MZ_CLEAR_OBJ(d->m_huff_codes[table_num]);
			for (i = 1, j = num_used_syms; i <= code_size_limit; i++)
				for (l = num_codes[i]; l > 0; l--) d->m_huff_code_sizes[table_num][pSyms[--j].m_sym_index] = (mz_uint8)(i);
		}

		next_code[1] = 0; for (j = 0, i = 2; i <= code_size_limit; i++) next_code[i] = j = ((j + num_codes[i - 1]) << 1);

		for (i = 0; i < table_len; i++)
		{
			mz_uint rev_code = 0, code, code_size; if ((code_size = d->m_huff_code_sizes[table_num][i]) == 0) continue;
			code = next_code[code_size]++; for (l = code_size; l > 0; l--, code >>= 1) rev_code = (rev_code << 1) | (code & 1);
			d->m_huff_codes[table_num][i] = (mz_uint16)rev_code;
		}
	}

#define TDEFL_PUT_BITS(b, l) do { \
  mz_uint bits = b; mz_uint len = l; MZ_ASSERT(bits <= ((1U << len) - 1U)); \
  d->m_bit_buffer |= (bits << d->m_bits_in); d->m_bits_in += len; \
      while (d->m_bits_in >= 8) { \
    if (d->m_pOutput_buf < d->m_pOutput_buf_end) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_bit_buffer); \
      d->m_bit_buffer >>= 8; \
      d->m_bits_in -= 8; \
	  	  } \
		} MZ_MACRO_END

#define TDEFL_RLE_PREV_CODE_SIZE() { if (rle_repeat_count) { \
  if (rle_repeat_count < 3) { \
    d->m_huff_count[2][prev_code_size] = (mz_uint16)(d->m_huff_count[2][prev_code_size] + rle_repeat_count); \
		    while (rle_repeat_count--) packed_code_sizes[num_packed_code_sizes++] = prev_code_size; \
      } else { \
    d->m_huff_count[2][16] = (mz_uint16)(d->m_huff_count[2][16] + 1); packed_code_sizes[num_packed_code_sizes++] = 16; packed_code_sizes[num_packed_code_sizes++] = (mz_uint8)(rle_repeat_count - 3); \
    } rle_repeat_count = 0; } }

#define TDEFL_RLE_ZERO_CODE_SIZE() { if (rle_z_count) { \
  if (rle_z_count < 3) { \
    d->m_huff_count[2][0] = (mz_uint16)(d->m_huff_count[2][0] + rle_z_count); while (rle_z_count--) packed_code_sizes[num_packed_code_sizes++] = 0; \
      } else if (rle_z_count <= 10) { \
    d->m_huff_count[2][17] = (mz_uint16)(d->m_huff_count[2][17] + 1); packed_code_sizes[num_packed_code_sizes++] = 17; packed_code_sizes[num_packed_code_sizes++] = (mz_uint8)(rle_z_count - 3); \
		  } else { \
    d->m_huff_count[2][18] = (mz_uint16)(d->m_huff_count[2][18] + 1); packed_code_sizes[num_packed_code_sizes++] = 18; packed_code_sizes[num_packed_code_sizes++] = (mz_uint8)(rle_z_count - 11); \
		} rle_z_count = 0; } }

	static mz_uint8 s_tdefl_packed_code_size_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

	static void tdefl_start_dynamic_block(tdefl_compressor *d)
	{
		int num_lit_codes, num_dist_codes, num_bit_lengths; mz_uint i, total_code_sizes_to_pack, num_packed_code_sizes, rle_z_count, rle_repeat_count, packed_code_sizes_index;
		mz_uint8 code_sizes_to_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_code_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], prev_code_size = 0xFF;

		d->m_huff_count[0][256] = 1;

		tdefl_optimize_huffman_table(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
		tdefl_optimize_huffman_table(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

		for (num_lit_codes = 286; num_lit_codes > 257; num_lit_codes--) if (d->m_huff_code_sizes[0][num_lit_codes - 1]) break;
		for (num_dist_codes = 30; num_dist_codes > 1; num_dist_codes--) if (d->m_huff_code_sizes[1][num_dist_codes - 1]) break;

		memcpy(code_sizes_to_pack, &d->m_huff_code_sizes[0][0], num_lit_codes);
		memcpy(code_sizes_to_pack + num_lit_codes, &d->m_huff_code_sizes[1][0], num_dist_codes);
		total_code_sizes_to_pack = num_lit_codes + num_dist_codes; num_packed_code_sizes = 0; rle_z_count = 0; rle_repeat_count = 0;

		memset(&d->m_huff_count[2][0], 0, sizeof(d->m_huff_count[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
		for (i = 0; i < total_code_sizes_to_pack; i++)
		{
			mz_uint8 code_size = code_sizes_to_pack[i];
			if (!code_size)
			{
				TDEFL_RLE_PREV_CODE_SIZE();
				if (++rle_z_count == 138) { TDEFL_RLE_ZERO_CODE_SIZE(); }
			}
			else
			{
				TDEFL_RLE_ZERO_CODE_SIZE();
				if (code_size != prev_code_size)
				{
					TDEFL_RLE_PREV_CODE_SIZE();
					d->m_huff_count[2][code_size] = (mz_uint16)(d->m_huff_count[2][code_size] + 1); packed_code_sizes[num_packed_code_sizes++] = code_size;
				}
				else if (++rle_repeat_count == 6)
				{
					TDEFL_RLE_PREV_CODE_SIZE();
				}
			}
			prev_code_size = code_size;
		}
		if (rle_repeat_count) { TDEFL_RLE_PREV_CODE_SIZE(); }
		else { TDEFL_RLE_ZERO_CODE_SIZE(); }

		tdefl_optimize_huffman_table(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

		TDEFL_PUT_BITS(2, 2);

		TDEFL_PUT_BITS(num_lit_codes - 257, 5);
		TDEFL_PUT_BITS(num_dist_codes - 1, 5);

		for (num_bit_lengths = 18; num_bit_lengths >= 0; num_bit_lengths--) if (d->m_huff_code_sizes[2][s_tdefl_packed_code_size_syms_swizzle[num_bit_lengths]]) break;
		num_bit_lengths = MZ_MAX(4, (num_bit_lengths + 1)); TDEFL_PUT_BITS(num_bit_lengths - 4, 4);
		for (i = 0; (int)i < num_bit_lengths; i++) TDEFL_PUT_BITS(d->m_huff_code_sizes[2][s_tdefl_packed_code_size_syms_swizzle[i]], 3);

		for (packed_code_sizes_index = 0; packed_code_sizes_index < num_packed_code_sizes;)
		{
			mz_uint code = packed_code_sizes[packed_code_sizes_index++]; MZ_ASSERT(code < TDEFL_MAX_HUFF_SYMBOLS_2);
			TDEFL_PUT_BITS(d->m_huff_codes[2][code], d->m_huff_code_sizes[2][code]);
			if (code >= 16) TDEFL_PUT_BITS(packed_code_sizes[packed_code_sizes_index++], "\02\03\07"[code - 16]);
		}
	}

	static void tdefl_start_static_block(tdefl_compressor *d)
	{
		mz_uint i;
		mz_uint8 *p = &d->m_huff_code_sizes[0][0];

		for (i = 0; i <= 143; ++i) *p++ = 8;
		for (; i <= 255; ++i) *p++ = 9;
		for (; i <= 279; ++i) *p++ = 7;
		for (; i <= 287; ++i) *p++ = 8;

		memset(d->m_huff_code_sizes[1], 5, 32);

		tdefl_optimize_huffman_table(d, 0, 288, 15, MZ_TRUE);
		tdefl_optimize_huffman_table(d, 1, 32, 15, MZ_TRUE);

		TDEFL_PUT_BITS(1, 2);
	}

	static const mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS
	static mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
	{
		mz_uint flags;
		mz_uint8 *pLZ_codes;
		mz_uint8 *pOutput_buf = d->m_pOutput_buf;
		mz_uint8 *pLZ_code_buf_end = d->m_pLZ_code_buf;
		mz_uint64 bit_buffer = d->m_bit_buffer;
		mz_uint bits_in = d->m_bits_in;

#define TDEFL_PUT_BITS_FAST(b, l) { bit_buffer |= (((mz_uint64)(b)) << bits_in); bits_in += (l); }

		flags = 1;
		for (pLZ_codes = d->m_lz_code_buf; pLZ_codes < pLZ_code_buf_end; flags >>= 1)
		{
			if (flags == 1)
				flags = *pLZ_codes++ | 0x100;

			if (flags & 1)
			{
				mz_uint s0, s1, n0, n1, sym, num_extra_bits;
				mz_uint match_len = pLZ_codes[0], match_dist = *(const mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

				MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
				TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][s_tdefl_len_sym[match_len]], d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
				TDEFL_PUT_BITS_FAST(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]], s_tdefl_len_extra[match_len]);

				// This sequence coaxes MSVC into using cmov's vs. jmp's.
				s0 = s_tdefl_small_dist_sym[match_dist & 511];
				n0 = s_tdefl_small_dist_extra[match_dist & 511];
				s1 = s_tdefl_large_dist_sym[match_dist >> 8];
				n1 = s_tdefl_large_dist_extra[match_dist >> 8];
				sym = (match_dist < 512) ? s0 : s1;
				num_extra_bits = (match_dist < 512) ? n0 : n1;

				MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
				TDEFL_PUT_BITS_FAST(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
				TDEFL_PUT_BITS_FAST(match_dist & mz_bitmasks[num_extra_bits], num_extra_bits);
			}
			else
			{
				mz_uint lit = *pLZ_codes++;
				MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
				TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);

				if (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end))
				{
					flags >>= 1;
					lit = *pLZ_codes++;
					MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
					TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);

					if (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end))
					{
						flags >>= 1;
						lit = *pLZ_codes++;
						MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
						TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
					}
				}
			}

			if (pOutput_buf >= d->m_pOutput_buf_end)
				return MZ_FALSE;

			*(mz_uint64*)pOutput_buf = bit_buffer;
			pOutput_buf += (bits_in >> 3);
			bit_buffer >>= (bits_in & ~7);
			bits_in &= 7;
		}

#undef TDEFL_PUT_BITS_FAST

		d->m_pOutput_buf = pOutput_buf;
		d->m_bits_in = 0;
		d->m_bit_buffer = 0;

		while (bits_in)
		{
			mz_uint32 n = MZ_MIN(bits_in, 16);
			TDEFL_PUT_BITS((mz_uint)bit_buffer & mz_bitmasks[n], n);
			bit_buffer >>= n;
			bits_in -= n;
		}

		TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

		return (d->m_pOutput_buf < d->m_pOutput_buf_end);
	}
#else
	static mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
	{
		mz_uint flags;
		mz_uint8 *pLZ_codes;

		flags = 1;
		for (pLZ_codes = d->m_lz_code_buf; pLZ_codes < d->m_pLZ_code_buf; flags >>= 1)
		{
			if (flags == 1)
				flags = *pLZ_codes++ | 0x100;
			if (flags & 1)
			{
				mz_uint sym, num_extra_bits;
				mz_uint match_len = pLZ_codes[0], match_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

				MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
				TDEFL_PUT_BITS(d->m_huff_codes[0][s_tdefl_len_sym[match_len]], d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
				TDEFL_PUT_BITS(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]], s_tdefl_len_extra[match_len]);

				if (match_dist < 512)
				{
					sym = s_tdefl_small_dist_sym[match_dist]; num_extra_bits = s_tdefl_small_dist_extra[match_dist];
				}
				else
				{
					sym = s_tdefl_large_dist_sym[match_dist >> 8]; num_extra_bits = s_tdefl_large_dist_extra[match_dist >> 8];
				}
				MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
				TDEFL_PUT_BITS(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
				TDEFL_PUT_BITS(match_dist & mz_bitmasks[num_extra_bits], num_extra_bits);
			}
			else
			{
				mz_uint lit = *pLZ_codes++;
				MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
				TDEFL_PUT_BITS(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
			}
		}

		TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

		return (d->m_pOutput_buf < d->m_pOutput_buf_end);
	}
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

	static mz_bool tdefl_compress_block(tdefl_compressor *d, mz_bool static_block)
	{
		if (static_block)
			tdefl_start_static_block(d);
		else
			tdefl_start_dynamic_block(d);
		return tdefl_compress_lz_codes(d);
	}

	static int tdefl_flush_block(tdefl_compressor *d, int flush)
	{
		mz_uint saved_bit_buf, saved_bits_in;
		mz_uint8 *pSaved_output_buf;
		mz_bool comp_block_succeeded = MZ_FALSE;
		int n, use_raw_block = ((d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS) != 0) && (d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_size;
		mz_uint8 *pOutput_buf_start = ((d->m_pPut_buf_func == NULL) && ((*d->m_pOut_buf_size - d->m_out_buf_ofs) >= TDEFL_OUT_BUF_SIZE)) ? ((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs) : d->m_output_buf;

		d->m_pOutput_buf = pOutput_buf_start;
		d->m_pOutput_buf_end = d->m_pOutput_buf + TDEFL_OUT_BUF_SIZE - 16;

		MZ_ASSERT(!d->m_output_flush_remaining);
		d->m_output_flush_ofs = 0;
		d->m_output_flush_remaining = 0;

		*d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_num_flags_left);
		d->m_pLZ_code_buf -= (d->m_num_flags_left == 8);

		if ((d->m_flags & TDEFL_WRITE_ZLIB_HEADER) && (!d->m_block_index))
		{
			TDEFL_PUT_BITS(0x78, 8); TDEFL_PUT_BITS(0x01, 8);
		}

		TDEFL_PUT_BITS(flush == TDEFL_FINISH, 1);

		pSaved_output_buf = d->m_pOutput_buf; saved_bit_buf = d->m_bit_buffer; saved_bits_in = d->m_bits_in;

		if (!use_raw_block)
			comp_block_succeeded = tdefl_compress_block(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_BLOCKS) || (d->m_total_lz_bytes < 48));

		// If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
		if (((use_raw_block) || ((d->m_total_lz_bytes) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_total_lz_bytes))) &&
			((d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_size))
		{
			mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_bit_buffer = saved_bit_buf, d->m_bits_in = saved_bits_in;
			TDEFL_PUT_BITS(0, 2);
			if (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); }
			for (i = 2; i; --i, d->m_total_lz_bytes ^= 0xFFFF)
			{
				TDEFL_PUT_BITS(d->m_total_lz_bytes & 0xFFFF, 16);
			}
			for (i = 0; i < d->m_total_lz_bytes; ++i)
			{
				TDEFL_PUT_BITS(d->m_dict[(d->m_lz_code_buf_dict_pos + i) & TDEFL_LZ_DICT_SIZE_MASK], 8);
			}
		}
		// Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
		else if (!comp_block_succeeded)
		{
			d->m_pOutput_buf = pSaved_output_buf; d->m_bit_buffer = saved_bit_buf, d->m_bits_in = saved_bits_in;
			tdefl_compress_block(d, MZ_TRUE);
		}

		if (flush)
		{
			if (flush == TDEFL_FINISH)
			{
				if (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); }
				if (d->m_flags & TDEFL_WRITE_ZLIB_HEADER) { mz_uint i, a = d->m_adler32; for (i = 0; i < 4; i++) { TDEFL_PUT_BITS((a >> 24) & 0xFF, 8); a <<= 8; } }
			}
			else
			{
				mz_uint i, z = 0; TDEFL_PUT_BITS(0, 3); if (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); } for (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_BITS(z & 0xFFFF, 16); }
			}
		}

		MZ_ASSERT(d->m_pOutput_buf < d->m_pOutput_buf_end);

		memset(&d->m_huff_count[0][0], 0, sizeof(d->m_huff_count[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
		memset(&d->m_huff_count[1][0], 0, sizeof(d->m_huff_count[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

		d->m_pLZ_code_buf = d->m_lz_code_buf + 1; d->m_pLZ_flags = d->m_lz_code_buf; d->m_num_flags_left = 8; d->m_lz_code_buf_dict_pos += d->m_total_lz_bytes; d->m_total_lz_bytes = 0; d->m_block_index++;

		if ((n = (int)(d->m_pOutput_buf - pOutput_buf_start)) != 0)
		{
			if (d->m_pPut_buf_func)
			{
				*d->m_pIn_buf_size = d->m_pSrc - (const mz_uint8 *)d->m_pIn_buf;
				if (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
					return (d->m_prev_return_status = TDEFL_STATUS_PUT_BUF_FAILED);
			}
			else if (pOutput_buf_start == d->m_output_buf)
			{
				int bytes_to_copy = (int)MZ_MIN((size_t)n, (size_t)(*d->m_pOut_buf_size - d->m_out_buf_ofs));
				memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf, bytes_to_copy);
				d->m_out_buf_ofs += bytes_to_copy;
				if ((n -= bytes_to_copy) != 0)
				{
					d->m_output_flush_ofs = bytes_to_copy;
					d->m_output_flush_remaining = n;
				}
			}
			else
			{
				d->m_out_buf_ofs += n;
			}
		}

		return d->m_output_flush_remaining;
	}

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#define TDEFL_READ_UNALIGNED_WORD(p) *(const mz_uint16*)(p)
	static MZ_FORCEINLINE void tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_match_len, mz_uint *pMatch_dist, mz_uint *pMatch_len)
	{
		mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK, match_len = *pMatch_len, probe_pos = pos, next_probe_pos, probe_len;
		mz_uint num_probes_left = d->m_max_probes[match_len >= 32];
		const mz_uint16 *s = (const mz_uint16*)(d->m_dict + pos), *p, *q;
		mz_uint16 c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]), s01 = TDEFL_READ_UNALIGNED_WORD(s);
		MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN); if (max_match_len <= match_len) return;
		for (;;)
		{
			for (;;)
			{
				if (--num_probes_left == 0) return;
#define TDEFL_PROBE \
        next_probe_pos = d->m_next[probe_pos]; \
        if ((!next_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - next_probe_pos)) > max_dist)) return; \
        probe_pos = next_probe_pos & TDEFL_LZ_DICT_SIZE_MASK; \
        if (TDEFL_READ_UNALIGNED_WORD(&d->m_dict[probe_pos + match_len - 1]) == c01) break;
				TDEFL_PROBE; TDEFL_PROBE; TDEFL_PROBE;
			}
			if (!dist) break; q = (const mz_uint16*)(d->m_dict + probe_pos); if (TDEFL_READ_UNALIGNED_WORD(q) != s01) continue; p = s; probe_len = 32;
			do {} while ((TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
				(TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0));
			if (!probe_len)
			{
				*pMatch_dist = dist; *pMatch_len = MZ_MIN(max_match_len, TDEFL_MAX_MATCH_LEN); break;
			}
			else if ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(const mz_uint8*)p == *(const mz_uint8*)q)) > match_len)
			{
				*pMatch_dist = dist; if ((*pMatch_len = match_len = MZ_MIN(max_match_len, probe_len)) == max_match_len) break;
				c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]);
			}
		}
	}
#else
	static MZ_FORCEINLINE void tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_match_len, mz_uint *pMatch_dist, mz_uint *pMatch_len)
	{
		mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK, match_len = *pMatch_len, probe_pos = pos, next_probe_pos, probe_len;
		mz_uint num_probes_left = d->m_max_probes[match_len >= 32];
		const mz_uint8 *s = d->m_dict + pos, *p, *q;
		mz_uint8 c0 = d->m_dict[pos + match_len], c1 = d->m_dict[pos + match_len - 1];
		MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN); if (max_match_len <= match_len) return;
		for (;;)
		{
			for (;;)
			{
				if (--num_probes_left == 0) return;
#define TDEFL_PROBE \
        next_probe_pos = d->m_next[probe_pos]; \
        if ((!next_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - next_probe_pos)) > max_dist)) return; \
        probe_pos = next_probe_pos & TDEFL_LZ_DICT_SIZE_MASK; \
        if ((d->m_dict[probe_pos + match_len] == c0) && (d->m_dict[probe_pos + match_len - 1] == c1)) break;
				TDEFL_PROBE; TDEFL_PROBE; TDEFL_PROBE;
			}
			if (!dist) break; p = s; q = d->m_dict + probe_pos; for (probe_len = 0; probe_len < max_match_len; probe_len++) if (*p++ != *q++) break;
			if (probe_len > match_len)
			{
				*pMatch_dist = dist; if ((*pMatch_len = match_len = probe_len) == max_match_len) return;
				c0 = d->m_dict[pos + match_len]; c1 = d->m_dict[pos + match_len - 1];
			}
		}
	}
#endif // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
	static mz_bool tdefl_compress_fast(tdefl_compressor *d)
	{
		// Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
		mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_size = d->m_lookahead_size, dict_size = d->m_dict_size, total_lz_bytes = d->m_total_lz_bytes, num_flags_left = d->m_num_flags_left;
		mz_uint8 *pLZ_code_buf = d->m_pLZ_code_buf, *pLZ_flags = d->m_pLZ_flags;
		mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK;

		while ((d->m_src_buf_left) || ((d->m_flush) && (lookahead_size)))
		{
			const mz_uint TDEFL_COMP_FAST_LOOKAHEAD_SIZE = 4096;
			mz_uint dst_pos = (lookahead_pos + lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK;
			mz_uint num_bytes_to_process = (mz_uint)MZ_MIN(d->m_src_buf_left, TDEFL_COMP_FAST_LOOKAHEAD_SIZE - lookahead_size);
			d->m_src_buf_left -= num_bytes_to_process;
			lookahead_size += num_bytes_to_process;

			while (num_bytes_to_process)
			{
				mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_SIZE - dst_pos, num_bytes_to_process);
				memcpy(d->m_dict + dst_pos, d->m_pSrc, n);
				if (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
					memcpy(d->m_dict + TDEFL_LZ_DICT_SIZE + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_MATCH_LEN - 1) - dst_pos));
				d->m_pSrc += n;
				dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_SIZE_MASK;
				num_bytes_to_process -= n;
			}

			dict_size = MZ_MIN(TDEFL_LZ_DICT_SIZE - lookahead_size, dict_size);
			if ((!d->m_flush) && (lookahead_size < TDEFL_COMP_FAST_LOOKAHEAD_SIZE)) break;

			while (lookahead_size >= 4)
			{
				mz_uint cur_match_dist, cur_match_len = 1;
				mz_uint8 *pCur_dict = d->m_dict + cur_pos;
				mz_uint first_trigram = (*(const mz_uint32 *)pCur_dict) & 0xFFFFFF;
				mz_uint hash = (first_trigram ^ (first_trigram >> (24 - (TDEFL_LZ_HASH_BITS - 8)))) & TDEFL_LEVEL1_HASH_SIZE_MASK;
				mz_uint probe_pos = d->m_hash[hash];
				d->m_hash[hash] = (mz_uint16)lookahead_pos;

				if (((cur_match_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_size) && ((*(const mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_SIZE_MASK)) & 0xFFFFFF) == first_trigram))
				{
					const mz_uint16 *p = (const mz_uint16 *)pCur_dict;
					const mz_uint16 *q = (const mz_uint16 *)(d->m_dict + probe_pos);
					mz_uint32 probe_len = 32;
					do {} while ((TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
						(TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0));
					cur_match_len = ((mz_uint)(p - (const mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(const mz_uint8 *)p == *(const mz_uint8 *)q);
					if (!probe_len)
						cur_match_len = cur_match_dist ? TDEFL_MAX_MATCH_LEN : 0;

					if ((cur_match_len < TDEFL_MIN_MATCH_LEN) || ((cur_match_len == TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 8U * 1024U)))
					{
						cur_match_len = 1;
						*pLZ_code_buf++ = (mz_uint8)first_trigram;
						*pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
						d->m_huff_count[0][(mz_uint8)first_trigram]++;
					}
					else
					{
						mz_uint32 s0, s1;
						cur_match_len = MZ_MIN(cur_match_len, lookahead_size);

						MZ_ASSERT((cur_match_len >= TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 1) && (cur_match_dist <= TDEFL_LZ_DICT_SIZE));

						cur_match_dist--;

						pLZ_code_buf[0] = (mz_uint8)(cur_match_len - TDEFL_MIN_MATCH_LEN);
						*(mz_uint16 *)(&pLZ_code_buf[1]) = (mz_uint16)cur_match_dist;
						pLZ_code_buf += 3;
						*pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

						s0 = s_tdefl_small_dist_sym[cur_match_dist & 511];
						s1 = s_tdefl_large_dist_sym[cur_match_dist >> 8];
						d->m_huff_count[1][(cur_match_dist < 512) ? s0 : s1]++;

						d->m_huff_count[0][s_tdefl_len_sym[cur_match_len - TDEFL_MIN_MATCH_LEN]]++;
					}
				}
				else
				{
					*pLZ_code_buf++ = (mz_uint8)first_trigram;
					*pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
					d->m_huff_count[0][(mz_uint8)first_trigram]++;
				}

				if (--num_flags_left == 0) { num_flags_left = 8; pLZ_flags = pLZ_code_buf++; }

				total_lz_bytes += cur_match_len;
				lookahead_pos += cur_match_len;
				dict_size = MZ_MIN(dict_size + cur_match_len, TDEFL_LZ_DICT_SIZE);
				cur_pos = (cur_pos + cur_match_len) & TDEFL_LZ_DICT_SIZE_MASK;
				MZ_ASSERT(lookahead_size >= cur_match_len);
				lookahead_size -= cur_match_len;

				if (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8])
				{
					int n;
					d->m_lookahead_pos = lookahead_pos; d->m_lookahead_size = lookahead_size; d->m_dict_size = dict_size;
					d->m_total_lz_bytes = total_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_num_flags_left = num_flags_left;
					if ((n = tdefl_flush_block(d, 0)) != 0)
						return (n < 0) ? MZ_FALSE : MZ_TRUE;
					total_lz_bytes = d->m_total_lz_bytes; pLZ_code_buf = d->m_pLZ_code_buf; pLZ_flags = d->m_pLZ_flags; num_flags_left = d->m_num_flags_left;
				}
			}

			while (lookahead_size)
			{
				mz_uint8 lit = d->m_dict[cur_pos];

				total_lz_bytes++;
				*pLZ_code_buf++ = lit;
				*pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
				if (--num_flags_left == 0) { num_flags_left = 8; pLZ_flags = pLZ_code_buf++; }

				d->m_huff_count[0][lit]++;

				lookahead_pos++;
				dict_size = MZ_MIN(dict_size + 1, TDEFL_LZ_DICT_SIZE);
				cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK;
				lookahead_size--;

				if (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8])
				{
					int n;
					d->m_lookahead_pos = lookahead_pos; d->m_lookahead_size = lookahead_size; d->m_dict_size = dict_size;
					d->m_total_lz_bytes = total_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_num_flags_left = num_flags_left;
					if ((n = tdefl_flush_block(d, 0)) != 0)
						return (n < 0) ? MZ_FALSE : MZ_TRUE;
					total_lz_bytes = d->m_total_lz_bytes; pLZ_code_buf = d->m_pLZ_code_buf; pLZ_flags = d->m_pLZ_flags; num_flags_left = d->m_num_flags_left;
				}
			}
		}

		d->m_lookahead_pos = lookahead_pos; d->m_lookahead_size = lookahead_size; d->m_dict_size = dict_size;
		d->m_total_lz_bytes = total_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_num_flags_left = num_flags_left;
		return MZ_TRUE;
	}
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

	static MZ_FORCEINLINE void tdefl_record_literal(tdefl_compressor *d, mz_uint8 lit)
	{
		d->m_total_lz_bytes++;
		*d->m_pLZ_code_buf++ = lit;
		*d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); if (--d->m_num_flags_left == 0) { d->m_num_flags_left = 8; d->m_pLZ_flags = d->m_pLZ_code_buf++; }
		d->m_huff_count[0][lit]++;
	}

	static MZ_FORCEINLINE void tdefl_record_match(tdefl_compressor *d, mz_uint match_len, mz_uint match_dist)
	{
		mz_uint32 s0, s1;

		MZ_ASSERT((match_len >= TDEFL_MIN_MATCH_LEN) && (match_dist >= 1) && (match_dist <= TDEFL_LZ_DICT_SIZE));

		d->m_total_lz_bytes += match_len;

		d->m_pLZ_code_buf[0] = (mz_uint8)(match_len - TDEFL_MIN_MATCH_LEN);

		match_dist -= 1;
		d->m_pLZ_code_buf[1] = (mz_uint8)(match_dist & 0xFF);
		d->m_pLZ_code_buf[2] = (mz_uint8)(match_dist >> 8); d->m_pLZ_code_buf += 3;

		*d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); if (--d->m_num_flags_left == 0) { d->m_num_flags_left = 8; d->m_pLZ_flags = d->m_pLZ_code_buf++; }

		s0 = s_tdefl_small_dist_sym[match_dist & 511]; s1 = s_tdefl_large_dist_sym[(match_dist >> 8) & 127];
		d->m_huff_count[1][(match_dist < 512) ? s0 : s1]++;

		if (match_len >= TDEFL_MIN_MATCH_LEN) d->m_huff_count[0][s_tdefl_len_sym[match_len - TDEFL_MIN_MATCH_LEN]]++;
	}

	static mz_bool tdefl_compress_normal(tdefl_compressor *d)
	{
		const mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_left = d->m_src_buf_left;
		tdefl_flush flush = d->m_flush;

		while ((src_buf_left) || ((flush) && (d->m_lookahead_size)))
		{
			mz_uint len_to_move, cur_match_dist, cur_match_len, cur_pos;
			// Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
			if ((d->m_lookahead_size + d->m_dict_size) >= (TDEFL_MIN_MATCH_LEN - 1))
			{
				mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK, ins_pos = d->m_lookahead_pos + d->m_lookahead_size - 2;
				mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] << TDEFL_LZ_HASH_SHIFT) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK];
				mz_uint num_bytes_to_process = (mz_uint)MZ_MIN(src_buf_left, TDEFL_MAX_MATCH_LEN - d->m_lookahead_size);
				const mz_uint8 *pSrc_end = pSrc + num_bytes_to_process;
				src_buf_left -= num_bytes_to_process;
				d->m_lookahead_size += num_bytes_to_process;
				while (pSrc != pSrc_end)
				{
					mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; if (dst_pos < (TDEFL_MAX_MATCH_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_SIZE + dst_pos] = c;
					hash = ((hash << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_SIZE - 1);
					d->m_next[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
					dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK; ins_pos++;
				}
			}
			else
			{
				while ((src_buf_left) && (d->m_lookahead_size < TDEFL_MAX_MATCH_LEN))
				{
					mz_uint8 c = *pSrc++;
					mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK;
					src_buf_left--;
					d->m_dict[dst_pos] = c;
					if (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
						d->m_dict[TDEFL_LZ_DICT_SIZE + dst_pos] = c;
					if ((++d->m_lookahead_size + d->m_dict_size) >= TDEFL_MIN_MATCH_LEN)
					{
						mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_size - 1) - 2;
						mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] << (TDEFL_LZ_HASH_SHIFT * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK] << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_SIZE - 1);
						d->m_next[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
					}
				}
			}
			d->m_dict_size = MZ_MIN(TDEFL_LZ_DICT_SIZE - d->m_lookahead_size, d->m_dict_size);
			if ((!flush) && (d->m_lookahead_size < TDEFL_MAX_MATCH_LEN))
				break;

			// Simple lazy/greedy parsing state machine.
			len_to_move = 1; cur_match_dist = 0; cur_match_len = d->m_saved_match_len ? d->m_saved_match_len : (TDEFL_MIN_MATCH_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK;
			if (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS))
			{
				if ((d->m_dict_size) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS)))
				{
					mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_SIZE_MASK];
					cur_match_len = 0; while (cur_match_len < d->m_lookahead_size) { if (d->m_dict[cur_pos + cur_match_len] != c) break; cur_match_len++; }
					if (cur_match_len < TDEFL_MIN_MATCH_LEN) cur_match_len = 0; else cur_match_dist = 1;
				}
			}
			else
			{
				tdefl_find_match(d, d->m_lookahead_pos, d->m_dict_size, d->m_lookahead_size, &cur_match_dist, &cur_match_len);
			}
			if (((cur_match_len == TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 8U * 1024U)) || (cur_pos == cur_match_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_match_len <= 5)))
			{
				cur_match_dist = cur_match_len = 0;
			}
			if (d->m_saved_match_len)
			{
				if (cur_match_len > d->m_saved_match_len)
				{
					tdefl_record_literal(d, (mz_uint8)d->m_saved_lit);
					if (cur_match_len >= 128)
					{
						tdefl_record_match(d, cur_match_len, cur_match_dist);
						d->m_saved_match_len = 0; len_to_move = cur_match_len;
					}
					else
					{
						d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_match_dist = cur_match_dist; d->m_saved_match_len = cur_match_len;
					}
				}
				else
				{
					tdefl_record_match(d, d->m_saved_match_len, d->m_saved_match_dist);
					len_to_move = d->m_saved_match_len - 1; d->m_saved_match_len = 0;
				}
			}
			else if (!cur_match_dist)
				tdefl_record_literal(d, d->m_dict[MZ_MIN(cur_pos, sizeof(d->m_dict) - 1)]);
			else if ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_match_len >= 128))
			{
				tdefl_record_match(d, cur_match_len, cur_match_dist);
				len_to_move = cur_match_len;
			}
			else
			{
				d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, sizeof(d->m_dict) - 1)]; d->m_saved_match_dist = cur_match_dist; d->m_saved_match_len = cur_match_len;
			}
			// Move the lookahead forward by len_to_move bytes.
			d->m_lookahead_pos += len_to_move;
			MZ_ASSERT(d->m_lookahead_size >= len_to_move);
			d->m_lookahead_size -= len_to_move;
			d->m_dict_size = MZ_MIN(d->m_dict_size + len_to_move, TDEFL_LZ_DICT_SIZE);
			// Check if it's time to flush the current LZ codes to the internal output buffer.
			if ((d->m_pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8]) ||
				((d->m_total_lz_bytes > 31 * 1024) && (((((mz_uint)(d->m_pLZ_code_buf - d->m_lz_code_buf) * 115) >> 7) >= d->m_total_lz_bytes) || (d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS))))
			{
				int n;
				d->m_pSrc = pSrc; d->m_src_buf_left = src_buf_left;
				if ((n = tdefl_flush_block(d, 0)) != 0)
					return (n < 0) ? MZ_FALSE : MZ_TRUE;
			}
		}

		d->m_pSrc = pSrc; d->m_src_buf_left = src_buf_left;
		return MZ_TRUE;
	}

	static tdefl_status tdefl_flush_output_buffer(tdefl_compressor *d)
	{
		if (d->m_pIn_buf_size)
		{
			*d->m_pIn_buf_size = d->m_pSrc - (const mz_uint8 *)d->m_pIn_buf;
		}

		if (d->m_pOut_buf_size)
		{
			size_t n = MZ_MIN(*d->m_pOut_buf_size - d->m_out_buf_ofs, d->m_output_flush_remaining);
			memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
			d->m_output_flush_ofs += (mz_uint)n;
			d->m_output_flush_remaining -= (mz_uint)n;
			d->m_out_buf_ofs += n;

			*d->m_pOut_buf_size = d->m_out_buf_ofs;
		}

		return (d->m_finished && !d->m_output_flush_remaining) ? TDEFL_STATUS_DONE : TDEFL_STATUS_OKAY;
	}

	tdefl_status tdefl_compress(tdefl_compressor *d, const void *pIn_buf, size_t *pIn_buf_size, void *pOut_buf, size_t *pOut_buf_size, tdefl_flush flush)
	{
		if (!d)
		{
			if (pIn_buf_size) *pIn_buf_size = 0;
			if (pOut_buf_size) *pOut_buf_size = 0;
			return TDEFL_STATUS_BAD_PARAM;
		}

		d->m_pIn_buf = pIn_buf; d->m_pIn_buf_size = pIn_buf_size;
		d->m_pOut_buf = pOut_buf; d->m_pOut_buf_size = pOut_buf_size;
		d->m_pSrc = (const mz_uint8 *)(pIn_buf); d->m_src_buf_left = pIn_buf_size ? *pIn_buf_size : 0;
		d->m_out_buf_ofs = 0;
		d->m_flush = flush;

		if (((d->m_pPut_buf_func != NULL) == ((pOut_buf != NULL) || (pOut_buf_size != NULL))) || (d->m_prev_return_status != TDEFL_STATUS_OKAY) ||
			(d->m_wants_to_finish && (flush != TDEFL_FINISH)) || (pIn_buf_size && *pIn_buf_size && !pIn_buf) || (pOut_buf_size && *pOut_buf_size && !pOut_buf))
		{
			if (pIn_buf_size) *pIn_buf_size = 0;
			if (pOut_buf_size) *pOut_buf_size = 0;
			return (d->m_prev_return_status = TDEFL_STATUS_BAD_PARAM);
		}
		d->m_wants_to_finish |= (flush == TDEFL_FINISH);

		if ((d->m_output_flush_remaining) || (d->m_finished))
			return (d->m_prev_return_status = tdefl_flush_output_buffer(d));

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
		if (((d->m_flags & TDEFL_MAX_PROBES_MASK) == 1) &&
			((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
			((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS | TDEFL_RLE_MATCHES)) == 0))
		{
			if (!tdefl_compress_fast(d))
				return d->m_prev_return_status;
		}
		else
#endif // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
		{
			if (!tdefl_compress_normal(d))
				return d->m_prev_return_status;
		}

		if ((d->m_flags & (TDEFL_WRITE_ZLIB_HEADER | TDEFL_COMPUTE_ADLER32)) && (pIn_buf))
			d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (const mz_uint8 *)pIn_buf, d->m_pSrc - (const mz_uint8 *)pIn_buf);

		if ((flush) && (!d->m_lookahead_size) && (!d->m_src_buf_left) && (!d->m_output_flush_remaining))
		{
			if (tdefl_flush_block(d, flush) < 0)
				return d->m_prev_return_status;
			d->m_finished = (flush == TDEFL_FINISH);
			if (flush == TDEFL_FULL_FLUSH) { MZ_CLEAR_OBJ(d->m_hash); MZ_CLEAR_OBJ(d->m_next); d->m_dict_size = 0; }
		}

		return (d->m_prev_return_status = tdefl_flush_output_buffer(d));
	}

	tdefl_status tdefl_compress_buffer(tdefl_compressor *d, const void *pIn_buf, size_t in_buf_size, tdefl_flush flush)
	{
		MZ_ASSERT(d->m_pPut_buf_func); return tdefl_compress(d, pIn_buf, &in_buf_size, NULL, NULL, flush);
	}

	tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags)
	{
		d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
		d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
		d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
		if (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_OBJ(d->m_hash);
		d->m_lookahead_pos = d->m_lookahead_size = d->m_dict_size = d->m_total_lz_bytes = d->m_lz_code_buf_dict_pos = d->m_bits_in = 0;
		d->m_output_flush_ofs = d->m_output_flush_remaining = d->m_finished = d->m_block_index = d->m_bit_buffer = d->m_wants_to_finish = 0;
		d->m_pLZ_code_buf = d->m_lz_code_buf + 1; d->m_pLZ_flags = d->m_lz_code_buf; d->m_num_flags_left = 8;
		d->m_pOutput_buf = d->m_output_buf; d->m_pOutput_buf_end = d->m_output_buf; d->m_prev_return_status = TDEFL_STATUS_OKAY;
		d->m_saved_match_dist = d->m_saved_match_len = d->m_saved_lit = 0; d->m_adler32 = 1;
		d->m_pIn_buf = NULL; d->m_pOut_buf = NULL;
		d->m_pIn_buf_size = NULL; d->m_pOut_buf_size = NULL;
		d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = NULL; d->m_src_buf_left = 0; d->m_out_buf_ofs = 0;
		memset(&d->m_huff_count[0][0], 0, sizeof(d->m_huff_count[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
		memset(&d->m_huff_count[1][0], 0, sizeof(d->m_huff_count[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
		return TDEFL_STATUS_OKAY;
	}

	tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d)
	{
		return d->m_prev_return_status;
	}

	mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
	{
		return d->m_adler32;
	}

	mz_bool tdefl_compress_mem_to_output(const void *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, void *pPut_buf_user, int flags)
	{
		tdefl_compressor *pComp; mz_bool succeeded; if (((buf_len) && (!pBuf)) || (!pPut_buf_func)) return MZ_FALSE;
		pComp = (tdefl_compressor*)MZ_MALLOC(sizeof(tdefl_compressor)); if (!pComp) return MZ_FALSE;
		succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_STATUS_OKAY);
		succeeded = succeeded && (tdefl_compress_buffer(pComp, pBuf, buf_len, TDEFL_FINISH) == TDEFL_STATUS_DONE);
		MZ_FREE(pComp); return succeeded;
	}

	typedef struct
	{
		size_t m_size, m_capacity;
		mz_uint8 *m_pBuf;
		mz_bool m_expandable;
	} tdefl_output_buffer;

	static mz_bool tdefl_output_buffer_putter(const void *pBuf, int len, void *pUser)
	{
		tdefl_output_buffer *p = (tdefl_output_buffer *)pUser;
		size_t new_size = p->m_size + len;
		if (new_size > p->m_capacity)
		{
			size_t new_capacity = p->m_capacity; mz_uint8 *pNew_buf; if (!p->m_expandable) return MZ_FALSE;
			do { new_capacity = MZ_MAX(128U, new_capacity << 1U); } while (new_size > new_capacity);
			pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_capacity); if (!pNew_buf) return MZ_FALSE;
			p->m_pBuf = pNew_buf; p->m_capacity = new_capacity;
		}
		memcpy((mz_uint8*)p->m_pBuf + p->m_size, pBuf, len); p->m_size = new_size;
		return MZ_TRUE;
	}

	void *tdefl_compress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len, size_t *pOut_len, int flags)
	{
		tdefl_output_buffer out_buf; MZ_CLEAR_OBJ(out_buf);
		if (!pOut_len) return MZ_FALSE; else *pOut_len = 0;
		out_buf.m_expandable = MZ_TRUE;
		if (!tdefl_compress_mem_to_output(pSrc_buf, src_buf_len, tdefl_output_buffer_putter, &out_buf, flags)) return NULL;
		*pOut_len = out_buf.m_size; return out_buf.m_pBuf;
	}

	size_t tdefl_compress_mem_to_mem(void *pOut_buf, size_t out_buf_len, const void *pSrc_buf, size_t src_buf_len, int flags)
	{
		tdefl_output_buffer out_buf; MZ_CLEAR_OBJ(out_buf);
		if (!pOut_buf) return 0;
		out_buf.m_pBuf = (mz_uint8*)pOut_buf; out_buf.m_capacity = out_buf_len;
		if (!tdefl_compress_mem_to_output(pSrc_buf, src_buf_len, tdefl_output_buffer_putter, &out_buf, flags)) return 0;
		return out_buf.m_size;
	}

#ifndef MINIZ_NO_ZLIB_APIS
	static const mz_uint s_tdefl_num_probes[11] = { 0, 1, 6, 32, 16, 32, 128, 256, 512, 768, 1500 };

	// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
	mz_uint tdefl_create_comp_flags_from_zip_params(int level, int window_bits, int strategy)
	{
		mz_uint comp_flags = s_tdefl_num_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
		if (window_bits > 0) comp_flags |= TDEFL_WRITE_ZLIB_HEADER;

		if (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_BLOCKS;
		else if (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
		else if (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_MASK;
		else if (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_BLOCKS;
		else if (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

		return comp_flags;
	}
#endif //MINIZ_NO_ZLIB_APIS

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#endif

	// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
	// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
	// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
	void *tdefl_write_image_to_png_file_in_memory_ex(const void *pImage, int w, int h, int num_chans, size_t *pLen_out, mz_uint level, mz_bool flip)
	{
		// Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
		static const mz_uint s_tdefl_png_num_probes[11] = { 0, 1, 6, 32, 16, 32, 128, 256, 512, 768, 1500 };
		tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(sizeof(tdefl_compressor)); tdefl_output_buffer out_buf; int i, bpl = w * num_chans, y, z; mz_uint32 c; *pLen_out = 0;
		if (!pComp) return NULL;
		MZ_CLEAR_OBJ(out_buf); out_buf.m_expandable = MZ_TRUE; out_buf.m_capacity = 57 + MZ_MAX(64, (1 + bpl)*h); if (NULL == (out_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(out_buf.m_capacity))) { MZ_FREE(pComp); return NULL; }
		// write dummy header
		for (z = 41; z; --z) tdefl_output_buffer_putter(&z, 1, &out_buf);
		// compress image data
		tdefl_init(pComp, tdefl_output_buffer_putter, &out_buf, s_tdefl_png_num_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_HEADER);
		for (y = 0; y < h; ++y) { tdefl_compress_buffer(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_buffer(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, bpl, TDEFL_NO_FLUSH); }
		if (tdefl_compress_buffer(pComp, NULL, 0, TDEFL_FINISH) != TDEFL_STATUS_DONE) { MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); return NULL; }
		// write real header
		*pLen_out = out_buf.m_size - 41;
		{
			static const mz_uint8 chans[] = { 0x00, 0x00, 0x04, 0x02, 0x06 };
			mz_uint8 pnghdr[41] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52,
				0, 0, (mz_uint8)(w >> 8), (mz_uint8)w, 0, 0, (mz_uint8)(h >> 8), (mz_uint8)h, 8, chans[num_chans], 0, 0, 0, 0, 0, 0, 0,
				(mz_uint8)(*pLen_out >> 24), (mz_uint8)(*pLen_out >> 16), (mz_uint8)(*pLen_out >> 8), (mz_uint8)*pLen_out, 0x49, 0x44, 0x41, 0x54 };
			c = (mz_uint32)mz_crc32(MZ_CRC32_INIT, pnghdr + 12, 17); for (i = 0; i<4; ++i, c <<= 8) ((mz_uint8*)(pnghdr + 29))[i] = (mz_uint8)(c >> 24);
			memcpy(out_buf.m_pBuf, pnghdr, 41);
		}
		// write footer (IDAT CRC-32, followed by IEND chunk)
		if (!tdefl_output_buffer_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); return NULL; }
		c = (mz_uint32)mz_crc32(MZ_CRC32_INIT, out_buf.m_pBuf + 41 - 4, *pLen_out + 4); for (i = 0; i<4; ++i, c <<= 8) (out_buf.m_pBuf + out_buf.m_size - 16)[i] = (mz_uint8)(c >> 24);
		// compute final size of file, grab compressed data buffer and return
		*pLen_out += 57; MZ_FREE(pComp); return out_buf.m_pBuf;
	}
	void *tdefl_write_image_to_png_file_in_memory(const void *pImage, int w, int h, int num_chans, size_t *pLen_out)
	{
		// Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
		return tdefl_write_image_to_png_file_in_memory_ex(pImage, w, h, num_chans, pLen_out, 6, MZ_FALSE);
	}

#ifdef _MSC_VER
#pragma warning (pop)
#endif

	// ------------------- .ZIP archive reading

#ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef MINIZ_NO_STDIO
#define MZ_FILE void *
#else
#include <stdio.h>
#include <sys/stat.h>

#if defined(_MSC_VER) || defined(__MINGW64__)
	static FILE *mz_fopen(const char *pFilename, const char *pMode)
	{
		FILE* pFile = NULL;
		fopen_s(&pFile, pFilename, pMode);
		return pFile;
	}
	static FILE *mz_freopen(const char *pPath, const char *pMode, FILE *pStream)
	{
		FILE* pFile = NULL;
		if (freopen_s(&pFile, pPath, pMode, pStream))
			return NULL;
		return pFile;
	}
#ifndef MINIZ_NO_TIME
#include <sys/utime.h>
#endif
#define MZ_FILE FILE
#define MZ_FOPEN mz_fopen
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 _ftelli64
#define MZ_FSEEK64 _fseeki64
#define MZ_FILE_STAT_STRUCT _stat
#define MZ_FILE_STAT _stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN mz_freopen
#define MZ_DELETE_FILE remove
#elif defined(__MINGW32__)
#ifndef MINIZ_NO_TIME
#include <sys/utime.h>
#endif
#define MZ_FILE FILE
#define MZ_FOPEN(f, m) fopen(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftello64
#define MZ_FSEEK64 fseeko64
#define MZ_FILE_STAT_STRUCT _stat
#define MZ_FILE_STAT _stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(f, m, s) freopen(f, m, s)
#define MZ_DELETE_FILE remove
#elif defined(__TINYC__)
#ifndef MINIZ_NO_TIME
#include <sys/utime.h>
#endif
#define MZ_FILE FILE
#define MZ_FOPEN(f, m) fopen(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftell
#define MZ_FSEEK64 fseek
#define MZ_FILE_STAT_STRUCT stat
#define MZ_FILE_STAT stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(f, m, s) freopen(f, m, s)
#define MZ_DELETE_FILE remove
#elif defined(__GNUC__) && _LARGEFILE64_SOURCE
#ifndef MINIZ_NO_TIME
#include <utime.h>
#endif
#define MZ_FILE FILE
#define MZ_FOPEN(f, m) fopen64(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftello64
#define MZ_FSEEK64 fseeko64
#define MZ_FILE_STAT_STRUCT stat64
#define MZ_FILE_STAT stat64
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(p, m, s) freopen64(p, m, s)
#define MZ_DELETE_FILE remove
#else
#ifndef MINIZ_NO_TIME
#include <utime.h>
#endif
#define MZ_FILE FILE
#define MZ_FOPEN(f, m) fopen(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftello
#define MZ_FSEEK64 fseeko
#define MZ_FILE_STAT_STRUCT stat
#define MZ_FILE_STAT stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(f, m, s) freopen(f, m, s)
#define MZ_DELETE_FILE remove
#endif // #ifdef _MSC_VER
#endif // #ifdef MINIZ_NO_STDIO

#define MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

	// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
	enum
	{
		// ZIP archive identifiers and record sizes
		MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_HEADER_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_HEADER_SIG = 0x04034b50,
		MZ_ZIP_LOCAL_DIR_HEADER_SIZE = 30, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE = 46, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE = 22,
		// Central directory header record offsets
		MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_VERSION_MADE_BY_OFS = 4, MZ_ZIP_CDH_VERSION_NEEDED_OFS = 6, MZ_ZIP_CDH_BIT_FLAG_OFS = 8,
		MZ_ZIP_CDH_METHOD_OFS = 10, MZ_ZIP_CDH_FILE_TIME_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_CRC32_OFS = 16,
		MZ_ZIP_CDH_COMPRESSED_SIZE_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
		MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_START_OFS = 34, MZ_ZIP_CDH_INTERNAL_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_HEADER_OFS = 42,
		// Local directory header offsets
		MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_VERSION_NEEDED_OFS = 4, MZ_ZIP_LDH_BIT_FLAG_OFS = 6, MZ_ZIP_LDH_METHOD_OFS = 8, MZ_ZIP_LDH_FILE_TIME_OFS = 10,
		MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_CRC32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_SIZE_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_SIZE_OFS = 22,
		MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
		// End of central directory offsets
		MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_NUM_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_NUM_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS = 8,
		MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_SIZE_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_SIZE_OFS = 20,
	};

	typedef struct
	{
		void *m_p;
		size_t m_size, m_capacity;
		mz_uint m_element_size;
	} mz_zip_array;

	struct mz_zip_internal_state_tag
	{
		mz_zip_array m_central_dir;
		mz_zip_array m_central_dir_offsets;
		mz_zip_array m_sorted_central_dir_offsets;
		MZ_FILE *m_pFile;
		void *m_pMem;
		size_t m_mem_size;
		size_t m_mem_capacity;
	};

#define MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(array_ptr, element_size) (array_ptr)->m_element_size = element_size
#define MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, index) ((element_type *)((array_ptr)->m_p))[index]

	static MZ_FORCEINLINE void mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
	{
		pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
		memset(pArray, 0, sizeof(mz_zip_array));
	}

	static mz_bool mz_zip_array_ensure_capacity(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_capacity, mz_uint growing)
	{
		void *pNew_p; size_t new_capacity = min_new_capacity; MZ_ASSERT(pArray->m_element_size); if (pArray->m_capacity >= min_new_capacity) return MZ_TRUE;
		if (growing) { new_capacity = MZ_MAX(1, pArray->m_capacity); while (new_capacity < min_new_capacity) new_capacity *= 2; }
		if (NULL == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_size, new_capacity))) return MZ_FALSE;
		pArray->m_p = pNew_p; pArray->m_capacity = new_capacity;
		return MZ_TRUE;
	}

	static MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_capacity, mz_uint growing)
	{
		if (new_capacity > pArray->m_capacity) { if (!mz_zip_array_ensure_capacity(pZip, pArray, new_capacity, growing)) return MZ_FALSE; }
		return MZ_TRUE;
	}

	static MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_size, mz_uint growing)
	{
		if (new_size > pArray->m_capacity) { if (!mz_zip_array_ensure_capacity(pZip, pArray, new_size, growing)) return MZ_FALSE; }
		pArray->m_size = new_size;
		return MZ_TRUE;
	}

	static MZ_FORCEINLINE mz_bool mz_zip_array_ensure_room(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
	{
		return mz_zip_array_reserve(pZip, pArray, pArray->m_size + n, MZ_TRUE);
	}

	static MZ_FORCEINLINE mz_bool mz_zip_array_push_back(mz_zip_archive *pZip, mz_zip_array *pArray, const void *pElements, size_t n)
	{
		size_t orig_size = pArray->m_size; if (!mz_zip_array_resize(pZip, pArray, orig_size + n, MZ_TRUE)) return MZ_FALSE;
		memcpy((mz_uint8*)pArray->m_p + orig_size * pArray->m_element_size, pElements, n * pArray->m_element_size);
		return MZ_TRUE;
	}

#ifndef MINIZ_NO_TIME
	static time_t mz_zip_dos_to_time_t(int dos_time, int dos_date)
	{
		struct tm tm;
		memset(&tm, 0, sizeof(tm)); tm.tm_isdst = -1;
		tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
		tm.tm_hour = (dos_time >> 11) & 31; tm.tm_min = (dos_time >> 5) & 63; tm.tm_sec = (dos_time << 1) & 62;
		return mktime(&tm);
	}

	static void mz_zip_time_to_dos_time(time_t time, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
	{
#ifdef _MSC_VER
		struct tm tm_struct;
		struct tm *tm = &tm_struct;
		errno_t err = localtime_s(tm, &time);
		if (err)
		{
			*pDOS_date = 0; *pDOS_time = 0;
			return;
		}
#else
		struct tm *tm = localtime(&time);
#endif
		*pDOS_time = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
		*pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
	}
#endif

#ifndef MINIZ_NO_STDIO
	static mz_bool mz_zip_get_file_modified_time(const char *pFilename, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
	{
#ifdef MINIZ_NO_TIME
		(void)pFilename; *pDOS_date = *pDOS_time = 0;
#else
		struct MZ_FILE_STAT_STRUCT file_stat;
		// On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
		if (MZ_FILE_STAT(pFilename, &file_stat) != 0)
			return MZ_FALSE;
		mz_zip_time_to_dos_time(file_stat.st_mtime, pDOS_time, pDOS_date);
#endif // #ifdef MINIZ_NO_TIME
		return MZ_TRUE;
	}

#ifndef MINIZ_NO_TIME
	static mz_bool mz_zip_set_file_times(const char *pFilename, time_t access_time, time_t modified_time)
	{
		struct utimbuf t; t.actime = access_time; t.modtime = modified_time;
		return !utime(pFilename, &t);
	}
#endif // #ifndef MINIZ_NO_TIME
#endif // #ifndef MINIZ_NO_STDIO

	static mz_bool mz_zip_reader_init_internal(mz_zip_archive *pZip, mz_uint32 flags)
	{
		(void)flags;
		if ((!pZip) || (pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
			return MZ_FALSE;

		if (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
		if (!pZip->m_pFree) pZip->m_pFree = def_free_func;
		if (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

		pZip->m_zip_mode = MZ_ZIP_MODE_READING;
		pZip->m_archive_size = 0;
		pZip->m_central_directory_file_ofs = 0;
		pZip->m_total_files = 0;

		if (NULL == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, sizeof(mz_zip_internal_state))))
			return MZ_FALSE;
		memset(pZip->m_pState, 0, sizeof(mz_zip_internal_state));
		MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir, sizeof(mz_uint8));
		MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir_offsets, sizeof(mz_uint32));
		MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_sorted_central_dir_offsets, sizeof(mz_uint32));
		return MZ_TRUE;
	}

	static MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(const mz_zip_array *pCentral_dir_array, const mz_zip_array *pCentral_dir_offsets, mz_uint l_index, mz_uint r_index)
	{
		const mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_index)), *pE;
		const mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_index));
		mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
		mz_uint8 l = 0, r = 0;
		pL += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE; pR += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
		pE = pL + MZ_MIN(l_len, r_len);
		while (pL < pE)
		{
			if ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
				break;
			pL++; pR++;
		}
		return (pL == pE) ? (l_len < r_len) : (l < r);
	}

#define MZ_SWAP_UINT32(a, b) do { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_END

	// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
	static void mz_zip_reader_sort_central_dir_offsets_by_filename(mz_zip_archive *pZip)
	{
		mz_zip_internal_state *pState = pZip->m_pState;
		const mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
		const mz_zip_array *pCentral_dir = &pState->m_central_dir;
		mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
		const int size = pZip->m_total_files;
		int start = (size - 2) >> 1, end;
		while (start >= 0)
		{
			int child, root = start;
			for (;;)
			{
				if ((child = (root << 1) + 1) >= size)
					break;
				child += (((child + 1) < size) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1])));
				if (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[root], pIndices[child]))
					break;
				MZ_SWAP_UINT32(pIndices[root], pIndices[child]); root = child;
			}
			start--;
		}

		end = size - 1;
		while (end > 0)
		{
			int child, root = 0;
			MZ_SWAP_UINT32(pIndices[end], pIndices[0]);
			for (;;)
			{
				if ((child = (root << 1) + 1) >= end)
					break;
				child += (((child + 1) < end) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1]));
				if (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[root], pIndices[child]))
					break;
				MZ_SWAP_UINT32(pIndices[root], pIndices[child]); root = child;
			}
			end--;
		}
	}

	static mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
	{
		mz_uint cdir_size, num_this_disk, cdir_disk_index;
		mz_uint64 cdir_ofs;
		mz_int64 cur_file_ofs;
		const mz_uint8 *p;
		mz_uint32 buf_u32[4096 / sizeof(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
		mz_bool sort_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY) == 0);
		// Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
		if (pZip->m_archive_size < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
			return MZ_FALSE;
		// Find the end of central directory record by scanning the file from the end towards the beginning.
		cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_size - (mz_int64)sizeof(buf_u32), 0);
		for (;;)
		{
			int i, n = (int)MZ_MIN(sizeof(buf_u32), pZip->m_archive_size - cur_file_ofs);
			if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
				return MZ_FALSE;
			for (i = n - 4; i >= 0; --i)
				if (MZ_READ_LE32(pBuf + i) == MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG)
					break;
			if (i >= 0)
			{
				cur_file_ofs += i;
				break;
			}
			if ((!cur_file_ofs) || ((pZip->m_archive_size - cur_file_ofs) >= (0xFFFF + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)))
				return MZ_FALSE;
			cur_file_ofs = MZ_MAX(cur_file_ofs - (sizeof(buf_u32) - 3), 0);
		}
		// Read and verify the end of central directory record.
		if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) != MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
			return MZ_FALSE;
		if ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG) ||
			((pZip->m_total_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS)))
			return MZ_FALSE;

		num_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_NUM_THIS_DISK_OFS);
		cdir_disk_index = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_NUM_DISK_CDIR_OFS);
		if (((num_this_disk | cdir_disk_index) != 0) && ((num_this_disk != 1) || (cdir_disk_index != 1)))
			return MZ_FALSE;

		if ((cdir_size = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_SIZE_OFS)) < pZip->m_total_files * MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)
			return MZ_FALSE;

		cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
		if ((cdir_ofs + (mz_uint64)cdir_size) > pZip->m_archive_size)
			return MZ_FALSE;

		pZip->m_central_directory_file_ofs = cdir_ofs;

		if (pZip->m_total_files)
		{
			mz_uint i, n;

			// Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
			if ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_size, MZ_FALSE)) ||
				(!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_total_files, MZ_FALSE)))
				return MZ_FALSE;

			if (sort_central_dir)
			{
				if (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_total_files, MZ_FALSE))
					return MZ_FALSE;
			}

			if (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_size) != cdir_size)
				return MZ_FALSE;

			// Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
			p = (const mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
			for (n = cdir_size, i = 0; i < pZip->m_total_files; ++i)
			{
				mz_uint total_header_size, comp_size, decomp_size, disk_index;
				if ((n < MZ_ZIP_CENTRAL_DIR_HEADER_SIZE) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_HEADER_SIG))
					return MZ_FALSE;
				MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (const mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
				if (sort_central_dir)
					MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
				comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
				decomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);
				if (((!MZ_READ_LE32(p + MZ_ZIP_CDH_METHOD_OFS)) && (decomp_size != comp_size)) || (decomp_size && !comp_size) || (decomp_size == 0xFFFFFFFF) || (comp_size == 0xFFFFFFFF))
					return MZ_FALSE;
				disk_index = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_START_OFS);
				if ((disk_index != num_this_disk) && (disk_index != 1))
					return MZ_FALSE;
				if (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS) + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + comp_size) > pZip->m_archive_size)
					return MZ_FALSE;
				if ((total_header_size = MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
					return MZ_FALSE;
				n -= total_header_size; p += total_header_size;
			}
		}

		if (sort_central_dir)
			mz_zip_reader_sort_central_dir_offsets_by_filename(pZip);

		return MZ_TRUE;
	}

	mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size, mz_uint32 flags)
	{
		if ((!pZip) || (!pZip->m_pRead))
			return MZ_FALSE;
		if (!mz_zip_reader_init_internal(pZip, flags))
			return MZ_FALSE;
		pZip->m_archive_size = size;
		if (!mz_zip_reader_read_central_dir(pZip, flags))
		{
			mz_zip_reader_end(pZip);
			return MZ_FALSE;
		}
		return MZ_TRUE;
	}

	static size_t mz_zip_mem_read_func(void *pOpaque, mz_uint64 file_ofs, void *pBuf, size_t n)
	{
		mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
		size_t s = (file_ofs >= pZip->m_archive_size) ? 0 : (size_t)MZ_MIN(pZip->m_archive_size - file_ofs, n);
		memcpy(pBuf, (const mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
		return s;
	}

	mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, const void *pMem, size_t size, mz_uint32 flags)
	{
		if (!mz_zip_reader_init_internal(pZip, flags))
			return MZ_FALSE;
		pZip->m_archive_size = size;
		pZip->m_pRead = mz_zip_mem_read_func;
		pZip->m_pIO_opaque = pZip;
#ifdef __cplusplus
		pZip->m_pState->m_pMem = const_cast<void *>(pMem);
#else
		pZip->m_pState->m_pMem = (void *)pMem;
#endif
		pZip->m_pState->m_mem_size = size;
		if (!mz_zip_reader_read_central_dir(pZip, flags))
		{
			mz_zip_reader_end(pZip);
			return MZ_FALSE;
		}
		return MZ_TRUE;
	}

#ifndef MINIZ_NO_STDIO
	static size_t mz_zip_file_read_func(void *pOpaque, mz_uint64 file_ofs, void *pBuf, size_t n)
	{
		mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
		mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
		if (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
			return 0;
		return MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
	}

	mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, const char *pFilename, mz_uint32 flags)
	{
		mz_uint64 file_size;
		MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
		if (!pFile)
			return MZ_FALSE;
		if (MZ_FSEEK64(pFile, 0, SEEK_END))
		{
			MZ_FCLOSE(pFile);
			return MZ_FALSE;
		}
		file_size = MZ_FTELL64(pFile);
		if (!mz_zip_reader_init_internal(pZip, flags))
		{
			MZ_FCLOSE(pFile);
			return MZ_FALSE;
		}
		pZip->m_pRead = mz_zip_file_read_func;
		pZip->m_pIO_opaque = pZip;
		pZip->m_pState->m_pFile = pFile;
		pZip->m_archive_size = file_size;
		if (!mz_zip_reader_read_central_dir(pZip, flags))
		{
			mz_zip_reader_end(pZip);
			return MZ_FALSE;
		}
		return MZ_TRUE;
	}
#endif // #ifndef MINIZ_NO_STDIO

	mz_uint mz_zip_reader_get_num_files(mz_zip_archive *pZip)
	{
		return pZip ? pZip->m_total_files : 0;
	}

	static MZ_FORCEINLINE const mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_index)
	{
		if ((!pZip) || (!pZip->m_pState) || (file_index >= pZip->m_total_files) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
			return NULL;
		return &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_index));
	}

	mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_index)
	{
		mz_uint m_bit_flag;
		const mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
		if (!p)
			return MZ_FALSE;
		m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
		return (m_bit_flag & 1);
	}

	mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_index)
	{
		mz_uint filename_len, external_attr;
		const mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
		if (!p)
			return MZ_FALSE;

		// First see if the filename ends with a '/' character.
		filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
		if (filename_len)
		{
			if (*(p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_len - 1) == '/')
				return MZ_TRUE;
		}

		// Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
		// Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
		// FIXME: Remove this check? Is it necessary - we already check the filename.
		external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
		if ((external_attr & 0x10) != 0)
			return MZ_TRUE;

		return MZ_FALSE;
	}

	mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index, mz_zip_archive_file_stat *pStat)
	{
		mz_uint n;
		const mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
		if ((!p) || (!pStat))
			return MZ_FALSE;

		// Unpack the central directory record.
		pStat->m_file_index = file_index;
		pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_index);
		pStat->m_version_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_MADE_BY_OFS);
		pStat->m_version_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_NEEDED_OFS);
		pStat->m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
		pStat->m_method = MZ_READ_LE16(p + MZ_ZIP_CDH_METHOD_OFS);
#ifndef MINIZ_NO_TIME
		pStat->m_time = mz_zip_dos_to_time_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_TIME_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#endif
		pStat->m_crc32 = MZ_READ_LE32(p + MZ_ZIP_CDH_CRC32_OFS);
		pStat->m_comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
		pStat->m_uncomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);
		pStat->m_internal_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_INTERNAL_ATTR_OFS);
		pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
		pStat->m_local_header_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS);

		// Copy as much of the filename and comment as possible.
		n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE - 1);
		memcpy(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n); pStat->m_filename[n] = '\0';

		n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE - 1);
		pStat->m_comment_size = n;
		memcpy(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

		return MZ_TRUE;
	}

	mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index, char *pFilename, mz_uint filename_buf_size)
	{
		mz_uint n;
		const mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
		if (!p) { if (filename_buf_size) pFilename[0] = '\0'; return 0; }
		n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
		if (filename_buf_size)
		{
			n = MZ_MIN(n, filename_buf_size - 1);
			memcpy(pFilename, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n);
			pFilename[n] = '\0';
		}
		return n + 1;
	}

	static MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(const char *pA, const char *pB, mz_uint len, mz_uint flags)
	{
		mz_uint i;
		if (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
			return 0 == memcmp(pA, pB, len);
		for (i = 0; i < len; ++i)
			if (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
				return MZ_FALSE;
		return MZ_TRUE;
	}

	static MZ_FORCEINLINE int mz_zip_reader_filename_compare(const mz_zip_array *pCentral_dir_array, const mz_zip_array *pCentral_dir_offsets, mz_uint l_index, const char *pR, mz_uint r_len)
	{
		const mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_index)), *pE;
		mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
		mz_uint8 l = 0, r = 0;
		pL += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
		pE = pL + MZ_MIN(l_len, r_len);
		while (pL < pE)
		{
			if ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
				break;
			pL++; pR++;
		}
		return (pL == pE) ? (int)(l_len - r_len) : (l - r);
	}

	static int mz_zip_reader_locate_file_binary_search(mz_zip_archive *pZip, const char *pFilename)
	{
		mz_zip_internal_state *pState = pZip->m_pState;
		const mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
		const mz_zip_array *pCentral_dir = &pState->m_central_dir;
		mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
		const int size = pZip->m_total_files;
		const mz_uint filename_len = (mz_uint)strlen(pFilename);
		int l = 0, h = size - 1;
		while (l <= h)
		{
			int m = (l + h) >> 1, file_index = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_index, pFilename, filename_len);
			if (!comp)
				return file_index;
			else if (comp < 0)
				l = m + 1;
			else
				h = m - 1;
		}
		return -1;
	}

	int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName, const char *pComment, mz_uint flags)
	{
		mz_uint file_index; size_t name_len, comment_len;
		if ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
			return -1;
		if (((flags & (MZ_ZIP_FLAG_IGNORE_PATH | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_size))
			return mz_zip_reader_locate_file_binary_search(pZip, pName);
		name_len = strlen(pName); if (name_len > 0xFFFF) return -1;
		comment_len = pComment ? strlen(pComment) : 0; if (comment_len > 0xFFFF) return -1;
		for (file_index = 0; file_index < pZip->m_total_files; file_index++)
		{
			const mz_uint8 *pHeader = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_index));
			mz_uint filename_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_FILENAME_LEN_OFS);
			const char *pFilename = (const char *)pHeader + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
			if (filename_len < name_len)
				continue;
			if (comment_len)
			{
				mz_uint file_extra_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_COMMENT_LEN_OFS);
				const char *pFile_comment = pFilename + filename_len + file_extra_len;
				if ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
					continue;
			}
			if ((flags & MZ_ZIP_FLAG_IGNORE_PATH) && (filename_len))
			{
				int ofs = filename_len - 1;
				do
				{
					if ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
						break;
				} while (--ofs >= 0);
				ofs++;
				pFilename += ofs; filename_len -= ofs;
			}
			if ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
				return file_index;
		}
		return -1;
	}

	mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_index, void *pBuf, size_t buf_size, mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size)
	{
		int status = TINFL_STATUS_DONE;
		mz_uint64 needed_size, cur_file_ofs, comp_remaining, out_buf_ofs = 0, read_buf_size, read_buf_ofs = 0, read_buf_avail;
		mz_zip_archive_file_stat file_stat;
		void *pRead_buf;
		mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) / sizeof(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
		tinfl_decompressor inflator;

		if ((buf_size) && (!pBuf))
			return MZ_FALSE;

		if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
			return MZ_FALSE;

		// Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
		if (!file_stat.m_comp_size)
			return MZ_TRUE;

		// Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
		// I'm torn how to handle this case - should it fail instead?
		if (mz_zip_reader_is_file_a_directory(pZip, file_index))
			return MZ_TRUE;

		// Encryption and patch files are not supported.
		if (file_stat.m_bit_flag & (1 | 32))
			return MZ_FALSE;

		// This function only supports stored and deflate.
		if ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
			return MZ_FALSE;

		// Ensure supplied output buffer is large enough.
		needed_size = (flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ? file_stat.m_comp_size : file_stat.m_uncomp_size;
		if (buf_size < needed_size)
			return MZ_FALSE;

		// Read and parse the local directory entry.
		cur_file_ofs = file_stat.m_local_header_ofs;
		if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
			return MZ_FALSE;
		if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
			return MZ_FALSE;

		cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
		if ((cur_file_ofs + file_stat.m_comp_size) > pZip->m_archive_size)
			return MZ_FALSE;

		if ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) || (!file_stat.m_method))
		{
			// The file is stored or the caller has requested the compressed data.
			if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_size) != needed_size)
				return MZ_FALSE;
			return ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) != 0) || (mz_crc32(MZ_CRC32_INIT, (const mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_size) == file_stat.m_crc32);
		}

		// Decompress the file either directly from memory or from a file input buffer.
		tinfl_init(&inflator);

		if (pZip->m_pState->m_pMem)
		{
			// Read directly from the archive in memory.
			pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
			read_buf_size = read_buf_avail = file_stat.m_comp_size;
			comp_remaining = 0;
		}
		else if (pUser_read_buf)
		{
			// Use a user provided read buffer.
			if (!user_read_buf_size)
				return MZ_FALSE;
			pRead_buf = (mz_uint8 *)pUser_read_buf;
			read_buf_size = user_read_buf_size;
			read_buf_avail = 0;
			comp_remaining = file_stat.m_comp_size;
		}
		else
		{
			// Temporarily allocate a read buffer.
			read_buf_size = MZ_MIN(file_stat.m_comp_size, MZ_ZIP_MAX_IO_BUF_SIZE);
#ifdef _MSC_VER
			if (((0, sizeof(size_t) == sizeof(mz_uint32))) && (read_buf_size > 0x7FFFFFFF))
#else
			if (((sizeof(size_t) == sizeof(mz_uint32))) && (read_buf_size > 0x7FFFFFFF))
#endif
				return MZ_FALSE;
			if (NULL == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_size)))
				return MZ_FALSE;
			read_buf_avail = 0;
			comp_remaining = file_stat.m_comp_size;
		}

		do
		{
			size_t in_buf_size, out_buf_size = (size_t)(file_stat.m_uncomp_size - out_buf_ofs);
			if ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
			{
				read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
				if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
				{
					status = TINFL_STATUS_FAILED;
					break;
				}
				cur_file_ofs += read_buf_avail;
				comp_remaining -= read_buf_avail;
				read_buf_ofs = 0;
			}
			in_buf_size = (size_t)read_buf_avail;
			status = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_size, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + out_buf_ofs, &out_buf_size, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_remaining ? TINFL_FLAG_HAS_MORE_INPUT : 0));
			read_buf_avail -= in_buf_size;
			read_buf_ofs += in_buf_size;
			out_buf_ofs += out_buf_size;
		} while (status == TINFL_STATUS_NEEDS_MORE_INPUT);

		if (status == TINFL_STATUS_DONE)
		{
			// Make sure the entire file was decompressed, and check its CRC.
			if ((out_buf_ofs != file_stat.m_uncomp_size) || (mz_crc32(MZ_CRC32_INIT, (const mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_size) != file_stat.m_crc32))
				status = TINFL_STATUS_FAILED;
		}

		if ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
			pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

		return status == TINFL_STATUS_DONE;
	}

	mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size, mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size)
	{
		int file_index = mz_zip_reader_locate_file(pZip, pFilename, NULL, flags);
		if (file_index < 0)
			return MZ_FALSE;
		return mz_zip_reader_extract_to_mem_no_alloc(pZip, file_index, pBuf, buf_size, flags, pUser_read_buf, user_read_buf_size);
	}

	mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index, void *pBuf, size_t buf_size, mz_uint flags)
	{
		return mz_zip_reader_extract_to_mem_no_alloc(pZip, file_index, pBuf, buf_size, flags, NULL, 0);
	}

	mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size, mz_uint flags)
	{
		return mz_zip_reader_extract_file_to_mem_no_alloc(pZip, pFilename, pBuf, buf_size, flags, NULL, 0);
	}

	void *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index, size_t *pSize, mz_uint flags)
	{
		mz_uint64 comp_size, uncomp_size, alloc_size;
		const mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
		void *pBuf;

		if (pSize)
			*pSize = 0;
		if (!p)
			return NULL;

		comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
		uncomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);

		alloc_size = (flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ? comp_size : uncomp_size;
#ifdef _MSC_VER
		if (((0, sizeof(size_t) == sizeof(mz_uint32))) && (alloc_size > 0x7FFFFFFF))
#else
		if (((sizeof(size_t) == sizeof(mz_uint32))) && (alloc_size > 0x7FFFFFFF))
#endif
			return NULL;
		if (NULL == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_size)))
			return NULL;

		if (!mz_zip_reader_extract_to_mem(pZip, file_index, pBuf, (size_t)alloc_size, flags))
		{
			pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
			return NULL;
		}

		if (pSize) *pSize = (size_t)alloc_size;
		return pBuf;
	}

	void *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, const char *pFilename, size_t *pSize, mz_uint flags)
	{
		int file_index = mz_zip_reader_locate_file(pZip, pFilename, NULL, flags);
		if (file_index < 0)
		{
			if (pSize) *pSize = 0;
			return MZ_FALSE;
		}
		return mz_zip_reader_extract_to_heap(pZip, file_index, pSize, flags);
	}

	mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_index, mz_file_write_func pCallback, void *pOpaque, mz_uint flags)
	{
		int status = TINFL_STATUS_DONE; mz_uint file_crc32 = MZ_CRC32_INIT;
		mz_uint64 read_buf_size, read_buf_ofs = 0, read_buf_avail, comp_remaining, out_buf_ofs = 0, cur_file_ofs;
		mz_zip_archive_file_stat file_stat;
		void *pRead_buf = NULL; void *pWrite_buf = NULL;
		mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) / sizeof(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;

		if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
			return MZ_FALSE;

		// Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
		if (!file_stat.m_comp_size)
			return MZ_TRUE;

		// Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
		// I'm torn how to handle this case - should it fail instead?
		if (mz_zip_reader_is_file_a_directory(pZip, file_index))
			return MZ_TRUE;

		// Encryption and patch files are not supported.
		if (file_stat.m_bit_flag & (1 | 32))
			return MZ_FALSE;

		// This function only supports stored and deflate.
		if ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
			return MZ_FALSE;

		// Read and parse the local directory entry.
		cur_file_ofs = file_stat.m_local_header_ofs;
		if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
			return MZ_FALSE;
		if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
			return MZ_FALSE;

		cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
		if ((cur_file_ofs + file_stat.m_comp_size) > pZip->m_archive_size)
			return MZ_FALSE;

		// Decompress the file either directly from memory or from a file input buffer.
		if (pZip->m_pState->m_pMem)
		{
			pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
			read_buf_size = read_buf_avail = file_stat.m_comp_size;
			comp_remaining = 0;
		}
		else
		{
			read_buf_size = MZ_MIN(file_stat.m_comp_size, MZ_ZIP_MAX_IO_BUF_SIZE);
			if (NULL == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_size)))
				return MZ_FALSE;
			read_buf_avail = 0;
			comp_remaining = file_stat.m_comp_size;
		}

		if ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) || (!file_stat.m_method))
		{
			// The file is stored or the caller has requested the compressed data.
			if (pZip->m_pState->m_pMem)
			{
#ifdef _MSC_VER
				if (((0, sizeof(size_t) == sizeof(mz_uint32))) && (file_stat.m_comp_size > 0xFFFFFFFF))
#else
				if (((sizeof(size_t) == sizeof(mz_uint32))) && (file_stat.m_comp_size > 0xFFFFFFFF))
#endif
					return MZ_FALSE;
				if (pCallback(pOpaque, out_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_size) != file_stat.m_comp_size)
					status = TINFL_STATUS_FAILED;
				else if (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
					file_crc32 = (mz_uint32)mz_crc32(file_crc32, (const mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_size);
				cur_file_ofs += file_stat.m_comp_size;
				out_buf_ofs += file_stat.m_comp_size;
				comp_remaining = 0;
			}
			else
			{
				while (comp_remaining)
				{
					read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
					if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
					{
						status = TINFL_STATUS_FAILED;
						break;
					}

					if (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
						file_crc32 = (mz_uint32)mz_crc32(file_crc32, (const mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

					if (pCallback(pOpaque, out_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
					{
						status = TINFL_STATUS_FAILED;
						break;
					}
					cur_file_ofs += read_buf_avail;
					out_buf_ofs += read_buf_avail;
					comp_remaining -= read_buf_avail;
				}
			}
		}
		else
		{
			tinfl_decompressor inflator;
			tinfl_init(&inflator);

			if (NULL == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_SIZE)))
				status = TINFL_STATUS_FAILED;
			else
			{
				do
				{
					mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));
					size_t in_buf_size, out_buf_size = TINFL_LZ_DICT_SIZE - (out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));
					if ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
					{
						read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
						if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
						{
							status = TINFL_STATUS_FAILED;
							break;
						}
						cur_file_ofs += read_buf_avail;
						comp_remaining -= read_buf_avail;
						read_buf_ofs = 0;
					}

					in_buf_size = (size_t)read_buf_avail;
					status = tinfl_decompress(&inflator, (const mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_size, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &out_buf_size, comp_remaining ? TINFL_FLAG_HAS_MORE_INPUT : 0);
					read_buf_avail -= in_buf_size;
					read_buf_ofs += in_buf_size;

					if (out_buf_size)
					{
						if (pCallback(pOpaque, out_buf_ofs, pWrite_buf_cur, out_buf_size) != out_buf_size)
						{
							status = TINFL_STATUS_FAILED;
							break;
						}
						file_crc32 = (mz_uint32)mz_crc32(file_crc32, pWrite_buf_cur, out_buf_size);
						if ((out_buf_ofs += out_buf_size) > file_stat.m_uncomp_size)
						{
							status = TINFL_STATUS_FAILED;
							break;
						}
					}
				} while ((status == TINFL_STATUS_NEEDS_MORE_INPUT) || (status == TINFL_STATUS_HAS_MORE_OUTPUT));
			}
		}

		if ((status == TINFL_STATUS_DONE) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)))
		{
			// Make sure the entire file was decompressed, and check its CRC.
			if ((out_buf_ofs != file_stat.m_uncomp_size) || (file_crc32 != file_stat.m_crc32))
				status = TINFL_STATUS_FAILED;
		}

		if (!pZip->m_pState->m_pMem)
			pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
		if (pWrite_buf)
			pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

		return status == TINFL_STATUS_DONE;
	}

	mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, const char *pFilename, mz_file_write_func pCallback, void *pOpaque, mz_uint flags)
	{
		int file_index = mz_zip_reader_locate_file(pZip, pFilename, NULL, flags);
		if (file_index < 0)
			return MZ_FALSE;
		return mz_zip_reader_extract_to_callback(pZip, file_index, pCallback, pOpaque, flags);
	}

#ifndef MINIZ_NO_STDIO
	static size_t mz_zip_file_write_callback(void *pOpaque, mz_uint64 ofs, const void *pBuf, size_t n)
	{
		(void)ofs; return MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
	}

	mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index, const char *pDst_filename, mz_uint flags)
	{
		mz_bool status;
		mz_zip_archive_file_stat file_stat;
		MZ_FILE *pFile;
		if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
			return MZ_FALSE;
		pFile = MZ_FOPEN(pDst_filename, "wb");
		if (!pFile)
			return MZ_FALSE;
		status = mz_zip_reader_extract_to_callback(pZip, file_index, mz_zip_file_write_callback, pFile, flags);
		if (MZ_FCLOSE(pFile) == EOF)
			return MZ_FALSE;
#ifndef MINIZ_NO_TIME
		if (status)
			mz_zip_set_file_times(pDst_filename, file_stat.m_time, file_stat.m_time);
#endif
		return status;
	}
#endif // #ifndef MINIZ_NO_STDIO

	mz_bool mz_zip_reader_end(mz_zip_archive *pZip)
	{
		if ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
			return MZ_FALSE;

		if (pZip->m_pState)
		{
			mz_zip_internal_state *pState = pZip->m_pState; pZip->m_pState = NULL;
			mz_zip_array_clear(pZip, &pState->m_central_dir);
			mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
			mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
			if (pState->m_pFile)
			{
				MZ_FCLOSE(pState->m_pFile);
				pState->m_pFile = NULL;
			}
#endif // #ifndef MINIZ_NO_STDIO

			pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
		}
		pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;

		return MZ_TRUE;
	}

#ifndef MINIZ_NO_STDIO
	mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, const char *pArchive_filename, const char *pDst_filename, mz_uint flags)
	{
		int file_index = mz_zip_reader_locate_file(pZip, pArchive_filename, NULL, flags);
		if (file_index < 0)
			return MZ_FALSE;
		return mz_zip_reader_extract_to_file(pZip, file_index, pDst_filename, flags);
	}
#endif

	// ------------------- .ZIP archive writing

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

	static void mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
	static void mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#define MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#define MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

	mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size)
	{
		if ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
			return MZ_FALSE;

		if (pZip->m_file_offset_alignment)
		{
			// Ensure user specified file offset alignment is a power of 2.
			if (pZip->m_file_offset_alignment & (pZip->m_file_offset_alignment - 1))
				return MZ_FALSE;
		}

		if (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
		if (!pZip->m_pFree) pZip->m_pFree = def_free_func;
		if (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

		pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
		pZip->m_archive_size = existing_size;
		pZip->m_central_directory_file_ofs = 0;
		pZip->m_total_files = 0;

		if (NULL == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, sizeof(mz_zip_internal_state))))
			return MZ_FALSE;
		memset(pZip->m_pState, 0, sizeof(mz_zip_internal_state));
		MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir, sizeof(mz_uint8));
		MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir_offsets, sizeof(mz_uint32));
		MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_sorted_central_dir_offsets, sizeof(mz_uint32));
		return MZ_TRUE;
	}

	static size_t mz_zip_heap_write_func(void *pOpaque, mz_uint64 file_ofs, const void *pBuf, size_t n)
	{
		mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
		mz_zip_internal_state *pState = pZip->m_pState;
		mz_uint64 new_size = MZ_MAX(file_ofs + n, pState->m_mem_size);
#ifdef _MSC_VER
		if ((!n) || ((0, sizeof(size_t) == sizeof(mz_uint32)) && (new_size > 0x7FFFFFFF)))
#else
		if ((!n) || ((sizeof(size_t) == sizeof(mz_uint32)) && (new_size > 0x7FFFFFFF)))
#endif
			return 0;
		if (new_size > pState->m_mem_capacity)
		{
			void *pNew_block;
			size_t new_capacity = MZ_MAX(64, pState->m_mem_capacity); while (new_capacity < new_size) new_capacity *= 2;
			if (NULL == (pNew_block = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_capacity)))
				return 0;
			pState->m_pMem = pNew_block; pState->m_mem_capacity = new_capacity;
		}
		memcpy((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
		pState->m_mem_size = (size_t)new_size;
		return n;
	}

	mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t size_to_reserve_at_beginning, size_t initial_allocation_size)
	{
		pZip->m_pWrite = mz_zip_heap_write_func;
		pZip->m_pIO_opaque = pZip;
		if (!mz_zip_writer_init(pZip, size_to_reserve_at_beginning))
			return MZ_FALSE;
		if (0 != (initial_allocation_size = MZ_MAX(initial_allocation_size, size_to_reserve_at_beginning)))
		{
			if (NULL == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_allocation_size)))
			{
				mz_zip_writer_end(pZip);
				return MZ_FALSE;
			}
			pZip->m_pState->m_mem_capacity = initial_allocation_size;
		}
		return MZ_TRUE;
	}

#ifndef MINIZ_NO_STDIO
	static size_t mz_zip_file_write_func(void *pOpaque, mz_uint64 file_ofs, const void *pBuf, size_t n)
	{
		mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
		mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
		if (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
			return 0;
		return MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
	}

	mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, const char *pFilename, mz_uint64 size_to_reserve_at_beginning)
	{
		MZ_FILE *pFile;
		pZip->m_pWrite = mz_zip_file_write_func;
		pZip->m_pIO_opaque = pZip;
		if (!mz_zip_writer_init(pZip, size_to_reserve_at_beginning))
			return MZ_FALSE;
		if (NULL == (pFile = MZ_FOPEN(pFilename, "wb")))
		{
			mz_zip_writer_end(pZip);
			return MZ_FALSE;
		}
		pZip->m_pState->m_pFile = pFile;
		if (size_to_reserve_at_beginning)
		{
			mz_uint64 cur_ofs = 0; char buf[4096]; MZ_CLEAR_OBJ(buf);
			do
			{
				size_t n = (size_t)MZ_MIN(sizeof(buf), size_to_reserve_at_beginning);
				if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
				{
					mz_zip_writer_end(pZip);
					return MZ_FALSE;
				}
				cur_ofs += n; size_to_reserve_at_beginning -= n;
			} while (size_to_reserve_at_beginning);
		}
		return MZ_TRUE;
	}
#endif // #ifndef MINIZ_NO_STDIO

	mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, const char *pFilename)
	{
		mz_zip_internal_state *pState;
		if ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
			return MZ_FALSE;
		// No sense in trying to write to an archive that's already at the support max size
		if ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + MZ_ZIP_LOCAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
			return MZ_FALSE;

		pState = pZip->m_pState;

		if (pState->m_pFile)
		{
#ifdef MINIZ_NO_STDIO
			pFilename; return MZ_FALSE;
#else
			// Archive is being read from stdio - try to reopen as writable.
			if (pZip->m_pIO_opaque != pZip)
				return MZ_FALSE;
			if (!pFilename)
				return MZ_FALSE;
			pZip->m_pWrite = mz_zip_file_write_func;
			if (NULL == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
			{
				// The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
				mz_zip_reader_end(pZip);
				return MZ_FALSE;
			}
#endif // #ifdef MINIZ_NO_STDIO
		}
		else if (pState->m_pMem)
		{
			// Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
			if (pZip->m_pIO_opaque != pZip)
				return MZ_FALSE;
			pState->m_mem_capacity = pState->m_mem_size;
			pZip->m_pWrite = mz_zip_heap_write_func;
		}
		// Archive is being read via a user provided read function - make sure the user has specified a write function too.
		else if (!pZip->m_pWrite)
			return MZ_FALSE;

		// Start writing new files at the archive's current central directory location.
		pZip->m_archive_size = pZip->m_central_directory_file_ofs;
		pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
		pZip->m_central_directory_file_ofs = 0;

		return MZ_TRUE;
	}

	mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf, size_t buf_size, mz_uint level_and_flags)
	{
		return mz_zip_writer_add_mem_ex(pZip, pArchive_name, pBuf, buf_size, NULL, 0, level_and_flags, 0, 0);
	}

	typedef struct
	{
		mz_zip_archive *m_pZip;
		mz_uint64 m_cur_archive_file_ofs;
		mz_uint64 m_comp_size;
	} mz_zip_writer_add_state;

	static mz_bool mz_zip_writer_add_put_buf_callback(const void* pBuf, int len, void *pUser)
	{
		mz_zip_writer_add_state *pState = (mz_zip_writer_add_state *)pUser;
		if ((int)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
			return MZ_FALSE;
		pState->m_cur_archive_file_ofs += len;
		pState->m_comp_size += len;
		return MZ_TRUE;
	}

	static mz_bool mz_zip_writer_create_local_dir_header(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_size, mz_uint16 extra_size, mz_uint64 uncomp_size, mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date)
	{
		(void)pZip;
		memset(pDst, 0, MZ_ZIP_LOCAL_DIR_HEADER_SIZE);
		MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_HEADER_SIG);
		MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_VERSION_NEEDED_OFS, method ? 20 : 0);
		MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_BIT_FLAG_OFS, bit_flags);
		MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_METHOD_OFS, method);
		MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_TIME_OFS, dos_time);
		MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
		MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_CRC32_OFS, uncomp_crc32);
		MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_SIZE_OFS, comp_size);
		MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_SIZE_OFS, uncomp_size);
		MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_size);
		MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_size);
		return MZ_TRUE;
	}

	static mz_bool mz_zip_writer_create_central_dir_header(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_size, mz_uint16 extra_size, mz_uint16 comment_size, mz_uint64 uncomp_size, mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs, mz_uint32 ext_attributes)
	{
		(void)pZip;
		memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE);
		MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_HEADER_SIG);
		MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_VERSION_NEEDED_OFS, method ? 20 : 0);
		MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_BIT_FLAG_OFS, bit_flags);
		MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_METHOD_OFS, method);
		MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_TIME_OFS, dos_time);
		MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
		MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_CRC32_OFS, uncomp_crc32);
		MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS, comp_size);
		MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS, uncomp_size);
		MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_size);
		MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_size);
		MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_size);
		MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_attributes);
		MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_HEADER_OFS, local_header_ofs);
		return MZ_TRUE;
	}

	static mz_bool mz_zip_writer_add_to_central_dir(mz_zip_archive *pZip, const char *pFilename, mz_uint16 filename_size, const void *pExtra, mz_uint16 extra_size, const void *pComment, mz_uint16 comment_size, mz_uint64 uncomp_size, mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs, mz_uint32 ext_attributes)
	{
		mz_zip_internal_state *pState = pZip->m_pState;
		mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_size;
		size_t orig_central_dir_size = pState->m_central_dir.m_size;
		mz_uint8 central_dir_header[MZ_ZIP_CENTRAL_DIR_HEADER_SIZE];

		// No zip64 support yet
		if ((local_header_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_size + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_size + extra_size + comment_size) > 0xFFFFFFFF))
			return MZ_FALSE;

		if (!mz_zip_writer_create_central_dir_header(pZip, central_dir_header, filename_size, extra_size, comment_size, uncomp_size, comp_size, uncomp_crc32, method, bit_flags, dos_time, dos_date, local_header_ofs, ext_attributes))
			return MZ_FALSE;

		if ((!mz_zip_array_push_back(pZip, &pState->m_central_dir, central_dir_header, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)) ||
			(!mz_zip_array_push_back(pZip, &pState->m_central_dir, pFilename, filename_size)) ||
			(!mz_zip_array_push_back(pZip, &pState->m_central_dir, pExtra, extra_size)) ||
			(!mz_zip_array_push_back(pZip, &pState->m_central_dir, pComment, comment_size)) ||
			(!mz_zip_array_push_back(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
		{
			// Try to push the central directory array back into its original state.
			mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size, MZ_FALSE);
			return MZ_FALSE;
		}

		return MZ_TRUE;
	}

	static mz_bool mz_zip_writer_validate_archive_name(const char *pArchive_name)
	{
		// Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
		if (*pArchive_name == '/')
			return MZ_FALSE;
		while (*pArchive_name)
		{
			if ((*pArchive_name == '\\') || (*pArchive_name == ':'))
				return MZ_FALSE;
			pArchive_name++;
		}
		return MZ_TRUE;
	}

	static mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
	{
		mz_uint32 n;
		if (!pZip->m_file_offset_alignment)
			return 0;
		n = (mz_uint32)(pZip->m_archive_size & (pZip->m_file_offset_alignment - 1));
		return (pZip->m_file_offset_alignment - n) & (pZip->m_file_offset_alignment - 1);
	}

	static mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
	{
		char buf[4096];
		memset(buf, 0, MZ_MIN(sizeof(buf), n));
		while (n)
		{
			mz_uint32 s = MZ_MIN(sizeof(buf), n);
			if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
				return MZ_FALSE;
			cur_file_ofs += s; n -= s;
		}
		return MZ_TRUE;
	}

	mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, const char *pArchive_name, const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32)
	{
		mz_uint16 method = 0, dos_time = 0, dos_date = 0;
		mz_uint level, ext_attributes = 0, num_alignment_padding_bytes;
		mz_uint64 local_dir_header_ofs = pZip->m_archive_size, cur_archive_file_ofs = pZip->m_archive_size, comp_size = 0;
		size_t archive_name_size;
		mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
		tdefl_compressor *pComp = NULL;
		mz_bool store_data_uncompressed;
		mz_zip_internal_state *pState;

		if ((int)level_and_flags < 0)
			level_and_flags = MZ_DEFAULT_LEVEL;
		level = level_and_flags & 0xF;
		store_data_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA));

		if ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || ((buf_size) && (!pBuf)) || (!pArchive_name) || ((comment_size) && (!pComment)) || (pZip->m_total_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
			return MZ_FALSE;

		pState = pZip->m_pState;

		if ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (uncomp_size))
			return MZ_FALSE;
		// No zip64 support yet
		if ((buf_size > 0xFFFFFFFF) || (uncomp_size > 0xFFFFFFFF))
			return MZ_FALSE;
		if (!mz_zip_writer_validate_archive_name(pArchive_name))
			return MZ_FALSE;

#ifndef MINIZ_NO_TIME
		{
			time_t cur_time; time(&cur_time);
			mz_zip_time_to_dos_time(cur_time, &dos_time, &dos_date);
		}
#endif // #ifndef MINIZ_NO_TIME

		archive_name_size = strlen(pArchive_name);
		if (archive_name_size > 0xFFFF)
			return MZ_FALSE;

		num_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

		// no zip64 support yet
		if ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + num_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + comment_size + archive_name_size) > 0xFFFFFFFF))
			return MZ_FALSE;

		if ((archive_name_size) && (pArchive_name[archive_name_size - 1] == '/'))
		{
			// Set DOS Subdirectory attribute bit.
			ext_attributes |= 0x10;
			// Subdirectories cannot contain data.
			if ((buf_size) || (uncomp_size))
				return MZ_FALSE;
		}

		// Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
		if ((!mz_zip_array_ensure_room(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + archive_name_size + comment_size)) || (!mz_zip_array_ensure_room(pZip, &pState->m_central_dir_offsets, 1)))
			return MZ_FALSE;

		if ((!store_data_uncompressed) && (buf_size))
		{
			if (NULL == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, sizeof(tdefl_compressor))))
				return MZ_FALSE;
		}

		if (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, num_alignment_padding_bytes + sizeof(local_dir_header)))
		{
			pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
			return MZ_FALSE;
		}
		local_dir_header_ofs += num_alignment_padding_bytes;
		if (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }
		cur_archive_file_ofs += num_alignment_padding_bytes + sizeof(local_dir_header);

		MZ_CLEAR_OBJ(local_dir_header);
		if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_size) != archive_name_size)
		{
			pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
			return MZ_FALSE;
		}
		cur_archive_file_ofs += archive_name_size;

		if (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
		{
			uncomp_crc32 = (mz_uint32)mz_crc32(MZ_CRC32_INIT, (const mz_uint8*)pBuf, buf_size);
			uncomp_size = buf_size;
			if (uncomp_size <= 3)
			{
				level = 0;
				store_data_uncompressed = MZ_TRUE;
			}
		}

		if (store_data_uncompressed)
		{
			if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_size) != buf_size)
			{
				pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
				return MZ_FALSE;
			}

			cur_archive_file_ofs += buf_size;
			comp_size = buf_size;

			if (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)
				method = MZ_DEFLATED;
		}
		else if (buf_size)
		{
			mz_zip_writer_add_state state;

			state.m_pZip = pZip;
			state.m_cur_archive_file_ofs = cur_archive_file_ofs;
			state.m_comp_size = 0;

			if ((tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_STATUS_OKAY) ||
				(tdefl_compress_buffer(pComp, pBuf, buf_size, TDEFL_FINISH) != TDEFL_STATUS_DONE))
			{
				pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
				return MZ_FALSE;
			}

			comp_size = state.m_comp_size;
			cur_archive_file_ofs = state.m_cur_archive_file_ofs;

			method = MZ_DEFLATED;
		}

		pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
		pComp = NULL;

		// no zip64 support yet
		if ((comp_size > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
			return MZ_FALSE;

		if (!mz_zip_writer_create_local_dir_header(pZip, local_dir_header, (mz_uint16)archive_name_size, 0, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date))
			return MZ_FALSE;

		if (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header, sizeof(local_dir_header)) != sizeof(local_dir_header))
			return MZ_FALSE;

		if (!mz_zip_writer_add_to_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_size, NULL, 0, pComment, comment_size, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date, local_dir_header_ofs, ext_attributes))
			return MZ_FALSE;

		pZip->m_total_files++;
		pZip->m_archive_size = cur_archive_file_ofs;

		return MZ_TRUE;
	}

#ifndef MINIZ_NO_STDIO
	mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, const char *pArchive_name, const char *pSrc_filename, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags)
	{
		mz_uint uncomp_crc32 = MZ_CRC32_INIT, level, num_alignment_padding_bytes;
		mz_uint16 method = 0, dos_time = 0, dos_date = 0, ext_attributes = 0;
		mz_uint64 local_dir_header_ofs = pZip->m_archive_size, cur_archive_file_ofs = pZip->m_archive_size, uncomp_size = 0, comp_size = 0;
		size_t archive_name_size;
		mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
		MZ_FILE *pSrc_file = NULL;

		if ((int)level_and_flags < 0)
			level_and_flags = MZ_DEFAULT_LEVEL;
		level = level_and_flags & 0xF;

		if ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || (!pArchive_name) || ((comment_size) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
			return MZ_FALSE;
		if (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)
			return MZ_FALSE;
		if (!mz_zip_writer_validate_archive_name(pArchive_name))
			return MZ_FALSE;

		archive_name_size = strlen(pArchive_name);
		if (archive_name_size > 0xFFFF)
			return MZ_FALSE;

		num_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

		// no zip64 support yet
		if ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + num_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + comment_size + archive_name_size) > 0xFFFFFFFF))
			return MZ_FALSE;

		if (!mz_zip_get_file_modified_time(pSrc_filename, &dos_time, &dos_date))
			return MZ_FALSE;

		pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
		if (!pSrc_file)
			return MZ_FALSE;
		MZ_FSEEK64(pSrc_file, 0, SEEK_END);
		uncomp_size = MZ_FTELL64(pSrc_file);
		MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

		if (uncomp_size > 0xFFFFFFFF)
		{
			// No zip64 support yet
			MZ_FCLOSE(pSrc_file);
			return MZ_FALSE;
		}
		if (uncomp_size <= 3)
			level = 0;

		if (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, num_alignment_padding_bytes + sizeof(local_dir_header)))
		{
			MZ_FCLOSE(pSrc_file);
			return MZ_FALSE;
		}
		local_dir_header_ofs += num_alignment_padding_bytes;
		if (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }
		cur_archive_file_ofs += num_alignment_padding_bytes + sizeof(local_dir_header);

		MZ_CLEAR_OBJ(local_dir_header);
		if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_size) != archive_name_size)
		{
			MZ_FCLOSE(pSrc_file);
			return MZ_FALSE;
		}
		cur_archive_file_ofs += archive_name_size;

		if (uncomp_size)
		{
			mz_uint64 uncomp_remaining = uncomp_size;
			void *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_SIZE);
			if (!pRead_buf)
			{
				MZ_FCLOSE(pSrc_file);
				return MZ_FALSE;
			}

			if (!level)
			{
				while (uncomp_remaining)
				{
					mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_SIZE, uncomp_remaining);
					if ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
					{
						pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
						MZ_FCLOSE(pSrc_file);
						return MZ_FALSE;
					}
					uncomp_crc32 = (mz_uint32)mz_crc32(uncomp_crc32, (const mz_uint8 *)pRead_buf, n);
					uncomp_remaining -= n;
					cur_archive_file_ofs += n;
				}
				comp_size = uncomp_size;
			}
			else
			{
				mz_bool result = MZ_FALSE;
				mz_zip_writer_add_state state;
				tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, sizeof(tdefl_compressor));
				if (!pComp)
				{
					pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
					MZ_FCLOSE(pSrc_file);
					return MZ_FALSE;
				}

				state.m_pZip = pZip;
				state.m_cur_archive_file_ofs = cur_archive_file_ofs;
				state.m_comp_size = 0;

				if (tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_STATUS_OKAY)
				{
					pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
					pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
					MZ_FCLOSE(pSrc_file);
					return MZ_FALSE;
				}

				for (;;)
				{
					size_t in_buf_size = (mz_uint32)MZ_MIN(uncomp_remaining, MZ_ZIP_MAX_IO_BUF_SIZE);
					tdefl_status status;

					if (MZ_FREAD(pRead_buf, 1, in_buf_size, pSrc_file) != in_buf_size)
						break;

					uncomp_crc32 = (mz_uint32)mz_crc32(uncomp_crc32, (const mz_uint8 *)pRead_buf, in_buf_size);
					uncomp_remaining -= in_buf_size;

					status = tdefl_compress_buffer(pComp, pRead_buf, in_buf_size, uncomp_remaining ? TDEFL_NO_FLUSH : TDEFL_FINISH);
					if (status == TDEFL_STATUS_DONE)
					{
						result = MZ_TRUE;
						break;
					}
					else if (status != TDEFL_STATUS_OKAY)
						break;
				}

				pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

				if (!result)
				{
					pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
					MZ_FCLOSE(pSrc_file);
					return MZ_FALSE;
				}

				comp_size = state.m_comp_size;
				cur_archive_file_ofs = state.m_cur_archive_file_ofs;

				method = MZ_DEFLATED;
			}

			pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
		}

		MZ_FCLOSE(pSrc_file); pSrc_file = NULL;

		// no zip64 support yet
		if ((comp_size > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
			return MZ_FALSE;

		if (!mz_zip_writer_create_local_dir_header(pZip, local_dir_header, (mz_uint16)archive_name_size, 0, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date))
			return MZ_FALSE;

		if (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header, sizeof(local_dir_header)) != sizeof(local_dir_header))
			return MZ_FALSE;

		if (!mz_zip_writer_add_to_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_size, NULL, 0, pComment, comment_size, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date, local_dir_header_ofs, ext_attributes))
			return MZ_FALSE;

		pZip->m_total_files++;
		pZip->m_archive_size = cur_archive_file_ofs;

		return MZ_TRUE;
	}
#endif // #ifndef MINIZ_NO_STDIO

	mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_index)
	{
		mz_uint n, bit_flags, num_alignment_padding_bytes;
		mz_uint64 comp_bytes_remaining, local_dir_header_ofs;
		mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
		mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) / sizeof(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
		mz_uint8 central_header[MZ_ZIP_CENTRAL_DIR_HEADER_SIZE];
		size_t orig_central_dir_size;
		mz_zip_internal_state *pState;
		void *pBuf; const mz_uint8 *pSrc_central_header;

		if ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
			return MZ_FALSE;
		if (NULL == (pSrc_central_header = mz_zip_reader_get_cdh(pSource_zip, file_index)))
			return MZ_FALSE;
		pState = pZip->m_pState;

		num_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

		// no zip64 support yet
		if ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + num_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
			return MZ_FALSE;

		cur_src_file_ofs = MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS);
		cur_dst_file_ofs = pZip->m_archive_size;

		if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
			return MZ_FALSE;
		if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
			return MZ_FALSE;
		cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE;

		if (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, num_alignment_padding_bytes))
			return MZ_FALSE;
		cur_dst_file_ofs += num_alignment_padding_bytes;
		local_dir_header_ofs = cur_dst_file_ofs;
		if (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }

		if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
			return MZ_FALSE;
		cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE;

		n = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
		comp_bytes_remaining = n + MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);

		if (NULL == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(sizeof(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_SIZE, comp_bytes_remaining)))))
			return MZ_FALSE;

		while (comp_bytes_remaining)
		{
			n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_SIZE, comp_bytes_remaining);
			if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
			{
				pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
				return MZ_FALSE;
			}
			cur_src_file_ofs += n;

			if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
			{
				pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
				return MZ_FALSE;
			}
			cur_dst_file_ofs += n;

			comp_bytes_remaining -= n;
		}

		bit_flags = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_BIT_FLAG_OFS);
		if (bit_flags & 8)
		{
			// Copy data descriptor
			if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, sizeof(mz_uint32) * 4) != sizeof(mz_uint32) * 4)
			{
				pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
				return MZ_FALSE;
			}

			n = sizeof(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
			if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
			{
				pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
				return MZ_FALSE;
			}

			cur_src_file_ofs += n;
			cur_dst_file_ofs += n;
		}
		pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

		// no zip64 support yet
		if (cur_dst_file_ofs > 0xFFFFFFFF)
			return MZ_FALSE;

		orig_central_dir_size = pState->m_central_dir.m_size;

		memcpy(central_header, pSrc_central_header, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE);
		MZ_WRITE_LE32(central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS, local_dir_header_ofs);
		if (!mz_zip_array_push_back(pZip, &pState->m_central_dir, central_header, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE))
			return MZ_FALSE;

		n = MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_COMMENT_LEN_OFS);
		if (!mz_zip_array_push_back(pZip, &pState->m_central_dir, pSrc_central_header + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n))
		{
			mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size, MZ_FALSE);
			return MZ_FALSE;
		}

		if (pState->m_central_dir.m_size > 0xFFFFFFFF)
			return MZ_FALSE;
		n = (mz_uint32)orig_central_dir_size;
		if (!mz_zip_array_push_back(pZip, &pState->m_central_dir_offsets, &n, 1))
		{
			mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size, MZ_FALSE);
			return MZ_FALSE;
		}

		pZip->m_total_files++;
		pZip->m_archive_size = cur_dst_file_ofs;

		return MZ_TRUE;
	}

	mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
	{
		mz_zip_internal_state *pState;
		mz_uint64 central_dir_ofs, central_dir_size;
		mz_uint8 hdr[MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE];

		if ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
			return MZ_FALSE;

		pState = pZip->m_pState;

		// no zip64 support yet
		if ((pZip->m_total_files > 0xFFFF) || ((pZip->m_archive_size + pState->m_central_dir.m_size + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
			return MZ_FALSE;

		central_dir_ofs = 0;
		central_dir_size = 0;
		if (pZip->m_total_files)
		{
			// Write central directory
			central_dir_ofs = pZip->m_archive_size;
			central_dir_size = pState->m_central_dir.m_size;
			pZip->m_central_directory_file_ofs = central_dir_ofs;
			if (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_size) != central_dir_size)
				return MZ_FALSE;
			pZip->m_archive_size += central_dir_size;
		}

		// Write end of central directory record
		MZ_CLEAR_OBJ(hdr);
		MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG);
		MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS, pZip->m_total_files);
		MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS, pZip->m_total_files);
		MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_SIZE_OFS, central_dir_size);
		MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

		if (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_size, hdr, sizeof(hdr)) != sizeof(hdr))
			return MZ_FALSE;
#ifndef MINIZ_NO_STDIO
		if ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
			return MZ_FALSE;
#endif // #ifndef MINIZ_NO_STDIO

		pZip->m_archive_size += sizeof(hdr);

		pZip->m_zip_mode = MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED;
		return MZ_TRUE;
	}

	mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, void **pBuf, size_t *pSize)
	{
		if ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!pSize))
			return MZ_FALSE;
		if (pZip->m_pWrite != mz_zip_heap_write_func)
			return MZ_FALSE;
		if (!mz_zip_writer_finalize_archive(pZip))
			return MZ_FALSE;

		*pBuf = pZip->m_pState->m_pMem;
		*pSize = pZip->m_pState->m_mem_size;
		pZip->m_pState->m_pMem = NULL;
		pZip->m_pState->m_mem_size = pZip->m_pState->m_mem_capacity = 0;
		return MZ_TRUE;
	}

	mz_bool mz_zip_writer_end(mz_zip_archive *pZip)
	{
		mz_zip_internal_state *pState;
		mz_bool status = MZ_TRUE;
		if ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) && (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED)))
			return MZ_FALSE;

		pState = pZip->m_pState;
		pZip->m_pState = NULL;
		mz_zip_array_clear(pZip, &pState->m_central_dir);
		mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
		mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
		if (pState->m_pFile)
		{
			MZ_FCLOSE(pState->m_pFile);
			pState->m_pFile = NULL;
		}
#endif // #ifndef MINIZ_NO_STDIO

		if ((pZip->m_pWrite == mz_zip_heap_write_func) && (pState->m_pMem))
		{
			pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
			pState->m_pMem = NULL;
		}

		pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
		pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;
		return status;
	}

#ifndef MINIZ_NO_STDIO
	mz_bool mz_zip_add_mem_to_archive_file_in_place(const char *pZip_filename, const char *pArchive_name, const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags)
	{
		mz_bool status, created_new_archive = MZ_FALSE;
		mz_zip_archive zip_archive;
		struct MZ_FILE_STAT_STRUCT file_stat;
		MZ_CLEAR_OBJ(zip_archive);
		if ((int)level_and_flags < 0)
			level_and_flags = MZ_DEFAULT_LEVEL;
		if ((!pZip_filename) || (!pArchive_name) || ((buf_size) && (!pBuf)) || ((comment_size) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
			return MZ_FALSE;
		if (!mz_zip_writer_validate_archive_name(pArchive_name))
			return MZ_FALSE;
		if (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
		{
			// Create a new archive.
			if (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
				return MZ_FALSE;
			created_new_archive = MZ_TRUE;
		}
		else
		{
			// Append to an existing archive.
			if (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
				return MZ_FALSE;
			if (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
			{
				mz_zip_reader_end(&zip_archive);
				return MZ_FALSE;
			}
		}
		status = mz_zip_writer_add_mem_ex(&zip_archive, pArchive_name, pBuf, buf_size, pComment, comment_size, level_and_flags, 0, 0);
		// Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
		if (!mz_zip_writer_finalize_archive(&zip_archive))
			status = MZ_FALSE;
		if (!mz_zip_writer_end(&zip_archive))
			status = MZ_FALSE;
		if ((!status) && (created_new_archive))
		{
			// It's a new archive and something went wrong, so just delete it.
			int ignoredStatus = MZ_DELETE_FILE(pZip_filename);
			(void)ignoredStatus;
		}
		return status;
	}

	void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename, const char *pArchive_name, size_t *pSize, mz_uint flags)
	{
		int file_index;
		mz_zip_archive zip_archive;
		void *p = NULL;

		if (pSize)
			*pSize = 0;

		if ((!pZip_filename) || (!pArchive_name))
			return NULL;

		MZ_CLEAR_OBJ(zip_archive);
		if (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
			return NULL;

		if ((file_index = mz_zip_reader_locate_file(&zip_archive, pArchive_name, NULL, flags)) >= 0)
			p = mz_zip_reader_extract_to_heap(&zip_archive, file_index, pSize, flags);

		mz_zip_reader_end(&zip_archive);
		return p;
	}

#endif // #ifndef MINIZ_NO_STDIO

#endif // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef __cplusplus
}
#endif

#endif // MINIZ_HEADER_FILE_ONLY

/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

// end miniz.c

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

i32 zt_compressDeflate(void *data, i32 data_size, void *buffer, i32 buffer_size)
{
	zt_assert(false);
	return 0;
}

// ================================================================================================================================================================================================

i32 zt_compressInflate(void *compressed, i32 compressed_size, void *buffer, i32 buffer_size)
{
	mz_stream zipper;
	memset(&zipper, 0, sizeof(zipper));
	if (mz_inflateInit(&zipper) != MZ_OK) {
		return 0;
	}

	zipper.next_in  = (const unsigned char*)compressed;
	zipper.avail_in = compressed_size;

	zipper.next_out  = (u8*)buffer;
	zipper.avail_out = buffer_size;

	int r = mz_inflate(&zipper, MZ_FINISH);
	i32 total_out = zipper.total_out;

	mz_inflateEnd(&zipper);

	if (r != MZ_STREAM_END) {
		return 0;
	}

	return total_out;
}

// ================================================================================================================================================================================================


#endif // ZT_TOOLS_IMPLEMENTATION

#endif // include guard