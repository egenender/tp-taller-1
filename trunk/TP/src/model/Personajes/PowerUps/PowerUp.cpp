#include "PowerUp.h"
#include <time.h>
#include <stdlib.h>

PowerUp::PowerUp(const char* nom, Area* sup, int vel): Cuerpo(nom, sup) {
	velocidadX = vel;
	if(velocidadX <= 0)
		velocidadX = VELOCIDAD_PWRUP_STD;
	velocidadY = 0;
	direccion = calculoDireccionRandom();
	if (direccion == DERECHA)
		estado = CAMINANDODER;
	else
		estado = CAMINANDOIZQ;
	tengoPiso = chocaConSosten = false;

	puedoMovermeEnElAire = false;

	int anchoH, altoH, x, y;
	anchoH = (superficieOcupada->obtenerAncho() * FACTOR_PWRUP) / 100;
	altoH = (superficieOcupada->obtenerAlto() * FACTOR_PWRUP) / 100;
	x = superficieOcupada->obtenerPosicion()->obtenerX() + (superficieOcupada->obtenerAncho() - anchoH)/2;
	y = superficieOcupada->obtenerPosicion()->obtenerY() + (superficieOcupada->obtenerAlto() - altoH);

	superficieDeColision = new Area(anchoH, altoH, new Posicion(x,y));

}

PowerUp::~PowerUp() {

}

void PowerUp::chocarCon(Actualizable*){}

void PowerUp::chocarConPlataforma(Plataforma* p){
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

	if (p->esVigaPorDerecha())
		direccion = DERECHA;
	else if(p->esVigaPorIzquierda())
		direccion = IZQUIERDA;

	tengoPiso = true;
	chocaConSosten = true;
	velocidadY = 0;

	int y;
	y = obtenerArea()->obtenerPosicion()->obtenerY() + obtenerArea()->obtenerAlto();
	y -= p->obtenerArea()->obtenerPosicion()->obtenerY();

	trasladar(0,-y,cambio);

}

void PowerUp::actualizar(float){
	validarPiso();
	actualizarSalto();
	actualizarMovimiento();
	notificarObservadores();
	actualizarEstados();
}

void PowerUp::validarPiso(){
	if (obtenerArea()->estaSobreElPiso()){
		tengoPiso = true;
	}
}

void PowerUp::actualizarSalto(){
	if (tengoPiso) return;

	trasladar(0,velocidadY,true);
	velocidadY += ACELERACION_PWRUP;

	if (obtenerArea()->pasaPiso() || tengoPiso){
		superficieDeColision->ponerEnPiso();
		superficieOcupada->ponerEnPiso();
		velocidadY = 0;
	}

}

void PowerUp::actualizarEstados(){
	if (!chocaConSosten){
		tengoPiso = false;
	}
	chocaConSosten = false;
}

void PowerUp::actualizarMovimiento(){
	if ((!tengoPiso && !puedoMovermeEnElAire)|| estaMuerto()) return;

	int movX = velocidadX * direccion;

	if (((obtenerArea()->obtenerPosicion()->obtenerX() + movX) < 0) || ((obtenerArea()->obtenerPosicion()->obtenerX()+ obtenerArea()->obtenerAncho() + movX) > Posicion::obtenerMaximo()->obtenerX())){
		estado = MUERTO;
		huboCambios();
		return;
	}
	trasladar(movX,0,true);

	if (direccion == DERECHA)
		estado = CAMINANDODER;
	else if (direccion == IZQUIERDA)
		estado = CAMINANDOIZQ;
}

int PowerUp::calculoDireccionRandom(){
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

bool PowerUp::estaMuerto(){
	return (estado == MUERTO);
}

int PowerUp::obtenerEstado(){
	return estado;
}
