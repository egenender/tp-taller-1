#ifndef CAMA_H_
#define CAMA_H_
#include "../Cuerpo.h"
#include "../Area.h"
#include "../Actualizable.h"

class CamaElastica : public Cuerpo {

protected:
	int estado;
public:
	CamaElastica(const char* , Area*);
	virtual ~CamaElastica();
	int obtenerEstado();	 //de observable
	virtual void actualizar(float delta); 		//de cuerpo

	void chocarCon(Actualizable*);

};

#endif
