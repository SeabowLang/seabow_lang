#include "nodes/node_dowhile.hpp"

SBW_NodeDowhile::SBW_NodeDowhile(sbw_ulong line, sbw_ulong column, SBW_Node *body, SBW_Node *condition)
    : SBW_Node(line, column)
{
    this->body = body;
    this->condition = condition;
}

SBW_NodeDowhile::~SBW_NodeDowhile()
{
    delete this->body;
    delete this->condition;
}