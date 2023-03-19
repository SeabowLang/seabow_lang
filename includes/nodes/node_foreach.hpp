#ifndef __SEABOW_NODE_FOREACH_HPP__
#define __SEABOW_NODE_FOREACH_HPP__

#include "nodes/node_for.hpp"

class SBW_NodeForeach: public SBW_Node
{
public:
    SBW_NodeForeach(sbw_ulong line, sbw_ulong column, SBW_Node *loop_val, SBW_Node *container, SBW_Node *body);
    virtual ~SBW_NodeForeach();

    inline sbw_node_type Type(sbw_none) const { return NT_FOREACH; }

    inline SBW_Node *LoopVal(sbw_none) const { return this->loop_val; }
    inline SBW_Node *Container(sbw_none) const { return this->container; }
    inline SBW_Node *Body(sbw_none) const { return this->body; }
private:
    SBW_Node *loop_val, *container, *body;
};

#endif // __SEABOW_NODE_FOREACH_HPP__