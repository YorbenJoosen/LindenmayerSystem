//
// Created by Yorben on 05/12/2022.
//

#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "lindenmayer-system/lindenmayer.hpp"

// This function verifies that all symbols in the production
// (Predecessor and all symbols in the successor) are
// in the given alphabet.
// If all symbols are in the alphabet, this function returns true,
// otherwise, this function returns false.
template <typename SymbolType>
bool Production<SymbolType>::isValidProduction(
        const Production<SymbolType>& production,
        const std::unordered_set<SymbolType>& alphabet
) const
{
    // Variables
    int i = 0;
    bool isValid = true;
    // Predecessor
    // Check if the predecessor only has 1 element
    if (production.Predecessor.size() == 1) {
        // If it does we check if the symbol exists in the alphabet
        // I could also use the find method, but the time complexity is equal to this one
        if (alphabet.count(production.Predecessor[0]) == 0) {
            isValid = false;
        }
    } else {
        isValid = false;
    }

    // Successor
    while (isValid and i < production.Successor.size()) {
        // Check if the successor symbol exists in the alphabet
        if (alphabet.count(production.Successor[i]) == 0) {
            // If not isValid becomes false
            isValid = false;
            // If it does we go an index higher
        } else {
            i++;
        }
    }
    // We return the isValid
    return isValid;
}

//LSystemInterpreter costructor
template<typename SymbolType>
LSystemInterpreter<SymbolType>::LSystemInterpreter(const std::vector<SymbolType> &axiom,
                                                   const std::unordered_set<Production<SymbolType>, custom_hash<SymbolType>> &productions,
                                                   const std::unordered_set<SymbolType> &alphabet) {
    // Check if all productions are valids
    // We go through all the productions
    for (const Production<SymbolType>& production: productions) {
        bool isValid = production.isValidProduction(production, alphabet);
        if (not isValid) {
            throw std::logic_error("Production contains symbols not declared in the alphabet, or the predecessor contains more than one symbol!");
        }
    }

    // Make an unordered set, so we can put all the unique predecessors into it
    std::unordered_set<SymbolType> Predecessors = {};

    // Go through all productions and copy the predecessor into the unordered set of predecessors
    for (const Production<SymbolType>& production: productions) {
        Predecessors.insert(production.Predecessor[0]);
    }

    // Check if each production has a unique predecessor
    // Since unordered_set does not allow duplicates to be inserted we can check if the size is equal to the size of productions
    if (Predecessors.size() != productions.size()) {
        throw std::logic_error("Some productions do not have a unique predecessor");

    }

    // Check if there is a production for each symbol in the alphabet
    for (const SymbolType& symbol: alphabet) {
        if (Predecessors.count(symbol) == 0) {
            throw std::logic_error("Not each symbol in the alphabet has a production");
        }
    }
}

template<typename SymbolType>
std::vector<SymbolType> LSystemInterpreter<SymbolType>::generate(unsigned long iterations) {
    return std::vector<SymbolType>();
}

// Constructor for Production
template<typename SymbolType>
Production<SymbolType>::Production(std::vector<SymbolType> Predecessor,  std::vector<SymbolType> Successor): Predecessor(Predecessor), Successor(Successor){}

// Explicit string instantation for Production class
template class Production<std::string>;

// Explicit int instantation for Production class
template class Production<int>;

// Explicit int instantation for LSystemInterpreter class
template class LSystemInterpreter<std::string>;


// == constructor
template<typename SymbolType>
bool Production<SymbolType>::operator==(const Production &rhs) const {
    return Predecessor == rhs.Predecessor &&
           Successor == rhs.Successor;
}

// != constructor
template<typename SymbolType>
bool Production<SymbolType>::operator!=(const Production &rhs) const {
    return rhs != *this;
}

