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
string lineSpaces(string line){
    for(unsigned long i = 0; i < line.length() - 1; i++){
        char currentChar = line[i];
        char nextChar = line[i + 1];
        if(currentChar != ' ' && (nextChar == '(' || nextChar == ')' || nextChar == '{' || nextChar == '}' || nextChar == ';')){
            line.insert(i + 1, " ");
        }
    }

    return line;
}

vector<string> splitLine(string line, const string &delimiter){
    size_t pos = 0;
    string token;
    vector<string> tokens;

    while((pos = line.find(delimiter)) != string::npos){
        token = line.substr(0, pos);
        tokens.push_back(token);
        line.erase(0, pos + delimiter.length());
    }

    return tokens;
}

vector<TOKEN> tokeniseFile(const string &filePath){
    ifstream file;
    file.open(filePath);
    string line;

    vector<TOKEN*> token_file;
    vector<string> line_split;
    TOKEN* tok;
    string temp;

    if(file.is_open()){
        while(getline(file, line)){
            line = lineSpaces(line);
            line_split = splitLine(line, " ");
            for(int i = 0; i < line_split.size(); i++){
                temp = line_split[i];
                if(temp == "if"){
                    tok = new TOKEN(TOKEN_IF, "if");
                    token_file.push_back(tok);
                }else if(temp == "("){
                    tok = new TOKEN(TOKEN_LEFT_BRACKET, "(");
                    token_file.push_back(tok);
                }else if(temp == ")"){
                    tok = new TOKEN(TOKEN_RIGHT_BRACKET, ")");
                    token_file.push_back(tok);
                }
            }
        }
    }
}



int main() {
    string line = "testing( 123);";
    line = lineSpaces(line);
    cout << line << endl;
    return 0;
}




