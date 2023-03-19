#include "nodes/node_for.hpp"

SBW_NodeFor::SBW_NodeFor(sbw_ulong line, sbw_ulong column, SBW_Node *loop_val, SBW_Node *condition, SBW_Node *loop_expr, SBW_Node *body)
    : SBW_Node(line, column)
{
    this->loop_val = loop_val;
    this->condition = condition;
    this->loop_expr = loop_expr;
    this->body = body;
}

SBW_NodeFor::~SBW_NodeFor()
{
    delete this->loop_val;
    delete this->condition;
    delete this->loop_expr;
    delete this->body;
}