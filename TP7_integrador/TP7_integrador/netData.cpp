#include "netData.h"

void netData::loadIPs() {

	std::ifstream dirFile;
	dirFile.open(IPFILE); //Abrimos el archivo .txt con las direcciones IP...
	std::string auxString; //...Y creamos un string auxiliar para poder trabajarlas.
	while (dirFile.good()) { // ¿Aún hay direcciones que agarrar?
		getline(dirFile, auxString); //Si las hay, la ponemos en el string auxiliar...
		this->IPList.push_back(auxString); //... Y la ponemos al final del vector de strings.
	}
}