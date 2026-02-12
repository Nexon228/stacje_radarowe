cmake_minimum_required(VERSION 3.10)

project(stacje_radarowe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ustaw vcpkg jako toolchain (poprawiona ścieżka)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Dodaj ścieżki do vcpkg i Qt (poprawiona ścieżka do vcpkg)
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_SOURCE_DIR}/../vcpkg/installed/x64-windows;F:/Qt/6.9.0/mingw_64")

# Znajdź Qt6
find_package(Qt6 COMPONENTS Widgets Network Charts Test REQUIRED)
if (NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 not found. Please ensure it is installed and CMAKE_PREFIX_PATH is set correctly.")
endif()

# Ręcznie ustaw GTest i GMock (poprawione ścieżki)
set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/../googletest")
set(GTEST_INCLUDE_DIRS "${GTEST_ROOT}/googletest/include" "${GTEST_ROOT}/googlemock/include")
set(GTEST_LIBRARY "${GTEST_ROOT}/build/lib/libgtest.a")
set(GTEST_MAIN_LIBRARY "${GTEST_ROOT}/build/lib/libgtest_main.a")
set(GMOCK_LIBRARY "${GTEST_ROOT}/build/lib/libgmock.a")
set(GMOCK_MAIN_LIBRARY "${GTEST_ROOT}/build/lib/libgmock_main.a")

# Sprawdź, czy pliki istnieją
if (NOT EXISTS "${GTEST_LIBRARY}")
    message(FATAL_ERROR "GTest library not found at ${GTEST_LIBRARY}. Please build GTest in ${GTEST_ROOT}/build.")
endif()
if (NOT EXISTS "${GTEST_MAIN_LIBRARY}")
    message(FATAL_ERROR "GTest main library not found at ${GTEST_MAIN_LIBRARY}.")
endif()
if (NOT EXISTS "${GMOCK_LIBRARY}")
    message(FATAL_ERROR "GMock library not found at ${GMOCK_LIBRARY}.")
endif()
if (NOT EXISTS "${GMOCK_MAIN_LIBRARY}")
    message(FATAL_ERROR "GMock main library not found at ${GMOCK_MAIN_LIBRARY}.")
endif()

# Wyświetl informacje o GTest dla diagnostyki
message(STATUS "GTest include dirs: ${GTEST_INCLUDE_DIRS}")
message(STATUS "GTest library: ${GTEST_LIBRARY}")
message(STATUS "GTest main library: ${GTEST_MAIN_LIBRARY}")
message(STATUS "GMock library: ${GMOCK_LIBRARY}")
message(STATUS "GMock main library: ${GMOCK_MAIN_LIBRARY}")

# Biblioteka współdzielona dla MainWindow
add_library(mainwindow_lib STATIC
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    apiworker.cpp
    apiworker.h
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

# Dodaj folder tests
add_executable(tests
    tests/test_main.cpp
)
set_target_properties(tests PROPERTIES AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR})
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR} ${GTEST_INCLUDE_DIRS})
target_link_libraries(tests PRIVATE mainwindow_lib Qt6::Widgets Qt6::Network Qt6::Charts Qt6::Test ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY})

# Dodaj testy do CTest
add_test(NAME MyTests COMMAND tests)
