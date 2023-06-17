//
// Created by galbert on 17/06/23.
//

#pragma once

class ChronoModel {
    public:
        void start();
        void pause();
        void resume();
        void stop();
        void reset();
        void display() const;
        std::time_t get_start();
        std::time_t get_end();
        std::time_t get_elapsed();

    private:
        std::time_t _startTime = 0;
        std::time_t _pausedTime = 0;
        std::time_t _endTime = 0;
        std::time_t _elapsed = 0;
        bool _isPaused = true;
};
