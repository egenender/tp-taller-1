#ifndef PLATAFORMA_H_
#define PLATAFORMA_H_
#include "Cuerpo.h"
#include "Area.h"

class Plataforma : public Cuerpo{
public:
	Plataforma(const char* , Area*);
	virtual ~Plataforma();
	int obtenerEstado();	 //de observable
	void actualizar(float delta); 		//de cuerpo
};

#endif /* PLATAFORMA_H_ */
