#pragma once

#include <string>
#include <cstdint>
#define EMPTY (-1)
#define ERR_STR "ERR"
#define PKGSIZE 8 //Tamaño del paquete en bytes. (Se necesita constante y aparte sizeof devuelve 12 para la estructura, pero 8 para la suma de los miembros individuales, que es lo que nos importa).

typedef struct{
public:
	uint8_t header;//1 byte header
	uint8_t action;//un byte, las acciones son D,I,J,T
	uint32_t id_worm;//Id worm 4bytes
	uint16_t x_coord;//Solo es pasada en el primer imready
	void clean()
	{
		header = EMPTY;
		action = EMPTY;
		id_worm = EMPTY;
		x_coord = EMPTY;
	}
}  package_data;

#define I_AM_READY 0x20
#define ACK 0x01
#define ACKS 0x00
#define MOVE 0x30
#define QUIT 0xE0
#define ERROR 0xFF

std::string compose_pkt(package_data data);
void decompose_data(std::string a, package_data& mydata);
bool checkValidPkgCompos(package_data data);