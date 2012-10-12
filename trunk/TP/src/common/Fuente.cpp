#include "Fuente.h"

Fuente Fuente::instancia;

Fuente::Fuente() {
	font = NULL;
	size = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
}

bool Fuente::inicializar() {
	 if(TTF_Init() == -1)
		 return false;

	 size = 18;

	 font = TTF_OpenFont("src/gui/resources/arial.ttf", size);
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

int Fuente::obtenerTamanio() {
	return size;
}

Fuente* Fuente::obtenerInstancia() {
	return &instancia;
}
