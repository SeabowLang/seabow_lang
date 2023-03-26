#ifndef __SEABOW_PARSER_HPP__
#define __SEABOW_PARSER_HPP__

#include "nodes/node_convert.hpp"

sbw_none ClearNodeList(std::vector<SBW_Node*> nodes);

class SBW_Parser
{
public:
    SBW_Parser(sbw_string code);
    virtual ~SBW_Parser();

    SBW_Node *Parse(sbw_none);
private:
    std::vector<SBW_Token*> tokens;
    sbw_ulong pos, size;

    SBW_Token *Advance(sbw_none);
    SBW_Token *Get(sbw_none); SBW_Token *Get(sbw_long offset);
    SBW_NodeBad *Match(sbw_token_type tt, sbw_string t_txt);

    SBW_Node *ParseStatement(sbw_bool is_stat);
    SBW_Node *ParseCompound(sbw_none);

    SBW_Node *ParseDeclaration(sbw_none);
    SBW_Node *ParseFunctionDeclaration(sbw_ulong line, sbw_ulong column, sbw_value_type decl_type, sbw_string name);
    SBW_Node *ParseVariableDeclaration(sbw_ulong line, sbw_ulong column, sbw_value_type decl_type, sbw_string name);

    SBW_Node *ParseParameter(sbw_none);
    SBW_Node *ParseReturn(sbw_none);
    SBW_Node *ParseConvertExpression(sbw_none);

    SBW_Node *ParseIf(sbw_none);
    SBW_Node *ParseElif(sbw_none);

    SBW_Node *ParseSwitch(sbw_none);
    SBW_Node *ParseCase(sbw_none);

    SBW_Node *ParseQuestionOp(sbw_none);

    SBW_Node *ParseFor(sbw_none);
    SBW_Node *ParseForeach(sbw_none);

    SBW_Node *ParseWhile(sbw_none);
    SBW_Node *ParseDowhile(sbw_none);

    SBW_Node *ParseTry(sbw_none);
    SBW_Node *ParseCatch(sbw_none);

    SBW_Node *ParseBinaryUnaryExpression(sbw_ubyte parent_precedence);
    SBW_Node *ParsePrimaryExpression(sbw_none);

    SBW_Node *ParseCall(sbw_none);
    SBW_Node *ParseFunctionCall(sbw_ulong line, sbw_ulong column, sbw_string name);
    SBW_Node *ParseArgument(sbw_none);

    SBW_Node *ParseIncImp(sbw_bool is_lib);
};

#endif // __SEABOW_PARSER_HPP__