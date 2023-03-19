#include "values/value_any.hpp"

SBW_ValueAny::SBW_ValueAny(SBW_Value *val)
{
    this->value = val;
}

SBW_Value *SBW_ValueAny::operator_convert(sbw_value_type dest_type) { return this->value->operator_convert(dest_type); }

SBW_Value *SBW_ValueAny::AutoConvert(sbw_value_type dest_type) { return this->value->AutoConvert(dest_type); }