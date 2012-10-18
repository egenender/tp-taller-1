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
#include "../model/Manual.h"
#include "VistaCuerpo.h"
#include "VistaProtagonista.h"
#include "../model/Actualizable.h"
#include <vector>

class ConfiguracionNivel{

	public:
		int alto;
		int ancho;
		Superficie* superficieCargada;

		int nivelElegido;

		Manual* manual;
		VistaProtagonista* vistaManual;
		std::vector<Actualizable*> actualizables;
		std::vector<VistaCuerpo*> vistas;
	public:
		ConfiguracionNivel(int );
};



#endif /* CONFIGURACIONNIVEL_H_ */
