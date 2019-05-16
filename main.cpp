#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum TOK{
    TOKEN_LETTER, TOKEN_DIGIT, TOKEN_EOL, TOKEN_EQUALSIGN, TOKEN_UNDERSCORE, TOKEN_WHITESPACE,
    TOKEN_LESSTHAN, TOKEN_GREATERTHAN, TOKEN_EXCLIMATION, TOKEN_LEFT_BRACKET, TOKEN_RIGHT_BRACKET, TOKEN_CURLY_OPEN,
    TOKEN_CURLY_CLOSED, TOKEN_SEMICOLON, TOK_PERIOD, TOKEN_COMMA, TOKEN_MULTI, TOKEN_DIVISION, TOKEN_ADD, TOKEN_MINUS,
    TOKEN_NOT, TOKEN_LINE_COMMENT, TOKEN_BLOCK_COMMENT, TOKEN_NOT_EQUAL, TOKEN_LESS_THAN, TOKEN_GREATER_THAN, TOKEN_EQUAL,
    TOKEN_LITERAL_INTERGER, TOKEN_TYPE, TOKEN_VARIABLE_DECLERATION, TOKEN_PRINT, TOKEN_RETURN, TOKEN_IF, TOKEN_FOR,
    TOKEN_ELSE, TOKEN_ELSE_IF, TOKEN_FUNCTION_DECLERATION, TOKEN_ID, TOKEN_LITERAL_BOOLEAN, TOKEN_LITERAL_FLOAT,
    TOKEN_AND, TOKEN_OR, TOKEN_EOF, TOKEN_LEX_ERROR, TOKEN_INVALID, TOKEN_ERROR
};

enum State{
    STATE__S0, STATE_APH, STATE_NUM, STATE_FLT, STATE_ANG, STATE_EXC, STATE_EQL, STATE_BRK, STATE_COL, STATE_SEM, STATE_COM,
    STATE_MTH, STATE_SLA, STATE_CMT, STATE_NLN, STATE_BLK, STATE_STR, STATE_END, STATE_ERR
};

State table[18][15] = {
    //             _ letters,   numbers,     point,angBracket,         =,         !,      {}(),         :,         ;,         ,,        +-,         /,         *,        \n,     other
    /*STATE__S0*/ {STATE_APH, STATE_NUM, STATE_ERR, STATE_ANG, STATE_EQL, STATE_EXC, STATE_BRK, STATE_COL, STATE_SEM, STATE_COM, STATE_MTH, STATE_SLA, STATE_MTH, STATE_ERR, STATE_ERR},//
    /*STATE_APH*/ {STATE_APH, STATE_APH, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_NUM*/ {STATE_ERR, STATE_NUM, STATE_FLT, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_FLT*/ {STATE_ERR, STATE_FLT, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_ANG*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_EQL, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_EXC*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_EQL, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_EQL*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_BRK*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_COL*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_SEM*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_COM*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_MTH*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_SLA*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_CMT, STATE_BLK, STATE_ERR, STATE_ERR},//
    /*STATE_CMT*/ {STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_CMT, STATE_NLN, STATE_ERR},//
    /*STATE_NLN*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
    /*STATE_BLK*/ {STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_STR, STATE_BLK, STATE_ERR},//
    /*STATE_STR*/ {STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_BLK, STATE_END, STATE_STR, STATE_BLK, STATE_ERR},//
    /*STATE_END*/ {STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},//
};


struct TOKEN{
    TOKEN(TOK tok, string data){
        this->tok = tok;
        this->data = move(data);
    }

    string getData(){
        return data;
    }

    TOK getTok(){
        return tok;
    }

private:
    TOK tok;
    string data;
};

//takes in a file line and adds spaces before or after a bracket
//string lineSpaces(string line){
//    for(unsigned long i = 0; i < line.length() - 1; i++){
//        char currentChar = line[i];
//        char nextChar = line[i + 1];
//        if(currentChar != ' ' && (nextChar == '(' || nextChar == ')' || nextChar == '{' || nextChar == '}' || nextChar == ';')){
//            line.insert(i + 1, " ");
//        }
//    }
//
//    return line;
//}

//vector<string> splitLine(string line, const string &delimiter){
//    size_t pos = 0;
//    string token;
//    vector<string> tokens;
//
//    while((pos = line.find(delimiter)) != string::npos){
//        token = line.substr(0, pos);
//        tokens.push_back(token);
//        line.erase(0, pos + delimiter.length());
//    }
//
//    return tokens;
//}

vector<TOKEN> tokeniseFile(const string &filePath){
    ifstream file;
    file.open(filePath);
    string line;

    vector<TOKEN*> token_file;
    vector<string> line_split;
    TOKEN* tok;
    string temp;

    State currentState = STATE__S0;
    State nextState;
    int col = 0;
    int counter = 0;
    char currentChar;
    if(file.is_open()){
        while(getline(file, line)){
            for (char i : line) {
                currentChar = i;
                if(isalpha(currentChar)){
                    col = 0;
                }else if(isdigit(currentChar)){
                    col = 1;
                }else if(currentChar == '.'){
                    col = 2;
                }else if(currentChar == '<' || currentChar == '>'){
                    col = 3;
                }else if(currentChar == '='){
                    col = 4;
                }else if(currentChar == '!'){
                    col = 5;
                }else if(currentChar == '{' || currentChar == '}' || currentChar == '(' || currentChar == ')'){
                    col = 6;
                }else if(currentChar == ':'){
                    col = 7;
                }else if(currentChar == ';'){
                    col = 8;
                }else if(currentChar == ','){
                    col = 9;
                }else if(currentChar == '+' || currentChar == '-'){
                    col = 10;
                }else if(currentChar == '/'){
                    col = 11;
                }else if(currentChar == '*'){
                    col = 12;
                }else if(currentChar == '\n'){
                    col = 13;
                }else{
                    col = 14;
                }

                nextState = table[currentState][col];
                counter++;
                cout << counter << ": " <<  nextState << endl;
            }
        }
    }
}



int main() {
    tokeniseFile(R"(C:\Users\seanp\CLionProjects\CPS2000\Code.txt)");
    return 0;
}




