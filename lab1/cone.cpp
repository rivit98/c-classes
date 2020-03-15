#include "cone.hpp"

int Cone::s_cones = 0;
const double Cone::default_height = 1.0;

Cone::Cone(double h, double r): m_height(h), m_radius(r){
	s_cones++;
}

Cone::~Cone(){
	s_cones--;
}


void Cone::print_data() const{
	std::cout << "Height: " << this->m_height << " | Radius: " << this->m_radius << std::endl;
}

void Cone::save(std::ostream& os) const{
	os << this->m_height;
	os << " ";
	os << this->m_radius;
	os << std::endl;
}

void Cone::read(std::istream& is){
	std::cout << "Podaj wysokosc: ";
	is >> this->m_height;
	std::cout << "Podaj promien: ";
	is >> this->m_radius;
	std::cout << std::endl;
}