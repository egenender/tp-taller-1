#include "VistaAutomatico.h"
#include <iostream>
using namespace std;

VistaAutomatico::VistaAutomatico(Observable* automatic, Animacion* inmovil, vector<Animacion*>* anim, vector<int>* period) {
	periodos = period;
	inmovil->transparencia(255,0,255);
	animacionActual = anim->at(0);
	animacionQuieto = inmovil;
	quieto = false;
	actual = 0;

	map<int, Animacion*>::iterator iter;
	for (unsigned int i = 0; i < anim->size(); i++) {
		anim->at(i)->transparencia(255,0,255);
		animaciones->insert(pair<int, Animacion*>(i, anim->at(i)));
	}

	terminoAhora = false;
	timer = new Timer();

	posicionDibujar = automatic->obtenerPosicion();
	//	actualizar(automatic);
}



VistaAutomatico::~VistaAutomatico() {
	if (timer) {
		delete(timer);
		timer = NULL;
	}
	if (periodos) {
		delete (periodos);
		periodos = NULL;
	}
	animacionQuieto = NULL;
/*	if (animacionQuieto) {
		delete (animacionQuieto);
		animacionQuieto = NULL;
	}*/
}


void VistaAutomatico::actualizar(Observable* observable) {
	posicionDibujar = observable->obtenerPosicion();

	if (quieto){
		if (timer->obtenerTiempo() >= (periodos->at(actual) * 1000)){
			cambiarAnimacion();
			timer->detener();
		}
	}else{
		if (animacionActual->termino()){
			quieto = true;
			animacionActual->detener();
			animacionActual = animacionQuieto;
			timer->comenzar();
		}
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

void VistaAutomatico::reiniciar(){
	actual = 0;
	quieto = false;
	terminoAhora = false;
	delete (timer);
	timer = new Timer();
	animacionActual->detener();
	animacionActual->resetear();
	animacionActual->detener();
	animacionActual = animaciones->at(0);
	animacionActual->resetear();
}
