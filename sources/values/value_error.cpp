#include "values/value_any.hpp"

SBW_ValueError::SBW_ValueError(sbw_string name, sbw_string dtls, sbw_ulong l, sbw_ulong c)
{
    this->name = name;
    this->details = dtls;
    this->line = l;
    this->column = c;
}

SBW_Value *SBW_ValueError::operator_convert(sbw_value_type dest_type)
{
    if (!this->IsNull())
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean(true);
            case VT_STRING_: {
                if (this->name.size() > 0) {
                    sbw_string s = this->name + L": " + this->details;
                    if (this->line != 0) { s += L" (line: "; s += std::to_wstring(this->line) + L", column: " + std::to_wstring(this->column); s += L")"; }
                    return new SBW_ValueString(s);
                } else return new SBW_ValueString(L"null");
            }
            case VT_ERROR_: return new SBW_ValueError(this->name, this->details, this->line, this->column);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueError(this->name, this->details, this->line, this->column));
            default: return this->ConvertionError(dest_type);
        }
    }
    else
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean((sbw_bool*)0);
            case VT_STRING_: return new SBW_ValueString(L"null");
            case VT_ERROR_: return new SBW_ValueError(L"", L"", 0, 0);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueError(L"", L"", 0, 0));
            default: return this->ConvertionError(dest_type);
        }
    }
   
}

SBW_Value *SBW_ValueError::AutoConvert(sbw_value_type dest_type) 
{ 
    if (!this->IsNull())
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean(true);
            case VT_ERROR_: return new SBW_ValueError(this->name, this->details, this->line, this->column);
        
            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueError(this->name, this->details, this->line, this->column));
            default: return this->AutoConvertionError(dest_type);
        }
    }
    else
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean((sbw_bool*)0);
            case VT_ERROR_: return new SBW_ValueError(L"", L"", 0, 0);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueError(L"", L"", 0, 0));
            default: return this->AutoConvertionError(dest_type);
        }
    }
}