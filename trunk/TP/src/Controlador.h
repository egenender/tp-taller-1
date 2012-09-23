#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_
#include "Manual.h"
#include "Evento.h"

//Dejo comentado todo lo relacionado con usar el Patrón Singleton

class Controlador {
private:
	/*static Controlador* instancia;*/
public:
	virtual ~Controlador();
	void manejarEvento(SDL_Event*, Manual*);
	/*Controlador* getInstance();*/
/*private:*/
	Controlador();
};

#endif /* CONTROLADOR_H_ */
