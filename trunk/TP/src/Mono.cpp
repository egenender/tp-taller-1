#include "Mono.h"
#include "Personaje.h"

Mono::Mono(Area* sup, Animacion* anim, EstrategiaMovimiento* estr):Personaje(sup,anim,estr) {

}

Mono::~Mono() {

}

void Mono::moverAIzquierda(){
	//No hace nada
}
void Mono::moverADerecha(){
	//No hace nada
}
void Mono::atacar(){
	//Acá podríamos agregarle que acuda a su "fábrica"
}

void Mono::saltar(){
	//No hace nada
}

void Mono::especial(){
	//?
}
