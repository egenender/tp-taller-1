#ifndef CUERPO_H_
#define CUERPO_H_
#include <stddef.h>

#include "Area.h"
#include <stdbool.h>
#include "lista.h"
#include "Observable.h"
#include "Actualizable.h"

//habria que ver que otros metodos tiene, alguno que tenga que ser definido mas abajo..

class Cuerpo: public Observable, public Actualizable {
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
	//virtual void actualizar(float delta)=0; //o que reciba o devuelva algo ?
	const char* obtenerNombre();
};

#endif /* CUERPO_H_ */