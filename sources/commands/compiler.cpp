#include "commands/compiler.hpp"

SBW_Compiler::SBW_Compiler(SBW_Options *options)
{
    this->error_occured = false;

    if (options->Inputs().size() != 1)
    {
        wprintf(L"\033[31mYou need to specify a unique seabow main file (.sbw) to compile it\033[0m\n");
        this->error_occured = true;
    }

    delete options;
}