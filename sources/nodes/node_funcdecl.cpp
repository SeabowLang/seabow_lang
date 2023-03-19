#include "nodes/node_funcdecl.hpp"

SBW_NodeFuncDecl::SBW_NodeFuncDecl(sbw_ulong line, sbw_ulong column, sbw_value_type f_type, sbw_string name, std::vector<SBW_Node*> params, SBW_Node *body)
    : SBW_Node(line, column)
{
    this->func_type = f_type;
    this->name = name;
    this->params = params;
    this->body = body;
}

SBW_NodeFuncDecl::~SBW_NodeFuncDecl()
{
    delete this->body;

    while (!this->params.empty())
    {
        delete this->params.back();
        this->params.pop_back();
    }
}