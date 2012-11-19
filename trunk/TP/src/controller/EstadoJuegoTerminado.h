#ifndef ESTADOJUEGOTERMINADO_H_
#define ESTADOJUEGOTERMINADO_H_

#include "Estado.h"
#include "../view/Superficie.h"

class EstadoJuegoTerminado: public Estado {
private:
	Superficie* fondo;
	Superficie* ganador;
	static EstadoJuegoTerminado instancia;
private:
	EstadoJuegoTerminado();
public:
	virtual ~EstadoJuegoTerminado();
	void manejarEvento(SDL_Event* evento);
	void iniciar();
	void terminar();
	void actualizar(float delta);
	void dibujar(SDL_Surface* display);
	static EstadoJuegoTerminado* obtenerInstancia();

};

#endif /* ESTADOJUEGOTERMINADO_H_ */
