//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTRETURNNODE_H
#define CPS2000_ASTRETURNNODE_H

#include "ASTNode.h"
class ASTReturnNode : public ASTNode{
public:
    explicit ASTReturnNode(ASTNode* toReturn) : ASTNode(){
        this->toReturn = toReturn;
        setNodeType(14);
    }

    ASTNode* getToReturn(){
        return toReturn;
    }

private:
    ~ASTReturnNode() = default;
    ASTNode* toReturn;
};


#endif //CPS2000_ASTRETURNNODE_H
