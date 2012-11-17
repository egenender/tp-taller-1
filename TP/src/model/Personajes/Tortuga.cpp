#include "Tortuga.h"
#include "../Observable.h"
#include <stdio.h>

Tortuga::Tortuga(const char* nom, Area* sup, int v): Hongo(nom, sup, v) {
	velocidadInicial = velocidadX;
	recien_movido = false;
	superficieReemplazo = NULL;
	proxEstado = -1;
}

Tortuga::~Tortuga() {
}

void Tortuga::perderVida(){
	huboCambios();
	if (estado == QUIETO){
		morir();
		return;
	}
	permitoMovEnSalto = true;
	if ((estado != MOVILDERECHA && estado != MOVILIZQUIERDA) || !enViga){
		estado = QUIETO;
		direccion = 0;
	}
	velocidadX = MULTIPLICADOR * velocidadInicial;

	int anchoH, altoH, x, y;
	anchoH = (superficieOcupada->obtenerAncho() * FACTOR_TORTUGA_CHICA) / 100;
	altoH = (superficieOcupada->obtenerAlto() * FACTOR_TORTUGA_CHICA) / 100;
	x = superficieOcupada->obtenerPosicion()->obtenerX() + (superficieOcupada->obtenerAncho() - anchoH)/2;
	y = superficieOcupada->obtenerPosicion()->obtenerY() + (superficieOcupada->obtenerAlto() - altoH);

	superficieReemplazo = new Area(anchoH, altoH, new Posicion(x,y));
}

void Tortuga::modificacionMovimiento(int dir){
	Hongo::modificacionMovimiento(dir);

//	if (estado == MOVILIZQUIERDA || estado == MOVILDERECHA)
//		return;

	if (estado == QUIETO || estado == MOVILDERECHA || estado == MOVILIZQUIERDA){
		if (dir == IZQUIERDA)
			proxEstado = MOVILDERECHA;
		else
			proxEstado = MOVILIZQUIERDA;
		recien_movido = true;
	}
	huboCambios();

}

bool Tortuga::recienMovido(){
	return recien_movido;
}

void Tortuga::actualizar(float a){
	if (superficieReemplazo){
		delete(superficieDeColision);
		superficieDeColision = superficieReemplazo;
		superficieReemplazo = NULL;
		if(posAnterior) delete(posAnterior);
		posAnterior = new Posicion(superficieDeColision->obtenerPosicion()->obtenerX(),superficieDeColision->obtenerPosicion()->obtenerY());
	}
	Hongo::actualizar(a);
	if (proxEstado != -1){
		estado = proxEstado;
		huboCambios();
		proxEstado = -1;
	}
	notificarObservadores();
	recien_movido = false;
}
