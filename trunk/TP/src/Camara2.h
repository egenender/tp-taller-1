#ifndef CAMARA2_H_
#define CAMARA2_H_

#include "Aplicacion.h"

#define ANCHO_NIVEL 1200
#define ALTO_NIVEL 622

class Camara {
	private:
		// Las dimensiones de la camara:
		SDL_Rect* cam;
		int margenScroll;

	public:
		Camara(int x, int y);
		void actualizar(int,int,int,int);
		int obtenerX();
		int obtenerY();
		SDL_Rect* obtenerDimensiones();
		~Camara();
};

#endif
