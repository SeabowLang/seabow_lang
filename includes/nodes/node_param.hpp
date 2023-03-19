#ifndef __SEABOW_NODE_PARAM_HPP__
#define __SEABOW_NODE_PARAM_HPP__

#include "nodes/node_funccall.hpp"

class SBW_NodeParam: public SBW_Node
{
public:
    SBW_NodeParam(sbw_ulong line, sbw_ulong column, sbw_value_type p_type, sbw_string name, SBW_Node *d_value);
    virtual ~SBW_NodeParam();

    inline sbw_node_type Type(sbw_none) const { return NT_PARAMETER; }

    inline sbw_value_type ParamType(sbw_none) const { return this->param_type; }
    inline sbw_string Name(sbw_none) const { return this->name; }
    inline SBW_Node *DefaultValue(sbw_none) const { return this->default_value; }
private:
    sbw_value_type param_type;
    sbw_string name;
    SBW_Node *default_value;
};

#endif // __SEABOW_NODE_PARAM_HPP__