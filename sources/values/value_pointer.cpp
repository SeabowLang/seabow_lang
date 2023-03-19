#include "values/value_pointer.hpp"

SBW_ValuePointer::SBW_ValuePointer(sbw_none *val, sbw_value_type ptr_type) 
{ 
    this->value = val;
    this->ptr_type = ptr_type;
}

SBW_ValuePointer::~SBW_ValuePointer()
{
    if (this->value)
    {
        if (this->ptr_type != VT_UNDEFINED_)
            delete ((SBW_Value*)this->value);
        else
            free(this->value);
    }
}

sbw_string SBW_ValuePointer::ToString(sbw_none) const
{
    if (this->ptr_type != VT_NULL_) {
        sbw_char out[19];
        swprintf(out, 19, L"%p", this->value);
        return out; 
    }
    else
        return L"null";
}