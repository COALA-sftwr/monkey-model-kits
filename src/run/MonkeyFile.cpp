/*
 *  File:       MonkeyFile.cpp
 *  Created:    Albert 03/04/2024
 *  Description: 
*/

#include "MonkeyManager.hpp"
#include "StringManipulation.hpp"

std::string MonkeyManager::findKey(const std::string &key, int iteration) {
    std::string line;
    std::string value;
    int foundCount = 0;

    _file.seekg(0);

    while (std::getline(_file, line)) {
        // Check if the line contains the key
        size_t pos = line.find(key);
        if (pos != std::string::npos) {
            if (foundCount == iteration) {
                value = line.substr(pos + key.length() + 2); // Skip key and ": "
                return cleanString(value);
            }
            foundCount++;
        }
    }

    // Return empty string if key is not found or iteration is not found
    return "";
}

MonkeyModel MonkeyManager::findModel(int model_number) {
    MonkeyModel model_t;

    model_t.setName(findKey("name", model_number));
    model_t.setGrade(stoe((findKey("grade", model_number)), gradeMap));
    model_t.setPrice(stod(findKey("price", model_number)));
    model_t.setStatus(stoe(findKey("status", model_number), statusMap));
    model_t.setSessions(stoms_v(findKey("sessions", model_number)));

    return model_t;
}

void MonkeyManager::setTimeZones(MonkeyCollection& collection) {
    for (auto model : collection.getModels())
        for (auto session : model.getSessions())
            session.setTimeZone(collection.getTimeZone());
}

void MonkeyManager::loadFile(MonkeyCollection& collection) {
    std::string line;
    MonkeyModel model;
    int modelCount = 0;

    for (int i = 0; i <= 2; i++) {
        std::getline(_file, line);
        if (i == 1) {
            modelCount = stoi(line);
        } else if (i == 2) {
            size_t pos = line.find("UTC");
            if (pos != std::string::npos) {
                collection.setTimezone(line.substr(pos));
            }
        }
    }

    for (int modelsAdded = 0; modelsAdded != modelCount; modelsAdded++) {
        collection.addModel(findModel(modelsAdded));
    }
    setTimeZones(collection);
}
