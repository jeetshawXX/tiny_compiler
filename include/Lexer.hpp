#pragma once
#include <string>
#include <vector>

enum class TokenType {
    // Keywords
    Int, Return, 
    // Literals & Identifiers
    Identifier, Number,
    // Operators
    Assignment, Plus, Minus, Asterisk, Slash, 
    // Punctuation
    Semicolon, LParen, RParen,
    // Control
    Eof, Unknown
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string src;
    size_t pos;
    int line;

    char peek();    // Look at current char without moving
    char advance(); // Return current char and move to next
    bool isAtEnd();
    
    Token readNumber();
    Token readIdentifierOrKeyword();
    Token readSymbol();
};