#include "Pluma.h"

Pluma::Pluma(const char* nom, Area* sup): Cuerpo(nom, sup) {
	estado=0;
	int anchoH, altoH, x, y;
	anchoH = (superficieOcupada->obtenerAncho());
	altoH = (superficieOcupada->obtenerAlto()) ;
	x = superficieOcupada->obtenerPosicion()->obtenerX() + (superficieOcupada->obtenerAncho() - anchoH)/2;
	y = superficieOcupada->obtenerPosicion()->obtenerY() + (superficieOcupada->obtenerAlto() - altoH);

	superficieDeColision = new Area(anchoH, altoH, new Posicion(x,y));
}

Pluma::~Pluma() {

}

int Pluma::obtenerEstado(){
	return estado;
}

void Pluma::actualizar(float delta){

}

void Pluma::chocarCon(Actualizable* ac){
	ac->chocarConPluma(this);
}
