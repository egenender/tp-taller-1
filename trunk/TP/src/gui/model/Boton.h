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
	bool estaEncima, clickeado, sostenido;
	ManejadorBoton* manejador;
	string mensaje;

private:
	void inicializar();

public:
	Boton(int x, int y, int ancho, int alto,ManejadorBoton* m);
	~Boton();
	void manejarEvento(SDL_Event* evento);
	bool mouseEncima();
	bool esClickeado();
	string obtenerMensaje();
	void setearMensaje(string texto);

private:
	bool mouseEncima(int x, int y);
};


#endif /* BOTON_H_ */
