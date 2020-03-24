#ifndef FRACTION_H
#define FRACTION_H

/** Implementacja ulamka:
[3pkt] Zaimplementuj klase Ulamek (ang. Fraction), posiadająca licznik (ang. numerator) i mianownik (ang. denominator).
       Powinna zawierac jeden konstruktor ustawiajacy licznik i mianownik (domyslne wartosci licznika=0 a mianownika domyslna 1)
       Gettery i settery do wartosci licznika i mianownika
       operator+ dla ulamka zwracajacy ulamek
       operator* dla ulamka zwracajacy ulamek
[1pkt] Niepoprawny mianownik powinien byc zglaszany przez wyjatek std::invalid_argument.
[1pkt] Prosze o skracanie ulamkow po operacji + i * (pomocny moze sie okazac algorytm euklidesa), oczywiscie tutaj robimy tylko dla przypadkow dodatnich
**/

#include <stdexcept>
#include <numeric>

class Fraction
{
private:
	int numerator;
	int denominator;

	int check_denominator(int x) const;

public:
	Fraction(int n=0, int d=1);
	~Fraction() = default;

	int getNumerator() const;
	int getDenominator() const;
	void setNumerator(int n);
	void setDenominator(int d);
	void reduce();

	Fraction operator+(const Fraction& other) const;
	Fraction operator*(const Fraction& other) const;
};

#endif // FRACTION_H
