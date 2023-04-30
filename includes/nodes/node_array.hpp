#ifndef __SEABOW_NODE_ARRAY_HPP__
#define __SEABOW_NODE_ARRAY_HPP__

#include "nodes/node_literal.hpp"

class SBW_NodeArray : public SBW_Node {
public:
    SBW_NodeArray(sbw_ulong line, sbw_ulong column, std::vector<SBW_Node*> val);
    virtual ~SBW_NodeArray();

    inline std::vector<SBW_Node*> Values(sbw_none) const { return this->values; }
    inline sbw_node_type Type(sbw_none) const { return NT_ARRAY; }
private:
    std::vector<SBW_Node*> values;
};

#endif // __SEABOW_NODE_ARRAY_HPP__