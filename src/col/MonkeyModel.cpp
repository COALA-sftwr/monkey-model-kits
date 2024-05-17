/*
 *  File:       MonkeyModel.cpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the model kits modifications
*/

#include <iostream>
#include "MonkeyModel.hpp"

#include <sstream>

MonkeyModel::MonkeyModel() {
    setSWStatus(false);
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

void MonkeyModel::setSessions(std::vector<MonkeySession> sessions) {
    _sessions = sessions;
}

void MonkeyModel::setSWStatus(bool newState) {
    _swOn = newState;
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

std::vector<MonkeySession> MonkeyModel::getSessions() {
    return _sessions;
}

MonkeySession *MonkeyModel::getLastSession() {
    MonkeySession *tempSession = nullptr;

    if (!_sessions.empty()) {
        tempSession = &_sessions.at(0);
        for (auto session : _sessions) {
            if (!session.getStopString().empty() && tempSession->getStopString().empty() ||
                !session.getStopString().empty() && !tempSession->getStopString().empty() && session.getStop() > tempSession->getStop())
                tempSession = &session;
        }
    }

    return tempSession;
}

int MonkeyModel::getNSessions() {
    int sessionNumber = 0;

    for (auto session : _sessions) {
        sessionNumber ++;
    }
    return sessionNumber;
}

bool MonkeyModel::isSWOn() {
    return _swOn;
}

// Others
void MonkeyModel::startSession() {
    _sessions.push_back(MonkeySession());
    _sessions.back().setStart();
    setSWStatus(true);
    setStatus(WIP);
}

void MonkeyModel::stopSession() {
    _sessions.back().setStop();
    setSWStatus(false);
}

std::ostream &operator<<(std::ostream &stream, const MonkeyModel &model) {
    stream << "Name: " << model._name << std::endl
           << "Grade: " << etos(gradeMap, model._grade) << std::endl
           << "Price: " << model._price << std::endl
           << "Status: " << etos(statusMap, model._status) << std::endl
           << "Sessions: ";

    if (model._sessions.empty())
        stream << "No sessions on this model." << std::endl;
    else {
        stream << std::endl;
        for (const auto &session: model._sessions) {
            stream << session << std::endl;
        }
    }
    return stream;
}

std::string MonkeyModel::saveSessions() {
    std::stringstream value_ss;
    std::vector<MonkeySession> vsess = getSessions();

    value_ss << "{ ";
    for (auto session = vsess.begin() ; session != vsess.end(); session++) {
        if (session->getStartString().empty() || session->getStopString().empty()) {
            auto hours = std::chrono::duration_cast<std::chrono::hours>(session->getDuration());
            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(session->getDuration()) - hours;
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(session->getDuration()) - hours - minutes;
            value_ss << "_" << hours.count() << ":" << minutes.count() << ":" << seconds.count();
        } else {
            value_ss << session->getStartString() << " > " << session->getStopString();
        }
        if (std::next(session) != vsess.end())
            value_ss << " | ";
    }
    value_ss << " }";

    return value_ss.str();
}

int MonkeyModel::getTime() {
    int time = 0;

    for (auto session : _sessions) {
        time += session.getDuration().count();
    }
    return time;
}

template <typename Enum>
Enum stoe(const std::string& gradeString, const std::unordered_map<std::string, Enum>& enumMap)
{
    auto it = enumMap.find(gradeString);
    if (it != enumMap.end())
        return it->second;
    else
        throw std::invalid_argument("Invalid enum string representation");
}

template <typename Enum>
std::string etos(const std::unordered_map<std::string, Enum>& enumMap, Enum value)
{
    for (const auto& pair : enumMap) {
        if (pair.second == value) {
            return pair.first;
        }
    }
    return "Unknown";
}

void getUpperInput(std::string string, std::string &input) {
    std::cout << string << std::endl;
    getline(std::cin, input);

    for (char& c : input) {
        c = std::toupper(c);
    }
}
