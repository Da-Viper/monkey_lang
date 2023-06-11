#ifndef MONKEY_LANG_AST_H
#define MONKEY_LANG_AST_H

#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "Token.h"

enum class TokenType;

namespace AST {

#define NODE_PTR(x) \
    using  x##Ptr = std::unique_ptr<x>\


// Node
    class Node {
    public:
        virtual TokenType tokenName() const = 0;

        [[nodiscard]]
        virtual std::string to_string() const { return ""; };

    };

    std::ostream &operator<<(std::ostream &os, const Node &node);

// Statement
    class Statement : public Node {
    public:
        virtual void statementNode() {};

        virtual ~Statement() = default;
    };

// Expression
    class Expression : public Node {
    public:
        virtual void expressionNode() {};

        virtual ~Expression() = default;
    };

    NODE_PTR(Expression);
    NODE_PTR(Statement);

// Identifier
    class Identifier : public Expression {
    public:
        explicit Identifier(std::string_view value);

        [[nodiscard]]
        TokenType tokenName() const override;

        [[nodiscard]]
        std::string_view value() const;

        std::string to_string() const override;

    private:
        std::string_view value_;
    };

// Program
    struct Program final : public Node {
        explicit Program() = default;

        explicit Program(std::vector<StatementPtr> stmt) : statements(std::move(stmt)) {};

        [[nodiscard]]
        TokenType tokenName() const override;

        std::string to_string() const override;

        std::vector<StatementPtr> statements;

    private:
        Token token_;
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

        std::string to_string() const override;

        // TODO make this private;
        Identifier name_;

    private:
        ExpressionPtr value_;
    };

    NODE_PTR(LetStatement);

    class ReturnStatement : public Statement {
    public:
        explicit ReturnStatement(ExpressionPtr expr) : return_value_(std::move(expr)) {}

        TokenType tokenName() const override;

        std::string to_string() const override;

    private:
        ExpressionPtr return_value_;
    };

    NODE_PTR(ReturnStatement);

    class ExpressionStatement : public Statement, public Expression {
    public:
        explicit ExpressionStatement(Token token, ExpressionPtr ptr) : expr_(std::move(ptr)), token_(token) {};

        void statementNode() override {};

        TokenType tokenName() const override;

        std::string to_string() const override;

        Expression *expression() const { return expr_.get(); };

    private:
        ExpressionPtr expr_;
        Token token_;
    };

    class TokenLiteral : public Expression {
    public:
        explicit TokenLiteral(Token token) : token_(token) {};

        TokenType tokenName() const override {
            return token_.type;
        }

        std::string to_string() const override {
            return std::string(Token::to_string(token_));
        }

    private:
        Token token_;
    };

    class IntegerLiteral : public Expression {
    public:
        explicit IntegerLiteral(int64_t val): value_(val) {};
        TokenType tokenName() const override;

        std::string to_string() const override;

        int64_t value() const { return value_; };

    private:
        int64_t value_;
    };

    NODE_PTR(ExpressionStatement);
#undef NODE_PTR
}  // namespace AST
#endif  // MONKEY_LANG_AST_H
