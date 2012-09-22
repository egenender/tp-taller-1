#include "VistaAutomatico.h"

VistaAutomatico::VistaAutomatico(Automatico* automatic, Animacion* pasiva, Animacion* activa) {

	pasiva->escala(automatic->obtenerAncho(), automatic->obtenerAlto());
	activa->escala(automatic->obtenerAncho(), automatic->obtenerAlto());
	pasiva->transparencia(255,0,255);
	activa->transparencia(255,0,255);

	animaciones->insert(pair<int, Animacion*>(PRIMERA, pasiva));
	animaciones->insert(pair<int, Animacion*>(SEGUNDA, activa));
	actualizar(automatic);
	animacionActual = pasiva;
	terminoAhora = true;
	actual = PRIMERA;
}

VistaAutomatico::~VistaAutomatico() {
	// TODO Auto-generated destructor stub
}

void VistaAutomatico::actualizar(Observable* observable) {
	Automatico* automatic = (Automatico*) observable;

	posicionDibujar = automatic->obtenerPosicion();

	//Si la animacion actual todavia no termino, entonces tengo que seguir
	//con esta. No cambio nada.
	if (!animacionActual->termino()) return;

	//si Recien termino, tengo que reiniciar el timer
	if (terminoAhora){
		terminoAhora = false;
		animacionActual->detener();
		//timer->reiniciar();
	}

	//Si el timer terminó de contar, tengo que cambiar la animacion

	//if (timer->termino()){
		cambiarAnimacion();
	//}

}

void VistaAutomatico::cambiarAnimacion(){
	if (actual == PRIMERA)
		actual = SEGUNDA;
	else
		actual = PRIMERA;

	animacionActual = animaciones->at(actual);
	animacionActual->resetear();
}
