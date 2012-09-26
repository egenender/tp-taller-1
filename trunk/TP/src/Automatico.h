#ifndef AUTOMATICO_H_
#define AUTOMATICO_H_
#include "Area.h"
#include "Cuerpo.h"
#define QUIETO 0

class Automatico: public Cuerpo{
private:
	int estado;

public:
	Automatico(const char*, Area*);
	virtual ~Automatico();

	void actualizar(float delta);
	int obtenerEstado();
};

#endif /* AUTOMATICO_H_ */
