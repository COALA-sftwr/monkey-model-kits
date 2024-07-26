//
// Created by alber on 23/07/2024.
//

#pragma once

#include <chrono>
#include <ctime>

class MonkeyDate
{
private:
    std::chrono::system_clock::time_point _tPoint;
    std::tm _locDate;
    std::tm _utcDate;
    std::tm _timeOffset;
public:
    MonkeyDate();

    void clearTm(std::tm *structure);
    void clearAll();

    void setAll();
    void setLoc();
    void setUtc();
    void setOffset();
    void setTPoint(); // Todo: add this if needed.
    void setLoc(std::tm givenTime);
    void setUtc(std::tm givenTime);
    void setOffset(std::vector<std::string> givenOffset);

    std::chrono::system_clock::time_point getC();
    std::tm getLoc();
    std::tm getUtc();
    std::tm getOffset();
    std::string getLocS();
    std::string getUtcS();
    std::string getOffsetS();

    int64_t toInt();

    friend std::ostream& operator<<(std::ostream& stream, MonkeyDate& date);
    bool isOlder(MonkeyDate monkey_date);
};

class MonkeySession
{
private:
    MonkeyDate _startDate;
    MonkeyDate _stopDate;
    std::tm _duration{};

public:
    MonkeySession();
    MonkeySession(std::string sessionString);
    MonkeySession(std::vector<std::string> sessionVector);

    MonkeyDate loadDate(std::string session_s);

    void clearTm(std::tm structure);

    void setStart();
    void setStop();
    void setDuration();
    void setStart(MonkeyDate startDate);
    void setStop(MonkeyDate stopDate);
    void setDuration(int seconds); // Todo: implement seconds adding
    void setDuration(std::string timeString);

    MonkeyDate getStart();
    MonkeyDate getStop();
    std::tm getDuration();
    std::string getDurationS();
    int getDurationI();

    friend std::ostream& operator<<(std::ostream& stream, MonkeySession& session);
};

int tmtoi(std::tm structure);
std::chrono::system_clock::time_point tmToTimePoint(const std::tm &tm);
std::vector<MonkeySession> stoms_v(std::string value);
std::tm add(const std::tm& addend, const std::tm& summand);
std::tm sub(const std::tm& minuend, const std::tm& subtrahend);