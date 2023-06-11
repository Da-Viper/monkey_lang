#include <catch2/catch.hpp>
#include "Lexer.h"
#include "AST.h"
#include "Parser.h"


TEST_CASE("Test Integer Literal", "[Parser]") {
    auto input = std::string("5;");

    auto parser = Parser(Lexer(input));
    auto program = parser.parseProgram();

    REQUIRE(program.statements.size() == 1);
    auto exprStmt = dynamic_cast<AST::ExpressionStatement *>(program.statements[0].get());
    REQUIRE(exprStmt != nullptr);
    auto exprInt =  dynamic_cast<AST::IntegerLiteral *>(exprStmt->expression());
    REQUIRE(exprInt != nullptr);

    REQUIRE(exprInt->value() == 5);
}