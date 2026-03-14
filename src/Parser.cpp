#include "Parser.hpp"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

const Token& Parser::peek() const { return tokens[pos]; }
const Token& Parser::advance() { if (!isAtEnd()) pos++; return tokens[pos - 1]; }
bool Parser::isAtEnd() const { return peek().type == TokenType::Eof; }

bool Parser::match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

const Token& Parser::consume(TokenType type, const std::string& message) {
    if (peek().type == type) return advance();
    throw std::runtime_error("Parser Error at line " + std::to_string(peek().line) + ": " + message);
}

// 1. Root: Entry point
std::unique_ptr<ASTNode> Parser::parse() {
    return parseDeclaration();
}

// 2. Declaration: 'int x = ...;'
std::unique_ptr<ASTNode> Parser::parseDeclaration() {
    if (match(TokenType::Int)) {
        Token name = consume(TokenType::Identifier, "Expect variable name.");
        
        // --- SEMANTIC CHECK: Define variable ---
        symbolTable.define(name.lexeme, "int");
        
        consume(TokenType::Assignment, "Expect '=' after identifier.");
        auto init = parseExpression();
        consume(TokenType::Semicolon, "Expect ';' after declaration.");
        return std::make_unique<VarDeclAST>(name.lexeme, std::move(init));
    }
    return parseExpression();
}

// 3. Expression: For now, we handle simple numbers/identifiers
// In the next step, we will add Math (+, -, *, /)
std::unique_ptr<ASTNode> Parser::parseExpression() {
    return parsePrimary();
}

// 4. Primary: The smallest units
std::unique_ptr<ASTNode> Parser::parsePrimary() {
    if (match(TokenType::Number)) {
        return std::make_unique<NumberExprAST>(std::stoi(tokens[pos-1].lexeme));
    }
    if (match(TokenType::Identifier)) {
    std::string name = tokens[pos-1].lexeme;
    
    // --- SEMANTIC CHECK: Use of undefined variable ---
    if (!SymbolTable.isDefined(name)) {
        throw std::runtime_error("Semantic Error: Variable '" + name + "' used before declaration.");
    }
    
    return std::make_unique<VariableExprAST>(name);
}
    if (match(TokenType::LParen)) {
        auto expr = parseExpression();
        consume(TokenType::RParen, "Expect ')' after expression.");
        return expr;
    }
    throw std::runtime_error("Expect expression.");
}