#include "nodes/node_bad.hpp"

SBW_NodeBad::SBW_NodeBad(sbw_ulong line, sbw_ulong column, SBW_ValueError *err)
    : SBW_Node(line, column)
{
    this->err = err;
}