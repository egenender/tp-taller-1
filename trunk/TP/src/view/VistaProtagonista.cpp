#include "HojaSprites.h"
#include "VistaProtagonista.h"

VistaProtagonista::VistaProtagonista(/*Observable* protagonista,*/ Animacion* caminar, Animacion* quieto, Animacion* saltar/*, BarraEstado* labarra*/) {
	//barra = labarra;
	//primeraVez = true;
	invisible = false;
	Animacion* caminaDer = caminar;
	caminaDer->transparencia(255,0,255);
	Animacion* caminaIzq = caminaDer->voltear(HORIZONTALMENTE);

	Animacion* quietoDer=quieto;
	quietoDer->transparencia(255,0,255);
	Animacion* quietoIzq = quietoDer->voltear(HORIZONTALMENTE);

	Animacion* saltandoDer = saltar;
	saltandoDer->transparencia(255,0,255);
	Animacion* saltandoIzq = saltandoDer->voltear(HORIZONTALMENTE);

	animaciones->insert(pair<int, Animacion*>(QUIETODER, quietoDer));
	animaciones->insert(pair<int, Animacion*>(QUIETOIZQ, quietoIzq));
	animaciones->insert(pair<int, Animacion*>(CAMINANDODER,caminaDer));
	animaciones->insert(pair<int, Animacion*>(CAMINANDOIZQ,caminaIzq));
	animaciones->insert(pair<int, Animacion*>(SALTANDODER, saltandoDer));
	animaciones->insert(pair<int, Animacion*>(SALTANDOIZQ, saltandoIzq));
}

void VistaProtagonista::actualizar(Observable* observable) {
	int estado = observable->obtenerEstado();
	if (estado == MUERTO){
		pararDeDibujar = true;
		return;
	}
	pararDeDibujar = false;

	posicionDibujar = observable->obtenerPosicion();

	// NEW:

	// Si el estado cambio, actualizo la animacion, y reseteo la anterior
	if (estado != estadoActual) {
		if (animacionActual)
			animacionActual->resetear(); // Reseteo la anterior, asi comienza del frame 0.
		animacionActual = animaciones->at(estado); // Actualizo la nueva animacion
		estadoActual = estado;
	}
	
	// OLD:
	// animacionActual = animaciones->at(estado);

	invisible = !invisible && observable->estaInvencible();
}

void VistaProtagonista::reiniciar(){

}

VistaProtagonista::~VistaProtagonista() {}

bool VistaProtagonista::dibujar(SDL_Surface* display, int xCamara, int yCamara){
	if (!invisible) return VistaAnimada::dibujar(display, xCamara, yCamara);
	return true;
}
