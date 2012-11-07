#include "Hongo.h"
#include <time.h>
#include <stdlib.h>
#include "../Posicion.h"
#include "Manual.h"

Hongo::Hongo(const char* nom, Area* sup, int vel): Cuerpo(nom,sup) {
	if (vel <= 0) vel = VELOCIDAD_HONGO_STANDARD;
	velocidadX = vel;

	velocidadY = 0;
	direccion = calculoDireccionRandom();

	if (direccion == DERECHA)
		estado = CAMINANDODER;
	else
		estado = CAMINANDOIZQ;
	tengoPiso = chocaConSosten = false;

	int anchoH, altoH, x, y;
	anchoH = (superficieOcupada->obtenerAncho() * FACTOR_ESCALA_HONGO) / 100;
	altoH = (superficieOcupada->obtenerAlto() * FACTOR_ESCALA_HONGO) / 100;
	x = superficieOcupada->obtenerPosicion()->obtenerX() + (superficieOcupada->obtenerAncho() - anchoH)/2;
	y = superficieOcupada->obtenerPosicion()->obtenerY() + (superficieOcupada->obtenerAlto() - altoH);

	superficieDeColision = new Area(anchoH, altoH, new Posicion(x,y));
}

Hongo::~Hongo() {
}

int Hongo::obtenerEstado(){
	return estado;
}

bool Hongo::estaMuerto(){
	return (estado == MUERTO);
}


void Hongo::chocarCon(Actualizable* ac){
	ac->chocarConHongo(this);
}

void Hongo::chocarConBarril(Barril*){
	perderVida();
}

int Hongo::calculoDireccionRandom(){
	float rnd;
	do{
		rnd = (rand() % 1000)+1;
		float w = (rand() % 1000)+1;
		if (rnd > w)
			rnd = w / rnd;
		else
			rnd = rnd/w;
	}while(rnd == 1);

	if (rnd < 0.5)
		return 1;
	else
		return -1;
}

void Hongo::morir(){
	estado = MUERTO;
	huboCambios();
	notificarObservadores();
}

void Hongo::actualizar(float){
	validarPiso();
	actualizarSalto();
	actualizarMovimiento();
	notificarObservadores();
	actualizarEstados();
}

void Hongo::validarPiso(){
	if (obtenerArea()->estaSobreElPiso()){
		tengoPiso = true;
		return;
	}

	if (tengoPiso) return;

	if (estado == CAMINANDODER)
		estado = SALTANDODER;
	else
		estado = SALTANDOIZQ;
}


void Hongo::actualizarSalto(){
	if (!estoySaltando()) return;

	trasladar(0,velocidadY,true);
	velocidadY += ACELERACION_HONGO;

	if (obtenerArea()->pasaPiso() || tengoPiso){
		superficieDeColision->ponerEnPiso();
		superficieOcupada->ponerEnPiso();
		velocidadY = 0;
		if (estado == SALTANDODER)
			estado = CAMINANDODER;
		else
			estado = CAMINANDOIZQ;
	}

}

void Hongo::actualizarEstados(){
	if (!chocaConSosten){
		tengoPiso = false;
	}
	chocaConSosten = false;
}

void Hongo::actualizarMovimiento(){
	if (estoySaltando() || estaMuerto()) return;

	if (direccion == 0){
		estado = QUIETO;
		return;
	}

	int movX = velocidadX * direccion;


	if (((obtenerArea()->obtenerPosicion()->obtenerX() + movX) < 0) || ((obtenerArea()->obtenerPosicion()->obtenerX()+ obtenerArea()->obtenerAncho() + movX) > Posicion::obtenerMaximo()->obtenerX())){
		estado = MUERTO;
		return;
	}
	trasladar(movX,0,true);

	if (direccion == DERECHA)
		estado = CAMINANDODER;
	else
		estado = CAMINANDOIZQ;
}

bool Hongo::estoySaltando(){
	return (estado == SALTANDODER || estado == SALTANDOIZQ);
}

void Hongo::chocarConManual(Manual* pers){
	//tengo que ver por cual direccion se chocan:
	Posicion* posPersAnterior = pers->obtenerPosicionAnterior();
	//me fijo nomas si vino de arriba:
	Posicion* posCmp = new Posicion(posPersAnterior->obtenerX(), posPersAnterior->obtenerY()+ pers->obtenerArea()->obtenerAlto());

	if(posCmp->estaArribaDe(posAnterior)){
		perderVida();
		delete(posCmp);
		return;
	}
	delete(posCmp);

	posCmp = new Posicion(posPersAnterior->obtenerX() + pers->obtenerArea()->obtenerAncho(),posPersAnterior->obtenerY() );

	if (posCmp->estaALaIzquierdaDe(posAnterior)){
		modificacionMovimiento(IZQUIERDA);
		delete (posCmp);
		return;
	}
	delete(posCmp);

	posCmp = new Posicion(posAnterior->obtenerX() + obtenerArea()->obtenerAncho(), posAnterior->obtenerY() );

	if (posCmp->estaALaIzquierdaDe(posPersAnterior)){
		modificacionMovimiento(DERECHA);
		delete(posCmp);
		return;
	}
	delete(posCmp);

}

void Hongo::chocarConPlataforma(Plataforma* p){
	Posicion* posCmp = new Posicion(posAnterior->obtenerX(),posAnterior->obtenerY() + obtenerArea()->obtenerAlto());

	if (!posCmp->estaArribaDe(p->obtenerArea()->obtenerPosicion())){

		Posicion* cmpIzquierda = new Posicion(posAnterior->obtenerX() + obtenerArea()->obtenerAncho()-velocidadX, posAnterior->obtenerY());
		if (cmpIzquierda->estaALaIzquierdaDe(p->obtenerArea()->obtenerPosicion()) && !p->esVigaPorIzquierda()){
			if (!(posCmp->obtenerY() == p->obtenerArea()->obtenerPosicion()->obtenerY())){
				delete(posCmp);
				posCmp = NULL;
				delete(cmpIzquierda);
				int mov = obtenerArea()->obtenerPosicion()->obtenerX() + obtenerArea()->obtenerAncho();
				mov	-= p->obtenerArea()->obtenerPosicion()->obtenerX();
				trasladar(-mov-1,0,true);
				direccion = IZQUIERDA;
				return;
			}

		}
		delete(cmpIzquierda);

		Posicion* cmpDer = new Posicion(p->obtenerArea()->obtenerPosicion()->obtenerX() + p->obtenerArea()->obtenerAncho()-velocidadX, p->obtenerArea()->obtenerPosicion()->obtenerY());
		if (posAnterior->estaALaDerechaDe(cmpDer) && !p->esVigaPorDerecha()){
			if (!(posCmp->obtenerY() == p->obtenerArea()->obtenerPosicion()->obtenerY())){
				delete(posCmp);
				posCmp = NULL;
				delete (cmpDer);
				int x = p->obtenerArea()->obtenerPosicion()->obtenerX() +p->obtenerArea()->obtenerAncho();
				x -= obtenerArea()->obtenerPosicion()->obtenerX();
				trasladar(x+1,0,true);
				direccion = DERECHA;
				return;
			}
		}
		delete(cmpDer);

		Posicion* cmpAbajo = new Posicion(p->obtenerArea()->obtenerPosicion()->obtenerX(), p->obtenerArea()->obtenerPosicion()->obtenerY()+p->obtenerArea()->obtenerAlto());

		if (posAnterior->obtenerY() >= cmpAbajo->obtenerY()){
			delete(posCmp);
			delete(cmpAbajo);
			int mov = p->obtenerArea()->obtenerPosicion()->obtenerY() + p->obtenerArea()->obtenerAlto();
			mov -= obtenerArea()->obtenerPosicion()->obtenerY();
			trasladar(0,mov+1,!(p->esVigaPorDerecha() || p->esVigaPorIzquierda()));
			velocidadY = 0;
			return;
		}
		delete(cmpAbajo);

		if (posCmp)
			delete (posCmp);
		posCmp = NULL;

	}

	bool cambio = true;
	if(posCmp)
		delete(posCmp);
	else
		cambio = false;


	tengoPiso = true;
	chocaConSosten = true;
	velocidadY = 0;

	int y;
	y = obtenerArea()->obtenerPosicion()->obtenerY() + obtenerArea()->obtenerAlto();
	y -= p->obtenerArea()->obtenerPosicion()->obtenerY();

	trasladar(0,-y,cambio);

}

void Hongo::perderVida(){
	morir();
}

void Hongo::chocarConHongo(Hongo* h){
	if (h->obtenerEstado() == MOVILIZQUIERDA || h->obtenerEstado() == MOVILDERECHA)
		morir();
}

void Hongo::modificacionMovimiento(int dir){
	if (dir == IZQUIERDA)
		direccion = DERECHA;
	else
		direccion = IZQUIERDA;
}
