#ifndef __SEABOW_COMPILER_HPP__
#define __SEABOW_COMPILER_HPP__

#include "commands/interpreter.hpp"

enum SBW_ByteCode : sbw_ushort {
// Basic operators
    BC_PLUS = 0x0000, BC_UNARY_PLUS = 0x0001, BC_L_INC = 0x0002, BC_R_INC = 0x0003,
    BC_MINUS = 0x0004, BC_UNARY_MINUS = 0x0005, BC_L_DEC = 0x0006, BC_R_DEC = 0x0007,
    BC_TIMES = 0x0008, BC_POWER = 0x0009, BC_DIV = 0x000a, BC_MODULO = 0x000b,
    BC_XOR = 0x000c, BC_BITWISE_AND = 0x000d, BC_BITWISE_OR = 0x000e, BC_BITWISE_NOT = 0x000f,
    BC_L_SHIFT = 0x0010, BC_R_SHIFT = 0x0011, BC_LOGICAL_NOT = 0x0012, BC_NOT_EQUALS = 0x0013,
    BC_EQUALS_TO = 0x0014, BC_LESS = 0x0015, BC_LESS_EQ = 0x0016, BC_GREATER = 0x0017, BC_GREATER_EQ = 0x0018,
    BC_LOGICAL_AND = 0x0019, BC_LOGICAL_OR = 0x001a, BC_ADDRESS_OF = 0x001b, BC_GET = 0x001c,

// Assignment operators
    BC_EQUALS = 0x0040, BC_PLUS_EQ = 0x0041, BC_MINUS_EQ = 0x0042, BC_TIMES_EQ = 0x0043, BC_POWER_EQ = 0x0044,
    BC_DIV_EQ = 0x0045, BC_MODULO_EQ = 0x0046, BC_XOR_EQ = 0x0047, BC_BITWISE_AND_EQ = 0x0048,
    BC_BITWISE_OR_EQ = 0x0049, BC_L_SHIFT_EQ = 0x004a, BC_R_SHIFT_EQ = 0x004b,

// Seabow elements
    BC_LITTERAL = 0x0060, 
    BC_VAR_DECL = 0x0061, BC_VAR_DECL_GLOBAL = 0x0062, BC_VAR_DECL_CONST = 0x0063, BC_VAR_DECL_GLOBAL_CONST = 0x0064,
    BC_VAR_CALL = 0x0070,
    BC_FUNC_DECL = 0x0080, BC_FUNC_CALL = 0x008f,

// Control operators
    BC_BREAK = 0x0100, BC_CONTINUE = 0x0101, BC_RETURN = 0x0102
};

class SBW_Compiler
{
public:
    SBW_Compiler(SBW_Options *options);
    virtual ~SBW_Compiler();

    inline sbw_bool ErrorOccured(sbw_none) const { return this->error_occured; }

    sbw_none Perform(sbw_none);
private:
    sbw_string output;
    sbw_string input;

    sbw_bool error_occured;
    FILE *output_file;

    const wchar_t *read_file(sbw_none);
    sbw_bool create_output_file(sbw_none);

    sbw_bool CompileMainFunction(SBW_NodeFuncDecl *main_func);
    sbw_bool CompileFunctionDeclaration(SBW_Node *node);
};

#endif // __SEABOW_COMPILER_HPP__