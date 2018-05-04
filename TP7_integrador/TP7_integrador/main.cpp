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

//---Observers---//
#include "obs_stage.h"
#include "observer.h"

#define MAX_INPUT_SIZE 4 // Nombre del programa + "-IP" + [La IP] + iniciar/escuchar (según).
#define BACKGROUNDSONG "dbs.wav"


int main(int argc, char * argv[])
{
	netData net; //Objeto que contiene información sobre las computadoras en la red.
	if ((argc > 1 && argc <= MAX_INPUT_SIZE) && (parseCmdLine(argc, argv, &parseCallback, &net) != ERRORPARSE)) //Evaluación de los parámetros. Si son correctos se continúa con el programa, de lo contrario pasamos a imprimir el mensaje de error.
	{
		Stage stage;
		allegro_c allegroTools; //Inicialización de Allegro.
		allegroTools.load_music(BACKGROUNDSONG);
		allegroTools.play_music();

		//Controllers
		EventHandler eventHandler; //eventHandler me permitirá administrar múltiples controllers.
		allegro_ctrl al_ctrl(allegroTools.getEventQueue(), ALLEGROCONT);
		//network_ctrl nw_ctrl(&net, NETWORKCONT);

		eventHandler.loadController(&al_ctrl);
		//eventHandler.loadController(&nw_ctrl);

		//Observer
		obs_stage obstage(JUMPFILE, JUMPPICS, WALKFILE, WALKPICS, BACKGROUNDFILE, STAGEFILE);
		stage.addObserver(&obstage);

		
		// Worms
		WormData wormData; 
		Worm worm1(&wormData); //Creo un worm...
		stage.createWorms(&worm1); //...Y lo meto en el vector de worms del escenario.
		Worm worm2(&wormData);
		stage.createWorms(&worm2);

		client netClient;
		server netServer;

		//nw_ctrl.loadClient(&netClient);
		//nw_ctrl.loadServer(&netServer);

		while (!stage.isOver()) {
			eventHandler.getEvent();
			if (eventHandler.areThereActiveEvents()) //Si hay eventos activos, procedo al dispatcher. De lo contrario, sigo esperando eventos.
				eventHandler.HandleEventDispatch(stage);
		}


//		info data;

//		array< char[14], WALKPICS> walk = fillWalk("wwalk-F", ".png");
//		array<char[14], JUMPPICS> jump = fillJump("wjump-F", ".png");

//		data.load(walk, jump);

	}
	else
		cout << "Algo está mal papu, ¿Por qué no lo arreglas?" << endl;
}
