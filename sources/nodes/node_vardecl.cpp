#include "nodes/node_vardecl.hpp"

SBW_NodeVarDecl::SBW_NodeVarDecl(sbw_ulong line, sbw_ulong column, sbw_value_type vt, sbw_string name, SBW_Node *value)
    : SBW_Node(line, column)
{
    this->vtype = vt;
    this->name = name;
    this->value = value;
}

SBW_NodeVarDecl::~SBW_NodeVarDecl()
{
    if (this->value)
        delete this->value;
}