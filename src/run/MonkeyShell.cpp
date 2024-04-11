/*
 *  File:       MonkeyShell.cpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the main shell
*/

#include <iostream>
#include "MonkeyShell.hpp"
#include "StringManipulation.hpp"

MonkeyShell::MonkeyShell() {
    _exitFlag = false;
    _level = "Home";

    commandMap["help"] = [this]() { helpCommand(); }; // Prints help message
    commandMap["quit"] = [this]() { quitCommand(); }; // Quits program

    commandMap["create"] = [this]() { createCommand(); }; // Creates a file
    commandMap["open"] = [this]() { openCommand(); }; // Opens a file
    commandMap["save"] = [this]() { saveCommand(); }; // Saves data to file
    commandMap["close"] = [this]() {closeCommand(); }; // Closes file
//    commandMap["delete"] = [this]() { deleteCommand(); }; // Deletes a file

    commandMap["list"] = [this]() {listCommand(); }; // Lists loaded collection
    commandMap["new"] = [this]() { newCommand(); }; // Creates a new model
    commandMap["select"] = [this]() { selectCommand(); }; // Selects a model to work on
    commandMap["show"] = [this]() { showCommand(); }; // Shows selected model

    commandMap["start"] = [this]() { startCommand(); }; // Starts timer
    commandMap["stop"] = [this]() { stopCommand(); }; // Stops timer
//    commandMap[] = [this]() { Command(); };
}

void MonkeyShell::start() {
    std::string input;

    while (!isExit()) {
        std::cout << "Kits@" << _level << "> ";
        getline(std::cin, input);
        _commands = tokenize(input, ' ');

        processCommand();
    }
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

void MonkeyShell::quitCommand() {
    if (_manager.IsFileOpen())
        closeCommand();
    setExit(true);
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
            _collection.clear();
            _selectedModel = nullptr;
            _manager.closeFile();
            _level = "Home";
        } else
            throw std::runtime_error("No file opened.");
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

void MonkeyShell::listCommand() {
    if (_collection.getModels().empty())
        std::cout << "No collection loaded." << std::endl;
    else
        std::cout << _collection << std::endl;
}

void MonkeyShell::newCommand() {
    _collection.newModel();
    _selectedModel = &_collection.getModelsAdr().back();
}

void MonkeyShell::selectCommand() {
    std::string modelNumberString;
    int modelNumber;

    if (_commands.size() == 2)
        modelNumber = std::stoi(_commands[1]) - 1;
    else {
        std::cout << "Which model do you want to work on ?" << std::endl << _collection << std::endl;
        std::getline(std::cin, modelNumberString);
        modelNumber = std::stoi(modelNumberString) - 1;
    }
    try {
        if (modelNumber < _collection.getModelsAdr().size()) {
            _selectedModel = &_collection.getModelsAdr().at(modelNumber);
            std::cout << "You selected: " << _selectedModel->getName() << "." << std::endl;
        }
        else {
            throw std::out_of_range("No corresponding model.");
        }
    } catch (std::exception &e) {
        std::cerr << "Could not select a model: " << e.what() << std::endl;
    }
}

void MonkeyShell::showCommand() {
    if (_selectedModel != nullptr)
        std::cout << *_selectedModel << std::endl;
    else
        std::cout << "No model selected." << std::endl;
}

void MonkeyShell::startCommand() {
    _selectedModel->startSession();
}

void MonkeyShell::stopCommand() {
    _selectedModel->stopSession();
}
