/*
 * ConfiguracionNivel.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#ifndef CONFIGURACIONNIVEL_H_
#define CONFIGURACIONNIVEL_H_

#include "Animacion.h"
#include "Automatico.h"
#include "Manual.h"
#include "VistaCuerpo.h"
#include <vector>

class ConfiguracionNivel{

	public:
		int alto;
		int ancho;
		std::vector<Automatico*> automaticos;
		Manual* manual;
		std::vector<Animacion*> animacionesAuto;
		Animacion* animacionManual;

		VistaCuerpo* vistaManual;
	public:
		ConfiguracionNivel();
};



#endif /* CONFIGURACIONNIVEL_H_ */
