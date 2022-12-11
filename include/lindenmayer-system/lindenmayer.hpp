//
// Created by Yorben on 05/12/2022.
//

#pragma once

#include <unordered_set>
#include <string>


template <typename SymbolType>
class Production
{
private:
    SymbolType Predecessor;
    SymbolType Successor;
public:
    // String
    Production(std::string Predecessor, std::string Successor);

    // const behind means that the class function can't change a member variable of the class
    bool isValidProduction(
            const Production<SymbolType>& production,
            const std::unordered_set<SymbolType>& alphabet
    ) const;
};

template <typename SymbolType>
class LSystemInterpreter
{
public:
    LSystemInterpreter(
            const std::vector<SymbolType>& axiom,
            const std::unordered_set<Production<SymbolType>>& productions,
            const std::unordered_set<SymbolType>& alphabet
    );
};



