#ifndef __SEABOW_VALUE_HPP__
#define __SEABOW_VALUE_HPP__

#include "lexer.hpp"

enum sbw_value_type: sbw_ubyte {
    VT_UNDEFINED_ = 0xff, VT_NULL_ = 0xfe, VT_ANY_ = 0xfd, VT_VOID_ = 0xfc, VT_XXXXX_ = 0xfb,

    VT_BYTE_ = 0x00, VT_UBYTE_ = 0x01, VT_SHORT_ = 0x02, VT_USHORT_ = 0x03, VT_INT_ = 0x04, VT_UINT_ = 0x05, VT_LONG_ = 0x06, VT_ULONG_ = 0x07,
    VT_FLOAT_ = 0x08, VT_DOUBLE_ = 0x09, VT_LDOUBLE_ = 0x0a,
    VT_BOOLEAN_ = 0x0e,

    VT_CHARACTER_ = 0x10, VT_STRING_ = 0x11,

    VT_ARRAY_ = 0x20, VT_LIST_ = 0x21, VT_DICT_ = 0x22,

    VT_TYPE_ = 0x28, VT_POINTER_ = 0x29,

    VT_ENUMERATION_ = 0x30, VT_STRUCTURE_ = 0x31, VT_CLASS_ = 0x32,

    VT_FUNCTION_ = 0x40,

    VT_ERROR_ = 0x50
};
const sbw_value_type GetKeywordType(sbw_string keyword);
const sbw_string GetStringType(sbw_value_type t);

inline const sbw_ldouble modulo(sbw_ldouble x, sbw_ldouble y) {
    sbw_ldouble result = x - (sbw_long)(x / y) * y;
    if (result < 0 && y > 0)
        result += y;
    else if (result > 0 && y < 0)
        result += y;
    
    return result;
}

inline const sbw_ldouble power(sbw_ldouble x, sbw_ldouble y) {
    return powl(x, y);
}

class SBW_Value
{
public:
    inline SBW_Value(sbw_none) {}
    inline virtual ~SBW_Value() {}

    inline virtual sbw_value_type Type(sbw_none) const { return VT_UNDEFINED_; }

    virtual SBW_Value *AutoConvert(sbw_value_type dest_type);
    inline virtual sbw_bool IsNull(sbw_none) const { return true; }

    virtual SBW_Value *operator+(sbw_none);
    virtual SBW_Value *operator+(SBW_Value *val);
    virtual SBW_Value *operator+=(SBW_Value *val);
    virtual SBW_Value *operator++(sbw_none);
    virtual SBW_Value *operator++(int);

    virtual SBW_Value *operator-(sbw_none);
    virtual SBW_Value *operator-(SBW_Value *val);
    virtual SBW_Value *operator-=(SBW_Value *val);
    virtual SBW_Value *operator--(sbw_none);
    virtual SBW_Value *operator--(int);

    virtual SBW_Value *operator*(SBW_Value *val);
    virtual SBW_Value *operator*=(SBW_Value *val);
    virtual SBW_Value *operator_power(SBW_Value *val);
    virtual SBW_Value *operator_power_eq(SBW_Value *val);

    virtual SBW_Value *operator/(SBW_Value *val);
    virtual SBW_Value *operator/=(SBW_Value *val);
    virtual SBW_Value *operator%(SBW_Value *val);
    virtual SBW_Value *operator%=(SBW_Value *val);

    virtual SBW_Value *operator^(SBW_Value *val);
    virtual SBW_Value *operator^=(SBW_Value *val);
    virtual SBW_Value *operator&(SBW_Value *val);
    virtual SBW_Value *operator&=(SBW_Value *val);
    virtual SBW_Value *operator|(SBW_Value *val);
    virtual SBW_Value *operator|=(SBW_Value *val);
    virtual SBW_Value *operator~(sbw_none);

    virtual SBW_Value *operator=(SBW_Value *val);
    virtual SBW_Value *operator[](SBW_Value *val);

    virtual SBW_Value *operator<<(SBW_Value *val);
    virtual SBW_Value *operator<<=(SBW_Value *val);
    virtual SBW_Value *operator>>(SBW_Value *val);
    virtual SBW_Value *operator>>=(SBW_Value *val);

    virtual SBW_Value *operator!(sbw_none);
    virtual SBW_Value *operator!=(SBW_Value *val);
    virtual SBW_Value *operator==(SBW_Value *val);
    virtual SBW_Value *operator<(SBW_Value *val);
    virtual SBW_Value *operator<=(SBW_Value *val);
    virtual SBW_Value *operator>(SBW_Value *val);
    virtual SBW_Value *operator>=(SBW_Value *val);
    virtual SBW_Value *operator&&(SBW_Value *val);
    virtual SBW_Value *operator||(SBW_Value *val);

    virtual SBW_Value *operator*(sbw_none);

    virtual SBW_Value *operator_abs(sbw_none);
    virtual SBW_Value *operator_convert(sbw_value_type dest_type);
    virtual SBW_Value *operator_size(sbw_none);
protected:
    SBW_Value *OpError(sbw_string op);
    SBW_Value *OpError(sbw_string op, sbw_value_type t);
    SBW_Value *OpWithNullError(sbw_string op);
    SBW_Value *ConvertionError(sbw_value_type t);
    SBW_Value *AutoConvertionError(sbw_value_type t);
    SBW_Value *ZeroError(sbw_none);
};

#endif // __SEABOW_VALUE_HPP__