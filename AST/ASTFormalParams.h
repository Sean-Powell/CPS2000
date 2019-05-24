//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTFORMALPARAMS_H
#define CPS2000_ASTFORMALPARAMS_H

#include "ASTNode.h"
#include <iostream>
#include <vector>

class ASTFormalParams : public ASTNode{
public:
    ASTFormalParams() : ASTNode(){
        setNodeType(7);
    }

    void addChild(ASTNode* child){
        children.push_back(child);
    }

    std::vector<ASTNode*> getChildren(){
        return children;
    }

private:
    std::vector<ASTNode*> children;
    ~ASTFormalParams() = default;
};
#endif //CPS2000_ASTFORMALPARAMS_H
