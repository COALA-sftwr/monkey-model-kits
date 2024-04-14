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

if(WIN32)
    # Windows: Add resource file for icon
    set(ICON_RESOURCE_FILE "res/ico/mmk.rc")
    target_sources(MMK PRIVATE ${ICON_RESOURCE_FILE})
elseif(APPLE)
    # macOS: Set icon for application bundle
    set(ICON_FILE "icon.icns")
    set_target_properties(MMK PROPERTIES MACOSX_BUNDLE_ICON_FILE ${ICON_FILE})
    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/${ICON_FILE}
            PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
elseif(UNIX)
    # Linux: Set icon for desktop shortcut
    set(ICON_FILE "icon.png")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MyApp.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/MyApp.desktop)
endif()
