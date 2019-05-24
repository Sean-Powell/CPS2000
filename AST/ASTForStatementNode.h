//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTFORSTATEMENTNODE_H
#define CPS2000_ASTFORSTATEMENTNODE_H


#include "ASTNode.h"
#include <iostream>

class ASTForStatementNode : public ASTNode{
public:
    ASTForStatementNode(ASTNode* init, ASTNode* cond, ASTNode* expr, ASTNode* body) : ASTNode(){
        this->init = init;
        this->cond = cond;
        this->expr = expr;
        this->body = body;
        setNodeType(8);
    }

    ASTNode* getInit(){
        return init;
    }

    ASTNode* getCond(){
        return cond;
    }

    ASTNode* getExpr(){
        return expr;
    }

    ASTNode* getBody(){
        return body;
    }

private:
    ~ASTForStatementNode() = default;
    ASTNode* init;
    ASTNode* cond;
    ASTNode* expr;
    ASTNode* body;
};
#endif //CPS2000_ASTFORSTATEMENTNODE_H
