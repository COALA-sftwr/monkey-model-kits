/*
 *  File:       StringManipulation.cpp
 *  Created:    Albert 04/04/2024
 *  Description: 
*/

#include <sstream>
#include "StringManipulation.hpp"

std::vector<std::string> tokenize(const std::string &s, char delimiter) {
    std::stringstream ss(s);
    std::string token;
    std::vector<std::string> value_t;

    while (getline(ss, token, delimiter))
        if (!token.empty())
            value_t.push_back(token);
    return value_t;
}

std::string cleanString(std::string& str) {
    const std::string charsToRemove = " \t\n\r\f\v\"{<>}";

    str.erase(0, str.find_first_not_of(charsToRemove)); // Remove leading and trailing whitespaces
    str.erase(str.find_last_not_of(charsToRemove) + 1);

    return str/*.substr(start, end - start + 1)*/;
}