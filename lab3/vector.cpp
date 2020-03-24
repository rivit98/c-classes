#include "vector.h"


int Vector::check_initial_size(int initSize) const{
	if(initSize < 0){
		throw std::invalid_argument("initSize musi byc wieksze od 0");
	}

	return initSize;
}

Vector::Vector(size_t initSize)
		: m_size(0),
		m_capacity(check_initial_size(initSize)),
		m_data(initSize ? std::unique_ptr<Fraction[]>(new Fraction[m_capacity]) : nullptr){
}

Vector::Vector(const Vector& other) 
		: m_size(other.m_size),
		m_capacity(other.m_capacity),
		m_data(m_capacity ? std::unique_ptr<Fraction[]>(new Fraction[m_capacity]) : nullptr){

	if(m_data != nullptr){
		std::copy(other.m_data.get(), other.m_data.get() + other.m_capacity, m_data.get());
	}
}

Vector& Vector::operator=(const Vector& other){
	if(this == &other){
		return *this;
	}
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	m_data = m_capacity ? std::unique_ptr<Fraction[]>(new Fraction[m_capacity]) : nullptr;
	if(m_data != nullptr){
		std::copy(other.m_data.get(), other.m_data.get() + other.m_capacity, m_data.get());
	}

	return *this;
}

Vector::Vector(Vector&& other)
		: Vector(){
			
	*this = std::move(other);
}

Vector& Vector::operator=(Vector&& other){
	if(this == &other){
		return *this;
	}
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	m_data = std::move(other.m_data);
	other.m_size = other.m_capacity = 0;

	return *this;
}

size_t Vector::size() const{
	return m_size;
}

size_t Vector::capacity() const{
	return m_capacity;
}

void Vector::push_back(Fraction f){
	if(m_size == m_capacity){
		m_capacity++;
		Fraction* temp = m_data.release();
		Fraction* new_data = new Fraction[m_capacity];
		std::copy(temp, temp+m_size, new_data);
		delete[] temp;
		m_data.reset(new_data);
	}
	
	m_data.get()[m_size++] = f;
}

Fraction& Vector::operator[](size_t index){
	if(index >= m_size){
		throw std::out_of_range("index > size");
	}

	return m_data.get()[index];
}

const Fraction& Vector::operator[](size_t index) const{
	if(index >= m_size){
		throw std::out_of_range("index > size");
	}

	return m_data.get()[index];
}