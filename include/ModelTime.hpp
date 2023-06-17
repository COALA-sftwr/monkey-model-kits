//
// Created by galbert on 17/06/23.
//

#pragma once

#include <ctime>
#include "ChronoModel.hpp"

class ModelTime {
    private:
        tm *_start = nullptr;
        tm *_stop = nullptr;
        tm *_elapsed = nullptr;
        ChronoModel _chrono;
    public:
        void launch_session();
        void pause_session();
        void end_session();
};
