#ifndef SURFACE_H
#define SUPERFICIE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <string>
using namespace std;

#define VERTICALMENTE 0x00000001
#define HORIZONTALMENTE 0x00000010

class Superficie {

	protected:
		SDL_Surface* superficie;
		int alto;
		int ancho;

	public:
		Superficie(SDL_Surface* superficie);
		Superficie(string archivo);
		~Superficie();

	protected:
		Superficie();
		SDL_Surface* cargar(string archivo);

	private:
		Uint32 getPixel(SDL_Surface *surface, int x, int y);
		void putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);


	public:
		bool dibujar(SDL_Surface* supDest, int X, int Y, SDL_Rect* corte = NULL);
		void transparencia(unsigned int R, unsigned int G, unsigned int B);
		bool escala(Uint16 width, Uint16 height);
		bool escala(Uint16 factor);
		int obtenerAlto();
		int obtenerAncho();
		Superficie* voltear(int flags);
		SDL_Surface* obtenerSurface();
};

#endif
