#ifndef __SEABOW_NODE_FUNC_CALL_HPP__
#define __SEABOW_NODE_FUNC_CALL_HPP__

#include "nodes/node_funcdecl.hpp"

class SBW_NodeFuncCall: public SBW_Node
{
public:
    SBW_NodeFuncCall(sbw_ulong line, sbw_ulong column, sbw_string name, std::vector<SBW_Node*> args);
    virtual ~SBW_NodeFuncCall();

    inline sbw_node_type Type(sbw_none) const { return NT_FUNCTION_CALL; }

    inline sbw_string Name(sbw_none) const { return this->name; }
    inline std::vector<SBW_Node*> Args(sbw_none) const { return this->args; }
private:
    sbw_string name;
    std::vector<SBW_Node*> args;
};

#endif // __SEABOW_NODE_FUNC_CALL_HPP__