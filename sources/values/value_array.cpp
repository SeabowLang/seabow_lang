#include "values/value_any.hpp"

SBW_ValueArray::SBW_ValueArray() { this->value = nullptr; }

SBW_ValueArray::SBW_ValueArray(sbw_ulong size)
{
    this->value = (SBW_Value**)calloc(size, sizeof(SBW_Value*));
    this->free_space = this->size = size;
}

SBW_ValueArray::~SBW_ValueArray()
{
    if (this->value)
        free(this->value);
}

SBW_Value *SBW_ValueArray::AutoConvert(sbw_value_type dest_type)
{
    if (!this->IsNull())
    {
        switch (dest_type)
        {
            case VT_ANY_: {
                SBW_ValueArray *array = new SBW_ValueArray(this->size);
                for (sbw_ulong i=0; i<this->size; i++)
                    (*array) += this->Get()[i];
                return new SBW_ValueAny(array);
            }

            default: return this->AutoConvertionError(dest_type);
        }
    }
    else
    {
        switch (dest_type)
        {
            case VT_ANY_: {
                return new SBW_ValueAny(new SBW_ValueArray());
            }

            default: return this->AutoConvertionError(dest_type);
        }
    }
}

SBW_Value *SBW_ValueArray::operator+(SBW_Value *val)
{
    if (this->free_space > 0)
    {
        SBW_ValueArray *array = new SBW_ValueArray(this->size);
        sbw_bool check = false;
        for (sbw_ulong i=0; i<this->size; i++)
        {
            if (!check && !this->value[i])
            {
                check = true;
                array->Get()[i] = val;
                return this;
            }
            else
                array->Get()[i] = this->value[i];
        }
        array->SetFreeSpace(this->free_space - 1);
        return array;
    }

    return new SBW_ValueError(L"IndexError", L"Array cannot store more value", 0, 0);
}

SBW_Value *SBW_ValueArray::operator+=(SBW_Value *val)
{
    if (this->free_space > 0)
    {
        for (sbw_ulong i=0; i<this->size; i++)
        {
            if (!this->value[i])
            {
                this->free_space--;
                this->value[i] = val;
                return this;
            }
        }
    }

    return new SBW_ValueError(L"IndexError", L"Array cannot store more value", 0, 0);
}

SBW_Value *SBW_ValueArray::operator-(SBW_Value *val)
{
    SBW_ValueArray *array = new SBW_ValueArray(this->size);
    sbw_bool check = false;
    for (sbw_ulong i=0; i<this->size; i++)
    {
        if (!check && (*this->value[i]) == val) {
            array->Get()[i] = nullptr;
            check = true;
        }
        else
            array->Get()[i] = this->value[i];
    }

    return array;
}

SBW_Value *SBW_ValueArray::operator-=(SBW_Value *val)
{
    if (this->size == this->free_space)
        return this;
    
    for (sbw_ulong i=0; i<this->size; i++)
    {
        if ((*this->value[i]) == val)
        {
            this->value[i] = nullptr;
            return this;
        }
    }

    return this;
}

SBW_Value *SBW_ValueArray::operator_convert(sbw_value_type dest_type)
{
    if (!this->IsNull())
    {
        switch (dest_type)
        {
            case VT_STRING_: {
                sbw_string str = L"[";
                if (this->size != 0)
                {
                    for (sbw_ulong i=0; i<this->size-1; i++)
                    {
                        if (this->value[i])
                            str += ((SBW_ValueString*)this->value[i]->operator_convert(VT_STRING_))->Get();
                        else
                            str += L"null";
                        str += L", ";
                    }

                    str += ((SBW_ValueString*)this->value[this->size-1]->operator_convert(VT_STRING_))->Get();
                }                    
                    
                str += L"]";
                return new SBW_ValueString(str);
            }

            case VT_TYPE_: return new SBW_ValueType(VT_ARRAY_, std::to_wstring(this->size));   
            case VT_POINTER_: return new SBW_ValuePointer(this, this->Type());

            case VT_ANY_: {
                SBW_ValueArray *array = new SBW_ValueArray(this->size);
                for (sbw_ulong i=0; i<this->size; i++)
                    (*array) += this->value[i];
                
                return new SBW_ValueAny(array);
            }
            default: return this->ConvertionError(dest_type);
        }
    }
    else
    {
        switch (dest_type)
        {
            case VT_STRING_: return new SBW_ValueString(L"null");
            case VT_TYPE_: return new SBW_ValueType(VT_ARRAY_, sbw_string(L"null"));
            case VT_POINTER_: return new SBW_ValuePointer((sbw_none*)0, VT_NULL_);
        
            case VT_ANY_: return new SBW_ValueAny(new SBW_ValueArray());
            default: return this->ConvertionError(dest_type);
        }
    }
}