/*
 * ConfiguracionNivel.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#ifndef CONFIGURACIONNIVEL_H_
#define CONFIGURACIONNIVEL_H_

#include "Animacion.h"
#include "../model/Automatico.h"
#include "../model/Personajes/Manual.h"
#include "VistaCuerpo.h"
#include "VistaProtagonista.h"
#include "SDL/SDL_mixer.h"
#include "../model/Actualizable.h"
#include <vector>

class ConfiguracionNivel{

	public:
		int alto;
		int ancho;
		Superficie* superficieCargada;
		int piso;
		int players;

		Manual* manual;
		VistaProtagonista* vistaManual;
		std::vector<Actualizable*> actualizables;
		std::vector<VistaCuerpo*> vistas;
		Mix_Music* musica;
	public:
		ConfiguracionNivel();
};



#endif /* CONFIGURACIONNIVEL_H_ */
