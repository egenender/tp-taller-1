#include "Manual.h"

// Nuevo:
/*Manual::Manual(const char* nombrecito,Area* sup): Cuerpo(nombrecito, sup) {
	velocidad = VELOCIDAD_STANDARD;
	velocidadX = 0;
	direccion = DERECHA;
	estado = QUIETODER;
}*/

// Nuevo:
/*Manual::Manual(const char* nombrecito, Area* sup, int vel):Cuerpo(nombrecito, sup){
	if (vel <= 0){
		//Lanzo excepcion?
		//Por ahora hago esto:
		vel = VELOCIDAD_STANDARD;
	}
	velocidad = vel;
	velocidadX = 0;
	direccion = DERECHA;
	estado = QUIETODER;
}*/

Manual::~Manual() {
	//Por ahora,  lo que se tiene se elimina en el destructor del padre.
}

// Nuevo:
/*void Manual::moverALaDerecha(){
	direccion = DERECHA;
	estado = CAMINANDODER;
	trasladar();
}*/

// Nuevo:
/*void Manual::moverALaIzquierda(){
	direccion = IZQUIERDA;
	estado = CAMINANDOIZQ;
	trasladar();
}*/

// Nuevo:
/*void Manual::trasladar(){

	velocidadX = velocidad * direccion;

	huboCambios(); //el método se hereda de Observable
}*/

void Manual::saltar(){
	if (estado == QUIETODER || estado == CAMINANDODER){
		estado = SALTANDODER;
		velocidadY = velocidadSaltoBase;
		return;
	}

	if(estado == QUIETOIZQ || estado == CAMINANDOIZQ){
		estado = SALTANDOIZQ;
		velocidadY = velocidadSaltoBase;
		return;
	}
}

void Manual::atacar(){} //idem

void Manual::especial(){} //idem


// Nuevo:
/*void Manual::actualizar(float delta){

	// Como lo unico que hacemos es esto por ahora:

	float DeltaX = velocidadX * delta;
	Posicion* posDesplazamiento = new Posicion ((int) DeltaX,0);
	superficieOcupada->mover(posDesplazamiento);
	delete(posDesplazamiento);

	notificarObservadores();
}*/

int Manual::obtenerEstado(){return estado;}

// Nuevo:
/*void Manual::detener(){
	if (estado == QUIETO || estado == QUIETODER || estado == QUIETOIZQ) return;

	if (estado == CAMINANDODER)
		estado = QUIETODER;
	if (estado == CAMINANDOIZQ)
		estado = QUIETOIZQ;
	velocidadX = 0;
	huboCambios();
}*/


// Viejo:
Manual::Manual(const char* nombrecito,Area* sup): Cuerpo(nombrecito, sup) {
	velocidad = VELOCIDAD_STANDARD;
	velocidadSaltoBase = VELOCIDAD_STANDARD;
	estado = QUIETODER;
}

// Viejo:
Manual::Manual(const char* nombrecito, Area* sup, int vel):Cuerpo(nombrecito, sup){
	if (vel <= 0){
		//Lanzo excepcion?
		//Por ahora hago esto:
		vel = VELOCIDAD_STANDARD;
	}
	velocidad = vel;

	//FIXME: esto tiene que cambiar cuando lo reciba por parametro
	velocidadSaltoBase = -500;

	estado = QUIETODER;
}

// Viejos:
void Manual::moverALaDerecha(){
	movimiento(SALTANDODER, CAMINANDODER, DERECHA);
}

void Manual::moverALaIzquierda(){
	movimiento(SALTANDOIZQ, CAMINANDOIZQ, IZQUIERDA);
}

void Manual::movimiento(int saltando, int caminando, int direccion){
	if (estoySaltando())
		estado = saltando;
	else
		estado = caminando;
	trasladar(direccion * velocidad, 0);
}


void Manual::trasladar(int factorX, int factorY){
	float DeltaX = factorX * delta;
	float DeltaY = factorY * delta;
	Posicion* posDesplazamiento = new Posicion ((int) DeltaX,(int)DeltaY);
	superficieOcupada->mover(posDesplazamiento);
	delete(posDesplazamiento);
	huboCambios(); //el método se hereda de Observable
}

// Viejo:
void Manual::actualizar(float delta){
	this->delta = delta;
	actualizarSalto();
	notificarObservadores();
}

bool Manual::estoySaltando(){
	return (estado == SALTANDOIZQ || estado == SALTANDODER);
}

// Viejo:
void Manual::detener(){
	if (estoySaltando()) return;
	if (estado == QUIETO || estado == QUIETODER || estado == QUIETOIZQ) return;

	if (estado == CAMINANDODER)
		estado = QUIETODER;
	if (estado == CAMINANDOIZQ)
		estado = QUIETOIZQ;
	huboCambios();
}


void Manual::actualizarSalto(){
	if (!estoySaltando()) return;

	trasladar(0,velocidadY);
	velocidadY += ACELERACION;
	if (chocaConPiso()){
		superficieOcupada->ponerEnPiso();
		velocidadY = 0;
		if (estado == SALTANDODER) estado = QUIETODER;
		else estado = QUIETOIZQ;
	}
}

bool Manual::chocaConPiso(){
	return superficieOcupada->pasaPiso();
}
