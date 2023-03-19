#ifndef __SEABOW_NODE_CONTINUE_HPP__
#define __SEABOW_NODE_CONTINUE_HPP__

#include "nodes/node_break.hpp"

class SBW_NodeContinue: public SBW_Node
{
public:
    inline SBW_NodeContinue(sbw_ulong line, sbw_ulong column): SBW_Node(line, column) {}
    inline virtual ~SBW_NodeContinue() {}

    inline sbw_node_type Type(sbw_none) const { return NT_CONTINUE; }
};

#endif // __SEABOW_NODE_CONTINUE_HPP__