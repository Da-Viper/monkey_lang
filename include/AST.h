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
        TokenType tokenLiteral() const override;

        Token token_;
        std::vector<std::unique_ptr<Statement>> statements;
    };

    class LetStatement : public Statement {
    public:
        // TODO: remove this constructor;
        explicit LetStatement(Identifier name): name_(std::move(name)){}
        LetStatement(Identifier name, std::unique_ptr<Expression> value);

        [[nodiscard]]
        TokenType tokenLiteral() const override;

        std::string_view identifierName() const;

        void statementNode() override;

        // TODO make this private;
        Identifier name_;
    private:
        std::unique_ptr<Expression> value_;
    };
}
#endif //MONKEY_LANG_AST_H
