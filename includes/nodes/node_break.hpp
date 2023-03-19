#ifndef __SEABOW_NODE_BREAK_HPP__
#define __SEABOW_NODE_BREAK_HPP__

#include "nodes/node_return.hpp"

class SBW_NodeBreak: public SBW_Node
{
public:
    inline SBW_NodeBreak(sbw_ulong line, sbw_ulong column): SBW_Node(line, column) {}
    inline virtual ~SBW_NodeBreak() {}

    inline sbw_node_type Type(sbw_none) const { return NT_BREAK; }
};

#endif // __SEABOW_NODE_BREAK_HPP__