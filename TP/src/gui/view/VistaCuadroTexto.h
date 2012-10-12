/*
 * VistaCuadroTexto.h
 *
 *  Created on: 12/10/2012
 *      Author: nicolas
 */

#ifndef VISTACUADROTEXTO_H_
#define VISTACUADROTEXTO_H_

#include "../../view/Superficie.h"
#include "SDL/SDL_ttf.h"
#include "../../common/Observador.h"
#include <string>
using namespace std;

class VistaCuadroTexto : public Observador {
private:
	int x, y, ancho, alto;
	string mensajeActual;
	SDL_Surface* mensajeAMostrar;
	Superficie* cuadroSinFoco;
	Superficie* cuadroConFoco;
	Superficie* imagenActual;
private:
	void inicializar();

public:
	VistaCuadroTexto();
	~VistaCuadroTexto();
	virtual void actualizar(Observable* observable);
	virtual bool dibujar(SDL_Surface* display);
};



#endif /* VISTACUADROTEXTO_H_ */
