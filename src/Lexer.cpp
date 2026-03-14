#include "Lexer.hpp"
#include <cctype>
#include <unordered_map>

static const std::unordered_map<std::string, TokenType> keywords = {
    {"int", TokenType::Int},
    {"return", TokenType::Return}
};

Lexer::Lexer(const std::string& source) : src(source), pos(0), line(1) {}

bool Lexer::isAtEnd() { return pos >= src.size(); }
char Lexer::peek() { return isAtEnd() ? '\0' : src[pos]; }
char Lexer::advance() { return src[pos++]; }

Token Lexer::readNumber() {
    size_t start = pos - 1; // Since tokenize() already called advance() for the first digit
    while (isdigit(peek())) advance();
    return {TokenType::Number, src.substr(start, pos - start), line};
}

Token Lexer::readIdentifierOrKeyword() {
    size_t start = pos - 1; 
    while (isalnum(peek()) || peek() == '_') advance();
    
    std::string text = src.substr(start, pos - start);
    if (keywords.count(text)) return {keywords.at(text), text, line};
    return {TokenType::Identifier, text, line};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        char c = advance(); // Consume the character

        if (isspace(c)) {
            if (c == '\n') line++;
            continue;
        }

        if (isdigit(c)) {
            tokens.push_back(readNumber());
        } else if (isalpha(c) || c == '_') {
            tokens.push_back(readIdentifierOrKeyword());
        } else {
            switch (c) {
                case '=': tokens.push_back({TokenType::Assignment, "=", line}); break;
                case '+': tokens.push_back({TokenType::Plus, "+", line}); break;
                case '-': tokens.push_back({TokenType::Minus, "-", line}); break;
                case '*': tokens.push_back({TokenType::Asterisk, "*", line}); break;
                case '/': tokens.push_back({TokenType::Slash, "/", line}); break;
                case ';': tokens.push_back({TokenType::Semicolon, ";", line}); break;
                case '(': tokens.push_back({TokenType::LParen, "(", line}); break;
                case ')': tokens.push_back({TokenType::RParen, ")", line}); break;
                default:  tokens.push_back({TokenType::Unknown, std::string(1, c), line}); break;
            }
        }
    }
    tokens.push_back({TokenType::Eof, "EOF", line});
    return tokens;
}