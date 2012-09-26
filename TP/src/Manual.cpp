#include "Manual.h"

// Nuevo:
Manual::Manual(const char* nombrecito,Area* sup): Cuerpo(nombrecito, sup) {
	velocidad = VELOCIDAD_STANDARD;
	velocidadX = 0;
	direccion = DERECHA;
	estado = QUIETODER;
}

// Nuevo:
Manual::Manual(const char* nombrecito, Area* sup, int vel):Cuerpo(nombrecito, sup){
	if (vel <= 0){
		//Lanzo excepcion?
		//Por ahora hago esto:
		vel = VELOCIDAD_STANDARD;
	}
	velocidad = vel;
	velocidadX = 0;
	direccion = DERECHA;
	estado = QUIETODER;
}

Manual::~Manual() {
	//Por ahora, todo lo que se tiene se elimina en el destructor del padre.
}

// Nuevo:
void Manual::moverALaDerecha(){
	direccion = DERECHA;
	estado = CAMINANDODER;
	trasladar();
}

// Nuevo:
void Manual::moverALaIzquierda(){
	direccion = IZQUIERDA;
	estado = CAMINANDOIZQ;
	trasladar();
}

// Nuevo:
void Manual::trasladar(){

	velocidadX = velocidad * direccion;

	huboCambios(); //el método se hereda de Observable
}

void Manual::saltar(){} //Por ahora no hace nada

void Manual::atacar(){} //idem

void Manual::especial(){} //idem


// Nuevo:
void Manual::actualizar(float delta){

	// Como lo unico que hacemos es esto por ahora:

	float DeltaX = velocidadX * delta;
	Posicion* posDesplazamiento = new Posicion ((int) DeltaX,0);
	superficieOcupada->mover(posDesplazamiento);
	delete(posDesplazamiento);

	notificarObservadores();
}

int Manual::obtenerEstado(){return estado;}

// Nuevo:
void Manual::detener(){
	if (estado == QUIETO || estado == QUIETODER || estado == QUIETOIZQ) return;

	if (estado == CAMINANDODER)
		estado = QUIETODER;
	if (estado == CAMINANDOIZQ)
		estado = QUIETOIZQ;
	velocidadX = 0;
	huboCambios();
}


// Viejo:
/*Manual::Manual(const char* nombrecito,Area* sup): Cuerpo(nombrecito, sup) {
	velocidad = VELOCIDAD_STANDARD;
	estado = QUIETODER;
}*/

// Viejo:
/*Manual::Manual(const char* nombrecito, Area* sup, int vel):Cuerpo(nombrecito, sup){
	if (vel <= 0){
		//Lanzo excepcion?
		//Por ahora hago esto:
		vel = VELOCIDAD_STANDARD;
	}
	velocidad = vel;
	estado = QUIETODER;
}*/

// Viejos:
/*void Manual::moverALaDerecha(){
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
}*/

// Viejo:
/*void Manual::actualizar(float delta){
	this->delta = delta;
	notificarObservadores();
}*/

// Viejo:
/*void Manual::detener(){
	if (estado == QUIETO || estado == QUIETODER || estado == QUIETOIZQ) return;

	if (estado == CAMINANDODER)
		estado = QUIETODER;
	if (estado == CAMINANDOIZQ)
		estado = QUIETOIZQ;
	huboCambios();
}*/
