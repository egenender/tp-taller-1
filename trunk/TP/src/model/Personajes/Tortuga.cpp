#include "Tortuga.h"
#include "../Observable.h"
#include <stdio.h>

Tortuga::Tortuga(const char* nom, Area* sup, int v): Hongo(nom, sup, v) {
	velocidadInicial = velocidadX;
}

Tortuga::~Tortuga() {
}

void Tortuga::perderVida(){
	printf("estado: %d\n", estado);
	if (estado == QUIETO){
		morir();
		return;
	}

	estado = QUIETO;
	direccion = 0;
	velocidadX = MULTIPLICADOR * velocidadInicial;

	delete(superficieDeColision);
	int anchoH, altoH, x, y;
	anchoH = (superficieOcupada->obtenerAncho() * FACTOR_TORTUGA_CHICA) / 100;
	altoH = (superficieOcupada->obtenerAlto() * FACTOR_TORTUGA_CHICA) / 100;
	x = superficieOcupada->obtenerPosicion()->obtenerX() + (superficieOcupada->obtenerAncho() - anchoH)/2;
	y = superficieOcupada->obtenerPosicion()->obtenerY() + (superficieOcupada->obtenerAlto() - altoH);

	superficieDeColision = new Area(anchoH, altoH, new Posicion(x,y));

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
