/*
 * Textura.cpp
 *
 *  Created on: 22/09/2012
 *      Author: nicolas
 */

#include "Textura.h"

Textura::Textura(string archivo, int Rtext, int Gtext, int Btext, int Rfond, int Gfond, int Bfond) : Superficie::Superficie(archivo){
	// Transparencia de la textura:
	Superficie::transparencia(Rtext,Gtext,Btext);

	// Transparencia del fondo de la textura (seteada despues en aplicarTextura)
	this->Bfond = Bfond;
	this->Gfond = Gfond;
	this->Rfond = Rfond;
}

/** Aplica una textura a una superficie, y devuelve eso. Se asume que
 *  Superficie y textura tienen el mismo alto y ancho...
 */
Superficie* Textura::aplicarTextura(Superficie* superficie) {
	SDL_Surface* sup = superficie->obtenerSurface();
	SDL_Surface* final = SDL_CreateRGBSurface(SDL_SWSURFACE, ancho, alto, 32, 0, 0, 0, 0);

	// Dibujamos sobre la superficie final:
	SDL_BlitSurface(sup, NULL, final, NULL); // Primero la original (seria como una copia esto)
	SDL_BlitSurface(this->superficie, NULL, final, NULL); // Ahora la textura sobre eso

	// Ponemos el color transparte de la textura, para sacar el fondo:
	Uint32 colorkey = SDL_MapRGB(final->format, Rfond, Gfond, Bfond);
	SDL_SetColorKey(final, SDL_SRCCOLORKEY, colorkey);

	// Devolvemos la superficie con la textura:
	return new Superficie(final);
}
