#include "nodes/node_while.hpp"

SBW_NodeWhile::SBW_NodeWhile(sbw_ulong line, sbw_ulong column, SBW_Node *condition, SBW_Node *body)
    : SBW_Node(line, column)
{
    this->condition = condition;
    this->body = body;
}

SBW_NodeWhile::~SBW_NodeWhile()
{
    delete this->condition;
    delete this->body;
}