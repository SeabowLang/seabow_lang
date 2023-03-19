#include "parser.hpp"

sbw_none ClearNodeList(std::vector<SBW_Node*> nodes)
{
    while (!nodes.empty())
    {
        delete nodes.back();
        nodes.pop_back();
    }   
}

SBW_Parser::SBW_Parser(sbw_string code)
{
    SBW_Lexer *lex = new SBW_Lexer(code);
    SBW_Token *tok = lex->Lex();

    this->size = this->pos = 0;
    while (tok->Type() != TT_EOF)
    {
        this->size++;
        this->tokens.push_back(tok);
        tok = lex->Lex();
    }
    this->tokens.push_back(tok);
    delete lex;
}

SBW_Parser::~SBW_Parser()
{
    while (!this->tokens.empty())
    {
        delete this->tokens.back();
        this->tokens.pop_back();
    }
}

SBW_Node *SBW_Parser::Parse(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Get()->Column();
    std::vector<SBW_Node*> stats;
    while (this->Get()->Type() != TT_EOF)
    {
        SBW_Node *node = this->ParseStatement(true);
        stats.push_back(node);
    }

    return new SBW_NodeCompound(line, column, stats);
}

SBW_Token *SBW_Parser::Advance(sbw_none)
{
    SBW_Token *current = this->Get();
    if (current->Type() != TT_EOF)
        this->pos++;
    
    return current;
}

SBW_Token *SBW_Parser::Get(sbw_none) { return this->tokens[this->pos]; }

SBW_Token *SBW_Parser::Get(sbw_long offset)
{
    sbw_ulong index = this->pos + offset;
    if (index < this->size)
        return this->tokens[index];
    
    return this->tokens.back();
}

SBW_NodeBad *SBW_Parser::Match(sbw_token_type tt, sbw_string t_txt)
{
    SBW_Token *current = this->Advance();
    if (current->Type() != tt)
    {
        sbw_string err = L"Expected '"; err += t_txt; err += L'\'';
        return new SBW_NodeBad(current->Line(), current->Column(), new SBW_ValueError(L"SyntaxError", err, current->Line(), current->Column()));
    }

    return (SBW_NodeBad*)0;
}

SBW_Node *SBW_Parser::ParseStatement(sbw_bool is_stat)
{
    SBW_Node *node = (SBW_Node*)0;
    SBW_Token *current = this->Get();
    if (current->Type() == TT_LBRACE)
        return this->ParseCompound();
    else if (current->Type() == TT_WORD)
    {
        if (GetKeywordType(current->Text()) < VT_NULL_)
        {
            if (this->Get(1)->Type() != TT_LPAR)
                node = this->ParseDeclaration();
            else
                node = this->ParseConvertExpression();
        }
        else if (current->Text() == L"break")
        {
            sbw_ulong line = this->Get()->Line();
            sbw_ulong column = this->Advance()->Column();
            node = new SBW_NodeBreak(line, column);
        }
        else if (current->Text() == L"continue")
        {
            sbw_ulong line = this->Get()->Line();
            sbw_ulong column = this->Advance()->Column();
            node = new SBW_NodeContinue(line, column);
        }
        else if (current->Text() == L"null")
        {
            sbw_ulong line = this->Get()->Line();
            sbw_ulong column = this->Advance()->Column();
            node = new SBW_NodeLitteral(line, column, new SBW_ValueNull());
        }
        else if (current->Text() == L"return")
            node = this->ParseReturn();
        else if (current->Text() == L"if")
            node = this->ParseIf();
        else if (current->Text() == L"switch")
            node = this->ParseSwitch();
        else if (current->Text() == L"for")
            node = this->ParseFor();
        else if (current->Text() == L"foreach")
            node = this->ParseForeach();
        else if (current->Text() == L"while")
            node = this->ParseWhile();
        else if (current->Text() == L"do")
            node = this->ParseDowhile();
        else if (current->Text() == L"try")
            node = this->ParseTry();
        else if (current->Text() == L"include")
            node = this->ParseIncImp(true);
        else if (current->Text() == L"import")
            node = this->ParseIncImp(false);
        else
        {
            sbw_token_type after = this->Get(1)->Type();
            if (after == TT_EQ || after == TT_PLUSEQ || after == TT_MINUSEQ || after == TT_STAREQ || after == TT_SLASHEQ || after == TT_POWEREQ || after == TT_PERCENTEQ ||
                after == TT_LSHIFTEQ || after == TT_RSHIFTEQ || after == TT_PIPEEQ || after == TT_AMPEQ || after == TT_HATEQ)
            node = this->ParseVariableAssignment();
        }
    }

    if (!node)
        node = this->ParseBinaryUnaryExpression(0);
    
    if (node->Type() == NT_BAD)
        return node;

    if (!node)
        return new SBW_NodeBad(current->Line(), current->Column(), new SBW_ValueError(L"SyntaxError", L"Invalid statement", current->Line(), current->Column()));

    if (is_stat)
    {
        if (this->Get()->Type() != TT_SEMI && this->Get()->Type() != TT_RBRACE)
        {
            SBW_Token *old = this->Get(-1);
            sbw_ulong col = old->Column() + old->Text().length() + 1;
            if (old->Type() == TT_CHAR || old->Type() == TT_STRING) col++;
            return new SBW_NodeBad(old->Line(), col, new SBW_ValueError(L"SyntaxError", L"Expected ';'", old->Line(), col));
        }

        this->Advance();
    }

    return node;
}

SBW_Node *SBW_Parser::ParseCompound(sbw_none)
{
    this->Advance();
    SBW_Token *first = this->Get();
    std::vector<SBW_Node*> stats;
    while (this->Get()->Type() != TT_RBRACE && this->Get()->Type() != TT_EOF)
    {
        SBW_Node *stat = this->ParseStatement(true);
        stats.push_back(stat);
    }

    if (this->Get()->Type() != TT_RBRACE)
    {
        ClearNodeList(stats);
        return this->Match(TT_RBRACE, L"}");
    }

    return new SBW_NodeCompound(first->Line(), first->Column(), stats);
}

SBW_Node *SBW_Parser::ParseConvertExpression(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Get()->Column();
    sbw_value_type dest_type = GetKeywordType(this->Advance()->Text());
    if (dest_type == VT_ANY_)
        return new SBW_NodeBad(line, column, new SBW_ValueError(L"ValueError", L"Can not convert value to type 'any'", line, column));
    else if (dest_type == VT_UNDEFINED_)
        return new SBW_NodeBad(line, column, new SBW_ValueError(L"ValueError", L"Can not convert value to a non-seabow type", line, column));

    this->Advance(); // Skip '('
    SBW_Node *expr = this->ParseStatement(false);
    SBW_NodeBad *err = this->Match(TT_RPAR, L")");
    if (err)
        return err;
    
    return new SBW_NodeConvert(line, column, dest_type, expr);
}

SBW_Node *SBW_Parser::ParseDeclaration(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Get()->Column();
    sbw_value_type decl_type = GetKeywordType(this->Advance()->Text());
    SBW_Token *name_tok = this->Get();
    if (name_tok->Type() != TT_WORD)
        return this->Match(TT_WORD, L"declaration name");
    
    switch (decl_type)
    {
        case VT_ARRAY_: {}
        case VT_LIST_: {}
        case VT_DICT_: {}

        case VT_ENUMERATION_: {}
        case VT_STRUCTURE_: {}
        case VT_CLASS_: {}

        default: {
            this->Advance();
            if (this->Get()->Type() == TT_LPAR)
                return this->ParseFunctionDeclaration(line, column, decl_type, name_tok->Text());
            
            if (decl_type == VT_VOID_)
                return new SBW_NodeBad(line, column, new SBW_ValueError(L"SyntaxError", L"Cannot define a void variable", line, column));

            return this->ParseVariableDeclaration(line, column, decl_type, name_tok->Text());
        }
    }
}

SBW_Node *SBW_Parser::ParseFunctionDeclaration(sbw_ulong line, sbw_ulong column, sbw_value_type decl_type, sbw_string name)
{
    this->Advance();
    std::vector<SBW_Node*> params;
    while (this->Get()->Type() != TT_RPAR && this->Get()->Type() != TT_EOF)
    {
        SBW_Node *param = this->ParseParameter();
        if (param->Type() == NT_BAD)
        {
            ClearNodeList(params);
            return param;
        }

        if (this->Get()->Type() == TT_COMMA)
            this->Advance();
    }

    SBW_NodeBad *err = this->Match(TT_RPAR, L")");
    if (err)
    {
        ClearNodeList(params);
        return err;
    }

    SBW_Node *body = this->ParseCompound();
    if (body->Type() == NT_BAD)
    {
        ClearNodeList(params);
        return body;
    }

    return new SBW_NodeFuncDecl(line, column, decl_type, name, params, body);
}

SBW_Node *SBW_Parser::ParseVariableDeclaration(sbw_ulong line, sbw_ulong column, sbw_value_type decl_type, sbw_string name)
{
    if (this->Get()->Type() != TT_EQ)
        return new SBW_NodeVarDecl(line, column, decl_type, name, (SBW_Node*)0);
    
    this->Advance();
    SBW_Node *value = this->ParseStatement(false);
    if (value->Type() == NT_BAD)
        return value;

    return new SBW_NodeVarDecl(line, column, decl_type, name, value);
}

SBW_Node *SBW_Parser::ParseParameter(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Get()->Column();
    sbw_value_type param_type = GetKeywordType(this->Get()->Text());
    if (param_type == VT_UNDEFINED_)
        return this->Match(TT_BAD, L"parameter type");
    this->Advance();

    SBW_Token *name_tok = this->Get();
    if (name_tok->Type() != TT_WORD)
        return this->Match(TT_WORD, L"parameter name");
    this->Advance();

    SBW_Node *default_value = (SBW_Node*)0;
    if (this->Get()->Type() == TT_EQ)
    {
        this->Advance();
        default_value = this->ParseStatement(false);
    }

    return new SBW_NodeParam(line, column, param_type, name_tok->Text(), default_value);
}

SBW_Node *SBW_Parser::ParseReturn(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_Node *expr = nullptr;
    if (this->Get()->Type() != TT_SEMI)
    {
        expr = this->ParseStatement(false);
        if (expr->Type() == NT_BAD)
            return expr;
    }
    
    return new SBW_NodeReturn(line, column, expr);
}

SBW_Node *SBW_Parser::ParseVariableAssignment(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Get()->Column();
    sbw_string name = this->Advance()->Text();
    sbw_token_type eq_type = this->Get()->Type();
    switch (eq_type)
    {
        case TT_EQ: case TT_PLUSEQ: case TT_MINUSEQ: case TT_STAREQ: case TT_SLASHEQ:
        case TT_POWEREQ: case TT_PERCENTEQ: case TT_LSHIFTEQ: case TT_RSHIFTEQ: case TT_HATEQ:
        case TT_AMPEQ: case TT_PIPEEQ:
            this->Advance(); break;

        default: return this->Match(TT_EQ, L"equals character");
    }

    SBW_Node *value = this->ParseStatement(false);
    if (value->Type() == NT_BAD)
        return value;
    
    return new SBW_NodeVarAssign(line, column, name, eq_type, value);
}

SBW_Node *SBW_Parser::ParseIf(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_NodeBad *err = this->Match(TT_LPAR, L"(");
    if (err)
        return err;
    
    SBW_Node *condition = this->ParseStatement(false);
    if (condition->Type() == NT_BAD)
        return condition;
    
    err = this->Match(TT_RPAR, L")");
    if (err)
        return err;
    
    SBW_Node *body = this->ParseStatement(false);
    if (body->Type() == NT_BAD)
        return body;
    
    std::vector<SBW_Node*> elif_clauses;
    while (this->Get(1)->Text() == L"elif")
    {
        this->Advance(); // Skip '}'
        SBW_Node *elif_clause = this->ParseElif();
        if (elif_clause->Type() == NT_BAD)
        {
            ClearNodeList(elif_clauses);
            return elif_clause;
        }

        elif_clauses.push_back(elif_clause);
    }

    SBW_Node *else_body = (SBW_Node*)0;
    if (this->Get(1)->Text() == L"else")
    {
        this->Advance(); // Skip '}'
        this->Advance(); // Skip 'else'
        else_body = this->ParseStatement(false);
        if (else_body->Type() == NT_BAD)
            return else_body;
    }

    return new SBW_NodeIf(line, column, condition, body, else_body, elif_clauses);
}

SBW_Node *SBW_Parser::ParseElif(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_NodeBad *err = this->Match(TT_LPAR, L"(");
    if (err)
        return err;
    
    SBW_Node *condition = this->ParseStatement(false);
    err = this->Match(TT_RPAR, L")");
    if (err)
        return err;
    
    SBW_Node *body = this->ParseStatement(false);
    if (body->Type() == NT_BAD)
        return body;
    
    return new SBW_NodeElif(line, column, condition, body);
}

SBW_Node *SBW_Parser::ParseSwitch(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_NodeBad *err = this->Match(TT_LPAR, L"(");
    if (err)
        return err;
    
    SBW_Node *condition = this->ParseStatement(false);
    if (condition->Type() == NT_BAD)
        return condition;
    
    err = this->Match(TT_RPAR, L")");
    if (err)
        return err;
    
    err = this->Match(TT_LBRACE, L"{");
    if (err)
        return err;
    
    std::vector<SBW_Node*> case_clauses;
    while (this->Get()->Text() == L"case")
    {
        SBW_Node *case_clause = this->ParseCase();
        if (case_clause->Type() == NT_BAD)
        {
            ClearNodeList(case_clauses);
            return case_clause;
        }

        case_clauses.push_back(case_clause);
        if (case_clause->Type() != NT_COMPOUND) this->Advance(); // Skip ';'
    }

    SBW_Node *default_body = (SBW_Node*)0;
    if (this->Get()->Text() == L"default")
    {
        this->Advance(); // Skip 'default'
        this->Advance(); // Skip ':'
        default_body = this->ParseStatement(false);
        if (default_body->Type() == NT_BAD)
        {
            ClearNodeList(case_clauses);
            return default_body;
        }

        if (default_body->Type() != NT_COMPOUND) this->Advance(); // Skip ';'
    }

    if (!default_body && case_clauses.empty())
        return new SBW_NodeBad(line, column, new SBW_ValueError(L"SyntaxError", L"Switch statement need at least one 'case' or 'default'", line, column));
    
    return new SBW_NodeSwitch(line, column, condition, default_body, case_clauses);
}

SBW_Node *SBW_Parser::ParseCase(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    std::vector<SBW_Node*> expressions;

    SBW_Node *expr = this->ParseStatement(false);
    if (expr->Type() == NT_BAD)
        return expr;
    
    expressions.push_back(expr);
    while (this->Get()->Type() == TT_COMMA)
    {
        this->Advance(); // Skip ','
        expr = this->ParseStatement(false);
        if (expr->Type() == NT_BAD)
        {
            ClearNodeList(expressions);
            return expr;
        }

        expressions.push_back(expr);
    }

    SBW_NodeBad *err = this->Match(TT_COLON, L":");
    if (err)
    {
        ClearNodeList(expressions);
        return err;
    }

    SBW_Node *body = this->ParseStatement(false);
    if (body->Type() == NT_BAD)
    {
        ClearNodeList(expressions);
        return body;
    }

    return new SBW_NodeCase(line, column, expressions, body);
}

SBW_Node *SBW_Parser::ParseQuestionOp(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_Node *condition = this->ParseStatement(false);
    if (condition->Type() == NT_BAD)
        return condition;
    
    SBW_NodeBad *err = this->Match(TT_COLON, L":");
    if (err)
        return err;
    
    SBW_Node *first = this->ParseStatement(false);
    if (first->Type() == NT_BAD)
        return first;
    
    err = this->Match(TT_COLON, L":");
    if (err)
        return err;
    
    SBW_Node *second = this->ParseStatement(false);
    if (second->Type() == NT_BAD)
        return second;
    
    return new SBW_NodeQuest(line, column, condition, first, second);
}

SBW_Node *SBW_Parser::ParseFor(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_NodeBad *err = this->Match(TT_LPAR, L"(");
    if (err)
        return err;
    
    SBW_Node *loop_val = this->ParseStatement(false);
    if (loop_val->Type() == NT_BAD)
        return loop_val;
    else if (loop_val->Type() != NT_VARIABLE_DECLARATION && loop_val->Type() != NT_VARIABLE_ASSIGNMENT && loop_val->Type() != NT_VARIABLE_CALL)
        return new SBW_NodeBad(loop_val->Line(), loop_val->Column(), new SBW_ValueError(L"SyntaxError", L"A variable is expected", loop_val->Line(), loop_val->Column()));
    
    err = this->Match(TT_SEMI, L";");
    if (err)
        return err;
    
    SBW_Node *loop_condition = this->ParseStatement(false);
    if (loop_condition->Type() == NT_BAD)
        return loop_condition;
    
    err = this->Match(TT_SEMI, L";");
    if (err)
        return err;
    
    SBW_Node *loop_expr = this->ParseStatement(false);
    if (loop_expr->Type() == NT_BAD)
        return loop_expr;
    
    err = this->Match(TT_RPAR, L")");
    if (err)
        return err;
    
    SBW_Node *body = this->ParseStatement(false);
    if (body->Type() == NT_BAD)
        return body;
    
    return new SBW_NodeFor(line, column, loop_val, loop_condition, loop_expr, body);
}

SBW_Node *SBW_Parser::ParseForeach(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_NodeBad *err = this->Match(TT_LPAR, L"(");
    if (err)
        return err;
    
    SBW_Node *loop_val = this->ParseStatement(false);
    if (loop_val->Type() == NT_BAD)
        return loop_val;
    else if (loop_val->Type() != NT_VARIABLE_CALL)
        return new SBW_NodeBad(loop_val->Line(), loop_val->Column(), new SBW_ValueError(L"SyntaxError", L"A variable name is expected", loop_val->Line(), loop_val->Column()));
    
    if (this->Get()->Type() != TT_WORD && this->Get()->Text() != L"in")
        return this->Match(TT_WORD, L"in");
    this->Advance(); // Skip 'in'
    
    SBW_Node *loop_container = this->ParseStatement(false);
    if (loop_container->Type() == NT_BAD)
        return loop_container;
    
    err = this->Match(TT_RPAR, L")");
    if (err)
        return err;
    
    SBW_Node *body = this->ParseStatement(false);
    if (body->Type() == NT_BAD)
        return body;
    
    return new SBW_NodeForeach(line, column, loop_val, loop_container, body);
}

SBW_Node *SBW_Parser::ParseWhile(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_NodeBad *err = this->Match(TT_LPAR, L"(");
    if (err)
        return err;
    
    SBW_Node *condition = this->ParseStatement(false);
    if (condition->Type() == NT_BAD)
        return condition;
    
    err = this->Match(TT_RPAR, L")");
    if (err)
        return err;
    
    SBW_Node *body = this->ParseStatement(false);
    if (body->Type() == NT_BAD)
        return body;
    
    return new SBW_NodeWhile(line, column, condition, body);
}

SBW_Node *SBW_Parser::ParseDowhile(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_Node *body = this->ParseStatement(false);
    if (body->Type() == NT_BAD)
        return body;
    
    this->Advance(); // Skip ';' or '}'
    if (this->Get()->Text() != L"while")
        return new SBW_NodeBad(this->Get()->Line(), this->Get()->Column(), new SBW_ValueError(L"SyntaxError", L"'while' keyword is expected", this->Get()->Line(), this->Get()->Column()));
    
    this->Advance();
    SBW_NodeBad *err = this->Match(TT_LPAR, L"(");
    if (err)
        return err;
    
    SBW_Node *condition = this->ParseStatement(false);
    if (condition->Type() == NT_BAD)
        return condition;
    
    err = this->Match(TT_RPAR, L")");
    if (err)
        return err;
    
    return new SBW_NodeDowhile(line, column, body, condition);
}

SBW_Node *SBW_Parser::ParseTry(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_NodeBad *err = this->Match(TT_LPAR, L"(");
    if (err)
        return err;
    
    if (this->Get()->Type() != TT_WORD)
        return this->Match(TT_WORD, L"error's variable name");
    sbw_string name = this->Advance()->Text();

    err = this->Match(TT_RPAR, L")");
    if (err)
        return err;

    SBW_Node *body = this->ParseStatement(false);
    if (body->Type() == NT_BAD)
        return body;
    
    std::vector<SBW_Node*> catch_clauses;
    while (this->Get(1)->Text() == L"catch")
    {
        this->Advance(); // Skip '}'
        SBW_Node *catch_clause = this->ParseCatch();
        if (catch_clause->Type() == NT_BAD)
        {
            ClearNodeList(catch_clauses);
            return catch_clause;
        }

        catch_clauses.push_back(catch_clause);
    }

    return new SBW_NodeTry(line, column, body, name, catch_clauses);
}

SBW_Node *SBW_Parser::ParseCatch(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    SBW_NodeBad *err = this->Match(TT_LPAR, L"(");
    if (err)
        return err;
    
    if (this->Get()->Type() != TT_WORD)
        return this->Match(TT_WORD, L"error type");
    
    std::vector<sbw_string> err_types;
    while (this->Get()->Type() == TT_WORD)
    {
        sbw_string err_type = this->Advance()->Text();
        err_types.push_back(err_type);
        if (this->Get()->Type() == TT_COMMA)
        {
            this->Advance(); // Skip ','
            if (this->Get()->Type() != TT_WORD)
                return this->Match(TT_WORD, L"error type");
        }
    }

    err = this->Match(TT_RPAR, L")");
    if (err)
        return err;
    
    SBW_Node *body = this->ParseStatement(false);
    if (body->Type() == NT_BAD)
        return body;
    
    return new SBW_NodeCatch(line, column, err_types, body);
}

SBW_Node *SBW_Parser::ParseBinaryUnaryExpression(sbw_ubyte parent_precedence)
{
    SBW_Node *left = (SBW_Node*)0;
    sbw_ubyte unary_precedence = GetUnaryPrecedence(this->Get()->Type());
    if (unary_precedence != 0 && unary_precedence >= parent_precedence)
    {
        if (unary_precedence == 2)
        {
            left = this->ParseQuestionOp();
            if (left->Type() == NT_BAD)
                return left;
        }
        else
        {
            sbw_ulong line = this->Get()->Line();
            sbw_ulong column = this->Get()->Column();
            sbw_token_type op_type = this->Advance()->Type();
            SBW_Node *operand = this->ParseBinaryUnaryExpression(unary_precedence);
            if (operand->Type() == NT_BAD)
                return operand;
            
            left = new SBW_NodeUnary(line, column, operand, op_type);
        }
    }
    else
    {
        left = this->ParsePrimaryExpression();
        if (left->Type() == NT_BAD)
            return left;
    }

    while (true)
    {
        sbw_ulong line = this->Get()->Line();
        sbw_ulong column = this->Get()->Column();
        sbw_ubyte binary_precedence = GetBinaryPrecedence(this->Get()->Type());
        if (binary_precedence == 0 || binary_precedence <= parent_precedence)
            break;
        
        sbw_token_type op_type = this->Advance()->Type();
        if (binary_precedence == 17)
            return new SBW_NodeUnary(line, column, left, op_type);
        
        SBW_Node *right = this->ParseBinaryUnaryExpression(binary_precedence);
        if (right->Type() == NT_BAD)
            return right;
        
        left = new SBW_NodeBinary(line, column, left, right, op_type);
    }

    return left;
}

SBW_Node *SBW_Parser::ParsePrimaryExpression(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Get()->Column();
    switch (this->Get()->Type())
    {
        case TT_LPAR: {
            this->Advance(); // Skip '('
            SBW_Node *expression = this->ParseStatement(false);
            if (expression->Type() == NT_BAD)
                return expression;
            
            SBW_NodeBad *err = this->Match(TT_RPAR, L")");
            if (err)
                return err;
            
            return new SBW_NodeParenthesized(line, column, expression);
        }

        case TT_INTEGER: {
            return new SBW_NodeLitteral(line, column, new SBW_ValueUlong(wcstoull(this->Advance()->Text().c_str(), NULL, 10)));
        }

        case TT_DECIMAL: {
            return new SBW_NodeLitteral(line, column, new SBW_ValueLdouble(wcstold(this->Advance()->Text().c_str(), NULL)));
        }

        case TT_CHAR: {
            return new SBW_NodeLitteral(line, column, new SBW_ValueCharacter(this->Advance()->Text()[0]));
        }

        case TT_STRING: {
            return new SBW_NodeLitteral(line, column, new SBW_ValueString(this->Advance()->Text()));
        }

        case TT_BOOLEAN: {
            return new SBW_NodeLitteral(line, column, new SBW_ValueBoolean(this->Advance()->Text() == L"true"));
        }

        case TT_BAD: {
            return new SBW_NodeBad(line, column, new SBW_ValueError(L"SyntaxError", this->Advance()->Text(), line, column));
        }

        default: {
            if (this->Get()->Type() == TT_WORD)
                return this->ParseCall();

            this->Advance();
            return new SBW_NodeBad(line, column, new SBW_ValueError(L"SyntaxError", L"Incorrect statement found", line, column));
        }
    }
}

SBW_Node *SBW_Parser::ParseCall(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Get()->Column();
    sbw_string name = this->Advance()->Text();
    if (this->Get()->Type() == TT_LPAR)
        return this->ParseFunctionCall(line, column, name);
    
    return new SBW_NodeVarCall(line, column, name);
}

SBW_Node *SBW_Parser::ParseFunctionCall(sbw_ulong line, sbw_ulong column, sbw_string name)
{
    this->Advance(); // Skip '('
    std::vector<SBW_Node*> args;
    while (this->Get()->Type() != TT_RPAR && this->Get()->Type() != TT_EOF)
    {
        SBW_Node *arg = this->ParseArgument();
        if (arg->Type() == NT_BAD)
        {
            ClearNodeList(args);
            return arg;
        }

        args.push_back(arg);
        if (this->Get()->Type() == TT_COMMA)
            this->Advance();
    }

    SBW_NodeBad *err = this->Match(TT_RPAR, L")");
    if (err)
    {
        ClearNodeList(args);
        return err;
    }

    return new SBW_NodeFuncCall(line, column, name, args);
}

SBW_Node *SBW_Parser::ParseArgument(sbw_none)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Get()->Column();
    sbw_string name;
    if (this->Get()->Type() == TT_WORD && this->Get(1)->Type() == TT_EQ)
    {
        name = this->Advance()->Text();
        this->Advance(); // Skip '='
    }

    return new SBW_NodeArg(line, column, name, this->ParseStatement(false));
}

SBW_Node *SBW_Parser::ParseIncImp(sbw_bool is_lib)
{
    sbw_ulong line = this->Get()->Line();
    sbw_ulong column = this->Advance()->Column();
    sbw_bool has_par = this->Get()->Type() == TT_LPAR;
    if (!has_par && this->Get()->Text() != L"*")
        return this->Match(TT_LPAR, L"'(' or '*'");
    
    std::vector<sbw_string> elements;
    if (has_par)
    {
        this->Advance(); // Skip '('
        while (this->Get()->Type() != TT_RPAR && this->Get()->Type() != TT_EOF)
        {
            sbw_string elt = this->Get()->Text();
            SBW_NodeBad *err = this->Match(TT_WORD, L"element name");
            if (err)
                return err;
            
            elements.push_back(elt);
            if (this->Get()->Type() == TT_COMMA)
            {
                this->Advance(); // Skip ','
                if (this->Get()->Type() != TT_WORD)
                    return new SBW_NodeBad(this->Get()->Line(), this->Get()->Column(), new SBW_ValueError(L"SyntaxError", L"Expected 'element name'", this->Get()->Line(), this->Get()->Column()));
            }
        }

        SBW_NodeBad *err = this->Match(TT_RPAR, L")");
        if (err)
            return err;
    }
    else
    {
        elements.push_back(L"*");
        this->Advance(); // Skip '*'
    }
    
    if (this->Get()->Type() != TT_WORD || this->Get()->Text() != L"from")
        return this->Match(TT_EOF, L"'from' keyword");
    this->Advance(); // Skip 'from'
    
    if (this->Get()->Type() != TT_WORD)
        return this->Match(TT_WORD, L"library or module name");
    sbw_string name = this->Advance()->Text();

    sbw_string alias;
    if (this->Get()->Type() == TT_AS)
    {
        this->Advance();
        if (this->Get()->Type() != TT_WORD)
            return this->Match(TT_WORD, L"alias name");
        alias = this->Advance()->Text();
    }

    if (is_lib)
        return new SBW_NodeInclude(line, column, name, alias, elements);
    return new SBW_NodeImport(line, column, name, alias, elements);
}