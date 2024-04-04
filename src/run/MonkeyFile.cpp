/*
 *  File:       MonkeyFile.cpp
 *  Created:    Albert 03/04/2024
 *  Description: 
*/

#include "MonkeyManager.hpp"
#include "StringManipulation.hpp"

std::string MonkeyManager::findKey(const std::string &key, int instance) {
    std::string line;
    std::string value;
    int foundCount = 0;

    _file.seekg(0);

    while (std::getline(_file, line)) {
        // Check if the line contains the key
        size_t pos = line.find(key);
        if (pos != std::string::npos) {
            if (foundCount == instance) {
                value = line.substr(pos + key.length() + 2); // Skip key and ": "
                return cleanString(value);
            }
            foundCount++;
        }
    }

    // Return empty string if key is not found or instance is not found
    return "";
}

MonkeyModel MonkeyManager::findModel(int model_number) {
    MonkeyModel model_t;

    model_t.setName(findKey("name", model_number));
    model_t.setGrade(stoe((findKey("grade", model_number)), gradeMap));
    model_t.setPrice(stod(findKey("price", model_number)));
    model_t.setStatus(stoe(findKey("status", model_number), statusMap));
//    model_t.setSessions(stoms(findKey("sessions", model_number)));

    return model_t;
}

void MonkeyManager::loadFile(MonkeyCollection& collection) {
    std::string line;
    MonkeyModel model;
    int modelCount = 0;

    for (int i = 0; i < 2; i++) {
        std::getline(_file, line);
        if (i == 1) {
            modelCount = stoi(line);
        }
    }

    for (int modelsAdded = 0; modelsAdded != modelCount; modelsAdded++) {
        collection.addModel(findModel(modelsAdded));
    }
}
