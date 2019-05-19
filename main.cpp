#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lexer.h"

int main() {
    std::vector<TOKEN*> tokenized = lexer(R"(C:\Users\seanp\CLionProjects\CPS2000\Code.txt)");
    return 0;
}




