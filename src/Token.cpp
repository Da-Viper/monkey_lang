#include "../include/Token.h"

#include <ostream>
#include <cassert>

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
            return "illegal";
        case TokenType::Eof:
            return "eof";
        case TokenType::Identifier:
            return "identifier";
        case TokenType::Int:
            return "int";
        case TokenType::Assign:
            return "=";
        case TokenType::Plus:
            return "+";
        case TokenType::Minus:
            return "-";
        case TokenType::Bang:
            return "!";
        case TokenType::Asterisk:
            return "*";
        case TokenType::Slash:
            return "/";
        case TokenType::LessThan:
            return "<";
        case TokenType::GreaterThan:
            return ">";
        case TokenType::Eq:
            return "==";
        case TokenType::NotEq:
            return "!=";
        case TokenType::Comma:
            return "comma";
        case TokenType::Semicolon:
            return ";";
        case TokenType::LParen:
            return "(";
        case TokenType::RParen:
            return ")";
        case TokenType::LCurly:
            return "{";
        case TokenType::RCurly:
            return "}";
        case TokenType::Function:
            return "fn";
        case TokenType::Let:
            return "let";
        case TokenType::True:
            return "true";
        case TokenType::False:
            return "false";
        case TokenType::If:
            return "if";
        case TokenType::Else:
            return "else";
        case TokenType::Return:
            return "return";
    }
    assert(false && "token type not handled");
}

std::string_view Token::to_string(Token token) {
    return tokenTypeToString(token.type);
}

std::ostream &operator<<(std::ostream &os, TokenType tokenType) {
    return os << tokenTypeToString(tokenType);
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

