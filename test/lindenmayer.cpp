//
// Created by Yorben on 05/12/2022.
//

#include <catch2/catch.hpp>
#include "lindenmayer-system/lindenmayer.hpp"

TEST_CASE("isValid, string", "[isValid] [string]")
{
    const Production<std::string> production1({"a"}, {"a", "b"});
    const Production<std::string> production2({"a", "w", "q"}, {"a", "b", "c"});
    const std::unordered_set<std::string> alphabet = {"a", "b"};
    bool isValid1 = production1.isValidProduction(production1, alphabet);
    bool isValid2 = production2.isValidProduction(production2, alphabet);
    CHECK(isValid1 == true);
    CHECK(isValid2 == false);
}

TEST_CASE("isValid, int", "[isValid] [int]")
{
    const Production<int> production1({1}, {1, 2});
    const Production<int> production2({1, 2}, {1, 2, 3});;
    const std::unordered_set<int> alphabet = {1, 2};
    bool isValid1 = production1.isValidProduction(production1, alphabet);
    bool isValid2 = production2.isValidProduction(production2, alphabet);
    CHECK(isValid1 == true);
    CHECK(isValid2 == false);
}

TEST_CASE("Interpreter, string, wrong production", "[interpreter] [string] [wrong production]") {
    const Production<std::string> production({"a", "w", "q"}, {"a", "b", "c"});
    const std::unordered_set<std::string> alphabet = {"a", "b"};
    const std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production};
    const std::vector<std::string> axiom = {"a"};
    LSystemInterpreter<std::string> (axiom, productions, alphabet);
}

TEST_CASE("Interpreter, string, unique predecessor check", "[interpreter] [string] [unique predecessor check]") {
    const Production<std::string> production1({"a"}, {"a", "b"});
    const Production<std::string> production2({"a"}, {"a", "b"});
    const std::unordered_set<std::string> alphabet = {"a", "b"};
    const std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production1, production2};
    const std::vector<std::string> axiom = {"a"};
    LSystemInterpreter<std::string> (axiom, productions, alphabet);
}

TEST_CASE("Interpreter, string, alphabet check", "[interpreter] [string] [alphabet check]") {
    const Production<std::string> production1({"a"}, {"a", "b"});
    const Production<std::string> production2({"b"}, {"a", "b"});
    const std::unordered_set<std::string> alphabet = {"a", "b", "c"};
    const std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production1, production2};
    const std::vector<std::string> axiom = {"a"};
    LSystemInterpreter<std::string> (axiom, productions, alphabet);
}