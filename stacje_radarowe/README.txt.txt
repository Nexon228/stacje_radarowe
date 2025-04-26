# Air Quality Monitoring Application

## Overview
This application monitors air quality in Poland by fetching data from the GIOŚ API. It supports online and offline modes, displays data on a chart, and performs statistical analysis (min, max, average, trend).

## Requirements
- Qt 6.9.0 or higher
- CMake 3.14 or higher
- Google Test (for unit tests)
- Doxygen (for documentation generation)
- MinGW (for Windows)

## Building the Application
1. Clone the repository from GitHub.
2. Create a build directory: `mkdir build && cd build`
3. Run CMake: `cmake .. -G "Ninja"`
4. Build the application: `ninja`

## Running the Application
1. Navigate to the build directory.
2. Run the executable: `./stacje_radarowe`

## Running Unit Tests
1. In the build directory, build the tests: `ninja tests`
2. Run the tests: `ctest`

## Generating Documentation
1. Install Doxygen.
2. Run: `doxygen Doxyfile`
3. Open `docs/html/index.html` to view the documentation.

## Usage
1. Enter a city name and click "Pobierz stacje" to fetch stations.
2. Select a station and a sensor.
3. Choose a time range and click "Pobierz dane" to fetch and display data.
4. Use the "Offline" button to work with locally cached data if the network is unavailable.