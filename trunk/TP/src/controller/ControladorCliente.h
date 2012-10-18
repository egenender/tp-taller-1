
#ifndef CONTROLADORCLIENTE_H_
#define CONTROLADORCLIENTE_H_
#include "Evento.h"
#include "../model/cola.h"
#include "../model/Observable.h"

class ControladorCliente {
private:
	cola_t* cola_salida;
	unsigned int ID;
	int ultimoEstado;
public:
	ControladorCliente(cola_t*, unsigned int id);
	virtual ~ControladorCliente();
	void manejarEvento(SDL_Event*);
private:
	void enviarStruct(int);
};

#endif /* CONTROLADORCLIENTE_H_ */
