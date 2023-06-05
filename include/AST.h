#ifndef MONKEY_LANG_AST_H
#define MONKEY_LANG_AST_H

#include <string_view>
#include <vector>
#include <memory>
#include "Token.h"

namespace AST {

    // Node
    class Node {
    public:
        virtual std::string_view tokenLiteral() const = 0;
    };

    // Statement
    class Statement : public Node {
        void statementNode();
    };

    // Expression
    class Expression : public Node {
        void expressionNode();
    };

    // Identifier
    class Identifier : public Node {
    };

    // Program
    class Program final : public Node {
    public:
        [[nodiscard]]
        std::string_view tokenLiteral() const override;

    private:
        std::vector<Statement> statements;
    };

    class LetStatement : public Statement {
    public:
        std::string_view tokenLiteral() const override;

    private:
        Token token_;
        std::unique_ptr<Identifier> name_;
        std::unique_ptr<Expression> value_;
    };
}
#endif //MONKEY_LANG_AST_H
