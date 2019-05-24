//
// Created by seanp on 24/05/2019.
//

#ifndef CPS2000_SEMANTICANAYLASISVISITOR_H
#define CPS2000_SEMANTICANAYLASISVISITOR_H

#include "iostream"
#include "vector"
#include "../AST/ASTActualParmasNode.h"
#include "../AST/ASTAssignmentNode.h"
#include "../AST/ASTBlockNode.h"
#include "../AST/ASTExpressionNode.h"
#include "../AST/ASTFactorNode.h"
#include "../AST/ASTFormalParam.h"
#include "../AST/ASTFormalParams.h"
#include "../AST/ASTForStatementNode.h"
#include "../AST/ASTFunctionCallNode.h"
#include "../AST/ASTFunctionDeclNode.h"
#include "../AST/ASTIfStatementNode.h"
#include "../AST/ASTPrintNode.h"
#include "../AST/ASTProgramNode.h"
#include "../AST/ASTReturnNode.h"
#include "../AST/ASTSimpleExpressionNode.h"
#include "../AST/ASTStatmentNode.h"
#include "../AST/ASTSubExpressionNode.h"
#include "../AST/ASTTermNode.h"
#include "../AST/ASTUnaryNode.h"
#include "../AST/ASTVariableNode.h"


struct variable{
public:
    variable(std::string name, std::string type){
        this->name = std::move(name);
        this->type = std::move(type);
    }

    std::string getName(){
        return name;
    }

    std::string getType(){
        return type;
    }

    ~variable() = default;
private:
    std::string name;
    std::string type;
};

struct funcs{
public:
    explicit funcs(std::string name, std::string type){
        this->name = std::move(name);
        this->type = std::move(type);
    }

    std::string getName(){
        return name;
    }

    std::string getType(){
        return type;
    }

    ~funcs() = default;
private:
    std::string name;
    std::string type;
};

struct scope{
public:
    scope() = default;
    ~scope() = default;

    bool checkVar(std::string &name){
        for(variable v : vars){
            if(v.getName() == name){
                return true;
            }
        }
        return false;
    }

    bool checkVarType(std::string &name, std::string &type){
        for(variable v : vars){
            if(v.getName() == name){
                return v.getType() == type;
            }
        }
    }

    bool checkFunctions(std::string &name){
        for(funcs func : fns){
            if(func.getName() == name){
                return true;
            }
        }
        return false;
    }


    void addVar(std::string name, std::string type){
        vars.emplace_back(std::move(name), std::move(type));
    }

    bool checkFunctionType(std::string &name, std::string &type){
        for(funcs func: fns){
            if(func.getName() == name && func.getType() == type){
                return true;
            }
        }
        return false;
    }

    void addFunc(const funcs &f){
        fns.push_back(f);
    }

private:
    std::vector<variable> vars;
    std::vector<funcs> fns;
};
class SemanticAnalysisVisitor : public Visitor {
public:
    SemanticAnalysisVisitor() : Visitor(){
        createScope();
    }

    bool checkScopes(std::string name){
        for(scope* s: scopes){
            if(s->checkVar(name)){
                return true;
            }
        }
        return false;
    }

    bool checkFunction(std::string name){
        for(scope* s :scopes){
            if(s->checkFunctions(name)){
                return true;
            }
        }
        return false;
    }

    bool checkFunctionType(std::string name, std::string type){
        for(scope* s : scopes){
            if(s->checkFunctionType(name, type)){
                return true;
            }
        }
        return false;
    }

    bool checkType(std::string name, std::string type){
        for(scope* s : scopes){
            if(s->checkVarType(name, type)){
                return true;
            }
        }

        return false;
    }

    void addToLatestScope(std::string name, std::string type){
        scopes[scopes.size()]->addVar(name, type);
    }

    void removeLastScope(){
        scopes.erase(scopes.end() - 1, scopes.end());
    }
    ~SemanticAnalysisVisitor() = default;

    void visit(ASTActualParamsNode *node);

    void visit(ASTAssignmentNode *node);

    void visit(ASTBlockNode *node);

    void visit(ASTExpressionNode *node);

    void visit(ASTFactorNode *node);

    void visit(ASTFormalParam *node);

    void visit(ASTFormalParams *node);

    void visit(ASTForStatementNode *node);

    void visit(ASTFunctionCallNode *node);

    void visit(ASTFunctionDeclNode *node);

    void visit(ASTIfStatementNode *node);

    void visit(ASTPrintNode *node);

    void visit(ASTProgramNode *node);

    void visit(ASTReturnNode *node);

    void visit(ASTSimpleExpressionNode *node);

    void visit(ASTStatementNode *node);

    void visit(ASTSubExpressionNode *node);

    void visit(ASTTermNode *node);

    void visit(ASTUnaryNode *node);

    void visit(ASTVariableNode *node);

    void visit(ASTNode *node) override;

    void createScope(){
        scopes.push_back(new scope);
    }

private:
    std::vector<scope*> scopes;
};

#endif //CPS2000_SEMANTICANAYLASISVISITOR_H
