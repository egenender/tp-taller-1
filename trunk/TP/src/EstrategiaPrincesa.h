#ifndef ESTRATEGIAPRINCESA_H_
#define ESTRATEGIAPRINCESA_H_
#include "EstrategiaMovimiento.h"
#include "Personaje.h"

class EstrategiaPrincesa:public EstrategiaMovimiento {
public:
	EstrategiaPrincesa();
	virtual ~EstrategiaPrincesa();
	void actuar(Personaje*);
};

#endif /* ESTRATEGIAPRINCESA_H_ */
