#include "nodes/node_return.hpp"

SBW_NodeReturn::SBW_NodeReturn(sbw_ulong line, sbw_ulong column, SBW_Node *expr)
    : SBW_Node(line, column)
{
    this->expression = expr;
}

SBW_NodeReturn::~SBW_NodeReturn() { delete this->expression; }