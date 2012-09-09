#ifndef ESTRATEGIAMARIO_H_
#define ESTRATEGIAMARIO_H_
#include "EstrategiaMovimiento.h"
#include "Personaje.h"

class EstrategiaMario: public EstrategiaMovimiento {
public:
	EstrategiaMario();
	virtual ~EstrategiaMario();
	void actuar(Personaje*);
};

#endif /* ESTRATEGIAMARIO_H_ */
