#include "values/value_any.hpp"

SBW_ValueAny::SBW_ValueAny(SBW_Value *val)
{
    this->value = val;
}

SBW_Value *SBW_ValueAny::AutoConvert(sbw_value_type dest_type) { return this->value->AutoConvert(dest_type); }

SBW_Value *SBW_ValueAny::operator+(sbw_none) { return +(*this->value); }
SBW_Value *SBW_ValueAny::operator+(SBW_Value *val) { return (*this->value) + val; }
SBW_Value *SBW_ValueAny::operator+=(SBW_Value *val) { return (*this->value) += val; }
SBW_Value *SBW_ValueAny::operator++(sbw_none) { return ++(*this->value); }
SBW_Value *SBW_ValueAny::operator++(int) { return (*this->value)++; }

SBW_Value *SBW_ValueAny::operator-(sbw_none) { return -(*this->value); }
SBW_Value *SBW_ValueAny::operator-(SBW_Value *val) { return (*this->value) - val; }
SBW_Value *SBW_ValueAny::operator-=(SBW_Value *val) { return (*this->value) -= val; }
SBW_Value *SBW_ValueAny::operator--(sbw_none) { return --(*this->value); }
SBW_Value *SBW_ValueAny::operator--(int) { return (*this->value)--; }

SBW_Value *SBW_ValueAny::operator*(SBW_Value *val) { return (*this->value) * val; }
SBW_Value *SBW_ValueAny::operator*=(SBW_Value *val) { return (*this->value) *= val; }
SBW_Value *SBW_ValueAny::operator_power(SBW_Value *val) { return this->value->operator_power(val); }
SBW_Value *SBW_ValueAny::operator_power_eq(SBW_Value *val) { return this->value->operator_power_eq(val); }

SBW_Value *SBW_ValueAny::operator/(SBW_Value *val) { return (*this->value) / val; }
SBW_Value *SBW_ValueAny::operator/=(SBW_Value *val) { return (*this->value) /= val; }
SBW_Value *SBW_ValueAny::operator%(SBW_Value *val) { return (*this->value) % val; }
SBW_Value *SBW_ValueAny::operator%=(SBW_Value *val) { return (*this->value) %= val; }

SBW_Value *SBW_ValueAny::operator^(SBW_Value *val) { return (*this->value) ^ val; }
SBW_Value *SBW_ValueAny::operator^=(SBW_Value *val) { return (*this->value) ^= val; }
SBW_Value *SBW_ValueAny::operator&(SBW_Value *val) { return (*this->value) & val; }
SBW_Value *SBW_ValueAny::operator&=(SBW_Value *val) { return (*this->value) &= val; }
SBW_Value *SBW_ValueAny::operator|(SBW_Value *val) { return (*this->value) | val; }
SBW_Value *SBW_ValueAny::operator|=(SBW_Value *val) { return (*this->value) |= val; }
SBW_Value *SBW_ValueAny::operator~(sbw_none) { return ~(*this->value); }

SBW_Value *SBW_ValueAny::operator=(SBW_Value *val) { return (*this->value) = val; }
SBW_Value *SBW_ValueAny::operator[](SBW_Value *val) { return (*this->value)[val]; }

SBW_Value *SBW_ValueAny::operator<<(SBW_Value *val) { return (*this->value) << val; }
SBW_Value *SBW_ValueAny::operator<<=(SBW_Value *val) { return (*this->value) <<= val; }
SBW_Value *SBW_ValueAny::operator>>(SBW_Value *val) { return (*this->value) >> val; }
SBW_Value *SBW_ValueAny::operator>>=(SBW_Value *val) { return (*this->value) >>= val; }

SBW_Value *SBW_ValueAny::operator!(sbw_none) { return !(*this->value); }
SBW_Value *SBW_ValueAny::operator!=(SBW_Value *val) { return (*this->value) != val; }
SBW_Value *SBW_ValueAny::operator==(SBW_Value *val) { return (*this->value) == val; }
SBW_Value *SBW_ValueAny::operator<(SBW_Value *val) { return (*this->value) < val; }
SBW_Value *SBW_ValueAny::operator<=(SBW_Value *val) { return (*this->value) <= val; }
SBW_Value *SBW_ValueAny::operator>(SBW_Value *val) { return (*this->value) > val; }
SBW_Value *SBW_ValueAny::operator>=(SBW_Value *val) { return (*this->value) >= val; }
SBW_Value *SBW_ValueAny::operator&&(SBW_Value *val) { return (*this->value) && val; }
SBW_Value *SBW_ValueAny::operator||(SBW_Value *val) { return (*this->value) || val; }

SBW_Value *SBW_ValueAny::operator*(sbw_none) { return *(*this->value); }

SBW_Value *SBW_ValueAny::operator_abs(sbw_none) { return this->value->operator_abs(); }
SBW_Value *SBW_ValueAny::operator_convert(sbw_value_type dest_type) { return this->value->operator_convert(dest_type); }
SBW_Value *SBW_ValueAny::operator_size(sbw_none) { return this->value->operator_size(); }