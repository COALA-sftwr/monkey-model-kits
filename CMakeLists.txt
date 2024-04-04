cmake_minimum_required(VERSION 3.27)
project(MMK)

set(CMAKE_CXX_STANDARD 26)

include_directories(
        include/
        include/col
        include/run
)

add_executable(MMK
        src/main.cpp
        src/run/MonkeyShell.cpp
        src/run/MonkeyManager.cpp
        src/col/MonkeyModel.cpp
        src/col/MonkeySession.cpp
        src/col/MonkeyCollection.cpp
        src/run/MonkeyFile.cpp
        src/StringManipulation.cpp
)
