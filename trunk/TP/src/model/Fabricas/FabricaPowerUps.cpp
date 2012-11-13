#include "FabricaPowerUps.h"
#include "FabricaActivaEspeciales.h"
#include "FabricaVidasExtra.h"
#include "FabricaStones.h"
#include "FabricaInvencibilidad.h"
#include <stdlib.h>
#include <time.h>

FabricaPowerUps::FabricaPowerUps() {
	fabricas = new std::vector<FabricaActualizable*>();

	fabricas->push_back(new FabricaActivaEspeciales());
	fabricas->push_back(new FabricaVidasExtra());
	fabricas->push_back(new FabricaStones());
	fabricas->push_back(new FabricaInvencibilidad());
}

FabricaPowerUps::~FabricaPowerUps() {
	for (unsigned int i = 0; i < fabricas->size(); i++){
		delete (fabricas->at(i));
	}
	fabricas->clear();
	delete(fabricas);
}

void FabricaPowerUps::fabricar(Posicion* pos, int valor){
	fabricas->at(eleccionFabrica())->fabricar(pos, valor);
}

int FabricaPowerUps::eleccionFabrica(){
	float equiprobable = 100 / fabricas->size();
	float rnd = tirarRandom();

	unsigned int i = 0;
	int acum = 0;

	while (acum < (rnd * 100)){
		acum += equiprobable;
		i++;
	}

	return (i-1);

}

float FabricaPowerUps::tirarRandom(){
	float u;
	do{
		u =(rand() % 1000) + 1;
		float w;
		do{
			w =(rand() % 1000);
		}while (w >= u);
		u = w / u;
	}while(u == 1);
	return u;
}
