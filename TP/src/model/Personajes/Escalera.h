#ifndef ESCALERA_H_
#define ESCALERA_H_
#include "../Cuerpo.h"
#include "../Area.h"
#include "../Actualizable.h"

class Manual;
class Plataforma;
class Barril;

class Escalera : public Cuerpo {
public:
	Escalera(const char*, Area*);
	virtual ~Escalera();
	int obtenerEstado();	 //de observable
	void actualizar(float delta); 		//de cuerpo


	void chocarCon(Actualizable*);
};

#endif /* ESCALERA_H_ */
