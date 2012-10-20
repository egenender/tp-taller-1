#include "ContenedorDummy.h"

ContenedorDummy::ContenedorDummy() {
	lista_dummies = lista_crear();
	cliente = Cliente::obtenerInstancia("",0);
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
	//barra->setearMensaje("Se ha conectado el cliente "+(lista_cantidad(lista)-1));
}

void ContenedorDummy::actualizar(float delta){
	while (cliente->hay_cambios()){
		structServidor_t* mod = (structServidor_t*)cliente->desencolar_cambio();
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


	//TODO: si es que estaba muerto, hay que ver si queremos sacarlo del listado...
	//igual da lo mismo porque no va a volver a cambiar

	/*
	 if (structServidor_obtener_estado(mod) == MUERTO){
	 	 barra->setearMensaje("Se ha desconectado el Cliente "+id);
	 }
	 */
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
