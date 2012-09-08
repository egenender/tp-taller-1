#ifndef APLICACION_H
#define APLICACION_H

#include "SDL/SDL.h"
#include "Evento.h"

#define ANCHO_VENTANA 640
#define ALTO_VENTANA 480

class Aplicacion: public Evento {
	private:
		bool corriendo; // si esta corriendo
		SDL_Surface* display; // Aca se dibuja todo

	// Constructor:
	public:
		Aplicacion();

	// Metodos:
		int ejecutar();
		bool iniciar();
		void manejarEvento(SDL_Event* evento);
		void salir();
		void actualizar();
		void dibujar();
		void limpiar();
};

#endif
