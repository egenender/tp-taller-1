#include "Tortuga.h"
#include "../Observable.h"

Tortuga::Tortuga(const char* nom, Area* sup, int v): Hongo(nom, sup, v) {
	velocidadInicial = velocidadX;
}

Tortuga::~Tortuga() {
}

void Tortuga::perderVida(){
	if (estado == QUIETO){
		morir();
		return;
	}

	estado = QUIETO;
	direccion = 0;
	velocidadX = 5 * velocidadInicial;
}

void Tortuga::modificacionMovimiento(int dir){
	if (estado == MOVILIZQUIERDA || estado == MOVILDERECHA)
		return;

	Hongo::modificacionMovimiento(dir);
	if (dir == IZQUIERDA)
		estado = MOVILDERECHA;
	else
		estado = MOVILIZQUIERDA;
}
