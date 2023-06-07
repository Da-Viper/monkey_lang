//
// Created by da-viper on 04/06/23.
//

#include "AST.h"

#include <utility>

namespace AST {
    TokenType Program::tokenLiteral() const {
        return token_.type;
    }

    // LET
    TokenType LetStatement::tokenLiteral() const {
        return TokenType::Let;
    }

    std::string_view LetStatement::identifierName() const {
        return name_.value();
    }

    void LetStatement::statementNode() {

    }

    LetStatement::LetStatement(Identifier name, std::unique_ptr<Expression> value)
            : name_(std::move(name)),
              value_(std::move(value)) {}

    // Identifier
    TokenType Identifier::tokenLiteral() const {
        return TokenType::Identifier;
    }

    std::string_view Identifier::value() const {
        return value_;
    }

    Identifier::Identifier(std::string_view value) : value_(value) {}
}