#include "nodes/node_arg.hpp"

SBW_NodeArg::SBW_NodeArg(sbw_ulong line, sbw_ulong column, sbw_string name, SBW_Node *expr)
    : SBW_Node(line, column)
{
    this->name = name;
    this->expression = expr;
}

SBW_NodeArg::~SBW_NodeArg() { delete this->expression; }