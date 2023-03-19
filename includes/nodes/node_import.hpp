#ifndef __SEABOW_NODE_IMPORT_HPP__
#define __SEABOW_NODE_IMPORT_HPP__

#include "nodes/node_include.hpp"

class SBW_NodeImport: public SBW_Node
{
public:
    SBW_NodeImport(sbw_ulong line, sbw_ulong column, sbw_string name, sbw_string alias, std::vector<sbw_string> elts);
    virtual ~SBW_NodeImport();

    inline sbw_node_type Type(sbw_none) const { return NT_IMPORT; }

    inline sbw_string Name(sbw_none) const { return this->name; }
    inline sbw_string Alias(sbw_none) const { return this->alias; }
    inline std::vector<sbw_string> Elements(sbw_none) const { return this->elements; }
private:
    sbw_string name;
    sbw_string alias;
    std::vector<sbw_string> elements;
};

#endif // __SEABOW_NODE_IMPORT_HPP__