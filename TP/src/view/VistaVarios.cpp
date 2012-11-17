#include "VistaVarios.h"
#include "../model/Observable.h"

VistaVarios::VistaVarios() {
	invisible = false;
}

VistaVarios::~VistaVarios() {
}

void VistaVarios::actualizar(Observable* observable){
	if (!observable)
		return;
	posicionDibujar = observable->obtenerPosicion();

	int estado = observable->obtenerEstado();
	if (estado == MUERTO){
		pararDeDibujar = true;
		return;
	}
	pararDeDibujar = false;

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
void VistaVarios::reiniciar(){}

void VistaVarios::agregarEstadoSoportado(int estado, Animacion* anim){
	anim->transparencia(255,0,255);
	animaciones->insert(pair<int, Animacion*>(estado, anim));
}

void VistaVarios::agregarEstadoSoportadoEInverso(int estado,int estadoInverso, Animacion* anim){
	anim->transparencia(255,0,255);
	Animacion* derecha = anim;
	Animacion* inversa = anim->voltear(HORIZONTALMENTE);

	animaciones->insert(pair<int, Animacion*>(estado, derecha));
	animaciones->insert(pair<int, Animacion*>(estadoInverso, inversa));
}

bool VistaVarios::dibujar(SDL_Surface* display, int xCamara, int yCamara){
	if (!invisible) return VistaAnimada::dibujar(display, xCamara, yCamara);
	return true;
}
