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
        void newModel();
        void addModel(MonkeyModel model);
        void setTimezone(std::string givenTimeZone);
        void clear();

        Collection getModels();
        Collection& getModelsAdr();
        std::string getTimeZone();

        int count();
        std::string save();

        friend std::ostream& operator<<(std::ostream& stream, const MonkeyCollection& collection);

        MonkeyModel *findLastModel();
};
