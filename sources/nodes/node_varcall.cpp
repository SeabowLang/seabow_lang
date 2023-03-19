#include "nodes/node_varcall.hpp"

SBW_NodeVarCall::SBW_NodeVarCall(sbw_ulong line, sbw_ulong column, sbw_string name)
    : SBW_Node(line, column)
{
    this->name = name;
}