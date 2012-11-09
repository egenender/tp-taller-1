#include "VistaVidas.h"
#include "Superficie.h"
#include "../model/Personajes/Plataforma.h"
#include "../model/Area.h"

VistaVidas::VistaVidas() {
	vidas = 0;
	sup = new Superficie("src/resources/items/luvdisc.bmp");
	sup->escala(DIM_CORAZON,DIM_CORAZON);
	sup->transparencia(255,0,255);

}

VistaVidas::~VistaVidas() {
	delete(sup);
}

void VistaVidas::actualizar(Observable* observable){
	vidas = observable->obtenerVidas();
}

bool VistaVidas::dibujar(SDL_Surface* display, int xCamara, int yCamara, bool debug){
	bool retorno = true;;
	int inicial = 10;
	for (int i = 0; i < vidas; i++){
		retorno &= sup->dibujar(display, inicial, 10);
		inicial += DIM_CORAZON;
	}

	return retorno;
}
