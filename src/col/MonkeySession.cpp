/*
*  File:       MonkeySession.cpp
*  Created:    Albert 01/04/2024
*  Description: Functions for the time log
*/

#include "MonkeySession.hpp"
#include "StringManipulation.hpp"

MonkeySession::MonkeySession() {

}

MonkeySession::MonkeySession(const TimePoint &start, const TimePoint &end) {
    _startDate = start;
    setString(_startDate, _startString);
    _stopDate = end;
    setString(_stopDate, _stopString);
    setDuration();
}

MonkeySession::MonkeySession(std::vector<TimePoint> timePoints) {
    _startDate = timePoints[0];
    setString(_startDate, _startString);
    _stopDate = timePoints [1];
    setString(_stopDate, _stopString);
    setDuration();

}

MonkeySession::MonkeySession(intS duration) {
    _duration = duration;
}


// Setters
void MonkeySession::setStart() {
    _startDate = std::chrono::system_clock::now();
}

void MonkeySession::setStart(TimePoint givenTime) {
    _startDate = givenTime;
}

void MonkeySession::setStop() {
    _stopDate = std::chrono::system_clock::now();
    setDuration();
}

void MonkeySession::setStop(TimePoint givenTime) {
    _stopDate = givenTime;
    setDuration();
}

void MonkeySession::setDuration() {
    auto durationInSeconds = std::chrono::duration_cast<std::chrono::seconds>(getStop() - getStart());
    _duration = std::chrono::duration<int>(durationInSeconds);
}

void MonkeySession::setString(TimePoint givenTime, std::string& string) {
    std::stringstream ss;

    std::time_t time = std::chrono::system_clock::to_time_t(givenTime);
    ss << std::put_time(std::localtime(&time), "%Y.%m.%d-%H:%M:%S");

    string = ss.str();
}

void MonkeySession::setTimeZone(std::string givenTimeZone) {
    _timeZone = givenTimeZone;
}


// Getters
TimePoint MonkeySession::getStart() {
    return _startDate;
}

TimePoint MonkeySession::getStop() {
    return _stopDate;
}


intS MonkeySession::getDuration() {
    return _duration;
}

std::ostream& operator<<(std::ostream& stream, const MonkeySession& session) {
    std::string unknown = "No known date.";

    stream << "Start date: " << (session._startString.empty() ? session._startString : unknown) << std::endl
           << "Stop date: " << (session._stopString.empty() ? session._stopString : unknown) << std::endl
    << "Duration : " << session._duration << std::endl;
    return stream;
}


// String to time-types functions

TimePoint stotp(const std::string& timeStr) {
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

std::vector<TimePoint> stotps_v(const std::string& tString) {
    std::vector<TimePoint> value_t;
    std::vector<std::string> tStrings = tokenize(tString, '>');

    for (auto instance : tStrings) {
        cleanString(instance);
        value_t.push_back(stotp(instance));
    }

    return value_t;
}

intS stomd(const std::string& timeStr) {
    intS duration_t;
    std::vector<std::string> times = tokenize(timeStr, ':');
    int hours_s, minutes_s, seconds_s;

    hours_s = std::stoi(times[0]) * 3600;
    minutes_s = std::stoi(times[1]) * 60;
    seconds_s = std::stoi(times[2]);

    duration_t = std::chrono::seconds(hours_s + minutes_s + seconds_s);

    return duration_t;
}

std::vector<MonkeySession> stoms_v(std::string value) {
    std::vector<MonkeySession> value_t;
    std::vector<std::string> strings = tokenize(value, '|');

    for (std::string instance : strings) {
        if (instance.at(0) == '_')
            value_t.push_back(MonkeySession(stomd(instance)));
        value_t.push_back(MonkeySession(stotps_v(instance)));
    }

    return value_t;
}