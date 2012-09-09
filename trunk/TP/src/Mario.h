#ifndef MARIO_H_
#define MARIO_H_
#include "EstrategiaMovimiento.h"
#include "Personaje.h"
#include "Animacion.h"
#include "Area.h"

class Mario: public Personaje {
public:
	Mario(Area*, Animacion*);
	Mario(Area*, Animacion*, EstrategiaMovimiento*);
	virtual ~Mario();

	void moverAIzquierda();
	void moverADerecha();
	void atacar();
	void saltar();
	void especial();

private:
	void moverHaciaCostados(int);
};

#endif /* MARIO_H_ */
