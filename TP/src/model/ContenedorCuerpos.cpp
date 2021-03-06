#include "ContenedorCuerpos.h"
#include "../controller/Server.h"
#include "structures/structServidor.h"
#include "../model/Tipos.h"

ContenedorCuerpos::ContenedorCuerpos() {
	huboCambios = new map<unsigned int, bool>() ;
	cuerpos = new map<unsigned int, Cuerpo*>() ;
	IDs = new vector<unsigned int>();
}

ContenedorCuerpos::~ContenedorCuerpos() {
	delete(huboCambios);
	cuerpos->clear();
	delete(cuerpos);
	delete(IDs);
}

void ContenedorCuerpos::actualizar(Observable* observable){
	Cuerpo* cuerpo = (Cuerpo*) observable;
	unsigned int id = 0;
	id = cuerpo->obtenerID();
	huboCambios->erase(id);
	huboCambios->insert(pair<unsigned int, bool>(id, true));
	cuerpos->erase(id);
	cuerpos->insert(pair<unsigned int, Cuerpo*>(id,cuerpo));

	for (unsigned int i = 0; i < IDs->size(); i++)
		if (IDs->at(i) == id) return;
	IDs->push_back(id);
}

void ContenedorCuerpos::encolarCambios(){
	Server* servidor = Server::obtenerInstancia(0);
	structServidor_t* estructura;
	vector<unsigned int>* eliminables = new vector<unsigned int>();
	for (unsigned int i = 0; i < IDs->size(); i++){
		unsigned int idActual = IDs->at(i);
		if (huboCambios->at(idActual)){
			int estado = cuerpos->at(idActual)->obtenerEstado();
			Posicion* pos = cuerpos->at(idActual)->obtenerPosicion();
			unsigned int tipo = cuerpos->at(idActual)->obtenerTipo();
			if (cuerpos->at(idActual)->estaInvencible())
				tipo = INVENCIBLE;
			if (cuerpos->at(idActual)->mataAlContacto())
				tipo = MATADOR;
			if (cuerpos->at(idActual)->saltaAlto())
				tipo = SALTOALTO;
			if (cuerpos->at(idActual)->estaInvencible()  && cuerpos->at(idActual)->saltaAlto() )
				tipo = SALTOALTO + INVENCIBLE;
			if (cuerpos->at(idActual)->mataAlContacto()  && cuerpos->at(idActual)->saltaAlto() )
				tipo = SALTOALTO + MATADOR;
			estructura = structServidor_crear(idActual, pos->obtenerX(), pos->obtenerY(), estado, tipo);

			if (estructura)
				servidor->encolar_cambio(estructura);
			if (estado == MUERTO){
				eliminables->push_back(idActual);
			}
		}
		/*Pongo que ya no hay cambios, ya que ya estoy mandando los cambios actuales
		ademas sirve en caso que en el vector de IDs haya alguno repetido: NO quiero
		MANDAR dos veces el MISMO cambio*/
		huboCambios->erase(idActual);
		huboCambios->insert(pair<unsigned int, bool>(idActual, false));
	}
	unsigned int cant = eliminables->size();
	for (unsigned int i = 0; i < cant; i++){
		unsigned int cantj = IDs->size();
		vector<unsigned int>* aux = new vector<unsigned int>();
		for (unsigned int j = 0; j < cantj; j++){
			unsigned int valor = IDs->at(IDs->size()-1);
			IDs->pop_back();
			if (eliminables->at(i) != valor)
				aux->push_back(valor);
		}
		delete (IDs);
		IDs = aux;
	}


}

void ContenedorCuerpos::encolarTodos(){
	for (unsigned int i = 0; i < IDs->size(); i++){
		unsigned int idActual = IDs->at(i);
		huboCambios->erase(idActual);
		huboCambios->insert(pair<unsigned int, bool> (idActual, true));
	}
	encolarCambios();
}

void ContenedorCuerpos::reinsertar(){
	for (unsigned int i = 0; i < IDs->size(); i++){
		unsigned int idAct = IDs->at(i);
		Cuerpo* cuerpo = cuerpos->at(idAct);
		cuerpo->huboCambios();
		cuerpo->notificarObservadores();
	}
}
