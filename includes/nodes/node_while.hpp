#ifndef __SEABOW_NODE_WHILE_HPP__
#define __SEABOW_NODE_WHILE_HPP__

#include "nodes/node_foreach.hpp"

class SBW_NodeWhile: public SBW_Node
{
public:
    SBW_NodeWhile(sbw_ulong line, sbw_ulong column, SBW_Node *condition, SBW_Node *body);
    virtual ~SBW_NodeWhile();

    inline sbw_node_type Type(sbw_none) const { return NT_WHILE; }

    inline SBW_Node *Body(sbw_none) const { return this->body; }
    inline SBW_Node *Condition(sbw_none) const { return this->condition; }
private:
    SBW_Node *body, *condition;
};

#endif // __SEABOW_NODE_WHILE_HPP__