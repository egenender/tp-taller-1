#ifndef AUTOMATICO_H_
#define AUTOMATICO_H_
#include "Area.h"
#include "Cuerpo.h"
#include "Actualizable.h"

class Manual;
class Plataforma;
class Escalera;
class Barril;

class Automatico: public Cuerpo{
private:
	int estado;

public:
	Automatico(const char*, Area*);
	virtual ~Automatico();

	void actualizar(float delta);
	int obtenerEstado();

	void chocarCon(Actualizable*);
};

#endif /* AUTOMATICO_H_ */
