#include "nodes/node_convert.hpp"

SBW_NodeConvert::SBW_NodeConvert(sbw_ulong line, sbw_ulong column, sbw_value_type dt, SBW_Node *expr)
    : SBW_Node(line, column)
{
    this->dest_type = dt;
    this->expression = expr;
}

SBW_NodeConvert::~SBW_NodeConvert() { delete this->expression; }