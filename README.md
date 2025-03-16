# Symulacja Świateł Drogowych w C

## Opis Projektu
Projekt symuluje działanie świateł drogowych z użyciem języka C. Aplikacja przetwarza plik JSON z listą komend i zwraca plik JSON z informacją o samochodach, które opuściły skrzyżowanie po każdym kroku symulacji.

### Założenia projektowe
- Światła są standardowymi światłami kolizyjnymi.
- Samochód na zielonym świetle może jechać prosto i w prawo bez przeszkód.
- Aby skręcić w lewo, musi przepuścić pojazdy nadjeżdżające z naprzeciwka (chyba że te również skręcają w lewo).
- Podczas żółtego światła żaden samochód nie przejeżdża.
- Czas trwania zielonego światła zależy od liczby samochodów na danej drodze – każdy samochód wydłuża czas o jeden krok.

## Format Pliku Wejściowego
```json
{
  "commands": [
    {
      "type": "addVehicle",
      "vehicleId": "vehicle1",
      "startRoad": "south",
      "endRoad": "north"
    },
    {
      "type": "addVehicle",
      "vehicleId": "vehicle2",
      "startRoad": "north",
      "endRoad": "south"
    },
    {
      "type": "step"
    },
    {
      "type": "step"
    },
    {
      "type": "addVehicle",
      "vehicleId": "vehicle3",
      "startRoad": "west",
      "endRoad": "south"
    },
    {
      "type": "addVehicle",
      "vehicleId": "vehicle4",
      "startRoad": "west",
      "endRoad": "south"
    },
    {
      "type": "step"
    },
    {
      "type": "step"
    }
  ]
}
```

## Format Pliku Wyjściowego
```json
{
  "stepStatuses": [
    {
      "leftVehicles": [
        "vehicle1",
        "vehicle2"
      ]
    },
    {
      "leftVehicles": []
    },
    {
      "leftVehicles": [
        "vehicle3"
      ]
    },
    {
      "leftVehicles": [
        "vehicle4"
      ]
    }
  ]
}
```

## Struktura Projektu
```
traffic_lights_simulation/
│
├── CMakeLists.txt
├── src/
│   ├── main.c
│   ├── simulation.c
│   ├── lights.c
│   ├── parser.c
│   ├── vehicle.c
│   └── queue.c
│
├── include/
│   ├── simulation.h
│   ├── lights.h
│   ├── parser.h
│   ├── vehicle.h
│   └── queue.h
└── 
```

## Kompilacja
### Wymagania
- Kompilator C (np. GCC)
- CMake

### Kroki
1. Klonowanie repozytorium:
```bash
git clone https://github.com/vimzoomer/CrossroadsSimulator
cd CrossroadsSimulator
```

2. Utworzenie katalogu build i generowanie plików Makefile:
```bash
mkdir build
cd build
cmake ..
```

3. Kompilacja projektu:
```bash
make
```

## Uruchomienie
```bash
./crossroads input.json output.json
```

## Opis Logiki
1. Aplikacja parsuje plik JSON z komendami.
2. `addVehicle` dodaje pojazd na wskazanej drodze początkowej (startRoad) z celem dojazdu do drogi końcowej (endRoad).
3. `step` wykonuje krok symulacji, podczas którego przez skrzyżowanie przejeżdżają pierwsze pojazdy na drodze, która aktualnie ma zielone światło.
4. Program aktualizuje czas trwania, zadany w krokach, zielonego światła w zależności od liczby pojazdów na drodze.
5. Wynik jest zapisywany w pliku `output.json`.

## Szczegóły implementacyjne
- W obecnej wersji cała zawartość pliku JSON jest ładowana do pamięci, co może być nieefektywne przy dużej liczbie komend. 
- Tablica przechowująca komendy ma stały rozmiar wynoszący `MAX_COMMANDS`, co ogranicza elastyczność programu. 
- Światła są reprezentowane jako struktura zawierająca kolejki przechowujące pojazdy oczekujące na każdym ze świateł oraz obecny stan świateł i pozostały czas światła zielonego dla obu dróg.
- Algorytm zarządzania światłami opiera się na liczbie samochodów na każdej drodze, co umożliwia dynamiczne dostosowanie czasu trwania świateł. Czas jest dostosowywany po każdym cyklu, tj. po odliczeniu obu czasów świateł zielonych na obu drogach.

## Potencjalne ulepszenia
- Implementacja parsowania strumieniowego pliku JSON dla dużych plików wejściowych, instrukcja po instrukcji.
- Implementacja dynamicznej struktury danych, np. Linked Listy, do przechowywania komend aby umożliwić przetwarzanie dowolnych ich ilości.
- Rozszerzenie logiki o obsługę priorytetów dla pojazdów uprzywilejowanych czy dróg.
- Dodanie logów diagnostycznych dla analizy stanu świateł w każdym kroku symulacji.

## Wynik
Po uruchomieniu symulacji, plik `output.json` zawiera listę samochodów, które opuściły skrzyżowanie po każdym kroku symulacji.

## Testowanie
```bash
make test
```





