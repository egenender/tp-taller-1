#ifndef ESCALERA_H_
#define ESCALERA_H_
#include "Cuerpo.h"
#include "Area.h"
#include "Actualizable.h"

class Manual;
class Plataforma;

class Escalera : public Cuerpo {
public:
	Escalera(const char*, Area*);
	virtual ~Escalera();
	int obtenerEstado();	 //de observable
	void actualizar(float delta); 		//de cuerpo


	void chocarCon(Actualizable*);
	void chocarConManual(Manual*);
	void chocarConPlataforma(Plataforma*);
	void chocarConEscalera(Escalera*);
};

#endif /* ESCALERA_H_ */
