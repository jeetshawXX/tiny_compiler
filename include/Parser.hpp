#pragma once
#include "Lexer.hpp"
#include "AST.hpp"
#include <memory>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::unique_ptr<ASTNode> parse();

private:
    std::vector<Token> tokens;
    size_t pos;

    // Helper functions
    const Token& peek() const;
    const Token& advance();
    bool isAtEnd() const;
    bool match(TokenType type);
    const Token& consume(TokenType type, const std::string& message);

    // Parsing rules (Top-down)
    std::unique_ptr<ASTNode> parseDeclaration();
    std::unique_ptr<ASTNode> parseExpression();
    std::unique_ptr<ASTNode> parsePrimary(); // Numbers, Parens, Identifiers
};