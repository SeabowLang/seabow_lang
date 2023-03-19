#ifndef __SEABOW_NODE_LITERAL_HPP__
#define __SEABOW_NODE_LITERAL_HPP__

#include "nodes/node_arg.hpp"

class SBW_NodeLiteral: public SBW_Node
{
public:
    SBW_NodeLiteral(sbw_ulong line, sbw_ulong column, SBW_Value *val);
    virtual ~SBW_NodeLiteral();

    inline sbw_node_type Type(sbw_none) const { return NT_LITERAL; }

    inline SBW_Value *Value(sbw_none) const { return this->value; }
private:
    SBW_Value *value;
};

#endif // __SEABOW_NODE_LITTERAL_HPP__