#ifndef MONO_H_
#define MONO_H_
#include "EstrategiaMovimiento.h"
#include "Personaje.h"
#include "Animacion.h"
#include "Area.h"

class Mono: public Personaje{
private:
	//fabrica de cosas para tirar
public:
	Mono(Area*, Animacion*, EstrategiaMovimiento*);
	virtual ~Mono();

	void moverAIzquierda();
	void moverADerecha();
	void atacar();
	void saltar();
	void especial();
};

#endif /* MONO_H_ */
