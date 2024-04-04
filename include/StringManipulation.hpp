/*
 *  File:       StringManipulation.hpp
 *  Created:    Albert 04/04/2024
 *  Description:    File for editing strings.
*/

#pragma once

#include <vector>
#include <string>

std::vector<std::string> tokenize(const std::string& s, char delimiter);
std::string cleanString(std::string& str);