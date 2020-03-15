#pragma once

#include <iostream>
#include <string>

class Cone{
	
private:
	static int s_cones;
	double m_height;
	double m_radius;
	const std::string class_name = "Cone";
	static const double default_height;
	static constexpr double default_radius = 2.0; 
	

public:
	Cone() : m_height(0.0), m_radius(0.0) { s_cones++; };
	Cone(double h, double r = default_height);
	~Cone();

	double get_height() const { return m_height; };
	double get_radius() const { return m_radius; };
	void set_height(double h) { m_height = h; };
	void set_radius(double r) { m_radius = r; };

	void print_data() const;


	void save(std::ostream& os) const;
	void read(std::istream& is);

	const std::string get_class_name() const { return class_name; };
	static int get_cones_num() { return s_cones; };
	static const double get_default_height() { return default_height; };
	static constexpr double get_default_radius() { return default_radius; };
};