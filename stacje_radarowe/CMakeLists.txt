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
)

# Tworzenie pliku wykonywalnego
qt_add_executable(stacje_radarowe
    ${PROJECT_SOURCES}
)

# Podpięcie bibliotek Qt
target_link_libraries(stacje_radarowe
    PRIVATE Qt6::Widgets Qt6::Network Qt6::Charts
)
