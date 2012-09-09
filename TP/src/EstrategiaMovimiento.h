#ifndef ESTRATEGIAMOVIMIENTO_H_
#define ESTRATEGIAMOVIMIENTO_H_
#include "Personaje.h"

class EstrategiaMovimiento {

public:
	//Deberia tener conocimiento del mundo, o algo asi
	EstrategiaMovimiento();
	virtual ~EstrategiaMovimiento();
	virtual void actuar(Personaje*) = 0;

	//Faltaria ver de agregar el actuar(Evento) o algo por el estilo
};

#endif /* ESTRATEGIAMOVIMIENTO_H_ */
