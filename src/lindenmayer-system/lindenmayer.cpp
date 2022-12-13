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
                                                   const std::unordered_set<SymbolType> &alphabet): axiom(axiom), productions(productions), alphabet(alphabet) {
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
    // How it works: I have a vector of vectors. I do this because I can then easily loop over this vector of vectors and check a vector against the predecessor.
    // If this vector has already been changed it will not be equal. This is so that we can do multiple productions without accidently changing a symbol that came out of a production.
    // After I ran through a whole a production I get out all the data of each vector in the vector of vectors and put it into a vector of single symbols.
    // This one is only used, so I can get a vector of vectors with only one symbol in each vector again, I copy this data over to the vector of vectors.
    // I then put each symbol in a vector inside the vector of vectors, so it's usable for the next iteration.
    // It's a complicated way, but this assures that it works for each SymbolType


    // Create a CopyVector which is a vector of vectors and will be used to store the new string
    std::vector<std::vector<SymbolType>> CopyVector;
    // Create a SingleSymbolVector
    std::vector<SymbolType> SingleSymbolVector;
    // Put the axiomvector into the CopyVector
    CopyVector.push_back(axiom);
    // We iterate as many times as needed
    for (unsigned long i = 0; i < iterations; i++) {
        // Loop through all the productions
        for (const Production<SymbolType> &production: productions) {
            // Loop over the CopyVector
            for (int j = 0; j < CopyVector.size(); j++) {
                // Check if the Vector in CopyVector equals the PredecessorVector
                if (CopyVector[j] == production.Predecessor) {
                    // If it does we clear Vector of CopyVector, so we can put the new data inside it
                    CopyVector[j].clear();
                    // We loop over all the Symbols in the SuccessorVector
                    for (const SymbolType& SuccessorSymbol: production.Successor) {
                        // We put the Symbol in the Vector of CopyVector
                        CopyVector[j].push_back(SuccessorSymbol);
                    }
                }
            }
        }
        // Clear the SingleSymbolVector so it's usable
        SingleSymbolVector.clear();
        // Loop over all the Vectors in CopyVector
        for (const std::vector<SymbolType>& CopyVectorVector: CopyVector) {
            // Loop over all the symbols in the Vector of CopyVector
            for (const SymbolType& VectorSymbol: CopyVectorVector) {
                // Put this symbol in the SingleSymbolVector
                SingleSymbolVector.push_back(VectorSymbol);
            }
        }
        // Clear the CopyVector so it's usable
        CopyVector.clear();
        // Loop over all the Symbols in SingleSymbolVector
        for (const SymbolType& SingleSymbolVectorSymbol: SingleSymbolVector) {
            // We put the Symbol in a Vector
            std::vector<SymbolType> SymbolAsVector = {SingleSymbolVectorSymbol};
            // This Vector we put into the CopyVector
            CopyVector.push_back(SymbolAsVector);
        }
    }
    // After we ran through all the iterations we return the SingleSymbolVector
    return SingleSymbolVector;
}

// Constructor for Production
template<typename SymbolType>
Production<SymbolType>::Production(std::vector<SymbolType> Predecessor,  std::vector<SymbolType> Successor): Predecessor(Predecessor), Successor(Successor){}

// Explicit string instantation for Production class
template class Production<std::string>;

// Explicit int instantation for Production class
template class Production<int>;

// Explicit string instantation for LSystemInterpreter class
template class LSystemInterpreter<std::string>;

// Explicit int instantation for LSystemInterpreter class
template class LSystemInterpreter<int>;


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

