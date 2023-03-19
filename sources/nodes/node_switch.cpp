#include "nodes/node_switch.hpp"

SBW_NodeCase::SBW_NodeCase(sbw_ulong line, sbw_ulong column, std::vector<SBW_Node*> expr, SBW_Node *bd)
    : SBW_Node(line, column)
{
    this->expressions = expr;
    this->body = bd;
}

SBW_NodeCase::~SBW_NodeCase()
{
    delete this->body;

    while (!this->expressions.empty())
    {
        delete this->expressions.back();
        this->expressions.pop_back();
    }
}


SBW_NodeSwitch::SBW_NodeSwitch(sbw_ulong line, sbw_ulong column, SBW_Node *cnd, SBW_Node *default_bd, std::vector<SBW_Node*> case_cl)
    : SBW_Node(line, column)
{
    this->condition = cnd;
    this->default_body = default_bd;
    this->case_clauses = case_cl;
}

SBW_NodeSwitch::~SBW_NodeSwitch()
{
    delete this->condition;
    if (this->default_body)
        delete this->default_body;
    
    while (!this->case_clauses.empty())
    {
        delete this->case_clauses.back();
        this->case_clauses.pop_back();
    }
}