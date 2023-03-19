#include "compiler/interpreter.hpp"

SBW_Variable::SBW_Variable()
{
    this->value = new SBW_Value();
    this->modifier = 0;
}

SBW_Variable::SBW_Variable(SBW_Value *value, sbw_ubyte mod)
{
    this->value = value;
    this->modifier = mod;
}

SBW_Variable::~SBW_Variable()
{
    if (this->value)
        delete this->value;
}

SBW_Interpreter::SBW_Interpreter()
{
    this->statement = false;
}

SBW_Interpreter::~SBW_Interpreter()
{
    while (!this->data.empty())
    {
        SBW_Variable *var = this->data.begin()->second;
        if (var) delete var;
        this->data.erase(this->data.begin());
    }
}

sbw_none SBW_Interpreter::Perform(sbw_none)
{
    wprintf(L"Seabow %u.%u.%u (on %s)\nType '#h' for helps, '#q' to quit seabow interpreter, '#l' to list all seabow elements, '#c' to clear the screen\n", SEABOW_MAJOR, SEABOW_MINOR, SEABOW_PATCH, SEABOW_OS);

    while (true)
    {
        wprintf((this->statement) ? L"... " : L">>> ");
        sbw_string code;
        std::getline(std::wcin, code);
        if (code[0] == L'\n')
            code.erase(0);

        if (code[0] == L'#') // Special commands
        {
            if (code == L"#q")
                return;
            else if (code == L"#h")
                wprintf(L"Welcome to Seabow helps!\n");
            else if (code == L"#c")
                wprintf(L"\033[2J\033[H");
            else if (code == L"#l")
                {}
            else
                wprintf(L"\033[31mInterpreterError: '%ls' is not a special command.\033[0m\n", code.c_str());
        }
        else // Code interpretation
            this->StartInterpreter(code);
    }
}

sbw_none SBW_Interpreter::StartInterpreter(sbw_string code)
{
    SBW_Parser *parser = new SBW_Parser(code);
    SBW_NodeCompound *root = (SBW_NodeCompound*)parser->Parse();
    delete parser;

    if (root->Statements().size() != 0)
    {
        SBW_Value *ret = (root->Statements().size() > 1) ? this->InterpretNode(root)->Value() : this->InterpretNode(root->Statements()[0])->Value();

        if (ret->Type() == VT_ERROR_)
            wprintf(L"\033[31m%ls\033[0m\n", ((SBW_ValueString*)ret->operator_convert(VT_STRING_))->Get().c_str());
        else if (ret->Type() != VT_UNDEFINED_)
            wprintf(L"%ls\n", ((SBW_ValueString*)ret->operator_convert(VT_STRING_))->Get().c_str());
    }

    delete root;
}

SBW_Variable *SBW_Interpreter::InterpretNode(SBW_Node *node)
{
    switch (node->Type())
    {
        case NT_BAD: return this->InterpretNodeBad(node);
        case NT_COMPOUND: return this->InterpretCompound(node);

        case NT_VARIABLE_DECLARATION: return this->InterpretVarDecl(node);
        case NT_VARIABLE_CALL: return this->InterpretVarCall(node);

        case NT_LITERAL: return this->InterpretLiteral(node);
        case NT_PARENTHESIZED: return this->InterpretParenthesized(node);

        case NT_BINARY_EXPR: return this->InterpretBinaryExpression(node);
        case NT_UNARY_EXPR: return this->InterpretUnaryExpression(node);

        default: return new SBW_Variable(new SBW_ValueError(L"RuntimeError", L"Incorrect statement found", node->Line(), node->Column()), UNASSIGNABLE_ERROR);
    }
}

SBW_Variable *SBW_Interpreter::InterpretNodeBad(SBW_Node *node) { return new SBW_Variable(((SBW_NodeBad*)node)->Err(), UNASSIGNABLE_ERROR); }

SBW_Variable *SBW_Interpreter::InterpretCompound(SBW_Node *node)
{
    SBW_NodeCompound *cmp = (SBW_NodeCompound*)node;
    for (sbw_ulong i=0; i<cmp->Statements().size(); i++)
    {
        SBW_Node *nd = cmp->Statements()[i];
        this->InterpretNode(nd);
    }

    return new SBW_Variable();
}

SBW_Variable *SBW_Interpreter::InterpretVarDecl(SBW_Node *node)
{
    SBW_NodeVarDecl *vd = (SBW_NodeVarDecl*)node;
    if (this->data.count(vd->Name()) != 0) {
        sbw_string dtls = L"A variable named '"; dtls += vd->Name(); dtls += L"' already exists";
        return new SBW_Variable(new SBW_ValueError(L"NameError", dtls, vd->Line(), vd->Column()), UNASSIGNABLE_ERROR);
    }

    if (vd->Value())
    {
        SBW_Variable *conv = this->InterpretNode(vd->Value());
        if (conv->Value()->Type() == VT_UNDEFINED_)
        {
            delete conv;
            SBW_Value *null_value = new SBW_ValueNull();
            this->data[vd->Name()] = new SBW_Variable(null_value->AutoConvert(vd->VType()), 0);
            delete null_value;
        }
        else if (conv->Value()->Type() == VT_ERROR_ && conv->Modifier() == UNASSIGNABLE_ERROR)
            return conv;
        else
            this->data[vd->Name()] = new SBW_Variable(conv->Value()->AutoConvert(vd->VType()), 0);
    }
    else
    {
        SBW_Value *null_value = new SBW_ValueNull();
        this->data[vd->Name()] = new SBW_Variable(null_value->AutoConvert(vd->VType()), 0);
        delete null_value;
    }

    return new SBW_Variable();
}

SBW_Variable *SBW_Interpreter::InterpretVarCall(SBW_Node *node)
{
    SBW_NodeVarCall *vc = (SBW_NodeVarCall*)node;
    if (this->data.count(vc->Name()) == 0) {
        sbw_string dtls = L"Unknown variable '"; dtls += vc->Name(); dtls += L"'";
        return new SBW_Variable(new SBW_ValueError(L"NameError", dtls, vc->Line(), vc->Column()), UNASSIGNABLE_ERROR);
    }

    return this->data[vc->Name()];
}

SBW_Variable *SBW_Interpreter::InterpretLiteral(SBW_Node *node) { return new SBW_Variable(((SBW_NodeLiteral*)node)->Value(), 0); }

SBW_Variable *SBW_Interpreter::InterpretParenthesized(SBW_Node *node) { return this->InterpretNode(((SBW_NodeParenthesized*)node)->Expression()); }

SBW_Variable *SBW_Interpreter::InterpretBinaryExpression(SBW_Node *node)
{
    SBW_NodeBinary *bn = (SBW_NodeBinary*)node;
    SBW_Variable *left = this->InterpretNode(bn->Left());
    if (left->Value()->Type() == VT_ERROR_ && left->Modifier() == UNASSIGNABLE_ERROR)
        return left;

    SBW_Variable *right = bn->Right() ? this->InterpretNode(bn->Right()) : new SBW_Variable(new SBW_Value(), 0);
    if (right->Value()->Type() == VT_ERROR_ && right->Modifier() == UNASSIGNABLE_ERROR)
        return right;

    switch (bn->OpType())
    {
        case TT_PLUS: {
            SBW_Value *v = ((*left->Value()) + right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_PLUSEQ: {
            SBW_Value *v = ((*left->Value()) += right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_PLUSPLUS: {
            SBW_Value *v = (*left->Value())++;
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_MINUS: {
            SBW_Value *v = ((*left->Value()) - right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_MINUSEQ: {
            SBW_Value *v = ((*left->Value()) -= right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_MINUSMINUS: {
            SBW_Value *v = (*left->Value())--;
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_STAR: {
            SBW_Value *v = ((*left->Value()) * right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_STAREQ: {
            SBW_Value *v = ((*left->Value()) *= right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_POWER: {
            SBW_Value *v = left->Value()->operator_power(right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_POWEREQ: {
            SBW_Value *v = left->Value()->operator_power_eq(right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_SLASH: {
            SBW_Value *v = ((*left->Value()) / right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_SLASHEQ: {
            SBW_Value *v = ((*left->Value()) /= right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_PERCENT: {
            SBW_Value *v = (*left->Value()) % right->Value();
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_PERCENTEQ: {
            SBW_Value *v = (*left->Value()) %= right->Value();
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_HAT: {
            SBW_Value *v = ((*left->Value()) ^ right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_HATEQ: {
            SBW_Value *v = ((*left->Value()) ^= right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_AMP: {
            SBW_Value *v = ((*left->Value()) & right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_AMPEQ: {
            SBW_Value *v = ((*left->Value()) &= right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_PIPE: {
            SBW_Value *v = ((*left->Value()) | right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_PIPEEQ: {
            SBW_Value *v = ((*left->Value()) |= right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_LSHIFT: {
            SBW_Value *v = ((*left->Value()) << right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_LSHIFTEQ: {
            SBW_Value *v = ((*left->Value()) <<= right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_RSHIFT: {
            SBW_Value *v = ((*left->Value()) >> right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_RSHIFTEQ: {
            SBW_Value *v = ((*left->Value()) >>= right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_NE: {
            SBW_Value *v = ((*left->Value()) != right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_EE: {
            SBW_Value *v = ((*left->Value()) == right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_LESS: {
            SBW_Value *v = ((*left->Value()) < right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_LESSEQ: {
            SBW_Value *v = ((*left->Value()) <= right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_GREAT: {
            SBW_Value *v = ((*left->Value()) > right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_GREATEQ: {
            SBW_Value *v = ((*left->Value()) >= right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_AMPAMP: {
            SBW_Value *v = ((*left->Value()) && right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_PIPEPIPE: {
            SBW_Value *v = ((*left->Value()) || right->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }

        default: return new SBW_Variable(new SBW_ValueError(L"OperatorError", L"Undefined binary operation", bn->Line(), bn->Column()), UNASSIGNABLE_ERROR);
    }
}

SBW_Variable *SBW_Interpreter::InterpretUnaryExpression(SBW_Node *node)
{
    SBW_NodeUnary *un = (SBW_NodeUnary*)node;
    SBW_Variable *operand = this->InterpretNode(un->Operand());
    if (operand->Value()->Type() == VT_ERROR_ && operand->Modifier() == UNASSIGNABLE_ERROR)
        return operand;
    
    switch (un->OpType())
    {
        case TT_PLUS: {
            SBW_Value *v = +(*operand->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_MINUS: {
            SBW_Value *v = -(*operand->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_NOT: {
            SBW_Value *v = !(*operand->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_TILDE: {
            SBW_Value *v = ~(*operand->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_DOLLAR: {
            SBW_Value *v = *(*operand->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_PLUSPLUS: {
            SBW_Value *v = ++(*operand->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }
        case TT_MINUSMINUS: {
            SBW_Value *v = --(*operand->Value());
            return v->Type() == VT_ERROR_ ? new SBW_Variable(v, UNASSIGNABLE_ERROR) : new SBW_Variable(v, 0);
        }

        default: return new SBW_Variable(new SBW_ValueError(L"OperatorError", L"Undefined unary operation", un->Line(), un->Column()), UNASSIGNABLE_ERROR);
    }
}