#include "Repl.h"
#include "Lexer.h"

#include <string>

namespace Repl {
    void start(std::istream &in, std::ostream &out) {
        while (true) {
            // get line
            out << Prompt ;
            std::string line;
            std::getline(in, line);
            if (line.empty()) {
                return;
            }

            auto lexer = Lexer(line);
            for (auto token = lexer.nextToken(); token.type != TokenType::Eof; token = lexer.nextToken()) {
                out << token << '\n';
            }
        }
    }
}