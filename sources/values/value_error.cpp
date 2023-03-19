#include "values/value_error.hpp"

SBW_ValueError::SBW_ValueError(sbw_string name, sbw_string dtls, sbw_ulong l, sbw_ulong c)
{
    this->name = name;
    this->details = dtls;
    this->line = l;
    this->column = c;
}

SBW_Value *SBW_ValueError::operator_convert(sbw_value_type dest_type)
{
    switch (dest_type)
    {
        case VT_STRING_: {
            if (this->name.size() > 0) {
                sbw_string s = this->name + L": " + this->details + L" (line: "; s += std::to_wstring(this->line) + L", column: " + std::to_wstring(this->column); s += L")";
                return new SBW_ValueString(s);
            } else return new SBW_ValueString(L"null");
        }

        default: return this->ConvertionError(dest_type);
    }
}

SBW_Value *SBW_ValueError::AutoConvert(sbw_value_type dest_type) { return this->AutoConvertionError(dest_type); }