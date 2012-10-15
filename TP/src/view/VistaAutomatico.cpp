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

	vector<Animacion*>::iterator iter;
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
	delete(timer);
	delete (periodos);
	delete (animacionQuieto);
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