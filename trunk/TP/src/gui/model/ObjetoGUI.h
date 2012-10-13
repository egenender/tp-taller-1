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
#include "../../model/Posicion.h"
#include <string>
using namespace std;

/*enum {
	ACTIVO,
	INACTIVO
};*/
#define ACTIVO 0
#define INACTIVO 1

class ObjetoGUI : public Observable {
	protected:
		SDL_Rect dimensiones;
		int estado;
		bool visible;
		string nombre; // Para identificarlo

	public:
		ObjetoGUI(int x, int y, int ancho, int alto);
		~ObjetoGUI();

	public:
		int obtenerX();
		int obtenerY();
		Posicion* obtenerPosicion();
		int obtenerAlto();
		int obtenerAncho();
		string obtenerNombre();
		int obtenerEstado();

		void setearX(int x);
		void setearY(int y);
		void setearNombre(string nombre);
		void setearEstado(int estado);

		void manejarEvento(SDL_Event* evento);
		void actualizar();
		void hacerVisible();
		void hacerInvisible();

		bool esVisible();
		bool mouseEncima(int mouseX, int mouseY);
};


#endif /* OBJETOGUI_H_ */
