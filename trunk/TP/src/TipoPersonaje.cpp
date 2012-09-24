/*
 * TipoPersonaje.cpp
 *
 *  Created on: Sep 21, 2012
 *      Author: juaqi
 */

#include "TipoPersonaje.h"

TipoPersonaje::TipoPersonaje (){
	ancho=0;
	alto=0;
	nombre=0;
	animacionPasiva=0;
	animacionActiva=0;
	periodo=0;
}

Manual* TipoPersonaje::CrearManual(const char* nombre,int x, int y, int velocidad){

	return new Manual(nombre,new Area(alto,ancho,new Posicion(x,y)),velocidad);

}
Automatico* TipoPersonaje::CrearAutomatico(const char* nombre,int x, int y){

	return new Automatico(nombre,new Area(alto,ancho,new Posicion(x,y)));

}
