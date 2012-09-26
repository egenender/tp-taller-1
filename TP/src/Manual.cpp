#include "Manual.h"

Manual::Manual(const char* nombrecito,Area* sup): Cuerpo(nombrecito, sup) {
	velocidad = VELOCIDAD_STANDARD;
	estado = QUIETODER;
}

Manual::Manual(const char* nombrecito, Area* sup, int vel):Cuerpo(nombrecito, sup){
	if (vel <= 0){
		//Lanzo excepcion?
		//Por ahora hago esto:
		vel = VELOCIDAD_STANDARD;
	}
	velocidad = vel;
	estado = QUIETODER;
}

Manual::~Manual() {
	//Por ahora, todo lo que se tiene se elimina en el destructor del padre.
}

void Manual::moverALaDerecha(){
	trasladar(1);
	estado = CAMINANDODER;
}

void Manual::moverALaIzquierda(){
	trasladar(-1);
	estado = CAMINANDOIZQ;
}

void Manual::trasladar(int factor){
	float DeltaX = velocidad * factor * delta;
	Posicion* posDesplazamiento = new Posicion ((int) DeltaX,0);
	superficieOcupada->mover(posDesplazamiento);
	delete(posDesplazamiento);
	huboCambios(); //el método se hereda de Observable
}

void Manual::saltar(){} //Por ahora no hace nada

void Manual::atacar(){} //idem

void Manual::especial(){} //idem

void Manual::actualizar(float delta){
	this->delta = delta;
	notificarObservadores();
}

int Manual::obtenerEstado(){return estado;}

void Manual::detener(){
	if (estado == QUIETO || estado == QUIETODER || estado == QUIETOIZQ) return;

	if (estado == CAMINANDODER)
		estado = QUIETODER;
	if (estado == CAMINANDOIZQ)
		estado = QUIETOIZQ;
	huboCambios();
}
