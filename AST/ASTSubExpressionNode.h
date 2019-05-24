//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTSUBEXPRESSIONNODE_H
#define CPS2000_ASTSUBEXPRESSIONNODE_H

#include "ASTNode.h"

class ASTSubExpressionNode : public ASTNode{
public:
    explicit ASTSubExpressionNode(ASTNode* expr) : ASTNode(){
        this->expr = expr;
        setNodeType(17);
    }

    ASTNode* getExpr(){
        return expr;
    }

private:
    ASTNode* expr;
    ~ASTSubExpressionNode() = default;
};
#endif //CPS2000_ASTSUBEXPRESSIONNODE_H
