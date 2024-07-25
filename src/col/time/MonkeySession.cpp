//
// Created by alber on 23/07/2024.
//

#include <iomanip>
#include <iostream>
#include <vector>

#include "MonkeyTime.hpp"
#include "StringManipulation.hpp"

std::vector<std::string> tokenize(const std::string& str, const std::vector<char>& delimiters) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find_first_of(delimiters.data());

    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find_first_of(delimiters.data(), start);
        tokens.back() = cleanString(tokens.back());
    }
    tokens.push_back(str.substr(start));
    tokens.back() = cleanString(tokens.back());

    return tokens;
}

MonkeySession::MonkeySession()
{
    clearTm(_duration);
}

MonkeySession::MonkeySession(std::string sessionString)
{
    clearTm(_duration);
    sessionString = sessionString.substr(1);
    // sessionString.erase(sessionString.at(0));
    setDuration(sessionString);
}

MonkeySession::MonkeySession(std::vector<std::string> sessionVector)
{
    clearTm(_duration);
    _startDate = loadDate(sessionVector.at(0));
    _stopDate = loadDate(sessionVector.at(1));
    setDuration();
}

MonkeyDate MonkeySession::loadDate(std::string session_s) // 2024.7.23-14:21:18+2:0:0
{
    MonkeyDate result;
    std::tm temp = {};
    std::vector<std::string> strings = tokenize(session_s, {'_', '+', '-'});
    std::vector<std::string> day = tokenize(strings.at(0), {'.'});
    std::vector<std::string> hour = tokenize(strings.at(1), {':'});

    clearTm(temp);

    temp.tm_year = stoi(day.at(0));
    temp.tm_mon = stoi(day.at(1));
    temp.tm_mday = stoi(day.at(2));

    temp.tm_hour = stoi(hour.at(0));
    temp.tm_min = stoi(hour.at(1));
    temp.tm_sec = stoi(hour.at(2));

    if (session_s.find('-') != std::string::npos)
        strings.at(2).insert(strings.at(2).begin(), '-');

    if (strings.size() > 2)
        result.setOffset(tokenize(strings.at(2), {':'}));
    result.setUtc(temp);
    return result;
}

void MonkeySession::clearTm(std::tm structure)
{
    structure.tm_year = 0;
    structure.tm_mon = 0;
    structure.tm_yday = 0;
    structure.tm_mday = 0;
    structure.tm_wday = 0;
    structure.tm_hour = 0;
    structure.tm_min = 0;
    structure.tm_sec = 0;
    structure.tm_isdst = 0;
}

// Setters
void MonkeySession::setStart()
{
    _startDate.setAll();
}

void MonkeySession::setStop()
{
    _stopDate.setAll();
    setDuration();
}

void MonkeySession::setDuration()
{
    /*int startS = _startDate.getUtc().tm_hour * 3600 + _startDate.getUtc().tm_min * 60 + _startDate.getUtc().tm_sec;
    int stopS = _stopDate.getUtc().tm_hour * 3600 + _stopDate.getUtc().tm_min * 60 + _stopDate.getUtc().tm_sec;
    int total_seconds = stopS - startS;

    _duration.tm_hour = total_seconds / 3600;
    total_seconds %= 3600;
    _duration.tm_min = total_seconds / 60;
    total_seconds %= 60;
    _duration.tm_sec = total_seconds;*/
    _duration = sub(getStop().getUtc(), getStart().getUtc());
    if (_duration.tm_mday > 0) {
        _duration.tm_hour += _duration.tm_mday * 24;
    }
    /*if (_duration.tm_mon > 0) {
        _duration.tm_hour += _duration.tm_mday * 24;
    }*/
}

void MonkeySession::setStart(MonkeyDate startDate)
{
    _startDate = startDate;
}

void MonkeySession::setStop(MonkeyDate stopDate)
{
    _stopDate = stopDate;
}

void MonkeySession::setDuration(int seconds)
{

}

void MonkeySession::setDuration(std::string timeString)
{
    std::vector<std::string> temp = tokenize(timeString, {':'});

    _duration.tm_hour = std::stoi(temp.at(0));
    _duration.tm_min = std::stoi(temp.at(1));
    _duration.tm_sec = std::stoi(temp.at(2));
}


// Getters
MonkeyDate MonkeySession::getStart()
{
    return _startDate;
}

MonkeyDate MonkeySession::getStop()
{
    return _stopDate;
}

std::tm MonkeySession::getDuration()
{
    return _duration;
}

std::string MonkeySession::getDurationS()
{
    std::stringstream dResult;

    dResult << std::setfill('0')
                << std::setw(2) << _duration.tm_hour << ":"
                << std::setw(2) << _duration.tm_min << ":"
                << std::setw(2) << _duration.tm_sec;

    return dResult.str();
}

int MonkeySession::getDurationI() {
    int result;

    result = getStop().toInt() - getStart().toInt();
    if (result == 0)
        result = tmtoi(getDuration());

    return result;
}

std::ostream& operator<<(std::ostream& stream, MonkeySession& session)
{
    std::string unknown = "No known date.";
    MonkeyDate temp = session.getStart();
    auto tempStart = session.getStart().getUtcS();
    auto tempStop = session.getStop().getUtcS();
    auto tempDur = session.getDurationI();

    // if (session.getStart().getUtcS().empty() || session.getStop().getUtcS().empty())
    if (session.getStart().getUtcS() == session.getStop().getUtcS() && session.getDurationI() > 0)
        stream << "_" << session.getDurationS();
    else {
        stream << temp << " > ";
        temp = session.getStop();
        stream << temp;
    }
    return stream;
}

int tmtoi(std::tm structure) {
    int sum;

    sum += structure.tm_sec;
    sum += structure.tm_min * 60;
    sum += structure.tm_hour * 3600;

    sum += structure.tm_mday * 86400;
    sum += structure.tm_mon * 2628000;
    sum += structure.tm_year * 31536000;

    return sum;
}

std::chrono::system_clock::time_point tmToTimePoint(const std::tm &tm) {
    std::time_t timeT = std::mktime(const_cast<std::tm*>(&tm)); // Convert std::tm to time_t
    return std::chrono::system_clock::from_time_t(timeT);       // Convert time_t to time_point
}

std::vector<MonkeySession> stoms_v(std::string value) {
    std::vector<MonkeySession> value_t;
    std::vector<std::string> strings = tokenize(value, {'|'});

    for (std::string instance : strings) {
        if (instance.at(0) == '_')
            value_t.push_back(MonkeySession(instance));
            // value_t.push_back(MonkeySession(stomd(instance.erase(0, 1))));
        else
            value_t.push_back(MonkeySession(tokenize(instance, {'>'})));
            // value_t.push_back(MonkeySession(stotps_v(instance)));
    }

    return value_t;
}
