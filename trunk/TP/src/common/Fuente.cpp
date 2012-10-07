#include "Fuente.h"

Fuente Fuente::instancia;

Fuente::Fuente() {
	font = NULL;
	color.r = 255;
	color.g = 255;
	color.b = 255;
}

bool Fuente::inicializar() {
	 if(TTF_Init() == -1)
		 return false;

	 font = TTF_OpenFont("src/common/lazy.ttf", 28);
	 if (font == NULL) {
		 printf("%s\n", TTF_GetError());
		 return false;
	 }
	 return true;
}

void Fuente::terminar() {
	if (font)
		TTF_CloseFont(font);

	TTF_Quit();
}

TTF_Font* Fuente::obtenerFuente() {
	return font;
}

SDL_Color Fuente::obtenerColor() {
	return color;
}


Fuente* Fuente::obtenerInstancia() {
	return &instancia;
}
