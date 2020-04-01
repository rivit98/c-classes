#ifndef SHAPE_H
#define SHAPE_H

#include <utility> // std::pair<>

/**
  Sprawdzają je testy automatyczne:
[8pkt] Zaimplementuj hierarchię klas zadaną na zajęciach.
    zadane atrybuty i metody,
    odpowiednie konstruktory (pusty konstruktor domyślny nie powinien być dostępny) inicjujące atrybuty (bez wartości domyślnych) z użyciem listy inicjalizującej,
[2pkt] Stwórz w funkcji main tablicę wskaźników do obiektów klas oraz wstawione do niej dynamicznie zaalokowane obiekty, testując wszystkie zaimplementowane konstruktory i metody.

  Sprawdzam ręcznie:
[3pkt] Należy wykorzystać metody wirtualne i czysto wirtualne we właściwych miejscach
       (pamiętając o wirtualnym destruktorze tam, gdzie jest to potrzebne).
[2pkt] Dla każdej klasy stwórz odpowiedni plik źródłowy i nagłówkowy.
[2pkt] Wszystkie klasy powinny być umieszczone we wspólnej przestrzeni nazw.

------ szczegolowa tresc:
Prosze o zaimplementowanie klasy czysto abstrakcyjnej Shape, majacej funkcje:
bool isIn(int x, int y) const, ktora dla podklas zwraca informacje czy dany punkt jest wewnatrz figury.
Po niej maja implementowac klasy:
Rectangle i Circle
oraz klasa-kompozyt ShapeComposite, ktora w konstruktorze przyjmuje dwie shared_ptr<Shape>
i operacje na zbiorach: INTERSECTION, SUM, DIFFERENCE
W oparciu o to bedzie mozna cala hierarchie figur polaczyc w jedno drzewo,
dla ktorego bedzie mozna zapytac czy dany punkt jest w hierarchii, czy nie.
Przyklad z kodu testow:
     21:            *******
     20:          ***********
     19:         *************
     18:        ***************
     17:       *****************
     16:      *******************
     15:      *******************
     14:     *********************
     13:     *********************
     12:     ***      ***      ***
     11:     ***      ***      ***
     10:     ***      ***      ***
      9:     ***      ***      ***
      8:     ***      ***      ***
      7:     ***      ***      ***
      6:     ***      ************
      5:     ***      ************
      4:     ***      ************
      3:     ***      ************
      2:     ***      ************
      1:     *********************
Opcjonalnie mozna sobie zaimplementowac klase Stage rysujaca na konsole.
**/

namespace Shapes
{
typedef std::pair<int,int> Point;

class Shape
{
public:
	virtual ~Shape() = default;
    virtual bool isIn(int x, int y) const = 0;
};
} // namespace Shapes

#endif // SHAPE_H
