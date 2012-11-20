#include "Nivel.h"
#include "../view/VistaProtagonista.h"
#include "../controller/GestorConfiguraciones.h" //FIXME
#include "Server.h"
#include "../model/Colisionador.h"
#include "../model/Personajes/CamaElastica.h"
#include "../model/Personajes/Pluma.h"
#include "../view/VistaVidas.h"
#include "../view/VistaVarios.h"

//TODO: *le hardcode:
#include "../model/Fabricas/FabricaPowerUps.h"
#include "../model/Personajes/Caja.h"

Nivel Nivel::instancia;

Nivel::Nivel() {
	estado = -1;
	parar = false;
	principal = NULL;
	actualizables = NULL;
	vistas = NULL;
	camara = NULL;
	musica = NULL;
	controlador = NULL;
	fondoServidor = NULL;
	puedoJugar = false;
}

Nivel::~Nivel() {
	this->terminar();
}

void Nivel::setEstado(int state){
	estado = state;
}

void Nivel::manejarEvento(SDL_Event* evento) {
	if ((evento->type == SDL_KEYDOWN)
			&& (evento->key.keysym.sym == SDLK_ESCAPE)) {
		if(estado==CLIENTE){

		}
		if(estado==SERVIDOR){
			Log::getInstance()->writeToLogFile("INFO","SOCK: Se han desconectado todos los clientes");
			Server::obtenerInstancia(0)->detenerServer();
			ManejadorEstados::setearEstadoActual(ESTADO_GUI);
		}

	}
	if(estado==SERVIDOR){
		Server* server = Server::obtenerInstancia(0);
		if (server->desco){
			if ( server->IDsockets->size() == 0){
				server->desco = false;
				server->detenerServer();
				ManejadorEstados::setearEstadoActual(ESTADO_GUI);
			}
		}
		return;
	}

	controlador->manejarEvento(evento);
}

void Nivel::iniciar() {
	parar = false;
	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();

	actualizables = gestor->ObtenerActualizables();
	vistas = gestor->ObtenerVistas();

	if(estado==SERVIDOR){

		Server::obtenerInstancia(0)->escribir(structServidor_obtener_tamanio());
		fondoServidor = new Superficie("src/gui/resources/fondo.bmp");
	}

	Posicion::indicarMaximo(gestor->ObtenerAnchoNivel(),gestor->ObtenerAltoNivel());
	Posicion::indicarPiso(gestor->ObtenerPisoNivel());
	if (estado == CLIENTE || estado == SINGLE){
		//Cliente::obtenerInstancia("",0) -> escuchar( structServidor_obtener_tamanio());

		// Vidas:
		VistaVidas* corazones = new VistaVidas();
		vistas->push_back(corazones);

		// Musica:
		musica = new VistaMusical();
		// Camara:
		camara = new Camara(0, 0);

		if (estado == CLIENTE){
			Dummy* algo = gestor->obtenerDummyMio();
			algo->agregarObservador(camara);
			algo->agregarObservador(corazones);
	//		algo->agregarObservador(musica);
			controlador = new ControladorCliente(algo->obtenerID(), algo);
		}else{
			Manual* prin = gestor->ObtenerManual();
			prin->moverA(new Posicion(10, Posicion::obtenerPiso()-prin->obtenerAlto()));
			prin->agregarObservador(camara);
			prin->agregarObservador(corazones);
			prin->agregarObservador(musica);
			controlador = new ControladorSinglePlayer(prin);
		}
	}
	if (estado == SINGLE ){
		for (unsigned int i = 0; i < gestor->lasCajas->size() ; i++){
			actualizables->push_back(gestor->lasCajas->at(i));
			gestor->lasCajas->at(i)->agregarObservador(gestor->lasVistaDeCajas->at(i));
			vistas->push_back(gestor->lasVistaDeCajas->at(i));
		}
	}

}

void Nivel::terminar() {
	actualizables = NULL;
	vistas = NULL;
//	if (actualizables) {
//		while (!actualizables->empty()){
//			Actualizable* cuerpito = actualizables->back();
//			actualizables->pop_back();
//			if (cuerpito != NULL) {
//				delete(cuerpito);
//				cuerpito = NULL;
//			}
//		}
//
//		actualizables->clear();
//		actualizables = NULL;
//	}
//
//	if (vistas) {
//		/*while (!vistas->empty()){
//			VistaCuerpo* vista = vistas->back();
//			vistas->pop_back();
//			if (vista != NULL) {
//				delete (vista);
//				vista = NULL;
//			}
//		}*/
//		vistas->clear();
//		vistas = NULL;
//	}

	if (camara) {
		delete (camara);
		camara = NULL;
	}
	if (musica) {
		delete(musica);
		musica = NULL;
	}

	if (controlador) {
		delete (controlador);
		controlador = NULL;
	}
	if (fondoServidor){
		delete(fondoServidor);
		fondoServidor = NULL;
	}

	puedoJugar = false;
}

void Nivel::sePuedeJugar(){
	puedoJugar = true;
}

void Nivel::actualizar(float delta) {
	if (!puedoJugar) return;

	if (parar && estado==CLIENTE){
		Cliente::obtenerInstancia("",0)->detener_escuchar();
		Cliente::obtenerInstancia("",0)->detener_escribir();
		Cliente::obtenerInstancia("",0)->detener();
		GestorConfiguraciones::getInstance()->acabarGestor();
		ManejadorEstados::setearEstadoActual(ESTADO_GUI);
		return;
	}
	// Actualizamos cada cuerpo:
	for (unsigned int i = 0; i < actualizables->size(); i++) {
		Actualizable* cuerpito = actualizables->at(i);
		cuerpito->actualizar(delta);
	}

	if (estado == SERVIDOR){
		ContenedorCuerpos* cont = GestorConfiguraciones::getInstance()->obtenerContenedorCuerpos();
		if (cont){
			Server* server = Server::obtenerInstancia(0);
			if (server->envio->obtenerTiempo() >= 1000*TIEMPO_ENVIO){
				server->envio->detener();
				server->envio->comenzar();
				cont->encolarTodos();
				return ;
			}
			cont->encolarCambios();
		}
	}

	// Verificar aca colisiones:
	if (estado == SERVIDOR || estado == SINGLE){
		quitarMuertos();
		generarColisiones(actualizables);
	}
	// Aca vemos si tenemos que eliminar algun cuerpo:

	// Aca eliminamos los cuerpos y vistas que tegan que ser eliminados:
}

void Nivel::dibujar(SDL_Surface* display) {
	if (estado == SERVIDOR){
		fondoServidor->dibujar(display,0,0);
		return;
	}
	// Dibujamos el fondo:
	camara->dibujar(display, 0, 0); // No importa los numeros, porque camara no le da bola :P
	musica->dibujar(display,0, 0);

	// Dibujamos las vistas:

	for (unsigned int i = 0; i < vistas->size(); i++) {
		VistaCuerpo* vista = vistas->at(i);
		vista->dibujar(display, camara->obtenerX(), camara->obtenerY()); // Estos si le dan bola a los numeros, porque tienen que dibujarse RESPECTO a la camara.
	}
	// Ponele que se reproducen los sonidos (?)
}

void Nivel::agregarCuerpo(Cuerpo* c) {
	actualizables->push_back(c);
}

void Nivel::agregarVista(VistaCuerpo* v) {
	vistas->push_back(v);
}

void Nivel::indicarManual(Manual* m) {
	principal = m;
	//Nivel::agregarCuerpo(m);
}

/** Devuelve la instancia del estado (Singleton) **/
Nivel* Nivel::obtenerInstancia() {
	return &instancia;
}

void Nivel::morir(){
	parar = true;
}

void Nivel::quitarMuertos(){
	vector<Actualizable*>* aux = new vector<Actualizable*>();
	Actualizable* ac;
	for (unsigned int i = 0; i < actualizables->size(); i++){
		ac = actualizables->at(i);
		if (ac->estaMuerto()){
			if (ac->esEliminable() && estado != SERVIDOR)
				delete(ac);
		}else
			aux->push_back(ac);
	}
	actualizables->clear();
	for (unsigned int j = 0; j < aux->size(); j++){
		actualizables->push_back(aux->at(j));
	}

}
