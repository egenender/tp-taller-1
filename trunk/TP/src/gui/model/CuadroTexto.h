/*
 * CuadroTexto.h
 *
 *  Created on: 12/10/2012
 *      Author: nicolas
 */

#ifndef CUADROTEXTO_H_
#define CUADROTEXTO_H_

#include "ObjetoGUI.h"
#include <string>
using namespace std;

class CuadroTexto : public ObjetoGUI {
private:
	string mensajeEscrito;
	unsigned int maximosCaracteres;

private:
	void inicializar();
	bool mouseEncima(int x, int y);

public:
	CuadroTexto(int x, int y, int ancho, int alto, unsigned int cantCaracteres);
	~CuadroTexto();
	string obtenerMensaje();
	void manejarEvento(SDL_Event* evento);
};


#endif /* CUADROTEXTO_H_ */