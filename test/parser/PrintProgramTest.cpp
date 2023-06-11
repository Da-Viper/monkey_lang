#include <catch2/catch.hpp>
#include <iostream>

#include "Parser.h"
#include "AST.h"
#include "Token.h"

TEST_CASE("Test Printing Program", "[Parser]") {
    using namespace AST;
    std::vector<StatementPtr> vec;
    vec.push_back(
            std::make_unique<LetStatement>(
                    Identifier("myVar"),
                    std::make_unique<Identifier>("anotherVar")
            )
    );

    auto program = Program(std::move(vec));
    const auto programString= program.to_string();
    // TODO: Comeback and use the one below after implementing parsing expression;
//    auto parser = Parser(Lexer("let myVar = anotherVar;"));
//    auto program = parser.parseProgram();
//    const auto programString = program.to_string();
    REQUIRE(programString == "let myVar = anotherVar;");
}