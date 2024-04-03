#include "MonkeySession.hpp"

/*
 *  File:       MonkeySession.cpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the time log
*/



MonkeySession::MonkeySession() {

}

MonkeySession::MonkeySession(const timePoint &start, const timePoint &end) {
    _startDate = start;
    _stopDate = end;
}

// Setters
void MonkeySession::setStart() {
    _startDate = std::chrono::system_clock::now();
}

void MonkeySession::setStart(timePoint givenTime) {
    _startDate = givenTime;
}

void MonkeySession::setStop() {
    _stopDate = std::chrono::system_clock::now();
    setDuration();
}

void MonkeySession::setStop(timePoint givenTime) {
    _stopDate = givenTime;
    setDuration();
}

void MonkeySession::setDuration() {
    auto durationInSeconds = std::chrono::duration_cast<std::chrono::seconds>(this->getStart() - this->getStop());
    _duration = std::chrono::duration<int>(durationInSeconds);
}

// Getters
timePoint MonkeySession::getStart() {
    return _startDate;
}

timePoint MonkeySession::getStop() {
    return _stopDate;
}

intS MonkeySession::getDuration() {
    return _duration;
}

std::ostream& operator<<(std::ostream& stream, const MonkeySession& session) {
    stream << "Start date: " << session._startDate << std::endl
    << "Stop date: " << session._stopDate << std::endl
    << "Duration : " << session._duration << std::endl;
    return stream;
}

timePoint stotp(const std::string& timeStr) {
    std::tm tm = {};
    std::istringstream ss(timeStr);

    // Parse date part
    char dot;
    ss >> tm.tm_year >> dot >> tm.tm_mon >> dot >> tm.tm_mday;
    tm.tm_year -= 1900; // Years since 1900
    tm.tm_mon -= 1;     // Months since January

    // Parse time part
    char hyphen;
    ss >> hyphen >> tm.tm_hour >> dot >> tm.tm_min >> dot >> tm.tm_sec;

    // Check if parsing was successful
    if (ss.fail() || dot != '.' || hyphen != '-') {
        throw std::runtime_error("Failed to parse time string");
    }

    // Convert std::tm to std::chrono::time_point
    std::time_t time = std::mktime(&tm);
    if (time == -1) {
        throw std::runtime_error("Failed to convert time to time_t");
    }
    return std::chrono::system_clock::from_time_t(time);
}
