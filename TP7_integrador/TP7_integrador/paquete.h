#pragma once

#include <string>

struct package_data {
public:
	char id_pkg;//Identificador de paquete, osea move y eso
	int id_worm;//Identificador del worm
	double x_coord;//
	double y_coord;
};
std::string compose_pkt(package_data data);
void decompose_data(std::string a, package_data& mydata);