//
// Created by Yorben on 05/12/2022.
//

#include <sstream>
#include <vector>
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
    int i = 0;
    bool isValid = true;
    // Predecessor
    // Zolang het nog steeds valid is en we nog niet het einde van de productie bereikt hebben gaan we verder
    while (isValid and i < production.Predecessor.size()) {
        // We kijken of de productiewaarde op index i bestaat in alphabet
        // Moeten omvormen naar een string want dit is wat de methode verwacht
        // Ik zou ook de find methode kunnen gebruiken, maar ze hebben beide constant complexity on average en worst case lineair in the size of the container, dus het maakt niet uit
        if (alphabet.count(std::string(1, production.Predecessor[i])) == 0) {
            // Zoniet wordt isValid false
            isValid = false;
            // Zoja gaan we index omhoog
        } else {
            i++;
        }
    }
    // Zetten terug op 0 voor de volgende loop
    i = 0;

    // Successor
    while (isValid and i < production.Successor.size()) {
        // We kijken of de productiewaarde op index i bestaat in alphabet
        // Moeten omvormen naar een string want dit is wat de methode verwacht
        if (alphabet.count(std::string(1, production.Successor[i])) == 0) {
            // Zoniet wordt isValid false
            isValid = false;
            // Zoja gaan we index omhoog
        } else {
            i++;
        }
    }
    return isValid;
}
template<typename SymbolType>
LSystemInterpreter<SymbolType>::LSystemInterpreter(const std::vector<SymbolType> &axiom,
                                                   const std::unordered_set<Production<SymbolType>> &productions,
                                                   const std::unordered_set<SymbolType> &alphabet) {
    // Check if all productions are valids
    for (int i = 0; i < productions.size(); i++) {
        bool isValid = Production<SymbolType>::isValidProduction(productions[i], alphabet);
        if (not isValid) {
            throw std::logic_error("Production contains symbols not declared in the alphabet");
        }
    }
    // Check if each production has a unique predecessor
    // Als dit niet werkt, elke predecessor in een nieuwe unordered set kopieren en hierop count uitoefenen, zou wel n square duren
    for (int i = 0; i < productions.size(); i++) {
        if (productions.count(productions[i][0]) != 0) {
            throw std::logic_error("Some productions do not have a unique predecessor");
        }
    }
    // Check if there is a production for each symbol in the alphabet
    for ()
}

// String constructor voor Production
template<typename SymbolType>
Production<SymbolType>::Production(std::string Predecessor,  std::string Successor): Predecessor(Predecessor), Successor(Successor){}

// Expliciete string instantiering van heel de Production klasse
template class Production<std::string>;
