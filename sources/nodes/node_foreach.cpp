#include "nodes/node_foreach.hpp"

SBW_NodeForeach::SBW_NodeForeach(sbw_ulong line, sbw_ulong column, SBW_Node *loop_val, SBW_Node *container, SBW_Node *body)
    : SBW_Node(line, column)
{
    this->loop_val = loop_val;
    this->container = container;
    this->body = body;
}

SBW_NodeForeach::~SBW_NodeForeach()
{
    delete this->loop_val;
    delete this->container;
    delete this->body;
}