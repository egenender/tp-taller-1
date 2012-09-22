#include "HojaSprites.h"
#include "VistaProtagonista.h"
VistaProtagonista::VistaProtagonista(Manual* protagonista) {

	// O algo similar:
	//animaciones = ResourcesManager::obtenerInstancia()->obtenerAnimaciones(protagonista->obtenerNombre());

	// A lo YaoMing mientras no este el parser:
//	Animacion* caminaDer = new Animacion(new HojaSprites("src/yoshi1.bmp", 64, 64), 150);
	Animacion* caminaDer = new Animacion(new HojaSprites("src/charmeleonMovimiento.png", 65, 73), 150);
	caminaDer->escala(protagonista->obtenerAncho(), protagonista->obtenerAlto());
	caminaDer->transparencia(255,0,255);

	Animacion* caminaIzq = caminaDer->voltear(HORIZONTALMENTE);

	//Animacion* quieto = new Animacion(new HojaSprites("src/yoshi2.bmp", 64, 64), 150);
	Animacion* quietoDer = new Animacion(new HojaSprites("src/charmeleonQuieto.png", 65, 73), 150);
	quietoDer->escala(protagonista->obtenerAncho(), protagonista->obtenerAlto());
	quietoDer->transparencia(255,0,255);

	Animacion* quietoIzq = quietoDer->voltear(HORIZONTALMENTE);

	animaciones->insert(pair<int, Animacion*>(QUIETODER, quietoDer));
	animaciones->insert(pair<int, Animacion*>(QUIETOIZQ, quietoIzq));
	animaciones->insert(pair<int, Animacion*>(CAMINANDODER,caminaDer));
	animaciones->insert(pair<int, Animacion*>(CAMINANDOIZQ,caminaIzq));
	actualizar(protagonista);
}
VistaProtagonista::VistaProtagonista(Manual* protagonista, Animacion* caminar, Animacion* quieto) {

	// O algo similar:
	//animaciones = ResourcesManager::obtenerInstancia()->obtenerAnimaciones(protagonista->obtenerNombre());

	// A lo YaoMing mientras no este el parser:
//	Animacion* caminaDer = new Animacion(new HojaSprites("src/yoshi1.bmp", 64, 64), 150);
	Animacion* caminaDer = new Animacion(new HojaSprites("src/charmeleonMovimiento.png", 65, 73), 150);
	caminaDer->escala(protagonista->obtenerAncho(), protagonista->obtenerAlto());
	caminaDer->transparencia(255,0,255);

	Animacion* caminaIzq = caminaDer->voltear(HORIZONTALMENTE);

	//Animacion* quieto = new Animacion(new HojaSprites("src/yoshi2.bmp", 64, 64), 150);
	Animacion* quietoDer = new Animacion(new HojaSprites("src/charmeleonQuieto.png", 65, 73), 150);
	quietoDer->escala(protagonista->obtenerAncho(), protagonista->obtenerAlto());
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

VistaProtagonista::~VistaProtagonista() {}
