//
// Created by seanp on 21/05/2019.
//

#ifndef CPS2000_ASTNODE_H
#define CPS2000_ASTNODE_H

class ASTNode{
public:
    void setNodeType(int nodeType){
        this->nodeType = nodeType;
    }

    int getLineNumber(){
        return nodeType;
    }

    ~ASTNode() = default;

private:
    int nodeType;
};

#endif //CPS2000_ASTNODE_H
