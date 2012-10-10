/*
 * Boton.h
 *
 *  Created on: 30/09/2012
 *      Author: nicolas
 */

#ifndef BOTON_H_
#define BOTON_H_

#include "ObjetoGUI.h"
#include "ManejadorBoton.h"

class Boton : public ObjetoGUI {
private:
	bool estaEncima, clickeado, sostenido;
	ManejadorBoton* manejador;

public:
	Boton(int x, int y, int ancho, int alto,ManejadorBoton* m);
	~Boton();
	void manejarEvento(SDL_Event* evento);
	bool mouseEncima();
	bool esClickeado();

private:
	bool mouseEncima(int x, int y);
};


#endif /* BOTON_H_ */
