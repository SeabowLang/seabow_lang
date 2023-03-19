#ifndef __SEABOW_NODE_FUNC_DECLARATION_HPP__
#define __SEABOW_NODE_FUNC_DECLARATION_HPP__

#include "nodes/node_varcall.hpp"

class SBW_NodeFuncDecl: public SBW_Node
{
public:
    SBW_NodeFuncDecl(sbw_ulong line, sbw_ulong column, sbw_value_type f_type, sbw_string name, std::vector<SBW_Node*> params, SBW_Node *body);
    virtual ~SBW_NodeFuncDecl();

    inline sbw_node_type Type(sbw_none) const { return NT_FUNCTION_DECLARATION; }

    inline sbw_value_type FuncType(sbw_none) const { return this->func_type; }
    inline sbw_string Name(sbw_none) const { return this->name; }
    inline std::vector<SBW_Node*> Params(sbw_none) const { return this->params; }
    inline SBW_Node *Body(sbw_none) const { return this->body; }
private:
    sbw_value_type func_type;
    sbw_string name;
    std::vector<SBW_Node*> params;
    SBW_Node *body;
};

#endif // __SEABOW_NODE_FUNC_DECLARATION_HPP__