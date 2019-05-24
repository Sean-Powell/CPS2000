//
// Created by seanp on 24/05/2019.
//

#include "SemanticAnalysisVisitor.h"

void SemanticAnalysisVisitor::visit(ASTActualParamsNode* node){
    auto children = node->getChildren();
    for(ASTNode* child: children){
        child->accept(this);
    }
}

void SemanticAnalysisVisitor::visit(ASTAssignmentNode* node){
    std::string name = node->getName();
    if(!checkScopes(name)){
        cerr << "Variable " << name << " does note exist in the current scope" << endl;
    }
}

void SemanticAnalysisVisitor::visit(ASTBlockNode* node){
    createScope();
    auto children = node->getChildren();
    for(auto child: children){
        child->accept(this);
    }
    removeLastScope();
}

void SemanticAnalysisVisitor::visit(ASTExpressionNode* node){
    //check if both side are of the same type
}

void SemanticAnalysisVisitor::visit(ASTFactorNode *node){}

void SemanticAnalysisVisitor::visit(ASTFormalParam *node){}

void SemanticAnalysisVisitor::visit(ASTFormalParams* node){}

void SemanticAnalysisVisitor::visit(ASTForStatementNode*node){
    //check if init and condition are valid types
}

void SemanticAnalysisVisitor::visit(ASTFunctionCallNode* node){
    std::string name = node->getName();
    checkFunction(name);
    auto params = node->getParams();
    params->accept(this);
}

void SemanticAnalysisVisitor::visit(ASTFunctionDeclNode* node){
    std::string name = node->getName();
    std::string type = node->getType();

    if(checkFunction(name) && checkFunctionType(name, type)){
       cerr << "A function with " << name << " already exists within the scope";
    }
    auto body =node->getBody();
    body->accept(this);
}

void SemanticAnalysisVisitor::visit(ASTIfStatementNode* node){

}

void SemanticAnalysisVisitor::visit(ASTPrintNode* node){

}

void SemanticAnalysisVisitor::visit(ASTProgramNode* node){

}

void SemanticAnalysisVisitor::visit(ASTReturnNode* node){

}
void SemanticAnalysisVisitor::visit(ASTSimpleExpressionNode* node){

}

void SemanticAnalysisVisitor::visit(ASTStatementNode* node){

}

void SemanticAnalysisVisitor::visit(ASTSubExpressionNode* node){

}

void SemanticAnalysisVisitor::visit(ASTTermNode* node){

}

void SemanticAnalysisVisitor::visit(ASTUnaryNode* node){

}

void SemanticAnalysisVisitor::visit(ASTVariableNode* node){

}

void SemanticAnalysisVisitor::visit(ASTNode* node){
    switch (node->getNodeType()){
        case 1:
            visit(reinterpret_cast<ASTActualParamsNode*>(node));
            break;
        case 2:
            visit(reinterpret_cast<ASTAssignmentNode*> (node));
            break;
        case 3:
            visit(reinterpret_cast<ASTBlockNode*>(node));
            break;
        case 4:
            visit(reinterpret_cast<ASTExpressionNode*>(node));
            break;
        case 5:
            visit(reinterpret_cast<ASTFactorNode*>(node));
            break;
        case 6:
            visit(reinterpret_cast<ASTFormalParam*>(node));
            break;
        case 7:
            visit(reinterpret_cast<ASTFormalParams*>(node));
            break;
        case 8:
            visit(reinterpret_cast<ASTForStatementNode*>(node));
            break;
        case 9:
            visit(reinterpret_cast<ASTFunctionCallNode*>(node));
            break;
        case 10:
            visit(reinterpret_cast<ASTFunctionDeclNode*>(node));
            break;
        case 11:
            visit(reinterpret_cast<ASTIfStatementNode*>(node));
            break;
        case 12:
            visit(reinterpret_cast<ASTPrintNode*>(node));
            break;
        case 13:
            visit(reinterpret_cast<ASTProgramNode*>(node));
            break;
        case 14:
            visit(reinterpret_cast<ASTReturnNode*>(node));
            break;
        case 15:
            visit(reinterpret_cast<ASTSimpleExpressionNode*>(node));
            break;
        case 16:
            visit(reinterpret_cast<ASTStatementNode*>(node));
            break;
        case 17:
            visit(reinterpret_cast<ASTSubExpressionNode*>(node));
            break;
        case 18:
            visit(reinterpret_cast<ASTTermNode*>(node));
            break;
        case 19:
            visit(reinterpret_cast<ASTUnaryNode*>(node));
            break;
        case 20:
            visit(reinterpret_cast<ASTVariableNode*>(node));
            break;
        default:
            cerr << "unknown AST node type" << endl;

    }
}

