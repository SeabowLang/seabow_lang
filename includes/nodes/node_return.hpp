#ifndef __SEABOW_NODE_RETURN_HPP__
#define __SEABOW_NODE_RETURN_HPP__

#include "nodes/node_quest.hpp"

class SBW_NodeReturn: public SBW_Node
{
public:
    SBW_NodeReturn(sbw_ulong line, sbw_ulong column, SBW_Node *expr);
    virtual ~SBW_NodeReturn();

    inline sbw_node_type Type(sbw_none) const { return NT_RETURN; }

    inline SBW_Node *Expression(sbw_none) const { return this->expression; }
private:
    SBW_Node *expression;
};

#endif // __SEABOW_NODE_RETURN_HPP__