#ifndef __SEABOW_VALUE_BYTE_HPP__
#define __SEABOW_VALUE_BYTE_HPP__

#include "values/value_null.hpp"

class SBW_ValueByte: public SBW_Value
{
public:
    SBW_ValueByte(sbw_byte val);
    SBW_ValueByte(sbw_byte *val);
    inline virtual ~SBW_ValueByte() { if (this->value) free(this->value); }

    inline sbw_value_type Type(sbw_none) const { return VT_BYTE_; }

    inline sbw_byte Get(sbw_none) const { return this->value ? *this->value : 0; }
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
    sbw_byte *value;
};

#endif // __SEABOW_VALUE_BYTE_HPP__