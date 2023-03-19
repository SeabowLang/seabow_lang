#ifndef __SEABOW_VAR_CALL_HPP__
#define __SEABOW_VAR_CALL_HPP__

#include "nodes/node_varassign.hpp"

class SBW_NodeVarCall: public SBW_Node
{
public:
    SBW_NodeVarCall(sbw_ulong line, sbw_ulong column, sbw_string name);
    inline virtual ~SBW_NodeVarCall() {}

    inline sbw_node_type Type(sbw_none) const { return NT_VARIABLE_CALL; }

    inline sbw_string Name(sbw_none) const { return this->name; }
private:
    sbw_string name;
};

#endif // __SEABOW_VAR_CALL_HPP__