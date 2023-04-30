#include "commands/compiler.hpp"

SBW_Compiler::SBW_Compiler(SBW_Options *options)
{
    this->error_occured = false;

    if (options->Inputs().size() != 1)
    {
        wprintf(L"\033[31mYou need to specify a unique seabow main file (.sbw) to compile it\033[0m\n");
        this->error_occured = true;
    }

    this->output = options->Output();

    delete options;
}

SBW_Compiler::~SBW_Compiler()
{
    if (this->output_file)
        fclose(this->output_file);
}

sbw_none SBW_Compiler::Perform(sbw_none)
{
    const wchar_t *code = read_file();
    if (code == nullptr)
        return;

    if (!create_output_file())
        return;
    
    SBW_Parser *parser = new SBW_Parser(code);
    SBW_Node *root = parser->Parse();
    delete parser;

    if (root->Type() != NT_COMPOUND)
    {
        SBW_NodeBad *err = (SBW_NodeBad*)root;
        wprintf(L"\033[31m%ls\033[0m\n", ((SBW_ValueString*)err->Err()->operator_convert(VT_STRING_))->Get().c_str());
    }
    else
    {
        SBW_NodeFuncDecl *main_func = nullptr;
        SBW_NodeCompound *all = (SBW_NodeCompound*)root;
        for (sbw_ulong i=0; i<all->Statements().size(); i++)
        {
            SBW_Node *stat = all->Statements()[i];
            if (stat->Type() == NT_FUNCTION_DECLARATION)
            {
                SBW_NodeFuncDecl *maybe_main = (SBW_NodeFuncDecl*)stat;
                if (maybe_main->Name() == L"main")
                {
                    if (maybe_main->FuncType() != VT_INT_)
                    {
                        wprintf(L"\033[31mMain function have to return <int> value\n\033[0m");
                        delete root;
                        return;
                    }
                    else if (maybe_main->Params().size() != 1 || ((SBW_NodeParam*)maybe_main->Params()[0])->ParamType() != VT_ARRAY_)
                    {
                        wprintf(L"\033[31mMain function have to take a unique parameter of type <array>\n\033[0m");
                        delete root;
                        return;
                    }
                    else
                    {
                        main_func = maybe_main;
                        break;
                    }
                }
            }
        }

        if (main_func == nullptr)
        {
            wprintf(L"\033[31mYou need to specify a 'main' function in the seabow main file\n\033[0m");
            delete root;
            return;
        }

        if (this->CompileMainFunction(main_func))
        {
            // TODO
        }
    }

    delete root;
}

const wchar_t *SBW_Compiler::read_file(sbw_none)
{
    std::vector<char> buffer(this->input.size() + 1);
    std::wcstombs(buffer.data(), this->input.c_str(), buffer.size());
    const char *in_path = buffer.data();

    FILE *in_file = fopen64(in_path, "r,ccs=UTF-8");
    if (!in_file)
    {
        wprintf(L"\033[31mInput file '%ls' is incorrect or does not exist.\033[0m\n", this->input.c_str());
        return nullptr;
    }

    sbw_string code;
    sbw_char c = fgetwc(in_file);
    while (c != (sbw_char)(WEOF))
    {
        code += c;
        c = fgetwc(in_file);
    }

    fclose(in_file);
    return code.c_str();
}

sbw_bool SBW_Compiler::create_output_file(sbw_none)
{
    std::vector<char> buffer(this->output.size() + 1);
    std::wcstombs(buffer.data(), this->output.c_str(), buffer.size());
    const char *out_path = buffer.data();

    this->output_file = fopen64(out_path, "w");
    if (!this->output_file)
    {
        wprintf(L"\033[31mOutput path '%ls' is not correct.\033[0m\n", this->output.c_str());
        return false;
    }
    return true;
}

sbw_bool SBW_Compiler::CompileMainFunction(SBW_NodeFuncDecl *main_func)
{
    return false; // TODO
}

sbw_bool SBW_Compiler::CompileFunctionDeclaration(SBW_Node *node)
{
    return false; // TODO
}