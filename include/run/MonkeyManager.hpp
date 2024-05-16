/*
 *  File:       MonkeyManager.hpp
 *  Created:    Albert 01/04/2024
 *  Description: Functions for the file management
*/

#pragma once

#include <filesystem>
#include <fstream>
#include <vector>
#include "MonkeyCollection.hpp"

namespace fs = std::filesystem;

class MonkeyManager
{
private:
    fs::path _docPath;
    fs::path _filePath;
    std::fstream _file;
    bool _fileOpen;

public:
    MonkeyManager();

    // Create the directory for the files
    void createKitsDirectory();

    // Work with files
    void createFile(std::vector<std::string> commands);
    void openFile(std::filesystem::path _filePath, MonkeyCollection &collection);
    void closeFile();

    fs::path getDocPath();
    fs::path getFilePath();
    void clearFilePath();

    bool IsFileOpen();
    void setDocPath(fs::path documentPath);
    void setFilePath(fs::path filePath);
    void setIsFileOpen(bool newState);

    // Mkit functions

    std::string findKey(const std::string& key, int iteration);
    MonkeyModel findModel(int model_number);

    void loadFile(MonkeyCollection& collection);

    void setTimeZones(MonkeyCollection& collection);

    void saveFile(MonkeyCollection &collection);
};

fs::path getFullPath(const fs::path& documentPath, int openOrCreate, std::vector<std::string> commands);
bool isFileEmpty(std::fstream &filename);
