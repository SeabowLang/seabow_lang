#include "nodes/node_try.hpp"

SBW_NodeCatch::SBW_NodeCatch(sbw_ulong line, sbw_ulong column, std::vector<sbw_string> err_t, SBW_Node *body)
    : SBW_Node(line, column)
{
    this->err_types = err_t;
    this->body = body;
}

SBW_NodeCatch::~SBW_NodeCatch()
{
    delete this->body;
    while (!this->err_types.empty())
        this->err_types.pop_back();
}

SBW_NodeTry::SBW_NodeTry(sbw_ulong line, sbw_ulong column, SBW_Node *body, sbw_string name, std::vector<SBW_Node*> c_cl)
    : SBW_Node(line, column)
{
    this->body = body;
    this->var_name = name;
    this->catch_clauses = c_cl;
}

SBW_NodeTry::~SBW_NodeTry()
{
    delete this->body;
    while (!this->catch_clauses.empty())
    {
        delete this->catch_clauses.back();
        this->catch_clauses.pop_back();
    }
}