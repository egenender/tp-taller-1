#include "Nivel.h"
#include "../view/VistaProtagonista.h"
#include "../controller/GestorConfiguraciones.h" //FIXME
#include "Server.h"


Nivel Nivel::instancia;

Nivel::Nivel() {
	principal = NULL;
	actualizables = NULL;
	vistas = NULL;
	camara = NULL;
	controlador = NULL;
}

Nivel::~Nivel() {

}

void Nivel::setEstado(int state){
	estado = state;
}

void Nivel::manejarEvento(SDL_Event* evento) {
	if (estado == SERVIDOR) return;
	if ((evento->type == SDL_KEYDOWN)
			&& (evento->key.keysym.sym == SDLK_ESCAPE)) {
		ManejadorEstados::setearEstadoActual(ESTADO_GUI);
	}

	controlador->manejarEvento(evento);
}

void Nivel::iniciar() {

	GestorConfiguraciones* gestor = GestorConfiguraciones::getInstance();

	// TODO: aca se deberia configurar la ventana. Habria que hacerla singleton!
	// Ventana::obtenerInstancia()->redimencionar(gestor->obtenerAnchoPantalla(), gestor->obtenerAltoPantalla());
	actualizables = gestor->ObtenerActualizables();

	vistas = gestor->ObtenerVistas();

	if(estado==SERVIDOR){

		Server::obtenerInstancia(0)->escribir(structServidor_obtener_tamanio());

	}

	Posicion::indicarMaximo(gestor->ObtenerAnchoNivel(),gestor->ObtenerAltoNivel());
	if (estado == CLIENTE){
		//Cliente::obtenerInstancia("",0) -> escuchar( structServidor_obtener_tamanio());
		camara = new Camara(0, 0);
		Dummy* algo = gestor->obtenerDummyMio();
		algo->agregarObservador(camara);
		controlador = new ControladorCliente(algo->obtenerID());
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
}

void Nivel::actualizar(float delta) {

	// Actualizamos cada cuerpo:
	for (unsigned int i = 0; i < actualizables->size(); i++) {
		Actualizable* cuerpito = actualizables->at(i);
		cuerpito->actualizar(delta);
	}

	if (estado == SERVIDOR){
		ContenedorManuales* cont = GestorConfiguraciones::getInstance()->obtenerContenedorManuales();
		if (cont)
			cont->encolarCambios();
	}
	// Verificar aca colisiones:

	// Aca vemos si tenemos que eliminar algun cuerpo:

	// Aca eliminamos los cuerpos y vistas que tegan que ser eliminados:
}

void Nivel::dibujar(SDL_Surface* display) {
	if (estado == SERVIDOR) return;
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
