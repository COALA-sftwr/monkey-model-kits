//
// Created by galbert on 17/06/23.
//

#pragma once

#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include "ModelTime.hpp"

using namespace std;

const char* const GRADE[] = {"EG", "SD", "HG", "RG", "MG", "PG", "MZ", "OG", "ST"};

class Models {
    public:
        enum Grade {EG, SD, HG, RG, MG, PG, MZ, OG, ST};
        enum Status {WL, BL, BD};

        Models();
        void Models::generate();
        void setName(string name);
        void setGrade(string input);
        void setPrice(const string& input);
        string getName();
        Grade getGrade();
        double getPrice();
        Models::Grade stGrade(string input);

    private:
        std::string _name;
        Grade _grade;
        tm *_tTime;
        int _sessions;
        ModelTime *_sTime;
        double _price;
        Status _status;

};
