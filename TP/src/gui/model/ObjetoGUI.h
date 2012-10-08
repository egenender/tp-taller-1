/*
 * ObjetoGUI.h
 *
 *  Created on: 06/10/2012
 *      Author: nicolas
 */

#ifndef OBJETOGUI_H_
#define OBJETOGUI_H_

#include "SDL/SDL.h"
#include "../../model/Observable.h"

enum {
	ACTIVO = 0,
	INACTIVO
};

class ObjetoGUI : public Observable {
	protected:
		SDL_Rect dimensiones;
		int estado;

	public:
		ObjetoGUI(int x, int y, int ancho, int alto);
		~ObjetoGUI();

	public:
		void manejarEvento(SDL_Event* evento);
		int obtenerEstado();
		void actualizar();
		int obtenerY();
		int obtenerX();
		void setearEstado(int estado);
		void activar();
		void desactivar();
};


#endif /* OBJETOGUI_H_ */
