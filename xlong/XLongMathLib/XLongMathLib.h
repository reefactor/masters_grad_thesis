// main include header for Xlong math lib

#if !defined(_XLONGMATHLIB_H_)
#define _XLONGMATHLIB_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/////////////////////////////////////////////////////////////////////
// standard library includes
#include <memory.h> 
#include <stdio.h>

///////////////////////////////////////////////////////////////////
// hardware compatibility check
#ifndef __cplusplus
# error C++ compiler required.
#endif

// x86 hardware check on win32 compliler
#ifdef _WIN32
# ifndef _M_IX86
#  error library is optimized only for x86 compatible hardware
# endif
#endif

// x86 hardware check on non win32 compliler
#ifndef _WIN32
# ifndef __i386__
#  error library is optimized only for x86 compatible hardware
# endif
#endif

//linux specific
#ifdef LINUX
// some definitions here
#endif

////////////////////////////////////////////////////////////////////
// software compatibility and portability 
#ifdef _WIN32  // MS VC++ specific
# define TARGET_IS_WIN32
# include <windows.h>
#endif

////////////////////////////////////////////////////////////////////
// type definitions 
#ifndef uint32
 typedef unsigned __int32 uint32;
#endif

#ifndef int32
 typedef __int32 int32;
#endif

#ifdef BYTE
 typedef unsigned __int8 BYTE;
#endif

#ifndef _WIN32 //MS VC++ version 5 and greater has built-in bool type
# ifndef bool
   typedef enum {false=0,true=1} bool;
# endif
#endif

///////////////////////////////////////////////////////////////
// lib defs

#define DEFAULT_BIT_LEN 1024

// core options  !!! definition must be mutable
#define STD_I386	1
#define I386_MMX	2

#define MATH_CORE STD_I386  // core selection


// for MMX low level routines
#if (MATH_CORE == I386_MMX)
# define BLOCK_BITLEN 64
#else
# define BLOCK_BITLEN 32
#endif

// strict check of value truncations and loss of data
// caused by length mismatch
// slows perfomance but alerts if there is loss of data
#define STRICT_CHECKS

// error and warning messages output via standard printf
#define ENABLE_DEBUG_CONSOLE

// optimization: shifting dwords by (n_shifts >> 5) bits at once 
#define OPTIMIZED_SHIFTS 

#ifdef OPTIMIZED_SHIFTS 
// single pass or multi pass shift routine
# define FAST_SINGLE_PASS_SHIFT
#endif


// base data container Object class XLong for lib
#include "Xlong.h"

////////////////////////////////////////////////////////////////////////////
namespace XLONG_MATH_LIB {


// math
bool evcl(XLong& e,XLong& N, XLong& e_mul_m);
bool evclm(XLong& e,XLong& N, XLong& e_mul_m);
int evclm2(XLong& e,XLong& N);
inline XLong modexp(const XLong& M, const XLong& exp, const XLong& N);
bool GCD(XLong& e,XLong& N, XLong& result);
XLong power(const XLong& x, const XLong& n);
XLong root(XLong& x, uint32 n);
void mod(XLong& a, const XLong& b);
bool isPrime(XLong& number);
void getPrime(XLong& left, XLong& prime);


// service 
void EXCEPT(const char* alert_str);
void CRASH(const char* info_string); 
void ALERT(const char* info_string); 

// logic
int cmp(const XLong& a, const uint32 small_number);
int cmp(const XLong& a, const XLong& b);


///////////////////////////////////////////////////////////////////////
//core module routines
///////////////////////////////////////////////////////////////////////
// bitwise shifts
void shl(XLong& a, uint32 n_shifts);
void shr(XLong& a, uint32 n_shifts);

//math
void add(XLong& a, const XLong& b);
void add(XLong& a, const uint32 b);
void sub(XLong& a, const XLong& b);
void sub(XLong& a, const uint32 b);
void mul(XLong& a, const XLong& b); 
void div(const XLong& a, const XLong& b, XLong &quot, XLong &rem);
////////////////////////////////////////////////////////////////////////


} // namespace XLONG_MATH_LIB 



#endif //_XLONGMATHLIB_H_
