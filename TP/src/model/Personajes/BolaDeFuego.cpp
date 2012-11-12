#include "BolaDeFuego.h"
#include "../Observable.h"
#include "Plataforma.h"

bool BolaDeFuego::cooperativo = true;

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
		estado = SALTANDODER;
	else
		estado = SALTANDOIZQ;

	int anchoC = (superficieOcupada->obtenerAncho() * FACTOR_BOLA_FUEGO )/100;
	int altoC = (superficieOcupada->obtenerAlto() * FACTOR_BOLA_FUEGO) / 100;
	int difAncho = superficieOcupada->obtenerAncho() - anchoC;
	int difAlto = superficieOcupada->obtenerAlto() - altoC;
	Posicion* posC = new Posicion(sup->obtenerPosicion()->obtenerX() + (difAncho/2), sup->obtenerPosicion()->obtenerY() + (difAlto/2));
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
	if (!cooperativo)
		morir();
}

void BolaDeFuego::chocarConBolaDeFuego(BolaDeFuego*){
	if (cooperativo)
		morir();
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
		delete(posCmp);
		posCmp = NULL;
		morir();
		return;
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
	if (posAnterior) delete(posAnterior);
	posAnterior = new Posicion(obtenerArea()->obtenerPosicion()->obtenerX(),obtenerArea()->obtenerPosicion()->obtenerY());
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
	if (obtenerArea()->estaSobreElPiso() || tengoPiso){
		tengoPiso = true;
		saltar();
		huboCambios();
	}
}


void BolaDeFuego::actualizarSalto(){
	trasladar(0,velocidadY,false);
	velocidadY += ACELERACION_BF;

	if (obtenerArea()->pasaPiso() || tengoPiso){
		superficieDeColision->ponerEnPiso();
		superficieOcupada->ponerEnPiso();
		velocidadY = 0;
	}

}

void BolaDeFuego::morir(){
	estado = MUERTO;
	huboCambios();
	notificarObservadores();
}

void BolaDeFuego::actualizarMovimiento(){
	int movX = velocidadX * direccion;

	if (((obtenerArea()->obtenerPosicion()->obtenerX() + movX) < 0) || ((obtenerArea()->obtenerPosicion()->obtenerX()+ obtenerArea()->obtenerAncho() + movX) > Posicion::obtenerMaximo()->obtenerX())){
		estado = MUERTO;
		huboCambios();
		return;
	}
	trasladar(movX,0,false);
	//saltar();
//
//	if (direccion == DERECHA_BF && !estoySaltando())
//		estado = CAMINANDODER;
//	else if (direccion == IZQUIERDA_BF && !estoySaltando())
//		estado = CAMINANDOIZQ;
}

void BolaDeFuego::saltar(){
	if(!tengoPiso) return;
	velocidadY = -velocidadSaltoBase;
	tengoPiso = false;
}

void BolaDeFuego::setearCooperatividad(bool c){
	cooperativo = c;
}
