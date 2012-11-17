#ifndef VISTAVARIOS_H_
#define VISTAVARIOS_H_

#include "VistaAnimada.h"
#include "Animacion.h"

class VistaVarios: public VistaAnimada{
public:
	VistaVarios();
	virtual ~VistaVarios();
	void actualizar(Observable* observable);
	void reiniciar();

	bool invisible;

	void agregarEstadoSoportado(int, Animacion*);
	void agregarEstadoSoportadoEInverso(int,int, Animacion*);
	bool dibujar(SDL_Surface* display, int xCamara, int yCamara);
};

#endif /* VISTAVARIOS_H_ */
