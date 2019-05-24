//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTFUNCTIONDECLNODE_H
#define CPS2000_ASTFUNCTIONDECLNODE_H

#include "ASTNode.h"
#include "iostream"

class ASTFunctionDeclNode : public ASTNode{
public:
    ASTFunctionDeclNode(std::string name, ASTNode* params, std::string type, ASTNode* body) : ASTNode() {
        this->name = std::move(name);
        this->params = params;
        this->type = std::move(type);
        this->body = body;
        setNodeType(10);
    }

    std::string getName(){
        return name;
    }

    ASTNode* getParams(){
        return params;
    }

    std::string getType(){
        return type;
    }

    ASTNode* getBody(){
        return body;
    }

private:
    ~ASTFunctionDeclNode() = default;
    std::string name;
    ASTNode* params;
    std::string type;
    ASTNode* body;
};
#endif //CPS2000_ASTFUNCTIONDECLNODE_H
