#include "HojaSprites.h"
#include "VistaProtagonista.h"

VistaProtagonista::VistaProtagonista(Manual* protagonista) {

	// O algo similar:
	//animaciones = ResourcesManager::obtenerInstancia()->obtenerAnimaciones(protagonista->obtenerNombre());

	// A lo YaoMing mientras no este el parser:
	Animacion* caminaDer = new Animacion(new HojaSprites("src/yoshi1.bmp", 64, 64), 150);
	caminaDer->escala(protagonista->obtenerAncho(), protagonista->obtenerAlto());
	//caminaDer->transparencia(255,0,255);

	Animacion* caminaIzq = caminaDer->voltear(HORIZONTALMENTE);

	Animacion* quieto = new Animacion(new HojaSprites("src/yoshi2.bmp", 64, 64), 150);
	quieto->escala(protagonista->obtenerAncho(), protagonista->obtenerAlto());
	quieto->transparencia(255,0,255);

	animaciones->insert(pair<int, Animacion*>(QUIETO, quieto));
	animaciones->insert(pair<int, Animacion*>(CAMINANDODER,caminaDer));
	animaciones->insert(pair<int, Animacion*>(CAMINANDOIZQ,caminaIzq));
	actualizar(protagonista);
}

void VistaProtagonista::actualizar(Observable* observable) {
	Manual* prot = (Manual*) observable;

	posicionDibujar = prot->obtenerPosicion();
	animacionActual = animaciones->at(prot->obtenerEstado());
}

VistaProtagonista::~VistaProtagonista() {}
