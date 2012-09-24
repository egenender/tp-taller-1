#include "VistaAutomatico.h"

VistaAutomatico::VistaAutomatico(Automatico* automatic, Animacion* activa, Animacion* pasiva, int period) {

//	pasiva->escala(automatic->obtenerAncho(), automatic->obtenerAlto());
//	activa->escala(automatic->obtenerAncho(), automatic->obtenerAlto());
	pasiva->transparencia(255,0,255);
	activa->transparencia(255,0,255);

	animaciones->insert(pair<int, Animacion*>(INMOVIL, pasiva));
	animaciones->insert(pair<int, Animacion*>(MOVIENDO, activa));

	animacionActual = pasiva;
	actual = INMOVIL;
	terminoAhora = true;
	periodo = period;
	timer = new Timer();
	timer->comenzar();
//	actualizar(automatic);
}

VistaAutomatico::~VistaAutomatico() {
	delete(timer);
}

/*void VistaAutomatico::actualizar(Observable* observable) {
	Automatico* automatic = (Automatico*) observable;

	posicionDibujar = automatic->obtenerPosicion();

	//Si la animacion actual todavia no termino, entonces tengo que seguir
	//con esta. No cambio nada.
	if (!animacionActual->termino()) return;

	//si Recien termino, tengo que reiniciar el timer
	if (terminoAhora){
		terminoAhora = false;
		animacionActual->detener();
		timer->comenzar();
	}

	//Si el timer terminó de contar, tengo que cambiar la animacion

	if (timer->obtenerTiempo() >= (periodo * 1000)){
		cambiarAnimacion();
		timer->detener();
	}

}*/

void VistaAutomatico::actualizar(Observable* observable) {
	Automatico* automatic = (Automatico*) observable;
	posicionDibujar = automatic->obtenerPosicion();

	//si estoy corriendo, me fijo si termino de correr:
	if (actual == MOVIENDO && animacionActual->termino()){
		cambiarAnimacion();
		timer->comenzar();
		return;
	}

	//Si simplemente esta corriendo, y no termino de correr, vuelvo
	if (actual == MOVIENDO) return;

	//Ya se que no esta corriendo, asi que me fijo si deberia

	if (timer->obtenerTiempo() >= (periodo * 1000)){
			cambiarAnimacion();
			timer->detener();
	}

}

void VistaAutomatico::cambiarAnimacion(){
	if (actual == INMOVIL)
		actual = MOVIENDO;
	else
		actual = INMOVIL;

	animacionActual = animaciones->at(actual);
	animacionActual->resetear();
	terminoAhora = true;

}
