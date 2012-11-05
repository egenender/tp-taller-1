#include "VistaVarios.h"
#include "../model/Observable.h"

VistaVarios::VistaVarios() {

}

VistaVarios::~VistaVarios() {
}

void VistaVarios::actualizar(Observable* observable){
	int estado = observable->obtenerEstado();
	if (estado == MUERTO){
		pararDeDibujar = true;
		return;
	}
	pararDeDibujar = false;

	posicionDibujar = observable->obtenerPosicion();
	animacionActual = animaciones->at(estado);

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

