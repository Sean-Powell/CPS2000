//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTPROGRAMNODE_H
#define CPS2000_ASTPROGRAMNODE_H

#include "ASTNode.h"
#include "ASTStatmentNode.h"
#include "iostream"
#include "vector"
class ASTProgramNode : public ASTNode{
public:
    ASTProgramNode():ASTNode(){
        setNodeType(13);
    }

    std::vector<ASTStatementNode*> getChildren(){
        return children;
    }

    void addChild(ASTStatementNode* child){
        children.push_back(child);
    }

private:
    std::vector<ASTStatementNode*> children;
    ~ASTProgramNode() = default;
};
#endif //CPS2000_ASTPROGRAMNODE_H
