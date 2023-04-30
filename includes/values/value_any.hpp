#ifndef __SEABOW_VALUE_ANY_HPP__
#define __SEABOW_VALUE_ANY_HPP__

#include "values/value_extern_function.hpp"

class SBW_ValueAny: public SBW_Value
{
public:
    SBW_ValueAny(SBW_Value *val);
    inline virtual ~SBW_ValueAny() { if (this->value) delete this->value; }

    inline sbw_value_type Type(sbw_none) const { return VT_ANY_; }

    inline SBW_Value *Get(sbw_none) const { return this->value; }
    SBW_Value *AutoConvert(sbw_value_type dest_type);
    inline sbw_bool IsNull(sbw_none) const { return this->value->IsNull(); }

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
    SBW_Value *operator[](SBW_Value *val);

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
    SBW_Value *operator||(SBW_Value *val);

    SBW_Value *operator*(sbw_none);

    SBW_Value *operator_abs(sbw_none);
    SBW_Value *operator_convert(sbw_value_type dest_type);
    SBW_Value *operator_size(sbw_none);
private:
    SBW_Value *value;
};

#endif // __SEABOW_VALUE_ANY_HPP__