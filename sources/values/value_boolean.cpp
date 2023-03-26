#include "values/value_any.hpp"

SBW_ValueBoolean::SBW_ValueBoolean(sbw_bool val)
{
    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
    (*this->value) = val;
}

SBW_ValueBoolean::SBW_ValueBoolean(sbw_bool *val)
{
    if (val)
    {
        this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
        (*this->value) = *val;
    }
    else
        this->value = (sbw_bool*)0;
}

SBW_Value *SBW_ValueBoolean::AutoConvert(sbw_value_type dest_type)
{
    if (this->value)
    {
        switch (dest_type)
        {
            case VT_BYTE_: return new SBW_ValueByte(*this->value);
            case VT_UBYTE_: return new SBW_ValueUbyte(*this->value);
            case VT_SHORT_: return new SBW_ValueShort(*this->value);
            case VT_USHORT_: return new SBW_ValueUshort(*this->value);
            case VT_INT_: return new SBW_ValueInt(*this->value);
            case VT_UINT_: return new SBW_ValueUint(*this->value);
            case VT_LONG_: return new SBW_ValueLong(*this->value);
            case VT_ULONG_: return new SBW_ValueUlong(*this->value);
            case VT_FLOAT_: return new SBW_ValueFloat(*this->value);
            case VT_DOUBLE_: return new SBW_ValueDouble(*this->value);
            case VT_LDOUBLE_: return new SBW_ValueLdouble(*this->value);
            case VT_BOOLEAN_: return new SBW_ValueBoolean(*this->value);
            case VT_CHARACTER_: return new SBW_ValueCharacter(*this->value);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueBoolean(*this->value));
            default: return this->AutoConvertionError(dest_type);
        }
    }
    else
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

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueBoolean((sbw_bool*)0));
            default: return this->AutoConvertionError(dest_type);
        }
    }    
}

SBW_Value *SBW_ValueBoolean::operator+(sbw_none) { if (!this->value) return this->OpWithNullError(L"left +"); return new SBW_ValueByte(*this->value); }

SBW_Value *SBW_ValueBoolean::operator+(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueShort(v + ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueShort(v + ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueInt(v + ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueInt(v + ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueLong(v + ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueLong(v + ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueLong(v + ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueLong(v + ((SBW_ValueUlong*)val)->Get());
        case VT_FLOAT_: return new SBW_ValueLdouble(v + ((SBW_ValueFloat*)val)->Get());
        case VT_DOUBLE_: return new SBW_ValueLdouble(v + ((SBW_ValueDouble*)val)->Get());
        case VT_LDOUBLE_: return new SBW_ValueLdouble(v + ((SBW_ValueLdouble*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueShort(v + ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueLong(v + ((SBW_ValueCharacter*)val)->Get());
        case VT_ANY_: return *this + ((SBW_ValueAny*)val)->Get();

        default: return this->OpError(L"+", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator-(sbw_none) { if (!this->value) return this->OpWithNullError(L"left -"); return new SBW_ValueByte(-(*this->value)); }

SBW_Value *SBW_ValueBoolean::operator-(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueShort(v - ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueShort(v - ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueInt(v - ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueInt(v - ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueLong(v - ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueLong(v - ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueLong(v - ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueLong(v - ((SBW_ValueUlong*)val)->Get());
        case VT_FLOAT_: return new SBW_ValueLdouble(v - ((SBW_ValueFloat*)val)->Get());
        case VT_DOUBLE_: return new SBW_ValueLdouble(v - ((SBW_ValueDouble*)val)->Get());
        case VT_LDOUBLE_: return new SBW_ValueLdouble(v - ((SBW_ValueLdouble*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueShort(v - ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueLong(v - ((SBW_ValueCharacter*)val)->Get());
        case VT_ANY_: return *this - ((SBW_ValueAny*)val)->Get();

        default: return this->OpError(L"-", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator*(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueByte(v * ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueUbyte(v * ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueShort(v * ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueUshort(v * ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueInt(v * ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueUint(v * ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueLong(v * ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueUlong(v * ((SBW_ValueUlong*)val)->Get());
        case VT_FLOAT_: return new SBW_ValueFloat(v * ((SBW_ValueFloat*)val)->Get());
        case VT_DOUBLE_: return new SBW_ValueDouble(v * ((SBW_ValueDouble*)val)->Get());
        case VT_LDOUBLE_: return new SBW_ValueLdouble(v * ((SBW_ValueLdouble*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueBoolean(v * ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueCharacter(v * ((SBW_ValueCharacter*)val)->Get());
        case VT_ANY_: return *this * ((SBW_ValueAny*)val)->Get();
    
        default: return this->OpError(L"*", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator_power(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueByte(power(v, ((SBW_ValueByte*)val)->Get()));
        case VT_UBYTE_: return new SBW_ValueUbyte(power(v, ((SBW_ValueUbyte*)val)->Get()));
        case VT_SHORT_: return new SBW_ValueShort(power(v, ((SBW_ValueShort*)val)->Get()));
        case VT_USHORT_: return new SBW_ValueUshort(power(v, ((SBW_ValueUshort*)val)->Get()));
        case VT_INT_: return new SBW_ValueInt(power(v, ((SBW_ValueInt*)val)->Get()));
        case VT_UINT_: return new SBW_ValueUint(power(v, ((SBW_ValueUint*)val)->Get()));
        case VT_LONG_: return new SBW_ValueLong(power(v, ((SBW_ValueLong*)val)->Get()));
        case VT_ULONG_: return new SBW_ValueUlong(power(v, ((SBW_ValueUlong*)val)->Get()));
        case VT_FLOAT_: return new SBW_ValueFloat(power(v, ((SBW_ValueFloat*)val)->Get()));
        case VT_DOUBLE_: return new SBW_ValueDouble(power(v, ((SBW_ValueDouble*)val)->Get()));
        case VT_LDOUBLE_: return new SBW_ValueLdouble(power(v, ((SBW_ValueLdouble*)val)->Get()));
        case VT_BOOLEAN_: return new SBW_ValueBoolean(power(v, ((SBW_ValueBoolean*)val)->Get()));
        case VT_CHARACTER_: return new SBW_ValueCharacter(power(v, ((SBW_ValueCharacter*)val)->Get()));
        case VT_ANY_: return this->operator_power(((SBW_ValueAny*)val)->Get());

        default: return this->OpError(L"**", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator/(SBW_Value *val)
{
    sbw_ldouble v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: {
            sbw_ldouble d = ((SBW_ValueByte*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_UBYTE_: {
            sbw_ldouble d = ((SBW_ValueUbyte*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_SHORT_: {
            sbw_ldouble d = ((SBW_ValueShort*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_USHORT_: {
            sbw_ldouble d = ((SBW_ValueUshort*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_INT_: {
            sbw_ldouble d = ((SBW_ValueInt*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_UINT_: {
            sbw_ldouble d = ((SBW_ValueUint*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_LONG_: {
            sbw_ldouble d = ((SBW_ValueLong*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_ULONG_: {
            sbw_ldouble d = ((SBW_ValueUlong*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_FLOAT_: {
            sbw_ldouble d = ((SBW_ValueFloat*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_DOUBLE_: {
            sbw_ldouble d = ((SBW_ValueDouble*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_LDOUBLE_: {
            sbw_ldouble d = ((SBW_ValueLdouble*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_BOOLEAN_: {
            sbw_ldouble d = ((SBW_ValueBoolean*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }
        case VT_CHARACTER_: {
            sbw_ldouble d = ((SBW_ValueCharacter*)val)->Get();
            if (d == 0) return this->ZeroError();
            return new SBW_ValueLdouble(v / d);
        }

        case VT_ANY_: return *this / ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"/", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator%(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueByte(v % ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueShort(v % ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueShort(v % ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueInt(v % ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueInt(v % ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueLong(v % ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueLong(v % ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueLong(v % ((SBW_ValueUlong*)val)->Get());
        case VT_FLOAT_: return new SBW_ValueLdouble(modulo(v, ((SBW_ValueFloat*)val)->Get()));
        case VT_DOUBLE_: return new SBW_ValueLdouble(modulo(v, ((SBW_ValueDouble*)val)->Get()));
        case VT_LDOUBLE_: return new SBW_ValueLdouble(modulo(v, ((SBW_ValueLdouble*)val)->Get()));
        case VT_BOOLEAN_: return new SBW_ValueByte(v % ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueInt(v % ((SBW_ValueCharacter*)val)->Get());

        case VT_ANY_: return *this % ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"%", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator^(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueByte(v ^ ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueByte(v ^ ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueShort(v ^ ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueShort(v ^ ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueInt(v ^ ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueInt(v ^ ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueLong(v ^ ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueLong(v ^ ((SBW_ValueLong*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueByte(v ^ ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueLong(v ^ ((SBW_ValueCharacter*)val)->Get());

        case VT_ANY_: return *this ^ ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"^", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator&(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueByte(v & ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueByte(v & ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueShort(v & ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueShort(v & ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueInt(v & ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueInt(v & ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueLong(v & ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueLong(v & ((SBW_ValueLong*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueByte(v & ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueLong(v & ((SBW_ValueCharacter*)val)->Get());

        case VT_ANY_: return *this & ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"&", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator|(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueByte(v | ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueByte(v | ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueShort(v | ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueShort(v | ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueInt(v | ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueInt(v | ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueLong(v | ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueLong(v | ((SBW_ValueLong*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueByte(v | ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueLong(v | ((SBW_ValueCharacter*)val)->Get());

        case VT_ANY_: return *this | ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"|", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator~(sbw_none) { if (!this->value) return this->OpWithNullError(L"~"); return new SBW_ValueByte(~(*this->value)); }

SBW_Value *SBW_ValueBoolean::operator=(SBW_Value *val)
{
    switch (val->Type())
    {
        case VT_BYTE_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueByte*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_UBYTE_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueUbyte*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_SHORT_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueShort*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_USHORT_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueUshort*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_INT_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueInt*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_UINT_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueUint*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_LONG_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueLong*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_ULONG_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueUlong*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_FLOAT_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueFloat*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_DOUBLE_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueDouble*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_LDOUBLE_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueLdouble*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_BOOLEAN_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueBoolean*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }
        case VT_CHARACTER_: {
            if (!val->IsNull()) { 
                if (this->value) (*this->value) = ((SBW_ValueCharacter*)val)->Get() != 0;
                else {
                    this->value = (sbw_bool*)malloc(sizeof(sbw_bool));
                    (*this->value) = *value;
                }
            }
            else {
                if (this->value) free(this->value);
                this->value = (sbw_bool*)0;
            }
            return this;
        }

        case VT_ANY_: return *this = ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"=", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator<<(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueLong(v << ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueLong(v << ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueLong(v << ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueLong(v << ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueLong(v << ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueLong(v << ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueLong(v << ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueLong(v << ((SBW_ValueLong*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueLong(v << ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueLong(v << ((SBW_ValueCharacter*)val)->Get());

        case VT_ANY_: return *this << ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"<<", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator>>(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueLong(v >> ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueLong(v >> ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueLong(v >> ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueLong(v >> ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueLong(v >> ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueLong(v >> ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueLong(v >> ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueLong(v >> ((SBW_ValueLong*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueLong(v >> ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueLong(v >> ((SBW_ValueCharacter*)val)->Get());

        case VT_ANY_: return *this >> ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L">>", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator!(sbw_none) { if (this->value) return new SBW_ValueBoolean((*this->value) == false); return new SBW_ValueBoolean(true); }

SBW_Value *SBW_ValueBoolean::operator!=(SBW_Value *val)
{
    if (this->value)
    {
        switch (val->Type())
        {
            case VT_NULL_: return new SBW_ValueBoolean(true);
            case VT_BYTE_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueByte*)val)->Get());
            case VT_UBYTE_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueUbyte*)val)->Get());
            case VT_SHORT_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueShort*)val)->Get());
            case VT_USHORT_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueUshort*)val)->Get());
            case VT_INT_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueInt*)val)->Get());
            case VT_UINT_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueUint*)val)->Get());
            case VT_LONG_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueLong*)val)->Get());
            case VT_ULONG_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueUlong*)val)->Get());
            case VT_FLOAT_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueFloat*)val)->Get());
            case VT_DOUBLE_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueDouble*)val)->Get());
            case VT_LDOUBLE_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueLdouble*)val)->Get());
            case VT_BOOLEAN_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueBoolean*)val)->Get());
            case VT_CHARACTER_: return new SBW_ValueBoolean((*this->value) != ((SBW_ValueCharacter*)val)->Get());

            case VT_ANY_: return *this != ((SBW_ValueAny*)val)->Get();
            default: return new SBW_ValueBoolean(true);
        }
    }
    else
        return new SBW_ValueBoolean(!val->IsNull());
}

SBW_Value *SBW_ValueBoolean::operator==(SBW_Value *val)
{
    if (this->value)
    {
        switch (val->Type())
        {
            case VT_NULL_: return new SBW_ValueBoolean(false);
            case VT_BYTE_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueByte*)val)->Get());
            case VT_UBYTE_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueUbyte*)val)->Get());
            case VT_SHORT_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueShort*)val)->Get());
            case VT_USHORT_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueUshort*)val)->Get());
            case VT_INT_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueInt*)val)->Get());
            case VT_UINT_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueUint*)val)->Get());
            case VT_LONG_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueLong*)val)->Get());
            case VT_ULONG_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueUlong*)val)->Get());
            case VT_FLOAT_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueFloat*)val)->Get());
            case VT_DOUBLE_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueDouble*)val)->Get());
            case VT_LDOUBLE_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueLdouble*)val)->Get());
            case VT_BOOLEAN_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueBoolean*)val)->Get());
            case VT_CHARACTER_: return new SBW_ValueBoolean((*this->value) == ((SBW_ValueCharacter*)val)->Get());

            case VT_ANY_: return *this == ((SBW_ValueAny*)val)->Get();
            default: return this->OpError(L"==", val->Type());
        }
    }
    else
        return new SBW_ValueBoolean(val->IsNull());
}

SBW_Value *SBW_ValueBoolean::operator<(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueBoolean(v < ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueBoolean(v < ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueBoolean(v < ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueBoolean(v < ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueBoolean(v < ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueBoolean(v < ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueBoolean(v < ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueBoolean(v < ((SBW_ValueUlong*)val)->Get());
        case VT_FLOAT_: return new SBW_ValueBoolean(v < ((SBW_ValueFloat*)val)->Get());
        case VT_DOUBLE_: return new SBW_ValueBoolean(v < ((SBW_ValueDouble*)val)->Get());
        case VT_LDOUBLE_: return new SBW_ValueBoolean(v < ((SBW_ValueLdouble*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueBoolean(v < ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueBoolean(v < ((SBW_ValueCharacter*)val)->Get());

        case VT_ANY_: return *this < ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"<", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator<=(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueBoolean(v <= ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueBoolean(v <= ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueBoolean(v <= ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueBoolean(v <= ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueBoolean(v <= ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueBoolean(v <= ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueBoolean(v <= ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueBoolean(v <= ((SBW_ValueUlong*)val)->Get());
        case VT_FLOAT_: return new SBW_ValueBoolean(v <= ((SBW_ValueFloat*)val)->Get());
        case VT_DOUBLE_: return new SBW_ValueBoolean(v <= ((SBW_ValueDouble*)val)->Get());
        case VT_LDOUBLE_: return new SBW_ValueBoolean(v <= ((SBW_ValueLdouble*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueBoolean(v <= ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueBoolean(v <= ((SBW_ValueCharacter*)val)->Get());

        case VT_ANY_: return *this <= ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"<=", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator>(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueBoolean(v > ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueBoolean(v > ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueBoolean(v > ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueBoolean(v > ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueBoolean(v > ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueBoolean(v > ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueBoolean(v > ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueBoolean(v > ((SBW_ValueUlong*)val)->Get());
        case VT_FLOAT_: return new SBW_ValueBoolean(v > ((SBW_ValueFloat*)val)->Get());
        case VT_DOUBLE_: return new SBW_ValueBoolean(v > ((SBW_ValueDouble*)val)->Get());
        case VT_LDOUBLE_: return new SBW_ValueBoolean(v > ((SBW_ValueLdouble*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueBoolean(v > ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueBoolean(v > ((SBW_ValueCharacter*)val)->Get());

        case VT_ANY_: return *this > ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L">", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator>=(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;

    switch (val->Type())
    {
        case VT_BYTE_: return new SBW_ValueBoolean(v >= ((SBW_ValueByte*)val)->Get());
        case VT_UBYTE_: return new SBW_ValueBoolean(v >= ((SBW_ValueUbyte*)val)->Get());
        case VT_SHORT_: return new SBW_ValueBoolean(v >= ((SBW_ValueShort*)val)->Get());
        case VT_USHORT_: return new SBW_ValueBoolean(v >= ((SBW_ValueUshort*)val)->Get());
        case VT_INT_: return new SBW_ValueBoolean(v >= ((SBW_ValueInt*)val)->Get());
        case VT_UINT_: return new SBW_ValueBoolean(v >= ((SBW_ValueUint*)val)->Get());
        case VT_LONG_: return new SBW_ValueBoolean(v >= ((SBW_ValueLong*)val)->Get());
        case VT_ULONG_: return new SBW_ValueBoolean(v >= ((SBW_ValueUlong*)val)->Get());
        case VT_FLOAT_: return new SBW_ValueBoolean(v >= ((SBW_ValueFloat*)val)->Get());
        case VT_DOUBLE_: return new SBW_ValueBoolean(v >= ((SBW_ValueDouble*)val)->Get());
        case VT_LDOUBLE_: return new SBW_ValueBoolean(v >= ((SBW_ValueLdouble*)val)->Get());
        case VT_BOOLEAN_: return new SBW_ValueBoolean(v >= ((SBW_ValueBoolean*)val)->Get());
        case VT_CHARACTER_: return new SBW_ValueBoolean(v >= ((SBW_ValueCharacter*)val)->Get());

        case VT_ANY_: return *this >= ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L">=", val->Type());
    }
}

SBW_Value *SBW_ValueBoolean::operator&&(SBW_Value *val)
{
    if (!this->value)
        return new SBW_ValueBoolean(false);

    return new SBW_ValueBoolean(this->Get() && ((SBW_ValueBoolean*)val->AutoConvert(VT_BOOLEAN_))->Get());
}

SBW_Value *SBW_ValueBoolean::operator||(SBW_Value *val)
{
    sbw_bool v = this->value ? *this->value : false;
    if (v)
        return new SBW_ValueBoolean(true);
    else
        return val->AutoConvert(VT_BOOLEAN_);
}

SBW_Value *SBW_ValueBoolean::operator*(sbw_none) { return new SBW_ValuePointer(this, this->Type()); }

SBW_Value *SBW_ValueBoolean::operator_convert(sbw_value_type dest_type)
{
    if (this->value)
    {
        switch (dest_type)
        {
            case VT_BYTE_: return new SBW_ValueByte(*this->value);
            case VT_UBYTE_: return new SBW_ValueUbyte(*this->value);
            case VT_SHORT_: return new SBW_ValueShort(*this->value);
            case VT_USHORT_: return new SBW_ValueUshort(*this->value);
            case VT_INT_: return new SBW_ValueInt(*this->value);
            case VT_UINT_: return new SBW_ValueUint(*this->value);
            case VT_LONG_: return new SBW_ValueLong(*this->value);
            case VT_ULONG_: return new SBW_ValueUlong(*this->value);
            case VT_FLOAT_: return new SBW_ValueFloat(*this->value);
            case VT_DOUBLE_: return new SBW_ValueDouble(*this->value);
            case VT_LDOUBLE_: return new SBW_ValueLdouble(*this->value);
            case VT_BOOLEAN_: return new SBW_ValueBoolean(*this->value);
            case VT_CHARACTER_: return new SBW_ValueCharacter(*this->value);
            case VT_STRING_: return new SBW_ValueString(*this->value ? L"true" : L"false");
            case VT_TYPE_: return new SBW_ValueType(VT_BOOLEAN_);
            case VT_POINTER_: return new SBW_ValuePointer(this, this->Type());

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueBoolean(*this->value));
            default: return this->ConvertionError(dest_type);
        }
    }
    else
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
            case VT_STRING_: return new SBW_ValueString(L"null");
            case VT_TYPE_: return new SBW_ValueType(VT_BOOLEAN_);
            case VT_POINTER_: return new SBW_ValuePointer((sbw_none*)0, VT_NULL_);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueBoolean((sbw_bool*)0));
            default: return this->ConvertionError(dest_type);
        }
    }
}

SBW_Value *SBW_ValueBoolean::operator_abs(sbw_none) { return new SBW_ValueBoolean(true); }