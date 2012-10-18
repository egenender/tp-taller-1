#include "ContenedorDummy.h"

ContenedorDummy::ContenedorDummy(cola_t* cola) {
	lista_dummies = lista_crear();
	cola_entrada = cola;
}

ContenedorDummy::~ContenedorDummy() {
	while (!lista_esta_vacia(lista_dummies)){
		Dummy* tonto = (Dummy*) lista_borrar_primero(lista_dummies);
		delete(tonto);
	}
	lista_destruir(lista_dummies,NULL);
}

void ContenedorDummy::agregarDummy(Dummy* tonto){
	lista_insertar_ultimo(lista_dummies, tonto);
}

void ContenedorDummy::actualizar(float delta){
	while (!cola_esta_vacia(cola_entrada)){
		structServidor_t* mod = (structServidor_t*)cola_desencolar(cola_entrada);
		interpretarStruct(mod);
	}
}

void ContenedorDummy::interpretarStruct(structServidor_t* mod){
	unsigned int id = structServidor_obtener_id(mod);
	Dummy* tonto = buscarID(id);
	if (!tonto) return;
	int x, y;
	structServidor_obtener_posicion(mod, &x,&y);
	tonto->setXY(x,y);
	tonto->setEstado(structServidor_obtener_estado(mod));
	tonto->notificar();
}

Dummy* ContenedorDummy::buscarID(unsigned int id){
	lista_iter_t* iter = lista_iter_crear(lista_dummies);
	bool encontrado = false;
	Dummy* tonto = NULL;
	while (!lista_iter_al_final(iter) && !encontrado){
		tonto = (Dummy*)lista_iter_ver_actual(iter);
		encontrado = (tonto->esMio(id));
		lista_iter_avanzar(iter);
	}
	return tonto;
}
