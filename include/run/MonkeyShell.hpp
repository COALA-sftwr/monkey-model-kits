/*
 *  File:       MonkeyShell.hpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the main shell
*/

#pragma once

#include <string>
#include <map>
#include <vector>
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
    MonkeyModel* _selectedModel = nullptr;
    std::string _level;

public:
    MonkeyShell();

    void start();
    void preload(char *str);

    void processCommand();

    bool isExit();
    void setExit(bool state);

    // Functions matching available commands

    void helpCommand();
    void quitCommand();

    void createCommand();
    void openCommand();
    void saveCommand();
    void closeCommand();

    void listCommand();
    void newCommand();
    void selectCommand();
    void showUnselected();
    void showCommand();
    void startCommand();
    void stopCommand();
    void finishCommand();
    void backlogCommand();
};
