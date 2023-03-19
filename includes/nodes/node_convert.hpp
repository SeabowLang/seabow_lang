#ifndef __SEABOW_NODE_CONVERT_HPP__
#define __SEABOW_NODE_CONVERT_HPP__

#include "nodes/node_import.hpp"

class SBW_NodeConvert: public SBW_Node
{
public:
    SBW_NodeConvert(sbw_ulong line, sbw_ulong column, sbw_value_type dt, SBW_Node *expr);
    virtual ~SBW_NodeConvert();

    inline sbw_node_type Type(sbw_none) const { return NT_CONVERT_EXPR; }

    inline sbw_value_type DestType(sbw_none) const { return this->dest_type; }
    inline SBW_Node *Expression(sbw_none) const { return this->expression; }
private:
    sbw_value_type dest_type;
    SBW_Node *expression;
};

#endif // __SEABOW_NODE_CONVERT_HPP__