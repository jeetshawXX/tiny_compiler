// #include <iostream>
// #include "Lexer.hpp"

// int main() {
//     std::string code = "int result = (10 + 5) * 2;";
//     Lexer lexer(code);
//     auto tokens = lexer.tokenize();

//     for (const auto& t : tokens) {
//         std::cout << "Lexeme: [" << t.lexeme << "] | Line: " << t.line << std::endl;
//     }
//     return 0;
// }

// #include <iostream>
// #include "Lexer.hpp"
// #include "Parser.hpp"

// int main() {
//     std::string code = "int x = 42;";
    
//     try {
//         Lexer lexer(code);
//         auto tokens = lexer.tokenize();

//         Parser parser(tokens);
//         auto ast = parser.parse();

//         std::cout << "Successfully parsed the program into an AST!" << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << e.what() << std::endl;
//     }

//     return 0;
// }

#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"

int main() {
    // Testing Operator Precedence: (10 + 5 * 2)
std::string code = "int x = y + 5;";    
    try {
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        Parser parser(tokens);
        auto ast = parser.parse();

        std::cout << "--- Abstract Syntax Tree ---" << std::endl;
        ast->print(0);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}