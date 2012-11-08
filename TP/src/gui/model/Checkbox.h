/*
 * Checkbox.h
 *
 *  Created on: 07/11/2012
 *      Author: nicolas
 */

#ifndef CHECKBOX_H_
#define CHECKBOX_H_

#include "ObjetoGUI.h"
#include "ManejadorBoton.h"

class Checkbox : public ObjetoGUI {

private:
	bool estaEncima;
	bool checked, pressed;
	ManejadorBoton* manejador;

private:
	void inicializar();

public:
	Checkbox(int x, int y, int ancho, int alto,ManejadorBoton* m);
	~Checkbox();

	bool esCheckeado();
	void setearCheckeado();
	bool mouseEstaEncima(); // FIXME: haria falta esto?

	void manejarEvento(SDL_Event* evento);
};


#endif /* CHECKBOX_H_ */
