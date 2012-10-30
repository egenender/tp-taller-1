#include "Manual.h"
#include <stdio.h>


Manual::~Manual() {
	//Por ahora,  lo que se tiene se elimina en el destructor del padre.
}

void Manual::saltar(){
	if (estado == QUIETODER || estado == CAMINANDODER){
		estado = SALTANDODER;
		velocidadY = velocidadSaltoBase;
		tengoPiso = false;
		return;
	}

	if(estado == QUIETOIZQ || estado == CAMINANDOIZQ){
		estado = SALTANDOIZQ;
		velocidadY = velocidadSaltoBase;
		tengoPiso = false;
		return;
	}
}

void Manual::atacar(){} //idem

void Manual::especial(){} //idem

int Manual::obtenerEstado(){
	return estado;
}

Manual::Manual(const char* nombrecito, Area* sup, int vel, int fuerza):Cuerpo(nombrecito, sup){
	if (vel <= 0){
		vel = VELOCIDAD_STANDARD;
	}
	if (fuerza <= 0){
		fuerza = VELOCIDAD_STANDARD;
	}

	velocidad = vel;
	velocidadSaltoBase = -fuerza;
	estado = QUIETODER;
	puedoSubir = false;
	tengoPiso = false;
}

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
	//float DeltaX = factorX * delta;
	//float DeltaY = factorY * delta;

	Posicion* posDesplazamiento = new Posicion (factorX,factorY);
	superficieOcupada->mover(posDesplazamiento);
	delete(posDesplazamiento);
	huboCambios();
	puedoSubir = false;
	//tengoPiso = false;
}

// Viejo:
void Manual::actualizar(float delta){
	this->delta = delta;
	validarPiso();
	actualizarSalto();
	notificarObservadores();
	tengoPiso = false;
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
	if (chocaConPiso() || tengoPiso){
		superficieOcupada->ponerEnPiso();
		velocidadY = 0;
		if (estado == SALTANDODER) estado = QUIETODER;
		else estado = QUIETOIZQ;
	}
}

bool Manual::chocaConPiso(){
	return superficieOcupada->pasaPiso();
}

void Manual::morir(){
	estado = MUERTO;
	huboCambios();
}
bool Manual::estaMuerto(){
	return (estado == MUERTO);
}

void Manual::validarPiso(){
	if (superficieOcupada->estaSobreElPiso()){
		tengoPiso = true;
		return;
	}

	if (tengoPiso) return;

	if (estado == CAMINANDODER || estado == QUIETODER)
		estado = SALTANDODER;
	else if (estado == CAMINANDOIZQ || estado == QUIETOIZQ)
		estado = SALTANDOIZQ;

}

void Manual::subir(){
	if (!puedoSubir) return;

	puedoSubir = false;
	//por ahora digo que la velocidad a la que sube, es la misma a la que se mueve
	trasladar(0, -velocidad);
}

void Manual::bajar(){
	if (!puedoSubir) return;
	puedoSubir = false;
	trasladar(0,velocidad);
}


void Manual::chocarCon(Actualizable* ac){
	ac->chocarConManual(this);
}
void Manual::chocarConManual(Manual* manual){
	//No pasa nada
}
void Manual::chocarConPlataforma(Plataforma* p){
	int y = p->obtenerPosicion()->obtenerY();
	int MIy = superficieOcupada->obtenerPosicion()->obtenerY();

	if (MIy < y){
		Posicion* posNueva = new Posicion(superficieOcupada->obtenerPosicion()->obtenerX(), (y - superficieOcupada->obtenerAlto()));
		moverA(posNueva);
		tengoPiso = true;
	}
}
void Manual::chocarConEscalera(Escalera*){
	puedoSubir = true;
	tengoPiso = true;
}
