/*
 * VistaMusical.h
 *
 *  Created on: 18/11/2012
 *      Author: nicolas
 */

#ifndef VISTAMUSICAL_H_
#define VISTAMUSICAL_H_

#include "VistaCuerpo.h"
#include "SDL/SDL_mixer.h"

class VistaMusical : public VistaCuerpo {
	private:
		Mix_Music* musicaNivel, *musicaInvensible, *musicaActual;
		bool invensibilidad;

	private:
		void iniciarVista();
		bool reproducirMusica();

	public:
		VistaMusical();
		void actualizar(Observable* observable);
		bool dibujar(SDL_Surface* display, int xCamara, int yCamara);
		~VistaMusical();
};

#endif /* VISTAMUSICAL_H_ */
