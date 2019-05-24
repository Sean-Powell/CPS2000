//
// Created by seanp on 23/05/2019.
//

#include "parser_fixed.h"

vector<TOKEN *> tokens;
int currentToken = 0;
int previousTokenPosition = 0;

TOKEN *getNextToken() {
    TOKEN *token = tokens[currentToken];
    currentToken++;
    return token;
}

bool isTokensAvailable(int amount) {
    return currentToken + amount <= tokens.size();
}

bool isRelationalOp(TOKEN *t) {
    TOK tok = t->getTok();
    return tok == TOKEN_ANGLE_BRACKET || tok == TOKEN_EQUIVELENCE || tok == TOKEN_NOT_EQUAL
           || tok == TOKEN_GREATER_EQUAL || tok == TOKEN_LESS_EQUAL;
}

ASTActualParamsNode *parseActualParams() {
    previousTokenPosition = currentToken;
    auto node = new ASTActualParamsNode();
    auto child = parseExpression();
    node->addChild(child);
    if (isTokensAvailable(1)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_COMMA) {
            auto returned = parseActualParams();
            for (ASTNode *c: returned->getChildren()) {
                node->addChild(c);
            }
        } else {
            currentToken--;
        }
    } else {
        currentToken = previousTokenPosition;
        return nullptr;
    }

    return node;
}

ASTUnaryNode *parseUnary() {
    previousTokenPosition = currentToken;
    if (isTokensAvailable(1)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_NOT || next->getData() == "-") {
            auto result = parseExpression();
            return new ASTUnaryNode(result);
        }
    }
    currentToken = previousTokenPosition;
    return nullptr;
}

ASTSubExpressionNode *parseSubExpression() {
    previousTokenPosition = currentToken;

    if (isTokensAvailable(2)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_OPEN_BRACKET) {
            auto result = parseExpression();
            next = getNextToken();
            if (next->getTok() == TOKEN_CLOSE_BRACKET) {
                return new ASTSubExpressionNode(result);
            }
        }
    }

    currentToken = previousTokenPosition;
    return nullptr;
}

ASTFunctionCallNode *parseFunctionCall() {
    previousTokenPosition = currentToken;
    if (isTokensAvailable(3)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_ALPHANUMERIC) {
            string name = next->getData();
            next = getNextToken();
            if (next->getTok() == TOKEN_OPEN_BRACKET) {
                next = getNextToken();
                if (next->getTok() == TOKEN_CLOSE_BRACKET) {
                    return new ASTFunctionCallNode(name, nullptr);
                } else {
                    currentToken--;
                    auto params = parseActualParams();
                    if (isTokensAvailable(1)) {
                        next = getNextToken();
                        if (next->getTok() == TOKEN_CLOSE_BRACKET) {
                            return new ASTFunctionCallNode(name, params);
                        }
                    }
                }
            }
        }
    }

    currentToken = previousTokenPosition;
    return nullptr;
}

ASTFactorNode *parseFactor() {
    previousTokenPosition = currentToken;
    if (isTokensAvailable(1)) {
        TOKEN *next = getNextToken();
        TOK tok = next->getTok();

        auto node = new ASTFactorNode();
        if (tok == TOKEN_BOOLEAN_LITERAL || tok == TOKEN_INT || tok == TOKEN_FLOAT) {
            node->setData(next->getData());
        } else {
            if (tok == TOKEN_ALPHANUMERIC) {
                node->setData(next->getData());
            } else {
                currentToken--;
                auto parseFuncReturn = parseFunctionCall();
                if (parseFuncReturn != nullptr) {
                    node->setASTNode(parseFuncReturn);
                } else {
                    auto subExprReturn = parseSubExpression();
                    if (subExprReturn != nullptr) {
                        node->setASTNode(subExprReturn);
                    } else {
                        auto unaryReturn = parseUnary();
                        if (unaryReturn != nullptr) {
                            node->setASTNode(unaryReturn);
                        } else {
                            currentToken = previousTokenPosition;
                            return nullptr;
                        }
                    }
                }
            }
        }
        return node;
    }

    currentToken = previousTokenPosition;
    return nullptr;
}

ASTTermNode *parseTerm() {
    previousTokenPosition = currentToken;

    auto left = parseFactor();
    if (isTokensAvailable(1)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_MULTIPLICATIVE_OP) {
            auto right = parseFactor();
            return new ASTTermNode(left, right, next->getData());
        } else {
            currentToken--;
            return new ASTTermNode(left, nullptr, "");
        }
    }

    currentToken = previousTokenPosition;
    return nullptr;
}

ASTSimpleExpressionNode *parseSimpleExpression() {

    if (isTokensAvailable(1)) {
        auto left = parseTerm();
        TOKEN *next = getNextToken();
        if (left != nullptr) {
            if (next->getTok() == TOKEN_ADDITIVE_OP) {
                auto right = parseSimpleExpression();
                if (right != nullptr) {
                    return new ASTSimpleExpressionNode(left, right, next->getData());
                }
            } else {
                currentToken--;
                return new ASTSimpleExpressionNode(left, nullptr, "");
            }
        }
    }
    return nullptr;
}

ASTExpressionNode *parseExpression() {

    auto left = parseSimpleExpression();
    if (isTokensAvailable(1)) {
        TOKEN *next = getNextToken();
        if (isRelationalOp(next)) {
            auto right = parseExpression();
            return new ASTExpressionNode(left, right, next->getData());
        } else {
            currentToken--;
            return new ASTExpressionNode(left, nullptr, "");
        };
    }
    return nullptr;
}

ASTVariableNode *parseVariableDecl() {
    string name;
    string type;

    if (isTokensAvailable(5)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_VARIABLE_DECL) {
            next = getNextToken();
            if (next->getTok() == TOKEN_ALPHANUMERIC) {
                name = next->getData();
                next = getNextToken();
                if (next->getTok() == TOKEN_COLON) {
                    next = getNextToken();
                    if (next->getTok() == TOKEN_TYPE) {
                        type = next->getData();
                        next = getNextToken();
                        if (next->getTok() == TOKEN_EQUAL) {
                            auto *data = parseExpression();
                            if (data != nullptr) {
                                return new ASTVariableNode(type, name, data);
                            } else {
                                return new ASTVariableNode(type, name, nullptr);
                            }
                        }
                    }
                }
            }
        }
    }

    return nullptr;
}

ASTAssignmentNode *parseAssignment() {
    if (isTokensAvailable(2)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_ALPHANUMERIC) {
            string name = next->getData();
            next = getNextToken();
            if (next->getTok() == TOKEN_EQUAL) {
                return new ASTAssignmentNode(name, parseExpression());
            }
        }
    }
    return nullptr;
}


ASTReturnNode *parseReturn() {


    if (isTokensAvailable(1)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_RETURN) {
            auto returned = parseExpression();
            if (returned != nullptr) {
                return new ASTReturnNode(returned);
            }
        }
    }

    return nullptr;
}

ASTBlockNode *parseBlock() {
    previousTokenPosition = currentToken;

    auto node = new ASTBlockNode();
    if (isTokensAvailable(2)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_OPEN_CURLY_BRACKET) {
            next = getNextToken();
            while (next->getTok() != TOKEN_CLOSE_CURLY_BRACKET) {
                currentToken--;
                node->addChild(parseStatement());
                if (isTokensAvailable(1)) {
                    next = getNextToken();
                } else {
                    currentToken = previousTokenPosition;
                    return nullptr;
                }
            }
        }
    }

    return node;
}

ASTFormalParam *parseFormalParam() {
    string name;
    TOKEN *next;

    if (isTokensAvailable(3)) {
        next = getNextToken();
        if (next->getTok() == TOKEN_ALPHANUMERIC) {
            name = next->getData();
            next = getNextToken();
            if (next->getTok() == TOKEN_COLON) {
                next = getNextToken();
                if (next->getTok() == TOKEN_TYPE) {
                    return new ASTFormalParam(name, next->getData());
                }
            }
        }
    }
    return nullptr;
}

ASTFormalParams *parseFormalParams() {
    auto toReturn = new ASTFormalParams();
    auto returned = parseFormalParam();

    if (returned != nullptr) {
        toReturn->addChild(returned);
    }


    if (isTokensAvailable(1)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_COMMA) {
            auto ret = parseFormalParams();
            for (ASTNode *child : ret->getChildren()) {
                toReturn->addChild(child);
            }
        } else {
            currentToken--;
        }
    }

    return toReturn;
}

ASTForStatementNode *parseForStatement() {
    previousTokenPosition = currentToken;
    TOKEN *next;
    if (isTokensAvailable(5)) {
        next = getNextToken();
        if (next->getTok() == TOKEN_FOR) {
            next = getNextToken();
            if (next->getTok() == TOKEN_OPEN_BRACKET) {
                auto init = parseVariableDecl();
                next = getNextToken();
                if (next->getTok() == TOKEN_SEMI_COLON) {
                    auto cond = parseExpression();
                    next = getNextToken();
                    if (next->getTok() == TOKEN_SEMI_COLON) {
                        auto expr = parseAssignment();
                        next = getNextToken();
                        if (next->getTok() == TOKEN_CLOSE_BRACKET) {
                            auto body = parseBlock();
                            return new ASTForStatementNode(init, cond, expr, body);
                        }
                    }
                }
            }
        }
    }

    currentToken = previousTokenPosition;
    return nullptr;
}

ASTFunctionDeclNode *parseFunctionDecl() {
    previousTokenPosition = currentToken;
    TOKEN *next;
    if (isTokensAvailable(6)) {
        next = getNextToken();
        if (next->getTok() == TOKEN_FUNCTION_DECL) {
            next = getNextToken();
            if (next->getTok() == TOKEN_ALPHANUMERIC) {
                string name = next->getData();
                next = getNextToken();
                if (next->getTok() == TOKEN_OPEN_BRACKET) {
                    auto params = parseFormalParams();
                    next = getNextToken();
                    if (next->getTok() == TOKEN_CLOSE_BRACKET) {
                        next = getNextToken();
                        if (next->getTok() == TOKEN_COLON) {
                            next = getNextToken();
                            if (next->getTok() == TOKEN_TYPE) {
                                string type = next->getData();
                                auto body = parseBlock();
                                return new ASTFunctionDeclNode(name, params, type, body);
                            }
                        }
                    }
                }
            }
        }
    }

    currentToken = previousTokenPosition;
    return nullptr;
}

ASTIfStatementNode *parseIfStatement() {
    previousTokenPosition = currentToken;
    if (isTokensAvailable(3)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_IF) {
            auto cond = parseExpression();
            next = getNextToken();
            if (next->getTok() == TOKEN_CLOSE_BRACKET) {
                auto ifBody = parseBlock();
                if (isTokensAvailable(1)) {
                    next = getNextToken();
                    if (next->getTok() == TOKEN_ELSE) {
                        auto elseBody = parseBlock();
                        return new ASTIfStatementNode(cond, ifBody, elseBody);
                    } else {
                        currentToken--;
                        return new ASTIfStatementNode(cond, ifBody, nullptr);
                    }
                }
            }
        }
    }

    currentToken = previousTokenPosition;
    return nullptr;
}

ASTPrintNode *parsePrint() {
    previousTokenPosition = currentToken;

    if (isTokensAvailable(1)) {
        TOKEN *next = getNextToken();
        if (next->getTok() == TOKEN_PRINT) {
            return new ASTPrintNode(parseExpression());
        }
    }

    currentToken = previousTokenPosition;
    return nullptr;
}


ASTStatementNode *parseStatement() {
    ASTNode *returned;
    TOKEN *next;
    previousTokenPosition = currentToken;
    returned = parseVariableDecl();
    if(isTokensAvailable(1)) {
        next = getNextToken();
        if (returned != nullptr) {
            if (next->getTok() == TOKEN_SEMI_COLON) {
                return new ASTStatementNode(returned);
            }
        } else {/*can't parseVariable*/
            currentToken = previousTokenPosition;
            returned = parseAssignment();
            if (returned != nullptr) {
                if (isTokensAvailable(1)) {
                    if (next->getTok() == TOKEN_SEMI_COLON) {
                        return new ASTStatementNode(returned);
                    }
                }
            } else {
                currentToken = previousTokenPosition;
                returned = parsePrint();
                if (returned != nullptr) {
                    if (isTokensAvailable(1)) {
                        if (next->getTok() == TOKEN_SEMI_COLON) {
                            return new ASTStatementNode(returned);
                        }
                    }
                } else {
                    currentToken = previousTokenPosition;
                    returned = parseIfStatement();
                    if (returned != nullptr) {
                        return new ASTStatementNode(returned);
                    } else {
                        currentToken = previousTokenPosition;
                        returned = parseForStatement();
                        if (returned != nullptr) {
                            return new ASTStatementNode(returned);
                        } else {
                            currentToken = previousTokenPosition;
                            returned = parseReturn();
                            if (returned != nullptr) {
                                if (isTokensAvailable(1)) {
                                    next = getNextToken();
                                    if (next->getTok() == TOKEN_SEMI_COLON) {
                                        return new ASTStatementNode(returned);
                                    }
                                }
                            } else {
                                currentToken = previousTokenPosition;
                                returned = parseFunctionDecl();
                                if (returned != nullptr) {
                                    return new ASTStatementNode(returned);
                                } else {
                                    currentToken = previousTokenPosition;
                                    returned = parseBlock();
                                    return new ASTStatementNode(returned);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    currentToken = previousTokenPosition;
    return nullptr;
}

ASTProgramNode *parseProgram(std::vector<TOKEN *> tok) {
    tokens = move(tok);

    auto ast = new ASTProgramNode();

    while (isTokensAvailable(1)) {
        ast->addChild(parseStatement());
    }

    return ast;
}