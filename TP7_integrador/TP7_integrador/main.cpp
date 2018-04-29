#include <iostream>
#include <vector>
#include <fstream>
#include <ctype.h>


//-----Parser-----//
#include "parseCmdLine.h"
#include "parser.h"

//-------Net------//
#include "paquete.h"
#include "netData.h"
#include "server.h"
#include "client.h"

//--Miscellanous--//
#include "general.h"
#include "EventHandler.h"

//-----Worms-----//
#include "Stage.h"

//----Graphics----//
#include "allegroClass.h"
#include "bitinit.h"
#include "init_arr.h"

#include "obs_stage.h"
#include "observer.h"

#define MAX_INPUT_SIZE 4 // Nombre del programa + "-IP" + [La IP] + iniciar/escuchar (según).
#define BACKGROUNDSONG "dbs.wav"
/*
int main(int argc, char * argv[])
{

	netData net; //Objeto que contiene información sobre las computadoras en la red.


	if ((argc > 1 && argc <= MAX_INPUT_SIZE) && (parseCmdLine(argc, argv, &parseCallback, &net) != ERRORPARSE)) //Evaluación de los parámetros. Si son correctos se continúa con el programa, de lo contrario pasamos a imprimir el mensaje de error.
	{
		allegro_c allegroTools; //Inicialización de Allegro.
		allegroTools.load_music(BACKGROUNDSONG);
		allegroTools.play_music();

		EventHandler eventHandler;
		Stage stage;
		info data;

		array< char[14], WALKPICS> walk = fillWalk("wwalk-F", ".png");
		array<char[14], JUMPPICS> jump = fillJump("wjump-F", ".png");

		data.load(walk, jump);

		stage.createWorms(&data);
		stage.loadImages("Scenario.png", "background.png");

		while (!net.getIfShouldEnd())
		{
			while (eventHandler.getEvent(allegroTools.getEventQueue()))
			{
				if (eventHandler.isThereEvent())
				{
					eventHandler.handleEventDispatcher(stage);
					allegroTools.updateDisplay();
				}
			}
			if (net.getCurrentMode() == SERVER)
			{													//Actuo de server

			}
		}

		data.unload(WALKPICS, JUMPPICS);
		allegroTools.~allegro_c();
	}
	
	else {
		std::cout << "Error: Wrong parameters or options." << std::endl;
		std::cout << std::endl;
		std::cout << "You MUST send " << std::endl;
		std::cout << "-IP [Your IP]" << std::endl;
		std::cout << "Additionally, you may introduce the 'iniciar' parameter in order to configure the program as a server." << std::endl;
		std::cout << std::endl;
		std::cout << "Please execute the program again with neither excess parameters/options nor invalid ones." << std::endl;
	}


	std::cout << "Press any key to end the program." << std::endl;
	getchar();

	return 0;
}
*/

int main(int argc, char * argv[])
{
	netData net; //Objeto que contiene información sobre las computadoras en la red.
	if ((argc > 1 && argc <= MAX_INPUT_SIZE) && (parseCmdLine(argc, argv, &parseCallback, &net) != ERRORPARSE)) //Evaluación de los parámetros. Si son correctos se continúa con el programa, de lo contrario pasamos a imprimir el mensaje de error.
	{
		Stage stage;
		allegro_c allegroTools; //Inicialización de Allegro.
		allegroTools.load_music(BACKGROUNDSONG);
		allegroTools.play_music();
		//Controller
		EventHandler eventHandler;
		allegro_ctrl al_ctrl(allegroTools.getEventQueue());
		eventHandler.loadController(&al_ctrl);
		//Observer
		obs_stage obstage(JUMPFILE, JUMPPICS, WALKFILE, WALKPICS, BACKGROUNDFILE, STAGEFILE);
		stage.addObserver(&obstage);
		// Falta el observer de network y cargarlo 
		// Worms

		WormData wormData;
		Worm worm1(&wormData);
		stage.createWorms(&worm1);
		//Worm worm2(&wormData);
		//stage.createWorms(&worm2); Lo descomento cuadno tenga networking

		bool quit = false;
		while (!stage.isOver()) {
			eventHandler.getEvent();
			if (eventHandler.areThereActiveEvents())
				eventHandler.HandleEventDispatch(stage);
		}


//		info data;

//		array< char[14], WALKPICS> walk = fillWalk("wwalk-F", ".png");
//		array<char[14], JUMPPICS> jump = fillJump("wjump-F", ".png");

//		data.load(walk, jump);

	}
	else
		cout << "Puto" << endl;
}
