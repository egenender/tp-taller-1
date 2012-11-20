/*
 * SonInvencibles.h
 *
 *  Created on: Nov 20, 2012
 *      Author: genender
 */

#ifndef SONINVENCIBLES_H_
#define SONINVENCIBLES_H_

#include "../Observable.h"
#include "../Dummy.h"

class SonInvencibles:public Observable {
public:
	SonInvencibles();
	virtual ~SonInvencibles();
	bool mataAlContacto();

	void agregarDummy(Dummy*);

	int obtenerEstado();
	int obtenerAncho();
	int obtenerAlto();
	Posicion* obtenerPosicion();

private:
	bool invencible;
	std::vector<Dummy*>* dummies;
};

#endif /* SONINVENCIBLES_H_ */
