#ifndef __SEABOW_VALUE_FUNCTION_HPP__
#define __SEABOW_VALUE_FUNCTION_HPP__

#include "values/value_pointer.hpp"

class SBW_ValueFunction: public SBW_Value
{
public:

    inline sbw_value_type Type(sbw_none) const { return VT_FUNCTION_; }
private:

};

#endif // __SEABOW_VALUE_FUNCTION_HPP__