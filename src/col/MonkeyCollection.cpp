/*
 *  File:       MonkeyCollection.cpp
 *  Created:    Albert 03/04/2024
 *  Description:    Functions regarding collection modification.
*/

#include <iostream>
#include "MonkeyCollection.hpp"

#include <sstream>

void MonkeyCollection::newModel() {
    MonkeyModel model_t;

    model_t.newModel();
    _models.push_back(model_t);
}

std::ostream &operator<<(std::ostream &stream, const MonkeyCollection &collection) {
    int models = 0;
    int space = 0;

    for (MonkeyModel model : collection._models) {
        models++;
        stream << models << ": " << model.getName() << "\t";
        if (space == 4) {
            space = 0;
            std::cout << std::endl;
        } else
            space++;
    }

    return stream;
}

void MonkeyCollection::addModel(MonkeyModel model) {
    _models.push_back(model);
}

void MonkeyCollection::setTimezone(std::string givenTimeZone) {
    _timeZone = givenTimeZone;
}

Collection MonkeyCollection::getModels() {
    return _models;
}

std::string MonkeyCollection::getTimeZone() {
    return _timeZone;
}

Collection& MonkeyCollection::getModelsAdr() {
    return _models;
}

void MonkeyCollection::clear() {
    _models.clear();
    _timeZone.clear();
}

std::string MonkeyCollection::save() {
    std::stringstream file_s;

    file_s << "  " << count() << std::endl;
    file_s << "  " << "time: " << _timeZone << std::endl;

    for (auto model : _models) {
        file_s << "    " << "[" << std::endl;
        file_s << "      " << "name: " << model.getName() << std::endl;
        file_s << "      " << "grade: " << etos(gradeMap, model.getGrade()) << std::endl;
        file_s << "      " << "price: " << model.getPrice() << std::endl;
        file_s << "      " << "status: " << etos(statusMap, model.getStatus()) << std::endl;
        file_s << "      " << "sessions: " << model.saveSessions() << std::endl;
        file_s << "    " << "]" << std::endl;
    }
    //std::cout << file_s.str() << std::endl;
    return file_s.str();
}

MonkeyModel *MonkeyCollection::findLastModel() {
    MonkeyModel *modelOutLoop = &_models.at(0);

    for (auto& modelInLoop : _models) {
        MonkeySession *modelOLSession = modelOutLoop->getLastSession();
        MonkeySession *modelILSession = modelInLoop.getLastSession();
        if (modelOLSession == nullptr && modelILSession != nullptr ||
            modelOLSession != nullptr && modelILSession != nullptr && modelOLSession->getStop() < modelILSession->getStop())
            modelOutLoop = &modelInLoop;
    }
    return modelOutLoop;
}

int MonkeyCollection::count() {
    return _models.size();
}
