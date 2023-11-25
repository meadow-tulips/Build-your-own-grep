#include "grep_parser.hpp"
#include <iostream>
#include <vector>

std::vector<std::string> parseExpressionPattern(std::string expression);
bool doesStringContainsNumber(const std::string &s);

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
                auto t = doesStringContainsNumber(input_line);
                return doesStringContainsNumber(input_line);
            }
            else
            {
                throw std::runtime_error("Unhandled pattern " + v[i]);
            }
        }
        return -1;
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
        int asci_value = s[i];
        if (s[i] > 47 && s[i] < 58)
        {
            return true;
        }
    }
    return false;
}