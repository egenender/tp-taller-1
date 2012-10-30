#ifndef ACTUALIZABLE_H_
#define ACTUALIZABLE_H_
#include "Area.h"

class Actualizable {
public:
	Actualizable();
	virtual ~Actualizable();
	virtual void actualizar(float delta)=0;
	virtual Area* obtenerArea()= 0;
};

#endif /* ACTUALIZABLE_H_ */
