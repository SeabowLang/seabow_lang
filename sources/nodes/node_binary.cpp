#include "nodes/node_binary.hpp"

SBW_NodeBinary::SBW_NodeBinary(sbw_ulong line, sbw_ulong column, SBW_Node *left, SBW_Node *right, sbw_token_type op_type)
    : SBW_Node(line, column)
{
    this->left = left;
    this->right = right;
    this->op_type = op_type;
}

SBW_NodeBinary::~SBW_NodeBinary()
{
    delete this->left;
    delete this->right;
}