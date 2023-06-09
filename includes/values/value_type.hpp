#ifndef __SEABOW_VALUE_TYPE_HPP__
#define __SEABOW_VALUE_TYPE_HPP__

#include "values/value_error.hpp"

class SBW_ValueType: public SBW_Value
{
public:
    SBW_ValueType(sbw_value_type t);
    SBW_ValueType(sbw_value_type t, sbw_string m);
    inline virtual ~SBW_ValueType() {}

    inline sbw_value_type Type(sbw_none) const { return VT_TYPE_; }

    inline sbw_value_type Get(sbw_none) const { return this->value; }
    SBW_Value *AutoConvert(sbw_value_type dest_type);
    inline sbw_bool IsNull(sbw_none) const { return this->value == VT_XXXXX_; }
    inline sbw_string More(sbw_none) const { return this->more; }

    SBW_Value *operator_convert(sbw_value_type dest_type);
private:
    sbw_value_type value;
    sbw_string more;
};

#endif // __SEABOW_VALUE_TYPE_HPP__