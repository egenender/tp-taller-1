#include "Automatico.h"

Automatico::Automatico(const char* nombrecito, Area* sup): Cuerpo(nombrecito,sup) {
	estado = QUIETO;
}

Automatico::~Automatico() {
	//ya se destruyen las cosas en el cuerpo

	//si despues se hace algo que le agregue inteligencia artificial, se lo avisa
}

void Automatico::actualizar(float delta){
	huboCambios();
	Automatico::notificarObservadores();
}

int Automatico::obtenerEstado(){
	return estado;
}


void Automatico::chocarCon(Actualizable*){}
