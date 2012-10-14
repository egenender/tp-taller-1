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
#include <string>
using namespace std;

class Boton : public ObjetoGUI {
private:
	bool estaEncima, clickeado, presionado;
	ManejadorBoton* manejador;
	string mensaje;

private:
	void inicializar();

public:
	Boton(int x, int y, int ancho, int alto,ManejadorBoton* m);
	~Boton();

	void setearPresionado(bool flag);
	void setearMensaje(string texto);
	string obtenerMensaje();

	bool esPresionado();
	bool esClickeado();
	bool mouseEstaEncima(); // FIXME: haria falta esto?

	void manejarEvento(SDL_Event* evento);
};

#endif /* BOTON_H_ */
