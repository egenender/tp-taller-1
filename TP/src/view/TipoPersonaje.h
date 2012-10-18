/*
 * TipoPersonaje.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "Animacion.h"
#include "../model/Automatico.h"

class TipoPersonaje {

	public:
		int ancho;
		int alto;
		const char* nombre;
		Animacion* animacionPasiva;
		vector<Animacion*> animacionesActiva;
		vector<int> periodos;

	public:
		TipoPersonaje();
		Automatico* CrearAutomatico(const char*,int, int);

};
