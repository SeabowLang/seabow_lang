#ifndef __SEABOW_NODE_LITTERAL_HPP__
#define __SEABOW_NODE_LITTERAL_HPP__

#include "nodes/node_arg.hpp"

class SBW_NodeLitteral: public SBW_Node
{
public:
    SBW_NodeLitteral(sbw_ulong line, sbw_ulong column, SBW_Value *val);
    virtual ~SBW_NodeLitteral();

    inline sbw_node_type Type(sbw_none) const { return NT_LITERAL; }

    inline SBW_Value *Value(sbw_none) const { return this->value; }
private:
    SBW_Value *value;
};

#endif // __SEABOW_NODE_LITTERAL_HPP__