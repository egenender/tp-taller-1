
#ifndef CONTROLADORCLIENTE_H_
#define CONTROLADORCLIENTE_H_
#include "Evento.h"
#include "../model/cola.h"

class ControladorCliente {
private:
	cola_t* cola_salida;
	unsigned int ID;
	bool cambioReciente;
public:
	ControladorCliente(cola_t*, unsigned int id);
	virtual ~ControladorCliente();
	void manejarEvento(SDL_Event*);
};

#endif /* CONTROLADORCLIENTE_H_ */
