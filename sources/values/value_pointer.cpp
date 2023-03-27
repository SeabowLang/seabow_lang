#include "values/value_any.hpp"

SBW_ValuePointer::SBW_ValuePointer(sbw_none *val, sbw_value_type ptr_type) 
{ 
    this->value = val;
    this->ptr_type = ptr_type;
}

SBW_ValuePointer::~SBW_ValuePointer()
{
    if (this->value)
    {
        if (this->ptr_type == VT_UNDEFINED_ && this->value)
            free(this->value);
    }
}

SBW_Value *SBW_ValuePointer::AutoConvert(sbw_value_type dest_type)
{
    if (this->ptr_type != VT_NULL_)
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean(this->value != (sbw_none*)0);
            case VT_POINTER_: return new SBW_ValuePointer(this->value, this->ptr_type);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValuePointer(this->value, this->ptr_type));
            default: return this->AutoConvertionError(dest_type);
        }
    }
    else
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean((sbw_bool*)0);
            case VT_POINTER_: return new SBW_ValuePointer((sbw_none*)0, VT_NULL_);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValuePointer((sbw_none*)0, VT_NULL_));
            default: return this->AutoConvertionError(dest_type);
        }        
    }
}

SBW_Value *SBW_ValuePointer::operator*(sbw_none) 
{ 
    return (this->ptr_type != VT_UNDEFINED_) ? (SBW_Value*)this->value : new SBW_Value(); 
}

SBW_Value *SBW_ValuePointer::operator_convert(sbw_value_type dest_type)
{
    if (this->ptr_type != VT_NULL_)
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean(this->value != (sbw_none*)0);
            case VT_STRING_: {
                std::wstringstream ss;
                ss << this->value;
                return new SBW_ValueString(ss.str());
            }
            case VT_TYPE_: return new SBW_ValueType(VT_POINTER_);
            case VT_POINTER_: return new SBW_ValuePointer(this->value, this->ptr_type);
        
            case VT_ANY_: return new SBW_ValueAny(new SBW_ValuePointer(this->value, this->ptr_type));
            default: return this->ConvertionError(dest_type);
        }
    }
    else
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean((sbw_bool*)0);
            case VT_STRING_: return new SBW_ValueString(L"null");
            case VT_TYPE_: return new SBW_ValueType(VT_POINTER_);
            case VT_POINTER_: return new SBW_ValuePointer((sbw_none*)0, VT_NULL_);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValuePointer((sbw_none*)0, VT_NULL_));
            default: return this->ConvertionError(dest_type);
        }
    }
}

SBW_Value *SBW_ValuePointer::operator_abs(sbw_none) { return new SBW_ValuePointer(this->value, this->ptr_type); }