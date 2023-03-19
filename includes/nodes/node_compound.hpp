#ifndef __SEABOW_NODE_COMPOUND_HPP__
#define __SEABOW_NODE_COMPOUND_HPP__

#include "nodes/node_bad.hpp"

class SBW_NodeCompound: public SBW_Node
{
public:
    SBW_NodeCompound(sbw_ulong line, sbw_ulong column, std::vector<SBW_Node*> stats);
    virtual ~SBW_NodeCompound();

    inline sbw_node_type Type(sbw_none) const { return NT_COMPOUND; }

    inline std::vector<SBW_Node*> Statements(sbw_none) const { return this->statements; }
private:
    std::vector<SBW_Node*> statements;
};

#endif // __SEABOW_NODE_COMPOUND_HPP__