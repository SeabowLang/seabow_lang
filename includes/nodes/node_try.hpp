#ifndef __SEABOW_NODE_TRY_HPP__
#define __SEABOW_NODE_TRY_HPP__

#include "nodes/node_unary.hpp"

class SBW_NodeCatch: public SBW_Node
{
public:
    SBW_NodeCatch(sbw_ulong line, sbw_ulong column, std::vector<sbw_string> err_t, SBW_Node *body);
    virtual ~SBW_NodeCatch();

    inline sbw_node_type Type(sbw_none) const { return NT_CATCH; }

    inline std::vector<sbw_string> ErrTypes(sbw_none) const { return this->err_types; }
    inline SBW_Node *Body(sbw_none) const { return this->body; }
private:
    std::vector<sbw_string> err_types;
    SBW_Node *body;
};

class SBW_NodeTry: public SBW_Node
{
public:
    SBW_NodeTry(sbw_ulong line, sbw_ulong column, SBW_Node *body, sbw_string name, std::vector<SBW_Node*> c_cl);
    virtual ~SBW_NodeTry();

    inline sbw_node_type Type(sbw_none) const { return NT_TRY; }

    inline SBW_Node *Body(sbw_none) const { return this->body; }
    inline sbw_string VarName(sbw_none) const { return this->var_name; }
    inline std::vector<SBW_Node*> CatchClauses(sbw_none) const { return this->catch_clauses; }
private:
    SBW_Node *body;
    sbw_string var_name;
    std::vector<SBW_Node*> catch_clauses;
};

#endif // __SEABOW_NODE_TRY_HPP__