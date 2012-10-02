/*
 * ConfiguracionNivel.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#ifndef CONFIGURACIONNIVEL_H_
#define CONFIGURACIONNIVEL_H_

#include "view/Animacion.h"
#include "model/Automatico.h"
#include "model/Manual.h"
#include "view/VistaCuerpo.h"
#include "view/VistaProtagonista.h"
#include <vector>

class ConfiguracionNivel{

	public:
		int alto;
		int ancho;
		Manual* manual;
		VistaProtagonista* vistaManual;
		std::vector<Cuerpo*> cuerpos;
		std::vector<VistaCuerpo*> vistas;
	public:
		ConfiguracionNivel();
};



#endif /* CONFIGURACIONNIVEL_H_ */
