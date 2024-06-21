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

    commandMap["help"] = [this]() { helpCommand(); }; // Prints help message // TODO: make so that all separate commands are available only in their section
    commandMap["quit"] = [this]() { quitCommand(); }; // Quits program

    commandMap["create"] = [this]() { createCommand(); }; // Creates a file
    commandMap["open"] = [this]() { openCommand(); }; // Opens a file
    commandMap["save"] = [this]() { saveCommand(); }; // Saves data to file
    commandMap["close"] = [this]() {closeCommand(); }; // Closes file
//    commandMap["delete"] = [this]() { deleteCommand(); }; // Deletes a file // TODO: Delte files

    commandMap["list"] = [this]() {listCommand(); }; // Lists loaded collection
    commandMap["new"] = [this]() { newCommand(); }; // Creates a new model
    commandMap["select"] = [this]() { selectCommand(); }; // Selects a model to work on // TODO: Add command to edit the values of the model
    commandMap["show"] = [this]() { showCommand(); }; // Shows selected model

    commandMap["start"] = [this]() { startCommand(); }; // Starts timer
    commandMap["stop"] = [this]() { stopCommand(); }; // Stops timer

    commandMap["finish"] = [this]() { finishCommand(); }; // Finishes model
    commandMap["backlog"] = [this]() { backlogCommand(); }; // Finishes model
//    commandMap[] = [this]() { Command(); }; Command template.
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

void MonkeyShell::preload(char *test) {
    std::vector<std::string> commands;
    std::string filename;
    std::string str(test);

    commands.push_back("");

    size_t pos = str.rfind('\\', str.rfind('.'));

    // Check if a '\\' is found before '.'
    if (pos != std::string::npos) {
        // Extract the substring starting from the character after the last '\\' (excluding '\\')
        filename = str.substr(pos + 1, str.rfind('.') - pos - 1);
    } else {
        std::cout << "No valid path found." << std::endl;
    }
    commands.insert(commands.begin() + 1, filename);
    _manager.openFile(commands, filename, _collection);
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
                 "\t\t-help:\t\t\tShows this message.\n"
                 "\t\t-create\t[profile]:\tCreates the file related to the given profile. If none is given, will be requested\n"
                 "\t\t-open\t[profile]:\tOpens the file related to the given profile. If none is given, will be requested.\n"
                 "\t\t-save:\t\t\tSaves collection changes to the open file.\n"
                 "\t\t-close:\t\t\tCloses the open file without exiting program.\n\n"

                 "\t\t-list:\t\t\tLists all loaded models.\n"
                 "\t\t-new:\t\t\tCreates a new model to the collection.\n\n"
                 "\t\t-select [model id]:\tSelects a model to edit. If no model id given, will show the list of models to select.\n"
                 "\t\t-show [model id]:\tShows infos of a model you select. If no model id given, will show the list of models to select.\n\n"

                 "\t\t-start:\t\t\tStarts the timer of a new session on the selected model.\n"
                 "\t\t-stop:\t\t\tStops the timer of the session.\n\n"

                 "\t\t-finish:\t\tSets the model state to finished.\n"
                 "\t\t-backlog:\t\tSets the model state to backlogged.\n\n"

                 "\t\t-quit:\t\tExits MMK"
              << std::endl;
}

void MonkeyShell::quitCommand() {
    if (_manager.IsFileOpen())
        saveCommand();
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
    _manager.saveFile(_collection);
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
    int modelNumber;

    if (_commands.size() == 2)
        modelNumber = std::stoi(_commands[1]) - 1;
    else {
        std::string modelNumberString;
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

void MonkeyShell::showUnselected() {
    int temp_i;

    if (_commands.size() == 2)
        temp_i = std::stoi(_commands.at(1));
    else {
        std::string temp_s;
        std::cout << "No model selected, chose one to show: (0 to quit)" << std::endl;
        listCommand();
        std::getline(std::cin, temp_s);
        temp_i = std::stoi(temp_s);
    }
    switch (temp_i) {
        case 0:
            break;
        default :
            std::cout << _collection.getModelsAdr().at(temp_i - 1) << std::endl;
    }
}

void MonkeyShell::showCommand() {
    if (_selectedModel != nullptr)
        std::cout << *_selectedModel << std::endl;
    else {
        showUnselected();
    }
}

void MonkeyShell::startCommand() {
    try {
        if (!_selectedModel->isSWOn())
            _selectedModel->startSession();
        else
            throw std::runtime_error("StopWatch already running.");
    } catch (std::exception &e)
    {
        std::cout << "Could not start StopWatch: " << e.what() << std::endl;
    }
}

void MonkeyShell::stopCommand() {
    try {
        if (_selectedModel->isSWOn())
            _selectedModel->stopSession();
        else
            throw std::runtime_error("No running StopWatch.");
    } catch (std::exception &e)
    {
        std::cout << "Could not stop StopWatch: " << e.what() << std::endl;
    }
}

void MonkeyShell::finishCommand() {
    _selectedModel->setStatus(BLT);
}

void MonkeyShell::backlogCommand() {
    _selectedModel->setStatus(BCK);
}
