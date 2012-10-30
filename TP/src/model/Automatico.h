#ifndef AUTOMATICO_H_
#define AUTOMATICO_H_
#include "Area.h"
#include "Cuerpo.h"
#include "Actualizable.h"

class Manual;
class Plataforma;
class Escalera;

class Automatico: public Cuerpo{
private:
	int estado;

public:
	Automatico(const char*, Area*);
	virtual ~Automatico();

	void actualizar(float delta);
	int obtenerEstado();

	void chocarCon(Actualizable*);
	void chocarConManual(Manual*);
	void chocarConPlataforma(Plataforma*);
	void chocarConEscalera(Escalera*);
};

#endif /* AUTOMATICO_H_ */
