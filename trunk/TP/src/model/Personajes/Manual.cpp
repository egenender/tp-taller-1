#include "Manual.h"
#include "Hongo.h"
#include "CamaElastica.h"

bool Manual::cooperativo = true;

Manual::~Manual() {
	//Por ahora,  lo que se tiene se elimina en el destructor del padre.
	delete(superficieReemplazo);
	delete(timeout);
}

void Manual::saltar(bool autogenerado){
	if (estado == QUIETODER || estado == CAMINANDODER){
		estado = SALTANDODER;
		velocidadY = velocidadSaltoBase;
		if (saltoAlto && !autogenerado) velocidadY *= 2;
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

void Manual::especial(){
	if (!especialHabilitado) return;

	int direccion = 0;
	if (estado == CAMINANDODER || estado == SALTANDODER || estado == QUIETODER)
		direccion = DERECHA;
	else if (estado == CAMINANDOIZQ || estado == SALTANDOIZQ || estado == QUIETOIZQ)
		direccion = IZQUIERDA;

	if (direccion == 0) return;
	int vel = velocidad + 1;

	int x,y;
	x = obtenerArea()->obtenerPosicion()->obtenerX();
	y = obtenerArea()->obtenerPosicion()->obtenerY() + obtenerArea()->obtenerAlto() / 2;

	int dif = obtenerArea()->obtenerAncho() + 1;
	if (direccion == DERECHA)
		x += dif;
	else
		x -= 1;

	Posicion* pos = new Posicion(x,y);
	fabrica->fabricar(pos,(vel*direccion));
	delete(pos);
}

int Manual::obtenerEstado(){
	return (estado + evolucionado);
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
	juegoGanado = false;
	enViga = false;
	especialHabilitado = false;
	vidas = CANT_VIDAS;
	x_inicial = 0;

	posAnterior = NULL;
	evolucionado = 0;
	fabrica = new FabricaBolasDeFuego(nombrecito);
	chocaConCama = saltoAlto = false;

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

	int anchoE = (ancho * FACTOR_EVOLUCION )/100;
	int altoE = (alto * FACTOR_EVOLUCION) / 100;
	difAncho = ancho - anchoE;
	difAlto = alto - altoE;
	Posicion* posE = new Posicion(sup->obtenerPosicion()->obtenerX() + (difAncho/2), sup->obtenerPosicion()->obtenerY() + (difAlto));
	superficieReemplazo = new Area(anchoE, altoE, posE);
	//superficieOcupada->cambiarPermisos(difAncho/2, difAlto);
	supActual = SUPERFICIE_INVOLUCION;

	timeout = new Timer();
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
	actualizarTimeOut();
	actualizarEvolucion();
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
	if (!estoySaltando() && !enViga) return;
	enViga = false;
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
		else if (estado == SALTANDOIZQ)estado = QUIETOIZQ;
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
	if (obtenerArea()->estaSobreElPiso()) return;
	puedoSubir = false;
	mtrasladar(0,velocidad,true);
	estado = SUBIENDOMOVIMIENTO;
}


void Manual::chocarCon(Actualizable* ac){
	ac->chocarConManual(this);
}
void Manual::chocarConManual(Manual* manual){
	if (cooperativo) return;

	Posicion* posCmp = new Posicion (manual->obtenerArea()->obtenerPosicion()->obtenerX(),manual->obtenerArea()->obtenerPosicion()->obtenerY() + manual->obtenerArea()->obtenerAlto());

	if (posCmp->estaArribaOIgualDe(posAnterior))
		perderVida();

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
				mtrasladar(-mov-1,0,false);
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
				mtrasladar(x+1,0,false);
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

//	bool cambio = true;
//	if(posCmp)
//		delete(posCmp);
//	else
//		cambio = false;

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

	mtrasladar(0,-y,false);

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

void Manual::chocarConCamaElastica(CamaElastica* ce){

	//tengo que ver por cual direccion se chocan:
	Posicion* posPersAnterior = ce->obtenerArea()->obtenerPosicion();
		//me fijo nomas si vino de arriba:
	Posicion* posCmp = new Posicion(posAnterior->obtenerX(), posAnterior->obtenerY() + obtenerArea()->obtenerAlto());
	if(posPersAnterior->estaAbajoDe(posCmp)){
		tengoPiso = true;
		chocaConSosten = true;
		estado = QUIETODER;
		if (saltoAlto){
			saltar(true);
		}
		saltoAlto = true;
		chocaConCama = true;
	}
	delete(posCmp);
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

	if(!chocaConCama)
		saltoAlto = false;
	chocaConCama = false;
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
	timeout->comenzar();
	if (evolucionado == EVOLUCION){
		evolucionado = 0;
		//habria que poner el timeOut
		return;
	}
	if (estado == MUERTO) return;
	vidas--;
	if (vidas == 0){
		morir();
		return;
	}

	//aca deberia ponerlo en alguna "posicionInicial"
	Posicion* pos = new Posicion (x_inicial, Posicion::obtenerPiso() - obtenerArea()->obtenerAlto());
	posicionar(pos);
	huboCambios();
}

void Manual::chocarConBarril(Barril*){
	if (timeout->estaEmpezado()) return;
	perderVida();
}

void Manual::chocarConHongo(Hongo* h){
	if (timeout->estaEmpezado()) return;

	//tengo que ver por cual direccion se chocan:
	Posicion* posPersAnterior = h->obtenerPosicionAnterior();
	//me fijo nomas si vino de arriba:
	Posicion* posCmp = new Posicion(posAnterior->obtenerX(), posAnterior->obtenerY() + obtenerArea()->obtenerAlto());
	if(posPersAnterior->estaAbajoDe(posCmp)){
		tengoPiso = true;
		estado = QUIETODER;
		saltar();
	}else{
		if (!(h->obtenerEstado() == QUIETO || h->recienMovido()))
			perderVida();

	}
	delete(posCmp);
}

bool Manual::esGanador(){
	return juegoGanado;
}

void Manual::chocarConPrincesa(Princesa*){
	juegoGanado = true;
}

void Manual::chocarConBolaDeFuego(BolaDeFuego*){
	if(cooperativo) return;

	perderVida();
}

void Manual::setearXInicial(int x){
	if (x >= 0 && x <= Posicion::obtenerMaximo()->obtenerX())
		x_inicial = x;
}

int Manual::obtenerVidas(){
	return vidas;
}

void Manual::evolucionar(){
	evolucionado = EVOLUCION;
}

void Manual::actualizarEvolucion(){
	if (supActual == SUPERFICIE_EVOLUCION && evolucionado == EVOLUCION) return;
	if (supActual == SUPERFICIE_INVOLUCION && evolucionado == 0) return;

	Area* aux = superficieDeColision;
	superficieDeColision = superficieReemplazo;
	superficieReemplazo = aux;

	int anchoC = superficieDeColision->obtenerAncho();
	int altoC = superficieDeColision->obtenerAlto();
	int difAncho = superficieOcupada->obtenerAncho() - anchoC;
	int difAlto = superficieOcupada->obtenerAlto() - altoC;

	Posicion* posC = new Posicion(superficieOcupada->obtenerPosicion()->obtenerX() + (difAncho/2), superficieOcupada->obtenerPosicion()->obtenerY() + (difAlto));
	superficieDeColision->cambiarPosicion(posC);
	superficieOcupada->cambiarPermisos(difAncho/2, difAlto);

	if (evolucionado == EVOLUCION)
		supActual = SUPERFICIE_EVOLUCION;
	else
		supActual = SUPERFICIE_INVOLUCION;
	huboCambios();
}

void Manual::aumentarVida(){
	vidas++;
}

void Manual::habilitarEspecial(){
	especialHabilitado = true;
}

void Manual::actualizarTimeOut(){
	if (timeout->obtenerTiempo() >= (TIEMPO_TIMEOUT * 1000))
		timeout->detener();
	else
		huboCambios();
}

bool Manual::estaInvencible(){
	return timeout->estaEmpezado();
}

void Manual::setearCooperatividad(bool c){
	cooperativo = c;
}