/*
 *  File:       MonkeyFile.cpp
 *  Created:    Albert 03/04/2024
 *  Description:    Functions for Mkit parsing
*/

#include <string>

#include "MonkeyManager.hpp"
#include "StringManipulation.hpp"
#include "MonkeyTime.hpp"

std::string MonkeyManager::findKey(const std::string &key, int iteration)
{
    std::string rValue;

    for (auto value : _stringVectors.at(iteration))
    {
        if (value.find(key) != std::string::npos)
        {
            size_t pos = value.find(key);
            rValue = value.substr(pos + key.length() + 2);
            return cleanString(rValue);
        }
    }
    return "";
}

MonkeyModel MonkeyManager::findModel(int model_number) {
    MonkeyModel model_t;

    model_t.setName(findKey("name", model_number));
    model_t.setGrade(stoe(findKey("grade", model_number), gradeMap));
    model_t.setPrice(stod(findKey("price", model_number)));
    model_t.setStatus(stoe(findKey("status", model_number), statusMap));
    model_t.setFavStatus(findKey("favorite", model_number) != "" ? stoi(findKey("favorite", model_number)) : false);
    if (model_t.getStatus() != BCK)
        model_t.setSessions(stoms_v(findKey("sessions", model_number)));

    return model_t;
}

/*void MonkeyManager::setTimeZones(MonkeyCollection& collection) {
    for (auto model : collection.getModels())
        for (auto session : model.getSessions())
            session.setTimeZone(collection.getTimeZone());
}*/

void MonkeyManager::loadFile(MonkeyCollection& collection) {
    std::string line;
    MonkeyModel model;
    int modelCount = 0;

    for (int i = 0; i <= 2; i++) {
        std::getline(_file, line);
        if (i == 1) {
            modelCount = stoi(line);
        } /*else if (i == 2) {
            size_t pos = line.find("UTC");
            if (pos != std::string::npos) {
                collection.setTimezone(line.substr(pos));
            }
        }*/
    }

    loadContent();

    for (int modelsAdded = 0; modelsAdded != modelCount; modelsAdded++) {
        collection.addModel(findModel(modelsAdded));
    }
    // setTimeZones(collection);
}

bool MonkeyManager::validLine(std::string str)
{
    return std::all_of(str.begin(), str.end(), [](char c) {
      return c == ' ' || c == '[' || c == ']';
    });
}

void MonkeyManager::loadContent()
{
    std::string line;

    while (!_file.eof())
    {
        std::getline(_file, line);
        if (line.find('[') != std::string::npos)
        {
            _stringVectors.push_back({});
            while (std::getline(_file, line))
            {
                if (line.find(']') != std::string::npos && validLine(line))
                    break;
                _stringVectors.back().push_back(cleanString(line));
            }
        }
    }
}
