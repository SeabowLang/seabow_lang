#ifndef __SEABOW_NODE_FOR_HPP__
#define __SEABOW_NODE_FOR_HPP__

#include "nodes/node_continue.hpp"

class SBW_NodeFor: public SBW_Node
{
public:
    SBW_NodeFor(sbw_ulong line, sbw_ulong column, SBW_Node *loop_val, SBW_Node *condition, SBW_Node *loop_expr, SBW_Node *body);
    virtual ~SBW_NodeFor();

    inline sbw_node_type Type(sbw_none) const { return NT_FOR; }

    inline SBW_Node *LoopVal(sbw_none) const { return this->loop_val; }
    inline SBW_Node *Condition(sbw_none) const { return this->condition; }
    inline SBW_Node *LoopExpr(sbw_none) const { return this->loop_expr; }
    inline SBW_Node *Body(sbw_none) const { return this->body; }
private:
    SBW_Node *loop_val, *condition, *loop_expr, *body;
};

#endif // __SEABOW_NODE_FOR_HPP__