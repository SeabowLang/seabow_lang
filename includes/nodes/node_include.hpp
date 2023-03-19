#ifndef __SEABOW_NODE_INCLUDE_HPP__
#define __SEABOW_NODE_INCLUDE_HPP__

#include "nodes/node_try.hpp"

class SBW_NodeInclude: public SBW_Node
{
public:
    SBW_NodeInclude(sbw_ulong line, sbw_ulong column, sbw_string name, sbw_string alias, std::vector<sbw_string> elts);
    virtual ~SBW_NodeInclude();

    inline sbw_node_type Type(sbw_none) const { return NT_INCLUDE; }

    inline sbw_string Name(sbw_none) const { return this->name; }
    inline sbw_string Alias(sbw_none) const { return this->alias; }
    inline std::vector<sbw_string> Elements(sbw_none) const { return this->elements; }
private:
    sbw_string name;
    sbw_string alias;
    std::vector<sbw_string> elements;
};

#endif // __SEABOW_NODE_INCLUDE_HPP__