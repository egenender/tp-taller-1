#include "VistaCuerpo.h"
#include "../model/Cuerpo.h"

VistaCuerpo::VistaCuerpo() {
	posicionDibujar = NULL;
	posicionColision = NULL;
	supDebug = new Superficie("src/resources/cuerpos/debugSup.png");
};

VistaCuerpo::~VistaCuerpo() {

	if (supDebug) {
		delete(supDebug);
		supDebug = NULL;
	}

	// TODO: HMMM... no la borraria cuerpo?

	/*if (posicionDibujar != NULL) {
		delete(posicionDibujar);
		posicionDibujar = NULL;
	}*/
}


void VistaCuerpo::actualizar(Observable* observable) {
	if (!observable)
		return;

	posicionDibujar = observable->obtenerPosicion();
	Cuerpo* cuerpo = (Cuerpo*) observable;
//	if (supDebug) {
//		supDebug->escala(cuerpo->obtenerArea()->obtenerAncho(), cuerpo->obtenerArea()->obtenerAlto());
//	}
//	posicionColision = cuerpo->obtenerArea()->obtenerPosicion();
}
