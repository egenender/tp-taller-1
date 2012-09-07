#ifndef SURFACE_H
#define SUPERFICIE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Superficie {

	protected:
		SDL_Surface* superficie;
		int alto;
		int ancho;

	public:
		Superficie(const char* archivo);
		~Superficie();

	protected:
		Superficie();
		SDL_Surface* cargar(const char* archivo);

	private:
		Uint32 getPixel(SDL_Surface *surface, int x, int y);
		void putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);


	public:
		bool dibujar(SDL_Surface* supDest, int X, int Y);
		bool dibujar(SDL_Surface* supDest, int xDest, int yDest, int xOri, int yOri, int Ancho, int Altura);
		void transparencia(unsigned int R, unsigned int G, unsigned int B);
		bool escala(Uint16 width, Uint16 height);
		bool scale(Uint16 factor);
};

#endif
