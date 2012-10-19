#include "ContenedorManuales.h"
#include "../controller/Server.h"
#include "structures/structCliente.h"

#include "Posicion.h"

ContenedorManuales::ContenedorManuales() {
	//FIXME: Si no se van agregando los ID de manera secuancial correlativa,
	//hay que cambiar a todos estos por hashes!
	estados = new vector<int>();
	manuales = new vector<Manual*>();
	huboCambios = new vector<bool>();
}

ContenedorManuales::~ContenedorManuales() {
	delete (manuales);
	delete (huboCambios);
	delete(estados);
}

void ContenedorManuales::agregarManual(Manual* principal){
	manuales->push_back(principal);
	estados->push_back(principal->obtenerEstado());
	huboCambios->push_back(true);
}

void ContenedorManuales::actualizar(float delta){
	Server* servidor = Server::obtenerInstancia(0);
	structCliente_t* cambio;
	while (servidor->hay_cambios()){
		cambio = (structCliente_t*)servidor->desencolar_cambio();
		actualizarEstados(structCliente_obtener_id(cambio), structCliente_obtener_estado(cambio));
	}

	for (unsigned int i = 0; i < manuales->size(); i++){
		actualizarManual(manuales->at(i), estados->at(i), i);
	}
}
void ContenedorManuales::actualizarManual(Manual* manual, int estado, unsigned int indice){
	int estadoActual = manual->obtenerEstado();
	switch (estado){
		case QUIETO:
			if (estadoActual == CAMINANDODER || estadoActual == CAMINANDOIZQ){
				manual->detener();
				huboCambios->assign(indice,true);
			}
			break;
		case SALTAR:
			manual->saltar(); //si no debe hacerlo ya lo maneja el mismo Manual
			huboCambios->assign(indice,true);
			break;
		case CAMINANDOIZQ:
			manual->moverALaIzquierda();
			huboCambios->assign(indice,true);
			break;
		case CAMINANDODER:
			manual->moverALaDerecha();
			huboCambios->assign(indice,true);
			break;
		case MUERTO:
			if (!manual->estaMuerto()){
				manual->morir();
				huboCambios->assign(indice,true);
			}
			break;
		}
}

void ContenedorManuales::actualizarEstados(unsigned int id, int estado){
	//si el vector es correlativo al estado
	estados->assign(id, estado);
}

void ContenedorManuales::encolarCambios(){
	Server* servidor = Server::obtenerInstancia(0);
	structServidor_t* estructura;
	for (unsigned int i = 0; i < manuales->size(); i++){
		if (huboCambios->at(i)){
			int estado = manuales->at(i)->obtenerEstado();
			Posicion* pos = manuales->at(i)->obtenerPosicion();
			estructura = structServidor_crear(i, pos->obtenerX(), pos->obtenerY(), estado);

			if (estructura)
				servidor->encolar_cambio(estructura);
		}
	}
}

structServidor_t* crearEnvio(Manual* manual, unsigned int id){
	structServidor_t* estructura;
	int estado = manual->obtenerEstado();
	Posicion* pos = manual->obtenerPosicion();
	estructura = structServidor_crear(id, pos->obtenerX(), pos->obtenerY(), estado);
	return estructura;
}
