/*
 * CamaElastica.cpp
 *
 *  Created on: Nov 9, 2012
 *      Author: juaqi
 */

#include "CamaElastica.h"

CamaElastica::CamaElastica(const char* nom, Area* sup): Cuerpo(nom,sup) {

	estado=0;
	int anchoH, altoH, x, y;
	anchoH = (superficieOcupada->obtenerAncho());
	altoH = (superficieOcupada->obtenerAlto()) ;
	x = superficieOcupada->obtenerPosicion()->obtenerX() + (superficieOcupada->obtenerAncho() - anchoH)/2;
	y = superficieOcupada->obtenerPosicion()->obtenerY() + (superficieOcupada->obtenerAlto() - altoH);

	superficieDeColision = new Area(anchoH, altoH, new Posicion(x,y));

	//posAnterior= superficieOcupada->obtenerPosicion();

}


CamaElastica::~CamaElastica() {

}

int CamaElastica::obtenerEstado(){
	return estado;
}
void CamaElastica::actualizar(float delta){

}


void CamaElastica::chocarCon(Actualizable* ac){
	ac->chocarConCamaElastica(this);
}



