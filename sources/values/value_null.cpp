#include "values/value_any.hpp"


SBW_Value *SBW_ValueNull::AutoConvert(sbw_value_type dest_type) 
{
    SBW_Value *val = this->operator_convert(dest_type);
    if (val->Type() == VT_ERROR_)
        return this->AutoConvertionError(val->Type()); 
    return val;
}

SBW_Value *SBW_ValueNull::operator^(SBW_Value *val) { return val->AutoConvert(val->Type()); }
SBW_Value *SBW_ValueNull::operator&(SBW_Value *val) { return new SBW_ValueInt((sbw_int)0); }
SBW_Value *SBW_ValueNull::operator|(SBW_Value *val) { return val->AutoConvert(val->Type()); }

SBW_Value *SBW_ValueNull::operator!(sbw_none) { return new SBW_ValueBoolean(true); }
SBW_Value *SBW_ValueNull::operator!=(SBW_Value *val) { return new SBW_ValueBoolean(!val->IsNull()); }
SBW_Value *SBW_ValueNull::operator==(SBW_Value *val) { return new SBW_ValueBoolean(val->IsNull()); }
SBW_Value *SBW_ValueNull::operator&&(SBW_Value *val) { return new SBW_ValueBoolean(false); }
SBW_Value *SBW_ValueNull::operator||(SBW_Value *val) { return val->AutoConvert(VT_BOOLEAN_); }

SBW_Value *SBW_ValueNull::operator*(sbw_none) { return new SBW_ValuePointer(this, this->Type()); }

SBW_Value *SBW_ValueNull::operator_abs(sbw_none) { return new SBW_ValueNull(); }

SBW_Value *SBW_ValueNull::operator_convert(sbw_value_type dest_type) 
{
    switch (dest_type)
    {
        case VT_BYTE_: return new SBW_ValueByte((sbw_byte*)0);
        case VT_UBYTE_: return new SBW_ValueUbyte((sbw_ubyte*)0);
        case VT_SHORT_: return new SBW_ValueShort((sbw_short*)0);
        case VT_USHORT_: return new SBW_ValueUshort((sbw_ushort*)0);
        case VT_INT_: return new SBW_ValueInt((sbw_int*)0);
        case VT_UINT_: return new SBW_ValueUint((sbw_uint*)0);
        case VT_LONG_: return new SBW_ValueLong((sbw_long*)0);
        case VT_ULONG_: return new SBW_ValueUlong((sbw_ulong*)0);
        case VT_FLOAT_: return new SBW_ValueFloat((sbw_float*)0);
        case VT_DOUBLE_: return new SBW_ValueDouble((sbw_double*)0);
        case VT_LDOUBLE_: return new SBW_ValueLdouble((sbw_ldouble*)0);
        case VT_BOOLEAN_: return new SBW_ValueBoolean((sbw_bool*)0);
        case VT_CHARACTER_: return new SBW_ValueCharacter((sbw_char*)0);
        case VT_STRING_: return new SBW_ValueString();
        case VT_ERROR_: return new SBW_ValueError(L"", L"", 0, 0);
        case VT_POINTER_: return new SBW_ValuePointer((sbw_none*)0, VT_NULL_);

        case VT_ANY_: return new SBW_ValueAny(new SBW_ValueNull());
        default: return this->ConvertionError(dest_type);
    } 
}