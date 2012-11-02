#include "Area.h"
#include "Posicion.h"

/*Area::Area(int alto, int ancho) {
	Area(alto, ancho, new Posicion(0,0));
}*/

Area::Area(int ancho, int alto, Posicion *pos_inicial = NULL){
	if (alto <= 0 || ancho <= 0){
		//Lanzo Excepcion
	}

	this->alto = alto;
	this->ancho = ancho;

	if (!pos_inicial)
		pos = new Posicion(0,0);
	else
		pos = pos_inicial;
	permisoX = permisoY = 0;
}

Area::~Area() {
	delete(pos);
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
	pos->sumarlePosicion(traslado,-permisoX, -permisoY);
	Posicion* maximoPosible = Posicion::obtenerMaximo();
	if ((pos->obtenerX() + ancho - permisoX) > maximoPosible->obtenerX())
		pos->setearX( maximoPosible->obtenerX() - ancho + permisoX);
	if ((pos->obtenerY() + alto - permisoY)> maximoPosible->obtenerY())
		pos->setearY( maximoPosible->obtenerY() - alto + permisoY);
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

void Area::ponerEnPiso(){
	if (!pasaPiso()) return;

	pos->setearY(Posicion::obtenerPiso()-alto);
}

bool Area::pasaPiso(){
	int y = pos->obtenerY();
	y += alto;
	return (y >= Posicion::obtenerPiso());
}

bool Area::estaSobreElPiso(){
	//FIXME: cuando se agreguen colisiones con las plataformas esto tiene que cambiar
	return ((pos->obtenerY() + alto) == Posicion::obtenerPiso());
}

bool Area::colisionaConOtra(Area* otra){
	int aux, auxOtra;

	aux = pos->obtenerX() + ancho;
	auxOtra = otra->obtenerPosicion()->obtenerX();
	if (auxOtra > aux) return false;

	aux = pos->obtenerX();
	auxOtra = otra->obtenerPosicion()->obtenerX() + otra->obtenerAncho();
	if (auxOtra < aux) return false;

	aux = pos->obtenerY() + alto;
	auxOtra = otra->obtenerPosicion()->obtenerY();
	if (auxOtra > aux) return false;

	aux = pos->obtenerY();
	auxOtra = otra->obtenerPosicion()->obtenerY() + otra->obtenerAlto();
	if (auxOtra < aux) return false;

	return true;
}

void Area::cambiarPermisos(int x, int y){
	permisoX = x;
	permisoY = y;
}
