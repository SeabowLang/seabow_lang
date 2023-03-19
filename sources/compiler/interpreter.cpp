#include "compiler/interpreter.hpp"

SBW_Interpreter::SBW_Interpreter()
{
    this->statement = false;
}

SBW_Interpreter::~SBW_Interpreter()
{

}

sbw_none SBW_Interpreter::Perform(sbw_none)
{
    std::wcout << L"Seabow " << SEABOW_MAJOR << L"." << SEABOW_MINOR << L"." << SEABOW_PATCH << L" (on " << SEABOW_OS << L")\nType '#h' for helps, '#q' to quit seabow interpreter, '#c' to clear the screen\n";

    while (true)
    {
        std::wcout << ((this->statement) ? L"... " : L">>> ");
        sbw_string code;
        std::wcin >> code;
        if (code[0] == L'\n')
            code.erase(0);

        if (code[0] == L'#') // Special commands
        {
            if (code == L"#q")
                return;
            else if (code == L"#h")
                std::wcout << L"Welcome to Seabow helps!\n";
            else if (code == L"#c")
                wprintf(L"\033[2J\033[H");
            else {
                wprintf(L"\033[31m");
                std::wcerr << L"InterpreterError: '" << code << L"' is not a special command.";
                wprintf(L"\033[0m\n");
            }
        }
        else // Code interpretation
            this->Interpret(code);
    }
}

sbw_none SBW_Interpreter::Interpret(sbw_string code)
{
    SBW_Parser *parser = new SBW_Parser(code);
    SBW_NodeCompound *root = (SBW_NodeCompound*)parser->Parse();
    delete parser;

    for (sbw_ulong i=0; i<root->Statements().size(); i++) {
        SBW_Node *st = root->Statements()[i];
        wprintf(L"NODE(t: %u, l: %lu, c: %lu)\n", st->Type(), st->Line(), st->Column());
    }

    delete root;
}