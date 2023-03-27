#ifndef __SEABOW_VALUE_POINTER_HPP__
#define __SEABOW_VALUE_POINTER_HPP__

#include "values/value_type.hpp"

class SBW_ValuePointer: public SBW_Value
{
public:
    SBW_ValuePointer(sbw_none *val, sbw_value_type ptr_type);
    inline virtual ~SBW_ValuePointer();

    inline sbw_value_type Type(sbw_none) const { return VT_POINTER_; }

    inline sbw_none *Get(sbw_none) const { return this->value; }
    inline sbw_value_type PtrType(sbw_none) const { return this->ptr_type; }
    SBW_Value *AutoConvert(sbw_value_type dest_type);
    inline sbw_bool IsNull(sbw_none) const { return this->ptr_type == VT_NULL_; }

    SBW_Value *operator*(sbw_none);

    SBW_Value *operator_convert(sbw_value_type dest_type);
    SBW_Value *operator_abs(sbw_none);
private:
    sbw_none *value;
    sbw_value_type ptr_type;
};

#endif // __SEABOW_VALUE_POINTER_HPP__