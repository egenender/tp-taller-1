/*
 * TipoPersonaje.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "Animacion.h"


class TipoPersonaje {

	public:
		int ancho;
		int alto;
		Animacion* animacionPasiva;
		Animacion* animacionActiva;

	public:
		TipoPersonaje();
};
