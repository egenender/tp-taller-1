#ifndef APLICACION_H
#define APLICACION_H

#include "../gui/model/Ventana.h"
#include "../controller/Evento.h"

class Aplicacion: public Evento {
	private:
		bool FPS_ON; // Si mostramos los FPS o no
		bool corriendo; // Si esta corriendo
		Ventana* ventana;

	// Constructor:
	public:
		Aplicacion();

	// Metodos:
		int ejecutar();
		bool iniciar();
		void manejarEvento(SDL_Event* evento);
		void actualizar(float delta);
		void dibujar();
		void limpiar();
		void salir();

		void mostrarFPS(bool mostrar);
};

#endif
