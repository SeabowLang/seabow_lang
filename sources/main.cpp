#include "commands/virtual_machine.hpp"

void show_compound_infos(std::vector<SBW_Node*> nodes);

int main(int argc, char **argv)
{
    sbw_int ret_val = 0;
    #ifndef _WIN32
        std::setlocale(LC_ALL, "C.UTF-8");
    #else
        _setmode(_fileno(stdout), _O_U16TEXT);
        _setmode(_fileno(stdin), _O_U16TEXT);
    #endif

    if (argc <= 1 || (argv[1][0] == '-' && argv[1][1] != '-')) 
    {
        SBW_Options *options = new SBW_Options(argv, argc, 1);
        if (options->ErrorOccured())
        {
            delete options;
            return -1;
        }

        SBW_Interpreter *interpreter = new SBW_Interpreter(options);
        interpreter->Perform();
        delete interpreter;
    }
    else
    {
        if (string_equals(argv[1], "cmp"))
        {
            SBW_Options *options = new SBW_Options(argv, argc, 2);
            if (options->ErrorOccured())
            {
                delete options;
                return -1;
            }

            SBW_Compiler *compiler = new SBW_Compiler(options);
            if (compiler->ErrorOccured())
            {
                delete compiler;
                return -1;
            }

            compiler->Perform();
            delete compiler;
        }
        else if (string_equals(argv[1], "run"))
        {
            SBW_Options *options = new SBW_Options(argv, argc, 2);
            if (options->ErrorOccured())
            {
                delete options;
                return -1;
            }

            SBW_VirtualMachine *vm = new SBW_VirtualMachine(options);
            ret_val = vm->Perform();
            delete vm;
        }
        else if (string_equals(argv[1], "pack"))
            wprintf(L"/!\\ Seabow's option 'pack' is not yet implemented.\n"); // TODO: Implement 'pack' option
        else if (string_equals(argv[1], "help") || string_equals(argv[1], "--help"))
            wprintf(SEABOW_HELPS);
        else if (string_equals(argv[1], "license") || string_equals(argv[1], "--l"))
            wprintf(L"GPL-3.0+\nAll releases and libraries of seabow are open source. You can find it at https://github.com/orgs/SeabowLang/repositories.\n");
        else
        {
            FILE *file = fopen64(argv[1], "r,ccs=UTF-8");
            sbw_string code;
            if (file != nullptr)
            {
                sbw_char c = fgetwc(file);
                while (c != (sbw_char)(WEOF))
                {
                    code += c;
                    c = fgetwc(file);
                }

                fclose(file);
            }
            else
            {
                std::wcerr << L"No file !!!\n";
                return -1;
            }

            SBW_Parser *parser = new SBW_Parser(code);

            SBW_Node *nd = parser->Parse();
            delete parser;
            if (nd->Type() == NT_COMPOUND)
                show_compound_infos(((SBW_NodeCompound*)nd)->Statements());
            else
            {
                SBW_NodeBad *err = (SBW_NodeBad*)nd;
                wprintf(L"NODE BAD => %ls\n", ((SBW_ValueString*)err->Err()->operator_convert(VT_STRING_))->Get().c_str());
            }

            delete nd;
        }
    }

    return ret_val;
}

void show_compound_infos(std::vector<SBW_Node*> nodes)
{
    while (!nodes.empty())
    {
        SBW_Node *node = *nodes.begin().base();
        if (node->Type() == NT_BAD) {
            SBW_NodeBad *err = (SBW_NodeBad*)node;
            wprintf(L"NODE BAD => %ls\n", ((SBW_ValueString*)err->Err()->operator_convert(VT_STRING_))->Get().c_str());
        }
        else {
            wprintf(L"NODE{%u} (l: %lu, c: %lu)\n", node->Type(), node->Line(), node->Column());
            if (node->Type() == NT_COMPOUND)
                show_compound_infos(((SBW_NodeCompound*)node)->Statements());
            else if (node->Type() == NT_FUNCTION_DECLARATION) {
                show_compound_infos(((SBW_NodeFuncDecl*)node)->Params());
                show_compound_infos(((SBW_NodeCompound*)((SBW_NodeFuncDecl*)node)->Body())->Statements());
            }
        }
    
        nodes.erase(nodes.begin());
    }
}