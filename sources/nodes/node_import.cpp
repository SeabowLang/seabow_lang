#include "nodes/node_import.hpp"

SBW_NodeImport::SBW_NodeImport(sbw_ulong line, sbw_ulong column, sbw_string name, sbw_string alias, std::vector<sbw_string> elts)
    : SBW_Node(line, column)
{
    this->name = name;
    this->alias = alias;
    this->elements = elts;
}

SBW_NodeImport::~SBW_NodeImport()
{
    while (!this->elements.empty())
        this->elements.pop_back();
}