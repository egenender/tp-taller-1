#include "Nivel.h"

Nivel::Nivel() {
	principal = NULL;
	lista_cuerpos = NULL;
	//lista_vistas = NULL;
}

Nivel::~Nivel() {
	Nivel::terminar();
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

	lista_cuerpos = lista_crear();
	//lista_vistas = lista_crear();

	// Se inicializan los cuerpos y se agregan a las listas
	// Idem con las vistas


	// Se pregunta a alguien quien es el Protagonista!
}

void destruirCuerpo(void* cuerpo){
	Cuerpo* c = (Cuerpo*) cuerpo;
	delete c;
}

void Nivel::terminar() {
	lista_destruir(lista_cuerpos,destruirCuerpo); //o usar un destructor null?
	//lista_destruir(lista_vistas, destruirVista);
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

	// Actualizamos cada vista:
	/*iter = lista_iter_crear(lista_vistas);
	while (!lista_iter_al_final(iter)){
		Vista* vista = (Vista*)lista_iter_ver_actual(iter);
		vista->actualizar();
		lista_iter_avanzar(iter);
	}

	lista_iter_destruir(iter);*/


	// Aca vemos si tenemos que eliminar algun cuerpo:

	// Aca eliminamos los cuerpos y vistas que tegan que ser eliminados:
}

void Nivel::dibujar(SDL_Surface* display){
	// Dibujamos el fondo:


	// Dibujamos las vistas:

	/*
	 lista_iter_t* iter = lista_iter_crear(lista_vistas);
	 while (!lista_iter_al_final(iter)){
	 	 Vista* vista = (Vista*) lista_iter_ver_actual(iter);
	 	 vista->dibujar(display);
	 	 lista_iter_avanzar(iter);
	 }
	 lista_iter_destruir(iter);
	 */

	// Ponele que se reproducen los sonidos (?)
}

void Nivel::agregarCuerpo(Cuerpo* c){
	lista_insertar_ultimo(lista_cuerpos,c);
}

/*void Nivel::agregarVista(Vista* v){
 	 lista_insertar_ultimo(lista_vistas,v);
}
*/

void Nivel::indicarManual(Manual* m){
	principal = m;
	//Nivel::agregarCuerpo(m);
}
