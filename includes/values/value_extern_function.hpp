#ifndef __SEABOW_EXTERN_FUNCTION_HPP__
#define __SEABOW_EXTERN_FUNCTION_HPP__

#include "values/value_function.hpp"

class SBW_ValueExternFunc: public SBW_Value
{
public:
    SBW_ValueExternFunc(sbw_none);
    SBW_ValueExternFunc(SBW_Value *(*ext)(std::unordered_map<sbw_string, SBW_Value*>));
    inline virtual ~SBW_ValueExternFunc() {}

    inline sbw_value_type Type(sbw_none) const { return VT_EXTERN_FUNCTION_; }

    inline auto Get(sbw_none) const { return this->extern_func; }
    inline sbw_bool IsNull(sbw_none) const { return !this->extern_func; }
private:
    SBW_Value *(*extern_func)(std::unordered_map<sbw_string, SBW_Value*>);
};

#endif // __SEABOW_EXTERN_FUNCTION_HPP__