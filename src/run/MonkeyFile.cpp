/*
 *  File:       MonkeyFile.cpp
 *  Created:    Albert 03/04/2024
 *  Description: 
*/

#include "MonkeyManager.hpp"

void MonkeyManager::findName(std::string line, MonkeyModel model) {
    size_t pos = line.find("name:");

    if (pos != std::string::npos) {
        pos += 5; // Length of "name:"
        model.setName(line.substr(pos, line.find('"', pos + 1) - pos));
    }
}

void MonkeyManager::findGrade(std::string line, MonkeyModel model) {
    size_t pos = line.find("grade:");

    if (pos != std::string::npos) {
        pos += 6; // Length of "grade:"
        model.setGrade(stoe(line.substr(pos, line.find('>', pos + 1) - pos), gradeMap));
    }
}

void MonkeyManager::findPrice(std::string line, MonkeyModel model) {
    size_t pos = line.find("price:");

    if (pos != std::string::npos) {
        pos += 6; // Length of "price:"
        model.setPrice(std::stod(line.substr(pos)));
    }
}

void MonkeyManager::findStatus(std::string line, MonkeyModel model) {
    size_t pos = line.find("status:");

    if (pos != std::string::npos) {
        pos += 7; // Length of "status:"
        model.setStatus(stoe(line.substr(pos, line.find('>', pos + 1) - pos), statusMap));
    }
}

void MonkeyManager::findSessions(std::string line, MonkeyModel model) {
    size_t pos = line.find("sessions:");

    if (pos != std::string::npos) {
        pos += 9; // Length of "sessions:"
        std::string sessionStr = line.substr(pos, line.size() - pos);
        std::istringstream sessionIss(sessionStr);
        std::string session;
        while (std::getline(sessionIss, session, '|')) {
            MonkeySession monkey_Session;
            size_t pos1 = session.find('>');
            monkey_Session.setStart(stotp(session.substr(1, pos1 - 1)));
            monkey_Session.setStop(stotp(session.substr(pos1 + 1, session.size() - pos1 - 3)));
            model.addSession(monkey_Session);
        }
    }
}

/*void MonkeyManager::findKey(std::string key) {
    std::string line;

    while (std::getline(_file, line)) {

    }
}

void MonkeyManager::findModel() {
    while
}*/

void MonkeyManager::loadFile(MonkeyCollection Collection) {
    std::string line;
    MonkeyModel model;
    int modelCount = 0;

    for (int i = 0; i < 2; i++) {
        std::getline(_file, line);
        if (i == 1) {
            modelCount = stoi(line);
        }
    }

    for (modelCount; modelCount > 0; modelCount--) {
//        findModel();
    }

    while (std::getline(_file, line)) {
        if (line.empty() || line.front() != '[' || line.back() != ']')
            continue; // Skip lines that do not represent model entries

        // Parse model fields
        findName(line, model);
        findGrade(line, model);
        findPrice(line, model);
        findStatus(line, model);
        findSessions(line, model);

        Collection.addModel(model);
    }
}
