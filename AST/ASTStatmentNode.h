//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTSTATMENTNODE_H
#define CPS2000_ASTSTATMENTNODE_H

#include "ASTNode.h"

class ASTStatementNode : public ASTNode{
public:
    explicit ASTStatementNode(ASTNode* node): ASTNode(){
        this->node = node;
        setNodeType(16);
    }

    ASTNode* getNode(){
        return node;
    }

private:
    ASTNode* node;
    ~ASTStatementNode() = default;
};

#endif //CPS2000_ASTSTATMENTNODE_H
