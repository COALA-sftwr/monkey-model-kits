cmake_minimum_required(VERSION 3.15)

project(MonkeyModelKit LANGUAGES CXX)

# Find the Qt libraries

set(CMAKE_PREFIX_PATH "C:/Qt/6.6.0/mingw_64")
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Set the source files for your application
set(SOURCES
        src/main.cpp
        src/run/MonkeyShell.cpp
        src/run/MonkeyManager.cpp
        src/col/MonkeyModel.cpp
        src/col/MonkeySession.cpp
        src/col/MonkeyCollection.cpp
        src/run/MonkeyFile.cpp
        src/StringManipulation.cpp
        # Add more source files as needed
)

#[[# Set the header files for your application
set(HEADERS
        include/
        include/col
        include/run
        # Add more header files as needed
)]]

include_directories(
        include/
        include/col
        include/run
)

# Set the user interface files (if any)
set(UI_FILES
        # Add more UI files as needed
)

# Set up the translation files
set(TS_FILES
        # Add translation files if needed
)

# Generate header files from UI files
qt6_wrap_ui(UI_HEADERS ${UI_FILES})

# Add the executable target
add_executable(MonkeyModelKit WIN32
        ${SOURCES}
        ${HEADERS}
        ${UI_FILES}
        ${UI_HEADERS}
        ${QM_FILES}
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
