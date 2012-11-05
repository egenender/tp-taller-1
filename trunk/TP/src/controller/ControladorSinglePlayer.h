#ifndef CONTROLADORSINGLEPLAYER_H_
#define CONTROLADORSINGLEPLAYER_H_
#include "../model/Personajes/Manual.h"
#include "Controlador.h"
#include "Evento.h"

//Dejo comentado todo lo relacionado con usar el Patrón Singleton

class ControladorSinglePlayer : public Controlador{
private:
	Manual* principal;
public:
	virtual ~ControladorSinglePlayer();
	void manejarEvento(SDL_Event*);

	ControladorSinglePlayer(Manual*);
};

#endif /* CONTROLADOR_H_ */
