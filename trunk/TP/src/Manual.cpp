#include "Manual.h"

Manual::Manual(const char* nombrecito,Area* sup): Cuerpo(nombrecito, sup) {
	velocidad = VELOCIDAD_STANDARD;
}

Manual::Manual(const char* nombrecito, Area* sup, int vel):Cuerpo(nombrecito, sup){
	if (vel <= 0){
		//Lanzo excepcion?
		//Por ahora hago esto:
		vel = VELOCIDAD_STANDARD;
	}
	velocidad = vel;
}

Manual::~Manual() {
	//Por ahora, todo lo que se tiene se elimina en el destructor del padre.
}

void Manual::moverALaDerecha(){
	trasladar(1);
	//avisar Cambios al observador
}

void Manual::moverALaIzquierda(){
	trasladar(-1);
	//avisar Cambios al observador
}

void Manual::trasladar(int factor){
	int DeltaX = velocidad * factor;
	Posicion* posDesplazamiento = new Posicion (DeltaX,0);
	superficieOcupada->mover(posDesplazamiento);
	delete posDesplazamiento;
}

void Manual::saltar(){} //Por ahora no hace nada

void Manual::atacar(){} //idem

void Manual::especial(){} //idem

void Manual::actualizar(){
// que hago aca?
}
