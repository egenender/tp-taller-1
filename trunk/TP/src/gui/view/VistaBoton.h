/*
 * VistaBoton.h
 *
 *  Created on: 30/09/2012
 *      Author: nicolas
 */

#ifndef VISTABOTON_H_
#define VISTABOTON_H_

#include "../../view/Superficie.h"
#include "../../common/Observador.h"
#include <string>
using namespace std;

class VistaBoton : public Observador {
private:
	int x, y;
	Superficie *activo, *inactivo, *actual;

public:
	VistaBoton(string, string);
	~VistaBoton();
	virtual void actualizar(Observable* observable);
	virtual bool dibujar(SDL_Surface* display);
};


#endif /* VISTABOTON_H_ */
