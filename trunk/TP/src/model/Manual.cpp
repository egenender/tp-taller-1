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
	atraviesaBloques = false;
	chocaConEscalera = false;
	posAnterior = NULL;

//	int ancho = sup->obtenerAncho();
//	int alto = sup->obtenerAlto();
//
//	int anchoC = ancho * 3 / 4;
//	int altoC = alto * 3/4;
//	Posicion* posC = new Posicion(sup->obtenerPosicion()->obtenerX() + (ancho/4), sup->obtenerPosicion()->obtenerY() + (alto/4));
//	superficieDeColision = new Area(anchoC, altoC, posC);

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
	if (posAnterior) delete(posAnterior);
	posAnterior = new Posicion(obtenerArea()->obtenerPosicion()->obtenerX(),obtenerArea()->obtenerPosicion()->obtenerY());
	Posicion* posDesplazamiento = new Posicion (factorX,factorY);
	superficieOcupada->mover(posDesplazamiento);
//	superficieDeColision->mover(posDesplazamiento);

	delete(posDesplazamiento);
	huboCambios();
	puedoSubir = false;
//	atraviesaBloques = false;
	//tengoPiso = false;
}

// Viejo:
void Manual::actualizar(float delta){
	this->delta = delta;
	validarPiso();
	actualizarSalto();
	notificarObservadores();
	tengoPiso = false;
	if(!chocaConEscalera){
		atraviesaBloques = false;
	}
	chocaConEscalera = false;
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
	if(atraviesaBloques) return;

	Posicion* posCmp = new Posicion(posAnterior->obtenerX(),posAnterior->obtenerY() + obtenerArea()->obtenerAlto());

	if (!posCmp->estaArribaDe(p->obtenerArea()->obtenerPosicion())){

		delete (posCmp);
		posCmp = NULL;
		Posicion* cmpAbajo = new Posicion(p->obtenerArea()->obtenerPosicion()->obtenerX(), p->obtenerArea()->obtenerPosicion()->obtenerY()+p->obtenerArea()->obtenerAlto());
		if (posAnterior->estaAbajoDe(cmpAbajo)){
			delete(cmpAbajo);
			if (atraviesaBloques) return;
			int mov = p->obtenerArea()->obtenerPosicion()->obtenerY() + p->obtenerArea()->obtenerAlto();
			mov -= obtenerArea()->obtenerPosicion()->obtenerY();
			trasladar(0,mov+1);
			velocidadY = 0;
			return;
		}
		delete(cmpAbajo);

		Posicion* cmpIzquierda = new Posicion(posAnterior->obtenerX() + obtenerArea()->obtenerAncho(), posAnterior->obtenerY());
		if (cmpIzquierda->estaALaIzquierdaDe(p->obtenerArea()->obtenerPosicion())){
			delete(cmpIzquierda);
			if (atraviesaBloques) return;
			int mov = obtenerArea()->obtenerPosicion()->obtenerX() + obtenerArea()->obtenerAncho();
			mov	-= p->obtenerArea()->obtenerPosicion()->obtenerX();
			trasladar(-mov-1,0);
			return;
		}

		delete(cmpIzquierda);
		Posicion* cmpDer = new Posicion(p->obtenerArea()->obtenerPosicion()->obtenerX() + p->obtenerArea()->obtenerAncho(), p->obtenerArea()->obtenerPosicion()->obtenerY());
		if (posAnterior->estaALaDerechaDe(cmpDer)){
			delete (cmpDer);
			if (atraviesaBloques) return;
			int x = p->obtenerArea()->obtenerPosicion()->obtenerX() +p->obtenerArea()->obtenerAncho();
			x -= obtenerArea()->obtenerPosicion()->obtenerX();
			trasladar(x+1,0);
			return;
		}
		delete(cmpDer);
//		tengoPiso = true;
//		return;
	}
	if(posCmp)
		delete(posCmp);


	int y;
	y = obtenerArea()->obtenerPosicion()->obtenerY() + obtenerArea()->obtenerAlto();
	y -= p->obtenerArea()->obtenerPosicion()->obtenerY();

	trasladar(0,-y);
	tengoPiso = true;
}
void Manual::chocarConEscalera(Escalera*){
	puedoSubir = true;
	tengoPiso = true;
	atraviesaBloques = true;
	chocaConEscalera = true;
}
