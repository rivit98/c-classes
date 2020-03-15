#include <iostream>
#include "cone.hpp"


int main(){

	Cone c;
	c.print_data();
	std::cout << "Cones: " << Cone::get_cones_num() << std::endl;

	Cone c2(2.0, 2.0);
	c2.print_data();
	std::cout << "Cones: " << Cone::get_cones_num() << std::endl;

	Cone c3(3.0);
	c3.print_data();
	std::cout << "Cones: " << Cone::get_cones_num() << std::endl;

	c3.save(std::cout);

	c2.read(std::cin);
	c2.print_data();


	std::cout << std::endl;
	std::cout << c.get_class_name() << std::endl;
	std::cout << Cone::get_default_height() << std::endl;
	std::cout << Cone::get_default_radius() << std::endl;

	return 0;
}