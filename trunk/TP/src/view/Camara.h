#ifndef CAMARA_H_
#define CAMARA_H_

#include "VistaCuerpo.h"
#include "Superficie.h"
#include "../model/Posicion.h"

class Camara : public VistaCuerpo {
	private:
		Superficie* imagen;
		// Las dimensiones de la camara:
		SDL_Rect* camara;
		int margenScroll, margenScrollY, altoNivel, anchoNivel;

	private:
		void iniciarCamara();

	public:
		Camara(int x, int y);
		void actualizar(Observable* observable);
		bool dibujar(SDL_Surface* display, int xCamara, int yCamara);
		int obtenerX();
		int obtenerY();
		Posicion* obtenerPosicion();
		SDL_Rect* obtenerDimensiones();
		~Camara();
};

#endif
