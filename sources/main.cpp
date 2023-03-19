#include "compiler/interpreter.hpp"

void show_compound_infos(std::vector<SBW_Node*> nodes);

int main(int argc, char **argv)
{
#ifndef _WIN32
    setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "en_US.UTF-8");
#else
    _setmode(_fileno(stdin), _O_WTEXT);
#endif
    if (argc <= 1) 
    {
        SBW_Interpreter *interpreter = new SBW_Interpreter();
        interpreter->Perform();

        delete interpreter;
    }
    else
    {
        FILE *file = fopen64(argv[1], "r,ccs=UNICODE");
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

        std::wcout << code << L"\n";
        SBW_Parser *parser = new SBW_Parser(code);

        SBW_Node *nd = parser->Parse();
        delete parser;
        if (nd->Type() == NT_COMPOUND)
            show_compound_infos(((SBW_NodeCompound*)nd)->Statements());
        else
        {
            SBW_NodeBad *err = (SBW_NodeBad*)nd;
            std::wcout << L"NODE BAD => " << ((SBW_ValueString*)err->Err()->operator_convert(VT_STRING_))->Get() << L"\n";
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
            std::wcout << L"NODE BAD => " << ((SBW_ValueString*)err->Err()->operator_convert(VT_STRING_))->Get() << L"\n";
        }
        else {
            std::wcout << L"NODE{" << node->Type() << L"} (l: " << node->Line() << L", c: " << node->Column() << L")\n";
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