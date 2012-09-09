#ifndef PRINCESA_H_
#define PRINCESA_H_
#include "Personaje.h"
#include "Area.h"
#include "Animacion.h"

class Princesa:public Personaje {
public:
	Princesa(Area*, Animacion*);
	Princesa(Area*, Animacion*, EstrategiaMovimiento*);
	virtual ~Princesa();

	void moverAIzquierda();
	void moverADerecha();
	void atacar();
	void saltar();
	void especial();
};

#endif /* PRINCESA_H_ */
