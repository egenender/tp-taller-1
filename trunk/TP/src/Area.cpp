#include "Area.h"
#include "Posicion.h"

Area::Area(int height, int weight) {
	Area(height, weight, new Posicion(0,0));
}

Area::Area(int height, int weight, Posicion *pos_inicial){
	if (height <= 0 || weight <= 0){
		//Lanzo Excepcion
	}

	alto = height;
	ancho = weight;
	pos = pos_inicial;
}

Area::~Area() {
	delete pos;
}

void Area::cambiarPosicion(Posicion* pos_nueva){
	delete pos;
	pos = pos_nueva;
}

void Area::mover(Posicion* traslado){
	//Posicion *pos_nueva = NULL;
	/**pos_nueva = pos->sumar(*traslado);
	delete(pos);
	pos = pos_nueva;*/
	pos->sumarlePosicion(traslado);
	Posicion* maximoPosible = Posicion::obtenerMaximo();
	if (pos->getX() + ancho > maximoPosible->getX())
		pos->setX( maximoPosible->getX() - ancho);
	if (pos->getY() + alto > maximoPosible->getY())
		pos->setY( maximoPosible->getY() - alto );
}

bool Area::verificarColision(Area otraArea){
	bool choque = false;

	//Falta hacer la verificacion de choques..

	return choque;
}

int Area::getAlto(){
	return alto;
}

int Area::getAncho(){
	return ancho;
}

Posicion* Area::getPosicion(){
	return pos;
}
