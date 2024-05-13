cmake_minimum_required(VERSION 3.28)

project(MonkeyModelKit LANGUAGES CXX)

# Find the Qt libraries
set(CMAKE_PREFIX_PATH "C:/Qt/6.6.0/mingw_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_LIST_DIR}/gui)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(SOURCES
        src/main.cpp
        src/StringManipulation.cpp

        src/run/MonkeyShell.cpp
        src/run/MonkeyManager.cpp
        src/run/MonkeyFile.cpp

        src/gui/MonkeyWindow.cpp

        src/col/MonkeyModel.cpp
        src/col/MonkeySession.cpp
        src/col/MonkeyCollection.cpp
)

set(HEADERS
        include/StringManipulation.hpp

        include/run/MonkeyFile.hpp
        include/run/MonkeyManager.hpp
        include/run/MonkeyShell.hpp

        include/gui/MonkeyWindow.hpp

        include/col/MonkeyCollection.hpp
        include/col/MonkeyModel.hpp
        include/col/MonkeySession.hpp
)

set(UI_FILES
        gui/MonkeyWindow.ui
        # Add more UI files as needed
)

#[[set(TS_FILES
# Add translation files if needed
)]]

qt_add_executable(MonkeyModelKit WIN32
        ${SOURCES}
        ${HEADERS}
        ${UI_FILES}
#        ${TS_FILES}
)

target_include_directories(MonkeyModelKit
        PRIVATE include include/col include/run include/gui gui/
)

# Link the Qt libraries to the executable
target_link_libraries(MonkeyModelKit PRIVATE Qt6::Widgets)

if(WIN32)
    # Windows: Add resource file for icon
    set(ICON_RESOURCE_FILE "res/ico/mmk.rc")
    target_sources(MonkeyModelKit PRIVATE ${ICON_RESOURCE_FILE})
elseif(APPLE)
    # macOS: Set icon for application bundle
    set(ICON_FILE "morris.icns")
    set_target_properties(MMK PROPERTIES MACOSX_BUNDLE_ICON_FILE ${ICON_FILE})
    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/${ICON_FILE}
            PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
elseif(UNIX)
    # Linux: Set icon for desktop shortcut
    set(ICON_FILE "morris.png")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MyApp.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/MyApp.desktop)
endif()
