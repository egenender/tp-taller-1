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

enum{
	TODO = 0,
	NUMEROS,
	LETRAS,
	NUMEROSYPUNTO
};

class CuadroTexto : public ObjetoGUI {
private:
	string mensajeEscrito;
	unsigned int maximosCaracteres;
	bool permitido;
	int validar;

private:
	void inicializar();

public:
	CuadroTexto(int x, int y, int ancho, int alto, unsigned int cantCaracteres);
	CuadroTexto(int x, int y, int ancho, int alto, unsigned int cantCaracteres, int posibles);
	CuadroTexto(int x, int y, int ancho, int alto, unsigned int cantCaracteres, int posibles, string inicial);
	~CuadroTexto();
	string obtenerMensaje();
	void manejarEvento(SDL_Event* evento);
private:
	bool caracterValido(SDL_Event* evento);
};


#endif /* CUADROTEXTO_H_ */
