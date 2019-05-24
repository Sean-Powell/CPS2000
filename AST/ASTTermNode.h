//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTTERMNODE_H
#define CPS2000_ASTTERMNODE_H

#include "ASTNode.h"
#include <iostream>


class ASTTermNode : public ASTNode{
public:
    ASTTermNode(ASTFactorNode* left, ASTNode* right, std::string op) : ASTNode(){
        this->right = right;
        this->left = left;
        this->op = std::move(op);
        setNodeType(18);
    }

    std::string getOp(){
        return op;
    }

    ASTNode* getLeftNode(){
        return left;
    }

    ASTNode* getRightNode(){
        return right;
    }

private:
    std::string op;
    ASTNode* left;
    ASTNode* right;
    ~ASTTermNode() = default;
};

#endif //CPS2000_ASTTERMNODE_H
