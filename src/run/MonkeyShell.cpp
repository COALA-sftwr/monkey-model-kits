/*
 *  File:       MonkeyShell.cpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the main shell
*/

#include <sstream>
#include <iostream>
#include "MonkeyShell.hpp"

MonkeyShell::MonkeyShell() {
    _exitFlag = false;
    _level = "Home";

    commandMap["help"] = []() { helpCommand(); };

    commandMap["create"] = [this]() { createCommand(); };
    commandMap["open"] = [this]() { openCommand(); };
    commandMap["save"] = [this]() { saveCommand(); };
    commandMap["close"] = [this]() {closeCommand(); };
    commandMap["quit"] = [this]() { quitCommand(); };

    commandMap["list"] = [this]() {listCommand(); };
    commandMap["new"] = [this]() { newCommand(); };
//    commandMap["edit"] = [this]() { editCommand(); };
//    commandMap["delete"] = [this]() { deleteCommand(); };
}

void MonkeyShell::start() {
    std::string input;

    while (!isExit()) {
        std::cout << "Kits@" << _level << "> ";
        getline(std::cin, input);
        split(input, ' ');

        processCommand();
    }
}

void MonkeyShell::split(const std::string &s, char delimiter) {
    std::stringstream ss(s);
    std::string token;

    while (getline(ss, token, delimiter))
        if (!token.empty())
            _commands.push_back(token);
}

void MonkeyShell::processCommand() {
    auto it = commandMap.find(_commands[0]);
    if (it != commandMap.end()) {
        it->second();
    } else {
        std::cout << "Command not found: " << _commands[0] << std::endl;
    }
    _commands.clear();
}

bool MonkeyShell::isExit() {
    return _exitFlag;
}

void MonkeyShell::setExit(bool state) {
    _exitFlag = state;
}

// Functions matching available commands

void MonkeyShell::helpCommand() {
    std::cout << "-Monkey Model Kits-\n"
                 "\tCommands\n"
                 "\t\t-help:\t\tShows this message.\n"
                 "\t\t-create\t[profile]:\tCreates the file related to the given profile. If none is given, will be requested\n"
                 "\t\t-open\t[profile]:\tOpens the file related to the given profile. If none is given, will be requested.\n"
                 "\t\t-list:\tLists all loaded models.\n"
                 "\t\t-new:\tCreates a new model to the collection.\n"
                 "\t\t-save:\tSaves the open file.\n"
                 "\t\t-close:\tCloses the open file without exiting program.\n"
                 "\t\t-quit:\t\tExits MMK"
              << std::endl;
}

void MonkeyShell::createCommand() {
    try {
        if (_commands.size() > 1) {
            _manager.createFile(_commands);
        } else
            throw std::out_of_range("Not enough parameters given.");
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

void MonkeyShell::openCommand() {
    try {
        if (_manager.IsFileOpen())
            throw std::runtime_error("A file is already opened, save the changes and close it before opening another one.");
        if (_commands.size() > 1) {
            _manager.openFile(_commands, _level, _collection);
        } else
            throw std::out_of_range("Not enough parameters given.");
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

void MonkeyShell::saveCommand() {
//    _manager.saveFile();
}

void MonkeyShell::closeCommand() {
    try {
        if (_manager.IsFileOpen()) {
            _manager.quitFile();
            _level = "Home";
        } else
            throw std::runtime_error("No file opened.");
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

void MonkeyShell::quitCommand() {
    if (_manager.IsFileOpen())
        closeCommand();
    setExit(true);
}

void MonkeyShell::listCommand() {
    std::cout << _collection << std::endl;
}

void MonkeyShell::newCommand() {
    _collection.newModel();
}
