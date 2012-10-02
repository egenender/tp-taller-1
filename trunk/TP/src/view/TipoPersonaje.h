/*
 * TipoPersonaje.h
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "Animacion.h"
#include "../model/Manual.h"
#include "../model/Automatico.h"

class TipoPersonaje {

	public:
		int ancho;
		int alto;
		const char* nombre;
		Animacion* animacionPasivaProt;
		Animacion* animacionActivaProt;
		vector<Animacion*> animacionesActiva;
		vector<int> periodos;

	public:
		TipoPersonaje();
		Manual* CrearManual(const char*,int, int,int);
		Automatico* CrearAutomatico(const char*,int, int);

};
