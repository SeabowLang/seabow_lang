#ifndef __SEABOW_VIRTUAL_MACHINE_HPP__
#define __SEABOW_VIRTUAL_MACHINE_HPP__

#include "commands/compiler.hpp"

extern std::vector<SBW_Variable*> gb_destroyables;
sbw_none garbage_collector(sbw_none);

class SBW_VirtualMachine
{
public:
    SBW_VirtualMachine(SBW_Options *options);
    virtual ~SBW_VirtualMachine();

    sbw_int Perform(sbw_none);
private:
    std::unordered_map<sbw_string, SBW_Variable*> global_scope;
};

#endif // __SEABOW_VIRTUAL_MACHINE_HPP__