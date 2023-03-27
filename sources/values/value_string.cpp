#include "values/value_any.hpp"

SBW_ValueString::SBW_ValueString()
{
    this->nl = true;
}

SBW_ValueString::SBW_ValueString(sbw_string val)
{
    this->value = val;
    this->nl = false;
}

SBW_Value *SBW_ValueString::AutoConvert(sbw_value_type dest_type)
{
    if (!this->nl)
    {
        switch (dest_type)
        {
            case VT_STRING_: return new SBW_ValueString(this->value);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueString(this->value));
            default: return this->AutoConvertionError(dest_type);
        }
    }
    else
    {
        switch (dest_type)
        {
            case VT_STRING_: return new SBW_ValueString();

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueString());
            default: return this->AutoConvertionError(dest_type);
        }
    }
}

SBW_Value *SBW_ValueString::operator+(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"+");
    
    if (val->Type() != VT_STRING_)
    {
        SBW_Value *v = val->operator_convert(VT_STRING_);
        if (v->Type() != VT_STRING_) return this->OpError(L"+", val->Type());
        return new SBW_ValueString(this->value + ((SBW_ValueString*)v)->Get());
    }
    
    return new SBW_ValueString(this->value + ((SBW_ValueString*)val)->Get());
}

SBW_Value *SBW_ValueString::operator+=(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"+=");

    if (val->Type() != VT_STRING_)
    {
        SBW_Value *v = val->operator_convert(VT_STRING_);
        if (v->Type() != VT_STRING_) return this->OpError(L"+=", val->Type());
        this->value += ((SBW_ValueString*)v)->Get();
    }
    else
        this->value += ((SBW_ValueString*)val)->Get();
    
    return this;
}

SBW_Value *SBW_ValueString::operator*(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"*");
    
    switch (val->Type())
    {
        case VT_BYTE_: {
            sbw_byte v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_byte i=1; i<=v; i++)
                s += this->value;
            return new SBW_ValueString(s);
        }
        case VT_UBYTE_: {
            sbw_ubyte v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_ubyte i=1; i<=v; i++)
                s += this->value;
            return new SBW_ValueString(s);
        }
        case VT_SHORT_: {
            sbw_short v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_short i=1; i<=v; i++)
                s += this->value;
            return new SBW_ValueString(s);
        }
        case VT_USHORT_: {
            sbw_ushort v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_ushort i=1; i<=v; i++)
                s += this->value;
            return new SBW_ValueString(s);
        }
        case VT_INT_: {
            sbw_int v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_int i=1; i<=v; i++)
                s += this->value;
            return new SBW_ValueString(s);
        }
        case VT_UINT_: {
            sbw_uint v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_uint i=1; i<=v; i++)
                s += this->value;
            return new SBW_ValueString(s);
        }
        case VT_LONG_: {
            sbw_long v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_long i=1; i<=v; i++)
                s += this->value;
            return new SBW_ValueString(s);
        }
        case VT_ULONG_: {
            sbw_ulong v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_ulong i=1; i<=v; i++)
                s += this->value;
            return new SBW_ValueString(s);
        }

        default: return this->OpError(L"*", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator*=(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"*=");
    
    switch (val->Type())
    {
        case VT_BYTE_: {
            sbw_byte v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_byte i=1; i<=v; i++)
                s += this->value;
            this->value = s;
        }
        case VT_UBYTE_: {
            sbw_ubyte v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_ubyte i=1; i<=v; i++)
                s += this->value;
            this->value = s;
        }
        case VT_SHORT_: {
            sbw_short v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_short i=1; i<=v; i++)
                s += this->value;
            this->value = s;
        }
        case VT_USHORT_: {
            sbw_ushort v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_ushort i=1; i<=v; i++)
                s += this->value;
            this->value = s;
        }
        case VT_INT_: {
            sbw_int v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_int i=1; i<=v; i++)
                s += this->value;
            this->value = s;
        }
        case VT_UINT_: {
            sbw_uint v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_uint i=1; i<=v; i++)
                s += this->value;
            this->value = s;
        }
        case VT_LONG_: {
            sbw_long v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_long i=1; i<=v; i++)
                s += this->value;
            this->value = s;
        }
        case VT_ULONG_: {
            sbw_ulong v = ((SBW_ValueByte*)val)->Get();
            sbw_string s;
            for (sbw_ulong i=1; i<=v; i++)
                s += this->value;
            this->value = s;
        }

        default: return this->OpError(L"*=", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator^(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"^");
    
    if (val->Type() == VT_STRING_)
    {
        sbw_string v = ((SBW_ValueString*)val)->Get();
        sbw_string s;
        sbw_ulong size = v.size() > this->value.size() ? this->value.size() : v.size();
        for (sbw_ulong i=0; i<size; i++)
        {
            if (v[i] != this->value[i])
                s += this->value[i];
        }
        if (size < this->value.size())
            s += this->value.substr(size);
        else if (size < v.size())
            s += v.substr(size);

        return new SBW_ValueString(s);
    }

    return this->OpError(L"^", val->Type());
}

SBW_Value *SBW_ValueString::operator^=(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"^=");
    
    if (val->Type() == VT_STRING_)
    {
        sbw_string v = ((SBW_ValueString*)val)->Get();
        sbw_string s;
        sbw_ulong size = v.size() > this->value.size() ? this->value.size() : v.size();
        for (sbw_ulong i=0; i<size; i++)
        {
            if (v[i] != this->value[i])
                s += this->value[i];
        }
        if (size < this->value.size())
            s += this->value.substr(size);
        else if (size < v.size())
            s += v.substr(size);

        this->value = s;
    }

    return this->OpError(L"^=", val->Type());
}

SBW_Value *SBW_ValueString::operator&(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"&");
    
    if (val->Type() == VT_STRING_)
    {
        sbw_string v = ((SBW_ValueString*)val)->Get();
        sbw_string s;
        sbw_ulong size = v.size() > this->value.size() ? this->value.size() : v.size();
        for (sbw_ulong i=0; i<size; i++)
        {
            if (v[i] == this->value[i])
                s += this->value[i];
        }
        return new SBW_ValueString(s);
    }

    return this->OpError(L"&", val->Type());
}

SBW_Value *SBW_ValueString::operator&=(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"&=");
    
    if (val->Type() == VT_STRING_)
    {
        sbw_string v = ((SBW_ValueString*)val)->Get();
        sbw_string s;
        sbw_ulong size = v.size() > this->value.size() ? this->value.size() : v.size();
        for (sbw_ulong i=0; i<size; i++)
        {
            if (v[i] == this->value[i])
                s += this->value[i];
        }
        this->value = s;
    }

    return this->OpError(L"&=", val->Type());
}

SBW_Value *SBW_ValueString::operator=(SBW_Value *val)
{   
    switch (val->Type())
    {
        case VT_CHARACTER_: {
            this->nl = false;
            this->value = ((SBW_ValueCharacter*)val)->Get();
            return this;
        }
        case VT_STRING_: {
            this->nl = false;
            this->value = ((SBW_ValueString*)val)->Get();
            return this;
        }

        case VT_ANY_: return *this = ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"=", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator[](SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"[]");
    
    switch (val->Type())
    {
        case VT_BYTE_: {
            sbw_byte v = ((SBW_ValueByte*)val)->Get();
            if (v >= 0 && v < this->value.size())
                return new SBW_ValueCharacter(this->value[v]);
            return new SBW_ValueNull();
        }
        case VT_UBYTE_: {
            sbw_ubyte v = ((SBW_ValueUbyte*)val)->Get();
            if (v < this->value.size())
                return new SBW_ValueCharacter(this->value[v]);
            return new SBW_ValueNull();
        }
        case VT_SHORT_: {
            sbw_short v = ((SBW_ValueShort*)val)->Get();
            if (v >= 0 && v < this->value.size())
                return new SBW_ValueCharacter(this->value[v]);
            return new SBW_ValueNull();
        }
        case VT_USHORT_: {
            sbw_ushort v = ((SBW_ValueUshort*)val)->Get();
            if (v < this->value.size())
                return new SBW_ValueCharacter(this->value[v]);
            return new SBW_ValueNull();
        }
        case VT_INT_: {
            sbw_int v = ((SBW_ValueInt*)val)->Get();
            if (v >= 0 && v < this->value.size())
                return new SBW_ValueCharacter(this->value[v]);
            return new SBW_ValueNull();
        }
        case VT_UINT_: {
            sbw_uint v = ((SBW_ValueUint*)val)->Get();
            if (v >= 0 && v < this->value.size())
                return new SBW_ValueCharacter(this->value[v]);
            return new SBW_ValueNull();
        }
        case VT_LONG_: {
            sbw_long v = ((SBW_ValueLong*)val)->Get();
            if (v >= 0 && v < this->value.size())
                return new SBW_ValueCharacter(this->value[v]);
            return new SBW_ValueNull();
        }
        case VT_ULONG_: {
            sbw_ulong v = ((SBW_ValueUlong*)val)->Get();
            if (v >= 0 && v < this->value.size())
                return new SBW_ValueCharacter(this->value[v]);
            return new SBW_ValueNull();
        }
        case VT_CHARACTER_: {
            sbw_char c = ((SBW_ValueCharacter*)val)->Get();
            for (sbw_ulong i=0; i<this->value.size(); i++)
            {
                if (this->value[i] == c)
                    return new SBW_ValueUlong(i);
            }
            return new SBW_ValueNull();
        }
        case VT_STRING_: {
            sbw_string s = ((SBW_ValueString*)val)->Get();
            if (s.size() > this->value.size())
                return new SBW_ValueNull();

            sbw_ulong i = 0;
            sbw_ulong pos = 0;
            while (i < this->value.size())
            {
                if (this->value[i] == s[pos])
                    pos++;
                else {
                    if (pos == s.size())
                        return new SBW_ValueUlong(i - pos);
                    pos = 0;
                    if (this->value[i] == s[pos])
                        pos++;
                }
                i++;
            }
            if (pos == s.size())
                return new SBW_ValueUlong(i - pos);

            return new SBW_ValueNull();
        }

        case VT_ANY_: return (*this)[((SBW_ValueAny*)val)->Get()];
        default: return this->OpError(L"[]", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator<<(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"<<");
    
    switch (val->Type())
    {
        case VT_BYTE_: {
            sbw_string s = this->value;
            sbw_byte v = ((SBW_ValueByte*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_byte i=0; i<v; i++)
                s.erase(0);
            return new SBW_ValueString(s);
        }
        case VT_UBYTE_: {
            sbw_string s = this->value;
            sbw_ubyte v = ((SBW_ValueUbyte*)val)->Get();
            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_ubyte i=0; i<v; i++)
                s.erase(0);
            return new SBW_ValueString(s);
        }
        case VT_SHORT_: {
            sbw_string s = this->value;
            sbw_short v = ((SBW_ValueShort*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_short i=0; i<v; i++)
                s.erase(0);
            return new SBW_ValueString(s);
        }
        case VT_USHORT_: {
            sbw_string s = this->value;
            sbw_ushort v = ((SBW_ValueUshort*)val)->Get();
            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_ushort i=0; i<v; i++)
                s.erase(0);
            return new SBW_ValueString(s);
        }
        case VT_INT_: {
            sbw_string s = this->value;
            sbw_int v = ((SBW_ValueInt*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_int i=0; i<v; i++)
                s.erase(0);
            return new SBW_ValueString(s);
        }
        case VT_UINT_: {
            sbw_string s = this->value;
            sbw_uint v = ((SBW_ValueUint*)val)->Get();
            if (v >= s.size())
                return new SBW_ValueString(L"");
            
            for (sbw_uint i=0; i<v; i++)
                s.erase(0);
            return new SBW_ValueString(s);
        }
        case VT_LONG_: {
            sbw_string s = this->value;
            sbw_long v = ((SBW_ValueLong*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_long i=0; i<v; i++)
                s.erase(0);
            return new SBW_ValueString(s);
        }
        case VT_ULONG_: {
            sbw_string s = this->value;
            sbw_ulong v = ((SBW_ValueUlong*)val)->Get();
            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_ulong i=0; i<v; i++)
                s.erase(0);
            return new SBW_ValueString(s);
        }

        case VT_ANY_: return *this << ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"<<", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator<<=(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"<<=");
    
    switch (val->Type())
    {
        case VT_BYTE_: {
            sbw_string s = this->value;
            sbw_byte v = ((SBW_ValueByte*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_byte i=0; i<v; i++)
                s.erase(0);
            this->value = s;
            return this;
        }
        case VT_UBYTE_: {
            sbw_string s = this->value;
            sbw_ubyte v = ((SBW_ValueUbyte*)val)->Get();
            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_ubyte i=0; i<v; i++)
                s.erase(0);
            this->value = s;
            return this;
        }
        case VT_SHORT_: {
            sbw_string s = this->value;
            sbw_short v = ((SBW_ValueShort*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_short i=0; i<v; i++)
                s.erase(0);
            this->value = s;
            return this;
        }
        case VT_USHORT_: {
            sbw_string s = this->value;
            sbw_ushort v = ((SBW_ValueUshort*)val)->Get();
            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_ushort i=0; i<v; i++)
                s.erase(0);
            this->value = s;
            return this;
        }
        case VT_INT_: {
            sbw_string s = this->value;
            sbw_int v = ((SBW_ValueInt*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_int i=0; i<v; i++)
                s.erase(0);
            this->value = s;
            return this;
        }
        case VT_UINT_: {
            sbw_string s = this->value;
            sbw_uint v = ((SBW_ValueUint*)val)->Get();
            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_uint i=0; i<v; i++)
                s.erase(0);
            this->value = s;
            return this;
        }
        case VT_LONG_: {
            sbw_string s = this->value;
            sbw_long v = ((SBW_ValueLong*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_long i=0; i<v; i++)
                s.erase(0);
            this->value = s;
            return this;
        }
        case VT_ULONG_: {
            sbw_string s = this->value;
            sbw_ulong v = ((SBW_ValueUlong*)val)->Get();
            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_ulong i=0; i<v; i++)
                s.erase(0);
            this->value = s;
            return this;
        }

        case VT_ANY_: return *this <<= ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"<<=", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator>>(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L">>");
    
    switch (val->Type())
    {
        case VT_BYTE_: {
            sbw_string s = this->value;
            sbw_byte v = ((SBW_ValueByte*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_byte i=0; i<v; i++)
                s.erase(s.size()-1);
            return new SBW_ValueString(s);
        }
        case VT_UBYTE_: {
            sbw_string s = this->value;
            sbw_ubyte v = ((SBW_ValueUbyte*)val)->Get();
            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_ubyte i=0; i<v; i++)
                s.erase(s.size()-1);
            return new SBW_ValueString(s);
        }
        case VT_SHORT_: {
            sbw_string s = this->value;
            sbw_short v = ((SBW_ValueShort*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_short i=0; i<v; i++)
                s.erase(s.size()-1);
            return new SBW_ValueString(s);
        }
        case VT_USHORT_: {
            sbw_string s = this->value;
            sbw_ushort v = ((SBW_ValueUshort*)val)->Get();
            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_ushort i=0; i<v; i++)
                s.erase(s.size()-1);
            return new SBW_ValueString(s);
        }
        case VT_INT_: {
            sbw_string s = this->value;
            sbw_int v = ((SBW_ValueInt*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_int i=0; i<v; i++)
                s.erase(s.size()-1);
            return new SBW_ValueString(s);
        }
        case VT_UINT_: {
            sbw_string s = this->value;
            sbw_uint v = ((SBW_ValueUint*)val)->Get();
            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_uint i=0; i<v; i++)
                s.erase(s.size()-1);
            return new SBW_ValueString(s);
        }
        case VT_LONG_: {
            sbw_string s = this->value;
            sbw_long v = ((SBW_ValueLong*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_long i=0; i<v; i++)
                s.erase(s.size()-1);
            return new SBW_ValueString(s);
        }
        case VT_ULONG_: {
            sbw_string s = this->value;
            sbw_ulong v = ((SBW_ValueUlong*)val)->Get();
            if (v >= s.size())
                return new SBW_ValueString(L"");

            for (sbw_ulong i=0; i<v; i++)
                s.erase(s.size()-1);
            return new SBW_ValueString(s);
        }

        case VT_ANY_: return *this >> ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L">>", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator>>=(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L">>=");
    
    switch (val->Type())
    {
        case VT_BYTE_: {
            sbw_string s = this->value;
            sbw_byte v = ((SBW_ValueByte*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_byte i=0; i<v; i++)
                s.erase(s.size()-1);
            this->value = s;
            return this;
        }
        case VT_UBYTE_: {
            sbw_string s = this->value;
            sbw_ubyte v = ((SBW_ValueUbyte*)val)->Get();
            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_ubyte i=0; i<v; i++)
                s.erase(s.size()-1);
            this->value = s;
            return this;
        }
        case VT_SHORT_: {
            sbw_string s = this->value;
            sbw_short v = ((SBW_ValueShort*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_short i=0; i<v; i++)
                s.erase(s.size()-1);
            this->value = s;
            return this;
        }
        case VT_USHORT_: {
            sbw_string s = this->value;
            sbw_ushort v = ((SBW_ValueUshort*)val)->Get();
            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_ushort i=0; i<v; i++)
                s.erase(s.size()-1);
            this->value = s;
            return this;
        }
        case VT_INT_: {
            sbw_string s = this->value;
            sbw_int v = ((SBW_ValueInt*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_int i=0; i<v; i++)
                s.erase(s.size()-1);
            this->value = s;
            return this;
        }
        case VT_UINT_: {
            sbw_string s = this->value;
            sbw_uint v = ((SBW_ValueUint*)val)->Get();
            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_uint i=0; i<v; i++)
                s.erase(s.size()-1);
            this->value = s;
            return this;
        }
        case VT_LONG_: {
            sbw_string s = this->value;
            sbw_long v = ((SBW_ValueLong*)val)->Get();
            if (v < 0)
                return new SBW_ValueError(L"OperatorError", L"Need positive number", 0, 0);

            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_long i=0; i<v; i++)
                s.erase(s.size()-1);
            this->value = s;
            return this;
        }
        case VT_ULONG_: {
            sbw_string s = this->value;
            sbw_ulong v = ((SBW_ValueUlong*)val)->Get();
            if (v > s.size())
            {
                this->value = L"";
                return this;
            }

            for (sbw_ulong i=0; i<v; i++)
                s.erase(s.size()-1);
            this->value = s;
            return this;
        }

        case VT_ANY_: return *this >>= ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L">>=", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator!(sbw_none) { if (!this->nl) return new SBW_ValueBoolean(this->value.size() <= 0); return new SBW_ValueBoolean(true); }

SBW_Value *SBW_ValueString::operator!=(SBW_Value *val)
{
    if (this->nl)
        return new SBW_ValueBoolean(!val->IsNull());
    
    switch (val->Type())
    {
        case VT_STRING_: return new SBW_ValueBoolean(this->value != ((SBW_ValueString*)val)->Get());

        case VT_ANY_: return *this != ((SBW_ValueAny*)val)->Get();
        default: return new SBW_ValueBoolean(true);
    }
}

SBW_Value *SBW_ValueString::operator==(SBW_Value *val)
{
    if (this->nl)
        return new SBW_ValueBoolean(val->IsNull());
    
    switch (val->Type())
    {
        case VT_STRING_: { 
            if (val->IsNull())
                return new SBW_ValueBoolean(false);

            return new SBW_ValueBoolean(this->value == ((SBW_ValueString*)val)->Get());
        }

        case VT_ANY_: return *this == ((SBW_ValueAny*)val)->Get();
        default: return new SBW_ValueBoolean(false);
    }
}

SBW_Value *SBW_ValueString::operator<(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"<");
    
    switch (val->Type())
    {
        case VT_STRING_: {
            sbw_string s = ((SBW_ValueString*)val)->Get();
            sbw_ulong sz = s.size() > this->value.size() ? this->value.size() : s.size();
            for (sbw_ulong i=0; i<sz; i++)
            {
                sbw_char c1 = this->value[i];
                sbw_char c2 = s[i];
                if (c1 < c2)
                    return new SBW_ValueBoolean(true);
                else if (c1 > c2)
                    return new SBW_ValueBoolean(false);
            }

            return new SBW_ValueBoolean(sz > s.size() ? false : true);
        }

        case VT_ANY_: return *this < ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"<", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator<=(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L"<=");
    
    switch (val->Type())
    {
        case VT_STRING_: {
            sbw_string s = ((SBW_ValueString*)val)->Get();
            sbw_ulong sz = s.size() > this->value.size() ? this->value.size() : s.size();
            for (sbw_ulong i=0; i<sz; i++)
            {
                sbw_char c1 = this->value[i];
                sbw_char c2 = s[i];
                if (c1 < c2)
                    return new SBW_ValueBoolean(true);
                else if (c1 > c2)
                    return new SBW_ValueBoolean(false);
            }

            if (s.size() == this->value.size())
                return new SBW_ValueBoolean(true);
            
            return new SBW_ValueBoolean(sz > s.size() ? false : true);
        }

        case VT_ANY_: return *this <= ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L"<=", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator>(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L">");
    
    switch (val->Type())
    {
        case VT_STRING_: {
            sbw_string s = ((SBW_ValueString*)val)->Get();
            sbw_ulong sz = s.size() > this->value.size() ? this->value.size() : s.size();
            for (sbw_ulong i=0; i<sz; i++)
            {
                sbw_char c1 = this->value[i];
                sbw_char c2 = s[i];
                if (c1 > c2)
                    return new SBW_ValueBoolean(true);
                else if (c1 < c2)
                    return new SBW_ValueBoolean(false);
            }

            return new SBW_ValueBoolean(sz > s.size() ? true : false);
        }

        case VT_ANY_: return *this > ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L">", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator>=(SBW_Value *val)
{
    if (this->nl)
        return this->OpWithNullError(L">=");
    
    switch (val->Type())
    {
        case VT_STRING_: {
            sbw_string s = ((SBW_ValueString*)val)->Get();
            sbw_ulong sz = s.size() > this->value.size() ? this->value.size() : s.size();
            for (sbw_ulong i=0; i<sz; i++)
            {
                sbw_char c1 = this->value[i];
                sbw_char c2 = s[i];
                if (c1 > c2)
                    return new SBW_ValueBoolean(true);
                else if (c1 < c2)
                    return new SBW_ValueBoolean(false);
            }

            if (s.size() == this->value.size())
                return new SBW_ValueBoolean(true);
            
            return new SBW_ValueBoolean(sz > s.size() ? true : false);
        }

        case VT_ANY_: return *this >= ((SBW_ValueAny*)val)->Get();
        default: return this->OpError(L">=", val->Type());
    }
}

SBW_Value *SBW_ValueString::operator&&(SBW_Value *val)
{
    if (this->nl)
        return new SBW_ValueBoolean(false);

    return new SBW_ValueBoolean(this->value.size() > 0 && ((SBW_ValueBoolean*)val->AutoConvert(VT_BOOLEAN_))->Get());
}

SBW_Value *SBW_ValueString::operator||(SBW_Value *val)
{
    if (!this->nl && this->value.size() > 0)
        return new SBW_ValueBoolean(true);
    else
        return val->AutoConvert(VT_BOOLEAN_);
}

SBW_Value *SBW_ValueString::operator*(sbw_none) { return new SBW_ValuePointer(this, this->Type()); }

SBW_Value *SBW_ValueString::operator_convert(sbw_value_type dest_type)
{
    if (!this->nl)
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean(this->value.size() > 0);
            case VT_STRING_: return new SBW_ValueString(this->value);
            case VT_TYPE_: return new SBW_ValueType(VT_STRING_);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueString(this->value));
            default: return this->ConvertionError(dest_type);
        }
    }
    else
    {
        switch (dest_type)
        {
            case VT_BOOLEAN_: return new SBW_ValueBoolean((sbw_bool*)0);
            case VT_STRING_: return new SBW_ValueString(L"null");
            case VT_TYPE_: return new SBW_ValueType(VT_STRING_);

            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueString());
            default: return this->ConvertionError(dest_type);
        }
    }
}

SBW_Value *SBW_ValueString::operator_abs(sbw_none) { return new SBW_ValueString(this->value); }