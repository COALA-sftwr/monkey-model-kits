/*
 *  File:       MonkeyCollection.cpp
 *  Created:    Albert 03/04/2024
 *  Description:    Functions regarding collection modification.
*/

#include <iostream>
#include "MonkeyCollection.hpp"

void MonkeyCollection::newModel() {
    MonkeyModel model_t;

    model_t.newModel();
    _models.push_back(model_t);
}

std::ostream &operator<<(std::ostream &stream, const MonkeyCollection &collection) {
    int models = 0;

    for (MonkeyModel model : collection._models) {
        models++;
        stream << models << " : " << model.getName() << "\t";
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
