#ifndef __SEABOW_INTERPRETER_HPP__
#define __SEABOW_INTERPRETER_HPP__

#include "parser.hpp"

#define UNASSIGNABLE_ERROR  0xff

class SBW_Variable 
{
public:
    SBW_Variable();
    SBW_Variable(SBW_Value *value, sbw_ubyte mod);
    virtual ~SBW_Variable();

    inline SBW_Value *Value(sbw_none) const { return this->value; }
    inline sbw_ubyte Modifier(sbw_none) const { return this->modifier; }
    inline sbw_none AddModifier(sbw_ubyte mod) { this->modifier += mod; }
private:
    SBW_Value *value;
    sbw_ubyte modifier;
};

class SBW_Interpreter 
{
public:
    SBW_Interpreter();
    virtual ~SBW_Interpreter();

    sbw_none Perform(sbw_none);
private:
    sbw_bool statement;
    std::unordered_map<sbw_string, SBW_Variable*> data;

    sbw_none StartInterpreter(sbw_string code);

    SBW_Variable *InterpretNode(SBW_Node *node);
    SBW_Variable *InterpretNodeBad(SBW_Node *node);
    SBW_Variable *InterpretCompound(SBW_Node *node);

    SBW_Variable *InterpretVarDecl(SBW_Node *node);
    SBW_Variable *InterpretVarCall(SBW_Node *node);

    SBW_Variable *InterpretLiteral(SBW_Node *node);
    SBW_Variable *InterpretParenthesized(SBW_Node *node);

    SBW_Variable *InterpretBinaryExpression(SBW_Node *node);
    SBW_Variable *InterpretUnaryExpression(SBW_Node *node);
};

#endif // __SEABOW_INTERPRETER_HPP__