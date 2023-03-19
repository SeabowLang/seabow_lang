#ifndef __SEABOW_VALUE_LIST_HPP__
#define __SEABOW_VALUE_LIST_HPP__

#include "values/value_array.hpp"

class SBW_ValueList: public SBW_Value
{
public:
    SBW_ValueList();
    virtual ~SBW_ValueList();

    inline sbw_value_type Type(sbw_none) const { return VT_LIST_; }

    inline std::list<SBW_Value*> Value(sbw_none) const { return this->value; }
private:
    std::list<SBW_Value*> value;
};

#endif // __SEABOW_VALUE_LIST_HPP__