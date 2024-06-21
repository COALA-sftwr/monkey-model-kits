/*
 *  File:       MonkeyManager.cpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the file management
*/

#include <iostream>
#include "MonkeyManager.hpp"

#include <thread>


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

    if (!is_directory(kitsPath)) {
        try {
            create_directory(kitsPath);
            setDocPath(getDocPath().append(kdir));
            std::cout << "Directory 'Kits' created successfully: " << getDocPath().string() << std::endl;
        }
        catch (const std::exception& ex) {
            std::cerr << "Error creating 'Kits' directory: " << ex.what() << std::endl;
        }
    } else {
        setDocPath(getDocPath().append(kdir));
        std::cout << "Directory already exists. (" << getDocPath().string() << ")" << std::endl;
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

void MonkeyManager::openFile(std::filesystem::path filePath, MonkeyCollection &collection)
{
    _file.open(filePath);

    try {
        if (!exists(filePath))
            throw std::runtime_error("File does not exist.");
        if (_file.is_open()) {
            if (!isFileEmpty(_file))
                loadFile(collection);
            else
                std::cout << "File is empty." << std::endl;
            setIsFileOpen(true);
            setFilePath(filePath);
            std::cout << "File opened successfully: " << filePath << std::endl;
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

void MonkeyManager::clearFilePath()
{
    _filePath.clear();
}

void MonkeyManager::saveFile(MonkeyCollection& collection) {
    // Clear the file content before writing
    _file.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    _file.open(_filePath, std::ios::out | std::ios::trunc); // Open in truncation mode to clear file

    // Check if the file opened successfully
    if (!_file.is_open()) {
        std::cerr << "Error opening file for writing: " << _filePath << std::endl;
        std::cerr << "Error state: " << _file.rdstate() << std::endl;
        return;
    }

    // Write the collection content to the file
    _file << "(" << std::endl << collection.save() << ")" << std::endl;
    std::cout << "File saved successfully: " << _filePath << std::endl;
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
