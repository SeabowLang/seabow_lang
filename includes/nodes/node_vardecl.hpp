#ifndef __SEABOW_NODE_VAR_DECLARATION_HPP__
#define __SEABOW_NODE_VAR_DECLARATION_HPP__

#include "nodes/node_compound.hpp"

class SBW_NodeVarDecl: public SBW_Node
{
public:
    SBW_NodeVarDecl(sbw_ulong line, sbw_ulong column, sbw_value_type vtype, sbw_string name, SBW_Node *value);
    virtual ~SBW_NodeVarDecl();

    inline sbw_node_type Type(sbw_none) const { return NT_VARIABLE_DECLARATION; }

    inline sbw_value_type VType(sbw_none) const { return this->vtype; }
    inline sbw_string Name(sbw_none) const { return this->name; }
    inline SBW_Node *Value(sbw_none) const { return this->value; }
private:
    sbw_value_type vtype;
    sbw_string name;
    SBW_Node *value;
};

#endif // __SEABOW_NODE_VAR_DECLARATION_HPP__