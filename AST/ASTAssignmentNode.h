//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTASSIGNMENTNODE_H
#define CPS2000_ASTASSIGNMENTNODE_H

#include "ASTNode.h"
#include "iostream"

class ASTAssignmentNode : public ASTNode{
public:
    ASTAssignmentNode(std::string name, ASTNode* assigned): ASTNode(){
        this->name = std::move(name);
        this->assigned = assigned;
        setNodeType(2);
    }

    ASTNode* getAssigned(){
        return assigned;
    }

    std::string getName(){
        return name;
    }


private:
    ASTNode* assigned;
    std::string name;
    ~ASTAssignmentNode() = default;
};

#endif //CPS2000_ASTASSIGNMENTNODE_H
