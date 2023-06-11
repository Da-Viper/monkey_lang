//
// Created by da-viper on 04/06/23.
//

#include "AST.h"

#include <utility>
#include <sstream>

namespace AST {

    std::ostream &operator<<(std::ostream &os, const Node &node) {
        return os << node.to_string();
    }

    TokenType Program::tokenName() const {
        return token_.type;
    }

    std::string Program::to_string() const {
        std::ostringstream oss;
        for (const auto &statement: statements) {
            oss << *statement;
        }
        return oss.str();
    }

    // LET
    TokenType LetStatement::tokenName() const {
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

    std::string LetStatement::to_string() const {
        std::ostringstream oss;
        oss << tokenName() << ' ' << name_.to_string()
            << " = " << value_->to_string() << ';';
        return oss.str();
    }

    // Identifier
    TokenType Identifier::tokenName() const {
        return TokenType::Identifier;
    }

    std::string_view Identifier::value() const {
        return value_;
    }

    Identifier::Identifier(std::string_view value) : value_(value) {}

    std::string Identifier::to_string() const {
        return std::string(value_.data() , value_.length());
    }

    // Return Statement
    TokenType ReturnStatement::tokenName() const {
        return TokenType::Return;
    }

    std::string ReturnStatement::to_string() const {
        std::ostringstream oss;
        oss << tokenName() << " " << return_value_->to_string() << ';';
        return oss.str();
    }

    // Expression Statement
    TokenType ExpressionStatement::tokenName() const { return token_.type; }

    std::string ExpressionStatement::to_string() const {
        return expr_->to_string();
    }

    TokenType IntegerLiteral::tokenName() const {
        return TokenType::Int;
    }

    std::string IntegerLiteral::to_string() const {
        return std::to_string(value_);
    }
}  // namespace AST