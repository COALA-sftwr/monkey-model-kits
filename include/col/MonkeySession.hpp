/*
 *  File:       MonkeySession.hpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the time log
*/

#pragma once

#include <unordered_map>
#include <chrono>

using TimePoint = std::chrono::system_clock::time_point;
using intS = std::chrono::duration<int>;

class MonkeySession {
private:
    TimePoint _startDate;
    TimePoint _stopDate;
    std::string _startString;
    std::string _stopString;
    intS _duration;
    std::string _timeZone;
public:
    MonkeySession();
    MonkeySession(const TimePoint& start, const TimePoint& end);
    MonkeySession(intS duration);
    MonkeySession(std::vector<TimePoint> timePoints);

    // TODO: Implement pauseTime eventually
    void setStart();
    void setStart(TimePoint givenTime);

    void setStop();
    void setStop(TimePoint givenTime);

    void setDuration();

    void setString(TimePoint givenTime, std::string& string);
    void setTimeZone(std::string givenTimeZone);
    void pauseTime(); // Won't be used rn, will be used when pause is implemented.


    TimePoint getStart();
    std::string getStartString();
    TimePoint getStop();
    std::string getStopString();
    intS getDuration();


    friend std::ostream& operator<<(std::ostream& stream, const MonkeySession& session);
};

TimePoint stotp(const std::string& timeStr);
std::vector<TimePoint> stotps_v(const std::string& tString);
intS stomd(const std::string& timeStr);
std::vector<MonkeySession> stoms_v(std::string value);


static const std::unordered_map<std::string, int> tzMap = {{"UTC-12", -12},
                                                           {"UTC-11",-11},
                                                           {"UTC-10",-10},
                                                           {"UTC-9",-9},
                                                           {"UTC-8",-8},
                                                           {"UTC-7",-7},
                                                           {"UTC-6",-6},
                                                           {"UTC-5",-5},
                                                           {"UTC-4",-4},
                                                           {"UTC-3",-3},
                                                           {"UTC-2",-2},
                                                           {"UTC-1",-1},
                                                           {"UTC",0},
                                                           {"UTC+1",1},
                                                           {"UTC+2",2},
                                                           {"UTC+3",3},
                                                           {"UTC+4",4},
                                                           {"UTC+5",5},
                                                           {"UTC+6",6},
                                                           {"UTC+7",7},
                                                           {"UTC+8",8},
                                                           {"UTC+9",9},
                                                           {"UTC+10",10},
                                                           {"UTC+11",11},
                                                           {"UTC+12",12},
                                                           {"UTC+13",13},
                                                           {"UTC+14",14}};
