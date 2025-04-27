Stacje Radarowe - Aplikacja Qt do analizy danych pomiarowych
Projekt "Stacje Radarowe" to aplikacja stworzona w Qt, która umożliwia pobieranie i wizualizację danych środowiskowych z API GIOŚ (Główny Inspektorat Ochrony Środowiska).

Program pozwala na:

Wyszukiwanie stacji pomiarowych na podstawie miasta,

Wybieranie czujników i zakresu dat,

Pobieranie oraz analizę danych (minimum, maksimum, średnia),

Prezentację wyników na wykresach (Qt Charts),

Tryb offline — obsługa danych lokalnych w przypadku braku internetu.

Wymagania:

CMake w wersji co najmniej 3.5

Qt6 (moduły: Widgets, Network, Charts)

Google Test (dla testów jednostkowych)

vcpkg (dla zarządzania bibliotekami)

Instalacja i budowanie:

Klonowanie repozytorium:

git clone https://github.com/Nexon228/stacje_radarowe.git cd stacje_radarowe

Instalacja zależności (przez vcpkg):

vcpkg install qt6-base qt6-charts gtest

Upewnij się, że w CMake masz ustawioną zmienną CMAKE_TOOLCHAIN_FILE wskazującą na plik vcpkg.cmake.

Budowanie projektu:

cmake -B build -S . cmake --build build

Uruchamianie aplikacji:

Po zbudowaniu aplikacji znajdziesz plik wykonywalny w katalogu build.

cd build ./stacje_radarowe

Testy jednostkowe:

Budowanie testów:

cmake --build build --target tests

Uruchamianie testów:

cd build ctest

lub

./tests

Testy są napisane w oparciu o Google Test.

Funkcje aplikacji:

Wyszukiwanie stacji: wpisz nazwę miasta i pobierz dostępne stacje pomiarowe.

Wybór sensora: wybierz czujnik przypisany do stacji.

Zakres dat: wybierz predefiniowany lub własny zakres dat.

Wizualizacja danych: wyświetlanie danych na wykresie czasowym.

Statystyki: automatyczne obliczanie średniej, minimum i maksimum.

Tryb offline: możliwość korzystania z zapisanych danych w przypadku braku internetu.

Autor:

Projekt stworzony przez Nexon228.

Licencja:

Projekt udostępniany na licencji MIT.
