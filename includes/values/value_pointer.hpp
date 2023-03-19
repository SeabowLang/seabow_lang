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
    inline sbw_bool IsNull(sbw_none) const { return !this->value; }
    sbw_string ToString(sbw_none) const;
private:
    sbw_none *value;
    sbw_value_type ptr_type;
};

#endif // __SEABOW_VALUE_POINTER_HPP__