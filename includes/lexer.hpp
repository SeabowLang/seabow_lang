#ifndef __SEABOW_LEXER_HPP__
#define __SEABOW_LEXER_HPP__

#include "token.hpp"

class SBW_Lexer
{
public:
    SBW_Lexer(sbw_string c);
    inline virtual ~SBW_Lexer() {}

    SBW_Token *Lex(sbw_none);
private:
    sbw_ulong code_size, code_pos;
    sbw_ulong line, column;
    sbw_string code;

    sbw_none Advance(sbw_none) { if (this->code_pos < this->code_size) { this->code_pos++; this->column++; } }
    sbw_char Get(sbw_none); sbw_char Get(sbw_long offset);
    sbw_none SkipSpaces(sbw_none);
    sbw_none SkipComments(sbw_none);
    SBW_Token *AdvanceWith(sbw_string txt, sbw_ubyte size, sbw_token_type t);

    SBW_Token *LexNumber(sbw_none);
    SBW_Token *LexCharacter(sbw_none);
    SBW_Token *LexString(sbw_none);
    SBW_Token *LexWord(sbw_none);

    sbw_char MakeCharacter(sbw_none);
};

#endif // __SEABOW_LEXER_HPP__