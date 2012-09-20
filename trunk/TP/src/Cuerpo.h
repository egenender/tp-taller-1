#ifndef CUERPO_H_
#define CUERPO_H_
#include <stddef.h>

#include "Area.h"
#include <stdbool.h>
#include "lista.h"
#include "Observable.h"

//habria que ver que otros metodos tiene, alguno que tenga que ser definido mas abajo..

class Cuerpo: public Observable {
protected:
	Area* superficieOcupada;
	const char* nombre;

public:
	Cuerpo(const char*, Area*);
	virtual ~Cuerpo();
	Posicion* obtenerPosicion();
	int obtenerAncho();
	int obtenerAlto();
	void moverA(Posicion*);
	virtual void actualizar()=0; //o que reciba o devuelva algo ?
	const char* obtenerNombre();
};

#endif /* CUERPO_H_ */
