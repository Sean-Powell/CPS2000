//
// Created by seanp on 18/05/2019.
//

#ifndef CPS2000_LEXER_H
#define CPS2000_LEXER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum TOK {
    TOKEN_ALPHANUMERIC,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_TYPE,
    TOKEN_BOOLEAN_LITERAL,
    TOKEN_MULTIPLICATIVE_OP,
    TOKEN_ADDITIVE_OP,
    TOKEN_VARIABLE_DECL,
    TOKEN_PRINT,
    TOKEN_RETURN,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_NOT,
    TOKEN_FUNCTION_DECL,
    TOKEN_ANGLE_BRACKET,
    TOKEN_EQUAL,
    TOKEN_EQUIVELENCE,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_OPEN_CURLY_BRACKET,
    TOKEN_CLOSE_CURLY_BRACKET,
    TOKEN_COMMA,
    TOKEN_SEMI_COLON,
    TOKEN_COLON,
    TOKEN_COMMENT,
    TOKEN_WHITE_SPACE
};

enum State {
    STATE__S0,
    STATE_APH,
    STATE_NUM,
    STATE_FLT,
    STATE_ANG,
    STATE_EQL,
    STATE_EQV,
    STATE_EXC,
    STATE_BRK,
    STATE_COL,
    STATE_SEM,
    STATE_COM,
    STATE_MTH,
    STATE_SLA,
    STATE_CMT,
    STATE_NLN,
    STATE_BLK,
    STATE_STR,
    STATE_END,
    STATE_WHT,
    STATE_ERR,
    STATE_ACP //STATE_ERR - rejects, STATE_ACP - accepts
};

struct TOKEN {
    TOKEN(TOK tok, std::string data) {
        this->tok = tok;
        this->data = move(data);
    }

    std::string getData() {
        return data;
    }

    TOK getTok() {
        return tok;
    }

private:
    TOK tok;
    std::string data;
};
using namespace std;

int fileOpen(const std::string &filePath);
int getChar();
State getState(int col, State currentState);
int getColumn(char i);
TOKEN *createToken(const std::string &currentString, State state);
std::vector<TOKEN *> processStateChange(State newState, char currentChar);
std::vector<TOKEN*> lexer(const std::string &fileLocation);

#endif //CPS2000_LEXER_H
