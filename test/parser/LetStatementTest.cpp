
#include <catch2/catch.hpp>
#include "Lexer.h"
#include "AST.h"
#include "Parser.h"

using namespace AST;

void letStatementTest(const AST::Statement &statement, std::string_view name) {

    const auto *dynCast = dynamic_cast<const LetStatement *>(&statement);
    REQUIRE(dynCast != nullptr);
    REQUIRE(dynCast->identifierName() == name);
    REQUIRE(dynCast->tokenName() == TokenType::Let);
}

TEST_CASE("Let Statement", "[Parser]") {
    SECTION("With Correct Input") {
        const std::string input = R"(let x = 5;
        let y = 10;
        let foobar = 838383;)";

        auto parser = Parser(Lexer(input));
        auto program = parser.parseProgram();

        constexpr std::size_t noOfExpectedStatements = 3;
        REQUIRE(program.statements.size() == noOfExpectedStatements);

        constexpr std::string_view expected[noOfExpectedStatements] = {"x", "y", "foobar"};
        for (std::size_t i = 0; i < noOfExpectedStatements; ++i) {
            letStatementTest(*program.statements[i].get(), expected[i]);
        }
    }

    SECTION("With Wrong Input") {
        const std::string input = R"(let x  5;;)";

        auto parser = Parser(Lexer(input));
        CHECK_THROWS_AS(parser.parseProgram(), ParsingException);
    }
}

