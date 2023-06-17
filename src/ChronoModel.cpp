//
// Created by galbert on 17/06/23.
//

#include <iostream>
#include <ctime>
#include "../include/ChronoModel.hpp"

void ChronoModel::start()
{
    _startTime = std::time(nullptr);
    _isPaused = false;
}

void ChronoModel::pause()
{
    if (!_isPaused) {
        _pausedTime = std::time(nullptr);
        _elapsed += _pausedTime - _startTime;
        _isPaused = true;
    }
}

void ChronoModel::resume()
{
    if (_isPaused) {
        _startTime = std::time(nullptr);
        _isPaused = false;
    }
}

void ChronoModel::stop()
{
    if (!_isPaused) {
        _endTime = std::time(nullptr);
        _elapsed += _endTime - _startTime;
        _isPaused = true;
    }
}

void ChronoModel::reset()
{
    _elapsed = 0;
    _startTime = 0;
    _pausedTime = 0;
    _isPaused = true;
}

void ChronoModel::display() const
{
    std::time_t totalSeconds = _elapsed;
    struct tm* timeinfo = localtime(&totalSeconds);
    std::cout << "Elapsed time: " << timeinfo->tm_hour << "h "
              << timeinfo->tm_min << "m "
              << timeinfo->tm_sec << "s" << std::endl;
}

std::time_t ChronoModel::get_start()
{
    return _startTime;
}

std::time_t ChronoModel::get_end()
{
    return _endTime;
}

std::time_t ChronoModel::get_elapsed()
{
    return _elapsed;
}
