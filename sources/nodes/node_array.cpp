#include "nodes/node_array.hpp"

SBW_NodeArray::SBW_NodeArray(sbw_ulong line, sbw_ulong column, std::vector<SBW_Node*> val)
    : SBW_Node(line, column) 
{
    this->values = val;
}

SBW_NodeArray::~SBW_NodeArray()
{
    while (!this->values.empty())
    {
        delete this->values.back();
        this->values.pop_back();
    }
}