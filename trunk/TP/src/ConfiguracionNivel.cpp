/*
 * ConfiguracionNivel.cpp
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "ConfiguracionNivel.h"


ConfiguracionNivel::ConfiguracionNivel(){

	ancho=alto=0;
	automaticos=vector<Automatico*>();
	manual=0;
	animacionesAuto=vector<Animacion*>();
	animacionManual=0;
	vistaManual=0;

}

