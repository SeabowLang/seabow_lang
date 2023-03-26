#include "token.hpp"

sbw_ubyte GetUnaryPrecedence(sbw_token_type t)
{
    switch (t)
    {
        case TT_DOLLAR:
            return 18;

        case TT_PLUSPLUS:
        case TT_MINUSMINUS:
            return 16; // Should be executed after the function is called

        case TT_NOT:
        case TT_TILDE:
        case TT_PLUS:
        case TT_MINUS:
            return 15;
        
        case TT_QUEST:
            return 2;
        
        default:
            return 0;
    }
}

sbw_ubyte GetBinaryPrecedence(sbw_token_type t)
{
    switch (t)
    {
        case TT_PLUSPLUS:
        case TT_MINUSMINUS:
            return 17;
        
        case TT_POWER:
            return 14;
        
        case TT_STAR:
        case TT_SLASH:
        case TT_PERCENT:
            return 13;
        
        case TT_PLUS:
        case TT_MINUS:
            return 12;
        
        case TT_LSHIFT:
        case TT_RSHIFT:
            return 11;
        
        case TT_IS:
        case TT_IN:
        case TT_AS:
            return 10;
        
        case TT_LESS:
        case TT_LESSEQ:
        case TT_GREAT:
        case TT_GREATEQ:
            return 9;
        
        case TT_EE:
        case TT_NE:
            return 8;
        
        case TT_AMP:
            return 7;
        
        case TT_HAT:
            return 6;
        
        case TT_PIPE:
            return 5;
        
        case TT_AMPAMP:
            return 4;
        
        case TT_PIPEPIPE:
            return 3;
        
        case TT_EQ:
        case TT_PLUSEQ:
        case TT_MINUSEQ:
        case TT_STAREQ:
        case TT_POWEREQ:
        case TT_SLASHEQ:
        case TT_PERCENTEQ:
        case TT_LSHIFTEQ:
        case TT_RSHIFTEQ:
        case TT_PIPEEQ:
        case TT_AMPEQ:
            return 1;
        
        default:
            return 0;
    }
}

SBW_Token::SBW_Token(sbw_token_type t, sbw_string txt, sbw_ulong l, sbw_ulong c)
{
    this->tok_type = t;
    this->text = txt;
    this->line = l;
    this->column = c;
}