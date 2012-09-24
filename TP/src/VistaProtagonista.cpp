#include "HojaSprites.h"
#include "VistaProtagonista.h"

VistaProtagonista::VistaProtagonista(Manual* protagonista) {
	// Nothing to do here (?)
}

VistaProtagonista::VistaProtagonista(Manual* protagonista, Animacion* caminar, Animacion* quieto) {

	Animacion* caminaDer=caminar;
//	caminaDer->escala(protagonista->obtenerAncho(), protagonista->obtenerAlto());
	caminaDer->transparencia(255,0,255); // color transparente = magenta

	Animacion* caminaIzq = caminaDer->voltear(HORIZONTALMENTE);

	Animacion* quietoDer=quieto;
//	quietoDer->escala(protagonista->obtenerAncho(), protagonista->obtenerAlto());
	quietoDer->transparencia(255,0,255);

	Animacion* quietoIzq = quietoDer->voltear(HORIZONTALMENTE);

	animaciones->insert(pair<int, Animacion*>(QUIETODER, quietoDer));
	animaciones->insert(pair<int, Animacion*>(QUIETOIZQ, quietoIzq));
	animaciones->insert(pair<int, Animacion*>(CAMINANDODER,caminaDer));
	animaciones->insert(pair<int, Animacion*>(CAMINANDOIZQ,caminaIzq));
	actualizar(protagonista);
}

void VistaProtagonista::actualizar(Observable* observable) {
	Manual* prot = (Manual*) observable;

	posicionDibujar = prot->obtenerPosicion();
	animacionActual = animaciones->at(prot->obtenerEstado());
}

VistaProtagonista::~VistaProtagonista() {
/*	map<int, Animacion*>::iterator iter;
	for (iter = animaciones->begin(); iter != animaciones->end(); iter++) {
		delete(iter->second);
	}*/
}
