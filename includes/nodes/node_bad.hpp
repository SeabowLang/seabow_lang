#ifndef __SEABOW_NODE_BAD_HPP__
#define __SEABOW_NODE_BAD_HPP__

#include "node.hpp"

class SBW_NodeBad: public SBW_Node
{
public:
    SBW_NodeBad(sbw_ulong line, sbw_ulong column, SBW_ValueError *err);
    inline virtual ~SBW_NodeBad() {}

    inline sbw_node_type Type(sbw_none) const { return NT_BAD; }
    
    inline SBW_ValueError *Err(sbw_none) const { return this->err; }
private:
    SBW_ValueError *err;
};

#endif // __SEABOW_NODE_BAD_HPP__