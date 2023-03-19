#include "nodes/node_unary.hpp"

SBW_NodeUnary::SBW_NodeUnary(sbw_ulong line, sbw_ulong column, SBW_Node *operand, sbw_token_type op_type)
    : SBW_Node(line, column)
{
    this->operand = operand;
    this->op_type = op_type;
}

SBW_NodeUnary::~SBW_NodeUnary() { delete this->operand; }