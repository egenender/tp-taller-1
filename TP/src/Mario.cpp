#include "Mario.h"
#include "Posicion.h"

Mario::Mario(Area* sup, Animacion* anim, EstrategiaMovimiento* estr):Personaje(sup,anim,estr) {

}

Mario::~Mario():~Personaje() {

}

void Mario::moverAIzquierda(){
	moverHaciaCostados(-1);
}

void Mario::moverADerecha(){
	moverHaciaCostados(1);
}

void Mario::moverHaciaCostados(int x){
	Posicion* delta = new Posicion(x,0);
	superficieOcupada->mover(*delta);
	delete delta;
}


void Mario::atacar(){
	//Hacemos que lance un ataque
}

void Mario::saltar(){
	//Hacemos que se mueva verticalmente --> analizar si hay que aplicar fisica
}

void Mario::especial(){
	//?
}

