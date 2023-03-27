#include "commands/options.hpp"

SBW_Options::SBW_Options(char **args, sbw_int size, sbw_int start)
{
    this->error_occured = false;
    this->optimisation = true;

    sbw_int i = start;
    while (i < size)
    {
        const char *arg = args[i];
        if (string_equals(arg, "-o"))
        {
            if (this->output.size() > 0)
            {
                this->error_occured = true;
                wprintf(L"\033[31m\nOptionError: You cannot define output path more than one time\033[0m\n");
                i++;
                continue;
            }

            i++;
            arg = (i >= size) ? "" : args[i];
            if (arg[0] == '\0' || arg[0] == '-')
            {
                this->error_occured = true;
                wprintf(L"\033[31m\nOptionError: You need to specify an output path after seabow's option '-o'\033[0m\n");
                continue;
            }

            this->output = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(arg);
        }
        else if (string_equals(arg, "-opt"))
            this->optimisation = false;
        else if (arg[0] != '-')
            this->inputs.push_back(std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(arg));
        else
            wprintf(L"\033[31m\nOptionError: Undefined seabow option '%s'\033[0m\n", arg); // Undefined option
        
        i++;
    }

    this->assign_default_values();
}

sbw_none SBW_Options::assign_default_values(sbw_none)
{
    if (this->output.size() == 0)
        this->output = L"out";
}