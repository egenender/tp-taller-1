#include "ContenedorManuales.h"
#include "../controller/Server.h"
#include "structures/structCliente.h"


#include "Posicion.h"

ContenedorManuales::ContenedorManuales() {
	estados = new map<unsigned int, int>();
	huboCambios = new map<unsigned int, bool>();
	manuales = new map<unsigned int, Manual*>();
	IDs = new vector<unsigned int>();
}

ContenedorManuales::~ContenedorManuales() {
	delete (manuales);
	delete (huboCambios);
	delete(estados);
	delete (IDs);
}

void ContenedorManuales::agregarManual(Manual* principal, unsigned int id){
	huboCambios->erase(id);
	estados->erase(id);
	manuales->erase(id);

	huboCambios->insert(pair<unsigned int, bool>(id, true));
	estados->insert(pair<unsigned int, int>(id, principal->obtenerEstado()));
	manuales->insert(pair<unsigned int, Manual*>(id, principal));
	IDs->push_back(id);
}

void ContenedorManuales::actualizar(float delta){
	Server* servidor = Server::obtenerInstancia(0);
	structCliente_t* cambio;
	while (servidor->hay_cambios()){
		cambio = (structCliente_t*)servidor->desencolar_cambio();
		actualizarEstados(structCliente_obtener_id(cambio), structCliente_obtener_estado(cambio));
		structCliente_destruir(cambio);
	}

	for (unsigned int i = 0; i < IDs->size(); i++){
		unsigned int idActual = IDs->at(i);
		actualizarManual(manuales->at(idActual), estados->at(idActual), idActual);
	}

}
void ContenedorManuales::actualizarManual(Manual* manual, int estado, unsigned int indice){
	int estadoActual = manual->obtenerEstado();
	switch (estado){
		case QUIETO:
			if (estadoActual != QUIETODER && estadoActual != QUIETOIZQ){
				manual->detener();
				huboCambios->erase(indice);
				huboCambios->insert(pair<unsigned int, bool>(indice,true));
			}
			break;
		case SALTAR:
			manual->saltar(); //si no debe hacerlo ya lo maneja el mismo Manual
			huboCambios->erase(indice);
			huboCambios->insert(pair<unsigned int, bool>(indice,true));
			break;
		case CAMINANDOIZQ:
			manual->moverALaIzquierda();
			huboCambios->erase(indice);
			huboCambios->insert(pair<unsigned int, bool>(indice,true));
			break;
		case CAMINANDODER:
			manual->moverALaDerecha();
			huboCambios->erase(indice);
			huboCambios->insert(pair<unsigned int, bool>(indice,true));
			break;
		case MUERTO:
			if (!manual->estaMuerto()){
				manual->morir();
				huboCambios->erase(indice);
				huboCambios->insert(pair<unsigned int, bool>(indice,true));
			}
			break;
		case SUBIR:
			manual->subir();
			huboCambios->erase(indice);
			huboCambios->insert(pair<unsigned int, bool>(indice,true));
			break;
		case BAJAR:
			manual->bajar();
			huboCambios->erase(indice);
			huboCambios->insert(pair<unsigned int, bool>(indice,true));
			break;
		}

}

void ContenedorManuales::actualizarEstados(unsigned int id, int estado){
	if(estado == VIVO){
		return;
	}
	estados->erase(id);
	estados->insert(pair<unsigned int, int>(id, estado));
	if (estado == SALTAR){
		manuales->at(id)->saltar();
	}


}

void ContenedorManuales::encolarCambios(){
	Server* servidor = Server::obtenerInstancia(0);
	structServidor_t* estructura;
	for (unsigned int i = 0; i < IDs->size(); i++){
		unsigned int idActual = IDs->at(i);
		if (huboCambios->at(idActual)){
			int estado = manuales->at(idActual)->obtenerEstado();
			Posicion* pos = manuales->at(idActual)->obtenerPosicion();
			estructura = structServidor_crear(idActual, pos->obtenerX(), pos->obtenerY(), estado,0);

			if (estructura)
				servidor->encolar_cambio(estructura);
		}
		/*Pongo que ya no hay cambios, ya que ya estoy mandando los cambios actuales
		ademas sirve en caso que en el vector de IDs haya alguno repetido: NO quiero
		MANDAR dos veces el MISMO cambio*/
		huboCambios->erase(idActual);
		huboCambios->insert(pair<unsigned int, bool>(idActual, false));
	}


}

structServidor_t* ContenedorManuales::crearEnvio(Manual* manual, unsigned int id){
	structServidor_t* estructura;
	int estado = manual->obtenerEstado();
	Posicion* pos = manual->obtenerPosicion();
	estructura = structServidor_crear(id, pos->obtenerX(), pos->obtenerY(), estado,0);
	return estructura;
}

void ContenedorManuales::encolarTodos(){
	for (unsigned int i = 0; i < IDs->size(); i++){
		unsigned int idActual = IDs->at(i);
		huboCambios->erase(idActual);
		huboCambios->insert(pair<unsigned int, bool> (idActual, true));
	}
	encolarCambios();
}

Area* ContenedorManuales::obtenerArea(){
	return NULL;
}

void ContenedorManuales::chocarCon(Actualizable*){}

