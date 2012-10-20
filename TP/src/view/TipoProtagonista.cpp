/*
 * TipoProtagonista.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: genender
 */

#include "TipoProtagonista.h"


TipoProtagonista::TipoProtagonista (){
	ancho=0;
	alto=0;
	nombre=0;
	velocidad = 0;
	animacionPasivaProt=0;
	animacionActivaProt=0;
	animacionSaltaProt=0;

	disponible = true;
}

Manual* TipoProtagonista::CrearManual(const char* nombre,int x, int y, int velocidad){

	return new Manual(nombre,new Area(ancho,alto,new Posicion(x,y)),velocidad);

}
