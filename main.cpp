#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "lexer.h"
#include "parser_fixed.h"


int main() {
    std::vector<TOKEN*> tokenized = lexer(R"(C:\Users\seanp\CLionProjects\CPS2000\Code.txt)");
    ASTProgramNode* AST = parseProgram(tokenized);
    return 0;
}




