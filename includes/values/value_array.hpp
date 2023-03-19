#ifndef __SEABOW_VALUE_ARRAY_HPP__
#define __SEABOW_VALUE_ARRAY_HPP__

#include "values/value_string.hpp"

class SBW_ValueArray: public SBW_Value
{
public:
    SBW_ValueArray();
    SBW_ValueArray(sbw_ulong size);
    virtual ~SBW_ValueArray();

    inline sbw_value_type Type(sbw_none) const { return VT_ARRAY_; }

    inline SBW_Value **Get(sbw_none) const { return this->value; }
    inline sbw_ulong Size(sbw_none) const { return this->size; }
    inline sbw_ulong FreeSpace(sbw_none) const { return this->free_space; }
    inline sbw_none SetFreeSpace(sbw_ulong ns) { this->free_space = ns; }
    inline sbw_bool IsNull(sbw_none) const { return !this->value; }

    SBW_Value *operator+(SBW_Value *val);
    SBW_Value *operator+=(SBW_Value *val);

    SBW_Value *operator-(SBW_Value *val);
    SBW_Value *operator-=(SBW_Value *val);
private:
    SBW_Value **value;
    sbw_ulong size;
    sbw_ulong free_space;
};

#endif // __SEABOW_VALUE_ARRAY_HPP__