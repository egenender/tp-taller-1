#include "HojaSprites.h"

void HojaSprites::inicializarHojaSprites() {
	altoSprite = 0;
	anchoSprite = 0;
	cantSprites = 0;
}

/** Crea una Hoja de Sprites a partir de un archivo. Ancho y Alto son
 *  de cada sprite individual. La Hoja se asume vertical (una columna).
 *  Debe haber una correspondencia entre el ancho y alto de la imagen completa
 *  con cada sprite individual... Ej: archivo de 64x256 pixeles, sprites de
 *  64x64 pixeles -> tenemos 4 sprites en total. **/
HojaSprites::HojaSprites(string archivo, int anchoSprite, int altoSprite) : Superficie(archivo) {

	inicializarHojaSprites();

	if (superficie && (anchoSprite > 0 && altoSprite > 0)) {
		if (anchoSprite > this->ancho)
			this->anchoSprite = this->ancho;
		if (altoSprite > this->alto)
			this->altoSprite = this->alto;

		else {
			this->altoSprite = altoSprite;
			this->anchoSprite = anchoSprite;
		}

		cantSprites = this->alto / this->altoSprite;
	}
}


/** Crea una hoja de sprites a partir de una superficie SDL **/
HojaSprites::HojaSprites(SDL_Surface* sup, int anchoSprite, int altoSprite) : Superficie(sup) {
	inicializarHojaSprites();

	if (superficie && (anchoSprite > 0 && altoSprite > 0)) {
		if (anchoSprite > this->ancho)
			this->anchoSprite = this->ancho;
		if (altoSprite > this->alto)
			this->altoSprite = this->alto;

		else {
			this->altoSprite = altoSprite;
			this->anchoSprite = anchoSprite;
		}

		cantSprites = this->alto / this->altoSprite;
	}
}

/** Devuelve el total de sprites que hay **/
unsigned int HojaSprites::obtenerNumeroSprites() {
	return cantSprites;
}

/** Dibuja el sprite numero "sprite" en la superficie "supDest", en X,Y
 *  Recordar que el primer sprite es el 0, el segundo el 1, etc... **/
bool HojaSprites::dibujar(SDL_Surface* supDest, int x, int y, int sprite) {
	if (supDest == NULL || superficie == NULL || sprite < 0) {
		printf("Error al dibujar hoja de sprites\n");
		return false;
	}

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

/** Redimenciona la hoja de sprites en ancho y alto.
 * ATENCION: pueden ocurrir efectos raros al utilizar este metodo, ya que
 * no se asegura que se puedan definir bien las dimensiones de los sprites
 * Se recomienda utilizar escala(factor). Aun asi, este metodo queda por si
 * llega a ser util en algun momento **/
bool HojaSprites::escala(Uint16 nuevoAnchoSprite, Uint16 nuevoAltoSprite) {

	if(!Superficie::escala(nuevoAnchoSprite, nuevoAltoSprite*cantSprites)) {
		return false;
	}

	anchoSprite = nuevoAnchoSprite;
	altoSprite = nuevoAltoSprite;

	return true;
}

/** Redimenciona la hoja de sprites en ancho y alto. **/
bool HojaSprites::escala(Uint16 factor) {
	return escala(anchoSprite*factor,altoSprite*factor);
}
/** Devuelve el alto de un Sprite **/
int HojaSprites::obtenerAltoSprite() {
	return altoSprite;
}

/** Devuelve el ancho de un Sprite **/
int HojaSprites::obtenerAnchoSprite() {
	return anchoSprite;
}

/** Devuelve una hoja de sprites volteada **/
HojaSprites* HojaSprites::voltear(int flags) {
	SDL_Surface* volteada = this->Superficie::voltear(flags)->obtenerSurface();

	return new HojaSprites(volteada, anchoSprite, altoSprite);
}
