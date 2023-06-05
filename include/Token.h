#ifndef WRITING_AN_INTERPRETER_TOKEN_H
#define WRITING_AN_INTERPRETER_TOKEN_H

#include <string>
#include <optional>

enum class TokenType {
    Illegal,
    Eof,
    // IDENTIFIERS + LITERALS
    Identifier,
    Int,

    // OPERATORS
    Assign,
    Plus,
    Minus,
    Bang,
    Asterisk,
    Slash,

    LessThan,
    GreaterThan,

    Eq,
    NotEq,

    // DELIMITERS
    Comma,
    Semicolon,

    LParen,
    RParen,
    LCurly,
    RCurly,

    // KEYWORDS
    Function,
    Let,
    True,
    False,
    If,
    Else,
    Return
};

std::ostream &operator<<(std::ostream &os, TokenType tokenType);

struct Token {
    TokenType type;
    std::string_view literal;

    static std::string_view toString(Token token);
    static std::optional<TokenType> lookupKeywords(std::string_view word);
    friend std::ostream &operator<<(std::ostream &os, Token token);
};

#endif  // WRITING_AN_INTERPRETER_TOKEN_H