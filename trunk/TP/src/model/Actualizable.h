#ifndef ACTUALIZABLE_H_
#define ACTUALIZABLE_H_
#include "Area.h"

class Manual;
class Escalera;
class Plataforma;

class Actualizable {
public:
	Actualizable();
	virtual ~Actualizable();
	virtual void actualizar(float delta)=0;
	virtual Area* obtenerArea()= 0;

	/*DOUBLE DISPATCHING*/
	virtual void chocarCon(Actualizable*)=0;
	virtual void chocarConManual(Manual*)=0;
	virtual void chocarConPlataforma(Plataforma*)=0;
	virtual void chocarConEscalera(Escalera*)=0;
//Los automaticos no haran nada
};

#endif /* ACTUALIZABLE_H_ */
