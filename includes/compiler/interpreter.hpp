#ifndef __SEABOW_INTERPRETER_HPP__
#define __SEABOW_INTERPRETER_HPP__

#include "parser.hpp"

class SBW_Interpreter {
public:
    SBW_Interpreter();
    virtual ~SBW_Interpreter();

    sbw_none Perform(sbw_none);
private:
    sbw_bool statement;

    sbw_none Interpret(sbw_string code);
};

#endif // __SEABOW_INTERPRETER_HPP__