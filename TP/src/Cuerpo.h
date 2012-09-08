/*
 * Cuerpo.h
 *
 *  Created on: 08/09/2012
 *      Author: martin
 */

#ifndef CUERPO_H_
#define CUERPO_H_
#include <stddef.h>

class Cuerpo {
protected:
	bool vivo; // esta vivo un cuerpo?
	Area* superficieOcupada;
	Animacion* animado; //lo mas sensato es que un cuerpo tenga una animacion -> preguntar si esto esta bien

public:
	Cuerpo(Area*, Animacion*);
	virtual ~Cuerpo();
	void mover(Posicion);
	void animar();
	bool estaVivo();
};

#endif /* CUERPO_H_ */
