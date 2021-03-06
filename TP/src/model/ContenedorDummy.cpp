#include "ContenedorDummy.h"
#include "../view/VistaProtagonista.h"
#include "../gui/view/VistaBarraEstado.h"
#include "../controller/GestorConfiguraciones.h"
#include "../controller/ManejadorEstados.h"
#include "../controller/ManejadorCliente.h"
#include "Tipos.h"
#include <string>

string ContenedorDummy::intToString(unsigned int numero){
	string resul = "";
	string temp = "";
	while (numero > 0){
		temp += numero % 10 + 48;
        numero /= 10;
	}
	for (unsigned int i=0;i<temp.length();i++)
		resul+=temp[temp.length()-i-1];
	return resul;
}


ContenedorDummy::ContenedorDummy() {
	lista_dummies = lista_crear();
	cliente = Cliente::obtenerInstancia("",0);
	barra = new BarraEstado(100, 0, 600, 37);
	VistaBarraEstado* vista = new VistaBarraEstado();
	barra->agregarObservador(vista);
	GestorConfiguraciones::getInstance()->ObtenerVistas()->push_back(vista);
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
	unsigned int id = tonto->obtenerID();
	string aux1 = "";
	if (id < GestorConfiguraciones::getInstance()->ObtenerPosiblesTiposProtagonistas()->size() ){
		aux1 = "Se ha conectado el cliente ";
		string aux2 = intToString(id+1);
		string aux3 = aux1 + aux2;
		barra->setearMensaje(aux3);
	}
}

void ContenedorDummy::actualizar(float delta){
	int interpretado = 0;
	while (cliente->hay_cambios() && interpretado < MAX_ACTUALIZACION){
		structServidor_t* mod = (structServidor_t*)cliente->desencolar_cambio();
		interpretarStruct(mod);
		structServidor_destruir(mod);
		interpretado++;
	}
	barra->actualizar();
	limpiarLista();
}

void ContenedorDummy::interpretarStruct(structServidor_t* mod){
	unsigned int id = structServidor_obtener_id(mod);
	Dummy* tonto = buscarID(id);
	if (!tonto) {
		int x, y;
		structServidor_obtener_posicion(mod, &x, &y);
		tonto = crearDummyNuevo(id, structServidor_obtener_tipo(mod),structServidor_obtener_estado(mod) , x,y );
		if (!tonto)
			return;
	}
	int x, y;
	structServidor_obtener_posicion(mod, &x,&y);
	tonto->setXY(x,y);
	tonto->setEstado(structServidor_obtener_estado(mod), structServidor_obtener_tipo(mod));
	tonto->notificar();


	//TODO: si es que estaba muerto, hay que ver si queremos sacarlo del listado...
	//igual da lo mismo porque no va a volver a cambiar

	if (structServidor_obtener_estado(mod) == MUERTO){
		string aux1 = "";
		if (id < GestorConfiguraciones::getInstance()->ObtenerPosiblesTiposProtagonistas()->size() ){
			aux1 = "Se ha desconectado el cliente ";
			string aux2 = intToString(id+1);
			string aux3 = aux1 + aux2;
			barra->setearMensaje(aux3);
		}
	}

}



void ContenedorDummy::borrarID(unsigned int id){
	lista_iter_t* iter = lista_iter_crear(lista_dummies);
	bool encontrado = false;
	Dummy* tonto = NULL;
	while (!lista_iter_al_final(iter) && !encontrado){
		tonto = (Dummy*)lista_iter_ver_actual(iter);
		encontrado = (tonto->esMio(id));
		if (!encontrado)
			lista_iter_avanzar(iter);
	}
	if (!encontrado) return ;
	//lista_borrar(lista_dummies, iter);
}

void ContenedorDummy::limpiarLista(){

	lista_t* aux = lista_crear();
	unsigned int largo = lista_largo(lista_dummies);
	Dummy* tonto;
	for (unsigned int i = 0; i < largo; i++){
		tonto = (Dummy*) lista_borrar_primero(lista_dummies);
		if (tonto->obtenerEstado() != MUERTO)
			lista_insertar_ultimo(aux, tonto);
		else{
			//delete (tonto);
		}
	}
	lista_destruir(lista_dummies, NULL);
	lista_dummies = aux;
}


Dummy* ContenedorDummy::buscarID(unsigned int id){
	lista_iter_t* iter = lista_iter_crear(lista_dummies);
	bool encontrado = false;
	Dummy* tonto = NULL;
	while (!lista_iter_al_final(iter) && !encontrado){
		tonto = (Dummy*)lista_iter_ver_actual(iter);
		encontrado = (tonto->esMio(id));
		if (!encontrado)
			lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	if (!encontrado){
		return NULL;
	}

//	if (tonto->obtenerEstado()==MUERTO){
//		tonto = (Dummy*)lista_borrar(lista_dummies, iter);
//
//		lista_iter_destruir(iter);
//		delete(tonto);
//		return NULL;
//	}

	return tonto;
}

//Dummy* ContenedorDummy::crearDummyNuevo(unsigned int idNuevo){
//	//Obtengo de los tiposProtagonistas el que corresponde al ID a crear
//	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();
//	vector<TipoProtagonista*>* tipos = gestor->ObtenerPosiblesTiposProtagonistas();
//	TipoProtagonista* tipo = tipos->at(idNuevo);
//	//Creo el nuevo Dummy, en una posicion Arbitraria
//	//FIXME: ver que onda esa posicion rara jaja
//	Dummy* nuevo = new Dummy(idNuevo, new Posicion(300,150), tipo->ancho, tipo->alto);
//
//	//Le asigno una vista para poder dibujarlo
//	VistaProtagonista* vistaNueva = new VistaProtagonista (tipo->animacionActivaProt, tipo->animacionPasivaProt, tipo->animacionSaltaProt);
//	nuevo->agregarObservador(vistaNueva);
//
//	//agrego la vista al vector de vistas del Nivel para que se dibuje:
//	gestor->ObtenerVistas()->push_back(vistaNueva);
//
//	//lo agrego al contenedor:
//	agregarDummy(nuevo);
//	return nuevo;
//}

Dummy* ContenedorDummy::crearDummyNuevo(unsigned int idNuevo,unsigned int tipo, int estado, int x, int y){
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();

	if (idNuevo == gestor->ObtenerPosiblesTiposProtagonistas()->size() || idNuevo == (gestor->ObtenerPosiblesTiposProtagonistas()->size() + 1)){
		if (idNuevo == (gestor->ObtenerPosiblesTiposProtagonistas()->size() + 1) )
			gestor->quienGano = (gestor->ObtenerPosiblesTiposProtagonistas()->size() + 1);
		else
			gestor->quienGano = tipo;
		ManejadorCliente::obtenerInstancia(NULL)->detener();
		Cliente::obtenerInstancia("",0)->detener_escuchar();
		Cliente::obtenerInstancia("",0)->detener_escribir();
		Cliente::obtenerInstancia("",0)->detener();
		GestorConfiguraciones::getInstance()->acabarGestor();
		ManejadorEstados::setearEstadoActual(ESTADO_TERMINADO);
		return NULL;
	}

	else if (idNuevo == (gestor->ObtenerPosiblesTiposProtagonistas()->size() + 2)){
		Dummy* dum = buscarID(tipo);
		unsigned int state = estado;
		dum->setearVidas(state);
		dum->notificar();
		return NULL;
	}

	unsigned int ref = idNuevo;
	std::string nombre = "";
	if (tipo >= TIPO_BOLA_FUEGO){
		nombre = "bola";
		ref = tipo - TIPO_BOLA_FUEGO;
	}

	if (tipo != TIPO_MANUAL && tipo < TIPO_BOLA_FUEGO){
		nombre = decodificarTipo(tipo);
	}else{
		nombre += gestor->ObtenerPosiblesTiposProtagonistas()->at(ref)->nombre;
	}

	parametrosPersonaje* parametros = gestor->obtenerParametrosPersonaje(nombre);
	Dummy* nuevo = new Dummy(idNuevo, new Posicion(x,y), parametros->ancho, parametros->alto);
	gestor->crearVistaElemento(nuevo, nombre, false);

	if ( idNuevo < gestor->ObtenerPosiblesTiposProtagonistas()->size() ){
		gestor->invenciTester->agregarDummy(nuevo);
	}

	if (tipo == TIPO_MANUAL){
		gestor->ObtenerPosiblesTiposProtagonistas()->at(idNuevo)->jugando = true;
	}

	agregarDummy(nuevo);
	return nuevo;
}


Area* ContenedorDummy::obtenerArea(){
	return NULL;
}

void ContenedorDummy::chocarCon(Actualizable*){}
