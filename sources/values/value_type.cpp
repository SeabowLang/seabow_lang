#include "values/value_pointer.hpp"

SBW_ValueType::SBW_ValueType(sbw_value_type t)
{
    this->value = t;
    this->more = L"";
}

SBW_ValueType::SBW_ValueType(sbw_value_type t, sbw_string m)
{
    this->value = t;
    this->more = m;
}

sbw_string SBW_ValueType::ToString(sbw_none) const
{
    if (this->value != VT_XXXXX_) {
        sbw_string s = L"<" + GetStringType(this->value);
        if (this->more.size() > 0)
            s += L"'" + this->more + L"'";
        
        s += L">";
        return s;
    }
    else
        return L"null";
}