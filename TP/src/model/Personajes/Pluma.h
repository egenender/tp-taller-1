#ifndef PLUMA_H_
#define PLUMA_H_
#include "../Fabricas/FabricaActualizable.h"

#include "../Cuerpo.h"
#include "../Area.h"
#include "../Actualizable.h"

class Pluma : public Cuerpo {
protected:
	int estado;
public:
	Pluma(const char*, Area*);
	virtual ~Pluma();
	int obtenerEstado();	 //de observable
	virtual void actualizar(float delta); 		//de cuerpo

	void chocarCon(Actualizable*);

};

#endif /* PLUMA_H_ */
