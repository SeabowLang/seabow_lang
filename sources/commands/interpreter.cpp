#include "commands/interpreter.hpp"

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

SBW_Interpreter::SBW_Interpreter(SBW_Options *options)
{
    this->braces = this->brackets = this->parenthesis = 0;

    /* Here could be an interpretation of seabow options */

    delete options;
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
    wprintf(L"Seabow %u.%u.%u (on %s)\nType '#h' for helps, '#q' to quit seabow interpreter, '#l' to list all seabow modules installed, '#c' to clear the screen\n", SEABOW_MAJOR, SEABOW_MINOR, SEABOW_PATCH, SEABOW_OS);

    while (true)
    {
        sbw_string code;
        do
        {
            wprintf((this->parenthesis || this->braces || this->brackets) ? L"... " : L">>> ");
            sbw_string more;
            std::getline(std::wcin, more);

            sbw_ulong i = 0;
            while (i < more.size())
            {
                if (more[i] == L'"') 
                {
                    while (i < more.size() && more[i] != L'"')
                        i++;
                    i++;
                    continue;
                }

                if (more[i] == L'(') this->parenthesis++;
                else if (more[i] == L')') this->parenthesis--;
                else if (more[i] == L'[') this->brackets++;
                else if (more[i] == L']') this->brackets--;
                else if (more[i] == L'{') this->braces++;
                else if (more[i] == L'}') this->braces--;

                i++;
            }

            code += more;
        } while (this->parenthesis || this->brackets || this->braces);

        if (code[0] == L'#') // Special commands
        {
            if (code == L"#q")
                return;
            else if (code == L"#h")
                wprintf(SEABOW_HELPS);
            else if (code == L"#c")
                wprintf(L"\033[2J\033[H");
            else if (code == L"#l") {
                wprintf(L"List of all seabow modules installed:\n");
                wprintf(L"\nTotal: 0\n");
            }
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
        SBW_Variable *ret = (root->Statements().size() > 1) ? this->InterpretNode(root) : this->InterpretNode(root->Statements()[0]);
        SBW_Value *ret_val = ret->Value();

        if (ret->Modifier() == SIGNAL_MODIFIER)
        {
            if (ret_val->Type() != VT_ERROR_)
            {
                if (ret_val->Type() == VT_BYTE_)
                {
                    delete ret_val;
                    ret_val = new SBW_ValueError(L"LoopControllerError", L"keyword 'break' must be in a loop (i.e. for, foreach, while, do-while)", 0, 0);
                }
                else // VT_UBYTE_
                {
                    delete ret_val;
                    ret_val = new SBW_ValueError(L"LoopControllerError", L"keyword 'continue' must be in a loop (i.e. for, foreach, while, do-while)", 0, 0);
                }
            }
            
            wprintf(L"\033[31m%ls\033[0m\n", ((SBW_ValueString*)ret_val->operator_convert(VT_STRING_))->Get().c_str());
        }
        else if (ret->Modifier() == RETURN_MODIFIER)
        {
            wprintf(L"\033[31m%ls\033[0m\n", ((SBW_ValueString*)(new SBW_ValueError(L"ReturnError", L"keyword 'return' must be used in a function", 0, 0))->operator_convert(VT_STRING_))->Get().c_str());
        }
            
        else if (ret->Modifier() != UNDISPLAYABLE && ret_val->Type() != VT_UNDEFINED_)
            wprintf(L"%ls\n", ((SBW_ValueString*)ret_val->operator_convert(VT_STRING_))->Get().c_str());
    }

    delete root;
}

SBW_Variable *SBW_Interpreter::InterpretNode(SBW_Node *node)
{
    switch (node->Type())
    {
        case NT_BAD: return this->InterpretNodeBad(node);
        case NT_COMPOUND: return this->InterpretCompound(node);
        case NT_RETURN: return this->InterpretReturn(node);

        case NT_VARIABLE_DECLARATION: return this->InterpretVarDecl(node);
        case NT_VARIABLE_CALL: return this->InterpretVarCall(node);

        case NT_FUNCTION_CALL: return this->InterpretFuncCall(node);

        case NT_LITERAL: return this->InterpretLiteral(node);
        case NT_PARENTHESIZED: return this->InterpretParenthesized(node);
        case NT_ARRAY: return this->InterpretArray(node);

        case NT_IF: return this->InterpretIf(node);
        case NT_QUEST_OP: return this->InterpretQuestOperation(node);

        case NT_BREAK: return this->InterpretBreak(node);
        case NT_CONTINUE: return this->InterpretContinue(node);
        case NT_FOR: return this->InterpretFor(node);
        case NT_WHILE: return this->InterpretWhile(node);
        case NT_DOWHILE: return this->InterpretDoWhile(node);

        case NT_BINARY_EXPR: return this->InterpretBinaryExpression(node);
        case NT_UNARY_EXPR: return this->InterpretUnaryExpression(node);
        case NT_CONVERT_EXPR: return this->InterpretConvertExpression(node);

        default: return new SBW_Variable(new SBW_ValueError(L"RuntimeError", L"Incorrect statement found", node->Line(), node->Column()), SIGNAL_MODIFIER);
    }
}

SBW_Variable *SBW_Interpreter::InterpretNodeBad(SBW_Node *node) { return new SBW_Variable(((SBW_NodeBad*)node)->Err(), SIGNAL_MODIFIER); }

SBW_Variable *SBW_Interpreter::InterpretCompound(SBW_Node *node)
{
    SBW_NodeCompound *cmp = (SBW_NodeCompound*)node;
    for (sbw_ulong i=0; i<cmp->Statements().size(); i++)
    {
        SBW_Node *nd = cmp->Statements()[i];
        SBW_Variable *v = this->InterpretNode(nd);
        if (v->Modifier() == SIGNAL_MODIFIER || v->Modifier() == RETURN_MODIFIER)
            return v;
    }

    return new SBW_Variable();
}

SBW_Variable *SBW_Interpreter::InterpretReturn(SBW_Node *node)
{
    SBW_NodeReturn *nr = (SBW_NodeReturn*)node;
    SBW_Variable *ret = this->InterpretNode(nr->Expression());
    if (ret->Modifier() == SIGNAL_MODIFIER)
    {
        if (ret->Value()->Type() != VT_ERROR_)
            return new SBW_Variable(new SBW_ValueError(L"ReturnError", L"Cannot return 'break' or 'continue'", nr->Expression()->Line(), nr->Expression()->Column()), SIGNAL_MODIFIER);
        return ret;
    }
    else if (ret->Modifier() == RETURN_MODIFIER)
        return new SBW_Variable(new SBW_ValueError(L"ReturnError", L"Cannot return a returned value", nr->Expression()->Line(), nr->Expression()->Column()), SIGNAL_MODIFIER);

    ret->SetModifier(RETURN_MODIFIER);
    return ret;
}

SBW_Variable *SBW_Interpreter::InterpretVarDecl(SBW_Node *node)
{
    SBW_NodeVarDecl *vd = (SBW_NodeVarDecl*)node;
    if (this->data.count(vd->Name()) != 0) {
        sbw_string dtls = L"A variable named '"; dtls += vd->Name(); dtls += L"' already exists";
        return new SBW_Variable(new SBW_ValueError(L"NameError", dtls, vd->Line(), vd->Column()), SIGNAL_MODIFIER);
    }

    if (vd->Value())
    {
        SBW_Variable *conv = this->InterpretNode(vd->Value());
        if (conv->Modifier() == SIGNAL_MODIFIER)
        {
            if (conv->Value()->Type() != VT_ERROR_)
                return new SBW_Variable(new SBW_ValueError(L"AssignmentError", L"Cannot assign 'break' or 'continue' to any value", vd->Value()->Line(), vd->Value()->Column()), SIGNAL_MODIFIER);
            return conv;
        }
        else if (conv->Modifier() == RETURN_MODIFIER)
            return new SBW_Variable(new SBW_ValueError(L"AssignmentError", L"Cannot assign a returned value", vd->Value()->Line(), vd->Value()->Column()), SIGNAL_MODIFIER);
        else if (conv->Value()->Type() == VT_UNDEFINED_)
        {
            delete conv;
            SBW_Value *null_value = new SBW_ValueNull();
            this->data[vd->Name()] = new SBW_Variable(null_value->AutoConvert(vd->VType()), VOID_MODIFIER);
            delete null_value;
        }
        else
        {
            SBW_Value *val_conv = conv->Value()->AutoConvert(vd->VType());
            if (val_conv->Type() == VT_ERROR_)
                return new SBW_Variable(val_conv, SIGNAL_MODIFIER);

            this->data[vd->Name()] = new SBW_Variable(val_conv, VOID_MODIFIER);
        }
    }
    else
    {
        SBW_Value *null_value = new SBW_ValueNull();
        this->data[vd->Name()] = new SBW_Variable(null_value->AutoConvert(vd->VType()), VOID_MODIFIER);
        delete null_value;
    }

    return new SBW_Variable();
}

SBW_Variable *SBW_Interpreter::InterpretVarCall(SBW_Node *node)
{
    SBW_NodeVarCall *vc = (SBW_NodeVarCall*)node;
    if (this->data.count(vc->Name()) == 0) {
        sbw_string dtls = L"Unknown variable '"; dtls += vc->Name(); dtls += L"'";
        return new SBW_Variable(new SBW_ValueError(L"NameError", dtls, vc->Line(), vc->Column()), SIGNAL_MODIFIER);
    }

    return this->data[vc->Name()];
}

SBW_Variable *SBW_Interpreter::InterpretFuncCall(SBW_Node *node)
{
    SBW_NodeFuncCall *nfc = (SBW_NodeFuncCall*)node;
    if (this->data.count(nfc->Name()) == 0) {
        sbw_string dtls = L"Unknown function '"; dtls += nfc->Name(); dtls += L"'";
        return new SBW_Variable(new SBW_ValueError(L"NameError", dtls, nfc->Line(), nfc->Column()), SIGNAL_MODIFIER);
    }

    SBW_Variable *func_var = this->data[nfc->Name()];
    SBW_Variable *ret_val = nullptr;
    if (func_var->Value()->Type() == VT_EXTERN_FUNCTION_)
    {
        SBW_ValueExternFunc *func = (SBW_ValueExternFunc*)func_var->Value();
        if (func->IsNull()) {
            sbw_string dtls = L"Cannot call null function '"; dtls += nfc->Name(); dtls += L"'";
            return new SBW_Variable(new SBW_ValueError(L"FuncCallError", dtls, nfc->Line(), nfc->Column()), SIGNAL_MODIFIER);
        }

        
    }
    else
    {
        
    }

    return ret_val ? ret_val : new SBW_Variable();
}

SBW_Variable *SBW_Interpreter::InterpretLiteral(SBW_Node *node) { return new SBW_Variable(((SBW_NodeLiteral*)node)->Value(), VOID_MODIFIER); }

SBW_Variable *SBW_Interpreter::InterpretParenthesized(SBW_Node *node) { return this->InterpretNode(((SBW_NodeParenthesized*)node)->Expression()); }

SBW_Variable *SBW_Interpreter::InterpretArray(SBW_Node *node)
{
    SBW_NodeArray *na = (SBW_NodeArray*)node;
    SBW_ValueArray *array = new SBW_ValueArray(na->Values().size());

    for (sbw_ulong i=0; i<na->Values().size(); i++)
    {
        SBW_Node *na_current = na->Values()[i];
        SBW_Variable *va = this->InterpretNode(na_current);
        if (va->Modifier() == SIGNAL_MODIFIER)
        {
            if (va->Value()->Type() != VT_ERROR_)
                return new SBW_Variable(new SBW_ValueError(L"ElementError", L"Array cannot store 'break' or 'continue'", na_current->Line(), na_current->Column()), SIGNAL_MODIFIER);
            return va;
        }
        else if (va->Modifier() == RETURN_MODIFIER)
            return new SBW_Variable(new SBW_ValueError(L"ElementError", L"Array cannot store a returned value", na_current->Line(), na_current->Column()), SIGNAL_MODIFIER);
        
        (*array) += va->Value();
    }

    return new SBW_Variable(array, VOID_MODIFIER);
}

SBW_Variable *SBW_Interpreter::InterpretIf(SBW_Node *node)
{
    SBW_NodeIf *ni = (SBW_NodeIf*)node;
    SBW_Variable *test = this->InterpretNode(ni->Condition());
    if (test->Modifier() == SIGNAL_MODIFIER)
    {
        if (test->Value()->Type() != VT_ERROR_)
            return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'if-condition' cannot be 'break' or 'continue'", ni->Condition()->Line(), ni->Condition()->Column()), SIGNAL_MODIFIER);
        return test;
    }
    else if (test->Modifier() == RETURN_MODIFIER)
        return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'if-condition' cannot be a returned value", ni->Condition()->Line(), ni->Condition()->Column()), SIGNAL_MODIFIER);
    
    if (((SBW_ValueBoolean*)test->Value()->operator_convert(VT_BOOLEAN_))->Get())
        return this->InterpretNode(ni->Body());
    
    for (sbw_ulong i=0; i<ni->ElifClauses().size(); i++)
    {
        SBW_NodeElif *ne = (SBW_NodeElif*)ni->ElifClauses()[i];
        SBW_Variable *test_ne = this->InterpretNode(ne->Condition());
        if (test_ne->Modifier() == SIGNAL_MODIFIER)
        {
            if (test_ne->Value()->Type() != VT_ERROR_)
                return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'elif-condition' cannot be 'break' or 'continue'", ne->Condition()->Line(), ne->Condition()->Column()), SIGNAL_MODIFIER);
            return test_ne;
        }
        else if (test_ne->Modifier() == RETURN_MODIFIER)
            return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'elif-condition' cannot be a returned value", ne->Condition()->Line(), ne->Condition()->Column()), SIGNAL_MODIFIER);
        
        if (((SBW_ValueBoolean*)test_ne->Value()->operator_convert(VT_BOOLEAN_))->Get())
            return this->InterpretNode(ne->Body());
    }

    if (ni->ElseBody())
        return this->InterpretNode(ni->ElseBody());
    
    return new SBW_Variable();
}

SBW_Variable *SBW_Interpreter::InterpretQuestOperation(SBW_Node *node)
{
    SBW_NodeQuest *q = (SBW_NodeQuest*)node;
    SBW_Variable *test = this->InterpretNode(q->Condition());
    if (test->Modifier() == SIGNAL_MODIFIER)
    {
        if (test->Value()->Type() != VT_ERROR_)
            return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'question-operator-condition' cannot be 'break' or 'continue'", q->Condition()->Line(), q->Condition()->Column()), SIGNAL_MODIFIER);
        return test;
    }
    else if (test->Modifier() == RETURN_MODIFIER)
        return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'question-operator-condition' cannot be a returned value", q->Condition()->Line(), q->Condition()->Column()), SIGNAL_MODIFIER);
    
    return (((SBW_ValueBoolean*)test->Value()->operator_convert(VT_BOOLEAN_))->Get()) 
        ? this->InterpretNode(q->First())
        : this->InterpretNode(q->Second());
}

SBW_Variable *SBW_Interpreter::InterpretBreak(SBW_Node *node)
{
    return new SBW_Variable(new SBW_ValueByte((sbw_byte*)0), SIGNAL_MODIFIER);
}

SBW_Variable *SBW_Interpreter::InterpretContinue(SBW_Node *node)
{
    return new SBW_Variable(new SBW_ValueUbyte((sbw_ubyte*)0), SIGNAL_MODIFIER);
}

SBW_Variable *SBW_Interpreter::InterpretFor(SBW_Node *node)
{
    SBW_NodeFor *nf = (SBW_NodeFor*)node;
    SBW_Variable *val = this->InterpretNode(nf->LoopVal());
    if (val->Modifier() == SIGNAL_MODIFIER)
    {
        if (val->Value()->Type() != VT_ERROR_)
            return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'for-value' cannot be 'break' or 'continue'", nf->LoopVal()->Line(), nf->LoopVal()->Column()), SIGNAL_MODIFIER);
        return val;
    }
    else if (val->Modifier() == RETURN_MODIFIER)
        return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'for-value' cannot be a returned value", nf->LoopVal()->Line(), nf->LoopVal()->Column()), SIGNAL_MODIFIER);

    while (true)
    {
        SBW_Variable *test = this->InterpretNode(nf->Condition());
        if (test->Modifier() == SIGNAL_MODIFIER)
        {
            if (test->Value()->Type() != VT_ERROR_)
                return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'for-condition' cannot be 'break' or 'continue'", nf->Condition()->Line(), nf->Condition()->Column()), SIGNAL_MODIFIER);
            return test;
        }
        else if (test->Modifier() == RETURN_MODIFIER)
            return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'for-condition' cannot be a returned value", nf->Condition()->Line(), nf->Condition()->Column()), SIGNAL_MODIFIER);
        
        if (!((SBW_ValueBoolean*)test->Value()->operator_convert(VT_BOOLEAN_))->Get())
            break;
        
        SBW_Variable *mod = this->InterpretNode(nf->Body());
        if (mod->Modifier() == SIGNAL_MODIFIER)
        {
            if (mod->Value()->Type() == VT_ERROR_)
                return mod;
            else if (mod->Value()->Type() == VT_BYTE_)
                break;
        }
        else if (mod->Modifier() == RETURN_MODIFIER)
            return mod;
        
        SBW_Variable *expr = this->InterpretNode(nf->LoopExpr());
        if (expr->Modifier() == SIGNAL_MODIFIER)
        {
            if (expr->Value()->Type() != VT_ERROR_)
                return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'for-expression' cannot be 'break' or 'continue'", nf->LoopExpr()->Line(), nf->LoopExpr()->Column()), SIGNAL_MODIFIER);
            return expr;
        }
        else if (expr->Modifier() == RETURN_MODIFIER)
            return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'for-expression' cannot be a returned value", nf->LoopExpr()->Line(), nf->LoopExpr()->Column()), SIGNAL_MODIFIER);
    }

    return new SBW_Variable();
}

SBW_Variable *SBW_Interpreter::InterpretWhile(SBW_Node *node)
{
    SBW_NodeWhile *nw = (SBW_NodeWhile*)node;
    while (true)
    {
        SBW_Variable *test = this->InterpretNode(nw->Condition());
        if (test->Modifier() == SIGNAL_MODIFIER)
        {
            if (test->Value()->Type() != VT_ERROR_)
                return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'while-condition' cannot be 'break' or 'continue'", nw->Condition()->Line(), nw->Condition()->Column()), SIGNAL_MODIFIER);
            return test;
        }
        else if (test->Modifier() == RETURN_MODIFIER)
            return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'while-condition' cannot be a returned value", nw->Condition()->Line(), nw->Condition()->Column()), SIGNAL_MODIFIER);
        
        if (!((SBW_ValueBoolean*)test->Value()->operator_convert(VT_BOOLEAN_))->Get())
            break;
        
        SBW_Variable *mod = this->InterpretNode(nw->Body());
        if (mod->Modifier() == SIGNAL_MODIFIER)
        {
            if (mod->Value()->Type() == VT_ERROR_)
                return mod;
            else if (mod->Value()->Type() == VT_BYTE_)
                break;
        }
        else if (mod->Modifier() == RETURN_MODIFIER)
            return mod;
    }

    return new SBW_Variable();
}

SBW_Variable *SBW_Interpreter::InterpretDoWhile(SBW_Node *node)
{
    SBW_NodeDowhile *ndw = (SBW_NodeDowhile*)node;
    while (true)
    {
        SBW_Variable *mod = this->InterpretNode(ndw->Body());
        if (mod->Modifier() == SIGNAL_MODIFIER)
        {
            if (mod->Value()->Type() == VT_ERROR_)
                return mod;
            else if (mod->Value()->Type() == VT_BYTE_)
                break;
        }   
        else if (mod->Modifier() == RETURN_MODIFIER)
            return mod;
        
        SBW_Variable *test = this->InterpretNode(ndw->Condition());
        if (test->Modifier() == SIGNAL_MODIFIER)
        {
            if (test->Value()->Type() != VT_ERROR_)
                return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'do-while-condition' cannot be 'break' or 'continue'", ndw->Condition()->Line(), ndw->Condition()->Column()), SIGNAL_MODIFIER);
            return test;
        }
        else if (test->Modifier() == RETURN_MODIFIER)
            return new SBW_Variable(new SBW_ValueError(L"ConditionError", L"'while-condition' cannot be a returned value", ndw->Condition()->Line(), ndw->Condition()->Column()), SIGNAL_MODIFIER);
        
        if (!((SBW_ValueBoolean*)test->Value()->operator_convert(VT_BOOLEAN_))->Get())
            break;
    }

    return new SBW_Variable();
}

SBW_Variable *SBW_Interpreter::InterpretBinaryExpression(SBW_Node *node)
{
    SBW_NodeBinary *bn = (SBW_NodeBinary*)node;
    SBW_Variable *left = this->InterpretNode(bn->Left());
    if (left->Modifier() == SIGNAL_MODIFIER)
    {
        if (left->Value()->Type() != VT_ERROR_)
            return new SBW_Variable(new SBW_ValueError(L"OperatorError", L"Binary operand cannot be 'break' or 'continue'", bn->Left()->Line(), bn->Left()->Column()), SIGNAL_MODIFIER);
        return left;
    }
    else if (left->Modifier() == RETURN_MODIFIER)
        return new SBW_Variable(new SBW_ValueError(L"OperatorError", L"Binary operand cannot be a returned value", bn->Left()->Line(), bn->Left()->Column()), SIGNAL_MODIFIER);

    SBW_Variable *right = bn->Right() ? this->InterpretNode(bn->Right()) : new SBW_Variable(new SBW_Value(), VOID_MODIFIER);
    if (right->Modifier() == SIGNAL_MODIFIER)
    {
        if (right->Value()->Type() != VT_ERROR_)
            return new SBW_Variable(new SBW_ValueError(L"OperatorError", L"Binary operand cannot be 'break' or 'continue'", bn->Right()->Line(), bn->Right()->Column()), SIGNAL_MODIFIER);
        return right;
    }
    else if (right->Modifier() == RETURN_MODIFIER)
        return new SBW_Variable(new SBW_ValueError(L"OperatorError", L"Binary operand cannot be a returned value", bn->Right()->Line(), bn->Right()->Column()), SIGNAL_MODIFIER);

    SBW_Value *v = nullptr;
    sbw_ubyte mode = VOID_MODIFIER;
    switch (bn->OpType())
    {
        case TT_PLUS: v = ((*left->Value()) + right->Value()); break;
        case TT_PLUSEQ: v = left->Value()->operator+=(right->Value()); mode = UNDISPLAYABLE; break;
        case TT_PLUSPLUS: v = (*left->Value())++; mode = UNDISPLAYABLE; break;
        case TT_MINUS: v = ((*left->Value()) - right->Value()); break;
        case TT_MINUSEQ: v = ((*left->Value()) -= right->Value()); mode = UNDISPLAYABLE; break;
        case TT_MINUSMINUS: v = (*left->Value())--; mode = UNDISPLAYABLE; break;
        case TT_STAR: v = ((*left->Value()) * right->Value()); break;
        case TT_STAREQ: v = ((*left->Value()) *= right->Value()); mode = UNDISPLAYABLE; break;
        case TT_POWER: v = left->Value()->operator_power(right->Value()); break;
        case TT_POWEREQ: v = left->Value()->operator_power_eq(right->Value()); mode = UNDISPLAYABLE; break;
        case TT_SLASH: v = ((*left->Value()) / right->Value()); break;
        case TT_SLASHEQ: v = ((*left->Value()) /= right->Value()); mode = UNDISPLAYABLE; break;
        case TT_PERCENT: v = (*left->Value()) % right->Value(); break;
        case TT_PERCENTEQ: v = (*left->Value()) %= right->Value(); mode = UNDISPLAYABLE; break;
        case TT_HAT: v = ((*left->Value()) ^ right->Value()); break;
        case TT_HATEQ: v = ((*left->Value()) ^= right->Value()); mode = UNDISPLAYABLE; break;
        case TT_AMP: v = ((*left->Value()) & right->Value()); break;
        case TT_AMPEQ: v = ((*left->Value()) &= right->Value()); mode = UNDISPLAYABLE; break;
        case TT_PIPE: v = ((*left->Value()) | right->Value()); break;
        case TT_PIPEEQ: v = ((*left->Value()) |= right->Value()); mode = UNDISPLAYABLE; break;
        case TT_LSHIFT: v = ((*left->Value()) << right->Value()); break;
        case TT_LSHIFTEQ: v = ((*left->Value()) <<= right->Value()); mode = UNDISPLAYABLE; break;
        case TT_RSHIFT: v = ((*left->Value()) >> right->Value()); break;
        case TT_RSHIFTEQ: v = ((*left->Value()) >>= right->Value()); mode = UNDISPLAYABLE; break;
        case TT_NE: v = ((*left->Value()) != right->Value()); break;
        case TT_EE: v = ((*left->Value()) == right->Value()); break;
        case TT_LESS: v = ((*left->Value()) < right->Value()); break;
        case TT_LESSEQ: v = ((*left->Value()) <= right->Value()); break;
        case TT_GREAT: v = ((*left->Value()) > right->Value()); break;
        case TT_GREATEQ: v = ((*left->Value()) >= right->Value()); break;
        case TT_AMPAMP: v = ((*left->Value()) && right->Value()); break;
        case TT_PIPEPIPE: v = ((*left->Value()) || right->Value()); break;
        case TT_EQ: v = ((*left->Value()) = right->Value()); mode = UNDISPLAYABLE; break;
    
        default: v = nullptr; break;
    }

    if (v == nullptr)
        return new SBW_Variable(new SBW_ValueError(L"OperatorError", L"Undefined binary operation", bn->Line(), bn->Column()), SIGNAL_MODIFIER);
    
    if (v->Type() == VT_ERROR_)
    {
        SBW_ValueError *err = (SBW_ValueError*)v;
        err->SetLine(bn->Line());
        err->SetColumn(bn->Column());
        return new SBW_Variable(err, SIGNAL_MODIFIER);
    }

    return new SBW_Variable(v, mode);
}

SBW_Variable *SBW_Interpreter::InterpretUnaryExpression(SBW_Node *node)
{
    SBW_NodeUnary *un = (SBW_NodeUnary*)node;
    SBW_Variable *operand = this->InterpretNode(un->Operand());
    if (operand->Modifier() == SIGNAL_MODIFIER)
    {
        if (operand->Value()->Type() != VT_ERROR_)
            return new SBW_Variable(new SBW_ValueError(L"OperatorError", L"Unary operand cannot be 'break' or 'continue'", un->Operand()->Line(), un->Operand()->Column()), SIGNAL_MODIFIER);
        return operand;
    }
    else if (operand->Modifier() == RETURN_MODIFIER)
        return new SBW_Variable(new SBW_ValueError(L"OperatorError", L"Unary operand cannot be a returned value", un->Operand()->Line(), un->Operand()->Column()), SIGNAL_MODIFIER);
    
    SBW_Value *v = nullptr;
    sbw_ubyte mode = VOID_MODIFIER;
    switch (un->OpType())
    {
        case TT_PLUS: v = +(*operand->Value()); break;
        case TT_MINUS: v = -(*operand->Value()); break;
        case TT_NOT: v = !(*operand->Value()); break;
        case TT_TILDE: v = ~(*operand->Value()); break;
        case TT_DOLLAR: v = *(*operand->Value()); break;
        case TT_PLUSPLUS: v = ++(*operand->Value()); mode = UNDISPLAYABLE; break;
        case TT_MINUSMINUS: v = --(*operand->Value()); mode = UNDISPLAYABLE; break;

        default: v = nullptr; break;
    }

    if (v == nullptr)
        return new SBW_Variable(new SBW_ValueError(L"OperatorError", L"Undefined unary operation", un->Line(), un->Column()), SIGNAL_MODIFIER);
    
    if (v->Type() == VT_ERROR_)
    {
        SBW_ValueError *err = (SBW_ValueError*)v;
        err->SetLine(un->Line());
        err->SetColumn(un->Column());
        return new SBW_Variable(err, SIGNAL_MODIFIER);
    }

    return new SBW_Variable(v, mode);
}

SBW_Variable *SBW_Interpreter::InterpretConvertExpression(SBW_Node *node)
{
    SBW_NodeConvert *nc = (SBW_NodeConvert*)node;
    SBW_Variable *operand = this->InterpretNode(nc->Expression());
    if (operand->Modifier() == SIGNAL_MODIFIER)
    {
        if (operand->Value()->Type() != VT_ERROR_)
            return new SBW_Variable(new SBW_ValueError(L"ConvertionError", L"Cannot convert 'break' or 'continue'", nc->Expression()->Line(), nc->Expression()->Column()), SIGNAL_MODIFIER);
    }
    else if (operand->Modifier() == RETURN_MODIFIER)
        return new SBW_Variable(new SBW_ValueError(L"ConvertionError", L"Cannot convert a returned value", nc->Expression()->Line(), nc->Expression()->Column()), SIGNAL_MODIFIER);
    
    SBW_Value *val = operand->Value()->operator_convert(nc->DestType());
    return val->Type() == VT_ERROR_ ? new SBW_Variable(val, SIGNAL_MODIFIER) : new SBW_Variable(val, VOID_MODIFIER);
}