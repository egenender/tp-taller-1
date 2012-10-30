#ifndef DUMMY_H_
#define DUMMY_H_
#include <stdbool.h>
#include <stddef.h>
#include "Observable.h"
#include "Area.h"


class Dummy : public Observable{
private:
	int estado;
	unsigned int ID;
	Posicion* pos;
	int ancho, alto;
public:
	Dummy(unsigned int,Posicion*, int ancho, int alto);

	virtual ~Dummy();
	void setXY(int,int);
	void setEstado(int);
	int obtenerEstado();
	Posicion* obtenerPosicion();
	bool esMio(unsigned int);
	void notificar();
	unsigned int obtenerID();
	int obtenerAncho();
	int obtenerAlto();
};

#endif /* DUMMY_H_ */
