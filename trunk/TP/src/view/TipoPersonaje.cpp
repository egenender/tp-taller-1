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
	animacionesActiva= vector<Animacion*>();
	periodos= vector<int>();
}


Automatico* TipoPersonaje::CrearAutomatico(const char* nombre,int x, int y){

	return new Automatico(nombre,new Area(ancho, alto,new Posicion(x,y)));

}
