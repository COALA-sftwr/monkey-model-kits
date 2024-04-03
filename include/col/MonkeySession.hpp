/*
 *  File:       MonkeySession.hpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the time log
*/

#pragma once
#include <chrono>

using timePoint = std::chrono::system_clock::time_point;
using intS = std::chrono::duration<int>;

class MonkeySession {
private:
    timePoint _startDate;
    timePoint _stopDate;
    intS _duration;
public:
    MonkeySession();
    MonkeySession(const timePoint& start, const timePoint& end); // TODO: add those constructors to be able to add already existing sessions.

    // TODO: Implement pauseTime eventually
    void setStart();
    void setStart(timePoint givenTime);
    void setStop();
    void setStop(timePoint givenTime);
    void setDuration();
    void pauseTime(); // Won't be used rn, will be used when pause is implemented.

    timePoint getStart();
    timePoint getStop();
    intS getDuration();


    friend std::ostream& operator<<(std::ostream& stream, const MonkeySession& session);
};

timePoint stotp(const std::string& timeStr);