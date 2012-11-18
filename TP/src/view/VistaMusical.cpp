#include "VistaMusical.h"
#include "../model/Personajes/Manual.h"
#include "../controller/GestorConfiguraciones.h" //FIXME

void VistaMusical::iniciarVista() {
	musicaNivel = musicaInvensible = musicaActual = NULL;
	invensibilidad = false;
}

VistaMusical::~VistaMusical() {
	Mix_HaltMusic();
	if (musicaNivel) {
		Mix_FreeMusic(musicaNivel);
		musicaNivel = NULL;
	}
	if (musicaInvensible) {
		Mix_FreeMusic(musicaInvensible);
		musicaInvensible = NULL;
	}

	musicaActual = NULL;
}

VistaMusical::VistaMusical() {
	iniciarVista();

	musicaNivel =  GestorConfiguraciones::getInstance()->ObtenerMusica();
	musicaInvensible = Mix_LoadMUS("./src/resources/cuerpos/invensible.ogg");
	musicaActual = musicaNivel;

	invensibilidad = false;
}

bool VistaMusical::dibujar(SDL_Surface* display, int xCamara, int yCamara) {
	return reproducirMusica();
}

bool VistaMusical::reproducirMusica() {
	if (musicaActual == NULL) {
		return false;
	}

	if (invensibilidad && musicaActual == musicaNivel) {
		Mix_HaltMusic();
		musicaActual = musicaInvensible;
	}

	else if (!invensibilidad && musicaActual == musicaInvensible){
		Mix_HaltMusic();
		musicaActual = musicaNivel;
	}

	// Si hay musicaActual y NO esta tocando:
	if (musicaActual && (Mix_PlayingMusic() == 0)) {
		if (Mix_PlayMusic(musicaActual, -1) == -1) {
			printf("No se puede reproducir la musica\n");
			printf("%s\n", Mix_GetError());
			return false;
		}
	}

	return true;
}

void VistaMusical::actualizar(Observable* observable) {
	invensibilidad = observable->mataAlContacto();
}
