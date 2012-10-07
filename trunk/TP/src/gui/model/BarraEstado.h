/*
 * BarraEstado.h
 *
 *  Created on: 06/10/2012
 *      Author: nicolas
 */

#ifndef BARRAESTADO_H_
#define BARRAESTADO_H_

#include "ObjetoGUI.h"
#include <string>
using namespace std;

class BarraEstado : public ObjetoGUI {
private:
	string mensaje;

public:
	BarraEstado(int x, int y, int ancho, int alto);
	~BarraEstado();
	void setearMensaje(string mensaje);
	string obtenerMensaje();
};


#endif /* BARRAESTADO_H_ */
