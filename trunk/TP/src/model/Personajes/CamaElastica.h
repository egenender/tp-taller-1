#ifndef CAMA_H_
#define CAMA_H_
#include "../Cuerpo.h"
#include "../Area.h"
#include "../Actualizable.h"

class Manual;

class CamaElastica : public Cuerpo {

protected:
	int estado;
	bool chocaConManual;
public:
	CamaElastica(const char* , Area*);
	virtual ~CamaElastica();
	int obtenerEstado();	 //de observable
	virtual void actualizar(float delta); 		//de cuerpo
	unsigned int obtenerTipo();

	void chocarCon(Actualizable*);
	void chocarConManual(Manual*);

};

#endif
