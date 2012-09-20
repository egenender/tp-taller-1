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
HojaSprites::HojaSprites(string archivo, unsigned int ancho, unsigned int alto) : Superficie(archivo) {

	HojaSprites();

	if (superficie && (ancho > 0 && alto > 0)) {
		altoSprite = alto;
		anchoSprite = ancho;

		cantSprites = this->alto / alto;
	}
}


/** Crea una hoja de sprites a partir de una superficie SDL **/
HojaSprites::HojaSprites(SDL_Surface* sup, unsigned int ancho, unsigned int alto) : Superficie(sup) {
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
	if(!superficie) {
		printf("Error al aplicar escala: superficie es NULL\n");
		return false;
	}

	float factorAncho = (float) nuevoAnchoSprite/this->anchoSprite;
	float factorAlto = (float) nuevoAltoSprite/this->altoSprite;

	if(!Superficie::escala(nuevoAnchoSprite, nuevoAltoSprite*cantSprites)) {
		printf("Error al aplicar escala\n");
		return false;
	}

	altoSprite *= factorAlto;
	anchoSprite *= factorAncho;

	return true;
}

/** Redimenciona la hoja de sprites en ancho y alto. **/
bool HojaSprites::escala(Uint16 factor) {
	return escala(ancho*factor,alto*factor);
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
