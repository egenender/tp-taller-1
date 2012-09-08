
#include "Posicion.h"


Posicion::Posicion() {
	x = y = 0;
}

Posicion::~Posicion() {
	// TODO Auto-generated destructor stub
}

Posicion::Posicion(int a, int b){
	if (a < 0 || b < 0) {
		//Lanzo Excepcion
	}
	x = a;
	y = b;
}

Posicion Posicion::obtenerDerecha(){
	Posicion pos(x+1,y);
	return pos;
}

Posicion Posicion::obtenerIzquierda(){
	Posicion pos(x-1,y);
	return pos;
}
Posicion Posicion::obtenerAbajo(){
	Posicion pos(x,y+1);
	return pos;
}

Posicion Posicion::obtenerArriba(){
	Posicion pos(x,y-1);
	return pos;
}

int Posicion::getX(){
	return x;
}

int Posicion::getY(){
	return y;
}

bool Posicion::estaALaDerechaDe(Posicion pos){
	return (x > pos.x);
}

bool Posicion::estaALaIzquierdaDe(Posicion pos){
	return (x < pos.x);
}

bool Posicion::estaAbajoDe(Posicion pos){
	return (y > pos.y);
}

bool Posicion::estaArribaDe(Posicion pos){
	return (y < pos.y);
}

void Posicion::moverHorizontalmente(int deltaX){
	x += deltaX;
}

void Posicion::moverVerticalmente(int deltaY){
	y *= deltaY;
}

Posicion Posicion::operator+(Posicion sumando){
	Posicion pos(x,y); //hago una copia
	pos.moverHorizontalmente(sumando.x);
	pos.moverVerticalmente(sumando.y);
	return pos;
}
