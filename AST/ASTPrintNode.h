//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTPRINTNODE_H
#define CPS2000_ASTPRINTNODE_H


#include "ASTNode.h"

class ASTPrintNode : public ASTNode{
public:
    explicit ASTPrintNode(ASTNode* toPrint) : ASTNode(){
        this->toPrint = toPrint;
        setNodeType(12);
    }

    ASTNode* getToPrint(){
        return toPrint;
    }

private:
    ~ASTPrintNode() = default;
    ASTNode* toPrint;
};
#endif //CPS2000_ASTPRINTNODE_H
