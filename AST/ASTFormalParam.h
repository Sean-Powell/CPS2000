//
// Created by seanp on 23/05/2019.
//

#ifndef CPS2000_ASTFORMALPARAM_H
#define CPS2000_ASTFORMALPARAM_H

#import "ASTNode.h"
#import <iostream>
class ASTFormalParam : public ASTNode{
public:
    ASTFormalParam(std::string name, std::string type) : ASTNode(){
        this->name = std::move(name);
        this->type = std::move(type);
        setNodeType(6);
    }

    std::string getName(){
        return name;
    }

    std::string getType(){
        return type;
    }

private:
    std::string name;
    std::string type;
    ~ASTFormalParam() = default;
};
#endif //CPS2000_ASTFORMALPARAM_H
