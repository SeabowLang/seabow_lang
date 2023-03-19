#ifndef __SEABOW_NODE_QUEST_HPP__
#define __SEABOW_NODE_QUEST_HPP__

#include "nodes/node_switch.hpp"

class SBW_NodeQuest: public SBW_Node
{
public:
    SBW_NodeQuest(sbw_ulong line, sbw_ulong column, SBW_Node *cnd, SBW_Node *f, SBW_Node *s);
    ~SBW_NodeQuest();

    inline sbw_node_type Type(sbw_none) const { return NT_QUEST_OP; }

    inline SBW_Node *Condition(sbw_none) const { return this->condition; }
    inline SBW_Node *First(sbw_none) const { return this->first; }
    inline SBW_Node *Second(sbw_none) const { return this->second; }
private:
    SBW_Node *condition, *first, *second;
};

#endif // __SEABOW_NODE_QUEST_HPP__