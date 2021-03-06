#include "Manual.h"
#include "Hongo.h"
#include "CamaElastica.h"
#include "../Tipos.h"

bool Manual::cooperativo = true;

Manual::~Manual() {
	delete(superficieReemplazo);
	delete(timeout);
}

void Manual::saltar(bool autogenerado){
	if (estaMuerto()) return;
	int y = obtenerArea()->obtenerPosicion()->obtenerY() + obtenerArea()->obtenerAlto();
	if (estado == QUIETODER || estado == CAMINANDODER || (puedoSubir && (y <= YTecho || enViga))){
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

bool Manual::saltaAlto(){
	return saltoAlto;
}

void Manual::atacar(){} //idem

void Manual::especial(){
	if (estaMuerto()) return;
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


	vel = vel * 100 + id;

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
	invencible = false;
	vidas = CANT_VIDAS;
	x_inicial = 0;
	YEscalera = 0;
	
	posAnterior = NULL;
	evolucionado = 0;
	fabrica = new FabricaBolasDeFuego(nombrecito);
	chocaConCama = saltoAlto = false;

	pisareViga = false;

	int ancho = sup->obtenerAncho();
	int alto = sup->obtenerAlto();

	int anchoC = (ancho * (FACTOR_DE_ESCALA - 20) )/100;
	int altoC = (alto * FACTOR_DE_ESCALA) / 100;
	int difAncho = ancho - anchoC;
	int difAlto = alto - altoC;
	Posicion* posC = new Posicion(sup->obtenerPosicion()->obtenerX() + (difAncho/2), sup->obtenerPosicion()->obtenerY() + (difAlto));
	superficieDeColision = new Area(anchoC, altoC, posC);
	superficieOcupada->cambiarPermisos(difAncho/2, difAlto);

	posAnterior = new Posicion(obtenerArea()->obtenerPosicion()->obtenerX(),obtenerArea()->obtenerPosicion()->obtenerY());

	int anchoE = (ancho * (FACTOR_EVOLUCION - 20) )/100;
	int altoE = (alto * FACTOR_EVOLUCION) / 100;
	difAncho = ancho - anchoE;
	difAlto = alto - altoE;
	Posicion* posE = new Posicion(sup->obtenerPosicion()->obtenerX() + (difAncho/2), sup->obtenerPosicion()->obtenerY() + (difAlto));
	superficieReemplazo = new Area(anchoE, altoE, posE);
	//superficieOcupada->cambiarPermisos(difAncho/2, difAlto);
	supActual = SUPERFICIE_INVOLUCION;

	timeout = new Timer();
	
	
	//NEW:
	reposicionar = false; // Cuando pierde una vida, hay que moverlo.
	bloquearMovimiento = false; // Hace que no responda a las teclas.
}

void Manual::moverALaDerecha(){
	movimiento(SALTANDODER, CAMINANDODER, DERECHA);
}

void Manual::moverALaIzquierda(){
	movimiento(SALTANDOIZQ, CAMINANDOIZQ, IZQUIERDA);
}

void Manual::movimiento(int saltando, int caminando, int direccion){
	if (estaMuerto()) return;
	if (estoySaltando())
		estado = saltando;
	else
		estado = caminando;
	mtrasladar(direccion * velocidad, 0,true);
}


void Manual::actualizar(float delta){
	if (estaMuerto()) return;
	this->delta = delta;
	actualizarTimeOut();
	actualizarEvolucion();
	validarPiso();
	actualizarSalto();
	notificarObservadores();
	actualizarEstados();
	if(pisareViga){
		enViga = true;
		pisareViga = false;
	}
}

bool Manual::estoySaltando(){
	return (estado == SALTANDOIZQ || estado == SALTANDODER);
}

// Viejo:
void Manual::detener(){
	if (estaMuerto()) return;
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
	notificarObservadores();
}
bool Manual::estaMuerto(){
	return (estado == MUERTO);
}

void Manual::validarPiso(){
	if (obtenerArea()->estaSobreElPiso()){
		if (!estoySaltando())
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
	if (estaMuerto()) return;
	if (!puedoSubir) return;
	puedoSubir = false;
	//por ahora digo que la velocidad a la que sube, es la misma a la que se mueve
	mtrasladar(0, -velocidad,true);
	estado = SUBIENDOMOVIMIENTO;
}

void Manual::bajar(){
	if (estaMuerto()) return;
	if (!puedoSubir) return;
	if (obtenerArea()->estaSobreElPiso()) return;
	int posBaja = obtenerArea()->obtenerPosicion()->obtenerY() + obtenerArea()->obtenerAlto();
	if (posBaja >= YEscalera) return;
	int movY = velocidad;
	if (posBaja + velocidad >= YEscalera) {
		movY = velocidad - (YEscalera - posBaja);
	}
	puedoSubir = false;
	mtrasladar(0,movY,true);
	estado = SUBIENDOMOVIMIENTO;
}


void Manual::chocarCon(Actualizable* ac){
	if (estaMuerto()) return;
	ac->chocarConManual(this);
}
void Manual::chocarConManual(Manual* manual){

	if (cooperativo) return;
	if (estaMuerto()) return;
	if (manual->mataAlContacto() && !this->estaInvencible()){
		perderVida();
		return;
	}
	return;

	Posicion* posCmp = new Posicion (manual->obtenerPosicionAnterior()->obtenerX(), manual->obtenerPosicionAnterior()->obtenerY() + manual->obtenerArea()->obtenerAlto());
	if (posCmp->estaArribaDe(posAnterior))
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
		//enViga = true;
		pisareViga = true;
	}

	int y;
	y = obtenerArea()->obtenerPosicion()->obtenerY() + obtenerArea()->obtenerAlto();
	y -= p->obtenerArea()->obtenerPosicion()->obtenerY();

	mtrasladar(0,-y,false);

}
void Manual::chocarConEscalera(Escalera* esc){
	if (!estoySubiendo()) estado = SUBIENDOQUIETO;
	puedoSubir = true;
	tengoPiso = true;
	chocaConEscalera = true;
	chocaConSosten = true;
	velocidadY = 0;
	atraviesaBloques = true;

	Cuerpo* e = (Cuerpo*)esc;

	YEscalera = e->obtenerArea()->obtenerPosicion()->obtenerY() + e->obtenerArea()->obtenerAlto();
	YTecho = e->obtenerArea()->obtenerPosicion()->obtenerY();
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
		return;
	}
	if (estado == MUERTO) return;
	especialHabilitado = false;
	vidas--;
	if (vidas == 0){
		morir();
		return;
	}

	//aca deberia ponerlo en alguna "posicionInicial"
	
	// NEW:
	reposicionar = true; // Lo marco para que luego sea reposicionado
	estado = HERIDO; // Lo seteo en el estado HERIDO, asi la vista pone su animacion
	bloquearMovimiento = true; // Evito que se mueva durante el estado HERIDO

	// OLD:
	//Posicion* pos = new Posicion (x_inicial, Posicion::obtenerPiso() - obtenerArea()->obtenerAlto());
	//posicionar(pos);

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
	if(posPersAnterior->estaAbajoDe(posCmp) && !enViga){
		tengoPiso = true;
		estado = QUIETODER;
		saltar();
	}else{
		int state = h->obtenerEstado();
		if (state == QUIETO){
			delete(posCmp);
			return;
		}

		if (state == MOVILDERECHA && posAnterior->estaALaDerechaOIgualDe(posPersAnterior)){
			perderVida();
			return;
		}

		else if (state == MOVILIZQUIERDA && posAnterior->estaALaIzquierdaOIgualDe(posPersAnterior)){
			perderVida();
			return;
		}

		else if (state != MOVILIZQUIERDA && state != MOVILDERECHA && state != QUIETO){
			perderVida();
			return;
		}
	}
	if (enViga) perderVida();
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
	if (estaInvencible()) return;
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
	huboCambios();
}

void Manual::habilitarEspecial(){
	especialHabilitado = true;
}

void Manual::actualizarTimeOut(){
	if (!timeout->estaEmpezado()) return;
	int tiempo = TIEMPO_TIMEOUT;
	if (invencible)
		tiempo = TIEMPO_INVENCIBLE;

	// NEW:

	// Si paso la mitad del tiempo de espera, y tenia que reposicionarlo:
	if (timeout->obtenerTiempo() >= (tiempo * 500) && reposicionar) {
		// Lo cambiamos de posicion:
		Posicion* pos = new Posicion (x_inicial, Posicion::obtenerPiso() - obtenerArea()->obtenerAlto());
		posicionar(pos);
		// Ya no hay que moverlo:
		reposicionar = false;
		// Recobra el movimiento:
		bloquearMovimiento = false;
		// Queda en un estado por defecto:
		estado = QUIETODER;
	}

	// (end del NEW)

	// Este es el caso de invensible, cuando se termino el tiempo deja de serlo:
	else if (timeout->obtenerTiempo() >= (tiempo * 1000)){
		timeout->detener();
		invencible = false;
	}
	huboCambios();
}

// Devuelve si el manual esta aceptando movimiento por teclas:
bool Manual::puedeMover() {
	return !bloquearMovimiento;
}

bool Manual::estaInvencible(){
	return timeout->estaEmpezado();
}

void Manual::setearCooperatividad(bool c){
	cooperativo = c;
}

void Manual::hacerInvencible(){
	timeout->detener();
	timeout->comenzar();
	invencible = true;
}

bool Manual::mataAlContacto(){
	return invencible;
}

bool Manual::esEliminable(){
	return false;
}

int Manual::obtenerVelocidad(){
	return velocidad;
}

unsigned int Manual::obtenerTipo(){
	return TIPO_MANUAL;
}

bool Manual::esCooperativo(){
	return cooperativo;
}
