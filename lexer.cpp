//
// Created by seanp on 18/05/2019.
//
#include "lexer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream currentFile;
int currentLinePosition = 0;
int lineNumber = 0;
string currentLine = "";
string currentData = "";

State currentState;
State table[20][16] = {
        //             _ letters,   numbers,     point,angBracket,         =,         !,      {}(),         :,         ;,         ,,        +-,         /,         *,        \n,whitespace,     other
        /*STATE__S0*/ {STATE_APH, STATE_NUM, STATE_ACP, STATE_ANG, STATE_EQL, STATE_EXC, STATE_BRK, STATE_COL, STATE_SEM, STATE_COM, STATE_MTH, STATE_SLA, STATE_MTH, STATE_WHT, STATE_WHT, STATE_ERR},//
        /*STATE_APH*/ {STATE_APH, STATE_APH, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_NUM*/ {STATE_ACP, STATE_NUM, STATE_FLT, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_FLT*/ {STATE_ACP, STATE_FLT, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_ANG*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_EQV, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_EQL*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_EQV, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_EQV*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP},//
        /*STATE_EXC*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_EQV, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
        /*STATE_BRK*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_COL*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_SEM*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_COM*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_MTH*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_SLA*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_CMT, STATE_BLK, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_CMT*/ {STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_ACP, STATE_CMT, STATE_CMT},//
        /*STATE_NLN*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_BLK*/ {STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_STR, STATE_BLK, STATE_BLK, STATE_BLK},//
        /*STATE_STR*/ {STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_END, STATE_STR, STATE_BLK, STATE_BLK, STATE_BLK},//
        /*STATE_END*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ERR},//
        /*STATE_WHT*/ {STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_ACP, STATE_WHT, STATE_ERR}//
};

int fileOpen(const std::string &filePath){
    currentFile.open(filePath);
    if(currentFile.is_open())
        return 0;
    return -1;
}

int getChar(){
    if(currentLinePosition < currentLine.size()){
        char c = currentLine[currentLinePosition];
        currentLinePosition++;
        return c;
    }else{
        currentLinePosition = 0;
        lineNumber++;
        return (getline(currentFile, currentLine) ? getChar() : -1);
    }
}

State getState(int col, State currentState){
    return table[currentState][col];
}

int getColumn(char i) {
    int col;
    if (i == '\n' || i == '\r') {
        col = 13;
    }else if (isspace(i)) {
        col = 14;
    } else if (isdigit(i)) {
        col = 1;
    } else if (i == '.') {
        col = 2;
    } else if (i == '<' || i == '>') {
        col = 3;
    } else if (i == '=') {
        col = 4;
    } else if (i == '!') {
        col = 5;
    } else if (i == '{' || i == '}' || i == '(' || i == ')') {
        col = 6;
    } else if (i == ':') {
        col = 7;
    } else if (i == ';') {
        col = 8;
    } else if (i == ',') {
        col = 9;
    } else if (i == '+' || i == '-') {
        col = 10;
    } else if (i == '/') {
        col = 11;
    } else if (i == '*') {
        col = 12;
    } else if (isalpha(i) || i == '_'){
        col = 0;
    }else{
        col = 15;
    }
    return col;
}

TOKEN *createToken(const std::string &currentString, State state) {
    switch (state) {
        case STATE_APH:
            if(currentString == "float" || currentString == "int" || currentString == "bool") {
                return new TOKEN(TOKEN_TYPE, currentString);
            }else if(currentString == "true" || currentString == "false"){
                return new TOKEN(TOKEN_BOOLEAN_LITERAL, currentString);
            }else if(currentString == "and"){
                return new TOKEN(TOKEN_MULTIPLICATIVE_OP, currentString);
            }else if(currentString == "or"){
                return new TOKEN(TOKEN_ADDITIVE_OP, currentString);
            }else if(currentString == "var"){
                return new TOKEN(TOKEN_VARIABLE_DECL, currentString);
            }else if(currentString == "print"){
                return new TOKEN(TOKEN_PRINT, currentString);
            }else if(currentString == "return"){
                return new TOKEN(TOKEN_RETURN, currentString);
            }else if(currentString == "if"){
                return new TOKEN(TOKEN_IF, currentString);
            }else if(currentString == "else"){
                return new TOKEN(TOKEN_ELSE, currentString);
            }else if(currentString == "for"){
                return new TOKEN(TOKEN_FOR, currentString);
            }else if(currentString == "fn"){
                return new TOKEN(TOKEN_FUNCTION_DECL, currentString);
            }else if(currentString == "not") {
                return new TOKEN(TOKEN_NOT, currentString);
            }else{
                return new TOKEN(TOKEN_ALPHANUMERIC, currentString);
            }
        case STATE_NUM:
            return new TOKEN(TOKEN_INT, currentString);
        case STATE_FLT:
            return new TOKEN(TOKEN_FLOAT, currentString);
        case STATE_ANG:
            return new TOKEN(TOKEN_ANGLE_BRACKET, currentString);
        case STATE_EQL:
            return new TOKEN(TOKEN_EQUAL, currentString);
        case STATE_EQV:
            if(currentString == "=="){
                return new TOKEN(TOKEN_EQUIVELENCE, currentString);
            }else if(currentString == ">="){
                return new TOKEN(TOKEN_GREATER_EQUAL, currentString);
            }else if(currentString == "<="){
                return new TOKEN(TOKEN_LESS_EQUAL, currentString);
            }else if(currentString == "!="){
                return new TOKEN(TOKEN_NOT_EQUAL, currentString);
            }
        case STATE_BRK:
            if(currentString == "("){
                return new TOKEN(TOKEN_OPEN_BRACKET, currentString);
            }else if(currentString == ")"){
                return new TOKEN(TOKEN_CLOSE_BRACKET, currentString);
            }else if(currentString == "{"){
                return new TOKEN(TOKEN_OPEN_CURLY_BRACKET, currentString);
            }else if(currentString == "}"){
                return new TOKEN(TOKEN_CLOSE_CURLY_BRACKET, currentString);
            }
        case STATE_COL:
            return new TOKEN(TOKEN_COLON, currentString);
        case STATE_SEM:
            return new TOKEN(TOKEN_SEMI_COLON, currentString);
        case STATE_COM:
            return new TOKEN(TOKEN_COMMA, currentString);
        case STATE_MTH:
            if(currentString == "*"){
                return new TOKEN(TOKEN_MULTIPLICATIVE_OP, currentString);
            }else{
                return new TOKEN(TOKEN_ADDITIVE_OP, currentString);
            }
        case STATE_SLA:
            return new TOKEN(TOKEN_MULTIPLICATIVE_OP, currentString);
        case STATE_CMT:
            return new TOKEN(TOKEN_COMMENT, currentString);
        case STATE_NLN:
            return new TOKEN(TOKEN_COMMENT, currentString);
        case STATE_BLK:
            return new TOKEN(TOKEN_COMMENT, currentString);
        case STATE_END:
            return new TOKEN(TOKEN_COMMENT, currentString);
        case STATE_WHT:
            return new TOKEN(TOKEN_WHITE_SPACE, currentString);
        default:
            std::cout << "unknown state type: " << state << " data was " << currentData << std::endl;
            return nullptr;

    }
}


std::vector<TOKEN *> processStateChange(State newState, char currentChar) {
    std::vector<TOKEN*> tokens;
    std::vector<TOKEN*> result;
    TOKEN* token;

    switch(newState){
        case STATE_ACP:
            token = createToken(currentData, currentState);
            if(token->getTok() != TOKEN_WHITE_SPACE){
                tokens.push_back(token);
            }
            currentState = STATE__S0;
            currentData = "";
            result = processStateChange(getState(getColumn(currentChar), currentState), currentChar);
            tokens.insert(end(tokens), begin(result), end(result));
            break;
        case STATE_ERR:
            cerr << "unknown data: " << currentData << " on line " << lineNumber << endl;
            exit(-1);
        default:
            currentData += currentChar;
            currentState = newState;
            break;
    }

    return tokens;
}

std::vector<TOKEN*> lexer(const std::string &fileLocation){
    char c;
    State state;
    std::vector<TOKEN*> tokens;
    std::vector<TOKEN*> returnedTokens;
    std::string currentLine;
    currentState = STATE__S0;

    if(fileOpen(fileLocation) == -1){
        std::cout << "The currentFile " << fileLocation << " could not be opened" << std::endl;
        return tokens;
    }else{
        while((c = (char) getChar()) != -1) {
            state = getState(getColumn(c), currentState);
            returnedTokens = processStateChange(state, c);
            tokens.insert(end(tokens), begin(returnedTokens), end(returnedTokens));
        }
        std::cout << "end of currentFile reached" << std::endl;
    }

    return tokens;
}