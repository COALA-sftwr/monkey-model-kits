/*
 *  File:       MonkeyManager.cpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the file management
*/

#include <iostream>
#include "MonkeyManager.hpp"


// Constructor

MonkeyManager::MonkeyManager()
{
#ifdef _WIN32
    // On Windows, use USERPROFILE environment variable
    const char* userProfile = std::getenv("USERPROFILE");
    if (userProfile) {
        _docPath = fs::path(userProfile) / "Documents";
    }

#else
    // On Unix-based systems, use HOME environment variable
    const char* home = std::getenv("HOME");
    if (home) {
        _docPath = fs::path(home) / "Documents";
    }
#endif

    if (_docPath.empty()) {
        std::cerr << "Error: Unable to determine Documents directory." << std::endl;
        _fileOpen = false;
        return;
    } else
        createKitsDirectory();

    _fileOpen = false;
}

void MonkeyManager::createKitsDirectory()
{
    std::string kdir = "Kits";

    // Append "Kits" to the Documents directory path
    fs::path kitsPath = getDocPath() / kdir;

    if (!fs::is_directory(kitsPath)) {
        try {
            fs::create_directory(kitsPath);
            setDocPath(getDocPath().append(kdir));
            std::cout << "Directory 'Kits' created successfully: " << getDocPath().string() << std::endl;
        }
        catch (const std::exception& ex) {
            std::cerr << "Error creating 'Kits' directory: " << ex.what() << std::endl;
        }
    } else {
        std::cout << "Directory already exists. (" << getDocPath().string() << ")" << std::endl;
        setDocPath(getDocPath().append(kdir));
    }
}


// MonkeyManager Methods

void MonkeyManager::createFile(std::vector<std::string> commands)
{
    setFilePath(getFullPath(getDocPath(), 1, commands));
    fs::path fpath = getFilePath();

    try {
        if (fs::exists(fpath)) {
            std::cout << "File already exists in : " << std::endl << fpath << std::endl;
            setIsFileOpen(false);
        } else {
            _file.open(fpath, std::ios::in | std::ios::out | std::ios::app);
            setIsFileOpen(true);
            std::cout << "File created successfully in: " << std::endl << fpath << std::endl;
            _file.close();
            setIsFileOpen(false);
        }
    }
    catch (const std::exception& ex) {
        _fileOpen = false;
        std::cerr << "Error creating the collection file: " << ex.what() << std::endl;
    }

    clearFilePath();
}

void MonkeyManager::openFile(std::vector<std::string> commands, std::string &level, MonkeyCollection &collection)
{
    _filePath = getFullPath(getDocPath(), 0, commands);

    _file.open(_filePath);

    try {
        if (!fs::exists(_filePath))
            throw std::runtime_error("File does not exist.");
        else if (_file.is_open()) {
            if (isFileEmpty(_file))
                throw std::runtime_error("File is empty.");
            setIsFileOpen(true);
            loadFile(collection);
            level = commands[1];
            std::cout << "File opened successfully: " << getFilePath() << std::endl;
        }
    }
    catch (const std::exception& ex) {
        _fileOpen = false;
        std::cerr << "Error opening the collection file: " << ex.what() << std::endl;
    }
}

void MonkeyManager::closeFile()
{
    _file.close();
    clearFilePath();
    setIsFileOpen(false);
    std::cout << "File closed successfully." << std::endl;
}


// Getters

fs::path MonkeyManager::getDocPath()
{
    return _docPath;
}

fs::path MonkeyManager::getFilePath()
{
    return _filePath;
}


bool MonkeyManager::IsFileOpen()
{
    return _fileOpen;
}

// Setters

void MonkeyManager::setDocPath(fs::path documentPath)
{
    _docPath = documentPath;
}

void MonkeyManager::setFilePath(fs::path filePath)
{
    _filePath = filePath;
}

void MonkeyManager::setIsFileOpen(bool newState)
{
    _fileOpen = newState;
}

void MonkeyManager::clearFilePath()
{
    _filePath.clear();
}

// Other functions

fs::path getFullPath(const fs::path& docPath, int openOrCreate, std::vector<std::string> commands)
{
    std::string name;
    fs::path fullPath;

    if (commands.size() == 1) {
        std::cout << "Enter the name of the file to " << (openOrCreate == 0 ? "open" : "create") << " in the Documents directory: ";
        std::getline(std::cin, name);
    } else
        name = commands[1];
    fullPath = docPath / name.append(".mkit");

    return fullPath;
}

bool isFileEmpty(std::fstream &filename) {
    return filename.peek() == std::ifstream::traits_type::eof();
}
