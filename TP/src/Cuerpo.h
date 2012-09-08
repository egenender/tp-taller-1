#ifndef CUERPO_H_
#define CUERPO_H_
#include <stddef.h>

#include "Area.h"
#include "Animacion.h"
#include <stdbool.h>

class Cuerpo {
protected:
	bool vivo; // esta vivo un cuerpo?
	Area* superficieOcupada;
	Animacion* animado; //lo mas sensato es que un cuerpo tenga una animacion -> preguntar si esto esta bien

public:
	Cuerpo(Area*, Animacion*);
	virtual ~Cuerpo();
	virtual void mover(Posicion)=0; //Cuerpo es abstracto
	void animar();
	bool estaVivo();
};

#endif /* CUERPO_H_ */
