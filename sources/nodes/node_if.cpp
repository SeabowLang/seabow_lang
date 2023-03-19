#include "nodes/node_if.hpp"

SBW_NodeElif::SBW_NodeElif(sbw_ulong line, sbw_ulong column, SBW_Node *cnd, SBW_Node *bd)
    : SBW_Node(line, column)
{
    this->condition = cnd;
    this->body = bd;
}

SBW_NodeElif::~SBW_NodeElif()
{
    delete this->condition;
    delete this->body;
}


SBW_NodeIf::SBW_NodeIf(sbw_ulong line, sbw_ulong column, SBW_Node *condition, SBW_Node *body, SBW_Node *else_body, std::vector<SBW_Node*> elif_cl)
    : SBW_Node(line, column)
{
    this->condition = condition;
    this->body = body;
    this->else_body = else_body;
    this->elif_clauses = elif_cl;
}

SBW_NodeIf::~SBW_NodeIf()
{
    delete this->condition;
    delete this->body;
    if (this->else_body)
        delete this->else_body;
    
    while (!this->elif_clauses.empty())
    {
        delete this->elif_clauses.back();
        this->elif_clauses.pop_back();
    }
}