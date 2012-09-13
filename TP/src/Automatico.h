#ifndef AUTOMATICO_H_
#define AUTOMATICO_H_
#include "Area.h"
#include "Cuerpo.h"

class Automatico: public Cuerpo{
public:
	Automatico(Area*);
	virtual ~Automatico();

};

#endif /* AUTOMATICO_H_ */
