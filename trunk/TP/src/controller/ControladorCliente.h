
#ifndef CONTROLADORCLIENTE_H_
#define CONTROLADORCLIENTE_H_
#include "Evento.h"
#include "../model/Observable.h"
#include "../model/Dummy.h"

class ControladorCliente {
private:
	unsigned int ID;
	//int ultimoEstado;
	Dummy* controlable;
	bool saltando, izquierda, derecha, quieto;
public:
	ControladorCliente(unsigned int id, Dummy*);
	virtual ~ControladorCliente();
	void manejarEvento(SDL_Event*);
private:
	void enviarStruct(int);
	//void revisarCambio(int);
};

#endif /* CONTROLADORCLIENTE_H_ */
