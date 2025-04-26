cmake_minimum_required(VERSION 3.14)

project(stacje_radarowe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Wyszukaj pakiet Qt6 z wymaganymi komponentami
find_package(Qt6 REQUIRED COMPONENTS Widgets Network Charts)

# Pliki źródłowe
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    apiworker.h  # Added for multithreading
)

# Tworzenie pliku wykonywalnego
qt_add_executable(stacje_radarowe
    ${PROJECT_SOURCES}
)

# Podpięcie bibliotek Qt
target_link_libraries(stacje_radarowe
    PRIVATE Qt6::Widgets Qt6::Network Qt6::Charts
)

# Enable testing
enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

# Test executable
add_executable(tests
    tests/test_main.cpp
    mainwindow.cpp  # Include source files to test
    apiworker.h     # Include ApiWorker for testing
)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(tests PRIVATE Qt6::Widgets Qt6::Network Qt6::Charts GTest::GTest GTest::Main)
gtest_discover_tests(tests)
