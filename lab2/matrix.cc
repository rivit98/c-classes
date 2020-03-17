#include <iostream>
#include <sstream>

using namespace std;
using uint = unsigned int;

#include "matrix.h"

TwoDimensionMatrix::TwoDimensionMatrix(const TwoDimensionMatrix& other){
	for(uint i = 0; i < m_size; i++){
		for(uint j = 0; j < m_size; j++){
			this->m_data[i][j] = other.get(i, j);
		}
	}
}

TwoDimensionMatrix::TwoDimensionMatrix(const MatrixElement matrix[m_size][m_size]){
	for(uint i = 0; i < m_size; i++){
		for(uint j = 0; j < m_size; j++){
			this->m_data[i][j] = matrix[i][j];
		}
	}
}

int TwoDimensionMatrix::get(unsigned int x, unsigned int y) const{
	return this->m_data[x][y];
}

std::ostringstream& operator<<(std::ostringstream& os, const TwoDimensionMatrix& m){
	for(uint i = 0; i < TwoDimensionMatrix::getSize(); i++){
		for(uint j = 0; j < TwoDimensionMatrix::getSize(); j++){
			os << m.get(i, j) << ", "; //ugly comma at the end :(
		}
	}

	return os;
}

TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2){
	int buf[TwoDimensionMatrix::getSize()][TwoDimensionMatrix::getSize()];
	for(uint i = 0; i < TwoDimensionMatrix::getSize(); i++){
		for(uint j = 0; j < TwoDimensionMatrix::getSize(); j++){
			buf[i][j] = matrix1.get(i, j) + matrix2.get(i, j);
		}
	}

	return TwoDimensionMatrix(buf);	
}

TwoDimensionMatrix& TwoDimensionMatrix::operator*=(MatrixElement number){
	for(uint i = 0; i < TwoDimensionMatrix::getSize(); i++){
		for(uint j = 0; j < TwoDimensionMatrix::getSize(); j++){
			this->m_data[i][j] *= number;
		}
	}

	return *this;
}

TwoDimensionMatrix TwoDimensionMatrix::operator&&(const TwoDimensionMatrix& matrix) const{
	int buf[TwoDimensionMatrix::getSize()][TwoDimensionMatrix::getSize()];
	for(uint i = 0; i < TwoDimensionMatrix::getSize(); i++){
		for(uint j = 0; j < TwoDimensionMatrix::getSize(); j++){
			buf[i][j] = this->get(i, j) && matrix.get(i, j);
		}
	}

	return TwoDimensionMatrix(buf);
}

MatrixElement* TwoDimensionMatrix::operator[](size_t i){
	return m_data[i];
}

const MatrixElement* TwoDimensionMatrix::operator[](size_t i) const{
	return m_data[i];
}