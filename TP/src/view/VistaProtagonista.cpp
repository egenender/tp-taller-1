#include "HojaSprites.h"
#include "VistaProtagonista.h"

VistaProtagonista::VistaProtagonista(Observable* protagonista, Animacion* caminar, Animacion* quieto) {

	Animacion* caminaDer = caminar;
	caminaDer->transparencia(255,0,255); // color transparente = magenta

	Animacion* caminaIzq = caminaDer->voltear(HORIZONTALMENTE);

	Animacion* quietoDer=quieto;
	quietoDer->transparencia(255,0,255);

	Animacion* quietoIzq = quietoDer->voltear(HORIZONTALMENTE);

	animaciones->insert(pair<int, Animacion*>(QUIETODER, quietoDer));
	animaciones->insert(pair<int, Animacion*>(QUIETOIZQ, quietoIzq));
	animaciones->insert(pair<int, Animacion*>(CAMINANDODER,caminaDer));
	animaciones->insert(pair<int, Animacion*>(CAMINANDOIZQ,caminaIzq));

	//FIXME: poner las animaciones que correspondan al salto cuando esten
	Animacion* saltandoDer = quietoIzq->voltear(HORIZONTALMENTE);
	Animacion* saltandoIzq = saltandoDer->voltear(HORIZONTALMENTE);
	animaciones->insert(pair<int, Animacion*>(SALTANDODER, saltandoDer));
	animaciones->insert(pair<int, Animacion*>(SALTANDOIZQ, saltandoIzq));

	posicionDibujar = protagonista->obtenerPosicion();
//	actualizar(protagonista);
}

void VistaProtagonista::actualizar(Observable* observable) {
	if (pararDeDibujar) return;
	int estado = observable->obtenerEstado();
	if (estado == MUERTO){
		pararDeDibujar = true;
		return;
	}

	posicionDibujar = observable->obtenerPosicion();
	animacionActual = animaciones->at(estado);
}

VistaProtagonista::~VistaProtagonista() {}
