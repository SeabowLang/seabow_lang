#ifndef __SEABOW_VALUE_STRING_HPP__
#define __SEABOW_VALUE_STRING_HPP__

#include "values/value_character.hpp"

class SBW_ValueString: public SBW_Value
{
public:
    SBW_ValueString();
    SBW_ValueString(sbw_string val);
    inline virtual ~SBW_ValueString() {}

    inline sbw_value_type Type(sbw_none) const { return VT_STRING_; }

    inline sbw_string Get(sbw_none) const { return this->value; }
    SBW_Value *AutoConvert(sbw_value_type dest_type);
    inline sbw_bool IsNull(sbw_none) const { return this->nl; }

    SBW_Value *operator+(SBW_Value *val);
    SBW_Value *operator+=(SBW_Value *val);

    SBW_Value *operator*(SBW_Value *val);
    SBW_Value *operator*=(SBW_Value *val);

    SBW_Value *operator^(SBW_Value *val);
    SBW_Value *operator^=(SBW_Value *val);
    SBW_Value *operator&(SBW_Value *val);
    SBW_Value *operator&=(SBW_Value *val);

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
private:
    sbw_string value;
    sbw_bool nl;
};

#endif // __SEABOW_VALUE_STRING_HPP__