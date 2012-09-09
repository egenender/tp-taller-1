
#include "Cuerpo.h"

Cuerpo::Cuerpo(Area* sup, Animacion* anim) {
	superficieOcupada = sup;
	animado = anim;
	vivo = true;
}

Cuerpo::~Cuerpo() {
	delete superficieOcupada;
	delete animado;
}

void Cuerpo::animar(){
	//animado.HacerAnimarOComoSeLlameElMetodo();
}

bool Cuerpo::estaVivo(){
	return vivo;
}

void Cuerpo::mover(Posicion* pos){
	superficieOcupada->cambiarPosicion(pos);
}
