#include "Formatter.h"


/*
 * italicize - Returns the given string with italicized HTML where italicized markdown was used
 * itLine:  string line to be formatted with italicize
 */
string Formatter::italicize(string itLine)
{
    while (itLine.find("*") != string::npos || itLine.find("_"))
    {
        if (itLine.find("*") != string::npos && itLine.find("*") != itLine.find_last_of("*"))
        {
            itLine.replace(itLine.find("*"), 1, "<i>");
            itLine.replace(itLine.find_last_of("*"), 1, "</i>");
        }
        else if (itLine.find("_") != string::npos && itLine.find("_") != itLine.find_last_of("*"))
        {
            itLine.replace(itLine.find("_"), 1, "<i>");
            itLine.replace(itLine.find_last_of("_"), 1, "</i>");
        }
        else
        {
            return itLine;
        }
    }
    return itLine;
}

/*
 * boldify - Returns the given string with bold HTML where bold markdown was used
 * boldLine:    string line to be formatted with bold
 */
string Formatter::boldify(string boldLine)
{
    while (boldLine.find("**") != string::npos || boldLine.find("__") != string::npos)
    {
        if (boldLine.find("**") != string::npos && boldLine.find("**") != boldLine.find_last_of("**"))
        {
            boldLine.replace(boldLine.find("**"), 2, "<b>");
            boldLine.replace(boldLine.find_last_of("**") - 1, 2, "</b>");
        }
        else if (boldLine.find("__") != string::npos && boldLine.find("__") != boldLine.find_last_of("__"))
        {
            boldLine.replace(boldLine.find("__"), 1, "<b>");
            boldLine.replace(boldLine.find_last_of("__"), 1, "</b>");
        }
        else
        {
            return boldLine;
        }
    }
    return boldLine;
}

/*
 * trim - Removes leading and trailing whitespace from a given string
 * line: string line to be trimmed
 */
string Formatter::trim(string line)
{
    const char* WhiteSpace = " \t\v\r\n";
    size_t start = line.find_first_not_of(WhiteSpace);
    size_t end = line.find_last_not_of(WhiteSpace);
    return start == end ? string() : line.substr(start, end - start + 1);
}

/*
 * inlineCode - Returns the given string with inline code HTML where inline code markdown was used
 * line:    string line to be formatted with inline code
 */
string Formatter::inlineCode(string line)
{
    while (line.find("`") != string::npos)
    {
        if (line.find("`") != string::npos && line.find("`") != line.find_last_of("`"))
        {
            line.replace(line.find("`"), 1, "<code>");
            line.replace(line.find("`"), 1, "</code>");
        }
        else
        {
            return line;
        }
    }
    return line;
}