//
// Created by Yorben on 05/12/2022.
//

#include <catch2/catch.hpp>
#include <iostream>
#include "lindenmayer-system/lindenmayer.hpp"

// Test isValid function
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
    const Production<int> production2({1, 2}, {1, 2, 3});
    const std::unordered_set<int> alphabet = {1, 2};
    bool isValid1 = production1.isValidProduction(production1, alphabet);
    bool isValid2 = production2.isValidProduction(production2, alphabet);
    CHECK(isValid1 == true);
    CHECK(isValid2 == false);
}


// Test throws
TEST_CASE("Interpreter, string, wrong production", "[interpreter] [string] [wrong production]") {
    const Production<std::string> production({"a", "w", "q"}, {"a", "b", "c"});
    const std::unordered_set<std::string> alphabet = {"a", "b"};
    const std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production};
    const std::vector<std::string> axiom = {"a"};
    CHECK_THROWS_WITH(LSystemInterpreter<std::string> (axiom, productions, alphabet), "Production contains symbols not declared in the alphabet, or the predecessor contains more than one symbol!");
}

TEST_CASE("Interpreter, string, unique predecessor check", "[interpreter] [string] [unique predecessor check]") {
    const Production<std::string> production1({"a"}, {"a", "b"});
    const Production<std::string> production2({"a"}, {"a", "b"});
    const std::unordered_set<std::string> alphabet = {"a", "b"};
    const std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production1, production2};
    const std::vector<std::string> axiom = {"a"};
    CHECK_THROWS_WITH(LSystemInterpreter<std::string> (axiom, productions, alphabet), "Some productions do not have a unique predecessor");
}

TEST_CASE("Interpreter, string, alphabet check", "[interpreter] [string] [alphabet check]") {
    const Production<std::string> production1({"a"}, {"a", "b"});
    const Production<std::string> production2({"b"}, {"a", "b"});
    const std::unordered_set<std::string> alphabet = {"a", "b", "c"};
    const std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production1, production2};
    const std::vector<std::string> axiom = {"a"};
    CHECK_THROWS_WITH(LSystemInterpreter<std::string> (axiom, productions, alphabet), "Not each symbol in the alphabet has a production");
}

// Test generate function
TEST_CASE("Interpreter, string, single alphabet check", "[interpreter] [string] [single alphabet check]") {
    const Production<std::string> production1({"F"}, {"F", "[", "+", "F", "]", "-", "F"});
    const Production<std::string> production2 ({"["}, {"["});
    const Production<std::string> production3 ({"+"}, {"+"});
    const Production<std::string> production4 ({"]"}, {"]"});
    const Production<std::string> production5 ({"-"}, {"-"});
    const std::unordered_set<std::string> alphabet = {"F", "+", "-", "[", "]"};
    const std::vector<std::string> axiom = {"F"};
    std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production1, production2, production3, production4, production5};
    LSystemInterpreter<std::string>  LSystemConstructed(axiom, productions, alphabet);
    std::vector<std::string> LSystem = LSystemConstructed.generate(2);
    std::string TestString;
    for (std::string& i : LSystem) {
        TestString.append(i);
    }
    CHECK(TestString == "F[+F]-F[+F[+F]-F]-F[+F]-F");
}

TEST_CASE("Interpreter, string, two alphabet check", "[interpreter] [string] [two alphabet check]") {
    const Production<std::string> production1({"A"}, {"A", "B"});
    const Production<std::string> production2 ({"B"}, {"B", "B"});
    const std::unordered_set<std::string> alphabet = {"A", "B"};
    const std::vector<std::string> axiom = {"A"};
    std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production1, production2};
    LSystemInterpreter<std::string>  LSystemConstructed(axiom, productions, alphabet);
    std::vector<std::string> LSystem = LSystemConstructed.generate(3);
    std::string TestString;
    for (std::string& i : LSystem) {
        TestString.append(i);
    }
    CHECK(TestString == "ABBBBBBB");
}

TEST_CASE("Interpreter, string, three alphabet check", "[interpreter] [string] [three alphabet check]") {
    const Production<std::string> production1({"A"}, {"A", "B", "B"});
    const Production<std::string> production2 ({"B"}, {"B", "B", "C", "C", "A", "C", "B"});
    const Production<std::string> production3 ({"C"}, {"A", "B", "C"});
    const std::unordered_set<std::string> alphabet = {"A", "B", "C"};
    const std::vector<std::string> axiom = {"A"};
    std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production1, production2, production3};
    LSystemInterpreter<std::string>  LSystemConstructed(axiom, productions, alphabet);
    std::vector<std::string> LSystem = LSystemConstructed.generate(3);
    std::string TestString;
    for (std::string& i : LSystem) {
        TestString.append(i);
    }
    CHECK(TestString == "ABBBBCCACBBBCCACBBBCCACBBBCCACBABCABCABBABCBBCCACBBBCCACBBBCCACBABCABCABBABCBBCCACB");
}

TEST_CASE("Interpreter, int, two alphabet check", "[interpreter] [int] [two alphabet check]") {
    const Production<int> production1({1}, {1, 2});
    const Production<int> production2 ({2}, {2, 2});
    const std::unordered_set<int> alphabet = {1, 2};
    const std::vector<int> axiom = {1};
    std::unordered_set<Production<int>, custom_hash<int>> productions = {production1, production2};
    LSystemInterpreter<int>  LSystemConstructed(axiom, productions, alphabet);
    std::vector<int> LSystem = LSystemConstructed.generate(3);
    std::vector<int> CheckVector = {1, 2, 2, 2, 2, 2, 2, 2};
    CHECK(LSystem == CheckVector);
}

// Test generate function
TEST_CASE("Stringbuilder for python", "[python]") {
    /*const Production<std::string> production1({"F"}, {"F", "[", "+", "F", "]", "-", "F"});
    const Production<std::string> production2 ({"["}, {"["});
    const Production<std::string> production3 ({"+"}, {"+"});
    const Production<std::string> production4 ({"]"}, {"]"});
    const Production<std::string> production5 ({"-"}, {"-"});
    const std::unordered_set<std::string> alphabet = {"F", "+", "-", "[", "]"};
    const std::vector<std::string> axiom = {"F"};
    std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production1, production2, production3, production4, production5};*/
    const Production<std::string> production1({"F"}, {"F", "+", "+", "F", "+", "+", "F", "+", "+", "+", "+", "+", "F", "-", "F", "+", "+", "F"});
    const Production<std::string> production2 ({"+"}, {"+"});
    const Production<std::string> production3 ({"-"}, {"-"});
    const std::unordered_set<std::string> alphabet = {"F", "+", "-"};
    const std::vector<std::string> axiom = {"F", "+", "+", "F", "+", "+", "F", "+", "+", "F", "+", "+", "F"};
    std::unordered_set<Production<std::string>, custom_hash<std::string>> productions = {production1, production2, production3};
    LSystemInterpreter<std::string> LSystemConstructed(axiom, productions, alphabet);
    std::vector<std::string> LSystem = LSystemConstructed.generate(4);
    std::string TestString;
    for (std::string& i : LSystem) {
        TestString.append(i);
    }
    std::cout << TestString;
}


