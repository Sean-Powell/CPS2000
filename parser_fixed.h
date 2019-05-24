//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_PARSER_FIXED_H
#define CPS2000_PARSER_FIXED_H

#include "lexer.h"
#include "AST/ASTNode.h"
#include "AST/ASTVariableNode.h"
#include "AST/ASTReturnNode.h"
#include "AST/ASTFormalParam.h"
#include "AST/ASTFormalParams.h"
#include "AST/ASTForStatementNode.h"
#include "AST/ASTFunctionDeclNode.h"
#include "AST/ASTIfStatementNode.h"
#include "AST/ASTPrintNode.h"
#include "AST/ASTActualParmasNode.h"
#include "AST/ASTUnaryNode.h"
#include "AST/ASTSubExpressionNode.h"
#include "AST/ASTFunctionCallNode.h"
#include "AST/ASTFactorNode.h"
#include "AST/ASTTermNode.h"
#include "AST/ASTSimpleExpressionNode.h"
#include "AST/ASTExpressionNode.h"
#include "AST/ASTAssignmentNode.h"
#include "AST/ASTBlockNode.h"
#include "AST/ASTStatmentNode.h"
#include "AST/ASTProgramNode.h"


ASTExpressionNode* parseExpression();
ASTStatementNode* parseStatement();

TOKEN* getNextToken();
void discardLastToken();
bool isRelationalOp(TOKEN* t);
ASTActualParamsNode* parseActualParams();
ASTUnaryNode* parseUnary();
ASTSubExpressionNode* parseSubExpression();
ASTFunctionCallNode* parseFunctionCall();
ASTFactorNode* parseFactor();
ASTTermNode* parseTerm();
ASTSimpleExpressionNode* parseSimpleExpression();
ASTVariableNode* parseVariableDecl();
ASTAssignmentNode* parseAssignment();
ASTReturnNode* parseReturn();
ASTBlockNode* parseBlock();
ASTFormalParam* parseFormalParam();
ASTFormalParams* parseFormalParams();
ASTForStatementNode* parseForStatement();
ASTFunctionDeclNode* parseFunctionDecl();
ASTIfStatementNode* parseIfStatement();
ASTPrintNode* parsePrint();
ASTProgramNode* parseProgram(vector<TOKEN*> tok);


#endif //CPS2000_PARSER_FIXED_H
