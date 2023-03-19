#include "nodes/node_literal.hpp"

SBW_NodeLiteral::SBW_NodeLiteral(sbw_ulong line, sbw_ulong column, SBW_Value *val)
    : SBW_Node(line, column)
{
    this->value = val;
}

SBW_NodeLiteral::~SBW_NodeLiteral() { delete this->value; }