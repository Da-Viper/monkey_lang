#include "../include/Token.h"

#include <ostream>

std::optional<TokenType> Token::lookupKeywords(std::string_view word) {
    if (word == "fn") {
        return TokenType::Function;
    }
    if (word == "let") {
        return TokenType::Let;
    }
    if (word == "true") {
        return TokenType::True;
    }
    if (word == "false") {
        return TokenType::False;
    }
    if (word == "if") {
        return TokenType::If;
    }
    if (word == "else") {
        return TokenType::Else;
    }
    if (word == "return") {
        return TokenType::Return;
    }
    return {};
}

static std::string_view tokenTypeToString(TokenType tokenType) {
    switch (tokenType) {
        case TokenType::Illegal:
            return "Illegal";
        case TokenType::Eof:
            return "Eof";
        case TokenType::Identifier:
            return "Identifier";
        case TokenType::Int:
            return "Int";
        case TokenType::Assign:
            return "Assign";
        case TokenType::Plus:
            return "Plus";
        case TokenType::Minus:
            return "Minus";
        case TokenType::Bang:
            return "Bang";
        case TokenType::Asterisk:
            return "Asterisk";
        case TokenType::Slash:
            return "Slash";
        case TokenType::LessThan:
            return "LessThan";
        case TokenType::GreaterThan:
            return "GreaterThan";
        case TokenType::Eq:
            return "Eq";
        case TokenType::NotEq:
            return "NotEq";
        case TokenType::Comma:
            return "Comma";
        case TokenType::Semicolon:
            return "Semicolon";
        case TokenType::LParen:
            return "LParen";
        case TokenType::RParen:
            return "RParen";
        case TokenType::LCurly:
            return "LCurly";
        case TokenType::RCurly:
            return "RCurly";
        case TokenType::Function:
            return "Function";
        case TokenType::Let:
            return "Let";
        case TokenType::True:
            return "True";
        case TokenType::False:
            return "False";
        case TokenType::If:
            return "If";
        case TokenType::Else:
            return "Else";
        case TokenType::Return:
            return "Return";
    }
}

std::string_view Token::toString(Token token) {
    return tokenTypeToString(token.type);
}

std::ostream &operator<<(std::ostream &os, TokenType tokenType) {
    return os << "Type: " << tokenTypeToString(tokenType);
}

std::ostream &operator<<(std::ostream &os, Token token) {
    switch (token.type) {
        case TokenType::Identifier:
        case TokenType::Int:
            os << '{' << token.type << " Literal: " << token.literal << '}';
            break;
        default:
            os << '{' << token.type << '}';
    }
    return os;
}

