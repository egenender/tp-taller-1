#ifndef ESCALERA_H_
#define ESCALERA_H_
#include "Cuerpo.h"
#include "Area.h"

class Escalera : public Cuerpo {
public:
	Escalera(const char*, Area*);
	virtual ~Escalera();
	int obtenerEstado();	 //de observable
	void actualizar(float delta); 		//de cuerpo
};

#endif /* ESCALERA_H_ */
