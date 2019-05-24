cmake_minimum_required(VERSION 3.13)
project(CPS2000)

set(CMAKE_CXX_STANDARD 11)

add_executable(CPS2000 main.cpp lexer.cpp AST/ASTNode.h AST/ASTExpressionNode.h AST/ASTVariableNode.h AST/ASTReturnNode.h AST/ASTPrintNode.h AST/ASTFormalParam.h AST/ASTFormalParams.h AST/ASTForStatementNode.h AST/ASTFunctionDeclNode.h AST/ASTIfStatementNode.h AST/ASTActualParmasNode.h AST/ASTUnaryNode.h AST/ASTSubExpressionNode.h AST/ASTFunctionCallNode.h AST/ASTFactorNode.h AST/ASTTermNode.h AST/ASTSimpleExpressionNode.h AST/ASTAssignmentNode.h AST/ASTBlockNode.h AST/ASTStatmentNode.h AST/ASTProgramNode.h parser_fixed.cpp parser_fixed.h Visitor.cpp Visitor.h)