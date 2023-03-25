#include "compiler/interpreter.hpp"

void show_compound_infos(std::vector<SBW_Node*> nodes);

int main(int argc, char **argv)
{
#ifndef _WIN32
    std::setlocale(LC_ALL, "C.UTF-8");
#else
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    _setmode(_fileno(stdin), _O_U8TEXT);
#endif

    if (argc <= 1) 
    {
        SBW_Interpreter *interpreter = new SBW_Interpreter();
        interpreter->Perform();

        delete interpreter;
    }
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

    return 0;
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