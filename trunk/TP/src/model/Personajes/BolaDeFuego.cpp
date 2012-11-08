#include "BolaDeFuego.h"
#include "../Observable.h"
#include "Plataforma.h"

BolaDeFuego::BolaDeFuego(const char* nom, Area* sup, int velX, int velY, int dir) : Cuerpo(nom,sup){
	direccion = dir;
	tengoPiso = chocaConSosten = false;

	velocidadX = velX;
	if (velocidadX <= 0)
		velocidadX = VELOCIDAD_BOLA_STD;

	velocidadSaltoBase = velY;
	if (velocidadSaltoBase <= 0)
		velocidadSaltoBase = VELOCIDAD_BOLA_STD;

	velocidadY = 0;
	if (direccion == DERECHA_BF)
		estado = CAMINANDODER;
	else
		estado = CAMINANDOIZQ;

	int anchoC = (superficieOcupada->obtenerAncho() * FACTOR_BOLA_FUEGO )/100;
	int altoC = (superficieOcupada->obtenerAlto() * FACTOR_BOLA_FUEGO) / 100;
	int difAncho = superficieOcupada->obtenerAncho() - anchoC;
	int difAlto = superficieOcupada->obtenerAlto() - altoC;
	Posicion* posC = new Posicion(sup->obtenerPosicion()->obtenerX() + (difAncho/2), sup->obtenerPosicion()->obtenerY() + (difAlto));
	superficieDeColision = new Area(anchoC, altoC, posC);
	//superficieOcupada->cambiarPermisos(difAncho/2, difAlto);
	posAnterior = new Posicion(obtenerArea()->obtenerPosicion()->obtenerX(),obtenerArea()->obtenerPosicion()->obtenerY());
}

BolaDeFuego::~BolaDeFuego() {

}

int BolaDeFuego::obtenerEstado(){
	return estado;
}

void BolaDeFuego::chocarCon(Actualizable* ac){
	ac->chocarConBolaDeFuego(this);
}

void BolaDeFuego::chocarConManual(Manual*){
	//por ahora no hago nada
}



void BolaDeFuego::chocarConHongo(Hongo*){
	morir();
}

void BolaDeFuego::chocarConBarril(Barril*){
	morir();
}

bool BolaDeFuego::estaMuerto(){
	return (estado == MUERTO);
}

void BolaDeFuego::chocarConPlataforma(Plataforma* p){
	Posicion* posCmp = new Posicion(posAnterior->obtenerX(),posAnterior->obtenerY() + obtenerArea()->obtenerAlto());

	if (!posCmp->estaArribaDe(p->obtenerArea()->obtenerPosicion())){

		Posicion* cmpIzquierda = new Posicion(posAnterior->obtenerX() + obtenerArea()->obtenerAncho()-velocidadX, posAnterior->obtenerY());
		if (cmpIzquierda->estaALaIzquierdaDe(p->obtenerArea()->obtenerPosicion()) && !p->esVigaPorIzquierda()){
			if (!(posCmp->obtenerY() == p->obtenerArea()->obtenerPosicion()->obtenerY())){
				delete(posCmp);
				posCmp = NULL;
				delete(cmpIzquierda);
//				int mov = obtenerArea()->obtenerPosicion()->obtenerX() + obtenerArea()->obtenerAncho();
//				mov	-= p->obtenerArea()->obtenerPosicion()->obtenerX();
//				trasladar(-mov-1,0,true);
//				direccion = IZQUIERDA_BF;
				morir();
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
//				int x = p->obtenerArea()->obtenerPosicion()->obtenerX() +p->obtenerArea()->obtenerAncho();
//				x -= obtenerArea()->obtenerPosicion()->obtenerX();
//				trasladar(x+1,0,true);
//				direccion = DERECHA_BF;
				morir();
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

void BolaDeFuego::actualizar(float){
	validarPiso();
	actualizarSalto();
	actualizarMovimiento();
	notificarObservadores();
	actualizarEstados();
}

void BolaDeFuego::actualizarEstados(){
	if (!chocaConSosten){
		tengoPiso = false;
	}
	chocaConSosten = false;
}

void BolaDeFuego::validarPiso(){
	if (obtenerArea()->estaSobreElPiso()){
		tengoPiso = true;
		return;
	}

	if (tengoPiso) return;

	if (estado == CAMINANDODER)
		estado = SALTANDODER;
	else if(estado == CAMINANDOIZQ)
		estado = SALTANDOIZQ;
	huboCambios();
}


void BolaDeFuego::actualizarSalto(){
	if (!estoySaltando()) return;

	trasladar(0,velocidadY,true);
	velocidadY += ACELERACION_BF;

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

void BolaDeFuego::morir(){
	estado = MUERTO;
	huboCambios();
	notificarObservadores();
}

bool BolaDeFuego::estoySaltando(){
	return (estado == SALTANDODER || estado == SALTANDOIZQ);
}

void BolaDeFuego::actualizarMovimiento(){
	int movX = velocidadX * direccion;

	if (((obtenerArea()->obtenerPosicion()->obtenerX() + movX) < 0) || ((obtenerArea()->obtenerPosicion()->obtenerX()+ obtenerArea()->obtenerAncho() + movX) > Posicion::obtenerMaximo()->obtenerX())){
		estado = MUERTO;
		huboCambios();
		return;
	}
	trasladar(movX,0,true);
	saltar();
//
//	if (direccion == DERECHA_BF && !estoySaltando())
//		estado = CAMINANDODER;
//	else if (direccion == IZQUIERDA_BF && !estoySaltando())
//		estado = CAMINANDOIZQ;
}

void BolaDeFuego::saltar(){
	if (estado == CAMINANDODER){
		estado = SALTANDODER;
		velocidadY = velocidadSaltoBase;
		tengoPiso = false;
		return;
	}

	if(estado == CAMINANDOIZQ){
		estado = SALTANDOIZQ;
		velocidadY = velocidadSaltoBase;
		tengoPiso = false;
		return;
	}
}
