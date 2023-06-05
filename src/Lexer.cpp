#include "../include/Lexer.h"
#include "../include/Token.h"

#include <algorithm>

Lexer::Lexer(const std::string &in) : input_(in), position_(input_.cbegin()) {}

Token Lexer::nextToken() {
    skipWhiteSpace();

    if (position_ >= input_.end()) {
        return Token{TokenType::Eof};
    }

    const auto currentPos = position_;
    const auto currentChar = static_cast<unsigned char>(*position_);

    position_++;
    switch (currentChar) {
        case ';':
            return Token{TokenType::Semicolon};
        case '(':
            return Token{TokenType::LParen};
        case ')':
            return Token{TokenType::RParen};
        case ',':
            return Token{TokenType::Comma};
        case '+':
            return Token{TokenType::Plus};
        case '-':
            return Token{TokenType::Minus};
        case '{':
            return Token{TokenType::LCurly};
        case '}':
            return Token{TokenType::RCurly};
        case '/':
            return Token{TokenType::Slash};
        case '*':
            return Token{TokenType::Asterisk};
        case '<':
            return Token{TokenType::LessThan};
        case '>':
            return Token{TokenType::GreaterThan};
        case '=': {
            if (peekChar() == '=') {
                position_++;
                return Token{TokenType::Eq};
            }
            return Token{TokenType::Assign};
        }
        case '!': {
            if (peekChar() == '=') {
                position_++;
                return Token{TokenType::NotEq};
            }
            return Token{TokenType::Bang};
        }
        default:
            break;
    }

    if (isalpha(currentChar)) {
        const auto literal = readIdentifier(currentPos);
        // if, else, fn , for,
        const auto keyword = Token::lookupKeywords(literal);
        if (keyword.has_value()) {
            return Token{keyword.value()};
        }
        return Token{TokenType::Identifier, literal};
    }

    if (isdigit(currentChar)) {
        position_ = std::find_if_not(position_, input_.cend(), isdigit);
        return Token{TokenType::Int, {currentPos, (unsigned long) std::distance(currentPos, position_)}};
    }

    return Token{TokenType::Illegal};
}

std::string_view Lexer::readIdentifier(std::string_view::const_iterator startPos) {
    position_ = std::find_if_not(position_, input_.cend(), isalnum);
    const unsigned int len = std::distance(startPos, position_);
    return std::string_view{startPos, len};
}

void Lexer::skipWhiteSpace() {
    position_ = std::find_if_not(position_, input_.cend(), [](char l) {
        return l == ' ' || l == '\f' || l == '\n' || l == '\r' || l == '\t' || l == '\v';
    });
}

char Lexer::peekChar() const {
    if (position_ == input_.cend()) {
        return '\0';
    }
    return *position_;
}
