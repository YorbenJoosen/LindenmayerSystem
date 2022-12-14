//
// Created by Yorben on 05/12/2022.
//

#pragma once

#include <unordered_set>
#include <string>


template <typename SymbolType>
class Production
{
public:
    // Need to declare these here otherwise we can't acces them in the function
    std::vector<SymbolType> Predecessor;
    std::vector<SymbolType> Successor;

    // Constructor
    Production(std::vector<SymbolType> Predecessor, std::vector<SymbolType> Successor);

    // const behind means that the class function can't change a member variable of the class
    bool isValidProduction(
            const Production<SymbolType>& production,
            const std::unordered_set<SymbolType>& alphabet
    ) const;

    // == nodig voor unordered set hashing
    bool operator==(const Production &rhs) const;

    // != nodig voor unordered set hashing
    bool operator!=(const Production &rhs) const;
};

// Custom hashing for unordered_set because the built-in hashing won't work with SymbolType
template <typename SymbolType, template<typename> typename ProductionType = Production>
struct custom_hash {
    std::size_t operator() (const ProductionType<SymbolType>& toBeHashed) const {
        std::size_t hash;
        std::hash<SymbolType> SymbolTypeHash;
        for (const auto& item : toBeHashed.Successor)
            hash ^= SymbolTypeHash(item);
        for (const auto& item : toBeHashed.Predecessor)
            hash ^= SymbolTypeHash(item);
        return hash;
    }
};

template <typename SymbolType>
class LSystemInterpreter
{
public:
    // Need to declare these here otherwise we can't acces them in the function
    std::vector<SymbolType> axiom;
    std::unordered_set<Production<SymbolType>, custom_hash<SymbolType>> productions;
    std::unordered_set<SymbolType>alphabet;
    // Constructor
    LSystemInterpreter(
            const std::vector<SymbolType>& axiom,
            const std::unordered_set<Production<SymbolType>, custom_hash<SymbolType>>& productions,
            const std::unordered_set<SymbolType>& alphabet
    );
    // Generate function
    std::vector<SymbolType> generate(unsigned long iterations);
};




