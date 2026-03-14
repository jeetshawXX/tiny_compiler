#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <vector>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
};

class NumberExprAST : public ASTNode {
    int Val;
public:
    NumberExprAST(int Val) : Val(Val) {}
    void print(int indent) const override {
        for (int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << "Number: " << Val << std::endl;
    }
};

class VariableExprAST : public ASTNode {
    std::string Name;
public:
    VariableExprAST(const std::string &Name) : Name(Name) {}
    void print(int indent) const override {
        for (int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << "Variable: " << Name << std::endl;
    }
};

class BinaryExprAST : public ASTNode {
    char Op;
    std::unique_ptr<ASTNode> LHS, RHS;
public:
    BinaryExprAST(char Op, std::unique_ptr<ASTNode> LHS, std::unique_ptr<ASTNode> RHS)
        : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

    void print(int indent) const override {
        for (int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << "BinaryOp: " << Op << std::endl;
        LHS->print(indent + 1);
        RHS->print(indent + 1);
    }
};

class VarDeclAST : public ASTNode {
    std::string Name;
    std::unique_ptr<ASTNode> InitValue;
public:
    VarDeclAST(const std::string &Name, std::unique_ptr<ASTNode> InitValue)
        : Name(Name), InitValue(std::move(InitValue)) {}

    void print(int indent) const override {
        for (int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << "VarDecl: " << Name << std::endl;
        if (InitValue) InitValue->print(indent + 1);
    }
};