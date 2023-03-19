#ifndef __SEABOW_VALUE_ERROR_HPP__
#define __SEABOW_VALUE_ERROR_HPP__

#include "values/value_list.hpp"

class SBW_ValueError: public SBW_Value
{
public:
    SBW_ValueError(sbw_string name, sbw_string dtls, sbw_ulong l, sbw_ulong c);
    inline virtual ~SBW_ValueError() {}

    inline sbw_value_type Type(sbw_none) const { return VT_ERROR_; }

    inline sbw_string Name(sbw_none) const { return this->name; }
    inline sbw_string Details(sbw_none) const { return this->details; }
    inline sbw_ulong Line(sbw_none) const { return this->line; }
    inline sbw_ulong Column(sbw_none) const { return this->column; }
    inline sbw_none SetLine(sbw_ulong l) { this->line = l; }
    inline sbw_none SetColumn(sbw_ulong c) { this->column = c; }
    inline sbw_bool IsNull(sbw_none) const { return this->name.size() == 0; }
    SBW_Value *operator_convert(sbw_value_type dest_type);
    SBW_Value *AutoConvert(sbw_value_type dest_type);
private:
    sbw_string name, details;
    sbw_ulong line, column;
};

#endif // __SEABOW_VALUE_ERROR_HPP__