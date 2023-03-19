#include "nodes/node_param.hpp"

SBW_NodeParam::SBW_NodeParam(sbw_ulong line, sbw_ulong column, sbw_value_type p_type, sbw_string name, SBW_Node *d_value)
    : SBW_Node(line, column)
{
    this->param_type = p_type;
    this->name = name;
    this->default_value = d_value;
}

SBW_NodeParam::~SBW_NodeParam()
{
    if (this->default_value)
        delete this->default_value;
}