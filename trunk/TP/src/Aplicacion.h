#ifndef APLICACION_H
#define APLICACION_H

#include "SDL/SDL.h"
#include "Evento.h"

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

class Aplicacion: public Evento {
	private:
		bool FPS_ON; // Si mostramos los FPS o no
		bool corriendo; // Si esta corriendo
		SDL_Surface* display; // Aca se dibujan las cosas

	// Constructor:
	public:
		Aplicacion();

	// Metodos:
		int ejecutar();
		bool iniciar();
		void manejarEvento(SDL_Event* evento);
		void actualizar();
		void dibujar();
		void limpiar();
		void salir();

		void mostrarFPS(bool mostrar);
};

#endif
