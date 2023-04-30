#include "commands/virtual_machine.hpp"

std::vector<SBW_Variable*> gb_destroyables;
sbw_none garbage_collector(sbw_none)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    while (!gb_destroyables.empty())
    {
        delete gb_destroyables.begin().base();
        gb_destroyables.erase(gb_destroyables.begin());
    }
}

SBW_VirtualMachine::SBW_VirtualMachine(SBW_Options *options)
{
    // TODO
    delete options;
}

SBW_VirtualMachine::~SBW_VirtualMachine()
{
    while (!this->global_scope.empty())
    {
        delete this->global_scope.begin()->second;
        this->global_scope.erase(this->global_scope.begin()->first);
    }

    while (!gb_destroyables.empty())
    {
        delete gb_destroyables.begin().base();
        gb_destroyables.erase(gb_destroyables.begin());
    }
}

sbw_int SBW_VirtualMachine::Perform(sbw_none)
{
    std::thread garb(garbage_collector);
    garb.detach();

    // TODO

    garb.join();
    return 0;
}