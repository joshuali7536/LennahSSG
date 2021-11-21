//#define CATCH_CONFIG_MAIN

#include <iostream>
#include <fstream>
#include <string>
#include "catch.hpp"
#include "Formatter.h"
#include "Config.h"

void inputManager(string input, string output);

bool filesMatch(string filePath1, string filePath2)
{
    std::ifstream file1(filePath1);
    std::ifstream file2(filePath2);

    if (file1.fail() || file2.fail())
    {
        return false;
    }

    if (file1.tellg() != file2.tellg())
    {
        return false;
    }

    file1.seekg(0, std::ifstream::beg);
    file2.seekg(0, std::ifstream::beg);

    return std::equal(std::istreambuf_iterator<char>(file1.rdbuf()), std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(file2.rdbuf()));
}

TEST_CASE("Italicize function", "[italics]")
{
    Formatter test;
    SECTION("Strings with * markdown")
    {
        REQUIRE(test.italicize("*Hello World*") == "<i>Hello World</i>");
        REQUIRE(test.italicize("*Testing 123*") == "<i>Testing 123</i>");
    }
    SECTION("String with _ markdown")
    {
        REQUIRE(test.italicize("_This is a sentence_") == "<i>This is a sentence</i>");
    }
    SECTION("Empty string")
    {
        REQUIRE(test.italicize("") == "");
    }
    SECTION("String with one *")
    {
        REQUIRE(test.italicize("*Hello World") == "*Hello World");
    }
    SECTION("String with one _")
    {
        REQUIRE(test.italicize("_Hello World") == "_Hello World");
    }
}

TEST_CASE("Boldify function", "[bold]")
{
    Formatter test;
    SECTION("Strings with ** markdown")
    {
        REQUIRE(test.boldify("**Hello World**") == "<b>Hello World</b>");
        REQUIRE(test.boldify("**Testing 123**") == "<b>Testing 123</b>");
    }
    SECTION("String with _ markdown")
    {
        REQUIRE(test.boldify("__This is a sentence__") == "<b>This is a sentence</b>");
    }
    SECTION("Empty string")
    {
        REQUIRE(test.boldify("") == "");
    }
    SECTION("String with one **")
    {
        REQUIRE(test.boldify("**Hello World") == "**Hello World");
    }
    SECTION("String with one __")
    {
        REQUIRE(test.boldify("__Hello World") == "__Hello World");
    }
}

TEST_CASE("Inline Code function", "[code]")
{
    Formatter test;
    SECTION("Strings with ` markdown")
    {
        REQUIRE(test.inlineCode("`Hello World`") == "<code>Hello World</code>");
        REQUIRE(test.inlineCode("`Testing 123`") == "<code>Testing 123</code>");
    }
    SECTION("Empty string")
    {
        REQUIRE(test.inlineCode("") == "");
    }
    SECTION("String with one `")
    {
        REQUIRE(test.inlineCode("`Hello World") == "`Hello World");
    }
}

TEST_CASE("Config File reader", "[config]")
{

    SECTION("Check config reads properly")
    {
        Config config;
        config.readConfig("./test/testConfig.json");
        REQUIRE(config.getInput() == "Silver Blaze.txt");
        REQUIRE(config.getOutput() == "build/");
        REQUIRE(config.getFileType() == 1);
    }
    SECTION("Check config reads properly with folder input")
    {
        Config config;
        config.readConfig("./test/testConfigFolder.json");
        REQUIRE(config.getInput() == "Folder 1");
        REQUIRE(config.getOutput() == "build/");
    }
    SECTION("Check config with md input")
    {
        Config config;
        config.readConfig("./test/testConfigMD.json");
        REQUIRE(config.getInput() == "TestMarkdown.md");
        REQUIRE(config.getOutput() == "build/");
        REQUIRE(config.getFileType() == 2);
    }
}

TEST_CASE("Trim Whitespace function", "[trim]")
{
    Formatter test;
    SECTION("Strings with front and back whitespace")
    {
        REQUIRE(test.trim("         Hello World            ") == "Hello World");
    }
    SECTION("Empty string")
    {
        REQUIRE(test.trim("") == "");
    }
    SECTION("String with only front whitespace")
    {
        REQUIRE(test.trim("       Hello World") == "Hello World");
    }
    SECTION("String with only back whitespace")
    {
        REQUIRE(test.trim("Hello World          ") == "Hello World");
    }
    SECTION("String with no extra whitespace")
    {
        REQUIRE(test.trim("Hello World") == "Hello World");
    }
}

TEST_CASE("E2E", "[E2E]")
{
    SECTION("Check if TXT file matches snapshot")
    {
        inputManager("./test/test.txt", "./test/output/");
        REQUIRE(filesMatch("./test/output/test.html", "./test/snapshotTXT.html"));
    }
    SECTION("Check if MD file matches snapshot")
    {
        inputManager("./test/test.md", "./test/output/");
        REQUIRE(filesMatch("./test/output/test.html", "./test/snapshotMD.html"));
    }
}
