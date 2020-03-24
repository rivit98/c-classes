#include "fraction.h"

int Fraction::check_denominator(int x) const{
	if(x == 0){
		throw std::invalid_argument("Mianownik nie moze byc 0");
	}
	return x;
}

Fraction::Fraction(int n, int d) :
								numerator(n),
								denominator(check_denominator(d)){
}

int Fraction::getDenominator() const{
	return denominator;
}

int Fraction::getNumerator() const{
	return numerator;
}

void Fraction::setDenominator(int d){
	denominator = check_denominator(d);
}

void Fraction::setNumerator(int n){
	numerator = n;
}

void Fraction::reduce(){
	int gcd = std::gcd(this->numerator, this->denominator);
	this->numerator /= gcd;
	this->denominator /= gcd;
}

Fraction Fraction::operator*(const Fraction& other) const{
	Fraction res(this->numerator * other.numerator, this->denominator * other.denominator);
	
	res.reduce();
	return res;
}

Fraction Fraction::operator+(const Fraction& other) const{
	Fraction res(
		(this->numerator * other.denominator) + (this->denominator * other.numerator),
		this->denominator * other.denominator
	);

	res.reduce();
	return res;
}