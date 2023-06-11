#ifndef WRITING_AN_INTERPRETER_LEXER_H
#define WRITING_AN_INTERPRETER_LEXER_H

#include <string>
#include "Token.h"

class Lexer final {

public:
    explicit Lexer(std::string_view input);

    char peekChar() const;

    Token advanceToken();

    Token curToken() const { return curToken_; };


private:
    void skipWhiteSpace();

    inline Token nextToken();

    std::string_view readIdentifier(std::string_view::const_iterator startPos);

    Token curToken_;
    const std::string_view input_;
    std::string_view::const_iterator position_;
};


#endif // WRITING_AN_INTERPRETER_LEXER_H