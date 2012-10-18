#include "ContenedorManuales.h"

ContenedorManuales::ContenedorManuales(vector<int>* vectorcito) {
	vectorEstados = vectorcito;
	vectorManuales = new vector<Manual*>();
}

ContenedorManuales::~ContenedorManuales() {
	delete (vectorManuales);
	delete (vectorHuboCambios);
}

void ContenedorManuales::agregarManual(Manual* principal){
	vectorManuales->push_back(principal);
}

void ContenedorManuales::actualizar(float delta){
	for (unsigned int i = 0; i < vectorManuales->size(); i++){
		actualizarManual(vectorManuales->at(i), vectorEstados->at(i), i);
	}
}
void ContenedorManuales::actualizarManual(Manual* manual, int estado, unsigned int indice){
	int estadoActual = manual->obtenerEstado();
	switch (estado){
		case QUIETO:
			if (estadoActual != QUIETODER && estadoActual != QUIETOIZQ){
				manual->detener();
				vectorHuboCambios->assign(indice,true);
			}
			break;
		case SALTAR:
			manual->saltar(); //si no debe hacerlo ya lo maneja el mismo Manual
			vectorHuboCambios->assign(indice,true);
			break;
		case CAMINANDOIZQ:
			manual->moverALaIzquierda();
			vectorHuboCambios->assign(indice,true);
			break;
		case CAMINANDODER:
			manual->moverALaDerecha();
			vectorHuboCambios->assign(indice,true);
			break;
	}
}
