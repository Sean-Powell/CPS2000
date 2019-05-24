//
// Created by seanp on 21/05/2019.
//

#ifndef CPS2000_ASTEXPRESSIONNODE_H
#define CPS2000_ASTEXPRESSIONNODE_H

#include "ASTNode.h"
#include "iostream"
class ASTExpressionNode : public ASTNode{
public:
    ASTExpressionNode(ASTNode* left, ASTNode* right, std::string relationalOP) : ASTNode(){
        this->left = left;
        this->right = right;
        this->relationalOp = std::move(relationalOP);
        setNodeType(4);
    }

    ASTNode* getLeft(){
        return left;
    }

    ASTNode* getRight(){
        return right;
    }

    std::string getRelationalOp(){
        return relationalOp;
    }

private:
    std::string relationalOp;
    ASTNode* left;
    ASTNode* right;
    ~ASTExpressionNode() = default;
};
#endif //CPS2000_ASTEXPRESSIONNODE_H
