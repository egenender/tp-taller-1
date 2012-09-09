#ifndef ESTRATEGIAMONO_H_
#define ESTRATEGIAMONO_H_
#include "Personaje.h"

class EstrategiaMono: public EstrategiaMovimiento {
public:
	EstrategiaMono();
	virtual ~EstrategiaMono();
	void actuar(Personaje*);
};

#endif /* ESTRATEGIAMONO_H_ */
