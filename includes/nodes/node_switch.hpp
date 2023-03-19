#ifndef __SEABOW_NODE_SWITCH_HPP__
#define __SEABOW_NODE_SWITCH_HPP__

#include "nodes/node_if.hpp"

class SBW_NodeCase: public SBW_Node
{
public:
    SBW_NodeCase(sbw_ulong line, sbw_ulong column, std::vector<SBW_Node*> expr, SBW_Node *bd);
    virtual ~SBW_NodeCase();

    inline sbw_node_type Type(sbw_none) const { return NT_CASE; }

    inline std::vector<SBW_Node*> Expressions(sbw_none) const { return this->expressions; }
    inline SBW_Node *Body(sbw_none) const { return this->body; }
private:
    std::vector<SBW_Node*> expressions;
    SBW_Node *body;
};

class SBW_NodeSwitch: public SBW_Node
{
public:
    SBW_NodeSwitch(sbw_ulong line, sbw_ulong column, SBW_Node *cnd, SBW_Node *default_bd, std::vector<SBW_Node*> case_cl);
    virtual ~SBW_NodeSwitch();

    inline sbw_node_type Type(sbw_none) const { return NT_SWITCH; }

    inline SBW_Node *Condition(sbw_none) const { return this->condition; }
    inline SBW_Node *DefaultBody(sbw_none) const { return this->default_body; }
    inline std::vector<SBW_Node*> CaseClauses(sbw_none) const { return this->case_clauses; }
private:
    SBW_Node *condition, *default_body;
    std::vector<SBW_Node*> case_clauses;
};

#endif // __SEABOW_NODE_SWITCH_HPP__