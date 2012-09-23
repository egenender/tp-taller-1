#include "Nivel.h"
#include "VistaProtagonista.h"
#include "GestorConfiguraciones.h"


Nivel Nivel::instancia;

/*#define ANCHO_NIVEL 640
#define ALTO_NIVEL 480*/

Nivel::Nivel() {
	principal = NULL;
	cuerpos = NULL;
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

	//Manual* algo = new Manual("algo", new Area(65,73,new Posicion(0,0)));
	//VistaCuerpo* vistaAlgo = new VistaProtagonista(algo);

	Manual* algo = gestor->ObtenerManual();
//	VistaCuerpo* vistaAlgo = gestor->ObtenerVistaManual();

	// Se inicializan los cuerpos y se agregan a las listas
	// Idem con las vistas
	cuerpos = gestor->ObtenerCuerpos();
	vistas = gestor->ObtenerVistas();

	Posicion::indicarMaximo(gestor->ObtenerAnchoNivel(), gestor->ObtenerAltoNivel());

	camara = new Camara(0,0);
	algo->agregarObservador(camara);

	indicarManual(algo);
	controlador = new Controlador();
	// Se pregunta a alguien quien es el Protagonista!
}

void Nivel::terminar() {
	//lista_destruir(lista_cuerpos, NULL); //o usar un destructor null?
	//lista_destruir(lista_vistas, NULL);
	/*delete(cuerpos);
	delete(vistas);
	delete(camara);*/
	delete controlador;
}


void Nivel::actualizar(){

	// Actualizamos cada cuerpo:
	for(unsigned int i=0;i<cuerpos->size();i++){
			Cuerpo* cuerpito = cuerpos->at(i);
			cuerpito->actualizar();
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
	cuerpos->push_back(c);
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
