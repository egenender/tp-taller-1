#include "Manual.h"
#include <stdio.h>
#include "SDL/SDL.h"

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

	delta = 0;
	velocidadY = 0;
	velocidad = vel;
	velocidadSaltoBase = -fuerza;
	estado = QUIETODER;
	puedoSubir = false;
	tengoPiso = false;
	atraviesaBloques = false;
	chocaConEscalera = false;
	chocaConSosten = false;
	vidas = CANT_VIDAS;

	posAnterior = NULL;

	int ancho = sup->obtenerAncho();
	int alto = sup->obtenerAlto();

	int anchoC = (ancho * FACTOR_DE_ESCALA )/100;
	int altoC = (alto * FACTOR_DE_ESCALA) / 100;
	int difAncho = ancho - anchoC;
	int difAlto = alto - altoC;
	Posicion* posC = new Posicion(sup->obtenerPosicion()->obtenerX() + (difAncho/2), sup->obtenerPosicion()->obtenerY() + (difAlto));
	superficieDeColision = new Area(anchoC, altoC, posC);
	superficieOcupada->cambiarPermisos(difAncho/2, difAlto);

	posAnterior = new Posicion(obtenerArea()->obtenerPosicion()->obtenerX(),obtenerArea()->obtenerPosicion()->obtenerY());
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
	mtrasladar(direccion * velocidad, 0,true);
}


void Manual::actualizar(float delta){
	this->delta = delta;
	validarPiso();
	actualizarSalto();
	notificarObservadores();
	actualizarEstados();
}

bool Manual::estoySaltando(){
	return (estado == SALTANDOIZQ || estado == SALTANDODER);
}

// Viejo:
void Manual::detener(){
	if (estoySaltando()) return;
	if (estado == QUIETO || estado == QUIETODER || estado == QUIETOIZQ) return;

	if(estoySubiendo()){
		if (estado == SUBIENDOMOVIMIENTO)
			estado = SUBIENDOQUIETO;
		huboCambios();
		return;
	}

	if (estado == CAMINANDODER)
		estado = QUIETODER;
	if (estado == CAMINANDOIZQ)
		estado = QUIETOIZQ;
	huboCambios();
}


void Manual::actualizarSalto(){
	if (!estoySaltando()) return;

	mtrasladar(0,velocidadY,true);
	velocidadY += ACELERACION;
	if (chocaConPiso() || tengoPiso){
		superficieDeColision->ponerEnPiso();
		superficieOcupada->ponerEnPiso();
//		//Posicion* trs = new Posicion (0, (superficieOcupada->obtenerAlto()-superficieDeColision->obtenerAlto()));
//		superficieOcupada->mover(trs);
//		delete(trs);
		velocidadY = 0;
		if (estado == SALTANDODER) estado = QUIETODER;
		else estado = QUIETOIZQ;
	}
}

bool Manual::chocaConPiso(){
	return obtenerArea()->pasaPiso();
}

void Manual::morir(){
	estado = MUERTO;
	huboCambios();
}
bool Manual::estaMuerto(){
	return (estado == MUERTO);
}

void Manual::validarPiso(){
	if (obtenerArea()->estaSobreElPiso()){
		tengoPiso = true;
		return;
	}

	if (tengoPiso) return;

	if (estado == CAMINANDODER || estado == QUIETODER || estoySubiendo())
		estado = SALTANDODER;
	else if (estado == CAMINANDOIZQ || estado == QUIETOIZQ)
		estado = SALTANDOIZQ;

}

void Manual::subir(){
	if (!puedoSubir) return;

	puedoSubir = false;
	//por ahora digo que la velocidad a la que sube, es la misma a la que se mueve
	mtrasladar(0, -velocidad,true);
	estado = SUBIENDOMOVIMIENTO;
}

void Manual::bajar(){
	if (!puedoSubir) return;
	puedoSubir = false;
	mtrasladar(0,velocidad,true);
	estado = SUBIENDOMOVIMIENTO;
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

		Posicion* cmpIzquierda = new Posicion(posAnterior->obtenerX() + obtenerArea()->obtenerAncho()-velocidad, posAnterior->obtenerY());
		if (cmpIzquierda->estaALaIzquierdaDe(p->obtenerArea()->obtenerPosicion()) && !p->esVigaPorIzquierda()){
			if (!(posCmp->obtenerY() == p->obtenerArea()->obtenerPosicion()->obtenerY())){
				delete(posCmp);
				posCmp = NULL;
				delete(cmpIzquierda);
				int mov = obtenerArea()->obtenerPosicion()->obtenerX() + obtenerArea()->obtenerAncho();
				mov	-= p->obtenerArea()->obtenerPosicion()->obtenerX();
				mtrasladar(-mov-1,0,true);
				return;
			}

		}
		delete(cmpIzquierda);

		Posicion* cmpDer = new Posicion(p->obtenerArea()->obtenerPosicion()->obtenerX() + p->obtenerArea()->obtenerAncho()-velocidad, p->obtenerArea()->obtenerPosicion()->obtenerY());
		if (posAnterior->estaALaDerechaDe(cmpDer) && !p->esVigaPorDerecha()){
			if (!(posCmp->obtenerY() == p->obtenerArea()->obtenerPosicion()->obtenerY())){
				delete(posCmp);
				posCmp = NULL;
				delete (cmpDer);
				int x = p->obtenerArea()->obtenerPosicion()->obtenerX() +p->obtenerArea()->obtenerAncho();
				x -= obtenerArea()->obtenerPosicion()->obtenerX();
				mtrasladar(x+1,0,true);
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
			mtrasladar(0,mov+1,!(p->esVigaPorDerecha() || p->esVigaPorIzquierda()));
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

	mtrasladar(0,-y,cambio);

}
void Manual::chocarConEscalera(Escalera*){
	if (!estoySubiendo()) estado = SUBIENDOQUIETO;
	puedoSubir = true;
	tengoPiso = true;
	atraviesaBloques = true;
	chocaConEscalera = true;
	chocaConSosten = true;
	velocidadY = 0;
}

void Manual::actualizarEstados(){
	if(!chocaConEscalera){
		atraviesaBloques = false;
	}
	chocaConEscalera = false;

	if (!chocaConSosten){
		tengoPiso = false;
	}
	chocaConSosten = false;
}

bool Manual::estoySubiendo(){
	return (estado == SUBIENDOQUIETO || estado == SUBIENDOMOVIMIENTO);
}

void Manual::posicionar(Posicion* pose){
	if(posAnterior) delete(posAnterior);
	posAnterior = new Posicion(obtenerArea()->obtenerPosicion()->obtenerX(),obtenerArea()->obtenerPosicion()->obtenerY());
	moverA(pose);
}

void Manual::mtrasladar(int fx, int fy, bool c){
	trasladar(fx,fy,c);
	puedoSubir = false;
}

void Manual::perderVida(){
	printf("Vidas: %d\n", vidas);
	if (estado == MUERTO) return;
	vidas--;
	if (vidas == 0){
		morir();
		return;
	}

	//aca deberia ponerlo en alguna "posicionInicial"
	huboCambios();
}

void Manual::chocarConBarril(Barril*){
	perderVida();
}
