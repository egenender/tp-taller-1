#include "VistaAutomatico.h"

/*VistaAutomatico::VistaAutomatico(Observable* automatic, vector<Animacion*>* anim, vector<int>* period) {
	periodos = period;
	animacionActual = anim->at(0);
	actual = 0;

	vector<Animacion*>::iterator iter;
	for (unsigned int i = 0; i < anim->size(); i++) {
		anim->at(i)->transparencia(255,0,255);
		animaciones->insert(pair<int, Animacion*>(i, anim->at(i)));
	}

	terminoAhora = true;
	timer = new Timer();
	posicionDibujar = automatic->obtenerPosicion();
//	actualizar(automatic);
}*/

VistaAutomatico::VistaAutomatico(Observable* automatic, Animacion* inmovil, vector<Animacion*>* anim, vector<int>* period) {
	periodos = period;
	inmovil->transparencia(255,0,255);
	animacionActual = inmovil;
	animacionQuieto = inmovil;
	quieto = true;
	actual = 0;

	vector<Animacion*>::iterator iter;
	for (unsigned int i = 0; i < anim->size(); i++) {
		anim->at(i)->transparencia(255,0,255);
		animaciones->insert(pair<int, Animacion*>(i, anim->at(i)));
	}

	terminoAhora = false;
	timer = new Timer();
	timer->comenzar();
	posicionDibujar = automatic->obtenerPosicion();
//	actualizar(automatic);
}



VistaAutomatico::~VistaAutomatico() {
	delete(timer);
	delete (periodos);
	delete (animacionQuieto);
}

/*void VistaAutomatico::actualizar(Observable* observable) {
	posicionDibujar = observable->obtenerPosicion();

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

	if (timer->obtenerTiempo() >= (periodos->at(actual) * 1000)){
		cambiarAnimacion();
		timer->detener();
	}

}*/

void VistaAutomatico::actualizar(Observable* observable) {
	posicionDibujar = observable->obtenerPosicion();

	//Si la animacion actual todavia no termino, entonces tengo que seguir
	//con esta. No cambio nada.
	if (!animacionActual->termino() && !quieto) return;

	//si Recien termino, tengo que reiniciar el timer
	if (terminoAhora){
		terminoAhora = false;
		quieto = true;
		animacionActual->detener();
		animacionActual = animacionQuieto;
		timer->comenzar();
	}

	//Si el timer terminó de contar, tengo que cambiar la animacion

	if (timer->obtenerTiempo() >= (periodos->at(actual) * 1000)){
		cambiarAnimacion();
		timer->detener();
	}

}

void VistaAutomatico::cambiarAnimacion(){
	actual++;
	if (actual == periodos->size()) actual = 0;

	animacionActual = animaciones->at(actual);
	animacionActual->resetear();
	terminoAhora = true;
	quieto = false;
}
