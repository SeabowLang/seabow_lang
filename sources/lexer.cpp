#include "lexer.hpp"

SBW_Lexer::SBW_Lexer(sbw_string c)
{
    this->code = c;
    this->code_pos = 0;
    this->column = this->line = 1;
    
    this->code_size = 0;
    while (this->code[this->code_size] != L'\0')
        this->code_size++;
}

SBW_Token *SBW_Lexer::Lex(sbw_none)
{
    this->SkipSpaces();
    sbw_char actual = this->Get();

    if (actual == L'/')
    {
        sbw_char next = this->Get(1);
        if (next == '/' || next == '*')
        {
            this->SkipComments();
            return this->Lex();
        }
        else if (next == '=')
            return this->AdvanceWith(L"/=", 2, TT_SLASHEQ);
        return this->AdvanceWith(L"/", 1, TT_SLASH);
    }

    if (iswdigit(actual))
        return this->LexNumber();    

    if (iswalpha(actual) || actual == L'_')
        return this->LexWord();

    if (actual == L'"')
        return this->LexString();
    
    if (actual == L'\'')
        return this->LexCharacter();

    switch (actual)
    {
        case L'(': return this->AdvanceWith(L"(", 1, TT_LPAR);
        case L')': return this->AdvanceWith(L")", 1, TT_RPAR);
        case L'{': return this->AdvanceWith(L"{", 1, TT_LBRACE);
        case L'}': return this->AdvanceWith(L"}", 1, TT_RBRACE);
        case L'[': return this->AdvanceWith(L"[", 1, TT_LBRACKET);
        case L']': return this->AdvanceWith(L"]", 1, TT_RBRACKET);

        case L';': return this->AdvanceWith(L";", 1, TT_SEMI);
        case L',': return this->AdvanceWith(L",", 1, TT_COMMA);
        case L':': return this->AdvanceWith(L":", 1, TT_COLON);
        case L'.': return this->AdvanceWith(L".", 1, TT_DOT);

        case L'?': return this->AdvanceWith(L"?", 1, TT_QUEST);
        case L'$': return this->AdvanceWith(L"$", 1, TT_DOLLAR);
        case L'@': return this->AdvanceWith(L"@", 1, TT_AT);

        case L'=': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L"==", 2, TT_EE);
            return this->AdvanceWith(L"=", 1, TT_EQ);
        }
        case L'!': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L"!=", 2, TT_NE);
            return this->AdvanceWith(L"!", 1, TT_NOT);
        }

        case L'+': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L"+=", 2, TT_PLUSEQ);
            else if (this->Get(1) == L'+')
                return this->AdvanceWith(L"++", 2, TT_PLUSPLUS);
            return this->AdvanceWith(L"+", 1, TT_PLUS);
        }
        case L'-': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L"-=", 2, TT_MINUSEQ);
            else if (this->Get(1) == L'-')
                return this->AdvanceWith(L"--", 2, TT_MINUSMINUS);
            return this->AdvanceWith(L"-", 1, TT_MINUS);
        }

        case L'*': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L"*=", 2, TT_STAREQ);
            else if (this->Get(1) == L'*') {
                if (this->Get(2) == L'=')
                    return this->AdvanceWith(L"**=", 3, TT_POWEREQ);
                return this->AdvanceWith(L"**", 2, TT_POWER);
            }
            return this->AdvanceWith(L"*", 1, TT_STAR);
        }

        case L'%': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L"%=", 2, TT_PERCENTEQ);
            return this->AdvanceWith(L"%", 1, TT_PERCENT);
        }

        case L'<': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L"<=", 2, TT_LESSEQ);
            else if (this->Get(1) == L'<') {
                if (this->Get(2) == L'=')
                    return this->AdvanceWith(L"<<=", 3, TT_LSHIFTEQ);
                return this->AdvanceWith(L"<<", 2, TT_LSHIFT);
            }
            return this->AdvanceWith(L"<", 1, TT_LESS);
        }

        case L'>': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L">=", 2, TT_GREATEQ);
            else if (this->Get(1) == L'>') {
                if (this->Get(2) == L'=')
                    return this->AdvanceWith(L">>=", 3, TT_RSHIFTEQ);
                return this->AdvanceWith(L">>", 2, TT_RSHIFT);
            }
            return this->AdvanceWith(L">", 1, TT_GREAT);
        }

        case L'~': return this->AdvanceWith(L"~", 1, TT_TILDE);
        case L'^': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L"^=", 2, TT_HATEQ);
            return this->AdvanceWith(L"^", 1, TT_HAT);
        }

        case L'&': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L"&=", 2, TT_AMPEQ);
            else if (this->Get(1) == L'&')
                return this->AdvanceWith(L"&&", 2, TT_AMPAMP);
            return this->AdvanceWith(L"&", 1, TT_AMP);
        }
        case L'|': {
            if (this->Get(1) == L'=')
                return this->AdvanceWith(L"|=", 2, TT_PIPEEQ);
            else if (this->Get(1) == L'|')
                return this->AdvanceWith(L"||", 2, TT_PIPEPIPE);
            return this->AdvanceWith(L"|", 1, TT_PIPE);
        }
    }

    if (actual == L'\0')
        return new SBW_Token(TT_EOF, L"", this->line, this->column);

    sbw_string bad_string = L"Unexpected character '"; bad_string += actual; bad_string += L'\'';
    sbw_ulong col = this->column;
    this->Advance();
    return new SBW_Token(TT_BAD, bad_string, this->line, col);
}

sbw_char SBW_Lexer::Get(sbw_none) { return this->code[this->code_pos]; }

sbw_char SBW_Lexer::Get(sbw_long offset)
{
    sbw_ulong pos = this->code_pos + offset;
    if (pos < this->code_size)
        return this->code[pos];
    return L'\0';
}

sbw_none SBW_Lexer::SkipSpaces(sbw_none)
{
    sbw_char c = this->Get();
    while (c == L' ' || c == L'\n' || c == '\r' || c == '\t' || c == '\v')
    {
        if (c == L'\n')
        {
            this->Advance();
            this->column = 1;
            this->line++;
            c = this->Get();
            continue;
        }

        this->Advance();
        c = this->Get();
    }
}

sbw_none SBW_Lexer::SkipComments(sbw_none)
{
    this->Advance();
    if (this->Get() == L'*')
    {
        this->Advance();
        sbw_char c = this->Get();
        while (c != L'\0')
        {
            if (c == L'\n')
            {
                this->Advance();
                this->column = 1;
                this->line++;
                c = this->Get();
                continue;
            }

            if (c == L'*')
            {
                if (this->Get(1) == L'/')
                {
                    this->Advance();
                    this->Advance();
                    return;
                }
            }

            this->Advance();
            c = this->Get();
        }
    }
    else
    {
        while (this->Get() != L'\n' && this->Get() != L'\0')
            this->Advance();
        this->Advance();
        this->column = 1;
        this->line++;
    }
}

SBW_Token *SBW_Lexer::AdvanceWith(sbw_string txt, sbw_ubyte size, sbw_token_type t)
{
    sbw_ulong column = this->column;
    for (sbw_ubyte i=0; i<size; i++)
        this->Advance();
    
    return new SBW_Token(t, txt, this->line, column);
}

SBW_Token *SBW_Lexer::LexNumber(sbw_none)
{
    sbw_ubyte dots = 0, exps = 0;
    sbw_bool want_digit = false;
    sbw_ulong column = this->column;
    sbw_string txt;
    txt += this->Get();
    this->Advance();
    sbw_char c = this->Get();
    while (iswdigit(c) || c == L'.' || c == L'_' || c == L'e' || c == L'E')
    {
        if (c == L'.')
        {
            dots++;
            if (dots > 1)
                return new SBW_Token(TT_BAD, L"Number cannot had more than one '.'", this->line, column);
        }
        else if (c == L'_')
        {
            this->Advance();
            c = this->Get();
            continue;
        }
        else if (c == L'e' || c == L'E')
        {
            exps++;
            if (exps > 1)
                return new SBW_Token(TT_BAD, L"Number cannot had more than one 'E'", this->line, column);
            
            txt += c;
            this->Advance();
            c = this->Get();
            if (c != L'+' && c != L'-')
                return new SBW_Token(TT_BAD, L"Scientist number miss '+' or '-'", this->line, column);
            want_digit = true;
        }
        else if (want_digit)
            want_digit = false;

        txt += c;
        this->Advance();
        c = this->Get();
    }

    if (want_digit)
        return new SBW_Token(TT_BAD, L"Scientist number need at least one digit", this->line, column);

    if (dots || exps)
        return new SBW_Token(TT_DECIMAL, txt, this->line, column);
    return new SBW_Token(TT_INTEGER, txt, this->line, column);
}

SBW_Token *SBW_Lexer::LexCharacter(sbw_none)
{
    sbw_ulong column = this->column;
    this->Advance();
    
    sbw_char cr = this->MakeCharacter();
    this->Advance();
    if (this->Get() != L'\'')
        return new SBW_Token(TT_BAD, L"Unterminated character definition", this->line, column);
    
    this->Advance();
    sbw_string txt; txt += cr;
    return new SBW_Token(TT_CHAR, txt, this->line, column);
}

SBW_Token *SBW_Lexer::LexString(sbw_none)
{
    sbw_ulong column = this->column;
    this->Advance();

    sbw_char c = this->MakeCharacter();
    sbw_string txt;
    while (c != L'"' && c != L'\0')
    {
        if (this->Get() == L'\n')
        {
            this->Advance();
            this->column = 1;
            this->line++;
            txt += c;
            c = this->MakeCharacter();
            continue;
        }

        txt += c;
        this->Advance();
        c = this->MakeCharacter();
    }

    if (c != L'"')
        return new SBW_Token(TT_BAD, L"Unterminated string definition", this->line, column);

    this->Advance();
    return new SBW_Token(TT_STRING, txt, this->line, column);
}

SBW_Token *SBW_Lexer::LexWord(sbw_none)
{
    sbw_ulong cl = this->column;
    sbw_string txt;
    txt += this->Get();
    this->Advance();
    sbw_char c = this->Get();
    while (iswalnum(c) || c == L'_')
    {
        txt += c;
        this->Advance();
        c = this->Get();
    }

    sbw_token_type t = TT_WORD;
    if (txt == L"true" || txt == L"false")
        t = TT_BOOLEAN;
    if (txt == L"in")
        t = TT_IN;
    else if (txt == L"is")
        t = TT_IS;
    else if (txt == L"as")
        t = TT_AS;

    return new SBW_Token(t, txt, this->line, cl);
}

sbw_char SBW_Lexer::MakeCharacter(sbw_none)
{
    sbw_char c = this->Get();
    if (c == L'\\')
    {
        this->Advance();
        c = this->Get();
        switch (c)
        {
            case L'n': return L'\n';
            case L't': return L'\t';
            case L'r': return L'\r';
            case L'b': return L'\b';
            case L'v': return L'\v'; 
            case L'f': return L'\f'; 
            case L'a': return L'\a';
            case L'e': return L'\e';
            case L'0': return L'\0';

            case L'\\': return L'\\';
            case L'\'': return L'\'';
            case L'"': return L'\"';
            case '?': return L'\?';

            case L'x': {
                sbw_string n = L"0x";
                this->Advance();
                sbw_char c = this->Get();
                while (iswdigit(c) || (c >= L'A' && c <= L'F') || (c >= L'a' && c <= L'f'))
                {
                    n += c;
                    this->Advance();
                    c = this->Get();
                }

                return (sbw_char)(wcstoull(n.c_str(), NULL, 16));
            }

            default: return c;
        }
    }

    return c;
}