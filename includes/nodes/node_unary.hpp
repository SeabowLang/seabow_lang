#ifndef __SEABOW_NODE_UNARY_HPP__
#define __SEABOW_NODE_UNARY_HPP__

#include "nodes/node_binary.hpp"

class SBW_NodeUnary: public SBW_Node
{
public:
    SBW_NodeUnary(sbw_ulong line, sbw_ulong column, SBW_Node *operand, sbw_token_type op_type);
    virtual ~SBW_NodeUnary();

    inline sbw_node_type Type(sbw_none) const { return NT_UNARY_EXPR; }

    inline SBW_Node *Operand(sbw_none) const { return this->operand; }
    inline sbw_token_type OpType(sbw_none) const { return this->op_type; }
private:
    SBW_Node *operand;
    sbw_token_type op_type;
};

#endif // __SEABOW_NODE_UNARY_HPP__