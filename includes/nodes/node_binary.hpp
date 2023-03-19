#ifndef __SEABOW_NODE_BINARY_HPP__
#define __SEABOW_NODE_BINARY_HPP__

#include "nodes/node_dowhile.hpp"

class SBW_NodeBinary: public SBW_Node
{
public:
    SBW_NodeBinary(sbw_ulong line, sbw_ulong column, SBW_Node *left, SBW_Node *right, sbw_token_type op_type);
    virtual ~SBW_NodeBinary();

    inline sbw_node_type Type(sbw_none) const { return NT_BINARY_EXPR; }

    inline SBW_Node *Left(sbw_none) const { return this->left; }
    inline SBW_Node *Right(sbw_none) const { return this->right; }
    inline sbw_token_type OpType(sbw_none) const { return this->op_type; }
private:
    SBW_Node *left, *right;
    sbw_token_type op_type;
};

#endif // __SEABOW_NODE_BINARY_HPP__