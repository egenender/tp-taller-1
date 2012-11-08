/*
 * VistaCheckbox.h
 *
 *  Created on: 07/11/2012
 *      Author: nicolas
 */

#ifndef VISTACHECKBOX_H_
#define VISTACHECKBOX_H_

#include "../../view/Superficie.h"
#include "../../common/Observador.h"
#include <string>
using namespace std;

class VistaCheckbox : public Observador {
private:
	int x, y;
	int ancho, alto;
	bool habilitado;
	Superficie *box, *tilde, *actual;
	bool visible;

public:
	VistaCheckbox(string fondo, string tilde);
	~VistaCheckbox();
	virtual void actualizar(Observable* observable);
	virtual bool dibujar(SDL_Surface* display);
};

#endif /* VISTACHECKBOX_H_ */
