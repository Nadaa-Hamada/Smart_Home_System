cmake_minimum_required(VERSION 3.16)

project(SmartHome3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets SerialPort)

set(SOURCES
    main.cpp
    mainwindow.cpp
    serialreader.cpp
    gpio.cpp
)

set(HEADERS
    mainwindow.h
    serialreader.h
    gpio.h
)

set(UI
    mainwindow.ui
)

qt_add_executable(SmartHome3
    ${SOURCES}
    ${HEADERS}
    ${UI}
    resources.qrc
)

target_link_libraries(SmartHome3 PRIVATE Qt6::Widgets Qt6::SerialPort)

set_target_properties(SmartHome3 PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SmartHome3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(SmartHome3)
