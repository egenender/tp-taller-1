#include "Personaje.h"
#include "lista.h"

Personaje::Personaje(Area* sup, Animacion* anim, EstrategiaMovimiento* estr):Cuerpo(sup,anim) {
	//Llama al constructor de la clase madre con los parametros de la animacion
	//y la superficie que ocupa
	estrategia = estr;
}

Personaje::~Personaje() : ~Cuerpo(){

}

void Personaje::jugar(){
	estrategia->actuar();
}
