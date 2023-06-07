#ifndef MONKEY_LANG_AST_H
#define MONKEY_LANG_AST_H

#include <string_view>
#include <utility>
#include <vector>
#include <memory>
#include "Token.h"

enum class TokenType;

namespace AST {

    // Node
    class Node {
    public:
        virtual TokenType tokenName() const = 0;
    };

    // Statement
    class Statement : public Node {
    public:
        virtual void statementNode() = 0;

        virtual ~Statement() = default;
    };

    // Expression
    class Expression : public Node {
    public:
        virtual void expressionNode() = 0;

        virtual ~Expression() = default;
    };

    using ExpressionPtr = std::unique_ptr<Expression>;
    using StatementPtr = std::unique_ptr<Statement>;

    // Identifier
    class Identifier : public Node {
    public:
        explicit Identifier(std::string_view value);

        [[nodiscard]]
        TokenType tokenName() const override;

        [[nodiscard]]
        std::string_view value() const;

    private:
        std::string_view value_;
    };

    // Program
    struct Program final : public Node {
        [[nodiscard]]
        TokenType tokenName() const override;

        Token token_;
        std::vector<StatementPtr> statements;
    };

    class LetStatement : public Statement {
    public:
        // TODO: remove this constructor;
        explicit LetStatement(Identifier name) : name_(std::move(name)) {}

        LetStatement(Identifier name, ExpressionPtr value);

        [[nodiscard]]
        TokenType tokenName() const override;

        std::string_view identifierName() const;

        void statementNode() override;

        // TODO make this private;
        Identifier name_;
    private:
        ExpressionPtr value_;
    };

    class ReturnStatement : public Statement {
        TokenType tokenName() const override;

        ExpressionPtr return_value_;
    };
}
#endif //MONKEY_LANG_AST_H
