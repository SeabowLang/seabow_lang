#include "nodes/node_parenthesized.hpp"

SBW_NodeParenthesized::SBW_NodeParenthesized(sbw_ulong line, sbw_ulong column, SBW_Node *expr)
    : SBW_Node(line, column)
{
    this->expression = expr;
}

SBW_NodeParenthesized::~SBW_NodeParenthesized() { delete this->expression; }