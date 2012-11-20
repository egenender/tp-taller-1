#ifndef ESTADOJUEGOTERMINADO_H_
#define ESTADOJUEGOTERMINADO_H_

#include "Estado.h"
#include "../view/Superficie.h"
#include <vector>
#include "../model/Timer.h"
#define TIEMPO_GANADOR 1

class EstadoJuegoTerminado: public Estado {
private:
	Superficie* fondo;
	std::vector<Superficie*>* ganadores;
	static EstadoJuegoTerminado instancia;
	Superficie* ganador;
	unsigned int actual;
	Timer* timer;
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
