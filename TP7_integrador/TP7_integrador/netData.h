#pragma once

#include "allegro_ctrl.h"
#include <string>
#include <vector>
#include <fstream>
#include "server.h"
#include "client.h"

#define OPTION_QTY 1
#define PARAM_QTY 2

typedef enum { CLIENT, SERVER } mode;
#define IPFILE "DireccionesIP.txt"

#define NOIP "No IP"
#define IP "ip"

#define LISTEN "escuchar"
#define START "iniciar"




/*
netData:
			netData es una clase que contiene toda la informaci�n pertinente al manejo de red, incluyendo lista de IPs, estado (server o client), 
*/
class netData {
public:
	netData(server * sv, client * cl) {
		loadIPs();
		options[0] = IP;
		params[0] = LISTEN;
		params[1] = START;
		this->end = false;
		myIP = NOIP;
		currentMode = CLIENT;
		this ->netServer = sv;
		this ->netClient = cl;
	}

	//------Setters------//
	void setOwnIP(unsigned int i) { this->myIP = this->IPList.at(i); }
	void setIfShouldEnd(bool shouldI) { this->end = shouldI; }
	void setCurrentMode(mode newMode) { this->currentMode = newMode; }


	//------Getters------//
	std::string getOwnIP() { return this->myIP; }
	const char * getIPAt(int i) { return this->IPList.at(i).c_str(); } //Devuelve la IP en una posici�n dada del vector.
	const char * getOptions(unsigned int i) { return this->options[i]; } //Devuelve una opci�n en una posici�n dada del arreglo de opciones.
	const char * getParams(unsigned int i) { return this->params[i]; }//Devuelve una opci�n en una posici�n dada del arreglo de parametros.
	unsigned int getIPListSize() { return this->IPList.size(); } //Devuelve el tama�o del vector.
	bool getIfShouldEnd() { return this->end; } //Devuelve si el loop del main debe finalizar
	mode getCurrentMode() { return this->currentMode; } //Devuelve el modo actual de la maquina (Cliente o server)
	server * getServer() { return netServer; }
	client * getClient() { return netClient; }
	

private:

	std::string myIP; //La direccion IP de la computadora actual.
	std::vector<std::string> IPList; //La lista de IPs de todas las m�quinas involucradas
	std::vector<unsigned int> orderList; //El orden en el cual solicitamos que se ejecute la animaci�n entre m�quinas.
	unsigned int orderNumber; //Posici�n de la IP de esta m�quina en la lista de IPs.

	mode currentMode; //Modo actual de esta computadora
	bool end; //�Deber�a terminar la ejecuci�n del programa?


	//Modificados solo en el cosntructor//
	const char * options[OPTION_QTY]; //Opciones y par�metros para el parser.
	const char * params[PARAM_QTY];
	server * netServer;
	client * netClient;


	void loadIPs();
};