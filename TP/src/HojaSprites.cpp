#include "HojaSprites.h"

HojaSprites::HojaSprites() {
	altoSprite = 0;
	anchoSprite = 0;
	cantSprites = 0;
}

/** Crea una Hoja de Sprites a partir de un archivo. Ancho y Alto son
 *  de cada sprite individual. La Hoja se asume vertical (una columna).
 *  Debe haber una correspondencia entre el ancho y alto de la imagen completa
 *  con cada sprite individual... Ej: archivo de 64x256 pixeles, sprites de
 *  64x64 pixeles -> tenemos 4 sprites en total. **/
HojaSprites::HojaSprites(const char* archivo, int ancho, int alto) : Superficie(archivo) {

	HojaSprites();

	if (superficie && (ancho > 0 && alto > 0)) {
		altoSprite = alto;
		anchoSprite = ancho;

		cantSprites = this->alto / alto;
	}
}

/** Devuelve el total de sprites que hay **/
unsigned int HojaSprites::obtenerNumeroSprites() {
	return cantSprites;
}

/** Dibuja el sprite numero "sprite" en la superficie "supDest", en X,Y
 *  Recordar que el primer sprite es el 0, el segundo el 1, etc... **/
bool HojaSprites::dibujar(SDL_Surface* supDest, int x, int y, int sprite) {
	if (supDest == NULL || superficie == NULL || sprite < 0)
		return false;

	SDL_Rect rectDest;

	rectDest.x = x;
	rectDest.y = y;

	SDL_Rect rectOri;

	rectOri.x = 0;
	rectOri.y = altoSprite*sprite;
	rectOri.w = anchoSprite;
	rectOri.h = altoSprite;

	SDL_BlitSurface(superficie, &rectOri, supDest, &rectDest);

	return true;
}

bool HojaSprites::escala(Uint16 ancho, Uint16 alto) {
	if(!superficie)
		return false;

	float factorAncho = (float) ancho/this->ancho;
	float factorAlto = (float) alto/this->alto;

	if(!Superficie::escala(ancho, alto))
		return false;

	altoSprite *= factorAlto;
	anchoSprite *= factorAncho;

	return true;
}
