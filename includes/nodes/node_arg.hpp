#ifndef __SEABOW_NODE_ARGUMENT_HPP__
#define __SEABOW_NODE_ARGUMENT_HPP__

#include "nodes/node_param.hpp"

class SBW_NodeArg: public SBW_Node
{
public:
    SBW_NodeArg(sbw_ulong line, sbw_ulong column, sbw_string name, SBW_Node *expr);
    virtual ~SBW_NodeArg();

    inline sbw_node_type Type(sbw_none) const { return NT_ARGUMENT; }

    inline sbw_string Name(sbw_none) const { return this->name; }
    inline SBW_Node *Expression(sbw_none) const { return this->expression; }
private:
    sbw_string name;
    SBW_Node *expression;
};

#endif // __SEABOW_NODE_ARGUMENT_HPP__