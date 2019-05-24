//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTUNARYNODE_H
#define CPS2000_ASTUNARYNODE_H

#include "ASTNode.h"

class ASTUnaryNode : public ASTNode{
public:
    explicit ASTUnaryNode(ASTNode* expr) : ASTNode(){
        this->expr = expr;
        setNodeType(19);
    }

    ASTNode* getExpr(){
        return expr;
    }

private:
    ASTNode* expr;
    ~ASTUnaryNode() = default;
};
#endif //CPS2000_ASTUNARYNODE_H
