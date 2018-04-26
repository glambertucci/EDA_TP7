#include "paquete.h"
using namespace std;
string compose_pkt(package_data data)
{
	char arr[2] = { data.id_pkg, 0 };//Lo hacemos solo para dos worms no?
	string result = arr;
	result += data.id_worm;
	result += data.x_coord;
	result += data.y_coord;
	return result;
}
void decompose_data(std::string a, package_data& mydata)
{
	mydata.id_pkg = a[0]; //Bueno, esto es bastante mogolitronico tipo, siempre deberia ser asi 
	mydata.id_worm = a[1];
	mydata.x_coord = a[2];
	mydata.y_coord = a[3];
}