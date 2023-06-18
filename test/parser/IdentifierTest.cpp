
#include <catch2/catch.hpp>
#include "Lexer.h"
#include "Parser.h"

TEST_CASE("Test Identifier can be parsed", "[Parser]") {
    std::string input = "foobar;";
    auto parser = Parser(Lexer(input));
    auto program = parser.parseProgram();

    REQUIRE(program.statements.size() == 1);
    auto firstStmt = dynamic_cast<AST::ExpressionStatement *>(program.statements[0].get());
    REQUIRE(firstStmt != nullptr);
    REQUIRE(firstStmt->tokenName() == TokenType::Identifier);
    auto firstIdent = dynamic_cast<AST::Identifier *>(firstStmt->expression());
    REQUIRE(firstIdent != nullptr);
    REQUIRE(firstIdent->value() == "foobar");
}