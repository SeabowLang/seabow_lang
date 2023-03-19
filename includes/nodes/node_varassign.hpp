#ifndef __SEABOW_NODE_VAR_ASSIGNMENT_HPP__
#define __SEABOW_NODE_VAR_ASSIGNMENT_HPP__

#include "nodes/node_vardecl.hpp"

class SBW_NodeVarAssign: public SBW_Node
{
public:
    SBW_NodeVarAssign(sbw_ulong line, sbw_ulong column, sbw_string name, sbw_token_type eq_t, SBW_Node *value);
    virtual ~SBW_NodeVarAssign();

    inline sbw_node_type Type(sbw_none) const { return NT_VARIABLE_ASSIGNMENT; }

    inline sbw_string Name(sbw_none) const { return this->name; }
    inline sbw_token_type EqType(sbw_none) const { return this->eq_type; }
    inline SBW_Node *Value(sbw_none) const { return this->value; }
private:
    sbw_string name;
    sbw_token_type eq_type;
    SBW_Node *value;
};

#endif // __SEABOW_NODE_VAR_ASSIGNMENT_HPP__