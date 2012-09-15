#include "Superficie.h"

Superficie::Superficie() {
	alto = 0;
	ancho = 0;
	superficie = NULL;
}

/** Crea una superficie a partir de una superficie SDL **/
Superficie::Superficie(SDL_Surface* superficie) {
	alto = superficie->h;
	ancho = superficie->w;
	this->superficie = superficie;
}

/** Crea una superficie a partir de una ruta de imagen **/
Superficie::Superficie(const char* archivo) {

	Superficie();
	if ((superficie = cargar(archivo)) != NULL) {
		alto = superficie->h;
		ancho = superficie->w;
	}
}

Superficie::~Superficie() {
	SDL_FreeSurface(superficie);
}

SDL_Surface* Superficie::cargar(const char* archivo) {
	SDL_Surface* supTemporal = NULL;
	SDL_Surface* supFinal = NULL;

	if ((supTemporal = IMG_Load(archivo)) == NULL) {
		printf("Error: No se puede cargar el archivo '%s'\n", archivo);
		return NULL;
	}

	supFinal = SDL_DisplayFormat(supTemporal);
	SDL_FreeSurface(supTemporal);

	return supFinal;
}

/** Dibuja la imagen sobre supDest, en la posicion (x,y). Si corte es distinto
 *  de NULL, se dibuja la parte deliminada por corte de la imagen. **/
bool Superficie::dibujar(SDL_Surface* supDest, int x, int y, SDL_Rect* corte) {
	if (supDest == NULL || superficie == NULL)
		return false;

	SDL_Rect rectDest;

	rectDest.x = x;
	rectDest.y = y;

	SDL_BlitSurface(superficie, corte, supDest, &rectDest);

	return true;
}

/** Setea un color RGB como transparente en la imagen **/
void Superficie::transparencia(unsigned int R, unsigned int G, unsigned int B) {
	if (superficie == NULL)
		return;

	Uint32 colorkey = SDL_MapRGB(superficie->format, R, G, B);
	SDL_SetColorKey(superficie, SDL_SRCCOLORKEY, colorkey);
}

Uint32 Superficie::getPixel(SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *) p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *) p;
		break;

	default:
		return 0; /* shouldn't happen, but avoids warnings */
	}
}

void Superficie::putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *) p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		} else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *) p = pixel;
		break;
	}
}

bool Superficie::escala(Uint16 ancho, Uint16 alto) {
	if (!superficie || !ancho || !alto)
		return false;

	SDL_Surface* _ret = SDL_CreateRGBSurface(superficie->flags, ancho, alto,
			superficie->format->BitsPerPixel, superficie->format->Rmask,
			superficie->format->Gmask, superficie->format->Bmask,
			superficie->format->Amask);

	if (!_ret)
		return false;

	double _stretch_factor_x = (static_cast<double>(ancho)
			/ static_cast<double>(superficie->w)), _stretch_factor_y =
			(static_cast<double>(alto) / static_cast<double>(superficie->h));

	for (Sint32 y = 0; y < superficie->h; y++)
		for (Sint32 x = 0; x < superficie->w; x++)
			for (Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
				for (Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
					putPixel(_ret,
							static_cast<Sint32>(_stretch_factor_x * x) + o_x,
							static_cast<Sint32>(_stretch_factor_y * y) + o_y,
							getPixel(superficie, x, y));

	SDL_FreeSurface(superficie);
	superficie = _ret;
	return true;
}

/** Escala la superficie con un determinado factor de escala **/
bool Superficie::escala(Uint16 factor) {
	return escala(ancho * factor, alto * factor);
}

/** Devuelve el alto de la superficie **/
int Superficie::obtenerAlto() {
	return alto;
}

/** Devuelve el ancho de la superficie **/
int Superficie::obtenerAncho() {
	return ancho;
}

Uint32 get_pixel32(SDL_Surface *surface, int x, int y) {
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *) surface->pixels;
	//Get the requested pixel
	return pixels[(y * surface->w) + x];
}
void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel) {
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *) surface->pixels;
	//Set the pixel
	pixels[(y * surface->w) + x] = pixel;
}

/** Devuelve una nueva superficie volteada, respecto de la original.
 * Parametros: El tipo de volteo: HORIZONTALMENTE y VERTICALMENTE
 * Se puede hacer ambos volteos a la vez, pasar como parametro:
 * HORIZONTALMENTE | VERTICALMENTE **/
Superficie* Superficie::voltear(int flags) {

	SDL_Surface* volteada = NULL;

	// Caso que la imagen tiene un color seteado como transparente:
	if (superficie->flags & SDL_SRCCOLORKEY)
		volteada = SDL_CreateRGBSurface(SDL_SWSURFACE, superficie->w,
				superficie->h, superficie->format->BitsPerPixel,
				superficie->format->Rmask, superficie->format->Gmask,
				superficie->format->Bmask, 0);
	// Otro caso:
	else
		volteada = SDL_CreateRGBSurface(SDL_SWSURFACE, superficie->w,
				superficie->h, superficie->format->BitsPerPixel,
				superficie->format->Rmask, superficie->format->Gmask,
				superficie->format->Bmask, superficie->format->Amask);

	// Bloqueamos la superficie original
	if (SDL_MUSTLOCK(superficie))
		SDL_LockSurface(superficie);

	// Recorremos las columnas
	for (int x = 0, rx = volteada->w - 1; x < volteada->w; x++, rx--) {
		// Recorremos las filas
		for (int y = 0, ry = volteada->h - 1; y < volteada->h; y++, ry--) {
			// Obtenemos un pixel:
			Uint32 pixel = get_pixel32(superficie, x, y);
			// Copiamos el pixel:
			if ((flags & VERTICALMENTE) && (flags & HORIZONTALMENTE)) {
				put_pixel32(volteada, rx, ry, pixel);
			} else if (flags & HORIZONTALMENTE) {
				put_pixel32(volteada, rx, y, pixel);
			} else if (flags & VERTICALMENTE) {
				put_pixel32(volteada, x, ry, pixel);
			}
		}
	}

	// Desbloqueamos la superficie original
	if (SDL_MUSTLOCK(superficie)) {
		SDL_UnlockSurface(superficie);
	}

	// Copiamos el color seteado como transparente:
	if (superficie->flags & SDL_SRCCOLORKEY) {
		SDL_SetColorKey(volteada, SDL_RLEACCEL | SDL_SRCCOLORKEY,
				superficie->format->colorkey);
	}

	return new Superficie(volteada);
}
