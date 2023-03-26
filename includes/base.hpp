#ifndef __SEABOW_BASE_HPP__
#define __SEABOW_BASE_HPP__

#define SEABOW_MAJOR 0
#define SEABOW_MINOR 1
#define SEABOW_PATCH 0

#define SEABOW_HELPS L"Welcome to Seabow helps!\n\tCompiler: seabow cmp <main_file> <other_arguments>\nThis will compile seabow files (.sbw) to seabow bytecode files (.sbb).\
\n\n\tInterpreter: seabow <other_arguments>\nThis will open seabow interpreter in your terminal.\n\n\tVirtual Machine: seabow run <bytecode_file> <other_arguments>\n\
This will interpret bytecode and perform it.\n\n/!\\ <other_arguments>: All seabow command arguments like: -opt, -o, -cmt, ...\n/!\\ <main_file>: seabow file (.sbw) \
that contains main function.\n/!\\ <bytecode_file>: seabow bytecode file (.sbb) to perform.\n"

// C standart libraries
#include <math.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include <iomanip>

#ifdef _WIN32
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

inline constexpr bool string_equals(const char *str1, const char *str2)
{
    sbw_ulong size1 = 0;
    while (str1[size1] != '\0')
        size1++;
    sbw_ulong size2 = 0;
    while (str2[size2] != '\0')
        size2++;

    if (size1 != size2)
        return false;
    
    for (sbw_ulong i=0; i<size1; i++)
    {
        if (str1[i] != str2[i])
            return false;
    }

    return true;
}

#endif // __SEABOW_BASE_HPP__