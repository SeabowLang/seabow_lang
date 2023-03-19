#include "nodes/node_varassign.hpp"

SBW_NodeVarAssign::SBW_NodeVarAssign(sbw_ulong line, sbw_ulong column, sbw_string name, sbw_token_type eq_t, SBW_Node *value)
    : SBW_Node(line, column)
{
    this->name = name;
    this->eq_type = eq_t;
    this->value = value;
}

SBW_NodeVarAssign::~SBW_NodeVarAssign() { delete this->value; }