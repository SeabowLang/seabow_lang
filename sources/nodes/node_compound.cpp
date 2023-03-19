#include "nodes/node_compound.hpp"

SBW_NodeCompound::SBW_NodeCompound(sbw_ulong line, sbw_ulong column, std::vector<SBW_Node*> stats)
    : SBW_Node(line, column)
{
    this->statements = stats;
}

SBW_NodeCompound::~SBW_NodeCompound()
{
    while (!this->statements.empty())
    {
        delete this->statements.back();
        this->statements.pop_back();
    }
}