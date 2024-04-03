/*
 *  File:       MonkeyCollection.hpp
 *  Created:    Albert 03/04/2024
 *  Description: 
*/

#pragma once

#include <vector>
#include "MonkeyModel.hpp"

using Collection = std::vector<MonkeyModel>;

class MonkeyCollection {
    private:
        Collection _models;
    public:
        void load(); // TODO: Implement the loading of existing collections from a file.
        void newModel();
        void addModel(MonkeyModel model);

        friend std::ostream& operator<<(std::ostream& stream, const MonkeyCollection& collection);
};
