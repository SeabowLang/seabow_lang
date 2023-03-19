#include "nodes/node_funccall.hpp"

SBW_NodeFuncCall::SBW_NodeFuncCall(sbw_ulong line, sbw_ulong column, sbw_string name, std::vector<SBW_Node*> args)
    : SBW_Node(line, column)
{
    this->name = name;
    this->args = args;
}

SBW_NodeFuncCall::~SBW_NodeFuncCall()
{
    while (!this->args.empty())
    {
        delete this->args.back();
        this->args.pop_back();
    }
}