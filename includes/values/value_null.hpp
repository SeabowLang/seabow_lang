#ifndef __SEABOW_VALUE_NULL_HPP__
#define __SEABOW_VALUE_NULL_HPP__

#include "values/value.hpp"

class SBW_ValueNull: public SBW_Value
{
public:
    inline SBW_ValueNull(sbw_none) {}
    inline virtual ~SBW_ValueNull() {}

    inline virtual sbw_value_type Type(sbw_none) const { return VT_NULL_; }

    virtual SBW_Value *AutoConvert(sbw_value_type dest_type);
    inline virtual sbw_bool IsNull(sbw_none) const { return true; }

    virtual SBW_Value *operator^(SBW_Value *val);
    virtual SBW_Value *operator&(SBW_Value *val);
    virtual SBW_Value *operator|(SBW_Value *val);

    virtual SBW_Value *operator!(sbw_none);
    virtual SBW_Value *operator!=(SBW_Value *val);
    virtual SBW_Value *operator==(SBW_Value *val);
    virtual SBW_Value *operator&&(SBW_Value *val);
    virtual SBW_Value *operator||(SBW_Value *val);

    virtual SBW_Value *operator*(sbw_none);

    virtual SBW_Value *operator_abs(sbw_none);
    virtual SBW_Value *operator_convert(sbw_value_type dest_type);
};

#endif // __SEABOW_VALUE_NULL_HPP__