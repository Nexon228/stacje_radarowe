# Stacje Radarowe

**Aplikacja Qt do analizy danych pomiarowych.**

---

## Funkcje aplikacji

- **Wyszukiwanie stacji**: Wpisz nazwę miasta i pobierz stacje pomiarowe.
- **Wybór sensora**: Wybierz czujnik dla wybranej stacji.
- **Zakres dat**: Wybierz zakres pomiarów lub podaj własny.
- **Wizualizacja danych**: Dane wyświetlane są na wykresach Qt Charts.
- **Statystyki**: Obliczanie minimum, maksimum i średniej wartości.
- **Tryb offline**: Wczytywanie danych z plików zapisanych lokalnie.

---

## Instalacja

1. Klonowanie repozytorium:
    ```bash
    git clone https://github.com/Nexon228/stacje_radarowe.git
    cd stacje_radarowe
    ```

2. Instalacja zależności:
    ```bash
    vcpkg install qt6-base qt6-charts gtest
    ```

3. Budowanie projektu:
    ```bash
    cmake -B build -S .
    cmake --build build
    ```

---

## Uruchamianie aplikacji

```bash
cd build
./stacje_radarowe
