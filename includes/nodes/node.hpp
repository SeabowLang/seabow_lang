#ifndef __SEABOW_NODE_HPP__
#define __SEABOW_NODE_HPP__

#include "values/value_any.hpp"

enum sbw_node_type: sbw_ubyte {
    NT_BAD = 0xff, NT_COMPOUND = 0xfe, NT_UNDEFINED = 0xfd,

    NT_VARIABLE_DECLARATION = 0x00, /*NT_VARIABLE_ASSIGNMENT = 0x01,*/ NT_VARIABLE_CALL = 0x02,
    NT_FUNCTION_DECLARATION = 0x10, NT_FUNCTION_CALL = 0x11, NT_PARAMETER = 0x12, NT_ARGUMENT = 0x13,

    NT_LITERAL = 0x20, NT_PARENTHESIZED = 0x21, NT_ARRAY = 0x22,

    NT_IF = 0x30, NT_ELIF = 0x31, NT_ELSE = 0x32, NT_QUEST_OP = 0x33,
    NT_SWITCH = 0x38, NT_CASE = 0x39, NT_DEFAULT = 0x3a,

    NT_FOR = 0x40, NT_FOREACH = 0x41, NT_WHILE = 0x42, NT_DOWHILE = 0x43,

    NT_TRY = 0x50, NT_CATCH = 0x51,

    NT_BREAK = 0x60, NT_CONTINUE = 0x61, NT_RETURN = 0x62,

    NT_INCLUDE = 0x70, NT_IMPORT = 0x71,

    NT_BINARY_EXPR = 0x78, NT_UNARY_EXPR = 0x79, NT_CONVERT_EXPR = 0x7a,

    NT_ENUMERATION = 0x88, NT_STRUCTURE = 0x89
};

class SBW_Node
{
public:
    SBW_Node(sbw_ulong line, sbw_ulong column);
    inline virtual ~SBW_Node() {}

    inline virtual sbw_node_type Type(sbw_none) const { return NT_UNDEFINED; }

    inline sbw_ulong Line(sbw_none) const { return this->line; }
    inline sbw_ulong Column(sbw_none) const { return this->column; }
protected:
    sbw_ulong line, column;
};

#endif // __SEABOW_NODE_HPP__