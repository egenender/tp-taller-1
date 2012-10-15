#include "Nivel.h"
#include "../view/VistaProtagonista.h"
#include "../controller/GestorConfiguraciones.h" //FIXME


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

void Nivel::manejarEvento(SDL_Event* evento){
	controlador->manejarEvento(evento, principal);
}

void Nivel::iniciar() {

	GestorConfiguraciones* gestor=GestorConfiguraciones::getInstance();

	// TODO: aca se deberia configurar la ventana. Habria que hacerla singleton!
	// Ventana::obtenerInstancia()->redimencionar(gestor->obtenerAnchoPantalla(), gestor->obtenerAltoPantalla());

	Manual* algo = gestor->ObtenerManual();

	actualizables = gestor->ObtenerActualizables();

	vistas = gestor->ObtenerVistas();

	Posicion::indicarMaximo(gestor->ObtenerAnchoNivel(), gestor->ObtenerAltoNivel());

	camara = new Camara(0,0);
	algo->agregarObservador(camara);

	indicarManual(algo);
	controlador = new Controlador();
}

void Nivel::terminar() {

	while (!actualizables->empty()){
		Actualizable* cuerpito = actualizables->back();
		actualizables->pop_back();
		delete(cuerpito);
	}

	while (!vistas->empty()){
		VistaCuerpo* vista = vistas->back();
		vistas->pop_back();
		delete (vista);
	}

	delete(actualizables);
	delete(vistas);
	delete(camara);
	delete (controlador);
}


void Nivel::actualizar(float delta){

	// Actualizamos cada cuerpo:
	for(unsigned int i=0;i<actualizables->size();i++){
			Actualizable* cuerpito = actualizables->at(i);
			cuerpito->actualizar(delta);
	}

	// Verificar aca colisiones:

	// Aca vemos si tenemos que eliminar algun cuerpo:

	// Aca eliminamos los cuerpos y vistas que tegan que ser eliminados:
}

void Nivel::dibujar(SDL_Surface* display){
	// Dibujamos el fondo:
	camara->dibujar(display, 0, 0); // No importa los numeros, porque camara no le da bola :P


	// Dibujamos las vistas:
	for(unsigned int i=0;i<vistas->size();i++){
			VistaCuerpo* vista = vistas->at(i);
			vista->dibujar(display, camara->obtenerX(), camara->obtenerY()); // Estos si le dan bola a los numeros, porque tienen que dibujarse RESPECTO a la camara.
	}
	// Ponele que se reproducen los sonidos (?)
}

void Nivel::agregarCuerpo(Cuerpo* c){
	actualizables->push_back(c);
}

void Nivel::agregarVista(VistaCuerpo* v){
 	 vistas->push_back(v);
}

void Nivel::indicarManual(Manual* m){
	principal = m;
	//Nivel::agregarCuerpo(m);
}

/** Devuelve la instancia del estado (Singleton) **/
Nivel* Nivel::obtenerInstancia() {
	return &instancia;
}
