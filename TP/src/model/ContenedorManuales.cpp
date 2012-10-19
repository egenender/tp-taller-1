#include "ContenedorManuales.h"
#include "../controller/Server.h"
#include "structures/structCliente.h"

ContenedorManuales::ContenedorManuales() {
	//FIXME: Si no se van agregando los ID de manera secuancial correlativa,
	//hay que cambiar a todos estos por hashes!
	vectorEstados = new vector<int>();
	vectorManuales = new vector<Manual*>();
	vectorHuboCambios = new vector<bool>();
}

ContenedorManuales::~ContenedorManuales() {
	delete (vectorManuales);
	delete (vectorHuboCambios);
}

void ContenedorManuales::agregarManual(Manual* principal){
	vectorManuales->push_back(principal);
	vectorEstados->push_back(principal->obtenerEstado());
	vectorHuboCambios->push_back(true);
}

void ContenedorManuales::actualizar(float delta){
	Server* servidor = Server::obtenerInstancia(0);
	structCliente_t* cambio;
	while (servidor->hay_cambios()){
		cambio = (structCliente_t*)servidor->desencolar_cambio();
		actualizarEstados(structCliente_obtener_id(cambio), structCliente_obtener_estado(cambio));
	}

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
		case MUERTO:
			if (!manual->estaMuerto()){
				manual->morir();
				vectorHuboCambios->assign(indice,true);
			}
			break;
		}
}

void ContenedorManuales::actualizarEstados(unsigned int id, int estado){
	//si el vector es correlativo al estado
	vectorEstados->assign(id, estado);
}
