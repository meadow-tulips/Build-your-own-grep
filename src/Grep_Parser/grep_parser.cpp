#include "grep_parser.hpp"
#include <iostream>
#include <vector>
#include <cctype>

std::vector<std::string> parseExpressionPattern(std::string expression);
int doesStringContainsNumber(const std::string &s);
int doesStringContainsAlphaNumericCharacter(const std::string &s);
int doesStringContainsPositiveCharacterGroups(const std::string input_value, const std::string grp);
int doesStringContainsNegativeCharacterGroups(const std::string input_line, const std::string grp);
bool doesStringContainsMatchedPattern(const std::string input_line, const std::string v);

GREP::GREP_PARSER::GREP_PARSER(std::string exp) { expression = exp; }

bool GREP::GREP_PARSER::match_pattern(const std::string &input_line)
{

    if (expression.length() == 1)
    {
        return input_line.find(expression) != std::string::npos;
    }
    else
    {
        if (expression == "\\d")
        {
            return doesStringContainsNumber(input_line) < 0 ? 0 : 1;
        }
        else if (expression == "\\w")
        {
            return doesStringContainsAlphaNumericCharacter(input_line) < 0 ? 0 : 1;
        }
        else if (expression[0] == '[' && expression[expression.length() -  1] == ']')
        {
            if (expression[1] == '^')
                return doesStringContainsNegativeCharacterGroups(input_line, expression) < 0 ? 0 : 1;
            return doesStringContainsPositiveCharacterGroups(input_line, expression) < 0 ? 0 : 1;
        }
        return doesStringContainsMatchedPattern(input_line, expression);
    }
}

std::vector<std::string> parseExpressionPattern(std::string expression)
{

    std::vector<std::string> tokens;
    std::string token{""};
    for (int i = 0; i < expression.length(); i++)
    {
        int asci_value = expression[i];
        if (asci_value == 92 || asci_value == 91)
        {
            if (token.length())
                tokens.push_back(token);
            token = "";
        }

        if (asci_value == 93)
        {
            token += expression[i];
            tokens.push_back(token);
        }

        token += expression[i];
    }

    if (token.length())
        tokens.push_back(token);

    return tokens;
}

int doesStringContainsNumber(const std::string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]))
            return i;
    }
    return -1;
}

int doesStringContainsAlphaNumericCharacter(const std::string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (isalnum(s[i]))
            return i;
    }
    return -1;
}

int doesStringContainsPositiveCharacterGroups(const std::string input_line, const std::string grp)
{
    for (int i = 1; i < grp.length() - 1; i++)
    {
        if (input_line.find(grp[i]) != std::string::npos)
            return i;
    }

    return -1;
}

int doesStringContainsNegativeCharacterGroups(const std::string input_line, const std::string grp)
{
    std::string grpstring = grp.substr(2, grp.length() - 3);
    for (int i = 0; i < input_line.length(); i++)
    {
        if (grpstring.find(input_line[i]) == std::string::npos)
            return i;
    }

    return -1;
}

bool doesStringContainsMatchedPattern(const std::string input_line, const std::string expression)
{
    auto v = parseExpressionPattern(expression);
    return 0;
}