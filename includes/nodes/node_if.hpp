#ifndef __SEABOW_NODE_IF_HPP__
#define __SEABOW_NODE_IF_HPP__

#include "nodes/node_parenthesized.hpp"

class SBW_NodeElif: public SBW_Node
{
public:
    SBW_NodeElif(sbw_ulong line, sbw_ulong column, SBW_Node *cnd, SBW_Node *bd);
    virtual ~SBW_NodeElif();

    inline sbw_node_type Type(sbw_none) const { return NT_ELIF; }

    inline SBW_Node *Condition(sbw_none) const { return this->condition; }
    inline SBW_Node *Body(sbw_none) const { return this->body; }
private:
    SBW_Node *condition, *body;
};

class SBW_NodeIf: public SBW_Node
{
public:
    SBW_NodeIf(sbw_ulong line, sbw_ulong column, SBW_Node *condition, SBW_Node *body, SBW_Node *else_body, std::vector<SBW_Node*> elif_cl);
    virtual ~SBW_NodeIf();

    inline sbw_node_type Type(sbw_none) const { return NT_IF; }

    inline SBW_Node *Condition(sbw_none) const { return this->condition; }
    inline SBW_Node *Body(sbw_none) const { return this->body; }
    inline SBW_Node *ElseBody(sbw_none) const { return this->else_body; }
    inline std::vector<SBW_Node*> ElifClauses(sbw_none) const { return this->elif_clauses; }
private:
    SBW_Node *condition, *body, *else_body;
    std::vector<SBW_Node*> elif_clauses;
};

#endif // __SEABOW_NODE_IF_HPP__