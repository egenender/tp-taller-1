/*
 * ConfiguracionNivel.cpp
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "ConfiguracionNivel.h"


ConfiguracionNivel::ConfiguracionNivel(){
	ancho=alto=0;
	actualizables=vector<Actualizable*>();
	manual=0;
	vistaManual=0;
	vistas=vector<VistaCuerpo*>();
	piso = 0;
}

