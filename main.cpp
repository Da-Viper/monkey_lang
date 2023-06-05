#include <iostream>
#include "Repl.h"

int main(int, char**) {
#ifdef  _WIN32
    const userName = std::getenv("USERPROFILE");
#else
    const auto userName = std::getenv("USER");
#endif
    std::cout << "Hello " << userName << ",\nThis is the monkey programming language!\n";
    std::cout << "Feel free to type in commands \n";

    Repl::start(std::cin, std::cout);
}
