#include "Plataforma.h"

Plataforma::Plataforma(const char* nom, Area* sup): Cuerpo(nom,sup) {

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
