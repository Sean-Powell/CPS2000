//
// Created by seanp on 21/05/2019.
//

#ifndef CPS2000_ASTNODE_H
#define CPS2000_ASTNODE_H

#include "../Visitors/Visitor.h"
class Visitor;
class ASTNode{
public:
    void setNodeType(int nodeType){
        this->nodeType = nodeType;
    }

    int getNodeType(){
        return nodeType;
    }

    ~ASTNode() = default;

    virtual void accept(Visitor* visitor){
        visitor->visit(this);
    }
private:
    int nodeType;
};

#endif //CPS2000_ASTNODE_H
