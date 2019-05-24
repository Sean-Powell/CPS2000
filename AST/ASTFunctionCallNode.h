//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTFUNCTIONCALLNODE_H
#define CPS2000_ASTFUNCTIONCALLNODE_H

#include "ASTNode.h"
#include "iostream"

class ASTFunctionCallNode : public ASTNode{
public:
    ASTFunctionCallNode(std::string name, ASTNode* params) : ASTNode(){
        this->name = std::move(name);
        this->params = params;
        setNodeType(9);
    }

    std::string getName(){
        return name;
    }

    ASTNode* getParams(){
        return params;
    }

private:
    ASTNode* params;
    std::string name;
    ~ASTFunctionCallNode() = default;
};
#endif //CPS2000_ASTFUNCTIONCALLNODE_H
