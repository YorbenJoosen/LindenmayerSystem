//
// Created by Yorben on 05/12/2022.
//

#include <catch2/catch.hpp>
#include "lindenmayer-system/lindenmayer.hpp"

TEST_CASE("isValid, string", "[isValid] [string]")
{
    const Production<std::string> production1("a", "ab");
    const Production<std::string> production2("ajewnnw", "adnscb");
    const std::unordered_set<std::string> alphabet = {"a", "b"};
    bool isValid1 = production1.isValidProduction(production1, alphabet);
    bool isValid2 = production2.isValidProduction(production2, alphabet);
    CHECK(isValid1 == true);
    CHECK(isValid2 == false);
}

TEST_CASE("Interpreter, string", "[interpreter] [string]") {
    const Production<std::string> production1("a", "ab");
    const Production<std::string> production2("ajewnnw", "adnscb");
    const std::unordered_set<Production<std::string>> productions = {production1, production2};
    const std::unordered_set<std::string> alphabet = {"a", "b"};
    const std::vector<std::string> axiom = {"a"};
    LSystemInterpreter<std::string> (axiom, productions, alphabet);
}