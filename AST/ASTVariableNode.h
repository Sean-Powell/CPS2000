//
// Created by seanp on 21/05/2019.
//

#ifndef CPS2000_ASTVARIABLENODE_H
#define CPS2000_ASTVARIABLENODE_H

#include <string.h>
#include <iostream>
#include "ASTNode.h"

using namespace std;

class ASTVariableNode : public ASTNode{
public:
    ASTVariableNode(string dataType, string name, ASTNode* data) : ASTNode(){
        this->dataType = move(dataType);
        this->name = move(name);
        this->data = data;
        setNodeType(20);
    }

    string getDataType(){
        return dataType;
    }

    string getName(){
        return name;
    }

    ASTNode* getData(){
        return data;
    }

private:
    ~ASTVariableNode() = default;
    ASTNode* data;
    string dataType;
    string name;
};

#endif //CPS2000_ASTVARIABLENODE_H
