// main include header for XGalois math lib

#if !defined(_XGALOISLIB_H_)
#define _XGALOISLIB_H_

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
# define TARGET_IS_LINUX
// linux specific
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
// library  definitions
////////////////////////////////////////////////////////////////////////////
namespace XGALOIS_MATH_LIB {

#define XGALOIS_DEFAULT_BIT_LEN 5

// core selection options  
#define STD_I386	1
//#define I386_MMX	2
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

}

// base data container Object class GF2m 
#include "GF2m.h"

namespace XGALOIS_MATH_LIB {


// service 
void EXCEPT(const char* alert_str);
void CRASH(const char* info_string); 
void ALERT(const char* info_string); 

// logic
int cmp(const GF2m& a, const uint32 small_number);
int cmp(const GF2m& a, const GF2m& b);

void inc(GF2m& a);
void dec(GF2m& a);


void power(GF2m& a, uint32 b);
void power2(GF2m& a, uint32 b);


//math
void add(GF2m& a, const GF2m& b);
void mul(GF2m& a, const GF2m& b);
////////////////////////////////////////////////////////////////////////


} // namespace XGALOIS_MATH_LIB



#endif //_XGALOISLIB_H_
