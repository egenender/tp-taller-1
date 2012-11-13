#include "Barril.h"
#include <time.h>
#include <stdlib.h>
#include "../Posicion.h"
#include "Hongo.h"

Barril::Barril(const char* nom, Area* sup, int vel, int dir):Cuerpo(nom,sup) {
	if (dir <= 1 && dir >= -1)
		direccion = dir;
	else
		direccion = 0;

	if (vel > 0)
		velocidadX = vel;
	else
		velocidadX = VEL_BASE;

	velocidadY = 0;
	estado = QUIETO;
	puedoBajar = tengoPiso = atraviesaBloques = chocaConEscalera = chocaConSosten = false;

	srand ( time(NULL) );
	bajarEnSiguiente = calculoBajada();

	int anchoN, altoN, difAncho, difAlto;
	anchoN = (superficieOcupada->obtenerAncho() * ESCALA)/100;
	altoN = (superficieOcupada->obtenerAlto() * ESCALA)/100;
	difAncho = superficieOcupada->obtenerAncho() - anchoN;
	difAlto = superficieOcupada->obtenerAlto() - altoN;
	int x = superficieOcupada->obtenerPosicion()->obtenerX() + difAncho/2;
	int y = superficieOcupada->obtenerPosicion()->obtenerY() + difAlto;
	superficieDeColision = new Area(anchoN, altoN, new Posicion(x,y));

	posAnterior = new Posicion(x,y);

	esc = NULL;
	plt = NULL;
	permito = false;
	enViga = false;
}

Barril::~Barril() {
	if (posAnterior) delete(posAnterior);
}

int Barril::obtenerEstado(){
	return estado;
}


void Barril::chocarCon(Actualizable* ac){
	ac->chocarConBarril(this);
}

void Barril::chocarConEscalera(Escalera* e){
	puedoBajar = true;
	tengoPiso = true;
	atraviesaBloques = true;
	chocaConEscalera = true;
	chocaConSosten = true;

	//Si cambio la escalera de contacto:
	if (esc != e){
		esc = e;
		plt = NULL;
	}
}

void Barril::chocarConManual(Manual*){
	destruir();
}

void Barril::actualizar(float){
	validarPiso();
	actualizarSalto();
	actualizarMovimiento();
	notificarObservadores();
	actualizarEstados();
}

void Barril::actualizarSalto(){
	if (estado != SALTAR && !enViga) return;
	enViga = false;
	trasladar(0,velocidadY,true); //aca ya se avisa que hubo cambios (a los observadores cuando los notifique)
	puedoBajar = false;

	velocidadY += ACELERACION;
	if (obtenerArea()->pasaPiso() || tengoPiso){
		superficieDeColision->ponerEnPiso();
		superficieOcupada->ponerEnPiso();
		velocidadY = 0;
		estado = QUIETO;
	}
}

void Barril::validarPiso(){
	if (obtenerArea()->estaSobreElPiso()){
		tengoPiso = true;
		permito = false;
		return;
	}

	if (tengoPiso) return;

	estado = SALTAR;
}

void Barril::actualizarEstados(){
	if(!chocaConEscalera){
		atraviesaBloques = false;
		bajarEnSiguiente = calculoBajada();
	}
	chocaConEscalera = false;

	if (!chocaConSosten){
		tengoPiso = false;
	}
	chocaConSosten = false;
}


void Barril::actualizarMovimiento(){
	if (estado == SALTAR || estado == MUERTO) return;
	if (puedoBajar && bajarEnSiguiente && permito){
		bajar();
		return;
	}

	int movX = velocidadX * direccion;

	if (movX != 0){
		if (((obtenerArea()->obtenerPosicion()->obtenerX() + movX) < 0) || ((obtenerArea()->obtenerPosicion()->obtenerX()+ obtenerArea()->obtenerAncho() + movX) > Posicion::obtenerMaximo()->obtenerX())){
				estado = MUERTO;
				huboCambios();
				return;
		}
		trasladar(movX,0,true);
		puedoBajar = false;

	}


	if (direccion == DIR_IZQ){
		estado = CAMINANDOIZQ;
	}
	else if (direccion == DIR_DER){
		estado = CAMINANDOIZQ;
	}else{
		estado = QUIETO;
	}
}

void Barril::destruir(){
	//por ahora solo hago esto:
	estado = MUERTO;
	huboCambios();
	notificarObservadores();
}

bool Barril::calculoBajada(){
	float rnd;
	do{
		rnd =(rand() % 1000) + 1;
		float w;
		do{
			w =(rand() % 1000);
		}while (w >= rnd);
		rnd = w / rnd;
	}while(rnd == 1);

	float cmp = (float)PROBABILIDAD_BAJADA / 100;

	return (rnd < cmp);
}

void Barril::bajar(){
	if (!puedoBajar) return;
	trasladar(0,velocidadX,true);
	puedoBajar = false;
	estado = SUBIENDOMOVIMIENTO;
}

void Barril::chocarConPlataforma(Plataforma* p){
	if (plt == NULL) plt = p;

	if(atraviesaBloques && plt == p){
		permito = true;
		return;
	}else{
		permito = false;
	}

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
				puedoBajar = false;
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
				puedoBajar = false;
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
			puedoBajar = false;
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
	if(p->caeADerecha()){
		direccion = 1;
		enViga = true;
	}else if(p->caeAIzquierda()){
		direccion = -1;
		enViga = true;
	}
	if(enViga)
		velocidadY = 15;

	int y;
	y = obtenerArea()->obtenerPosicion()->obtenerY() + obtenerArea()->obtenerAlto();
	y -= p->obtenerArea()->obtenerPosicion()->obtenerY();

	trasladar(0,-y,cambio);
	puedoBajar = false;
}

void Barril::chocarConBarril(Barril*){
	//No se muy bien que deberia hacerse.. supongo que morir
	destruir();
}

bool Barril::estaMuerto(){
	return (estado == MUERTO);
}

void Barril::chocarConBolaDeFuego(BolaDeFuego*){
	destruir();
}

void Barril::chocarConHongo(Hongo* h){
	if (h->obtenerEstado() == MOVILDERECHA || h->obtenerEstado() == MOVILIZQUIERDA)
		destruir();
}
