#include "values/value_any.hpp"

const sbw_value_type GetKeywordType(sbw_string keyword)
{
    if (keyword == L"byte") return VT_BYTE_;
    if (keyword == L"ubyte") return VT_UBYTE_;
    if (keyword == L"short") return VT_SHORT_;
    if (keyword == L"ushort") return VT_USHORT_;
    if (keyword == L"int") return VT_INT_;
    if (keyword == L"uint") return VT_UINT_;
    if (keyword == L"long") return VT_LONG_;
    if (keyword == L"ulong") return VT_ULONG_;
    if (keyword == L"float") return VT_FLOAT_;
    if (keyword == L"double") return VT_DOUBLE_;
    if (keyword == L"ldouble") return VT_LDOUBLE_;
    if (keyword == L"bool") return VT_BOOLEAN_;

    if (keyword == L"char") return VT_CHARACTER_;
    if (keyword == L"string") return VT_STRING_;

    if (keyword == L"array") return VT_ARRAY_;
    if (keyword == L"list") return VT_LIST_;
    if (keyword == L"dict") return VT_DICT_;

    if (keyword == L"enum") return VT_ENUMERATION_;
    if (keyword == L"struct") return VT_STRUCTURE_;
    if (keyword == L"class") return VT_CLASS_;

    if (keyword == L"func") return VT_FUNCTION_;

    if (keyword == L"error") return VT_ERROR_;
    if (keyword == L"type") return VT_TYPE_;
    if (keyword == L"pointer") return VT_POINTER_;

    if (keyword == L"any") return VT_ANY_;
    if (keyword == L"null") return VT_NULL_; 
    if (keyword == L"void") return VT_VOID_;

    return VT_UNDEFINED_;
}

const sbw_string GetStringType(sbw_value_type t)
{
    switch (t)
    {
        case VT_BYTE_: return L"byte";
        case VT_UBYTE_: return L"ubyte";
        case VT_SHORT_: return L"short";
        case VT_USHORT_: return L"ushort";
        case VT_INT_: return L"int";
        case VT_UINT_: return L"uint";
        case VT_LONG_: return L"long";
        case VT_ULONG_: return L"ulong";
        case VT_FLOAT_: return L"float";
        case VT_DOUBLE_: return L"double";
        case VT_LDOUBLE_: return L"ldouble";
        case VT_BOOLEAN_: return L"bool";

        case VT_CHARACTER_: return L"char";
        case VT_STRING_: return L"string";

        case VT_ARRAY_: return L"array";
        case VT_LIST_: return L"list";
        case VT_DICT_: return L"dict";

        case VT_FUNCTION_: return L"func";

        case VT_TYPE_: return L"type";
        case VT_POINTER_: return L"pointer";

        case VT_ANY_: return L"any";
        case VT_NULL_: return L"null";
        case VT_VOID_: return L"void";

        default: return L"undefined";
    }
}

SBW_Value *SBW_Value::AutoConvert(sbw_value_type dest_type) { return this->AutoConvertionError(dest_type); }

SBW_Value *SBW_Value::OpError(sbw_string op)
{
    sbw_string details = L"Operator '"; details += op; details += L"' is not defined for type <"; details += GetStringType(this->Type());
    details += L">";
    return new SBW_ValueError(L"OperatorError", details, 0, 0);
}

SBW_Value *SBW_Value::OpError(sbw_string op, sbw_value_type t)
{
    sbw_string details = L"Operator '"; details += op; details += L"' is not defined for types <"; details += GetStringType(this->Type());
    details += L"> and <"; details += GetStringType(t); details += L">";
    return new SBW_ValueError(L"OperatorError", details, 0, 0);
}

SBW_Value *SBW_Value::OpWithNullError(sbw_string op)
{
    sbw_string details = L"Cannot use operator '"; details += op; details += L"' with null value";
    return new SBW_ValueError(L"OperatorError", details, 0, 0);
}

SBW_Value *SBW_Value::ConvertionError(sbw_value_type t)
{
    sbw_string details = L"Cannot convert from type <"; details += GetStringType(this->Type()); details += L"> to type <";
    details += GetStringType(t); details += L">";
    return new SBW_ValueError(L"ConvertionError", details, 0, 0);
}

SBW_Value *SBW_Value::AutoConvertionError(sbw_value_type t)
{
    sbw_string details = L"Cannot automatically convert from type <" + GetStringType(this->Type()) + L"> to type <" + GetStringType(t) + L">";
    return new SBW_ValueError(L"ConvertionError", details, 0, 0);
}

SBW_Value *SBW_Value::ZeroError(sbw_none)
{
    return new SBW_ValueError(L"ZeroDivisionError", L"Cannot divide by zero", 0, 0);
}


SBW_Value *SBW_Value::operator+(sbw_none) { return this->OpError(L"left +"); }
SBW_Value *SBW_Value::operator+(SBW_Value *val) { return this->OpError(L"+", val->Type()); }
SBW_Value *SBW_Value::operator+=(SBW_Value *val) { return this->OpError(L"+=", val->Type()); }
SBW_Value *SBW_Value::operator++(sbw_none) { return this->OpError(L"right ++"); }
SBW_Value *SBW_Value::operator++(int) { return this->OpError(L"left ++"); }

SBW_Value *SBW_Value::operator-(sbw_none) { return this->OpError(L"left -"); }
SBW_Value *SBW_Value::operator-(SBW_Value *val) { return this->OpError(L"-", val->Type()); }
SBW_Value *SBW_Value::operator-=(SBW_Value *val) { return this->OpError(L"-=", val->Type()); }
SBW_Value *SBW_Value::operator--(sbw_none) { return this->OpError(L"right --"); }
SBW_Value *SBW_Value::operator--(int) { return this->OpError(L"left --"); }

SBW_Value *SBW_Value::operator*(SBW_Value *val) { return this->OpError(L"*", val->Type()); }
SBW_Value *SBW_Value::operator*=(SBW_Value *val) { return this->OpError(L"*=", val->Type()); }
SBW_Value *SBW_Value::operator_power(SBW_Value *val) { return this->OpError(L"**", val->Type()); }
SBW_Value *SBW_Value::operator_power_eq(SBW_Value *val) { return this->OpError(L"**=", val->Type()); }

SBW_Value *SBW_Value::operator/(SBW_Value *val) { return this->OpError(L"/", val->Type()); }
SBW_Value *SBW_Value::operator/=(SBW_Value *val) { return this->OpError(L"/=", val->Type()); }
SBW_Value *SBW_Value::operator%(SBW_Value *val) { return this->OpError(L"%", val->Type()); }
SBW_Value *SBW_Value::operator%=(SBW_Value *val) { return this->OpError(L"%=", val->Type()); }

SBW_Value *SBW_Value::operator^(SBW_Value *val) { return this->OpError(L"^", val->Type()); }
SBW_Value *SBW_Value::operator^=(SBW_Value *val) { return this->OpError(L"^=", val->Type()); }
SBW_Value *SBW_Value::operator&(SBW_Value *val) { return this->OpError(L"&", val->Type()); }
SBW_Value *SBW_Value::operator&=(SBW_Value *val) { return this->OpError(L"&=", val->Type()); }
SBW_Value *SBW_Value::operator|(SBW_Value *val) { return this->OpError(L"|", val->Type()); }
SBW_Value *SBW_Value::operator|=(SBW_Value *val) { return this->OpError(L"|=", val->Type()); }
SBW_Value *SBW_Value::operator~(sbw_none) { return this->OpError(L"~"); }

SBW_Value *SBW_Value::operator=(SBW_Value *val) { return this->OpError(L"=", val->Type()); }
SBW_Value *SBW_Value::operator[](SBW_Value *val) { 
    sbw_string details = L"Type <" + GetStringType(this->Type()) + L"> is not subscriptable";
    return new SBW_ValueError(L"OperatorError", details, 0, 0);
}

SBW_Value *SBW_Value::operator<<(SBW_Value *val) { return this->OpError(L"<<", val->Type()); }
SBW_Value *SBW_Value::operator<<=(SBW_Value *val) { return this->OpError(L"<<=", val->Type()); }
SBW_Value *SBW_Value::operator>>(SBW_Value *val) { return this->OpError(L">>", val->Type()); }
SBW_Value *SBW_Value::operator>>=(SBW_Value *val) { return this->OpError(L">>=", val->Type()); }

SBW_Value *SBW_Value::operator!(sbw_none) { return this->OpError(L"!"); }
SBW_Value *SBW_Value::operator!=(SBW_Value *val) { return this->OpError(L"!=", val->Type()); }
SBW_Value *SBW_Value::operator==(SBW_Value *val) { return this->OpError(L"==", val->Type()); }
SBW_Value *SBW_Value::operator<(SBW_Value *val) { return this->OpError(L"<", val->Type()); }
SBW_Value *SBW_Value::operator<=(SBW_Value *val) { return this->OpError(L"<=", val->Type()); }
SBW_Value *SBW_Value::operator>(SBW_Value *val) { return this->OpError(L">", val->Type()); }
SBW_Value *SBW_Value::operator>=(SBW_Value *val) { return this->OpError(L">=", val->Type()); }
SBW_Value *SBW_Value::operator&&(SBW_Value *val) { return this->OpError(L"&&", val->Type()); }
SBW_Value *SBW_Value::operator||(SBW_Value *val) { return this->OpError(L"||", val->Type()); }

SBW_Value *SBW_Value::operator*(sbw_none) { return this->OpError(L"$"); }

SBW_Value *SBW_Value::operator_abs(sbw_none) { return this->OpError(L"abs"); }

SBW_Value *SBW_Value::operator_convert(sbw_value_type dest_type) { return this->ConvertionError(dest_type); }

SBW_Value *SBW_Value::operator_size(sbw_none) { return new SBW_ValueUlong(sizeof(*this)); }