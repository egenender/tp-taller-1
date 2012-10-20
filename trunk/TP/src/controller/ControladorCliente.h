
#ifndef CONTROLADORCLIENTE_H_
#define CONTROLADORCLIENTE_H_
#include "Evento.h"
#include "../model/Observable.h"

class ControladorCliente {
private:
	unsigned int ID;
	int ultimoEstado;
public:
	ControladorCliente(unsigned int id);
	virtual ~ControladorCliente();
	void manejarEvento(SDL_Event*);
private:
	void enviarStruct(int);
	void revisarCambio(int);
};

#endif /* CONTROLADORCLIENTE_H_ */
