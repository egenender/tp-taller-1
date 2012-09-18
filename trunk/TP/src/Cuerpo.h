#ifndef CUERPO_H_
#define CUERPO_H_
#include <stddef.h>

#include "Area.h"
#include <stdbool.h>
#include "lista.h"

//habria que ver que otros metodos tiene, alguno que tenga que ser definido mas abajo..

class Cuerpo {
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
	//void agregarObservador(Observador* observer); Lo dejo comentado para cuando lo hagamos
	virtual void actualizar()=0; //o que reciba o devuelva algo ?
	const char* getNombre();
};

#endif /* CUERPO_H_ */