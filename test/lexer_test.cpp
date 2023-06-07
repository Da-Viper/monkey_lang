#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "../include/Lexer.h"

#include <catch2/catch.hpp>
#include <string>

#include "../include/Token.h"

template<class T, size_t Size>
void LEXER_CHECK_ALL_TOKENS(Lexer &lexer, const T (&expectedTokens)[Size]) {
    int i = 0;
    for (const auto &expectedToken: expectedTokens) {
        const auto token = lexer.advanceToken();

        REQUIRE(token.literal == expectedToken.literal);

        REQUIRE(token.type == expectedToken.type);
        i++;
    }
}

SCENARIO("Testing The Next Token ", "[Lexer]") {
    GIVEN("Input with random tokens: =+(){},;") {
        const std::string input = std::string("=+(){},;");
        Token expectedTokens[] = {
                {TokenType::Assign},
                {TokenType::Plus},
                {TokenType::LParen},
                {TokenType::RParen},
                {TokenType::LCurly},
                {TokenType::RCurly},
                {TokenType::Comma},
                {TokenType::Semicolon},
        };

        THEN("Next Token works correctly") {
            auto lexer = Lexer(input);
            LEXER_CHECK_ALL_TOKENS(lexer, expectedTokens);
        }
    }

    GIVEN("Input with assignment: `let five = 5`") {
        const std::string input = R"(let five = 5;
let ten = 10;
let add = fn(x, y) {
x + y;
};
let result = add(five, ten);)";
        Token expectedTokens[] = {
                {TokenType::Let},
                {TokenType::Identifier, "five"},
                {TokenType::Assign},
                {TokenType::Int,        "5"},
                {TokenType::Semicolon},
                {TokenType::Let},
                {TokenType::Identifier, "ten"},
                {TokenType::Assign},
                {TokenType::Int,        "10"},
                {TokenType::Semicolon},

                {TokenType::Let},
                {TokenType::Identifier, "add"},
                {TokenType::Assign},
                {TokenType::Function},
                {TokenType::LParen},
                {TokenType::Identifier, "x"},
                {TokenType::Comma},
                {TokenType::Identifier, "y"},
                {TokenType::RParen},
                {TokenType::LCurly},

                {TokenType::Identifier, "x"},
                {TokenType::Plus},
                {TokenType::Identifier, "y"},
                {TokenType::Semicolon},

                {TokenType::RCurly},
                {TokenType::Semicolon},

                {TokenType::Let},
                {TokenType::Identifier, "result"},
                {TokenType::Assign},
                {TokenType::Identifier, "add"},
                {TokenType::LParen},
                {TokenType::Identifier, "five"},
                {TokenType::Comma},
                {TokenType::Identifier, "ten"},
                {TokenType::RParen},
                {TokenType::Semicolon},
                {TokenType::Eof}
        };

        THEN("Next Token works correctly") {
            auto lexer = Lexer(input);
            LEXER_CHECK_ALL_TOKENS(lexer, expectedTokens);
        }
    }

    GIVEN("Large file input") {
        const std::string input = R"(let five = 5;
let ten = 10;

let add = fn(x, y) {
  x + y;
};

let result = add(five, ten);
!-/*5;
5 < 10 > 5;

if (5 < 10) {
	return true;
} else {
	return false;
}

10 == 10;
10 != 9;)";

        Token expectedTokens[] = {
                {TokenType::Let},
                {TokenType::Identifier, "five"},
                {TokenType::Assign},
                {TokenType::Int,        "5"},
                {TokenType::Semicolon},
                {TokenType::Let},
                {TokenType::Identifier, "ten"},
                {TokenType::Assign},
                {TokenType::Int,        "10"},
                {TokenType::Semicolon},

                {TokenType::Let},
                {TokenType::Identifier, "add"},
                {TokenType::Assign},
                {TokenType::Function},
                {TokenType::LParen},
                {TokenType::Identifier, "x"},
                {TokenType::Comma},
                {TokenType::Identifier, "y"},
                {TokenType::RParen},
                {TokenType::LCurly},

                {TokenType::Identifier, "x"},
                {TokenType::Plus},
                {TokenType::Identifier, "y"},
                {TokenType::Semicolon},

                {TokenType::RCurly},
                {TokenType::Semicolon},

                {TokenType::Let},
                {TokenType::Identifier, "result"},
                {TokenType::Assign},
                {TokenType::Identifier, "add"},
                {TokenType::LParen},
                {TokenType::Identifier, "five"},
                {TokenType::Comma},
                {TokenType::Identifier, "ten"},
                {TokenType::RParen},
                {TokenType::Semicolon},
                {TokenType::Bang},
                {TokenType::Minus},
                {TokenType::Slash},
                {TokenType::Asterisk},
                {TokenType::Int, "5"},
                {TokenType::Semicolon},
                {TokenType::Int, "5"},
                {TokenType::LessThan},
                {TokenType::Int , "10"},
                {TokenType::GreaterThan},
                {TokenType::Int , "5"},
                {TokenType::Semicolon},
                {TokenType::If},
                {TokenType::LParen},
                {TokenType::Int, "5"},
                {TokenType::LessThan},
                {TokenType::Int, "10"},
                {TokenType::RParen},
                {TokenType::LCurly },
                {TokenType::Return},
                {TokenType::True},
                {TokenType::Semicolon},
                {TokenType::RCurly},
                {TokenType::Else},
                {TokenType::LCurly},
                {TokenType::Return},
                {TokenType::False},
                {TokenType::Semicolon},
                {TokenType::RCurly},
                {TokenType::Int , "10"},
                {TokenType::Eq},
                {TokenType::Int, "10"},
                {TokenType::Semicolon},
                {TokenType::Int, "10"},
                {TokenType::NotEq},
                {TokenType::Int , "9"},
                {TokenType::Semicolon},
                {TokenType::Eof}
        };

        THEN("Read Next Token works correctly ") {
            auto lexer = Lexer(input);
            LEXER_CHECK_ALL_TOKENS(lexer, expectedTokens);
        }
    }
}
