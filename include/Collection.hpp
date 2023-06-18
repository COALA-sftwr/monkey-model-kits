//
// Created by galbert on 17/06/23.
//

#pragma once

#include "Models.hpp"

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
        void work_on(Models model);
        void show();
        Models getKit(string name);
};
