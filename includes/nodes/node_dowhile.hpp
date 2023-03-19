#ifndef __SEABOW_NODE_DOWHILE_HPP__
#define __SEABOW_NODE_DOWHILE_HPP__

#include "nodes/node_while.hpp"

class SBW_NodeDowhile: public SBW_Node
{
public:
    SBW_NodeDowhile(sbw_ulong line, sbw_ulong column, SBW_Node *body, SBW_Node *condition);
    virtual ~SBW_NodeDowhile();

    inline sbw_node_type Type(sbw_none) const { return NT_DOWHILE; }

    inline SBW_Node *Body(sbw_none) const { return this->body; }
    inline SBW_Node *Condition(sbw_none) const { return this->condition; }
private:
    SBW_Node *body, *condition;
};

#endif // __SEABOW_NODE_DOWHILE_HPP__