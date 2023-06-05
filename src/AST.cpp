//
// Created by da-viper on 04/06/23.
//

#include "AST.h"

namespace AST {
    std::string_view Program::tokenLiteral() const {
        return std::string_view();
    }

// LET
    std::string_view LetStatement::tokenLiteral() const {
        return Token::toString(token_);
    }

}