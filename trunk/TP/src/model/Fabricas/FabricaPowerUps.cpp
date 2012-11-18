#include "FabricaPowerUps.h"
#include "FabricaActivaEspeciales.h"
#include "FabricaVidasExtra.h"
#include "FabricaStones.h"
#include "FabricaInvencibilidad.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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
	float equiprobable = (float) 100 / fabricas->size();
	float rnd;
	do{
		rnd = tirarRandom();
	}while (rnd == 1 || rnd == 0);

	unsigned int i = 0;
	int acum = 0;

	while (acum < (rnd*100)){
		acum += equiprobable;
		i++;
	}
	if ((i-1) >= fabricas->size())
		return eleccionFabrica();

	return (i-1);

}

float FabricaPowerUps::tirarRandom(){
	float max = (float)RAND_MAX + 1;
	float tuvieja = ((float) rand() / max) ;
	return tuvieja;
}
