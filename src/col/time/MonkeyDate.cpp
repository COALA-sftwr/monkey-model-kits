//
// Created by alber on 23/07/2024.
//

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "MonkeyTime.hpp"

MonkeyDate::MonkeyDate()
{
    clearAll();
    setUtc();
    setLoc();
}

void MonkeyDate::clearTm(std::tm *structure)
{
    structure->tm_year = 0;
    structure->tm_mon = 0;
    structure->tm_yday = 0;
    structure->tm_mday = 0;
    structure->tm_wday = 0;
    structure->tm_hour = 0;
    structure->tm_min = 0;
    structure->tm_sec = 0;
    structure->tm_isdst = 0;
}

void MonkeyDate::clearAll()
{
    clearTm(&_locDate);
    clearTm(&_utcDate);
    clearTm(&_timeOffset);
}


// Setters
void MonkeyDate::setAll()
{
    clearAll();
    _tPoint = std::chrono::system_clock::now();
    setUtc();
    setLoc();
    setOffset();
}

void MonkeyDate::setLoc()
{
    std::time_t ctime;
    ctime = std::chrono::system_clock::to_time_t(_tPoint);
    _locDate = *std::localtime(&ctime);
    _locDate.tm_year += 1900;
    _locDate.tm_mon += 1;
}

void MonkeyDate::setUtc()
{
    std::time_t ctime;
    ctime = std::chrono::system_clock::to_time_t(_tPoint);
    _utcDate = *std::gmtime(&ctime);
    _utcDate.tm_year += 1900;
    _utcDate.tm_mon += 1;
}

void MonkeyDate::setOffset()
{
    _timeOffset = sub(_locDate, _utcDate);
}

void MonkeyDate::setLoc(std::tm givenTime)
{
    _locDate = givenTime;
}

void MonkeyDate::setUtc(std::tm givenTime)
{
    _utcDate = givenTime;
    setLoc(add(_utcDate, _timeOffset));
}

void MonkeyDate::setOffset(std::vector<std::string> givenOffset)
{
    clearTm(&_timeOffset);

    _timeOffset.tm_hour = stoi(givenOffset.at(0));
    if (givenOffset.size() > 1)
        _timeOffset.tm_min = stoi(givenOffset.at(1));
    if (givenOffset.size() > 2)
        _timeOffset.tm_sec = stoi(givenOffset.at(2));
}

// Getters
std::chrono::system_clock::time_point MonkeyDate::getC()
{
    return _tPoint;
}

std::tm MonkeyDate::getLoc()
{
    return _locDate;
}

std::tm MonkeyDate::getUtc()
{
    return _utcDate;
}

std::tm MonkeyDate::getOffset()
{
    return _timeOffset;
}

std::string MonkeyDate::getLocS()
{
    std::stringstream string;

    string << std::setfill('0')
    << std::setw(4) << _locDate.tm_year << "."
    << std::setw(2) << _locDate.tm_mon << "."
    << std::setw(2) << _locDate.tm_mday << "-"
    << std::setw(2) << _locDate.tm_hour << ":"
    << std::setw(2) << _locDate.tm_min << ":"
    << std::setw(2) << _locDate.tm_sec;
    return string.str();
}

std::string MonkeyDate::getUtcS()
{
    std::stringstream string;

    string << std::setfill('0')
    << std::setw(4) << _utcDate.tm_year << "."
    << std::setw(2) << _utcDate.tm_mon << "."
    << std::setw(2) << _utcDate.tm_mday << "-"
    << std::setw(2) << _utcDate.tm_hour << ":"
    << std::setw(2) << _utcDate.tm_min << ":"
    << std::setw(2) << _utcDate.tm_sec;
    return string.str();
}

std::string MonkeyDate::getOffsetS()
{
    std::stringstream result;

    if (getOffset().tm_hour >= 0)
        result << "+";
    result << std::setfill('0') << getOffset().tm_hour;
    if (getOffset().tm_min > 0 || getOffset().tm_sec > 0)
        result << ":" << std::setw(2) << getOffset().tm_min;
    if (getOffset().tm_sec > 0)
        result << ":" << std::setw(2) << getOffset().tm_sec;
    return result.str();
}

int MonkeyDate::toInt() {
    int sum;

    sum += getUtc().tm_sec;
    sum += getUtc().tm_min * 60;
    sum += getUtc().tm_hour * 3600;

    sum += getUtc().tm_mday * 86400;
    sum += getUtc().tm_mon * 2628000;
    sum += getUtc().tm_year * 31536000;

    return sum;
}

bool MonkeyDate::isOlder(const MonkeyDate& monkey_date) {
    bool result = true;
    MonkeyDate temp = monkey_date;

    /*if (monkey_date._utcDate.tm_year > getUtc().tm_year)
        result = false;
    if (monkey_date._utcDate.tm_mon > getUtc().tm_mon)
        result = false;
    if (monkey_date._utcDate.tm_mday > getUtc().tm_yday)
        result = false;
    if (monkey_date._utcDate.tm_hour > getUtc().tm_hour)
        result = false;
    if (monkey_date._utcDate.tm_min > getUtc().tm_min)
        result = false;
    if (monkey_date._utcDate.tm_sec > getUtc().tm_sec)
        result = false;*/
    if (this->toInt() > temp.toInt())
        result = false;

    return result;
}

std::ostream& operator<<(std::ostream& stream, MonkeyDate& date)
{
    stream << std::setfill('0') << date.getUtcS() << date.getOffsetS();

    return stream;
}

std::tm add(const std::tm& addend, const std::tm& summand)
{
    std::tm sum;

    sum.tm_year = addend.tm_year + summand.tm_year ;
    sum.tm_mon = addend.tm_mon + summand.tm_mon ;
    sum.tm_mday = addend.tm_mday + summand.tm_mday ;

    sum.tm_hour = addend.tm_hour + summand.tm_hour ;
    sum.tm_min = addend.tm_min + summand.tm_min ;
    sum.tm_sec = addend.tm_sec + summand.tm_sec ;

    if (sum.tm_sec >= 60) {
        sum.tm_min++;
        sum.tm_sec -= 60;
    }
    if (sum.tm_min >= 60) {
        sum.tm_hour++;
        sum.tm_min -= 60;
    }

    return sum;
}

std::tm sub(const std::tm& minuend, const std::tm& subtrahend)  //Todo: fix this (when passed midnight, time is 0 so result is erroneous)
{
    std::tm difference;

    // Handle year difference
    difference.tm_year = minuend.tm_year - subtrahend.tm_year;

    // Handle month difference (considering year passing)
    int months_diff = minuend.tm_mon - subtrahend.tm_mon;
    if (months_diff < 0) {
    difference.tm_year--;
    months_diff += 12;
    }
    difference.tm_mon = months_diff;

    // Handle day difference (considering month and year passing)
    int days_diff = minuend.tm_mday - subtrahend.tm_mday;

    // Check if we need to borrow a day from the previous month
    if (days_diff < 0) {
    // Handle leap year manually
    bool is_leap_year = (difference.tm_year % 4 == 0 && (difference.tm_year % 100 != 0 || difference.tm_year % 400 == 0));
    int days_in_prev_month = 31;  // Assume non-leap year initially

    // Adjust days based on previous month based on month value
    switch (months_diff - 1) {
        case 11:  // December
        case 9:   // September
        case 7:   // July
        case 4:   // April
        case 2:   // February (non-leap year)
          days_in_prev_month = 30;
          break;
        case 1:   // January
          days_in_prev_month = is_leap_year ? 29 : 28;
          break;
        // Other months have 31 days
    }

    months_diff--;
    days_diff += days_in_prev_month;
    }
    difference.tm_mday = days_diff;

    // Handle remaining time differences (hour, minute, second)
    difference.tm_hour = minuend.tm_hour - subtrahend.tm_hour;
    difference.tm_min = minuend.tm_min - subtrahend.tm_min;
    difference.tm_sec = minuend.tm_sec - subtrahend.tm_sec;

    // Normalize remaining time differences (ensure values are within valid ranges)
    if (difference.tm_hour < 0) {
    difference.tm_mday--;
    difference.tm_hour += 24;
    }
    if (difference.tm_min < 0) {
    difference.tm_hour--;
    difference.tm_min += 60;
    }
    if (difference.tm_sec < 0) {
    difference.tm_min--;
    difference.tm_sec += 60;
    }

    // Handle potential negative values due to normalization (might need further adjustments based on your use case)
    // ...

    return difference;
}