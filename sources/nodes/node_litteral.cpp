#include "nodes/node_litteral.hpp"

SBW_NodeLitteral::SBW_NodeLitteral(sbw_ulong line, sbw_ulong column, SBW_Value *val)
    : SBW_Node(line, column)
{
    this->value = val;
}

SBW_NodeLitteral::~SBW_NodeLitteral() { delete this->value; }