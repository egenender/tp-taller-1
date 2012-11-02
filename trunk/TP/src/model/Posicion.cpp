#include "Posicion.h"
#include <stddef.h>

Posicion* Posicion::maximo = NULL;
int Posicion::piso;

Posicion::Posicion() {
	x = y = 0;
}

Posicion::~Posicion() {
	if (maximo != NULL) {
	//	delete(maximo); // TODO: EEMMM VAMOS A PERDER MEMORIA D:
	}
}

Posicion::Posicion(int a, int b){
	if (a < 0 || b < 0) {
		//Lanzo Excepcion
	}
	x = a;
	y = b;
}

/*Posicion Posicion::obtenerDerecha(){
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
*/
int Posicion::obtenerX(){
	return x;
}

int Posicion::obtenerY(){
	return y;
}

bool Posicion::estaALaDerechaDe(Posicion *pos){
	return (x > pos->x);
}

bool Posicion::estaALaIzquierdaDe(Posicion *pos){
	return (x < pos->x);
}

bool Posicion::estaAbajoDe(Posicion *pos){
	return (y > pos->y);
}

bool Posicion::estaArribaDe(Posicion *pos){
	return (y < pos->y);
}

bool Posicion::estaALaDerechaOIgualDe(Posicion* pos){
	return (x >= pos->x);
}

bool Posicion::estaALaIzquierdaOIgualDe(Posicion* pos){
	return (x <= pos->x);
}

bool Posicion::estaArribaOIgualDe(Posicion* pos){
	return (y >= pos->y);
}

bool Posicion::estaAbajoOIgualDe(Posicion* pos){
	return (y <= pos->y);
}

/*void Posicion::moverHorizontalmente(int deltaX){
	x += deltaX;

}

void Posicion::moverVerticalmente(int deltaY){
	y *= deltaY;
}*/

/*
Posicion Posicion::operator+(Posicion sumando){
	Posicion pos(x,y); //hago una copia
	pos.moverHorizontalmente(sumando.x);
	pos.moverVerticalmente(sumando.y);
	return pos;
}
*/

void Posicion::sumarlePosicion(Posicion *pos_sumada){
	x += pos_sumada->x;
	if (x < 0) x = 0;
	if (maximo){
		if (x > maximo->x) x = maximo->x;}

	y += pos_sumada->y;
	if (y < 0) y = 0;
	if (maximo){
		if (y > maximo->y) y = maximo->y;}
}

void Posicion::indicarMaximo(int x, int y){
	maximo = new Posicion(x,y);
	//FIXME: Sacar esto de aca
	piso = y;
}

void Posicion::setearX(int a){
	if(!maximo){
		x = a;
		return;
	}

	if (a <= maximo->x)
		x = a;
}

void Posicion::setearY(int b){
	if (!maximo){
		y = b;
		return;
	}

	if (b <= maximo->y)
		y = b;
}

void Posicion::indicarPiso(int y){
	if (y < 0) return;
	if (y > maximo->y) return;
	piso = y;
}
int Posicion::obtenerPiso(){
	return piso;
}

Posicion* Posicion::restarPosiciones(Posicion* una, Posicion* otra){
	Posicion* resul = new Posicion (una->x - otra->x, una->y - otra->y);
	return resul;
}
