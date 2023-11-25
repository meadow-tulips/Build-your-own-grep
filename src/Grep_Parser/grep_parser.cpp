#include "grep_parser.hpp"
#include <iostream>
#include <vector>
#include <cctype>

std::vector<std::string> parseExpressionPattern(std::string expression);
bool doesStringContainsNumber(const std::string &s);
bool doesStringContainsAlphaNumericCharacter(const std::string &s);
bool doesStringContainsPositiveCharacterGroups(const std::string input_value, const std::string grp);

GREP::GREP_PARSER::GREP_PARSER(std::string exp) { expression = exp; }

bool GREP::GREP_PARSER::match_pattern(const std::string &input_line)
{

    if (expression.length() == 1)
    {
        return input_line.find(expression) != std::string::npos;
    }
    else
    {
        auto v = parseExpressionPattern(expression);
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i] == "\\d")
            {
                return doesStringContainsNumber(input_line);
            }
            else if (v[i] == "\\w")
            {
                return doesStringContainsAlphaNumericCharacter(input_line);
            }
            else if (v[i][0] == '[' && v[i][v[i].length() - 1] == ']')
            {
                return doesStringContainsPositiveCharacterGroups(input_line, v[i]);
            }
            else
            {
                throw std::runtime_error("Unhandled pattern " + v[i]);
            }
        }
        return 0;
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

bool doesStringContainsNumber(const std::string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]))
            return true;
    }
    return false;
}

bool doesStringContainsAlphaNumericCharacter(const std::string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (isalnum(s[i]))
            return true;
    }
    return false;
}

bool doesStringContainsPositiveCharacterGroups(const std::string input_line, const std::string grp)
{
    for (int i = 1; i < grp.length() - 1; i++)
    {
        if (input_line.find(grp[i]) != std::string::npos)
            return true;
    }

    return false;
}