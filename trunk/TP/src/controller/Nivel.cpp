#include "Nivel.h"
#include "../view/VistaProtagonista.h"
#include "../controller/GestorConfiguraciones.h" //FIXME
#include "Server.h"


Nivel Nivel::instancia;

Nivel::Nivel() {
	estado = -1;
	parar = false;
	principal = NULL;
	actualizables = NULL;
	vistas = NULL;
	camara = NULL;
	controlador = NULL;
	fondoServidor = NULL;
}

Nivel::~Nivel() {

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

	// TODO: aca se deberia configurar la ventana. Habria que hacerla singleton!
	// Ventana::obtenerInstancia()->redimencionar(gestor->obtenerAnchoPantalla(), gestor->obtenerAltoPantalla());
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
		camara = new Camara(0, 0);
		if (estado == CLIENTE){
			Dummy* algo = gestor->obtenerDummyMio();
			algo->agregarObservador(camara);
			controlador = new ControladorCliente(algo->obtenerID(), algo);
		}else{
			Manual* prin = gestor->ObtenerManual();
			prin->moverA(new Posicion(10, Posicion::obtenerPiso()-prin->obtenerAlto()));
			prin->agregarObservador(camara);
			controlador = new ControladorSinglePlayer(prin);
		}
	}
}

void Nivel::terminar() {
	while (!actualizables->empty()){
		Actualizable* cuerpito = actualizables->back();
		actualizables->pop_back();
		if (cuerpito != NULL) {
			delete(cuerpito);
			cuerpito = NULL;
		}
	}

	actualizables->clear();
	actualizables = NULL;

	/*while (!vistas->empty()){
		VistaCuerpo* vista = vistas->back();
		vistas->pop_back();
		if (vista != NULL) {
			delete (vista);
			vista = NULL;
		}
	}*/
	vistas->clear();
	vistas = NULL;

	delete (camara);
	delete (controlador);
	if (fondoServidor){
		delete(fondoServidor);
		fondoServidor = NULL;
	}
}

void Nivel::actualizar(float delta) {
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
		ContenedorManuales* cont = GestorConfiguraciones::getInstance()->obtenerContenedorManuales();
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
