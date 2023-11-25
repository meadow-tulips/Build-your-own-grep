#include "grep_parser.hpp"
#include <iostream>
#include <vector>
#include <cctype>

std::vector<std::string> parseExpressionPattern(std::string expression);
bool doesStringContainsNumber(const std::string &s);
bool doesStringContainsAlphaNumericCharacter(const std::string &s);

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
        if (asci_value == 92)
        {
            if (token.length())
                tokens.push_back(token);
            token = "";
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