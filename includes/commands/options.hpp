#ifndef __SEABOW_COMMAND_OPTIONS_HPP__
#define __SEABOW_COMMAND_OPTIONS_HPP__

#include "parser.hpp"

class SBW_Options
{
public:
    SBW_Options(char **args, sbw_int size, sbw_int start);
    inline virtual ~SBW_Options() {}

    inline sbw_bool ErrorOccured(sbw_none) const { return this->error_occured; }
    inline std::vector<sbw_string> Inputs(sbw_none) const { return this->inputs; }
    inline sbw_string Output(sbw_none) const { return this->output; }

    inline sbw_bool Optimisation(sbw_none) const { return this->optimisation; }
private:
    sbw_bool error_occured;
    sbw_string output;
    std::vector<sbw_string> inputs;

    sbw_bool optimisation;


    sbw_none assign_default_values(sbw_none);
};

#endif // __SEABOW_COMMAND_OPTIONS_HPP__