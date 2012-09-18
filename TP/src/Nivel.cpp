#include "Nivel.h"

Nivel::Nivel() {

}

Nivel::~Nivel() {
	Nivel::terminar();
}

void Nivel::manejarEvento(SDL_Event* evento){
	//CTRL-C CTRL-V de lo que hizo Nico en EstadoIntroduccion

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

void Nivel::iniciar(){
	lista_cuerpos = lista_crear();
	//lista_vistas = lista_crear();
}

void destruirCuerpo(void* cuerpo){
	Cuerpo* c = (Cuerpo*) cuerpo;
	delete c;
}

void Nivel::terminar(){
	lista_destruir(lista_cuerpos,destruirCuerpo); //o usar un destructor null?
	//lista_destruir(lista_vistas, destruirVista);
}


void Nivel::actualizar(){
	lista_iter_t* iter = lista_iter_crear(lista_cuerpos);
	while (!lista_iter_al_final(iter)){
		Cuerpo* cuerpito = (Cuerpo*)lista_iter_ver_actual(iter);
		cuerpito->actualizar();
		lista_iter_avanzar(iter);
	}

	lista_iter_destruir(iter);
}

void Nivel::dibujar(SDL_Surface* display){
	/*
	 lista_iter_t* iter = lista_iter_crear(lista_vistas);
	 while (!lista_iter_al_final(iter)){
	 	 Vista* vista = (Vista*) lista_iter_ver_actual(iter);
	 	 vista->dibujar(display);
	 	 lista_iter_avanzar(iter);
	 }
	 lista_iter_destruir(iter);
	 */
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
