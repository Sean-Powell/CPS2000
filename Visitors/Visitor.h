//
// Created by seanp on 24/05/2019.
//

#ifndef CPS2000_VISITOR_H
#define CPS2000_VISITOR_H

#include "iostream"
#include "vector"
#include "../AST/ASTNode.h"
class ASTNode;
class Visitor{
public:
    Visitor() = default;
    ~Visitor() = default;
    virtual void visit(ASTNode* node){

    }
};
#endif //CPS2000_VISITOR_H
