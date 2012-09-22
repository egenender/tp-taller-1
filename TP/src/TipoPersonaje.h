/*
 * TipoPersonaje.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "Animacion.h"
#include "Manual.h"
#include "Automatico.h"

class TipoPersonaje {

	public:
		int ancho;
		int alto;
		const char* nombre;
		Animacion* animacionPasiva;
		Animacion* animacionActiva;

	public:
		TipoPersonaje();
		Manual* CrearManual(const char*,int, int,int);
		Automatico* CrearAutomatico(const char*,int, int);

};
