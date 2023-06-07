
#include <catch2/catch.hpp>
#include "Lexer.h"
#include "AST.h"
#include "Parser.h"

void returnStatementTest(const AST::Statement &statement) {
    auto *dyncast = dynamic_cast<const AST::ReturnStatement *>(&statement);
    REQUIRE(dyncast != nullptr);
    REQUIRE(statement.tokenName() == TokenType::Return);
    // TODO: Check the value of the return statement;
}

TEST_CASE("Testing the return statement", "[Parser]") {
    SECTION("Valid Return Statement") {
        const std::string_view input = "return 5;";
        auto parser = Parser(Lexer(input));
        const auto program = parser.parseProgram();

        for (const auto &statement: program.statements) {
            returnStatementTest(*statement);
        }
    }
}