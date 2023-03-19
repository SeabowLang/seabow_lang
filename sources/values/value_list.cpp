#include "values/value_any.hpp"

SBW_ValueList::SBW_ValueList() {}

SBW_ValueList::~SBW_ValueList()
{
    while (!this->value.empty())
    {
        delete this->value.back();
        this->value.pop_back();
    }
}