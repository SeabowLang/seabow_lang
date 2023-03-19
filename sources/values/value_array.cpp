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
        if (!check && this->value[i] == val)
            check = true;
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
        if (this->value[i] == val)
        {
            this->value[i] = (SBW_Value*)0;
            return this;
        }
    }

    return this;
}