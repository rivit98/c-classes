#ifndef VECTOR_H
#define VECTOR_H

// author: Grzegorz Prowadzacy
#include "fraction.h"
#include "utils/memoryManagement.h"

/** 
Ćw3 [17pkt] Klasy z dynamiczną zawartością, wyjątki (UWAGA: To bardzo wazne zadanie, jeśli ktoś chce być programista C++ to w srodku nocy powinien umiec takie zadania robic!)
Plan zajęć:

    Panstwa zadaniem jest napisanie automatycznie rozszerzajacej sie tablicy dynamicznej (zwanej potocznie Vector), oraz funkcji do jej obslugi. Nasz Vector ma byc tablica elementow typu Fraction. Nasza implementacja wzorowana C++owym std::vector, aczkolwiek inna: http://www.cplusplus.com/reference/vector/vector/
    Nie wolno uzyc w srodku std::vector! Zaawansowani moga uzyc uzyc inteligetnych wskaznikow, jesli chca.
Nasza implementacja w razie automatycznego zwiekszania rozmiaru ma allokowac pamiec tylko o 1 wieksza!
    Ma to byc klasa Vector, ktora zawiera w sobie:
    - wskaznik na tablice dynamiczna (ang. data)
    - rozmiar aktualnie zaalokowanej tablicy dynamicznej (ang. capacity)
    - ilosc elementow w tablicy (ang. size)
    Ponadto proszę o zaimplementowanie metod zwracającej liczbę elementów w tablicy size(), wielkosc tablicy capacity()

    [6pkt] Uzupełnij drugą klasę o następujące elementy:
        - konstruktor przyjmujacy liczbe do wstepnej allokacji (z wartoscia domyslna 0)
        - destruktor (zwalniajacy pamiec),
        - konstruktor kopiujący (gleboko) oraz przenoszący,
        - operator podstawienia oraz przenoszący operator podstawienia,
        - metodę dodającą obiekt na koncu tablicy push_back()
        - operator dostepu po indeksie operator[](size_t index)
    [1pkt] Dostep po indeksie poza rozmiar tablicy (size) powinny być zgłaszane poprzez wyjątki std::out_of_range
    [1pkt] Auto-realokacja tablicy w razie braku elementow

    [1pkt] Deklaracje klasy powinny znaleźć się w odpowiednich plikach nagłówkowych, definicje metod i konstruktorów - w plikach źródłowych.
    [1pkt] Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne, metody/konstruktory/destruktory większe niż 1-linijkowe powinny być zadeklarowane w klasie, zdefiniowane poza klasą,

    [1pkt] Obiekty typów klasowych powinny być przekazywane do funkcji/metod przez referencje (zwykłe lub stałe), metody niemodyfikujące zawartości klasy powinny być oznaczane jako const.
    [1pkt] Wszystkie metody, które mogą być stałe proszę aby były

Uwaga:
    co się da na listę inicjalizacyjną konstruktora
**/

#include <memory>
#include <algorithm>
#include <stdexcept>

class Vector
{
private:
	size_t m_size;
	size_t m_capacity;
	std::unique_ptr<Fraction[]> m_data;

	int check_initial_size(int initSize) const;

public:
	Vector(size_t initSize = 0);
	Vector(const Vector& other);
	Vector(Vector&& other);
	~Vector() = default;

	Vector& operator=(const Vector& other);
	Vector& operator=(Vector&& other);
	Fraction& operator[](size_t index);
	const Fraction& operator[](size_t index) const;

	size_t capacity() const;
	size_t size() const;

	void push_back(Fraction f);
};

#endif // VECTOR_H
