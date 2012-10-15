/*
 * Ventana.h
 *
 *  Created on: 14/10/2012
 *      Author: nicolas
 */

#ifndef VENTANA_H_
#define VENTANA_H_

#include "../../view/Superficie.h"

#define ANCHO_ESTANDARD 800
#define ALTO_ESTANDARD 600

class Ventana {
private:
	SDL_Surface* screen;
	Superficie* superficieDibujable;
	bool ventanaOK;
	bool modoVentana;
	int ancho,alto,anchoOriginal,altoOriginal;

private:
	void inicializar();

public:
	Ventana();
	Ventana(int ancho, int alto);
	~Ventana();
	void manejarEvento(SDL_Event* evento);
	void redimencionar(int ancho, int alto);
	void pantallaCompleta();
	bool error();
	void setearTitulo(string titulo);
	Superficie* obtenerSuperficieDibujable();
	void limpiarPantalla();
	void dibujar();
	void volverALasDimensionesDeCreacion();
};


#endif /* VENTANA_H_ */
