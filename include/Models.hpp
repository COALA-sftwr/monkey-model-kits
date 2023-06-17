//
// Created by galbert on 17/06/23.
//

#pragma once

#include <string>
#include <ctime>
#include "ModelTime.hpp"

class Models {
    public:
        enum Grade {EG, SD, HG, RG, MG, PG, MZ, OG, ST};
        enum Status {WL, BL, BD};
    private:
        std::string _name;
        Grade _grade;
        tm *_tTime;
        int sessions;
        ModelTime *_sTime;
        double price;
        Status _status;

};

class Collection {
    private:
        bool _isOpen = false;
        FILE _file;
        Models *_builds;
    public:
        void collec_launcher(char *input);
};
