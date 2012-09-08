#ifndef ESTRATEGIAMOVIMIENTO_H_
#define ESTRATEGIAMOVIMIENTO_H_
#include "Personaje.h"

class EstrategiaMovimiento {
protected:
	Personaje* personaje;
public:
	EstrategiaMovimiento(Personaje*);
	EstrategiaMovimiento();
	void asignarPersonaje(Personaje*);
	virtual ~EstrategiaMovimiento();
	virtual void actuar() = 0;

	//Faltaria ver de agregar el actuar(Evento) o algo por el estilo
};

#endif /* ESTRATEGIAMOVIMIENTO_H_ */
