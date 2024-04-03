/*
 *  File:       MonkeyShell.hpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the main shell
*/

#pragma once

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <functional>
#include "MonkeyManager.hpp"
#include "MonkeyCollection.hpp"
#include "MonkeyModel.hpp"


class MonkeyShell {
private:
    bool _exitFlag;
    std::vector<std::string> _commands;
    std::map<std::string, std::function<void()>> commandMap;
    MonkeyManager _manager;
    MonkeyCollection _collection;
    std::string _level;

public:
    MonkeyShell();

    void start();

    void split(const std::string& s, char delimiter);
    void processCommand();

    bool isExit();
    void setExit(bool state);

    // Functions matching available commands

    static void helpCommand();
    void createCommand();
    void openCommand();
    void saveCommand();
    void closeCommand();
    void quitCommand();
    void listCommand();
    void newCommand();
    void editCommand();
    void deleteCommand();
};
