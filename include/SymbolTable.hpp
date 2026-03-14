#pragma once
#include <string>
#include <unordered_map>
#include <stdexcept>

struct Symbol {
    std::string name;
    std::string type; // e.g., "int"
};

class SymbolTable {
public:
    void define(const std::string& name, const std::string& type) {
        if (symbols.find(name) != symbols.end()) {
            throw std::runtime_error("Semantic Error: Variable '" + name + "' already defined.");
        }
        symbols[name] = {name, type};
    }

    bool isDefined(const std::string& name) {
        return symbols.find(name) != symbols.end();
    }

private:
    std::unordered_map<std::string, Symbol> symbols;
};