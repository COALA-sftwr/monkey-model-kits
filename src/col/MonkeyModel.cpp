/*
 *  File:       MonkeyModel.cpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the model kits modifications
*/

#include <iostream>
#include "MonkeyModel.hpp"

MonkeyModel::MonkeyModel() {
    std::string input;

    getUpperInput("\"What is the name of this model ?\"", input);
    setName(input);
    getUpperInput("What is its grade ?", input);
    setGrade(stoe(input, gradeMap));
    getUpperInput("What is its price ?", input);
    setPrice(!input.empty() ? stod(input) : 0.0);
    getUpperInput("Is it finished, work in progress or backlogged ? [WIP, BLT, BCK]", input);
    setStatus(stoe(input, statusMap));
}

void getUpperInput(std::string string, std::string &input) {
    std::cout << string << std::endl;
    getline(std::cin, input);

    for (char& c : input) {
        c = std::toupper(c);
    }
}

void MonkeyModel::newModel() {
    std::string input;

    getUpperInput("\"What is the name of this model ?\"", input);
    setName(input);
    getUpperInput("What is its grade ?", input);
    setGrade(stoe(input, gradeMap));
    getUpperInput("What is its price ?", input);
    setPrice(!input.empty() ? stod(input) : 0.0);
    getUpperInput("Is it finished, work in progress or backlogged ? [WIP, BLT, BCK]", input);
    setStatus(stoe(input, statusMap));
}

// Setters
void MonkeyModel::setName(std::string name) {
    _name = name;
}

void MonkeyModel::setGrade(Grade grade) {
    _grade = grade;
}

void MonkeyModel::setPrice(double price) {
    _price = price;
}

void MonkeyModel::setStatus(Status status) {
    _status = status;
}

// Getters
std::string MonkeyModel::getName() {
    return _name;
}

Grade MonkeyModel::getGrade() {
    return _grade;
}

double MonkeyModel::getPrice() {
    return _price;
}

Status MonkeyModel::getStatus() {
    return _status;
}

void MonkeyModel::addSession(MonkeySession session) {
    _sessions.push_back(session);
}

template <typename Enum> Enum stoe(const std::string& gradeString, const std::unordered_map<std::string, Enum>& enumMap)
{
    auto it = enumMap.find(gradeString);
    if (it != enumMap.end())
        return it->second;
    else
        throw std::invalid_argument("Invalid enum string representation");
}
