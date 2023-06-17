//
// Created by galbert on 17/06/23.
//

#include "../include/ModelTime.hpp"

void ModelTime::launch_session()
{
    _chrono.start();
    _start = reinterpret_cast<tm *>(_chrono.get_start());
}

void ModelTime::pause_session()
{
    _chrono.pause();
    _elapsed = reinterpret_cast<tm *>(_chrono.get_elapsed());
}

void ModelTime::end_session()
{
    _chrono.stop();
    _elapsed = reinterpret_cast<tm *>(_chrono.get_elapsed());
    _stop = reinterpret_cast<tm *>(_chrono.get_end());
}
