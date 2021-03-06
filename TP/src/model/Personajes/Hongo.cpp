#include "Hongo.h"
#include <time.h>
#include <stdlib.h>
#include "../Posicion.h"
#include "Manual.h"
#include "../Tipos.h"

Hongo::Hongo(const char* nom, Area* sup, int vel): Cuerpo(nom,sup) {
	if (vel <= 0) vel = VELOCIDAD_HONGO_STANDARD;
	velocidadX = vel;
	permitoMovEnSalto = false;
	velocidadY = 0;
	saltoMov = false;
	enViga = false;
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
	proxDir = 0;
	fabrica = new FabricaPowerUps();
}

Hongo::~Hongo() {
	delete(fabrica);
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

float Hongo::tirarRandom(){
	float rnd;
	do{
		rnd = (rand() % 1000)+1;
		float w = (rand() % 1000)+1;
		if (rnd > w)
			rnd = w / rnd;
		else
			rnd = rnd/w;
	}while(rnd == 1);
	return rnd;
}

int Hongo::calculoDireccionRandom(){
	float rnd = tirarRandom();

	if (rnd < 0.5)
		return 1;
	else
		return -1;
}

void Hongo::morir(){
	estado = MUERTO;
	huboCambios();
	notificarObservadores();


	float rnd = tirarRandom();
	if (PROB_FABRICAR <= (rnd * 1000)) return;

	Posicion* posCreacion = new Posicion (obtenerArea()->obtenerPosicion()->obtenerX(), obtenerArea()->obtenerPosicion()->obtenerY() + obtenerArea()->obtenerAlto());
	fabrica->fabricar(posCreacion, -2);
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
		saltoMov = false;
		return;
	}

	if (tengoPiso) return;

	if (estado == CAMINANDODER)
		estado = SALTANDODER;
	else if(estado == CAMINANDOIZQ)
		estado = SALTANDOIZQ;
	saltoMov = true;
}


void Hongo::actualizarSalto(){
	if (!(estoySaltando() || saltoMov) && !enViga) return;
	enViga = false;
	trasladar(0,velocidadY,true);
	velocidadY += ACELERACION_HONGO;

	if (obtenerArea()->pasaPiso() || tengoPiso){
		superficieDeColision->ponerEnPiso();
		superficieOcupada->ponerEnPiso();
		velocidadY = 0;
		if (estado == SALTANDODER)
			estado = CAMINANDODER;
		else if(estado == SALTANDOIZQ)
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
	if ((estoySaltando() && !permitoMovEnSalto)|| estaMuerto()) return;

	if (proxDir == DERECHA)
		direccion = DERECHA;
	else if (proxDir ==IZQUIERDA )
		direccion = IZQUIERDA;
	proxDir = 0;

	if (direccion == 0){
		estado = QUIETO;
		return;
	}
	if (direccion == DERECHA){
		if (estado == MOVILDERECHA || estado == MOVILIZQUIERDA)
			estado = MOVILDERECHA;
		else
			estado = CAMINANDODER;
	}
	if (direccion == IZQUIERDA){
		if (estado == MOVILDERECHA || estado == MOVILIZQUIERDA)
			estado = MOVILIZQUIERDA;
		else
			estado = CAMINANDOIZQ;
	}


	int movX = velocidadX * direccion;

	if (((obtenerArea()->obtenerPosicion()->obtenerX() + movX) < 0) || ((obtenerArea()->obtenerPosicion()->obtenerX()+ obtenerArea()->obtenerAncho() + movX) > Posicion::obtenerMaximo()->obtenerX())){
		estado = MUERTO;
		huboCambios();
		return;
	}
	trasladar(movX,0,true);

	if (direccion == DERECHA && estado != MOVILDERECHA && estado != MOVILIZQUIERDA)
		estado = CAMINANDODER;
	else if (direccion == IZQUIERDA && estado != MOVILIZQUIERDA && estado != MOVILDERECHA)
		estado = CAMINANDOIZQ;
}

bool Hongo::estoySaltando(){
	return (estado == SALTANDODER || estado == SALTANDOIZQ);
}

void Hongo::chocarConManual(Manual* pers){
	if (pers->mataAlContacto()) morir();

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

	posCmp = new Posicion(posPersAnterior->obtenerX() + pers->obtenerArea()->obtenerAncho() - pers->obtenerVelocidad(),posPersAnterior->obtenerY() );
	if (posCmp->estaALaIzquierdaDe(posAnterior)){
		modificacionMovimiento(IZQUIERDA);
		//if (estado != CAMINANDODER && estado != CAMINANDOIZQ)
		if (estado == QUIETO)
			trasladar(40,0,false);
		delete (posCmp);
		return;
	}
	delete(posCmp);

	posCmp = new Posicion(posAnterior->obtenerX() + obtenerArea()->obtenerAncho()-pers->obtenerVelocidad(), posAnterior->obtenerY() );

	if (posCmp->estaALaIzquierdaDe(posPersAnterior)){
		modificacionMovimiento(DERECHA);
		//if (estado != CAMINANDODER && estado != CAMINANDOIZQ)
		if (estado == QUIETO)
			trasladar(-40,0,false);
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

	if (p->esVigaPorDerecha() || p->esVigaPorIzquierda()){
		velocidadY = 15;
		enViga = true;
	}

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
		proxDir = DERECHA;
	else
		proxDir = IZQUIERDA;

	huboCambios();
}

bool Hongo::recienMovido(){
	return false;
}

void Hongo::chocarConBolaDeFuego(BolaDeFuego*){
	morir();
}

unsigned int Hongo::obtenerTipo(){
	return TIPO_HONGO;
}
