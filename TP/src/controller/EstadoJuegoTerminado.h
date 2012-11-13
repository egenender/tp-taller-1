#ifndef ESTADOJUEGOTERMINADO_H_
#define ESTADOJUEGOTERMINADO_H_

#include "Estado.h"
#include "../view/Superficie.h"

class EstadoJuegoTerminado: public Estado {
	Superficie* fondo;
	Superficie* ganador;
public:
	EstadoJuegoTerminado();
	virtual ~EstadoJuegoTerminado();
	void manejarEvento(SDL_Event* evento);
	void iniciar();
	void terminar();
	void actualizar(float delta);
	void dibujar(SDL_Surface* display);

};

#endif /* ESTADOJUEGOTERMINADO_H_ */
