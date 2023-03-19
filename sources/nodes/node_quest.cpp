#include "nodes/node_quest.hpp"

SBW_NodeQuest::SBW_NodeQuest(sbw_ulong line, sbw_ulong column, SBW_Node *cnd, SBW_Node *f, SBW_Node *s)
    : SBW_Node(line, column)
{
    this->condition = cnd;
    this->first = f;
    this->second = s;
}

SBW_NodeQuest::~SBW_NodeQuest()
{
    delete this->condition;
    delete this->first;
    delete this->second;
}