#include "Personaje.h"
#include "lista.h"

Personaje::Personaje(Area* sup, Animacion* anim, lista_t* acciones_posibles):Cuerpo(sup,anim) {
	//Llama al constructor de la clase madre con los parametros de la animacion
	//y la superficie que ocupa
	acciones = acciones_posibles;
}

Personaje::~Personaje() : ~Cuerpo(){
	lista_destruir(acciones,NULL);
}

