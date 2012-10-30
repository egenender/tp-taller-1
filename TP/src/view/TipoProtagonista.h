/*
 * TipoProtagonista.h
 *
 *  Created on: Oct 18, 2012
 *      Author: genender
 */

#ifndef TIPOPROTAGONISTA_H_
#define TIPOPROTAGONISTA_H_

#include "Animacion.h"
#include "../model/Manual.h"

class TipoProtagonista {
public:
	TipoProtagonista();
	bool disponible;

public:
	int ancho;
	int alto;
	int velocidad;
	int salto;
	const char* nombre;
	Animacion* animacionPasivaProt;
	Animacion* animacionActivaProt;
	Animacion* animacionSaltaProt;

public:
	//Manual* CrearManual(const char*,int, int,int);
};


#endif /* TIPOPROTAGONISTA_H_ */
