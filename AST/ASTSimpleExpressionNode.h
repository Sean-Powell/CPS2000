//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTSIMPLEEXPRESSIONNODE_H
#define CPS2000_ASTSIMPLEEXPRESSIONNODE_H

#include "ASTNode.h"
#include "iostream"

class ASTSimpleExpressionNode : public ASTNode{
public:
    ASTSimpleExpressionNode(ASTNode* left, ASTNode* right, std::string op): ASTNode(){
        this->left = left;
        this->right = right;
        this->op = std::move(op);
        setNodeType(15);
    }

    std::string getOp(){
        return op;
    }

    ASTNode* getLeft(){
        return left;
    }

    ASTNode* getRight(){
        return right;
    }

private:
    ASTNode* left;
    ASTNode* right;
    std::string op;
    ~ASTSimpleExpressionNode() = default;
};

#endif //CPS2000_ASTSIMPLEEXPRESSIONNODE_H
