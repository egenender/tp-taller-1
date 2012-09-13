#ifndef AUTOMATICO_H_
#define AUTOMATICO_H_
#include "Area.h"
#include "Cuerpo.h"

class Automatico: public Cuerpo{

public:
	Automatico(const char*, Area*);
	virtual ~Automatico();

	void actualizar();
};

#endif /* AUTOMATICO_H_ */
