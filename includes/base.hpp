#ifndef __SEABOW_BASE_HPP__
#define __SEABOW_BASE_HPP__

#define SEABOW_MAJOR 0
#define SEABOW_MINOR 1
#define SEABOW_PATCH 0

// C standart libraries
#include <math.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #include <fcntl.h>
    #define SEABOW_OS "windows"
#elif __APPLE__
    #define SEABOW_OS "macos"
#else
    #define SEABOW_OS "linux"
#endif

// Seabow types
typedef void                sbw_none;
typedef signed char         sbw_byte;
typedef unsigned char       sbw_ubyte;
typedef signed short        sbw_short;
typedef unsigned short      sbw_ushort;
typedef signed long         sbw_int;
typedef unsigned long       sbw_uint;
typedef signed long long    sbw_long;
typedef unsigned long long  sbw_ulong;
typedef float               sbw_float;
typedef double              sbw_double;
typedef long double         sbw_ldouble;
typedef signed char         sbw_bool;
typedef wchar_t             sbw_char;
typedef std::wstring        sbw_string;

#endif // __SEABOW_BASE_HPP__