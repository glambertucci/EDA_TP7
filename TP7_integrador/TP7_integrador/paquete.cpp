#include "paquete.h"
#include <cstdint>
using namespace std;
//funciones internas
//Compose
std::string acks_compose(package_data data);
std::string ack_compose(package_data data);
std::string imr_compose(package_data data);
std::string move_compose(package_data data);
std::string quit_compose(package_data data);
std::string error_compose(package_data data);

//util
std::string switchendianfier(uint16_t *param);
std::string switchendianfier(uint32_t *param);

//decompose
void ack_decompose(package_data& mydata, std::string a);
void imr_decompose(package_data& mydata, std::string a);
void move_decompose(package_data& mydata, std::string a);

std::string switchendianfier(uint16_t * param)
{
	int8_t pp[2];
	for (int i = 0; i < 2; i++)
		pp[1 - i] = *(((uint8_t*)param) + i); //Aprovechamos el casteo de punteros para descomponer el ID y rearmarlo en el string.
	string a = (char*)pp;
	return a;
}
std::string switchendianfier(uint32_t * param)
{
	uint8_t pp[4];
	for (int i = 0; i < 4; i++)
		pp[3 - i] = *((uint8_t *) param + i); //Aprovechamos el casteo de punteros para descomponer el ID y rearmarlo en el string.
	string a;
	for (int i=0;i<4;i++)
		a += pp[i];
	return a;
}

std::string compose_pkt(package_data data)
{
	std::string result;
	switch (data.header)
	{
	case ACKS:
		result = acks_compose(data); break;//el ack para imr y para quit
	case ACK:
		result = ack_compose(data);break;
	case I_AM_READY:
		result = imr_compose(data); break;
	case MOVE :
		result = move_compose(data); break;
	case QUIT:
		result = quit_compose(data);
	case ERROR:
		result = error_compose(data);
	};
	return result;
}
std::string move_compose(package_data data){
	string pkt;
	pkt+= data.header;
	pkt += data.action;
	//pkt += switchendianfier(&data.id_worm);
	uint8_t pp[4];
	for (int i = 0; i < 4; i++)
		pp[3 - i] = *((uint8_t *)(&data.id_worm) + i); //Aprovechamos el casteo de punteros para descomponer el ID y rearmarlo en el string.
	for (int i = 0; i<4; i++)
		pkt += pp[i];
	
	return pkt;
}
std::string imr_compose(package_data data)
{
	string pkt;
	pkt += data.header;
	uint8_t * pxc=(uint8_t *) &(data.x_coord);
	pkt += (*(pxc + 1));
	pkt += (*pxc);
	pkt += '\0';
	return pkt;
}
std::string quit_compose(package_data data)
{
	string pkt;
	return 	pkt += data.header;
}
std::string error_compose(package_data data)
{
	string pkt;
	return 	pkt += data.header;
}
std::string ack_compose(package_data data)
{
	std::string pkt;
	pkt += data.header;
	pkt += switchendianfier(&data.x_coord);//pasar a big endian
	return pkt;
}
std::string acks_compose(package_data data)
{
	string pkt;
	return pkt += data.header;
}

//msg, decompose, no necesitas el de los otros porque solo viene el header
void decompose_data(std::string a, package_data& mydata)
{
	mydata.header = a[0];

	switch (mydata.header)
	{
	case ACK:
		ack_decompose(mydata,a); break;
	case I_AM_READY:
		imr_decompose(mydata,a); break;
	case MOVE:
		move_decompose(mydata,a); break;
	};
}
void ack_decompose(package_data& mydata, std::string a) {
	int32_t num;
	int8_t * arr= (int8_t *) &num;
	for (int i = 0; i < 4; i++)
		arr[0] = a[4 - i]; //lo recibo en big endian
	mydata.id_worm=num;
}
void imr_decompose(package_data& mydata, std::string a) {
	int16_t num;
	int8_t * arr = (int8_t *)&num;
	for (int i = 0; i < 2; i++)
		arr[i] = a[2 - i]; //lo recibo en big endian
	mydata.x_coord = num;
}
void move_decompose(package_data& mydata, std::string a) {
	mydata.action = a[1];//Primeor header despues action
	int32_t num;
	int8_t * arr = (int8_t *)&num;
	for (int i = 0; i < 4; i++)
		arr[i] = a[5 - i]; //lo recibo en big endian
	mydata.id_worm = num;
}

bool checkValidPkgCompos(package_data pkg) {

	bool valid = true;

	if (pkg.header != I_AM_READY && pkg.header != ACK && pkg.header != ACKS && pkg.header != MOVE && pkg.header != QUIT && pkg.header != ERROR) {
		valid = false;
	}
	else if(pkg.header == MOVE && (pkg.action != 'D' && pkg.action != 'I' && pkg.action != 'J' && pkg.action != 'T'))
	{
		valid = false;
	}

	return valid;
}


#define I_AM_READY 0x20
#define ACK 0x01
#define ACKS 0x00
#define MOVE 0x30
#define QUIT 0xE0
#define ERROR 0xFF
