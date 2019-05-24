//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTFACTORNODE_H
#define CPS2000_ASTFACTORNODE_H

#include "ASTNode.h"
#include "iostream"

class ASTFactorNode : public ASTNode{
public:
    explicit ASTFactorNode() : ASTNode(){
        setNodeType(5);
    }

    void setData(std::string data){
        this->data = std::move(data);
    }

    void setASTNode(ASTNode* x){
        node_value = x;
    }

    std::string getData(){
        return data;
    }

    ASTNode* getASTNodeValue(){
        return node_value;
    }

private:
    std::string data;
    ASTNode* node_value;
    ~ASTFactorNode() = default;
};

#endif //CPS2000_ASTFACTORNODE_H
