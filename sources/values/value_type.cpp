#include "values/value_any.hpp"

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

SBW_Value *SBW_ValueType::AutoConvert(sbw_value_type dest_type)
{
    if (!this->IsNull())
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean(this->value != VT_NULL_);
            case VT_TYPE_: return new SBW_ValueType(this->value, this->more);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueType(this->value));
            default: return this->AutoConvertionError(dest_type);
        }
    }
    else
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean((sbw_bool*)0);
            case VT_TYPE_: return new SBW_ValueType(VT_XXXXX_);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueType(VT_XXXXX_));
            default: return this->AutoConvertionError(dest_type);
        }
    }
}

SBW_Value *SBW_ValueType::operator_convert(sbw_value_type dest_type)
{
    if (!this->IsNull())
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean(this->value != VT_NULL_);
            case VT_STRING_: {
                sbw_string s = L"<"; s += GetStringType(this->value);
                if (this->more.size() > 0)
                    s += L"'" + this->more + L"'";
                s += L">";
                return new SBW_ValueString(s);
            }
            case VT_TYPE_: return new SBW_ValueType(VT_TYPE_);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueType(this->value, this->more));
            default: return this->ConvertionError(dest_type);
        }
    }
    else
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean((sbw_bool*)0);
            case VT_STRING_: return new SBW_ValueString(L"null");
            case VT_TYPE_: return new SBW_ValueType(VT_TYPE_);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueType(VT_XXXXX_));
            default: return this->ConvertionError(dest_type);
        }
    }
}