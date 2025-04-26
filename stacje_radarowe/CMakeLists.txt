cmake_minimum_required(VERSION 3.5)

project(stacje_radarowe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Network Charts REQUIRED)

# Biblioteka współdzielona dla MainWindow
add_library(mainwindow_lib STATIC
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)
target_link_libraries(mainwindow_lib PRIVATE Qt6::Widgets Qt6::Network Qt6::Charts)

# Główna aplikacja
set(PROJECT_SOURCES
    main.cpp
)
add_executable(stacje_radarowe ${PROJECT_SOURCES})
target_link_libraries(stacje_radarowe PRIVATE mainwindow_lib Qt6::Widgets Qt6::Network Qt6::Charts)

# Włącz testowanie
enable_testing()

# Ustaw vcpkg jako toolchain
set(CMAKE_TOOLCHAIN_FILE "F:/stacje radarowe/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Dodaj ścieżkę do vcpkg
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};F:/stacje radarowe/vcpkg/installed/x64-windows")

# Znajdź Google Test
find_package(GTest CONFIG REQUIRED)

# Dodaj folder tests
add_executable(tests
    tests/test_main.cpp
)
set_target_properties(tests PROPERTIES AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR})
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(tests PRIVATE mainwindow_lib Qt6::Widgets Qt6::Network Qt6::Charts GTest::gtest GTest::gtest_main)

# Dodaj testy do CTest
add_test(NAME MyTests COMMAND tests)
