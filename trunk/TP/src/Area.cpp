#include "Area.h"
#include "Posicion.h"

Area::Area(int alto, int ancho) {
	Area(alto, ancho, new Posicion(0,0));
}

Area::Area(int alto, int ancho, Posicion *pos_inicial){
	if (alto <= 0 || ancho <= 0){
		//Lanzo Excepcion
	}

	this->alto = alto;
	this->ancho = ancho;
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
	if (pos->obtenerX() + ancho > maximoPosible->obtenerX())
		pos->setearX( maximoPosible->obtenerX() - ancho);
	if (pos->obtenerY() + alto > maximoPosible->obtenerY())
		pos->setearY( maximoPosible->obtenerY() - alto );
}

bool Area::verificarColision(Area otraArea){
	bool choque = false;

	//Falta hacer la verificacion de choques..

	return choque;
}

int Area::obtenerAlto(){
	return alto;
}

int Area::obtenerAncho(){
	return ancho;
}

Posicion* Area::obtenerPosicion(){
	return pos;
}
