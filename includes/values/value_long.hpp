#ifndef __SEABOW_VALUE_LONG_HPP__
#define __SEABOW_VALUE_LONG_HPP__

#include "values/value_uint.hpp"

class SBW_ValueLong: public SBW_Value
{
public:
    SBW_ValueLong(sbw_long val);
    SBW_ValueLong(sbw_long *val);
    inline virtual ~SBW_ValueLong() { if (this->value) free(this->value); }

    inline sbw_value_type Type(sbw_none) const { return VT_LONG_; }

    inline sbw_long Get(sbw_none) const { return *this->value; }
    SBW_Value *AutoConvert(sbw_value_type dest_type);
    inline sbw_bool IsNull(sbw_none) const { return !this->value; }

    SBW_Value *operator+(sbw_none);
    SBW_Value *operator+(SBW_Value *val);
    SBW_Value *operator+=(SBW_Value *val);
    SBW_Value *operator++(sbw_none);
    SBW_Value *operator++(int);

    SBW_Value *operator-(sbw_none);
    SBW_Value *operator-(SBW_Value *val);
    SBW_Value *operator-=(SBW_Value *val);
    SBW_Value *operator--(sbw_none);
    SBW_Value *operator--(int);

    SBW_Value *operator*(SBW_Value *val);
    SBW_Value *operator*=(SBW_Value *val);
    SBW_Value *operator_power(SBW_Value *val);
    SBW_Value *operator_power_eq(SBW_Value *val);

    SBW_Value *operator/(SBW_Value *val);
    SBW_Value *operator/=(SBW_Value *val);
    SBW_Value *operator%(SBW_Value *val);
    SBW_Value *operator%=(SBW_Value *val);

    SBW_Value *operator^(SBW_Value *val);
    SBW_Value *operator^=(SBW_Value *val);
    SBW_Value *operator&(SBW_Value *val);
    SBW_Value *operator&=(SBW_Value *val);
    SBW_Value *operator|(SBW_Value *val);
    SBW_Value *operator|=(SBW_Value *val);
    SBW_Value *operator~(sbw_none);

    SBW_Value *operator=(SBW_Value *val);

    SBW_Value *operator<<(SBW_Value *val);
    SBW_Value *operator<<=(SBW_Value *val);
    SBW_Value *operator>>(SBW_Value *val);
    SBW_Value *operator>>=(SBW_Value *val);

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
    sbw_long *value;
};

#endif // __SEABOW_VALUE_LONG_HPP__