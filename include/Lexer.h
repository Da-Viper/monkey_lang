#ifndef WRITING_AN_INTERPRETER_LEXER_H
#define WRITING_AN_INTERPRETER_LEXER_H

#include <string>
#include "Token.h"

class Lexer final {

public:
    explicit Lexer(const std::string &input);

    char peekChar() const;

    Token nextToken();

private:
    void skipWhiteSpace();

    std::string_view readIdentifier(std::string_view::const_iterator startPos);

    const std::string_view input_;
    std::string_view::const_iterator position_;
};


#endif // WRITING_AN_INTERPRETER_LEXER_H