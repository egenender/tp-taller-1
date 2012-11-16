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
	Area* superficieDeColision;
	Posicion* posAnterior;
	unsigned int id;
	unsigned int tipo;
	friend class PlataformaMovil;
public:
	Cuerpo(const char*, Area*);
	virtual ~Cuerpo();
	Posicion* obtenerPosicion();
	int obtenerAncho();
	int obtenerAlto();
	void moverA(Posicion*);
	//virtual void actualizar(float delta)=0; //o que reciba o devuelva algo ?
	const char* obtenerNombre();
	Area* obtenerArea();
	Posicion* obtenerPosicionAnterior();

	unsigned int obtenerID();
	unsigned int obtenerTipo();

protected:
	void trasladar(int, int, bool);
};

#endif /* CUERPO_H_ */
