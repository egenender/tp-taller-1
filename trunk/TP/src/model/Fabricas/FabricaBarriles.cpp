#include "FabricaBarriles.h"
#include "../Area.h"

FabricaBarriles::FabricaBarriles() {

}

FabricaBarriles::~FabricaBarriles() {

}

void FabricaBarriles::fabricar(Posicion* inicial, int valorInicial){
	int anchoBarril, altoBarril, velocidadBarril;

	//Por ahora los seteo a mano, pero necesito conseguir esta informacion de algun lado!
	anchoBarril = 70;
	altoBarril = 40;
	velocidadBarril = 10;

	Area* sup = new Area(anchoBarril, altoBarril, inicial);
	Barril* barril = new Barril (" ", sup, velocidadBarril, valorInicial);

	terminarCreacion(barril);
}

void FabricaBarriles::terminarCreacion(Barril* b){
	// aca tengo que ver como hago para crear al Barril
}
