#include "Plataforma.h"

Plataforma::Plataforma(const char* nom, Area* sup): Cuerpo(nom,sup) {
	vigaDer = false;
	vigaIzq = false;
	angulo = 0;
	direccion = 0;
}

Plataforma::~Plataforma() {

}

int Plataforma::obtenerEstado(){
	return 0;
}
void Plataforma::actualizar(float delta){

}


void Plataforma::chocarCon(Actualizable* ac){
	ac->chocarConPlataforma(this);
}
void Plataforma::chocarConManual(Manual*){}
void Plataforma::chocarConPlataforma(Plataforma*){}
void Plataforma::chocarConEscalera(Escalera*){}

bool Plataforma::esVigaPorDerecha(){
	return vigaDer;
}
bool Plataforma::esVigaPorIzquierda(){
	return vigaIzq;
}
void Plataforma::setearComoVigaPorDerecha(){
	vigaDer = true;
}
void Plataforma::setearComoVigaPorIzquierda(){
	vigaIzq = true;
}
void Plataforma::setearAngulo(float alfa){
	if (alfa < 90 && alfa > -90)
		angulo = alfa;
}
void Plataforma::setearDireccion(int dir){
	direccion = dir;
}

bool Plataforma::caeADerecha(){
	return direccion == 1;
}

bool Plataforma::caeAIzquierda(){
	return direccion == -1;
}
