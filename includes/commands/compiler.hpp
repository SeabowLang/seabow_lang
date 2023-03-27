#ifndef __SEABOW_COMPILER_HPP__
#define __SEABOW_COMPILER_HPP__

#include "commands/interpreter.hpp"

class SBW_Compiler
{
public:
    SBW_Compiler(SBW_Options *options);

    inline sbw_bool ErrorOccured(sbw_none) const { return this->error_occured; }
private:
    sbw_bool error_occured;
};

#endif // __SEABOW_COMPILER_HPP__