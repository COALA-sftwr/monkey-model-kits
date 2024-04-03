/*
 *  File:       MonkeyCollection.cpp
 *  Created:    Albert 03/04/2024
 *  Description: 
*/

#include <iostream>
#include "MonkeyCollection.hpp"

void MonkeyCollection::newModel() { // TODO: make this function not use the constructor to fill the new model.
    _models.emplace_back();
}

std::ostream &operator<<(std::ostream &stream, const MonkeyCollection &collection) {
    int models = 0;

    for (MonkeyModel model : collection._models) {
        models++;
        stream << models << " : " << model.getName() << "\t";
    }
    stream << std::endl;

    return stream;
}

void MonkeyCollection::addModel(MonkeyModel model) {
    _models.push_back(model);
}
