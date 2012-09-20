#include "Nivel.h"
#include "VistaProtagonista.h"

Nivel Nivel::instancia;

#define ANCHO_NIVEL 640
#define ALTO_NIVEL 480

Nivel::Nivel() {
	principal = NULL;
	lista_cuerpos = NULL;
	lista_vistas = NULL;
}

Nivel::~Nivel() {
	//Nivel::terminar();
}

void Nivel::manejarEvento(SDL_Event* evento){
	Uint8 *keystates = SDL_GetKeyState(NULL);

	// Podria ser mejor :P Movimiento medio choto este:
	if (keystates[SDLK_UP]){
		//principal->saltar(); ?
	}
	if (keystates[SDLK_DOWN]){

	}
	if (keystates[SDLK_LEFT]){
		principal->moverALaIzquierda();
	}

	if (keystates[SDLK_RIGHT]){
		principal->moverALaDerecha();
	}

	//Faltaria ver si hay que poner algo del estilo principal->quieto();

}

void Nivel::iniciar() {

	// Aca se leeria de algun lado datos para el nivel, crear los cuerpos etc.

	Manual* algo = new Manual("algo", new Area(128,128,new Posicion(0,0)));

	VistaCuerpo* vistaAlgo = new VistaProtagonista(algo);

	Posicion::indicarMaximo(ANCHO_NIVEL, ALTO_NIVEL);

	lista_cuerpos = lista_crear();
	lista_vistas = lista_crear();

	algo->agregarObservador(vistaAlgo);

	agregarCuerpo(algo);
	agregarVista(vistaAlgo);

//	algo->moverALaDerecha();

	indicarManual(algo);

	// Se inicializan los cuerpos y se agregan a las listas
	// Idem con las vistas


	// Se pregunta a alguien quien es el Protagonista!
}

void destruirCuerpo(void* cuerpo){
	Cuerpo* c = (Cuerpo*) cuerpo;
	delete (c);
}

void destruirVista(void* vista){
	VistaCuerpo* v = (VistaCuerpo*) vista;
	delete (v);
}

void Nivel::terminar() {
	lista_destruir(lista_cuerpos, NULL); //o usar un destructor null?
	lista_destruir(lista_vistas, NULL);
}


void Nivel::actualizar(){

	// Actualizamos cada cuerpo:
	lista_iter_t* iter = lista_iter_crear(lista_cuerpos);
	while (!lista_iter_al_final(iter)){
		Cuerpo* cuerpito = (Cuerpo*)lista_iter_ver_actual(iter);
		cuerpito->actualizar();
		lista_iter_avanzar(iter);
	}

	lista_iter_destruir(iter);

	// Verificar aca colisiones:

	// Aca vemos si tenemos que eliminar algun cuerpo:

	// Aca eliminamos los cuerpos y vistas que tegan que ser eliminados:
}

void Nivel::dibujar(SDL_Surface* display){
	// Dibujamos el fondo:


	// Dibujamos las vistas:

	 lista_iter_t* iter = lista_iter_crear(lista_vistas);
	 while (!lista_iter_al_final(iter)){
	 	 VistaCuerpo* vista = (VistaCuerpo*) lista_iter_ver_actual(iter);
	 	 vista->dibujar(display);
	 	 lista_iter_avanzar(iter);
	 }
	 lista_iter_destruir(iter);

	// Ponele que se reproducen los sonidos (?)
}

void Nivel::agregarCuerpo(Cuerpo* c){
	lista_insertar_ultimo(lista_cuerpos,c);
}

void Nivel::agregarVista(VistaCuerpo* v){
 	 lista_insertar_ultimo(lista_vistas,v);
}

void Nivel::indicarManual(Manual* m){
	principal = m;
	//Nivel::agregarCuerpo(m);
}

/** Devuelve la instancia del estado (Singleton) **/
Nivel* Nivel::obtenerInstancia() {
	return &instancia;
}
