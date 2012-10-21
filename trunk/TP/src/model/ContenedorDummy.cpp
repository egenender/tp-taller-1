#include "ContenedorDummy.h"
#include "../view/VistaProtagonista.h"
#include "../controller/GestorConfiguraciones.h"

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
	if (!tonto) {
		tonto = crearDummyNuevo(id);
	}
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
	if (!encontrado) return NULL;
	return tonto;
}

Dummy* ContenedorDummy::crearDummyNuevo(unsigned int idNuevo){
	//Obtengo de los tiposProtagonistas el que corresponde al ID a crear
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
	vector<TipoProtagonista*>* tipos = gestor->ObtenerPosiblesTiposProtagonistas();
	TipoProtagonista* tipo = tipos->at(idNuevo);
	//Creo el nuevo Dummy, en una posicion Arbitraria
	//FIXME: ver que onda esa posicion rara jaja
	Dummy* nuevo = new Dummy(idNuevo, new Posicion(50,50), tipo->ancho, tipo->alto);

	//Le asigno una vista para poder dibujarlo
	VistaProtagonista* vistaNueva = new VistaProtagonista (tipo->animacionActivaProt, tipo->animacionPasivaProt, tipo->animacionSaltaProt);
	nuevo->agregarObservador(vistaNueva);

	//agrego la vista al vector de vistas del Nivel para que se dibuje:
	gestor->ObtenerVistas()->push_back(vistaNueva);
	return nuevo;
}
