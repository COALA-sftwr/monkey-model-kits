/*
 *  File:       MonkeyCollection.hpp
 *  Created:    Albert 03/04/2024
 *  Description:    Functions regarding collection modification.
*/

#pragma once

#include <vector>
#include "MonkeyModel.hpp"


using Collection = std::vector<MonkeyModel>;

class MonkeyCollection {
    private:
        Collection _models;
        std::string _timeZone;
    public:
        void load(); // TODO: Implement the loading of existing collections from a file.
        void newModel();
        void addModel(MonkeyModel model);
        void setTimezone(std::string givenTimeZone);
        void clear();

        Collection getModels();
        Collection& getModelsAdr();
        std::string getTimeZone();

        friend std::ostream& operator<<(std::ostream& stream, const MonkeyCollection& collection);
};
