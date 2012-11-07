#include "Superficie.h"
#include "../log/Log.h"
#include "SDL/SDL_rotozoom.h"

void Superficie::inicializarSuperficie() {
	alto = 0;
	ancho = 0;
	superficie = NULL;
}

Superficie::Superficie(string archivo, SDL_Rect* corte) {
	inicializarSuperficie();
	SDL_Surface* temp = cargar(archivo);
	SDL_Surface* final = SDL_CreateRGBSurface(SDL_HWSURFACE, corte->w, corte->h,
			32, 0, 0, 0, 0);
	SDL_BlitSurface(temp, corte, final, NULL);
	superficie = final;
	alto = final->h;
	ancho = final->w;
}

Superficie::Superficie(string archivo, int x, int y, int ancho, int alto) {
	inicializarSuperficie();
	SDL_Surface* temp = cargar(archivo);
	SDL_Surface* final = SDL_CreateRGBSurface(SDL_HWSURFACE, ancho, alto, 32, 0,
			0, 0, 0);
	SDL_Rect corte;
	corte.x = x;
	corte.y = y;
	corte.h = alto;
	corte.w = ancho;
	SDL_BlitSurface(temp, &corte, final, NULL);
	superficie = final;
	alto = final->h;
	ancho = final->w;
	SDL_FreeSurface(temp);
}

/** Crea una superficie a partir de una superficie SDL **/
Superficie::Superficie(SDL_Surface* superficie) {
	inicializarSuperficie();
	alto = superficie->h;
	ancho = superficie->w;
	this->superficie = superficie;
}

/** Crea una superficie a partir de una ruta de imagen **/
Superficie::Superficie(string archivo) {
	inicializarSuperficie();

	superficie = cargar(archivo);

	if (superficie != NULL) {
		alto = superficie->h;
		ancho = superficie->w;
	}
}

Superficie::~Superficie() {
	if (superficie != NULL) {
		SDL_FreeSurface(superficie);
		superficie = NULL;
	}
}

SDL_Surface* Superficie::cargar(string archivo) {
	SDL_Surface* supTemporal = NULL;
	SDL_Surface* supFinal = NULL;

	if ((supTemporal = IMG_Load(archivo.c_str())) == NULL) {
		Log::getInstance()->writeToLogFile(Log::ERROR,
				"No se pudo cargar el archivo [" + archivo + "]\n");
		return NULL;
	}

	// Caso con png y transparencia incluida:
	if (archivo.find(".png") != string::npos)
		supFinal = SDL_DisplayFormatAlpha(supTemporal);
	else // otro tipo de archivo, sin transparencia incluida
		supFinal = SDL_DisplayFormat(supTemporal);
	if (!supFinal)
		return supTemporal;

	SDL_FreeSurface(supTemporal);

	return supFinal;
}

/** Dibuja la imagen sobre supDest, en la posicion (x,y). Si corte es distinto
 *  de NULL, se dibuja la parte deliminada por corte de la imagen. **/
bool Superficie::dibujar(SDL_Surface* supDest, int x, int y, SDL_Rect* corte) {
	if (supDest == NULL || superficie == NULL) {
		printf("Error al dibujar superficie: se recibio NULL\n");
		return false;
	}

	SDL_Rect rectDest;

	rectDest.x = x;
	rectDest.y = y;

	SDL_BlitSurface(superficie, corte, supDest, &rectDest);

	return true;
}

/** Setea un color RGB como transparente en la imagen **/
void Superficie::transparencia(unsigned int R, unsigned int G, unsigned int B) {
	if (superficie == NULL) {
		printf("Error al aplicar transparencia: superficie es NULL\n");
		return;
	}

	Uint32 colorkey = SDL_MapRGB(superficie->format, R, G, B);
	SDL_SetColorKey(superficie, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
}

Uint32 Superficie::getPixel(SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	// Here p is the address to the pixel we want to retrieve
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
		return 0; // shouldn't happen, but avoids warnings
	}
}

void Superficie::putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
	int bpp = surface->format->BytesPerPixel;
	// Here p is the address to the pixel we want to set
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
	if (ancho <= 0 || alto <= 0) {
		printf("Error al aplicar escala: ancho o algo <= 0\n");
		return false;
	}

	if (!superficie) {
		printf("Error al aplicar escala: SDL_Surface es NULL\n");
		return false;
	}

	/** Caso que no reescalo **/
	if (ancho == this->ancho && alto == this->alto)
		return true;

	SDL_Surface* _ret = NULL;

	/*_ret = SDL_CreateRGBSurface(superficie->flags, ancho, alto,
	 superficie->format->BitsPerPixel, superficie->format->Rmask,
	 superficie->format->Gmask, superficie->format->Bmask,
	 superficie->format->Amask);*/

	// Caso que la imagen tiene un color seteado como transparente:
	if (superficie->flags & SDL_SRCCOLORKEY)
		_ret = SDL_CreateRGBSurface(SDL_HWSURFACE, superficie->w, superficie->h,
				superficie->format->BitsPerPixel, superficie->format->Rmask,
				superficie->format->Gmask, superficie->format->Bmask, 0);
	// Otro caso:
	else
		_ret = SDL_CreateRGBSurface(SDL_HWSURFACE, ancho, alto,
				superficie->format->BitsPerPixel, superficie->format->Rmask,
				superficie->format->Gmask, superficie->format->Bmask,
				superficie->format->Amask);

	if (!_ret) {
		printf("Error al aplicar escala: no se pudo aplicar\n");
		return false;
	}

	// Bloqueamos la superficie original
	if (SDL_MUSTLOCK(superficie))
		SDL_LockSurface(superficie);

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

	// Desbloqueamos la superficie original
	if (SDL_MUSTLOCK(superficie)) {
		SDL_UnlockSurface(superficie);
	}

	// Copiamos el color seteado como transparente:
	if (superficie->flags & SDL_SRCCOLORKEY) {
		SDL_SetColorKey(_ret, SDL_RLEACCEL | SDL_SRCCOLORKEY,
				superficie->format->colorkey);
	}

	SDL_FreeSurface(superficie);
	superficie = _ret;
	this->alto = _ret->h;
	this->ancho = _ret->w;
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

/** Devuelve una nueva superficie volteada, respecto de la original.
 * Parametros: El tipo de volteo: HORIZONTALMENTE y VERTICALMENTE
 * Se puede hacer ambos volteos a la vez, pasar como parametro:
 * HORIZONTALMENTE | VERTICALMENTE **/
Superficie* Superficie::voltear(int flags) {

	// Caso que no piden voltear: (medio al pedo, pero puede pasar)
	if (flags == (HORIZONTALMENTE & VERTICALMENTE))
		return new Superficie(superficie);

	SDL_Surface* volteada = NULL;

	// Caso que la imagen tiene un color seteado como transparente:
	if (superficie->flags & SDL_SRCCOLORKEY)
		volteada = SDL_CreateRGBSurface(SDL_HWSURFACE, superficie->w,
				superficie->h, superficie->format->BitsPerPixel,
				superficie->format->Rmask, superficie->format->Gmask,
				superficie->format->Bmask, 0);
	// Otro caso:
	else
		volteada = SDL_CreateRGBSurface(SDL_HWSURFACE, superficie->w,
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
			Uint32 pixel = getPixel(superficie, x, y);
			// Copiamos el pixel:
			if ((flags & VERTICALMENTE) && (flags & HORIZONTALMENTE)) {
				putPixel(volteada, rx, ry, pixel);
			} else if (flags & HORIZONTALMENTE) {
				putPixel(volteada, rx, y, pixel);
			} else if (flags & VERTICALMENTE) {
				putPixel(volteada, x, ry, pixel);
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

/** Devuelve la superficie SDL **/
SDL_Surface* Superficie::obtenerSurface() {
	return superficie;
}


Superficie* Superficie::obtenerCopia() {
	if (this->superficie == NULL)
		return NULL;

	SDL_Surface* copia = NULL;
	copia = SDL_ConvertSurface(this->superficie, this->superficie->format, this->superficie->flags);
	if (copia == NULL)
		return NULL;

	return new Superficie(copia);
}

SDL_Surface* Superficie::obtenerCopia(SDL_Surface* otra) {
	if (otra == NULL)
		return NULL;

	return SDL_ConvertSurface(otra, otra->format, otra->flags);
}

bool Superficie::girar(int grados) {
	if (!superficie)
		return false;

	if (grados == 0 || grados == 360)
		return true;

	SDL_Surface* rotada = rotozoomSurface(superficie, grados, 0, SMOOTHING_ON);
	if (!rotada)
		return false;

	SDL_FreeSurface(superficie);
	superficie = rotada;

	alto = superficie->h;
	ancho = superficie->w;

	// TODO: revisar que pasa con la posicion de dibujado al ser rotada!

	return true;
}
