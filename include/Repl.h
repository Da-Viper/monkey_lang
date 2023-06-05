//
// Created by da-viper on 04/06/23.
//

#ifndef MONKEY_LANG_REPL_H
#define MONKEY_LANG_REPL_H

#include <iostream>
enum class TokenType;
namespace Repl {
    const auto Prompt = ">>> ";
    void start (std::istream &in, std::ostream &out );

}
#endif //MONKEY_LANG_REPL_H
