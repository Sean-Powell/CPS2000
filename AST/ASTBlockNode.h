//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTBLOCKNODE_H
#define CPS2000_ASTBLOCKNODE_H

#include "ASTNode.h"
#include "iostream"
#include "vector"

class ASTBlockNode : public ASTNode{
public:
    ASTBlockNode() : ASTNode() {
        setNodeType(3);
    }

    void addChild(ASTNode* child){
        children.push_back(child);
    }

    std::vector<ASTNode*> getChildren(){
        return children;
    }

private:
    std::vector<ASTNode*> children;
    ~ASTBlockNode() = default;
};
#endif //CPS2000_ASTBLOCKNODE_H
