//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTACTUALPARMASNODE_H
#define CPS2000_ASTACTUALPARMASNODE_H

#include "ASTNode.h"
#include "iostream"

class ASTActualParamsNode : public ASTNode{
public:
    ASTActualParamsNode() : ASTNode(){
        setNodeType(1);
    }

    void addChild(ASTNode* child){
        children.push_back(child);
    }

    std::vector<ASTNode*> getChildren(){
        return children;
    }

private:
    std::vector<ASTNode*> children;
    ~ASTActualParamsNode() = default;
};
#endif //CPS2000_ASTACTUALPARMASNODE_H
