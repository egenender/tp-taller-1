#ifndef HOJASPRITES_H
#define HOJASPRITES_H

#include "Superficie.h"

class HojaSprites : public Superficie {
	private:
		unsigned int anchoSprite, altoSprite, cantSprites;

	private:
		HojaSprites();
	public:
		HojaSprites(const char* archivo, unsigned int ancho, unsigned int alto);
		unsigned int obtenerNumeroSprites();
		bool dibujar(SDL_Surface* supDest, int x, int y, int sprite);
		bool escala(Uint16 ancho, Uint16 alto);
		bool escala(Uint16 factor);
		int obtenerAltoSprite();
		int obtenerAnchoSprite();
};

#endif
