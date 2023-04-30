#include "values/value_extern_function.hpp"

SBW_ValueExternFunc::SBW_ValueExternFunc(sbw_none)
{
    this->extern_func = nullptr;
}

SBW_ValueExternFunc::SBW_ValueExternFunc(SBW_Value *(*ext)(std::unordered_map<sbw_string, SBW_Value*>))
{
    this->extern_func = ext;
}