#ifndef __SEABOW_VALUE_BOOLEAN_HPP__
#define __SEABOW_VALUE_BOOLEAN_HPP__

#include "values/value_ldouble.hpp"

class SBW_ValueBoolean: public SBW_Value
{
public:
    SBW_ValueBoolean(sbw_bool val);
    SBW_ValueBoolean(sbw_bool *val);
    inline virtual ~SBW_ValueBoolean() { if (this->value) free(this->value); }

    inline sbw_value_type Type(sbw_none) const { return VT_BOOLEAN_; }

    inline sbw_bool Get(sbw_none) const { return this->value ? *this->value : false; }
    SBW_Value *AutoConvert(sbw_value_type dest_type);
    inline sbw_bool IsNull(sbw_none) const { return !this->value; }

    SBW_Value *operator+(sbw_none);
    SBW_Value *operator+(SBW_Value *val);

    SBW_Value *operator-(sbw_none);
    SBW_Value *operator-(SBW_Value *val);

    SBW_Value *operator*(SBW_Value *val);
    SBW_Value *operator_power(SBW_Value *val);

    SBW_Value *operator/(SBW_Value *val);
    SBW_Value *operator%(SBW_Value *val);

    SBW_Value *operator^(SBW_Value *val);
    SBW_Value *operator&(SBW_Value *val);
    SBW_Value *operator|(SBW_Value *val);
    SBW_Value *operator~(sbw_none);

    SBW_Value *operator=(SBW_Value *val);

    SBW_Value *operator<<(SBW_Value *val);
    SBW_Value *operator>>(SBW_Value *val);

    SBW_Value *operator!(sbw_none);
    SBW_Value *operator!=(SBW_Value *val);
    SBW_Value *operator==(SBW_Value *val);
    SBW_Value *operator<(SBW_Value *val);
    SBW_Value *operator<=(SBW_Value *val);
    SBW_Value *operator>(SBW_Value *val);
    SBW_Value *operator>=(SBW_Value *val);
    SBW_Value *operator&&(SBW_Value *val);
    SBW_Value *operator||(SBW_Value* val);

    SBW_Value *operator*(sbw_none);

    SBW_Value *operator_convert(sbw_value_type dest_type);
    SBW_Value *operator_abs(sbw_none);
private:
    sbw_bool *value;
};

#endif // __SEABOW_VALUE_BOOLEAN_HPP__