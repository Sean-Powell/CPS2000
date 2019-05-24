//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTIFSTATEMENTNODE_H
#define CPS2000_ASTIFSTATEMENTNODE_H


#include "ASTNode.h"

class ASTIfStatementNode : public ASTNode{
public:
    ASTIfStatementNode(ASTNode* cond, ASTNode* ifBody, ASTNode* elseBody) : ASTNode(){
        this->cond = cond;
        this->ifBody = ifBody;
        this->elseBody = elseBody;
        setNodeType(11);
    }

    ASTNode* getCond(){
        return cond;
    }

    ASTNode* getIfBody(){
        return ifBody;
    }

    ASTNode* getElseBody(){
        return elseBody;
    }

private:
    ASTNode* cond;
    ASTNode* ifBody;
    ASTNode* elseBody;
    ~ASTIfStatementNode() = default;
};
#endif //CPS2000_ASTIFSTATEMENTNODE_H
