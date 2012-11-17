#include "CamaElastica.h"
#include "../Tipos.h"

CamaElastica::CamaElastica(const char* nom, Area* sup): Cuerpo(nom,sup) {

	estado=0;
	int anchoH, altoH, x, y;
	anchoH = (superficieOcupada->obtenerAncho());
	altoH = (superficieOcupada->obtenerAlto()) ;
	x = superficieOcupada->obtenerPosicion()->obtenerX() + (superficieOcupada->obtenerAncho() - anchoH)/2;
	y = superficieOcupada->obtenerPosicion()->obtenerY() + (superficieOcupada->obtenerAlto() - altoH);

	superficieDeColision = new Area(anchoH, altoH, new Posicion(x,y));
	chocaConManual = false;
	//posAnterior= superficieOcupada->obtenerPosicion();

}


CamaElastica::~CamaElastica() {

}

int CamaElastica::obtenerEstado(){
	return estado;
}
void CamaElastica::actualizar(float delta){
	if (!chocaConManual){
		if (estado!=QUIETO){
			estado = QUIETO;
			huboCambios();
		}
	}
	chocaConManual = false;
	notificarObservadores();
}


void CamaElastica::chocarCon(Actualizable* ac){
	ac->chocarConCamaElastica(this);
}

void CamaElastica::chocarConManual(Manual* m){
	Cuerpo* cuerpo = (Cuerpo*)m;
	Posicion* pos = cuerpo->obtenerPosicionAnterior();
	Posicion* posCmp = new Posicion(pos->obtenerX(), pos->obtenerY() + cuerpo->obtenerArea()->obtenerAlto());
	if (posCmp->estaArribaDe(this->obtenerArea()->obtenerPosicion())){
		chocaConManual = true;
		estado = LANZANDO;
		huboCambios();
	}
	chocaConManual = true;
	delete (posCmp);
}

unsigned int CamaElastica::obtenerTipo(){
	return TIPO_CAMA_ELASTICA;
}
