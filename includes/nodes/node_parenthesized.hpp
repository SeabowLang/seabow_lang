#ifndef __SEABOW_NODE_PARENTHESIZED_HPP__
#define __SEABOW_NODE_PARENTHESIZED_HPP__

#include "nodes/node_literal.hpp"

class SBW_NodeParenthesized: public SBW_Node
{
public:
    SBW_NodeParenthesized(sbw_ulong line, sbw_ulong column, SBW_Node *expr);
    virtual ~SBW_NodeParenthesized();

    inline sbw_node_type Type(sbw_none) const { return NT_PARENTHESIZED; }

    inline SBW_Node *Expression(sbw_none) const { return this->expression; }
private:
    SBW_Node *expression;
};

#endif // __SEABOW_NODE_PARENTHESIZED_HPP__