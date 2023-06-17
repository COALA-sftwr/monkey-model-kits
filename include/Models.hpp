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

class Models {
    public:
        enum Grade {EG, SD, HG, RG, MG, PG, MZ, OG, ST};
        enum Status {WL, BL, BD};

        Models();
        void setName(string name);
        void setGrade(string input);
        void setPrice(const string& input);
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

class Collection {
    private:
        bool _isOpen = false;
        fstream _file;
        string _path = getenv("HOME");
        vector<Models> _builds;

    public:
        void collec_launcher(vector<string> command);
        void open(const string& file);
        void add();
};
