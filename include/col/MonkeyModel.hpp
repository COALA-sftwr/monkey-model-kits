/*
 *  File:       MonkeyModel.hpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the model kits modifications
*/

#pragma once


#include <unordered_map>
#include <string>
#include <vector>
#include "MonkeySession.hpp"

enum Grade { EG, SD, HG, RG, MG, PG, MS, OG, ST }; // [Entry, Super Deformed, High, Real, Master, Perfect, Mega Size, Other, Stand] Grade
enum Status { BCK, WIP, BLT };                     // Backlogged, Work In Progress, Built

static const std::unordered_map<std::string, Grade> gradeMap = {{"EG", EG},{"SD", SD},{"HG", HG},{"RG", RG},{"MG", MG},{"PG", PG},{"MS", MS},{"OG", OG},{"ST", ST}};
static const std::unordered_map<std::string, Status> statusMap = { {"BCK", BCK}, {"WIP", WIP}, {"BLT", BLT}};

class MonkeyModel
{
private:
    std::string _name;
    Grade _grade;
    double _price;
    Status _status;
    std::vector<MonkeySession> _sessions;

public:
    MonkeyModel();

    void newModel();
    // Setters
    void setName(std::string name);
    void setGrade(Grade grade);
    void setPrice(double price);
    void setStatus(Status status);
    void addSession(MonkeySession session);
    void setSessions(std::vector<MonkeySession> sessions); // TODO: implement this function to create the loading version of it.

    // Getters
    std::string getName();
    Grade getGrade();
    double getPrice();
    Status getStatus();
    std::vector<MonkeySession> getSessions();

    void newSession();

    friend std::ostream& operator<<(std::ostream& stream, const MonkeyModel& model);
};

template <typename Enum> Enum stoe(const std::string& gradeString, const std::unordered_map<std::string, Enum>& enumMap);
template <typename Enum> std::string etos(const std::unordered_map<std::string, Enum>& enumMap, Enum value);
void getUpperInput(std::string string, std::string &input);
