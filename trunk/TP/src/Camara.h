#ifndef CAMARA_H_
#define CAMARA_H_

// TODO: En realidad deberia cargar la configuracion del juego, pedirsela a alguien:
#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480
#define MARGEN_SCROLL 160
#define ANCHO_NIVEL 1200
#define ALTO_NIVEL 622


// Esto si va:
#include "VistaCuerpo.h"
#include "Superficie.h"
#include "Posicion.h"


class Camara : public VistaCuerpo {
	private:
		// Las dimensiones de la camara:
		Superficie* imagen;
		SDL_Rect* camara;
		int margenScroll, altoNivel, anchoNivel;

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
