#ifndef __SEABOW_TOKEN_HPP__
#define __SEABOW_TOKEN_HPP__

#include "base.hpp"

enum sbw_token_type: sbw_ubyte {
    TT_BAD = 0xff, TT_EOF = 0xfe,

    TT_IN = 0xfd, TT_IS = 0xfc, TT_AS = 0xfb,

    TT_WORD = 0x00, TT_CHAR = 0x01, TT_STRING = 0x02, TT_INTEGER = 0x03, TT_DECIMAL = 0x04, TT_BOOLEAN = 0x05,

    TT_LPAR = 0x10, TT_RPAR = 0x11, TT_LBRACE = 0x12, TT_RBRACE = 0x13, TT_LBRACKET = 0x14, TT_RBRACKET = 0x15, 
    TT_SEMI = 0x16, TT_COMMA = 0x17, TT_COLON = 0x18, TT_DOT = 0x19, 
    TT_QUEST = 0x1a, TT_DOLLAR = 0x1b, TT_AT = 0x1c,

    TT_EQ = 0x30, TT_EE = 0x31, TT_NOT = 0x32, TT_NE = 0x33,
    TT_PLUS = 0x34, TT_PLUSEQ = 0x35, TT_PLUSPLUS = 0x36, TT_MINUS = 0x37, TT_MINUSEQ = 0x38, TT_MINUSMINUS = 0x39,
    TT_STAR = 0x3a, TT_STAREQ = 0x3b, TT_POWER = 0x3c, TT_POWEREQ = 0x3d, TT_SLASH = 0x3e, TT_SLASHEQ = 0x3f, TT_PERCENT = 0x40, TT_PERCENTEQ = 0x41,
    TT_LESS = 0x42, TT_LESSEQ = 0x43, TT_LSHIFT = 0x44, TT_LSHIFTEQ = 0x45,
    TT_GREAT = 0x46, TT_GREATEQ = 0x47, TT_RSHIFT = 0x48, TT_RSHIFTEQ = 0x49,
    TT_TILDE = 0x4a, TT_HAT = 0x4b, TT_HATEQ = 0x4c,
    TT_AMP = 0x4d, TT_AMPEQ = 0x4e, TT_AMPAMP = 0x4f, TT_PIPE = 0x50, TT_PIPEEQ = 0x51, TT_PIPEPIPE = 0x52
};
sbw_ubyte GetUnaryPrecedence(sbw_token_type t);
sbw_ubyte GetBinaryPrecedence(sbw_token_type t);

class SBW_Token 
{
public:
    SBW_Token(sbw_token_type t, sbw_string txt, sbw_ulong l, sbw_ulong c);
    inline virtual ~SBW_Token() {}

    inline sbw_token_type Type(sbw_none) const { return this->tok_type; }
    inline sbw_string Text(sbw_none) const { return this->text; }
    inline sbw_ulong Line(sbw_none) const { return this->line; }
    inline sbw_ulong Column(sbw_none) const { return this->column; }

private:
    sbw_token_type tok_type;
    sbw_string text;
    sbw_ulong line, column; 
};

#endif // __SEABOW_TOKEN_HPP__