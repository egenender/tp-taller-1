#include "Escalera.h"
#include <stdio.h>

Escalera::Escalera(const char* nom, Area* sup):Cuerpo(nom,sup) {
	Posicion* pos = superficieOcupada->obtenerPosicion();
	int ancho = superficieOcupada->obtenerAncho();
	int alto = superficieOcupada->obtenerAlto();
	int y = pos->obtenerY();
	int x = pos->obtenerX();
	x += ancho / 2;
	ancho /= 4;
	x -= ancho / 2 ;

	//int FACTOR = 90;
	//alto = (alto *FACTOR) / 100;
	y += (superficieOcupada->obtenerAlto()- alto);

	superficieDeColision = new Area(ancho, alto, new Posicion(x,y));
}

Escalera::~Escalera() {

}

int Escalera::obtenerEstado(){
	return 0;
}

void Escalera::actualizar(float delta){

}


void Escalera::chocarCon(Actualizable* ac){
	ac->chocarConEscalera(this);
}
